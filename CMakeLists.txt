cmake_minimum_required(VERSION 2.8)
SET(CMAKE_C_FLAGS   "-g")

#Elasticity library
project(Blapp)
file(                  GLOB_RECURSE source_files src/*)
add_executable(        elastic      ${source_files})
target_link_libraries( elastic "-lm -lpthread")
