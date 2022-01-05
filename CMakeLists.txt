cmake_minimum_required(VERSION 3.8)

set(PROJECT_NAME chessboard)
set(INCLUDE_DIRS include)
set(SRC_FILES lib/Chessboard.cpp lib/Piece.cpp lib/Alfiere.cpp lib/Cavallo.cpp lib/Pedone.cpp lib/Re.cpp lib/Regina.cpp lib/Torre.cpp lib/Utilities.cpp)

project(${PROJECT_NAME} VERSION 1.0)

include_directories(${INCLUDE_DIRS})

add_library(Chessgame ${SRC_FILES})

add_executable(scacchiera src/scacchiera.cpp)

target_link_libraries(scacchiera Chessgame)