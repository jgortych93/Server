cmake_minimum_required(VERSION 2.8)

SET(CMAKE_CURRENT_SOURCE_DIR /media/jakub/2AC2CCF9C2CCCA71/Programowanie/Projects/Server_Project/src)

project(Server_Project C)

set( VERSION_MAJOR 0 )
set( VERSION_MINOR 1 )
set( VERSION_PATCH 1 )

##############################################
############### SOURCE SETTINGS ##############
##############################################


INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set ( SOURCES
    src/main.c
    src/server.h
    src/server.c
)

##############################################
################# COMPILATION ################
##############################################

# Add target
add_library( ${PROJECT_NAME} SHARED ${SOURCES})

