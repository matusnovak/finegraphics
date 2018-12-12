#include <ffw/graphics.h>
#include <iostream>

#define STRINGIFY(x) #x

///=============================================================================
static const std::string vertShaderSource = "#version 330\n" STRINGIFY(
    in vec2 position;
    in vec3 color;

    out vec3 v_color;

    void main() {
        v_color = color;
        gl_Position = vec4(position, 0.0, 1.0);
    }
);

///=============================================================================
static const std::string fragShaderSource = "#version 330\n" STRINGIFY(
    uniform float alpha;

    in vec3 v_color;

    void main() {
        gl_FragColor = vec4(v_color, alpha);
    }
);

///=============================================================================
static const float vboPositionData [3 * 2] = {
    0.0f, 1.0f,
    1.0, -1.0f,
    -1.0f, -1.0f
};

///=============================================================================
static const float vboColorData [3 * 3] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

///=============================================================================
class App : public ffw::GLRenderWindow {
public:
    App(const ffw::RenderWindowArgs& args) :GLRenderWindow(args, nullptr) {
        glEnable(GL_BLEND);
        glDisable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Background color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        try {
            // Create our vertex array
            // Needed if running Core Profile
            vertexArray = ffw::GLVertexArray(true);

            // Compile and link shaders into a program
            vertShader = ffw::GLShader(GL_VERTEX_SHADER, vertShaderSource);
            fragShader = ffw::GLShader(GL_FRAGMENT_SHADER, fragShaderSource);
            program = ffw::GLProgram({
                &vertShader, &fragShader
            });

            // Allocate VBO
            vboPosition = ffw::GLVertexBuffer(vboPositionData, sizeof(vboPositionData), GL_STATIC_DRAW);
            vboColor = ffw::GLVertexBuffer(vboColorData, sizeof(vboColorData), GL_STATIC_DRAW);

            // Find out the location of shader attributes and uniforms
            locPosition = program.getAttributeLocation("position");
            locColor = program.getAttributeLocation("color");
            locAlpha = program.getUniformLocation("alpha");
        } catch (ffw::GLException& e) {
            std::cerr << "Failed to initialize shaders: " << e.what() << std::endl;
        }
    }

    ~App() {
    }

    void render() override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use the shader 
        program.bind();

        // Bind the position VBO to the location of locPosition.
        vboPosition.bind();
        program.setAttributePointerf(locPosition, 2 /* size */, 2 * sizeof(float) /* stride */, 0 /* offset */);

        // Bind the color VBO to the location of locPosition.
        vboColor.bind();
        program.setAttributePointerf(locColor, 3 /* size */, 3 * sizeof(float) /* stride */, 0 /* offset */);

        // Set the uniforms directly
        program.setUniform1f(locAlpha, 1.0f);

        // Draw the triangle of 3 vertices
        program.drawArrays(GL_TRIANGLES, 0, 3);
    }

    void windowCloseEvent() override {
        this->shouldClose(true);
    }

private:
    ffw::GLShader fragShader;
    ffw::GLShader vertShader;
    ffw::GLProgram program;
    ffw::GLVertexBuffer vboPosition;
    ffw::GLVertexBuffer vboColor;
    ffw::GLVertexArray vertexArray;
    int locColor;
    int locPosition;
    int locAlpha;
};

///=============================================================================
int main(int argc, char *argv[]) {

    // set arguments
    ffw::RenderWindowArgs args;
    args.size = ffw::Vec2<int>(640, 480);
    args.title = "Shader Example";
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
