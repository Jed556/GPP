cmake_minimum_required(VERSION 3.0.0)
project(GPP VERSION 1.4.4)

include(CTest)
enable_testing()

file(GLOB_RECURSE SOURCE CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")

list(REMOVE_ITEM SOURCE ${REMOVE_CMAKE})

add_executable(GPP ${SOURCE})

#target_link_libraries(GPP "${CMAKE_SOURCE_DIR}/src/engine/audio/winmm.lib")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)