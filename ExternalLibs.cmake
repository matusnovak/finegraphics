cmake_minimum_required(VERSION 3.1)
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

# Add third party libraries
ExternalProject_Add(GLFW3
  DOWNLOAD_COMMAND ""
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/glfw
  CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF -DGLFW_INSTALL=OFF -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF
  BUILD_COMMAND cmake --build . --config MinSizeRel
  INSTALL_COMMAND ""
  TEST_COMMAND ""
)

if(MSVC)
  set(GLFW3_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/glfw/include)
  set(GLFW3_LIBRARY ${CMAKE_BINARY_DIR}/GLFW3-prefix/src/GLFW3-build/src/MinSizeRel/glfw3.lib)
else(MSVC)
  set(GLFW3_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/glfw/include)
  set(GLFW3_LIBRARY ${CMAKE_BINARY_DIR}/GLFW3-prefix/src/GLFW3-build/src/libglfw3.a)
endif(MSVC)

ExternalProject_Add(ZLIB
  DOWNLOAD_COMMAND ""
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/zlib
  CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF -DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=true
  BUILD_COMMAND cmake --build . --target zlibstatic --config MinSizeRel
  INSTALL_COMMAND ""
  TEST_COMMAND ""
)

if(MSVC)
  set(ZLIB_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/zlib)
  set(ZLIB_LIBRARY ${CMAKE_BINARY_DIR}/ZLIB-prefix/src/ZLIB-build/MinSizeRel/zlibstatic.lib)
elseif(MINGW)
  set(ZLIB_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/zlib)
  set(ZLIB_LIBRARY ${CMAKE_BINARY_DIR}/ZLIB-prefix/src/ZLIB-build/libzlibstatic.a)
else()
  set(ZLIB_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/zlib)
  set(ZLIB_LIBRARY ${CMAKE_BINARY_DIR}/ZLIB-prefix/src/ZLIB-build/libz.a)
endif()

if(MSVC)
  ExternalProject_Add(LIBPNG
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/libpng
    CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF -DPNG_FRAMEWORK=OFF -DPNG_SHARED=OFF -DPNG_STATIC=ON -DPNG_TESTS=OFF -DZLIB_INCLUDE_DIR=${CMAKE_SOURCE_DIR}/libs/zlib -DCMAKE_INCLUDE_PATH=${CMAKE_BINARY_DIR}/ZLIB-prefix/src/ZLIB-build -DZLIB_LIBRARY=${CMAKE_BINARY_DIR}/ZLIB-prefix/src/ZLIB-build/MinSizeRel/zlibstatic
    BUILD_COMMAND cmake -E copy ${CMAKE_BINARY_DIR}/ZLIB-prefix/src/ZLIB-build/zconf.h ${CMAKE_BINARY_DIR}/LIBPNG-prefix/src/LIBPNG-build && cmake --build . --config MinSizeRel
    INSTALL_COMMAND ""
    TEST_COMMAND ""
  )
  add_dependencies(LIBPNG ZLIB)
elseif(MINGW)
  ExternalProject_Add(LIBPNG
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/libpng
    CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF -DPNG_FRAMEWORK=OFF -DPNG_SHARED=OFF -DPNG_STATIC=ON -DPNG_TESTS=OFF -DZLIB_INCLUDE_DIR=${CMAKE_SOURCE_DIR}/libs/zlib -DZLIB_LIBRARY=${CMAKE_BINARY_DIR}/ZLIB-prefix/src/ZLIB-build/libzlibstatic.a
    BUILD_COMMAND cmake -E copy ${CMAKE_BINARY_DIR}/ZLIB-prefix/src/ZLIB-build/zconf.h ${CMAKE_BINARY_DIR}/LIBPNG-prefix/src/LIBPNG-build && cmake --build . --config MinSizeRel
    INSTALL_COMMAND ""
    TEST_COMMAND ""
  )
  add_dependencies(LIBPNG ZLIB)
else()
  ExternalProject_Add(LIBPNG
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/libpng
    CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF -DPNG_FRAMEWORK=OFF -DPNG_SHARED=OFF -DPNG_STATIC=ON -DPNG_TESTS=OFF -DZLIB_INCLUDE_DIR=${CMAKE_SOURCE_DIR}/libs/zlib -DZLIB_LIBRARY=${CMAKE_BINARY_DIR}/ZLIB-prefix/src/ZLIB-build/libz.a -DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=true
    BUILD_COMMAND cmake -E copy ${CMAKE_BINARY_DIR}/ZLIB-prefix/src/ZLIB-build/zconf.h ${CMAKE_BINARY_DIR}/LIBPNG-prefix/src/LIBPNG-build && cmake --build . --config MinSizeRel
    INSTALL_COMMAND ""
    TEST_COMMAND ""
  )
  add_dependencies(LIBPNG ZLIB)
endif()

ExternalProject_Add(FREETYPE2
  DOWNLOAD_COMMAND ""
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/freetype2
  CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF -DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=true
  BUILD_COMMAND cmake --build . --config MinSizeRel
  INSTALL_COMMAND ""
  TEST_COMMAND ""
)
add_dependencies(FREETYPE2 LIBPNG)

if(MSVC)
  set(FREETYPE2_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/freetype2/include)
  set(FREETYPE2_LIBRARY ${CMAKE_BINARY_DIR}/FREETYPE2-prefix/src/FREETYPE2-build/MinSizeRel/freetype.lib)
else(MSVC)
  set(FREETYPE2_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/freetype2/include)
  set(FREETYPE2_LIBRARY ${CMAKE_BINARY_DIR}/FREETYPE2-prefix/src/FREETYPE2-build/libfreetype.a)
endif(MSVC)

set(NANOVG_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/nanovg/src)
set(TINYOBJLOADER_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/tinyobjloader)
