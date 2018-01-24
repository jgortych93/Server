cmake_minimum_required(VERSION 2.8)

SET(CMAKE_CURRENT_SOURCE_DIR /media/jakub/2AC2CCF9C2CCCA71/Programowanie/Projects/Server_Project/Client/src)
SET(CMAKE_BINARY_DIR ../../build-Client-Desktop_Qt_5_9_0_GCC_64bit-Default)

project(Client)

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
    src/main.cpp
    src/Client.hpp
    src/Client.cpp
)

##############################################
################# COMPILATION ################
##############################################

# Add target
add_library( ${PROJECT_NAME} SHARED ${SOURCES})

