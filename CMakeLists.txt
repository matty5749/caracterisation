project(caracterisation)
cmake_minimum_required(VERSION 2.8)

IF(UNIX OR MINGW OR MSYS OR CYGWIN)
ADD_DEFINITIONS("-Wall -v -std=c++11 -O3")					#-O3 -std=c++11 
ENDIF(UNIX OR MINGW OR MSYS OR CYGWIN)

# link_directories ( ${Boost_LIBRARY_DIRS} )
# include_directories ( ${Boost_INCLUDE_DIRS} )

file(
    #GLOB_RECURSE
    GLOB
    sources     #La variable sources contiendra tout les .cpp
   src/*.cpp
)

add_executable(
    caracterisation
    ${sources}
#     ${Boost_LIBRARIES}
)
