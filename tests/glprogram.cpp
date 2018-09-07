#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <ffw/graphics/glshader.h>
#include <ffw/graphics/glprogram.h>
#include "dummywindow.h"
#include "traits.h"

#define STRINGIFY(x) #x

TEST_CASE("Test functionality", "ffw::GLProgram") {
    DUMMY_APP;

    SECTION("default constructor") {
        ffw::GLProgram shader;
        REQUIRE(shader.isCreated() == false);
        REQUIRE(shader.getHandle() == 0);
    }

    SECTION("basic functionality") {
        static const std::string vertCode = "#version 330 core\n" STRINGIFY(
            layout(location = 1) in vec3 aPos;
            uniform vec4 aColor;
            out vec4 vertexColor;

            void main() {
                gl_Position = vec4(aPos, 1.0);
                vertexColor = aColor;
            }
        );

        static const std::string fragCode = "#version 330 core\n" STRINGIFY(
            out vec4 FragColor;
            in vec4 vertexColor;

            void main() {
                FragColor = vertexColor;
            }
        );

        ffw::GLShader shaderVert = ffw::GLShader(GL_VERTEX_SHADER, vertCode);
        ffw::GLShader shaderFrag = ffw::GLShader(GL_FRAGMENT_SHADER, fragCode);
        ffw::GLProgram program = ffw::GLProgram({
            &shaderVert,
            &shaderFrag
        });

        REQUIRE(program.isCreated() == true);
        REQUIRE(program.getHandle() != 0);

        REQUIRE(program.getAttributeLocation("aPos") == 1);
        REQUIRE(program.getUniformLocation("aColor") == 0);
        REQUIRE(program.getUniformLocation("whatever") == -1);
    }

    SECTION("swap shaders") {
        static const std::string vertCode = "#version 330 core\n" STRINGIFY(
            layout(location = 0) in vec3 aPos;
            out vec4 vertexColor;

            void main() {
                gl_Position = vec4(aPos, 1.0);
                vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
            }
        );

        static const std::string fragCode = "#version 330 core\n" STRINGIFY(
            out vec4 FragColor;
            in vec4 vertexColor;

            void main() {
                FragColor = vertexColor;
            }
        );

        ffw::GLShader shaderVert = ffw::GLShader(GL_VERTEX_SHADER, vertCode);
        ffw::GLShader shaderFrag = ffw::GLShader(GL_FRAGMENT_SHADER, fragCode);
        ffw::GLProgram programA = ffw::GLProgram({
            &shaderVert,
            &shaderFrag
        });
        ffw::GLProgram programB;

        REQUIRE(programA.isCreated() == true);
        REQUIRE(programA.getHandle() != 0);

        std::swap(programA, programB);

        REQUIRE(programA.isCreated() == false);
        REQUIRE(programA.getHandle() == 0);

        REQUIRE(programB.isCreated() == true);
        REQUIRE(programB.getHandle() != 0);

        programB.destroy();
    }

    SECTION_TEST_MOVEABLE(ffw::GLProgram);
    SECTION_TEST_NOT_COPYABLE(ffw::GLProgram);
}
