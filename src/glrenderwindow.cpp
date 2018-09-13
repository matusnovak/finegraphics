/*** This file is part of FineFramework project ***/
#include <sstream>
#define FFW_DO_NOT_EXPORT_GL_PROC 1
#include "ffw/graphics/glrenderwindow.h"
#include "ffw/graphics/monitors.h"
#include <GLFW/glfw3.h>

static std::string lastError;

static const char* glfwErrorToStr(const int code) {
    switch(code) {
        case GLFW_NOT_INITIALIZED: return "GLFW_NOT_INITIALIZED";
        case GLFW_NO_CURRENT_CONTEXT: return "GLFW_NO_CURRENT_CONTEXT";
        case GLFW_INVALID_ENUM: return "GLFW_INVALID_ENUM";
        case GLFW_INVALID_VALUE: return "GLFW_INVALID_VALUE";
        case GLFW_OUT_OF_MEMORY: return "GLFW_OUT_OF_MEMORY";
        case GLFW_API_UNAVAILABLE: return "GLFW_API_UNAVAILABLE";
        case GLFW_VERSION_UNAVAILABLE: return "GLFW_VERSION_UNAVAILABLE ";
        case GLFW_PLATFORM_ERROR: return "GLFW_PLATFORM_ERROR";
        case GLFW_FORMAT_UNAVAILABLE: return "GLFW_FORMAT_UNAVAILABLE";
        default: return "UNKNOWN_ERROR";
    }
}

///=============================================================================
static void glfwErrorFunc(const int code, const char* msg) {
    std::stringstream ss;
    ss << msg << " (" << glfwErrorToStr(code) << ")";
    lastError = ss.str();
}

///=============================================================================
class GraphicsInitializer {
public:
    GraphicsInitializer() {
        counter = 0;
    }
    ~GraphicsInitializer() {
        if(counter >= 1) {
            glfwTerminate();
        }
    }
    bool init() {
        if (counter == 0) {
            glfwSetErrorCallback(&glfwErrorFunc);
            const auto result = glfwInit();
            if(!result) {
                return false;
            }
        }
        counter++;
        return true;
    }
private:
    size_t counter;
};

static GraphicsInitializer graphicsInitializer;

///=============================================================================
std::vector<ffw::Monitor> ffw::GLRenderWindow::getMonitors() {
    if(!graphicsInitializer.init()) {
        return std::vector<ffw::Monitor>();
    }
    
    int cnt;
    GLFWmonitor** monitorPtrs = glfwGetMonitors(&cnt);
    std::vector<Monitor> allMonitors;
    for (int i = 0; i < cnt; i++) {
        allMonitors.emplace_back(Monitor());

        allMonitors[i].name.assign(glfwGetMonitorName(monitorPtrs[i]));
        glfwGetMonitorPhysicalSize(monitorPtrs[i], &(allMonitors[i].physicalSize.x), &(allMonitors[i].physicalSize.y));
        glfwGetMonitorPos(monitorPtrs[i], &(allMonitors[i].position.x), &(allMonitors[i].position.y));
        const GLFWvidmode* mode = glfwGetVideoMode(monitorPtrs[i]);
        allMonitors[i].resolution.w = mode->width;
        allMonitors[i].resolution.h = mode->height;
        allMonitors[i].bitDepth.r = mode->redBits;
        allMonitors[i].bitDepth.g = mode->greenBits;
        allMonitors[i].bitDepth.b = mode->blueBits;
        allMonitors[i].refreshRate = mode->refreshRate;

        allMonitors[i].ptr = static_cast<void*>(monitorPtrs[i]);
    }
    return allMonitors;
}

///=============================================================================
ffw::Monitor ffw::GLRenderWindow::getPrimaryMonitor() {
    if (!graphicsInitializer.init()) {
        return ffw::Monitor();
    }
    
    GLFWmonitor* monitorPtr = glfwGetPrimaryMonitor();
    Monitor primaryMonitor;
    primaryMonitor.name.assign(glfwGetMonitorName(monitorPtr));
    glfwGetMonitorPhysicalSize(monitorPtr, &(primaryMonitor.physicalSize.x), &(primaryMonitor.physicalSize.y));
    glfwGetMonitorPos(monitorPtr, &(primaryMonitor.position.x), &(primaryMonitor.position.y));
    const GLFWvidmode* mode = glfwGetVideoMode(monitorPtr);
    primaryMonitor.resolution.w = mode->width;
    primaryMonitor.resolution.h = mode->height;
    primaryMonitor.bitDepth.r = mode->redBits;
    primaryMonitor.bitDepth.g = mode->greenBits;
    primaryMonitor.bitDepth.b = mode->blueBits;
    primaryMonitor.refreshRate = mode->refreshRate;

    primaryMonitor.ptr = monitorPtr;
    return primaryMonitor;
}

