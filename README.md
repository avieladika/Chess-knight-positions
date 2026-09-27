# Knight's Tour in C

An academic data-structures project that explores knight moves on a 5×5 board and searches for a path visiting every square.

## Highlights

- Arrays of legal knight moves.
- A tree of possible paths from a starting position.
- Linked lists to represent the resulting tour.
- Explicit dynamic-memory management.

## Build and use

The repository includes a CMake configuration requiring CMake 3.27 and requesting C23:

```sh
cmake -S . -B build
cmake --build build
./build/project_to_upload
```

Enter a position such as `A1`, followed by Enter. Valid coordinates are `A`–`E` and `1`–`5`. The program displays a covering path when found, or reports that no tour exists.

## Implementation

`validKnightMoves` enumerates legal moves; `findAllPossibleKnightPaths` constructs the search tree; `findKnightPathCoveringAllBoard` searches for a complete tour. Types and declarations are in `files.h`; implementations are split across `exe1.c` through `exe4.c`.

## Limitations

The exhaustive path tree can consume significant time and memory. The source currently declares `void main()`, which strict standard-conforming compilers may reject; portability cleanup is still needed. This repository preserves the original algorithm rather than claiming an optimized solver.
