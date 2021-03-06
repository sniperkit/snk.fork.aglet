cmake_minimum_required(VERSION 3.3)

include("cmake/HunterGate.cmake")

HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.21.9.tar.gz"
    SHA1 "0056188988906abb63a06c6f1aaef01832c62b74"
)

project(aglet VERSION 1.2.2)

hunter_add_package(check_ci_tag)
find_package(check_ci_tag CONFIG REQUIRED)
check_ci_tag()

option(AGLET_BUILD_TESTS "Build tests" OFF)
option(AGLET_OPENGL_ES3 "Use OpenGL ES 3.0" OFF) # default 2.0

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(AGLET_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/lib")

if(IOS OR ANDROID)
  set(AGLET_IS_MOBILE TRUE)
else()
  set(AGLET_IS_MOBILE FALSE)
endif()

add_subdirectory(lib/aglet)

string(COMPARE EQUAL "$ENV{TRAVIS}" "true" travis_ci)
string(COMPARE EQUAL "$ENV{APPVEYOR}" "True" appveyor_ci)
if(travis_ci OR appveyor_ci)
  set(AGLET_CI TRUE)
else()
  set(AGLET_CI FALSE)
endif()

if(AGLET_BUILD_TESTS)

  hunter_add_package(gauze)
  find_package(gauze CONFIG REQUIRED)

  # We can run CI tests w/ Android Emulator
  if(${AGLET_CI} AND NOT ANDROID)
    # Do not run tests (just build)
  else()
    enable_testing()
  endif()
  add_subdirectory(test)
endif()
