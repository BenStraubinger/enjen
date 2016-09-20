cmake_minimum_required(VERSION 3.5)
project(enjen)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")


include_directories("${PROJECT_SOURCE_DIR}/src")




################################################################################
#
# system libraries:
#
################################################################################

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})




################################################################################
#
# external source libraries:
#
################################################################################

include_directories("${PROJECT_SOURCE_DIR}/ext/glm")

include_directories("${PROJECT_SOURCE_DIR}/ext/jsoncpp")




################################################################################
#
# build and link:
#
################################################################################

add_executable( enjen

        src/main.cpp

        src/Enjen.cpp src/Enjen.h

        src/core/Runtime.cpp src/core/Runtime.h
        src/core/Renderer.cpp src/core/Renderer.h


        #
        # external source libraries
        #

        ext/jsoncpp/jsoncpp.cpp

)


target_link_libraries( enjen
        ${SDL2_LIBRARY}
        ${OPENGL_gl_LIBRARY}
        ${OPENGL_glu_LIBRARY}
        ${GLEW_LIBRARY}
)
