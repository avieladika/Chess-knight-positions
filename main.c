#include "files.h"

void main() {


    bool validFlag = true; // Flag to check input validity
    int i = ZERO;
    char validateInput[FORTH_PLACE] = {ZERO}; // Buffer to store user input
    chessPos location; // Starting position
    pathTree movesTree; // Tree of possible knight moves
    chessPosList *allBoardList; // List to store the knight's tour

    // Read and validate user input
    while (validFlag) {
        scanf("%c", &validateInput[i]);
        if (i == 2 && validateInput[THIRD_PLACE] != '\n') {
            validFlag = false; // Invalid input if more than 2 characters entered
        }
        if (i == 2 && validateInput[THIRD_PLACE] == '\n')
            break; // Valid input if exactly 2 characters followed by newline
        i++;
    }
    location[FIRST_PLACE] = validateInput[FIRST_PLACE];
    location[SECOND_PLACE] = validateInput[SECOND_PLACE];

    // Check if the input is within the valid range
    if (location[FIRST_PLACE] < 'A' || location[FIRST_PLACE] > 'E' || location[SECOND_PLACE] < '1' || location[SECOND_PLACE] > '5' || validFlag == false) {
        printf("Invalid input\n");
    } else {
        movesTree = findAllPossibleKnightPaths(&location); // Build the path tree
        allBoardList = findKnightPathCoveringAllBoard(&movesTree); // Find the knight's tour
        if (allBoardList) {
            display(allBoardList); // Display the knight's tour
            freeList(allBoardList); // Free the list memory
        } else {
            printf("No knight's tour\n");
        }
    }
}
