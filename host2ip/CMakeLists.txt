cmake_minimum_required(VERSION 3.1)
project(host2ip)

add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_options(${PROJECT_NAME} PUBLIC -std=c++17)
target_link_libraries(${PROJECT_NAME} PUBLIC pthread)

#
include(ExternalProject)
set(EXTERNAL_DIR ${PROJECT_BINARY_DIR}/external)
include_directories(SYSTEM ${EXTERNAL_DIR}/include)

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

#
enable_testing()

function(do_test target arg result)
  add_test(NAME ${target} COMMAND ${PROJECT_NAME} ${arg})
  set_tests_properties(${target}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endfunction()

do_test(Usage "" "Usage: host2ip <hostname>")
do_test(LocalHost localhost "127.0.0.1")
do_test(Example example.com "93.184.216.34")
do_test(Exception ariaenai.a.b.c "exception:.*Host not found")
