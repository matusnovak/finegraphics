/* This file is part of FineFramework project */
#ifndef FFW_GRAPHICS_EXCEPTIONS
#define FFW_GRAPHICS_EXCEPTIONS

#include <stdexcept>
#include <string>

namespace ffw {
    /**
    * @ingroup graphics
    */
    class GLException : public std::runtime_error {
    public:
        GLException(const char* msg) :std::runtime_error(msg) {

        }
        GLException(const std::string& msg) :std::runtime_error(msg) {

        }
    };
};

#endif