#include <ffw/graphics.h>
#include <iostream>

///=============================================================================
class App : public ffw::GLRenderWindow {
public:
    App(const ffw::RenderWindowArgs& args) :GLRenderWindow(args, nullptr) {

        // Create canvas using a GLCanvas::Settings. The canvas will hold the states
        // such as current color, transforms, etc...
        canvas = ffw::GLCanvas(ffw::GLCanvas::Settings());

        // Background color
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

        rotStep = 5.0f;
    }

    ~App() {
    }

    void drawBranch(const ffw::Vec2f& pos, const float dir, const float add, 
        const int steps, const float length) const {

        if (steps <= 0)return;

        canvas.strokeWidth(float(steps));
        canvas.beginPath();
        canvas.moveTo(pos);
        const auto end = pos + ffw::Vec2f(length, 0).rotate(dir);
        canvas.lineTo(end);
        canvas.stroke();

        drawBranch(end, dir - add, add, steps - 1, length * 0.9f);
        drawBranch(end, dir + add, add, steps - 1, length * 0.9f);
    }

    void render() override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const auto size = getSize();

        canvas.beginFrame(size);

        canvas.strokeColor(ffw::rgb(255, 255, 255));

        // In the moddile horizontally
        // 1 fourth from the bottom vertically
        const auto pos = ffw::Vec2f(size.x / 2.0f, size.y - size.y / 4.0f);
        const auto length = std::min(size.x, size.y) / 10;

        drawBranch(pos, 270.0f, rotStep, 10, length);

        canvas.endFrame();
    }

    void windowCloseEvent() override {
        this->shouldClose(true);
    }

    void mouseMovedEvent(int mousex, int mousey) override {
        rotStep = ffw::remap(float(mousex), 0.0f, float(getSize().x), 0.0f, 90.0f);
    }

private:
    ffw::GLCanvas canvas;
    ffw::Vec2f mousePos;
    float rotStep;
};

///=============================================================================
int main(int argc, char *argv[]) {

    // set arguments
    ffw::RenderWindowArgs args;
    args.size = ffw::Vec2<int>(800, 600);
    args.title = "Tree Example";
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
