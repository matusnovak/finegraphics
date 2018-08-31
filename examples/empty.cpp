#include <ffw/graphics.h>
#include <iostream>

///=============================================================================
class App : public ffw::GLRenderWindow {
public:
    App(const ffw::RenderWindowArgs& args):GLRenderWindow(args, nullptr) {

        // Create canvas using a GLCanvas::Settings. The canvas will hold the states
        // such as current color, transforms, etc...
        canvas = ffw::GLCanvas(ffw::GLCanvas::Settings());

        // Background color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    ~App() {
    }

    void render() override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const auto size = getSize();
        
        canvas.beginFrame(size);

        canvas.beginPath();
        canvas.roundedRect(
            ffw::Vec2f(10.0f, 10.0f), // pos
            size - ffw::Vec2f(20.0f, 20.0f), // size
            10.0f // roundness
        );
        canvas.fillColor(ffw::hsv(0.0f, 0.7f, 0.8f, 1.0f));
        canvas.fill();
        canvas.strokeWidth(10.0f);
        canvas.strokeColor(ffw::hsv(0.7f, 0.5f, 0.5f, 0.5f));
        canvas.stroke();

        canvas.endFrame();
    }

    void textInputEvent(const unsigned int c) override {

    }

    void keyPressedEvent(const ffw::Key key, const ffw::KeyMode mode) override {
        if (mode == ffw::KeyMode::PRESSED)
            std::cout << "Key pressed: " << int(key) << std::endl;
    }

    void mouseMovedEvent(const int mousex, const int mousey) override {
        std::cout << "Mouse moved to: " << mousex << "x" << mousey << std::endl;
        mousePos.set(mousex, mousey);
    }

    void mouseScrollEvent(const int scroll) override {
        std::cout << "Mouse scroll: " << scroll << std::endl;
    }

    void mouseButtonEvent(const ffw::MouseButton button, const ffw::MouseMode mode) override {
        if (mode == ffw::MouseMode::PRESSED) {
            switch (button) {
                case ffw::MouseButton::LEFT: std::cout << "Left mouse button pressed!" << std::endl; break;
                case ffw::MouseButton::MIDDLE: std::cout << "middle mouse button pressed!" << std::endl; break;
                case ffw::MouseButton::RIGHT: std::cout << "Right mouse button pressed!" << std::endl; break;
                default: break;
            }
        }
    }

    void windowResizedEvent(const int width, const int height) override {
        std::cout << "Window resized to: " << width << "x" << height << std::endl;
    }

    void windowMovedEvent(const int windowx, const int windowy) override {
        std::cout << "Window moved to: " << windowx << "x" << windowy << std::endl;
    }

    void windowFocusEvent(const bool focus) override {
        if (focus)std::cout << "Focus gained!" << std::endl;
        else std::cout << "Focus lost!" << std::endl;
    }

    void windowCloseEvent() override {
        std::cout << "Window close button pressed!" << std::endl;
        this->shouldClose(true);
    }

    void filesDroppedEvent(std::vector<std::string> filelist) override {
        std::cout << "Files dropped: " << std::endl;
        for (const auto& file : filelist) {
            std::cout << "\t\'" << file << "\'" << std::endl;
        }
    }

private:
    ffw::GLCanvas canvas;
    ffw::Vec2f mousePos;
};

///=============================================================================
int main(int argc, char *argv[]) {

    // set arguments
    ffw::RenderWindowArgs args;
    args.size = ffw::Vec2<int>(400, 400);
    args.title = "Empty Example";
    args.samples = 4;

    // Instance to our app class
    try {
        App app(args);

        // The main window loop
        while (app.shouldRender()) {
            app.renderFrame();
            app.poolEvents();
        }

        return EXIT_SUCCESS;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
