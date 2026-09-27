# Knight’s Tour in C

![C](https://img.shields.io/badge/C-A8B9CC?style=for-the-badge&logo=c&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white)

**Links:** [Repository](https://github.com/avieladika/Chess-knight-positions) · [Types and declarations](files.h) · [Entry point](main.c)

An academic data-structures project that searches for a knight path visiting every square of a 5×5 board. It models legal moves, builds a path tree, and represents a discovered tour as a linked list.

## The Challenge

A valid knight move is easy to enumerate, but finding a complete tour requires exploring alternative paths without revisiting squares. In C, the search also requires explicit handling of dynamically allocated structures.

## The Solution

The program enumerates legal moves, constructs a tree of possible paths from the supplied position, and searches that tree for a route covering the board.

## Highlights

### Legal-move enumeration and path-tree construction

The program treats board positions as vertices connected by legal knight moves. It precomputes available moves, then recursively constructs a tree of candidate paths from the starting square. Before extending a path, it checks whether the destination already appears in that path. This prevents revisiting squares within a candidate tour.

See [move generation](exe1.c) and [path-tree construction](exe3.c).

### Depth-first search and backtracking

The covering-path search traverses the constructed tree recursively. A visited matrix tracks board coverage, and each search branch extends a linked-list representation of the current route. A full board returns a tour; unsuccessful branches undo their visited mark and release temporary lists. This is an exhaustive **depth-first/backtracking** strategy, without heuristics such as Warnsdorff's rule.

The full candidate tree is materialized before the covering-path search, so time and memory can grow rapidly with the number of possible paths. This implementation is intended for the fixed 5×5 board.

See [recursive covering-path search](exe4.c).

### Data structures and explicit memory handling

Move arrays provide adjacency information, tree nodes represent alternatives, and singly linked lists hold paths. `malloc`, `calloc`, and `free` manage these structures explicitly. The implementation copies lists during recursive search, making allocation cost and ownership visible parts of the algorithm. Cleanup helpers exist, but the program is not claimed to be leak-free: the current entry point does not release the full path tree after use.

### Technologies and dependencies

| Component | How it is used |
| --- | --- |
| **C and its standard library** | Pointers, structures, recursion, heap allocation, and console input/output. |
| **CMake** | Builds the source modules into one executable; the configuration requests C23. |
| **Project-defined data structures** | `chessPosArray`, `pathTree`, and `chessPosList` implement move collections, search branches, and paths. |

There are **no third-party runtime libraries or chess engines**. The move generation, tree construction, search, and display logic are implemented in the C source files.


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
