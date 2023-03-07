cmake_minimum_required(VERSION 3.0.0)
project(GPP VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB_RECURSE SOURCE CONFIGURE_DEPENDS "*.h" "*.cpp")
file(GLOB_RECURSE REMOVE_CMAKE "build/*")
list(REMOVE_ITEM SOURCE ${REMOVE_CMAKE})

add_executable(GPP ${SOURCE})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)