cmake_minimum_required(VERSION 3.16)
project(Chess)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)
set(CMAKE_AUTOUIC ON)

add_executable(Chess
	main.cpp 
	mainwindow.h 
)

target_link_libraries(Chess PRIVATE Qt6::Widgets)