///=============================================================================
std::vector<ffw::Monitor::Mode> ffw::GLRenderWindow::getMonitorModes(const ffw::Monitor& monitor) {
    std::vector<Monitor::Mode> allModes;
    int cnt;
    const GLFWvidmode* modes = glfwGetVideoModes(reinterpret_cast<GLFWmonitor*>(monitor.ptr), &cnt);

    for (int i = 0; i < cnt; i++) {
        allModes.emplace_back(Monitor::Mode());
        allModes[i].resolution.w = modes[i].width;
        allModes[i].resolution.h = modes[i].height;
        allModes[i].bitDepth.r = modes[i].redBits;
        allModes[i].bitDepth.g = modes[i].greenBits;
        allModes[i].bitDepth.b = modes[i].blueBits;
        allModes[i].refreshRate = modes[i].refreshRate;
    }
    return allModes;
}

///=============================================================================
struct ffw::GLRenderWindow::WindowCallback{
    static void keyPressedCB            (GLFWwindow* windowContext, int key, int scancode, int action, int mods);
    static void textInputCB             (GLFWwindow* windowContext, unsigned int key);
    static void mouseMovedCB            (GLFWwindow* windowContext, double xpos, double ypos);
    static void mouseButtonPressedCB    (GLFWwindow* windowContext, int button,int action, int mods);
    static void mouseScrolledCB         (GLFWwindow* windowContext, double xoffset, double yoffset);
    static void windowShouldCloseCB     (GLFWwindow* windowContext);
    static void windowMovedCB           (GLFWwindow* windowContext, int xpos, int ypos);
    static void windowResizedCB         (GLFWwindow* windowContext, int width, int height);
    static void windowFocusCB           (GLFWwindow* windowContext, int focus);
    static void filesFroppedCB          (GLFWwindow* windowContext, int cnt, const char** files);
};

///=============================================================================
void ffw::GLRenderWindow::WindowCallback::keyPressedCB(GLFWwindow* windowContext, const int key, const int scancode, const int action, const int mods){
    (void)scancode;
    (void)mods;
    GLRenderWindow* windowPtr = static_cast<ffw::GLRenderWindow*>(glfwGetWindowUserPointer(windowContext));
    windowPtr->keyPressedEvent(static_cast<ffw::Key>(key), static_cast<ffw::KeyMode>(action));
}

///=============================================================================
void ffw::GLRenderWindow::WindowCallback::textInputCB(GLFWwindow* windowContext, const unsigned int key){
    GLRenderWindow* windowPtr = static_cast<ffw::GLRenderWindow*>(glfwGetWindowUserPointer(windowContext));
    windowPtr->textInputEvent(key);
}

///=============================================================================
void ffw::GLRenderWindow::WindowCallback::mouseMovedCB(GLFWwindow* windowContext, const double xpos, const double ypos){
    GLRenderWindow* windowPtr = static_cast<ffw::GLRenderWindow*>(glfwGetWindowUserPointer(windowContext));
    windowPtr->mouseMovedEvent(int(xpos), int(ypos));
}

///=============================================================================
void ffw::GLRenderWindow::WindowCallback::mouseButtonPressedCB(GLFWwindow* windowContext, const int button, const int action, const int mods){
    (void)mods;
    GLRenderWindow* windowPtr = static_cast<ffw::GLRenderWindow*>(glfwGetWindowUserPointer(windowContext));
    windowPtr->mouseButtonEvent(static_cast<ffw::MouseButton>(button), static_cast<ffw::MouseMode>(action));
}

///=============================================================================
void ffw::GLRenderWindow::WindowCallback::mouseScrolledCB(GLFWwindow* windowContext, const double xoffset, const double yoffset){
    (void)xoffset;
    GLRenderWindow* windowPtr = static_cast<ffw::GLRenderWindow*>(glfwGetWindowUserPointer(windowContext));
    windowPtr->mouseScrollEvent(int(yoffset));
}

///=============================================================================
void ffw::GLRenderWindow::WindowCallback::windowShouldCloseCB(GLFWwindow* windowContext){
    GLRenderWindow* windowPtr = static_cast<ffw::GLRenderWindow*>(glfwGetWindowUserPointer(windowContext));
    windowPtr->windowCloseEvent();
}

