cmake_minimum_required(VERSION 3.1)
project(host2ip)

add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_options(${PROJECT_NAME} PUBLIC -std=c++17)
target_link_libraries(${PROJECT_NAME} PUBLIC pthread)

set(EXTERNAL_DIR ${PROJECT_BINARY_DIR}/external)
include_directories(SYSTEM ${EXTERNAL_DIR}/include)
include(ExternalProject)

ExternalProject_Add(
  asio
  PREFIX ${EXTERNAL_DIR}
  GIT_REPOSITORY https://github.com/chriskohlhoff/asio
  GIT_TAG asio-1-12-2
  BINARY_DIR ${EXTERNAL_DIR}/src/asio/asio
  CONFIGURE_COMMAND
    COMMAND ./autogen.sh
    COMMAND ./configure --prefix=${EXTERNAL_DIR} --without-boost
  BUILD_COMMAND make VERBOSE=1
  INSTALL_COMMAND make install
)
add_dependencies(${PROJECT_NAME} asio)
