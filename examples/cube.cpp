#include <ffw/graphics.h>
#include <iostream>

#define EYES_DEFAULT_POS 1.7f, 1.7f, 1.7f
#define STRINGIFY(x) #x

///=============================================================================
static const std::string vertShaderSource = "#version 130\n" STRINGIFY(
    in vec3 position;
    in vec3 color;

    out vec3 out_color;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main() {
        out_color = color;
        gl_Position = projection * view * model * vec4(position, 1.0f);
    }
);

///=============================================================================
static const std::string fragShaderSource = "#version 130\n" STRINGIFY(
    in vec3 out_color;
    void main() {
        gl_FragColor = vec4(out_color, 1.0f);
    }
);

static const float cubeVertices [] = {
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    -1.0f, -1.0f,  1.0f, 0.0f, 1.0f, 0.0f,
    1.0f, -1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, -1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,

    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    -1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
    1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 1.0f,
    1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,

    -1.0f, -1.0f,  1.0f, 0.0f, 1.0f, 0.0f,
    -1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 0.0f,
    -1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
    -1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    -1.0f, -1.0f,  1.0f, 0.0f, 1.0f, 0.0f,

    -1.0f, -1.0f,  1.0f, 0.0f, 1.0f, 0.0f,
    1.0f, -1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
    1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f,
    1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f,
    -1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 0.0f,
    -1.0f, -1.0f,  1.0f, 0.0f, 1.0f, 0.0f,

    1.0f, -1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 1.0f,
    1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 1.0f,
    1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, -1.0f,  1.0f, 0.0f, 1.0f, 1.0f,

    1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 1.0f,
    1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f,
    -1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 0.0f,
    -1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 0.0f,
    -1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
    1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 1.0f,
};

///=============================================================================
class App : public ffw::GLRenderWindow {
public:
    App(const ffw::RenderWindowArgs& args) :GLRenderWindow(args, nullptr) {

        try {
            // Create our vertex array
            vertexArray = ffw::GLVertexArray(true);
            
            // Compile and link shaders into a program
            boxShaderVert = ffw::GLShader(GL_VERTEX_SHADER, vertShaderSource);
            boxShaderFrag = ffw::GLShader(GL_FRAGMENT_SHADER, fragShaderSource);
            boxProgram = ffw::GLProgram({
                &boxShaderVert, &boxShaderFrag
            });

            // Allocate VBO
            boxVbo = ffw::GLVertexBuffer(cubeVertices, sizeof(cubeVertices), GL_STATIC_DRAW);

            // set the position attribute to length 3 starting at position 0 in the vertex buffer
            // Each vertex has 8 floats total: {Px, Py, Pz, Nx, Ny, Nz, U, V}
            // Where P is position, N is normal and UV are texture coordinates
            vertexArray.setAttributePointerf(boxProgram.getAttributeLocation("position"), 3, 6 * sizeof(float), (void*)(0 * sizeof(float)));
            // set the normal attribute to length 3 starting at position 3 in the vertex buffer
            vertexArray.setAttributePointerf(boxProgram.getAttributeLocation("color"), 3, 6 * sizeof(float), (void*)(3 * sizeof(float)));

            vertexArray.unbind();
        }
        catch (ffw::GLException& e) {
            std::cerr << "Failed to initialize shaders: " << e.what() << std::endl;
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

        // set the model matrix
        modelMatrix = ffw::Mat4x4f(1.0f);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    }

    ~App() {
    }

    void render() override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Begin shader program
        boxProgram.bind();
        // Bind our vertex array
        // This VAO also holds the vertex buffers containing the vertex data
        // It does not hold the actual data, rather than a reference 
        vertexArray.bind();
        // set uniforms
        // set the model, view and projection matrices
        boxProgram.setUniformMatrix4fv(boxProgram.getUniformLocation("model"), &modelMatrix[0], 1);
        boxProgram.setUniformMatrix4fv(boxProgram.getUniformLocation("view"), &viewMatrix[0], 1);
        boxProgram.setUniformMatrix4fv(boxProgram.getUniformLocation("projection"), &projectionMatrix[0], 1);
        // draw whole object
        // 6 floats per one vertex
        boxProgram.drawArrays(GL_TRIANGLES, 0, boxVbo.getSize() / sizeof(float) / 6);
        
        // Stop object shader
        boxProgram.unbind();
        vertexArray.unbind();
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

            eyesRot.x += -diffx / 2;
            eyesRot.y += -diffy / 2;

            eyesPos.set(EYES_DEFAULT_POS);
            eyesPos.rotateY(eyesRot.x);

            // get penpedicular vector
            ffw::Vec3f axis((float)eyesPos.z, 0.0f, (float)-eyesPos.x);

            axis.normalize();

            //std::cout << "axis: " << axis << std::endl;
            eyesPos.rotateByAxis(eyesRot.y, axis);

            viewMatrix = ffw::makeLookAtMatrix(eyesPos, ffw::Vec3f(0.0f, 0.0f, 0.0f), ffw::Vec3f(0.0f, 1.0f, 0.0f));
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
    ffw::GLShader boxShaderFrag;
    ffw::GLShader boxShaderVert;
    ffw::GLProgram boxProgram;
    ffw::GLVertexBuffer boxVbo;
    ffw::GLVertexArray vertexArray;

    // Model, view and projection matrices used in shader
    ffw::Mat4x4f projectionMatrix;
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
    args.title = "Cube Example";
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
