#include <iostream>
#include <fstream>
#include <ffw/graphics.h>
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tiny_obj_loader.h"

#define EYES_DEFAULT_POS 1.7f, 1.7f, 1.7f
#define STRINGIFY(x) #x

///=============================================================================
static const std::string monkeyVertexShaderCode = "#version 140\n" STRINGIFY(
    in vec3 position;
    in vec3 normals;
    in vec2 texCoords;

    out vec3 v_normals;
    out vec3 v_position;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main() {
        v_normals = mat3(transpose(inverse(model))) * normals;
        v_position = vec4(model * vec4(position, 1.0)).xyz;
        gl_Position = projection * view * model * vec4(position, 1.0);
    }
);

///=============================================================================
static const std::string monkeyFragmentShaderCode = "#version 140\n" STRINGIFY(
    in vec3 v_normals;
    in vec3 v_position;

    uniform samplerCube sampler;
    uniform vec3 eyespos;

    const float brightness = 2.0;

    void main() {
        vec3 I = normalize(v_position - eyespos);
        vec3 R = reflect(I, normalize(v_normals));
        vec3 reflection = texture(sampler, R).rgb;
        gl_FragColor = vec4(mix(R, reflection, 0.8), 1.0) * brightness;
    }
);

///=============================================================================
// Skybox shader credits: https://learnopengl.com/#!Advanced-OpenGL/Cubemaps
static const std::string skyboxVertexShaderCode = "#version 130\n" STRINGIFY(
    in vec3 position;

    out vec3 v_texcoords;

    uniform mat4 projection;
    uniform mat4 view;

    void main() {
        v_texcoords = position;
        gl_Position = projection * view * vec4(position * 100.0, 1.0);
    }
);

///=============================================================================
static const std::string skyboxFragmentShaderCode = "#version 130\n" STRINGIFY(
    in vec3 v_texcoords;

    uniform samplerCube sampler;

    const float brightness = 2.0;

    void main() {
        gl_FragColor = texture(sampler, v_texcoords) * brightness;
    }
);

// The following represents skybox vertices needed to create a 3D cube
float skyboxVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f,  1.0f
};

///=============================================================================
static ffw::GLVertexBuffer loadObj(const std::string& fileName) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string err;
    const auto ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, fileName.c_str());

    if (!err.empty() && !ret) { // `err` may contain warning message.
        throw std::runtime_error(err);
    }

    if (shapes.size() != 1) throw std::runtime_error("Expected only one shape object!");

    const auto total = shapes[0].mesh.num_face_vertices.size() * 3 * 8;
    std::unique_ptr<float[]> vertices(new float[total]);
    auto ptr = vertices.get();

    // Loop over faces(polygon)
    size_t index_offset = 0;
    for (size_t f = 0; f < shapes[0].mesh.num_face_vertices.size(); f++) {
        const auto fv = shapes[0].mesh.num_face_vertices[f];

        if (fv != 3) throw std::runtime_error("Mesh is not triangulated!");

        // Loop over vertices in the face.
        for (size_t v = 0; v < fv; v++) {

            // access to vertex
            tinyobj::index_t idx = shapes[0].mesh.indices[index_offset + v];
            ptr[0] = attrib.vertices[3 * idx.vertex_index + 0];
            ptr[1] = attrib.vertices[3 * idx.vertex_index + 1];
            ptr[2] = attrib.vertices[3 * idx.vertex_index + 2];
            ptr[3] = attrib.normals[3 * idx.normal_index + 0];
            ptr[4] = attrib.normals[3 * idx.normal_index + 1];
            ptr[5] = attrib.normals[3 * idx.normal_index + 2];
            ptr[6] = attrib.texcoords[2 * idx.texcoord_index + 0];
            ptr[7] = attrib.texcoords[2 * idx.texcoord_index + 1];

            ptr += 8;
        }
        index_offset += fv;

        // per-face material
        shapes[0].mesh.material_ids[f];
    }

    return ffw::GLVertexBuffer(vertices.get(), total * sizeof(float), GL_STATIC_DRAW);
}

