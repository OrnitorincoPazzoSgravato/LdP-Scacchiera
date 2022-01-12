cmake_minimum_required(VERSION 3.8)

set(PROJECT_NAME chessboard)

set(INCLUDE_DIRS include)
set(SRC_FILES lib/Game.cpp lib/chessgame/Chessboard.cpp lib/chessgame/Piece.cpp lib/chessgame/Alfiere.cpp lib/chessgame/Cavallo.cpp lib/chessgame/Pedone.cpp lib/chessgame/Re.cpp lib/chessgame/Regina.cpp lib/chessgame/Torre.cpp lib/chessgame/Utilities.cpp)
set(HEADER_FILES include/Game.h include/chessgame/Chessboard.h include/chessgame/Piece.h include/chessgame/Alfiere.h include/chessgame/Cavallo.h include/chessgame/Pedone.h include/chessgame/Re.h include/chessgame/Regina.h include/chessgame/Torre.h include/chessgame/Utilities.h)

project(${PROJECT_NAME} VERSION 1.0)

include_directories(${INCLUDE_DIRS})

add_library(Chessgame ${SRC_FILES} ${HEADER_FILES})

add_executable(scacchiera src/scacchiera.cpp)

target_link_libraries(scacchiera Chessgame)