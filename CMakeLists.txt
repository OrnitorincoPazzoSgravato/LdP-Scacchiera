cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME Chess)
project(${PROJECT_NAME} VERSION 1.0)

set(SRC_FILES lib/Game.cpp lib/Replay.cpp lib/chessgame/Chessboard.cpp lib/chessgame/Bot.cpp lib/chessgame/Human.cpp lib/chessgame/Piece.cpp lib/chessgame/Alfiere.cpp lib/chessgame/Cavallo.cpp lib/chessgame/Pedone.cpp lib/chessgame/Re.cpp lib/chessgame/Regina.cpp lib/chessgame/Torre.cpp lib/chessgame/Utilities.cpp )
set(HEADER_FILES include/chessgame/Exception.h include/Game.h include/Replay.h include/chessgame/Player.h include/chessgame/Bot.h include/chessgame/Human.h include/chessgame/Chessboard.h include/chessgame/Piece.h include/chessgame/Alfiere.h include/chessgame/Cavallo.h include/chessgame/Pedone.h include/chessgame/Re.h include/chessgame/Regina.h include/chessgame/Torre.h include/chessgame/Utilities.h )
SET(GCC_COVERAGE_COMPILE_FLAGS "-g -O2")

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

include_directories(include lib)

add_library(
    Chessgame
    ${SRC_FILES} 
    ${HEADER_FILES}
)

add_executable(scacchiera src/scacchiera.cpp  )
add_executable(replay src/replay.cpp )

target_link_libraries(scacchiera Chessgame)
target_link_libraries(replay Chessgame)
