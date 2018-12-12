#include <ffw/graphics.h>
#include <iostream>
#include <fstream>

///=============================================================================
class App : public ffw::GLRenderWindow {
public:
    App(const ffw::RenderWindowArgs& args) :GLRenderWindow(args, nullptr) {

        // Create canvas using a GLCanvas::Settings. The canvas will hold the states
        // such as current color, transforms, etc...
        canvas = ffw::GLCanvas(ffw::GLCanvas::Settings());

        // Background color
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

        // Load texture to be used as an image in canvas.
        // It is up to the user to provide image loader!
        // For the purpose of this example, we will use raw image file (raw uncompressed pixels)
        // Photo by Harm Weustink on Unsplash
        std::fstream file("owl.raw", std::ios::in | std::ios::binary);
        if (!file) throw std::runtime_error("Failed to open owl.raw");
        std::unique_ptr<char[]> pixels(new char[800 * 600 * 3]); // expected size
        file.read(pixels.get(), 800 * 600 * 3);
        file.close();

        texture = ffw::GLTexture2D(800, 600, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE, pixels.get());
        image = canvas.createImage(texture);
    }

    ~App() {
    }

    void render() override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const auto size = getSize();

        canvas.beginFrame(size);

        const auto paint = canvas.imagePattern(ffw::Vec2f(0.0f, 0.0f), size, 0.0f, image, 1.0f);

        canvas.beginPath();
        canvas.moveTo(ffw::Vec2f(0.0f, 0.0f));
        canvas.rect(ffw::Vec2f(0.0f, 0.0f), size);
        canvas.fillPaint(paint);
        canvas.fill();

        canvas.endFrame();
    }

    void windowCloseEvent() override {
        this->shouldClose(true);
    }

    void mouseMovedEvent(int mousex, int mousey) override {
        mousePos.set(mousex, mousey);
    }

private:
    ffw::GLCanvas canvas;
    ffw::Vec2f mousePos;
    ffw::GLTexture2D texture;
    ffw::GLCanvas::Image image;
};

///=============================================================================
int main(int argc, char *argv[]) {

    // set arguments
    ffw::RenderWindowArgs args;
    args.size = ffw::Vec2<int>(800, 600);
    args.title = "Image Example";
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
        char c;
        std::cin >> c;
        return EXIT_FAILURE;
    }
}
