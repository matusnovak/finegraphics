#include <ffw/graphics.h>
#include <iostream>
#include <chrono>
#include <ctime>

///=============================================================================
class App : public ffw::GLRenderWindow {
public:
    App(const ffw::RenderWindowArgs& args) :GLRenderWindow(args, nullptr) {

        // Create canvas using a GLCanvas::Settings. The canvas will hold the states
        // such as current color, transforms, etc...
        canvas = ffw::GLCanvas(ffw::GLCanvas::Settings());

        // Background color
        glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
    }

    ~App() {
    }

    void render() override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Get local time
        const auto now = std::chrono::system_clock::now();
        const auto t = std::chrono::system_clock::to_time_t(now);
        std::tm* time = std::localtime(&t);

        const auto size = getSize();
        const auto width = std::min(size.x, size.y) / 2.0f - 40.0f;

        canvas.beginFrame(size);

        canvas.beginPath();
        canvas.strokeColor(ffw::Color(0.1f, 0.1f, 0.1f, 0.5f));
        canvas.strokeWidth(6.0f);
        canvas.arc(size / 2.0f, width, 0.0f, 360.0f, ffw::GLCanvas::Winding::CCW);
        canvas.stroke();

        // Convert time to angles
        const auto hours = (360.0f - time->tm_hour * (360.0f / 24.0f));
        const auto minutes = (360.0f - time->tm_min * (360.0f / 60.0f)) + 180.0f;
        const auto seconds = (360.0f - time->tm_sec * (360.0f / 60.0f)) + 180.0f;

        // Convert angles to 2D points
        const auto hoursPos = ffw::Vec2f(std::sin(hours * DEG_TO_RAD), std::cos(hours * DEG_TO_RAD)) * width * 0.5f;
        const auto minutesPos = ffw::Vec2f(std::sin(minutes * DEG_TO_RAD), std::cos(minutes * DEG_TO_RAD)) * width * 0.8f;
        const auto secondsPos = ffw::Vec2f(std::sin(seconds * DEG_TO_RAD), std::cos(seconds * DEG_TO_RAD)) * width * 0.8f;

        // Draw hours
        canvas.strokeWidth(6.0f);
        canvas.beginPath();
        canvas.moveTo(size / 2.0f);
        canvas.lineTo(size / 2.0f + hoursPos);
        canvas.stroke();

        // Draw minutes
        canvas.strokeWidth(4.0f);
        canvas.beginPath();
        canvas.moveTo(size / 2.0f);
        canvas.lineTo(size / 2.0f + minutesPos);
        canvas.stroke();

        // Draw seconds
        canvas.strokeWidth(2.0f);
        canvas.strokeColor(ffw::Color(0.9f, 0.1f, 0.1f, 0.5f));
        canvas.beginPath();
        canvas.moveTo(size / 2.0f);
        canvas.lineTo(size / 2.0f + secondsPos);
        canvas.stroke();

        canvas.endFrame();
    }

    void windowCloseEvent() override {
        this->shouldClose(true);
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
    args.title = "Clock Example";
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
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
