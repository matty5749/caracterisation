project(caracterisation)
cmake_minimum_required(VERSION 2.8)

IF(UNIX OR MINGW OR MSYS OR CYGWIN)
ADD_DEFINITIONS("-Wall -Wextra -DNDEBUG -v -std=c++11 -Ofast")					#-O3 -std=c++11    /!\ -s supprime tout les messages de debug 
ENDIF(UNIX OR MINGW OR MSYS OR CYGWIN)

find_package(Qt4 COMPONENTS QtXml QtCore)
include_directories(${QT_INCLUDES})


# link_directories ( ${Boost_LIBRARY_DIRS} )
# include_directories ( ${Boost_INCLUDE_DIRS} )

# SET(CMAKE_BUILD_TYPE "Release")

file(
    #GLOB_RECURSE
    GLOB
    sources     #La variable sources contiendra tout les .cpp
   src/*.cpp
)

add_executable(
    caracterisation
    ${sources})
    
target_link_libraries(
		caracterisation
    ${QT_QTXML_LIBRARY}
    ${QT_QTCORE_LIBRARY}
)
#     ${Boost_LIBRARIES}