/* This file is part of FineFramework project */
#ifndef FFW_GRAPHICS_GL_RENDER_WINDOW
#define FFW_GRAPHICS_GL_RENDER_WINDOW

#include <vector>
#include <memory>
#include "renderwindow.h"
#include "monitors.h"
#include "vec2.h"
#include "config.h"
#include "constants.h"

namespace ffw {
    /**
     * @ingroup graphics
     * @brief An OpenGL render window using GLFW library
     */
    class FFW_API GLRenderWindow: public RenderWindow {
    public:
        /**
        * @brief Returns a vector of all physical monitors available
        */
        static std::vector<Monitor> getMonitors();
        /**
        * @brief Returns the primary monitor defined by the OS
        */
        static Monitor getPrimaryMonitor();
        /**
        * @brief Returns all possible modes for the given monitor
        */
        static std::vector<Monitor::Mode> getMonitorModes(const Monitor& monitor);
        /**
        * @brief Creates the window
        * @param args    Arguments and hints for the window
        * @param other   If another window is provided, their OpenGL context will be shared,
        *                otherwise NULL
        * @param monitor If a monitor is provided, the window will be fullscreen
        */
        GLRenderWindow(const RenderWindowArgs& args, GLRenderWindow* other, Monitor* monitor = nullptr);
        virtual ~GLRenderWindow();
        /**
         * @brief Sets the position of the window relative to the framebuffer
         * @note This function must only be called from the main thread.
         */
        void setPos(int posx, int posy) override;
        /**
         * @brief Sets the size of the window's framebuffer
         * @note This function must only be called from the main thread.
         */
        void setSize(int width, int height) override;
        /**
         * @brief Returns the position of the window relative to the framebuffer (not relative to
         * the OS specific border around the window)
         */
        Vec2<int> getPos() const override;
        /**
         * @brief Returns the size of the window's framebuffer (does not include the OS specific 
         * border)
         */
        Vec2<int> getSize() const override;
        /**
        * @brief Sets the window into windowed mode, if the window was in maximized mode
        * @note This function must only be called from the main thread.
        * @details This function sets the window in windowed mode. This function does not update
        * the height, width, or position. Instead, it uses the last size and position before
        * entering fullscreen mode.
        */
        void setWindowedMode() const;
        /**
        * @brief Sets the window into windowed mode with specific size and position
        * @note This function must only be called from the main thread.
        * @details This function sets the window in windowed mode. This function also updates
        * the widh, height, and position.
        */
        void setWindowedMode(int posx, int posy, int width, int height) const;
        /**
        * @brief Sets the window into fullscreen mode
        * @note This function must only be called from the main thread.
        * @details This function sets the monitor that the window uses for full screen mode. 
        * When setting a monitor, this function updates the width, height and refresh rate of 
        * the desired video mode and switches to the video mode closest to it. 
        * The window position is ignored when setting a monitor.
        */
        void setFullscreen(const Monitor* monitor) const;
        /**
         * @brief Returns true if shouldClose() has been set to true
         */
        bool shouldRender() const override;
        /**
         * @brief Renders the frame by setting up the context and calling protected method render()
         * @details This function makes the OpenGL or OpenGL ES context of the specified window 
         * current on the calling thread. A context can only be made current on a single thread 
         * at a time and each thread can have only a single current context at a time.
         * This function also calls glViewport with the current window's framebuffer size.
         */
        void renderFrame() override;
        /**
         * @brief Processes all user events 
         * @details This function processes only those events that are already in the event queue 
         * and then returns immediately. Processing events will cause the window and input callbacks 
         * associated with those events to be called. On some platforms, a window move, resize will
         * cause event processing to block. This is due to how event processing is designed on those 
         * platforms. You can use the window refresh callback to redraw the contents of your window 
         * when necessary during such operations.
         */
        void poolEvents() override;
        /**
        * @brief Waits for user events and processes them all
        * @note This function must only be called from the main thread.
        * @details This function puts the calling thread to sleep until at least one event is 
        * available in the event queue. Once one or more events are available, it behaves exactly 
        * like poolEvents, i.e. the events in the queue are processed and the function then returns 
        * immediately. Processing events will cause the window and input callbacks associated with 
        * those events to be called. Since not all events are associated with callbacks, 
        * this function may return without a callback having been called even if you are monitoring 
        * all callbacks. On some platforms, a window move, resize or menu operation will cause 
        * event processing to block. This is due to how event processing is designed on those 
        * platforms. You can use the window refresh callback to redraw the contents 
        * of your window when necessary during such operations.
        */
        void waitForEvents() override;
        /**
         * @brief Returns true if the window has been initialized
         * @note This function must only be called from the main thread.
         */
        bool isInitialized() const override;
        /**
         * @brief Returns the address of the specified function for the current context.
         * @details This function returns the address of the specified OpenGL or OpenGL ES 
         * core or extension function, if it is supported by the current context. 
         * A context must be current on the calling thread. Calling this function without
         * a current context will cause a GLFW_NO_CURRENT_CONTEXT error.
         * @code
         * PFNGLACTIVETEXTUREPROC myGlActiveTexture = getGlextFunc("glActiveTexture");
         * if (myGlActiveTexture != nullptr) {
         *     std::cout << "myGlActiveTexture is loaded" << std::endl;
         * }
         * @endcode
         */
        void* getGlextFunc(const std::string& name) const override;
        /**
         * @brief Returns wheter given GL extension is supported.
         */
        bool isGlextExtSupported(const std::string& name) const override;
        /**
         * @brief Sets swap interval (enables or disables V-sync)
         * @note This function must only be called from the main thread.
         */
        void setSwapInterval(int interval) const;
        /**
         * @brief Sets the internal should close flag
         * @details This function sets the swap interval for the current OpenGL or 
         * OpenGL ES context, i.e. the number of screen updates to wait from the time 
         * glfwSwapBuffers was called before swapping the buffers and returning. This is 
         * sometimes called vertical synchronization, vertical retrace synchronization or 
         * just vsync.
         */
        void shouldClose(bool close) override;
        /**
         * @brief Makes the window visible
         * @details This function makes the specified window visible if it was previously hidden. 
         * If the window is already visible or is in full screen mode, this function 
         * does nothing.
         * @note This function must only be called from the main thread.
         */
        void show() override;
        /**
         * @brief Makes the window hidden
         * @details This function hides the specified window if it was previously visible.
         * If the window is already hidden or is in full screen mode, this function 
         * does nothing.
         * @note This function must only be called from the main thread.
         */
        void hide() override;
        /**
         * @brief Iconifies the specified window
         * @details This function iconifies (minimizes) the specified window if it was previously 
         * restored. If the window is already iconified, this function does nothing.If the 
         * specified window is a full screen window, the original monitor resolution is restored 
         * until the window is restored.
         * @note This function must only be called from the main thread.
         */
        void iconify() override;
        /**
         * @brief Restores the specified window
         * @details This function restores the specified window if it was previously iconified 
         * (minimized) or maximized. If the window is already restored, this function does nothing.
         * If the specified window is a full screen window, the resolution chosen for the window 
         * is restored on the selected monitor.
         * @note This function must only be called from the main thread.
         */
        void restore() override;
        /**
         * @brief Maximizes the specified window
         * @details This function maximizes the specified window if it was previously not
         * maximized. If the window is already maximized, this function does nothing. 
         * If the specified window is a full screen window, this function does nothing.
         * @note This function must only be called from the main thread.
         */
        void maximize() override;
        /**
         * @brief Sets single buffer mode
         * @details In single buffer mode, no back and front buffer swapping is done. Instead,
         * glFlush and glFinish is used.
         * @note This function must only be called from the main thread.
         */
        void setSingleBufferMode(bool enabled) override;
#if defined(FFW_WINDOWS)
        /**
         * @code
         * reinterpret_cast<HWND>(window->getCocoaWindow());
         * @endcode
         */
        void* getWin32Window();
        /**
         * @code
         * reinterpret_cast<HGLRC>(window->getCocoaWindow());
         * @endcode
         */
        void* getWGLContext();
#elif defined(FFW_LINUX)
        /**
         * @code
         * reinterpret_cast<Window>(window->getCocoaWindow());
         * @endcode
         */
        void* getX11Window();
        /**
         * @code
         * reinterpret_cast<Display*>(window->getCocoaWindow());
         * @endcode
         */
        void* getX11Display();
#elif defined(FFW_OSX)
        /**
         * @code
         * reinterpret_cast<NSWindow>(window->getCocoaWindow());
         * @endcode
         */
        void* getCocoaWindow();
        /**
         * @code
         * reinterpret_cast<NSOpenGLContext>(window->getCocoaWindow());
         * @endcode
         */
        void* getNSGLContext();
#endif
        struct WindowCallback;
        friend struct WindowCallback;
    protected:
        /**
        * @brief Called every time the frame is being rendered
        */
        virtual void render() = 0;
        /**
        * @brief Called when the user presses a key to type text (unicode only)
        */
        virtual void textInputEvent(unsigned int c);
        /**
        * @brief Called when the user presses a physical key
        */
        virtual void keyPressedEvent(ffw::Key key, ffw::KeyMode mode);
        /**
        * @brief Called when the user moves a mouse
        */
        virtual void mouseMovedEvent(int mousex, int mousey);
        /**
        * @brief Called when the user scrolls down or up
        */
        virtual void mouseScrollEvent(int scroll);
        /**
        * @brief Called when the user presses a mouse button
        */ 
        virtual void mouseButtonEvent(ffw::MouseButton button, ffw::MouseMode mode);
        /**
        * @brief Called when the window is resized to a new size
        */
        virtual void windowResizedEvent(int width, int height);
        /**
        * @brief Called when the window is moved to a new position
        */
        virtual void windowMovedEvent(int posx, int posy);
        /**
        * @brief Called when the user presses the [X] button on the window
        */
        virtual void windowCloseEvent();
        /**
        * @brief Called when the window will gain or looses focus
        */
        virtual void windowFocusEvent(bool focus);
        /**
        * @brief Called when the user drags and drops one or multiple files
        * @note UTF-8 enabled
        */
        virtual void filesDroppedEvent(std::vector<std::string> filelist);
    private:
        class Impl;
        std::unique_ptr<Impl> pimpl;
    };
};

#endif
