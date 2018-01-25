cmake_minimum_required(VERSION 2.8)

SET(CMAKE_CURRENT_SOURCE_DIR /media/jakub/2AC2CCF9C2CCCA71/Programowanie/Projects/Server_Project/src)
SET(CMAKE_CURRENT_BINARY_DIR ../build-Server_Project-Desktop_Qt_5_9_0_GCC_64bit-Default)

project(Server_Project C CXX)

set( VERSION_MAJOR 0 )
set( VERSION_MINOR 1 )
set( VERSION_PATCH 1 )

##############################################
############### SOURCE SETTINGS ##############
##############################################


INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

##############################################
################# COMPILATION ################
##############################################

# Add target
#add_library( ${PROJECT_NAME} SHARED ${SOURCES})

add_executable( ${PROJECT_NAME} ${SOURCES})

# build it (link libraries)
target_link_libraries( ${PROJECT_NAME} pthread)

