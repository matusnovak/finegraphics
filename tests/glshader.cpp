#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <ffw/graphics/glshader.h>
#include "dummywindow.h"
#include "traits.h"

#define STRINGIFY(x) #x

TEST_CASE("Test functionality", "ffw::GLShader") {
    DUMMY_APP;

    SECTION("default constructor") {
        ffw::GLShader shader;
        REQUIRE(shader.isCreated() == false);
        REQUIRE(shader.getHandle() == 0);
    }

    SECTION("basic functionality vertex shader") {
        static const std::string code = "#version 330 core\n" STRINGIFY(
            layout(location = 0) in vec3 aPos;

            out vec4 vertexColor;

            void main()
            {
                gl_Position = vec4(aPos, 1.0);
                vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
            }
        );

        ffw::GLShader shader = ffw::GLShader(GL_VERTEX_SHADER, code);
        REQUIRE(shader.isCreated() == true);
        REQUIRE(shader.getHandle() != 0);
        REQUIRE(shader.getType() == GL_VERTEX_SHADER);
    }

    SECTION("basic functionality vertex shader with error") {
        static const std::string code = "#version 330 core\n" STRINGIFY(
            layout(location = 0) in veasadasd aPos;

            out vec4 vertexColor;

            void main()
            {
                gl_Position = vec4(aPos, 1.0);
                vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
            }
        );

        REQUIRE_THROWS_AS(ffw::GLShader(GL_VERTEX_SHADER, code), ffw::GLException);
    }

    SECTION("swap shaders") {
        static const std::string code = "#version 330 core\n" STRINGIFY(
            layout(location = 0) in vec3 aPos;

            out vec4 vertexColor;

            void main()
            {
                gl_Position = vec4(aPos, 1.0);
                vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
            }
        );

        ffw::GLShader shaderA = ffw::GLShader(GL_VERTEX_SHADER, code);
        ffw::GLShader shaderB;
        REQUIRE(shaderA.isCreated() == true);
        REQUIRE(shaderA.getHandle() != 0);
        REQUIRE(shaderA.getType() == GL_VERTEX_SHADER);

        std::swap(shaderA, shaderB);
        REQUIRE(shaderA.isCreated() == false);
        REQUIRE(shaderA.getHandle() == 0);

        REQUIRE(shaderB.isCreated() == true);
        REQUIRE(shaderB.getHandle() != 0);
        REQUIRE(shaderB.getType() == GL_VERTEX_SHADER);
    }

    SECTION_TEST_MOVEABLE(ffw::GLShader);
    SECTION_TEST_NOT_COPYABLE(ffw::GLShader);
}
