cmake_minimum_required(VERSION 3.12)
project(fetch)

set(SOURCES
	src/main.cpp
	src/fetch.cpp
	src/fetch.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
