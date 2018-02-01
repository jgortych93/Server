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
find_package(Qt5Core REQUIRED)
# Set used libraries
set(QT_LIBRARIES
    Qt5::Core)

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
target_link_libraries( ${PROJECT_NAME} ${QT_LIBRARIES} )