///=============================================================================
void ffw::GLRenderWindow::WindowCallback::windowMovedCB(GLFWwindow* windowContext, const int xpos, const int ypos){
    GLRenderWindow* windowPtr = static_cast<ffw::GLRenderWindow*>(glfwGetWindowUserPointer(windowContext));
    windowPtr->windowMovedEvent(xpos, ypos);
}

///=============================================================================
void ffw::GLRenderWindow::WindowCallback::windowResizedCB(GLFWwindow* windowContext, const int width, const int height){
    GLRenderWindow* windowPtr = static_cast<ffw::GLRenderWindow*>(glfwGetWindowUserPointer(windowContext));
    windowPtr->windowResizedEvent(width, height);
}

///=============================================================================
void ffw::GLRenderWindow::WindowCallback::windowFocusCB(GLFWwindow* windowContext, const int focus){
    GLRenderWindow* windowPtr = static_cast<ffw::GLRenderWindow*>(glfwGetWindowUserPointer(windowContext));
    windowPtr->windowFocusEvent(focus == 1);
}

///=============================================================================
void ffw::GLRenderWindow::WindowCallback::filesFroppedCB(GLFWwindow* windowContext, const int cnt, const char** files){
    GLRenderWindow* windowPtr = static_cast<ffw::GLRenderWindow*>(glfwGetWindowUserPointer(windowContext));
    std::vector<std::string> fileList;
    fileList.resize(cnt);
    for(auto i = 0; i < cnt; i++){
        fileList[i].assign(files[i]);
    }
    windowPtr->filesDroppedEvent(fileList);
}

///=============================================================================
class ffw::GLRenderWindow::Impl{
public:
    ffw::GLRenderWindow* otherWindow;
    GLFWwindow* windowHandle;
    int sizeBeforeFillscreen[4];
    bool setupDone;
    bool initialized;
    bool closed;
    bool singleBuffer;
};

///=============================================================================
static void* getProcaddress(const char* str) {
    return reinterpret_cast<void*>(glfwGetProcAddress(str));
}

#include <iostream>

///=============================================================================
ffw::GLRenderWindow::GLRenderWindow(const RenderWindowArgs& args, GLRenderWindow* other, Monitor* monitor):pimpl(new Impl){
    pimpl->initialized = false;
    pimpl->setupDone = false;
    pimpl->otherWindow = nullptr;
    pimpl->windowHandle = nullptr;
    pimpl->closed = true;
    pimpl->singleBuffer = false;

    if (args.size.x < 0 || args.size.y < 0) throw WindowException("Incorrect window size");

    if (!graphicsInitializer.init())throw WindowException("GLFW Failed to initialise");

    glfwWindowHint(GLFW_RESIZABLE, args.resizable);
    glfwWindowHint(GLFW_DECORATED, args.border);
    glfwWindowHint(GLFW_AUTO_ICONIFY, args.maximize);
    glfwWindowHint(GLFW_FLOATING, args.floating);
    glfwWindowHint(GLFW_FOCUSED, args.focused);
    glfwWindowHint(GLFW_SAMPLES, args.samples);
    glfwWindowHint(GLFW_VISIBLE, args.visible);
    //glfwWindowHint(GLFW_DOUBLEBUFFER, !Args.singleBuffer);

    switch(args.glApi) {
        case ClientGLAPI::NONE: glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); break;
        case ClientGLAPI::OPENGL: glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API); break;
        case ClientGLAPI::OPENGL_ES: glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API); break;
        default: break;
    }

    GLFWwindow* parentWindowHandle = nullptr;
    GLFWmonitor* targetMonitor = nullptr;
    pimpl->otherWindow = other;

    if (other != nullptr)parentWindowHandle = other->pimpl->windowHandle;
    if (monitor != nullptr)targetMonitor = static_cast<GLFWmonitor*>(monitor->ptr);

    const auto newWindowContext = glfwCreateWindow(args.size.x, args.size.y, args.title.c_str(), targetMonitor, parentWindowHandle);

    if (newWindowContext == nullptr) throw WindowException("Failed to create a window " + lastError);

    if (args.pos.x != -1 && args.pos.y != -1)
        glfwSetWindowPos(newWindowContext, args.pos.x, args.pos.y);

    if (args.iconPtr != nullptr && args.iconWidth > 0 && args.iconHeight > 0) {
        GLFWimage image;
        image.width = args.iconWidth;
        image.height = args.iconHeight;
        image.pixels = const_cast<unsigned char*>(args.iconPtr);
        glfwSetWindowIcon(newWindowContext, 1, &image);
    }

    glfwSetWindowUserPointer(newWindowContext, this);
    glfwSetKeyCallback(newWindowContext, WindowCallback::keyPressedCB);
    glfwSetCursorPosCallback(newWindowContext, WindowCallback::mouseMovedCB);
    glfwSetMouseButtonCallback(newWindowContext, WindowCallback::mouseButtonPressedCB);
    glfwSetCharCallback(newWindowContext, WindowCallback::textInputCB);
    glfwSetScrollCallback(newWindowContext, WindowCallback::mouseScrolledCB);
    glfwSetWindowPosCallback(newWindowContext, WindowCallback::windowMovedCB);
    glfwSetWindowSizeCallback(newWindowContext, WindowCallback::windowResizedCB);
    glfwSetWindowCloseCallback(newWindowContext, WindowCallback::windowShouldCloseCB);
    glfwSetWindowFocusCallback(newWindowContext, WindowCallback::windowFocusCB);
    glfwSetDropCallback(newWindowContext, WindowCallback::filesFroppedCB);

    pimpl->initialized = true;
    pimpl->windowHandle = newWindowContext;
    pimpl->closed = false;

    glfwMakeContextCurrent(pimpl->windowHandle);
    loadGlCoreArb(&getProcaddress);

    glfwSwapInterval(1);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

