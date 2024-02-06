cmake_minimum_required(VERSION 3.22)
project(game)


set(LIB_ROOT            ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(GLFW_ROOT           ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw)
set(GLFW_HDR            ${GLFW_ROOT}/include)
set(GLFW_WINDOWS_ROOT   ${GLFW_ROOT}/WIN64)
set(GLFW_WINDOWS_BIN    ${GLFW_WINDOWS_ROOT}/lib)
set(GLFW_OSX_BIN        ${GLFW_ROOT}/OSX/lib)

set(INCLUDE_DIR         ${CMAKE_CURRENT_SOURCE_DIR}/hdr)
set(INJN_SOURCE         ${PROJECT_SOURCE_DIR}/src)

add_executable(game ${INJN_SOURCE}/main.c ${INJN_SOURCE}/shader.c ${INJN_SOURCE}/object.c ${INJN_SOURCE}/texture.c)

# https://cmake.org/cmake/help/latest/guide/importing-exporting/index.html#importing-libraries
add_library(libglfw SHARED IMPORTED ${GLFW_HDR})
if(WIN32)
    set_property(TARGET libglfw PROPERTY IMPORTED_IMPLIB ${GLFW_WINDOWS_BIN}/glfw3dll.lib)
    set_property(TARGET libglfw PROPERTY IMPORTED_LOCATION ${GLFW_WINDOWS_BIN}/glfw3.dll)
elseif(APPLE)
    set_property(TARGET libglfw PROPERTY IMPORTED_LOCATION ${GLFW_OSX_BIN}/libglfw.3.dylib)
else()
# TODO
    # set_property(TARGET libglfw PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/glfw3dll.lib)
endif(WIN32)

add_library(libglad OBJECT ${LIB_ROOT}/glad/glad.c)

target_sources(game PUBLIC
    ${INJN_SOURCE}/utils/log.c
    ${INJN_SOURCE}/utils/fs.c
    ${INJN_SOURCE}/utils/resmgr.c
    PUBLIC
    FILE_SET HEADERS
    BASE_DIRS ${INCLUDE_DIR}
)

target_link_libraries(game PRIVATE libglfw)
target_link_libraries(game PRIVATE libglad)