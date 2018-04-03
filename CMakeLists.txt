cmake_minimum_required(VERSION 3.0)

project(LUDIJAM
  VERSION 0.1.0
)

include(GNUInstallDirs)

find_package(gf REQUIRED)

set(LUDIJAM_DATA_DIR "${CMAKE_INSTALL_PREFIX}/share/games/ludijam")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/code/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h @ONLY)

if(NOT MSVC)
  add_definitions(-Wall -Wextra -g -O2 -std=c++14 -pedantic)
endif()

add_executable(ludijam
  code/main.cc
)

target_include_directories(ludijam
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/code
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(ludijam
  gf::gf0
)

install(
  TARGETS ludijam
  RUNTIME DESTINATION games
)

install(
  DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/data/ludijam"
  DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/games"
)
