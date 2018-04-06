cmake_minimum_required(VERSION 3.0)

project(LUDIJAM
  VERSION 0.1.0
)

include(GNUInstallDirs)

find_package(gf REQUIRED)

set(NOINC_DATA_DIR "${CMAKE_INSTALL_PREFIX}/share/games/no-inc")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/code/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h @ONLY)

if(NOT MSVC)
  add_definitions(-Wall -Wextra -g -O2 -std=c++14 -pedantic)
endif()

add_executable(no-inc
  code/main.cc
  code/local/Globe.cc
  code/local/Singletons.cc
  code/local/WorldMap.cc
)

target_include_directories(no-inc
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/code
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(no-inc
  gf::gf0
)

install(
  TARGETS no-inc
  RUNTIME DESTINATION games
)

install(
  DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/data/no-inc"
  DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/games"
)
