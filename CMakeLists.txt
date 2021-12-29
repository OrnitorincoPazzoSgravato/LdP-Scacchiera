cmake_minimum_required(VERSION 3.8)

set(${PROJECT_NAME} chessboard)
set(${INCLUDE_DIRS} include)
set(${SRC_FILES} src/Chessboard.cpp src/Piece.cpp src/Alfiere.cpp src/Cavallo.cpp src/Pedone.cpp src/Re.cpp src/Regina.cpp src/Torre.cpp src/Utilities.cpp)

project(${PROJECT_NAME})

include_directories(${INCLUDE_DIRS})

add_library(Chessgame ${SRC_FILES})

add_executable(scacchiera scacchiera.cpp)

target_link_libraries(scacchiera Chessgame)