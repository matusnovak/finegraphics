#include <ffw/graphics/glrenderwindow.h>
#include <ffw/graphics/exceptions.h>

class DummyApp: public ffw::GLRenderWindow {
public:
    DummyApp(const ffw::RenderWindowArgs& args):ffw::GLRenderWindow(args, nullptr) {
        
    }
    virtual ~DummyApp() = default;
    void render() override {
        
    }
    void shouldClose(bool close) override {
        
    }
};

#define DUMMY_APP \
    ffw::RenderWindowArgs args; \
    args.size.set(1280, 720); \
    args.visible = false; \
    args.setCore(); \
    DummyApp app(args);
