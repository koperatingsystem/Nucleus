cmake_minimum_required(VERSION 3.0)

project(kOS.LKI.Headers)

add_library(kOS.LKI.Headers INTERFACE)

target_include_directories(kOS.LKI.Headers INTERFACE Includes)
