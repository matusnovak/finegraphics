/**
 * @defgroup graphics graphics - OpenGL drawing and window handling
 * @brief Basic graphical functionality via OpenGL
 * @details This module contains the basic API wrappers around OpenGL
 * (such as textures, framebuffers, renderbuffers), Window management and user
 * input handling in easy to follow wrapper class using GLFW as the backend.
 * This module also contains basic drawing API using nanovg library, for drawing
 * bitmap fonts, true type fonts, shapes, and textures.
 * Uses the following third party libraries: 
 * [GLFW](http://www.glfw.org/),
 * [FreeType](https://www.freetype.org/),
 * [libpng](http://www.libpng.org/pub/png/libpng.html),
 * [libz](http://www.zlib.net/),
 * and [nanovg](https://github.com/memononen/nanovg)
 */

#ifndef FFW_GRAPHICS_MODULE
#define FFW_GRAPHICS_MODULE
#include "graphics/glbuffer.h"
#include "graphics/glcanvas.h"
#include "graphics/glframebuffer.h"
#include "graphics/glrenderbuffer.h"
#include "graphics/glrenderbuffer2d.h"
#include "graphics/glrenderbuffer2dms.h"
#include "graphics/glshader.h"
#include "graphics/glprogram.h"
#include "graphics/gltexture.h"
#include "graphics/gltexture1d.h"
#include "graphics/gltexture1darray.h"
#include "graphics/gltexture2d.h"
#include "graphics/gltexture2darray.h"
#include "graphics/gltexture2darrayms.h"
#include "graphics/gltexture2dms.h"
#include "graphics/gltexture3d.h"
#include "graphics/gltexturecubemap.h"
#include "graphics/glrenderwindow.h"
#include "graphics/glvertexarray.h"
#include "graphics/mvp.h"
#include "graphics/mat3.h"
#include "graphics/mat4.h"
#include "graphics/math.h"
#include "graphics/vec2.h"
#include "graphics/vec3.h"
#include "graphics/vec4.h"
#include "graphics/quaternion.h"
#include "graphics/monitors.h"
#include "graphics/constants.h"
#include "graphics/exceptions.h"
#endif