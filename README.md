Knight's Tour - C Project

This project implements knight movement logic on a 5x5 chessboard. It calculates all valid knight paths from a given position and attempts to find a complete path that covers the entire board.

Features

- Builds a move tree (pathTree) from any starting position
- Finds knight paths that cover the entire board
- Efficient position and board representation
- Includes memory cleanup functions

Structures

- chessPosList: linked list of positions
- pathTree: tree structure of knight moves
- chessPosArray: array of possible knight moves

Key Functions

- findAllPossibleKnightPaths
- findKnightPathCoveringAllBoard
- validKnightMoves

Board

- 5x5 board with columns A–E and rows 1–5
- Positions are represented as two-character arrays

Usage

Include the headers, call the knight path functions with a starting position, and display the result using display or print functions.
