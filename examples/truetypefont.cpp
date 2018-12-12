#include <ffw/graphics.h>
#include <iostream>

class App : public ffw::GLRenderWindow {
public:
    App(const ffw::RenderWindowArgs& args) :GLRenderWindow(args, nullptr) {

        // Create canvas using a GLCanvas::Settings. The canvas will hold the states
        // such as current color, transforms, etc...
        canvas = ffw::GLCanvas(ffw::GLCanvas::Settings());
        font = canvas.createFont("OpenSans-Regular.ttf");
        angle = 0.0f;

        // Background color
        glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
    }
    ~App() {
    }

    void render() override {
        static const std::string str = // UTF-8 encoded string as hex
            "\x41\x42\x43\xc4\x8c\xc4\x86\x44\xc4\x90\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\n"
            "\x4e\x4f\x50\x51\x52\x53\xc5\xa0\x54\x55\x56\x57\x58\x59\x5a\xc5\xbd\x61\x0a"
            "\x62\x63\xc4\x8d\xc4\x87\x64\xc4\x91\x65\x66\x67\x68\x69\x6a\x6b\x6c\x6d\x6e\x0a"
            "\x6f\x70\x71\x72\x73\xc5\xa1\x74\x75\x76\x77\x78\x79\x7a\xc5\xbe\xd0\x90\xd0\x91\x0a"
            "\xd0\x92\xd0\x93\xd2\x90\xd0\x94\xd0\x82\xd0\x95\xd0\x81\xd0\x84\xd0\x96\xd0\x97\xd0\x85\xd0\x98\xd0\x86\xd0\x87\xd0\x99\xd0\x88\x0a"
            "\xd0\x9a\xd0\x9b\xd0\x89\xd0\x9c\xd0\x9d\xd0\x8a\xd0\x9e\xd0\x9f\xd0\xa0\xd0\xa1\xd0\xa2\xd0\x8b\xd0\xa3\xd0\x8e\xd0\xa4\xd0\xa5\x0a"
            "\xd0\xa6\xd0\xa7\xd0\x8f\xd0\xa8\xd0\xa9\xd0\xaa\xd0\xab\xd0\xac\xd0\xad\xd0\xae\xd0\xaf\xd0\xb0\xd0\xb1\xd0\xb2\xd0\xb3\xd2\x91\x0a"
            "\xd0\xb4\xd1\x92\xd0\xb5\xd1\x91\xd1\x94\xd0\xb6\xd0\xb7\xd1\x95\xd0\xb8\xd1\x96\xd1\x97\xd0\xb9\xd1\x98\xd0\xba\xd0\xbb\xd1\x99\x0a"
            "\xd0\xbc\xd0\xbd\xd1\x9a\xd0\xbe\xd0\xbf\xd1\x80\xd1\x81\xd1\x82\xd1\x9b\xd1\x83\xd1\x9e\xd1\x84\xd1\x85\xd1\x86\xd1\x87\xd1\x9f\x0a";

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const auto size = getSize();

        canvas.beginFrame(size);

        canvas.fillColor(ffw::hsv(angle / 360.0f, 0.5f, 0.7f, 1.0f));
        canvas.fontFace(font);
        canvas.fontSize(28.0f);
        canvas.textLetterSpacing(std::sin(angle * DEG_TO_RAD) * 5.0f);
        canvas.textLineHeight(std::abs(std::cos(angle * DEG_TO_RAD)) + 1.0f);
        canvas.text(ffw::Vec2f(10.0f, 28.0f), str.c_str(), str.c_str() + str.size());

        canvas.endFrame();

        /*// You can also use:
        //   canvas.setColor(ffw::rgba(255, 0, 0, 255)); <- 100% red
        // or:
        //   canvas.setColor(ffw::Color(1.0f, 0.0f, 0.0f, 1.0f)); <- 100% red
        canvas.setColor(ffw::hsv(angle / 360.0f, 0.5f, 0.7f, 1.0f));
        canvas.setFontLineHeight(std::abs(std::cos(angle * DEG_TO_RAD)) + 1.0f);
        canvas.setFontSpacing(std::sin(angle * DEG_TO_RAD) * 5.0f);
        canvas.drawString(10, 10, &font, str);*/

        angle += 0.5f;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
    }
    void windowCloseEvent() override {
        this->shouldClose(true);
    }

private:
    ffw::GLCanvas canvas;
    ffw::GLCanvas::Font font;
    float angle;
};

///=============================================================================
int main(int argc, char *argv[]) {

    // set arguments
    ffw::RenderWindowArgs args;
    args.size = ffw::Vec2<int>(500, 500);
    args.title = "True Type Font Example";
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
