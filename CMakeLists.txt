cmake_minimum_required(VERSION 3.3)
project(ganeshEngine)

if(MSVC)
    # Force to always compile with W4
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # Update if necessary
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${ganeshEngine_SOURCE_DIR}/cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")

# git 1.8.5.2
find_package(Git REQUIRED)
find_package(OpenGL REQUIRED)

function(get_lib_from_github _folder _url _tag)
    if(NOT EXISTS "${_folder}")
        execute_process(
                COMMAND ${GIT_EXECUTABLE} clone --branch ${_tag} ${_url} ${_folder}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE GIT_RES
                OUTPUT_STRIP_TRAILING_WHITESPACE
        )
    endif()
endfunction()

add_definitions(
    -DDEBUG_ASSERTION_ENABLED
    -DPROFILING_ENABLED
    -DLOGGING_ENABLED
    -DTW_STATIC
    -DTW_NO_LIB_PRAGMA
    -DTW_NO_DIRECT3D
    -DGLEW_STATIC
    -D_CRT_SECURE_NO_WARNINGS)

set(LIB_DIR "${PROJECT_SOURCE_DIR}/libs")

set(RAPIDJSON_URL "https://github.com/miloyip/rapidjson.git")
set(RAPIDJSON_TAG "v1.0.2")
set(RAPIDJSON_DIR "${LIB_DIR}/rapidjson")

set(GLFW_URL "https://github.com/glfw/glfw.git")
set(GLFW_TAG "3.2")
set(GLFW_DIR "${LIB_DIR}/glfw")

set(GLEW_URL "https://github.com/nigels-com/glew.git")
set(GLEW_TAG "glew-1.12.0")
set(GLEW_DIR "${LIB_DIR}/glew")

set(GLM_URL "https://github.com/g-truc/glm.git")
set(GLM_TAG "0.9.7")
set(GLM_DIR "${LIB_DIR}/glm")


if(NOT EXISTS "${LIB_DIR}")
    file(MAKE_DIRECTORY "${LIB_DIR}")
endif()

set(BASH "bash")
if(${CMAKE_SYSTEM} MATCHES "Windows")
    if(${CMAKE_MAKE_PROGRAM} MATCHES "mingw")
        set(BASH "C:/MinGW/msys/1.0/bin/bash.exe")
    elseif(${CMAKE_MAKE_PROGRAM} MATCHES "cygwin")
        set(BASH "C:/MinGW/msys/1.0/bin/bash.exe")
    endif()
endif()

get_lib_from_github(${RAPIDJSON_DIR} ${RAPIDJSON_URL} ${RAPIDJSON_TAG})
get_lib_from_github(${GLFW_DIR} ${GLFW_URL} ${GLFW_TAG})
get_lib_from_github(${GLM_DIR} ${GLM_URL} ${GLM_TAG})
get_lib_from_github(${GLEW_DIR} ${GLEW_URL} ${GLEW_TAG})

if(NOT EXISTS "${GLEW_DIR}/src/glew.c")
    set(GEN_CMD "C:/MinGW/msys/1.0/bin/bash.exe")
    message(WARNING "generate glew.c")
    message(WARNING "${GEN_CMD} -l -c 'cd ${GLEW_DIR}/auto && make'")

    execute_process(
            COMMAND ${GEN_CMD} -l -c "cd ${GLEW_DIR}/auto && make"
            WORKING_DIRECTORY ${GLEW_DIR}
            OUTPUT_FILE ${LIB_DIR}/log.txt
            RESULT_VARIABLE MAKE_GLEW_RES
            OUTPUT_VARIABLE MAKE_GLEW_OUTPUT
    )

    # Cause compile failure on my platform if not removed before src generation
    file(REMOVE ${GLEW_DIR}/auto/extensions/gl/GL_NV_draw_vulkan_image)

    execute_process(
            COMMAND ${GEN_CMD} -l -c "cd ${GLEW_DIR} && make install"
            WORKING_DIRECTORY ${GLEW_DIR}
            OUTPUT_FILE ${LIB_DIR}/log.txt
            RESULT_VARIABLE MAKE_GLEW_RES
            OUTPUT_VARIABLE MAKE_GLEW_OUTPUT
    )

    message(WARNING "MAKE_GLEW_RES : ${MAKE_GLEW_RES}")
    message(WARNING "MAKE_GLEW_OUTPUT : ${MAKE_GLEW_OUTPUT}")
endif(NOT EXISTS "${GLEW_DIR}/src/glew.c")


add_subdirectory(libs)

add_subdirectory(ganeshEngineCore)
add_subdirectory(ganeshEngineDemo)
#add_subdirectory(ganeshEngineTest)
