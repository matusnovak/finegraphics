/* This file is part of FineFramework project */
#ifndef FFW_GRAPHICS_RENDER_WINDOW
#define FFW_GRAPHICS_RENDER_WINDOW

#include <string>
#include "glrenderextensions.h"
#include "vec2.h"

namespace ffw {
    /**
    * @ingroup graphics
    */
    class WindowException: public std::runtime_error {
    public:
        WindowException(const char* msg):std::runtime_error(msg) {
            
        }
        WindowException(const std::string& msg) :std::runtime_error(msg) {

        }
    };
    enum class ClientGLAPI {
        NONE,
        OPENGL,
        OPENGL_ES,
        ANY
    };
    /**
    * @ingroup graphics
    */
    struct FFW_API RenderWindowArgs {
        /**
         * @brief Which OpenGL API to use?
         */
        ClientGLAPI glApi = ClientGLAPI::ANY;
        /**
        * @brief Position of the window, set to [-1, -1] for the OS to decide
        */
        Vec2<int> pos = Vec2<int>(-1, -1);
        /**
        * @brief Size of the window
        */
        Vec2<int> size = Vec2<int>(400, 400);
        /**
        * @brief UTF-8 encoded title
        */
        std::string title;
        /**
        * @brief Can the user resize the window?
        */
        bool resizable = true;
        /**
        * @brief Does the window have a border?
        */
        bool border = true;
        /**
        * @brief Can the user maximize the window?
        */
        bool maximize = true;
        /**
        * @brief Should the window be always on top?
        */
        bool floating = false;
        /**
        * @brief Should the window be automatically focused on creation?
        */
        bool focused = true;
        /**
        * @brief Should the window be visible?
        */
        bool visible = true;
        /**
        * @brief Antialiasing samples, has to be in power of two
        */
        int samples = 0;
        /**
        * @brief Pointer to an array of pixels to be used as window icon (can be null)
        * @note The array must be 32bit image (8bit RGBA)
        */
        const unsigned char* iconPtr = nullptr;
        /**
        * @brief Window icon width
        */
        int iconWidth = 0;
        /**
        * @brief Window icon height
        */
        int iconHeight = 0;
    };
    /**
    * @ingroup graphics
    */
    class FFW_API RenderWindow {
    public:
        virtual ~RenderWindow() = default;
        /**
        * @brief Retuns the address of the GL extension function
        * @details The pointer to the GL extension function may not
        * be the same on different GL contexts!
        */
        virtual void* getGlextFunc(const std::string& name) const = 0;
        /**
        * @brief Returns true if the GL extension is suported
        * @details Checks if an GLEXT extension is supported, for example "GL_ARB_debug_output"
        */
        virtual bool isGlextExtSupported(const std::string& name) const = 0;
        /**
        * @brief Sets the position of the window
        */
        virtual void setPos(int posx, int posy) = 0;
        /**
        * @brief Sets the size of the window
        */
        virtual void setSize(int width, int height) = 0;
        virtual Vec2<int> getPos() const = 0;
        virtual Vec2<int> getSize() const = 0;
        /**
        * @brief Returns true if the window is not closed
        * @details When shouldClose() is called with a 'true' boolean value,
        * this function will then return false
        */
        virtual bool shouldRender() const = 0;
        /**
        * @brief Renders a frame
        */
        virtual void renderFrame() = 0;
        /**
        * @brief Pools all user input events, if any
        * @details This is blocking function that will return whenever there are
        * any events in the queue. If you wish to wait for the user first, see
        * waitForEvents()
        */
        virtual void poolEvents() = 0;
        /**
        * @brief Pools all user input events and waits if there is none
        * @details This is blocking function that will not return unless
        * there is at least one user event. If you wish to have continuous
        * rendering, even if there are no user events, use poolEvents()
        */
        virtual void waitForEvents() = 0;
        /**
        * @brief Returns true if the window is initialized
        */
        virtual bool isInitialized() const = 0;
        /**
        * @brief Set whether the window should close or stay alive
        */
        virtual void shouldClose(bool close) = 0;
        /**
        * @brief Shows the window if the window has been hidden
        */
        virtual void show() = 0;
        /**
        * @brief Hides the window if the window is visible
        */
        virtual void hide() = 0;
        /**
        * @brief Minimizes the window into the task bar
        */
        virtual void iconify() = 0;
        /**
        * @brief Restores minimized window into a visible window
        */
        virtual void restore() = 0;
        /**
        * @brief Maximizes the window in order to utilize whole screen
        * @details This is not the same as full screen mode!
        */
        virtual void maximize() = 0;
        /**
        * @brief Sets whether the window should operate using two
        * buffets (back and front) or only in one
        */
        virtual void setSingleBufferMode(bool enabled) = 0;
    };
};

#endif