///=============================================================================
class App : public ffw::GLRenderWindow {
public:
    App(const ffw::RenderWindowArgs& args) :GLRenderWindow(args, nullptr) {

        // Background color
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

        try {
            // Create our vertex array
            // Needed if running Core Profile
            vertexArray = ffw::GLVertexArray(true);

            // Compile and link shaders into a program
            monkeyShaderVert = ffw::GLShader(GL_VERTEX_SHADER, monkeyVertexShaderCode);
            monkeyShaderFrag = ffw::GLShader(GL_FRAGMENT_SHADER, monkeyFragmentShaderCode);
            monkeyProgram = ffw::GLProgram({
                &monkeyShaderVert, &monkeyShaderFrag
            });

            skyboxShaderVert = ffw::GLShader(GL_VERTEX_SHADER, skyboxVertexShaderCode);
            skyboxShaderFrag = ffw::GLShader(GL_FRAGMENT_SHADER, skyboxFragmentShaderCode);
            skyboxProgram = ffw::GLProgram({
                &skyboxShaderVert, &skyboxShaderFrag
            });

            // Allocate VBO
            skyboxVbo = ffw::GLVertexBuffer(skyboxVertices, sizeof(skyboxVertices), GL_STATIC_DRAW);
            monkeyVbo = loadObj("monkey.obj");

            // Load skybox textures
            skyboxTexture = ffw::GLTextureCubemap(1024, 1024, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE);

            // The order of the files corresponds with the side index needed by ffw::TextureCubemap
            static const std::string filenames[6] = {
                "skybox_right.raw",  // GL_TEXTURE_CUBE_MAP_POSITIVE_X = 0
                "skybox_left.raw",   // GL_TEXTURE_CUBE_MAP_NEGATIVE_X = 1
                "skybox_top.raw",    // GL_TEXTURE_CUBE_MAP_POSITIVE_Y = 2
                "skybox_bottom.raw", // GL_TEXTURE_CUBE_MAP_NEGATIVE_Y = 3
                "skybox_front.raw",  // GL_TEXTURE_CUBE_MAP_POSITIVE_Z = 4
                "skybox_back.raw",   // GL_TEXTURE_CUBE_MAP_NEGATIVE_Z = 5
            };

            static char pixels[1024 * 1024 * 3]; // Expected size

            for (auto i = 0; i < 6; i++) {
                std::fstream file(filenames[i], std::ios::in | std::ios::binary);

                file.read(pixels, sizeof(pixels));

                skyboxTexture.setPixels(0, 0, 0, 1024, 1024, i, pixels);
            }
        }
        catch (std::exception& e) {
            std::cerr << "Failed to initialize: " << e.what() << std::endl;
        }

        eyesPos.set(EYES_DEFAULT_POS);

        // This is not the most efficient way to calculate 
        // Model-View-Projection
        // We are doing it this way just for the purpose
        // of the example...

        // get the aspect ratio of the window
        const auto windowSize = getSize();
        const auto aspectRatio = windowSize.x / float(windowSize.y);
        // create the projection matrix
        // 60 deg field of view
        // 0.1 near distance of frustum
        // 1000.0 far distance of frustum
        projectionMatrix = ffw::makeProjectionMatrix(60.0f, aspectRatio, 0.05f, 1000.0f);

        // set the view matrix
        //viewMatrix = ffw::Mat4x4f(1.0f);
        viewMatrix = ffw::makeLookAtMatrix(eyesPos, ffw::Vec3f(0.0f, 0.0f, 0.0f), ffw::Vec3f(0.0f, 1.0f, 0.0f));
        skyboxViewMatrix = ffw::makeLookAtMatrix(ffw::Vec3f(0.0f, 0.0f, 0.0f), -eyesPos, ffw::Vec3f(0.0f, 1.0f, 0.0f));

        // set the model matrix
        modelMatrix = ffw::Mat4x4f(1.0f);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    ~App() {
    }

    void render() override {
        // Blending is needed by the font
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (!monkeyVbo.isCreated() || !skyboxTexture.isCreated()) return;

        // Render the skybox
        glDisable(GL_DEPTH_TEST);

        skyboxProgram.bind(); // Use shader
        skyboxVbo.bind(); // Bind VBO
        skyboxTexture.bind(); // Bind cube map texture

        skyboxProgram.setUniform1i(skyboxProgram.getUniformLocation("sampler"), 0);
        skyboxProgram.setAttributePointerf(skyboxProgram.getAttributeLocation("position"), 3, 3 * sizeof(float), 0);
        skyboxProgram.setUniformMatrix4fv(skyboxProgram.getUniformLocation("view"), &skyboxViewMatrix[0], 1);
        skyboxProgram.setUniformMatrix4fv(skyboxProgram.getUniformLocation("projection"), &projectionMatrix[0], 1);
        // draw whole object
        skyboxProgram.drawArrays(GL_TRIANGLES, 0, 36);

        // Render the monkey
        glEnable(GL_DEPTH_TEST);

        monkeyProgram.bind();
        monkeyVbo.bind();
        skyboxTexture.bind(); // Bind skybox texture for reflection (see GLSL)

                       // set uniforms and attribute pointers
                       // set the texture sampler to 0 (GL_TEXTURE0)
        monkeyProgram.setUniform1i(monkeyProgram.getUniformLocation("sampler"), 0);
        // Set the eyes pos needed by the reflection algorithm
        monkeyProgram.setUniform3f(monkeyProgram.getUniformLocation("eyespos"), eyesPos);
        // set the position attribute to length 3 starting at position 0 in the vertex buffer
        // Each vertex has 8 floats total: {Px, Py, Pz, Nx, Ny, Nz, U, V}
        // Where P is position, N is normal and UV are texture coordinates
        monkeyProgram.setAttributePointerf(monkeyProgram.getAttributeLocation("position"), 3, 8 * sizeof(float), (void*)(0 * sizeof(float)));
        // set the normal attribute to length 3 starting at position 3 in the vertex buffer
        monkeyProgram.setAttributePointerf(monkeyProgram.getAttributeLocation("normals"), 3, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        // set the texture coordinates attribute to length 2 starting at position 6 in the vertex buffer
        monkeyProgram.setAttributePointerf(monkeyProgram.getAttributeLocation("texCoords"), 2, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        // set the model, view and projection matrices
        monkeyProgram.setUniformMatrix4fv(monkeyProgram.getUniformLocation("model"), &modelMatrix[0], 1);
        monkeyProgram.setUniformMatrix4fv(monkeyProgram.getUniformLocation("view"), &viewMatrix[0], 1);
        monkeyProgram.setUniformMatrix4fv(monkeyProgram.getUniformLocation("projection"), &projectionMatrix[0], 1);
        // draw whole object
        monkeyProgram.drawArrays(GL_TRIANGLES, 0, monkeyVbo.getSize() / 24);

        // Disable depth test
        // Depth test needs to be disabled in order to
        // draw user interface or any other 2D graphics components
        glDisable(GL_DEPTH_TEST);

        // Draw GUI or any 2D stuff here
    }

    void textInputEvent(unsigned int c) override {
    }

    void keyPressedEvent(ffw::Key key, ffw::KeyMode mode) override {
    }

    void mouseMovedEvent(int mousex, int mousey) override {
        if (mouseDown) {
            const auto diffx = mousex - mouseOld.x;
            const auto diffy = mousey - mouseOld.y;
            mouseOld.x = mousex;
            mouseOld.y = mousey;

            eyesRot.x += -diffx / 2.0f;
            eyesRot.y += -diffy / 2.0f;

            eyesPos.set(EYES_DEFAULT_POS);
            eyesPos.rotateY(eyesRot.x);

            // get penpedicular vector
            ffw::Vec3f axis(eyesPos.z, 0.0f, -eyesPos.x);

            axis.normalize();

            //std::cout << "axis: " << axis << std::endl;
            eyesPos.rotateByAxis(eyesRot.y, axis);

            viewMatrix = ffw::makeLookAtMatrix(eyesPos, ffw::Vec3f(0.0f, 0.0f, 0.0f), ffw::Vec3f(0.0f, 1.0f, 0.0f));
            skyboxViewMatrix = ffw::makeLookAtMatrix(ffw::Vec3f(0.0f, 0.0f, 0.0f), -eyesPos, ffw::Vec3f(0.0f, 1.0f, 0.0f));
        }
        else {
            mouseOld.x = mousex;
            mouseOld.y = mousey;
        }
    }

    void mouseScrollEvent(int scroll) override {
    }

    void mouseButtonEvent(ffw::MouseButton button, ffw::MouseMode mode) override {
        if (mode == ffw::MouseMode::PRESSED)mouseDown = true;
        else mouseDown = false;
    }

    void windowResizedEvent(int width, int height) override {
        // Get the aspect ratio of the window
        float aspectRatio = width / float(height);
        // create the projection matrix
        // 60 deg field of view
        // 0.1 near distance of frustum
        // 1000.0 far distance of frustum
        projectionMatrix = ffw::makeProjectionMatrix(60.0f, aspectRatio, 0.05f, 1000.0f);
    }

    void windowMovedEvent(int windowx, int windowy) override {
    }

    void windowFocusEvent(bool focus) override {
    }

    void windowCloseEvent() override {
        this->shouldClose(true);
    }

    void filesDroppedEvent(std::vector<std::string> filelist) override {
    }

private:
    ffw::GLShader monkeyShaderFrag;
    ffw::GLShader monkeyShaderVert;
    ffw::GLProgram monkeyProgram;
    ffw::GLVertexBuffer monkeyVbo;

    ffw::GLShader skyboxShaderFrag;
    ffw::GLShader skyboxShaderVert;
    ffw::GLProgram skyboxProgram;
    ffw::GLVertexBuffer skyboxVbo;

    ffw::GLTextureCubemap skyboxTexture;
    ffw::GLVertexArray vertexArray;

    // Model, view and projection matrices used in shader
    ffw::Mat4x4f projectionMatrix;
    ffw::Mat4x4f skyboxViewMatrix;
    ffw::Mat4x4f viewMatrix;
    ffw::Mat4x4f modelMatrix;

    ffw::Vec3f eyesPos;
    bool mouseDown = false;
    ffw::Vec2i mouseOld;
    ffw::Vec2f eyesRot;
};

///=============================================================================
int main(int argc, char *argv[]) {

    // set arguments
    ffw::RenderWindowArgs args;
    args.size = ffw::Vec2<int>(800, 600);
    args.title = "Cubemap Example";
    args.samples = 4;
    args.setCore(); // Sets core profile

    // Instance to our app class
    try {
        App app(args);

        // The main window loop
        while (app.shouldRender()) {
            app.renderFrame();
            app.poolEvents();
        }

        return EXIT_SUCCESS;
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
