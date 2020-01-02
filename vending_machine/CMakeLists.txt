cmake_minimum_required(VERSION 3.1)
project(vending_machine)

add_executable(${PROJECT_NAME}_oop src/vending_machine_oop.cpp)
target_compile_options(${PROJECT_NAME}_oop PUBLIC -std=c++11)

add_executable(${PROJECT_NAME}_fp src/vending_machine_fp.cpp)
target_compile_options(${PROJECT_NAME}_fp PUBLIC -std=c++11)

#
enable_testing()

function(do_test target category arg result)
  add_test(NAME ${target}::${category}
    COMMAND ${PROJECT_NAME}_${category} ${arg})
  set_tests_properties(${target}::${category}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endfunction()

do_test(NoInvest oop  "" "money shortage")
do_test(Shortage oop 119999 "money shortage")
do_test(OnPrice oop 120000 "MacBook Air 13-inch sold!\npayback: 0")
do_test(PayBack oop 150000 "MacBook Air 13-inch sold!\npayback: 3000")
do_test(Negative oop -1 "money shortage")

do_test(NoInvest fp  "" "money shortage\npayback: 0")
do_test(Shortage fp 119999 "money shortage\npayback: 119999")
do_test(OnPrice fp 120000 "MacBook Air 13-inch sold!\npayback: 0")
do_test(PayBack fp 150000 "MacBook Air 13-inch sold!\npayback: 3000")
do_test(Negative fp -1 "money shortage\npayback: 0")
