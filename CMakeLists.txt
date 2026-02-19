cmake_minimum_required(VERSION 3.16)

project(OpenGLProject LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(APP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Primitive_Drawing - OpenGl 3.3+ std/Primitive_Drawing")

set(APP_SOURCES
    "${APP_DIR}/AABoundingBox.cpp"
    "${APP_DIR}/AirCraft.cpp"
    "${APP_DIR}/ApplicationManager.cpp"
    "${APP_DIR}/camera.cpp"
    "${APP_DIR}/Colider.cpp"
    "${APP_DIR}/CollidableModel.cpp"
    "${APP_DIR}/CollisionManager.cpp"
    "${APP_DIR}/GameObject.cpp"
    "${APP_DIR}/main.cpp"
    "${APP_DIR}/ModelData.cpp"
    "${APP_DIR}/Obj-Loader/list.cpp"
    "${APP_DIR}/Obj-Loader/objLoaderEX.cpp"
    "${APP_DIR}/Obj-Loader/objTester.cpp"
    "${APP_DIR}/Obj-Loader/obj_parser.cpp"
    "${APP_DIR}/Obj-Loader/string_extra.cpp"
    "${APP_DIR}/objloader.cpp"
    "${APP_DIR}/Renderer.cpp"
    "${APP_DIR}/shader.cpp"
    "${APP_DIR}/ShapeGenerator.cpp"
    "${APP_DIR}/stb_image.c"
    "${APP_DIR}/Texture.cpp"
    "${APP_DIR}/tcamera.cpp"
    "${APP_DIR}/Time.cpp"
    "${APP_DIR}/Transform.cpp"
    "${APP_DIR}/Utility.cpp"
    "${APP_DIR}/World.cpp"
)

foreach(src IN LISTS APP_SOURCES)
    if(NOT EXISTS "${src}")
        message(FATAL_ERROR "Missing source file referenced by build: ${src}")
    endif()
endforeach()

add_executable(Primitive_Drawing ${APP_SOURCES})

target_include_directories(Primitive_Drawing PRIVATE
    "${APP_DIR}"
    "${APP_DIR}/Obj-Loader"
)

if(MSVC)
    target_compile_definitions(Primitive_Drawing PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

if(APPLE)
    find_package(OpenGL REQUIRED)
    target_link_libraries(Primitive_Drawing PRIVATE OpenGL::GL)
else()
    find_package(OpenGL REQUIRED COMPONENTS OpenGL)
    target_link_libraries(Primitive_Drawing PRIVATE OpenGL::OpenGL)
endif()

find_package(PkgConfig QUIET)

find_package(glfw3 CONFIG QUIET)
if(TARGET glfw)
    target_link_libraries(Primitive_Drawing PRIVATE glfw)
elseif(TARGET glfw::glfw)
    target_link_libraries(Primitive_Drawing PRIVATE glfw::glfw)
elseif(PkgConfig_FOUND)
    pkg_check_modules(GLFW3 QUIET IMPORTED_TARGET glfw3)
    if(TARGET PkgConfig::GLFW3)
        target_link_libraries(Primitive_Drawing PRIVATE PkgConfig::GLFW3)
    else()
        message(FATAL_ERROR "GLFW3 was not found. Install glfw3 development package or provide glfw3 CMake config.")
    endif()
else()
    message(FATAL_ERROR "GLFW3 was not found. Install glfw3 development package or provide glfw3 CMake config.")
endif()

find_package(GLEW CONFIG QUIET)
if(TARGET GLEW::GLEW)
    target_link_libraries(Primitive_Drawing PRIVATE GLEW::GLEW)
elseif(TARGET GLEW::glew)
    target_link_libraries(Primitive_Drawing PRIVATE GLEW::glew)
elseif(PkgConfig_FOUND)
    pkg_check_modules(GLEW QUIET IMPORTED_TARGET glew)
    if(TARGET PkgConfig::GLEW)
        target_link_libraries(Primitive_Drawing PRIVATE PkgConfig::GLEW)
    else()
        message(FATAL_ERROR "GLEW was not found. Install glew development package or provide GLEW CMake config.")
    endif()
else()
    message(FATAL_ERROR "GLEW was not found. Install glew development package or provide GLEW CMake config.")
endif()

set(RUNTIME_FILE_ASSETS
    "SimpleVertexShader.vertexshader"
    "SimpleFragmentShader.fragmentshader"
)

set(RUNTIME_DIR_ASSETS
    "tex"
    "models"
    "Obj-Loader"
    "sound"
)

foreach(asset IN LISTS RUNTIME_FILE_ASSETS)
    add_custom_command(TARGET Primitive_Drawing POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${APP_DIR}/${asset}"
            "$<TARGET_FILE_DIR:Primitive_Drawing>/${asset}"
        VERBATIM
    )
endforeach()

foreach(asset IN LISTS RUNTIME_DIR_ASSETS)
    add_custom_command(TARGET Primitive_Drawing POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${APP_DIR}/${asset}"
            "$<TARGET_FILE_DIR:Primitive_Drawing>/${asset}"
        VERBATIM
    )
endforeach()
