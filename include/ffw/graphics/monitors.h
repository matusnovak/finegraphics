/* This file is part of FineFramework project */
#ifndef FFW_GRAPHICS_MONITORS
#define FFW_GRAPHICS_MONITORS

#include <string>
#include "vec2.h"

namespace ffw{
    struct Resolution {
        int w = 0;
        int h = 0;
    };
    struct BitDepth {
        int r = 0;
        int g = 0;
        int b = 0;
    };
    /**
     * @ingroup graphics
     */
    struct Monitor {
        struct Mode {
            /**
            * @brief Resolution
            */
            Resolution resolution;
            /**
            * @brief Bith depth
            * @details
            *     - .x = RED
            *     - .y = GREEN
            *     - .z = BLUE
            */
            BitDepth bitDepth;
            /**
            * @brief The prefered refresh rate (V-sync)
            */
            int refreshRate = 0;
        };
        /**
        * @brief Name of the physical monitor
        */
        std::string name;
        /**
        * @brief The current resolution
        */
        Resolution resolution;
        /**
        * @brief The current bith depth
        * @details
        *     - .x = RED
        *     - .y = GREEN
        *     - .z = BLUE
        */
        BitDepth bitDepth;
        /**
        * @brief The current refresh rate (V-sync)
        */
        int refreshRate = 0;
        /**
        * @brief The relative position to the primary monitor, in pixels
        */
        Vec2<int> position;
        /**
        * @brief The physical size of the monitor in millimeters
        */
        Vec2<int> physicalSize;
        /**
        * @brief GLFW specific pointer
        */
        void* ptr = nullptr;
    };
};
#endif
