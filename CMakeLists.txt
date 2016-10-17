cmake_minimum_required(VERSION 3.4)
project(enjen)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")


include(${PROJECT_SOURCE_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/ext/jsoncpp")


################################################################################
#
# system libraries:
#
################################################################################

#
# OpenGL: (https://www.opengl.org/wiki/Getting_Started
#
find_package(OpenGL)
if(NOT OPENGL_FOUND)
    message(ERROR "OpenGL not found!")
endif(NOT OPENGL_FOUND)
if(NOT OPENGL_GLU_FOUND)
    message(ERROR "OpenGL GLU not found!")
endif(NOT OPENGL_GLU_FOUND)

include_directories(${OPENGL_INCLUDE_DIR})


################################################################################
#
# build and link:
#
################################################################################

add_executable( enjen

        src/main.cpp

        src/Enjen.cpp src/Enjen.h

        src/core/Cfg.cpp src/core/Cfg.h
        src/core/Runtime.cpp src/core/Runtime.h
        src/core/Renderer.cpp src/core/Renderer.h
        src/core/Input.cpp src/core/Input.h
        src/core/Controller.cpp src/core/Controller.h


        #
        # external source libraries
        #

        ext/jsoncpp/jsoncpp.cpp

)


target_link_libraries( enjen 
    ${CONAN_LIBS}
    ${OPENGL_gl_LIBRARY}
    ${OPENGL_glu_LIBRARY}
)
