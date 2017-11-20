cmake_minimum_required(VERSION 2.8)

SET(CMAKE_CURRENT_SOURCE_DIR /media/jakub/2AC2CCF9C2CCCA71/Programowanie/Projects/Server_Project/src)

project(Server_Project C)
add_executable(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/main.c")

set( VERSION_MAJOR 0 )
set( VERSION_MINOR 1 )
set( VERSION_PATCH 1 )

##############################################
############### SOURCE SETTINGS ##############
##############################################