///=============================================================================
ffw::GLRenderWindow::~GLRenderWindow(){
    if(pimpl != nullptr){
        glfwDestroyWindow(pimpl->windowHandle);
        pimpl.reset();
    }
}

///=============================================================================
void ffw::GLRenderWindow::setPos(const int posx, const int posy){
    if(!pimpl->initialized)return;
    glfwSetWindowPos(pimpl->windowHandle, posx, posy);
}

///=============================================================================
void ffw::GLRenderWindow::setSize(const int width, const int height){
    if(!pimpl->initialized)return;
    glfwSetWindowSize(pimpl->windowHandle, width, height);
}

///=============================================================================
ffw::Vec2<int> ffw::GLRenderWindow::getPos() const {
    Vec2<int> pos;
    if(!pimpl->initialized)return pos;
    glfwGetWindowPos(pimpl->windowHandle, &pos.x, &pos.y);
    return pos;
}

///=============================================================================
ffw::Vec2<int> ffw::GLRenderWindow::getSize() const {
    Vec2<int> size;
    if(!pimpl->initialized)return size;
    glfwGetFramebufferSize(pimpl->windowHandle, &size.x, &size.y);
    return size;
}

///=============================================================================
void ffw::GLRenderWindow::setWindowedMode() const {
    if(pimpl->initialized){
        const auto& s = pimpl->sizeBeforeFillscreen;
        glfwSetWindowMonitor(pimpl->windowHandle, nullptr, s[0], s[1], s[2], s[3], GLFW_DONT_CARE);
    }
}

///=============================================================================
void ffw::GLRenderWindow::setWindowedMode(const int posx, const int posy, const int width, const int height) const {
    if(pimpl->initialized){
        glfwSetWindowMonitor(pimpl->windowHandle, nullptr, posx, posy, width, height, GLFW_DONT_CARE);
    }
}

///=============================================================================
void ffw::GLRenderWindow::setFullscreen(const Monitor* monitor) const {
    if(pimpl->initialized && monitor != nullptr){
        pimpl->sizeBeforeFillscreen[0] = getPos().x; 
        pimpl->sizeBeforeFillscreen[1] = getPos().y;
        pimpl->sizeBeforeFillscreen[2] = getSize().x;
        pimpl->sizeBeforeFillscreen[3] = getSize().y;
        glfwSetWindowMonitor(pimpl->windowHandle, nullptr, 0, 0, monitor->resolution.w, monitor->resolution.h, monitor->refreshRate);
    }
}

///=============================================================================
void ffw::GLRenderWindow::shouldClose(const bool close){
    pimpl->closed = close;
}

///=============================================================================
void ffw::GLRenderWindow::renderFrame(){
    if(!pimpl->initialized)return;

    glfwMakeContextCurrent(pimpl->windowHandle);

    if(pimpl->singleBuffer){
        glDrawBuffer(GL_FRONT);
    }

    int size[2];
    glfwGetWindowSize(pimpl->windowHandle, &size[0], &size[1]);

    glViewport(0, 0, size[0], size[1]);

    this->render();

    if(pimpl->singleBuffer){
        glFlush();
        glFinish();
    } else {
        glfwSwapBuffers(pimpl->windowHandle);
    }
}

///=============================================================================
void ffw::GLRenderWindow::poolEvents(){
    glfwPollEvents();
}

