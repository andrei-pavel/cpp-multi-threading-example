cmake_minimum_required(VERSION 3.2)

if (CMAKE_COMPILER_IS_GNUCC)
  option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)

  if (ENABLE_COVERAGE)
    add_compile_options(--coverage -O0)
  endif()
endif()

if (MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -ggdb3 -O0)
endif()

find_package(Threads)

add_executable(deadlock deadlock.cpp)
target_link_libraries(deadlock --coverage)
target_link_libraries (deadlock ${CMAKE_THREAD_LIBS_INIT})

enable_testing()

add_executable(multi-threading multi-threading.cpp)
target_link_libraries(multi-threading --coverage)
target_link_libraries (multi-threading ${CMAKE_THREAD_LIBS_INIT})
