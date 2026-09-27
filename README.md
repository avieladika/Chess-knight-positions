# Knight’s Tour in C

![C](https://img.shields.io/badge/C-A8B9CC?style=for-the-badge&logo=c&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white)

**Links:** [Repository](https://github.com/avieladika/Chess-knight-positions) · [Types and declarations](files.h) · [Entry point](main.c)

An academic data-structures project that searches for a knight path visiting every square of a 5×5 board. It models legal moves, builds a path tree, and represents a discovered tour as a linked list.

## The Challenge

A valid knight move is easy to enumerate, but finding a complete tour requires exploring alternative paths without revisiting squares. In C, the search also requires explicit handling of dynamically allocated structures.

## The Solution

The program enumerates legal moves, constructs a tree of possible paths from the supplied position, and searches that tree for a route covering the board.

## What It Includes

- A fixed 5×5 board with coordinates `A1` through `E5`.
- Arrays of legal knight moves.
- A tree representing candidate paths.
- Linked-list representation of the resulting tour.
- Explicit allocation and cleanup functions.
- Console input and board output.

## System Model

`validKnightMoves` builds legal-move data, `findAllPossibleKnightPaths` constructs the search tree, and `findKnightPathCoveringAllBoard` searches for a tour. Shared types are declared in `files.h`.

## Core Technical Flow

Starting square → validate input → enumerate legal moves → construct path tree → search for full coverage → display result.

```mermaid
flowchart LR
    S[Starting square] --> V[Input validation]
    V --> M[Legal moves]
    M --> T[Path tree]
    T --> F[Covering-path search]
    F --> D[Display tour or no result]
```

## Why This Design

The project makes arrays, trees, linked lists, and pointer-based memory management concrete in one problem. Its exhaustive strategy also demonstrates the time and memory costs of materializing a search space.

## Build and use

The repository includes a CMake configuration requiring CMake 3.27 and requesting C23:

```sh
cmake -S . -B build
cmake --build build
./build/project_to_upload
```

Enter a position such as `A1`, followed by Enter. Valid coordinates are `A`–`E` and `1`–`5`. The program displays a covering path when found, or reports that no tour exists.

## Limitations

The exhaustive path tree can consume significant time and memory. The source currently declares `void main()`, which strict standard-conforming compilers may reject; portability cleanup is still needed. This repository preserves the original algorithm rather than claiming an optimized solver.