///=============================================================================
void ffw::GLRenderWindow::waitForEvents(){
    glfwWaitEvents();
}

///=============================================================================
bool ffw::GLRenderWindow::isInitialized() const {
    return pimpl->initialized;
}

///=============================================================================
bool ffw::GLRenderWindow::shouldRender() const {
    return !pimpl->closed;
}

///=============================================================================
void ffw::GLRenderWindow::show(){
    glfwShowWindow(pimpl->windowHandle);
}

///=============================================================================
void ffw::GLRenderWindow::hide(){
    glfwHideWindow(pimpl->windowHandle);
}

///=============================================================================
void ffw::GLRenderWindow::iconify(){
    glfwIconifyWindow(pimpl->windowHandle);
}

///=============================================================================
void ffw::GLRenderWindow::restore(){
    glfwRestoreWindow(pimpl->windowHandle);
}

///=============================================================================
void ffw::GLRenderWindow::maximize(){
#ifdef FFW_WINDOWS
    glfwMaximizeWindow(pimpl->windowHandle);
#endif
}

///=============================================================================
void* ffw::GLRenderWindow::getGlextFunc(const std::string& name) const {
    if(!pimpl->initialized)return nullptr;
    return reinterpret_cast<void*>(glfwGetProcAddress(name.c_str()));
}

///=============================================================================
bool ffw::GLRenderWindow::isGlextExtSupported(const std::string& name) const {
    if(!pimpl->initialized)return false;
    return (glfwExtensionSupported(name.c_str()) == GLFW_TRUE);
}

///=============================================================================
void ffw::GLRenderWindow::setSwapInterval(const int interval) const {
    if(!pimpl->initialized)return;
    glfwSwapInterval(interval);
}

///=============================================================================
void ffw::GLRenderWindow::setSingleBufferMode(const bool enabled) {
    pimpl->singleBuffer = enabled;
}

#if defined(FFW_WINDOWS)
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <GLFW/glfw3native.h>
void* ffw::GLRenderWindow::getWin32Window(){
    if (!pimpl || !pimpl->initialized) return nullptr;
    return reinterpret_cast<void*>(glfwGetWin32Window(pimpl->windowHandle));
}

void* ffw::GLRenderWindow::getWGLContext(){
    if (!pimpl || !pimpl->initialized) return nullptr;
    return reinterpret_cast<void*>(glfwGetWGLContext(pimpl->windowHandle));
}

#elif defined(FFW_LINUX)
#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>
void* ffw::GLRenderWindow::getX11Window(){
    if (!pimpl || !pimpl->initialized) return nullptr;
    return reinterpret_cast<void*>(glfwGetX11Window(pimpl->windowHandle));
}

void* ffw::GLRenderWindow::getX11Display(){
    if (!pimpl || !pimpl->initialized) return nullptr;
    return reinterpret_cast<void*>(glfwGetX11Display());
}

#elif defined(FFW_OSX)
#define GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_NSGL
#include <GLFW/glfw3native.h>
void* ffw::GLRenderWindow::getCocoaWindow(){
    if (!pimpl || !pimpl->initialized) return nullptr;
    return reinterpret_cast<void*>(glfwGetCocoaWindow(pimpl->windowHandle));
}

void* ffw::GLRenderWindow::getNSGLContext(){
    if (!pimpl || !pimpl->initialized) return nullptr;
    return reinterpret_cast<void*>(glfwGetNSGLContext(pimpl->windowHandle));
}

#endif

///=============================================================================
void ffw::GLRenderWindow::textInputEvent(unsigned int c){(void)c;}
void ffw::GLRenderWindow::keyPressedEvent(ffw::Key key, ffw::KeyMode mode){(void)key; (void)mode;}
void ffw::GLRenderWindow::mouseMovedEvent(int mousex, int mousey){(void)mousex; (void)mousey;}
void ffw::GLRenderWindow::mouseScrollEvent(int scroll){(void)scroll;}
void ffw::GLRenderWindow::mouseButtonEvent(ffw::MouseButton button, ffw::MouseMode mode){(void)button; (void)mode;}
void ffw::GLRenderWindow::windowResizedEvent(int width, int height){(void)width; (void)height;}
void ffw::GLRenderWindow::windowMovedEvent(int posx, int posy){(void)posx; (void)posy;}
void ffw::GLRenderWindow::windowCloseEvent(){}
void ffw::GLRenderWindow::windowFocusEvent(bool focus){(void)focus;}
void ffw::GLRenderWindow::filesDroppedEvent(std::vector<std::string> filelist){(void)filelist;}
