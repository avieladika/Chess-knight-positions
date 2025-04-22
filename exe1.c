#include "files.h"


// fun 1

// Generate all valid knight moves for each position on the board
chessPosArray ***validKnightMoves() {
    chessPosArray ***possibilitiesArray;
    possibilitiesArray = builtArray();
    for (int letter = START_OF_COLUMN; letter < END_OF_COLUMN; letter++) {
        for (int number = START_OF_ROW; number < END_OF_ROW; number++) {
            possibilitiesArray[letter][number]->positions = availableMoveOptions(letter, number, &possibilitiesArray[letter][number]->size);
        }
    }
    return possibilitiesArray;
}

// Add a chess move to an array of moves
void enterChessMoveToArray(chessPos *originalArray, char letter, char number) {
    (*originalArray)[FIRST_PLACE] = letter;
    (*originalArray)[SECOND_PLACE] = number;
}

// Allocate memory for a 3D array to store possible moves
chessPosArray ***builtArray() {
    chessPosArray ***possibilitiesArray;
    possibilitiesArray = (chessPosArray ***)malloc(COLUMN_LENGTH * sizeof(chessPosArray **));
    for (int i = START_OF_ROW; i < END_OF_ROW; i++) {
        possibilitiesArray[i] = (chessPosArray **)malloc(COLUMN_LENGTH * sizeof(chessPosArray *));
        for (int j = START_OF_COLUMN; j < END_OF_COLUMN; j++) {
            possibilitiesArray[i][j] = (chessPosArray *)malloc(sizeof(chessPosArray));
        }
    }
    return possibilitiesArray;
}

// Allocate memory for an array of chess positions
chessPos *builtSpecificSquareKnightPossibilitiesArray(int options) {
    chessPos *chessPosArray;
    chessPosArray = (chessPos *)malloc(options * sizeof(chessPos));
    return chessPosArray;
}

// Determine the number of available moves for a knight from a given position
int checkNumberOfAvailableMoves(int letter, int number) {
    int realNumber = (int)(numbers[number]);
    char realLetter = letters[letter]; // in each if we understand on which square on the board the knight is found, so we can determine its possible moves.
    if (realNumber == '1' || realNumber == '5') {
        if (realLetter == 'A' || realLetter == 'E')
            return TWO_OPTIONS;
        if (realLetter == 'B' || realLetter == 'D')
            return THREE_OPTIONS;
        else
            return FOUR_OPTIONS;
    } else if (realNumber == '2' || realNumber == '4') {
        if (realLetter == 'A' || realLetter == 'E')
            return THREE_OPTIONS;
        if (realLetter == 'B' || realLetter == 'D')
            return FOUR_OPTIONS;
        else
            return SIX_OPTIONS;
    } else {
        if (realLetter == 'A' || realLetter == 'E')
            return FOUR_OPTIONS;
        if (realLetter == 'B' || realLetter == 'D')
            return SIX_OPTIONS;
        else
            return EIGHT_OPTIONS;
    }
}

// Calculate all possible moves a knight can make from a given position
chessPos *availableMoveOptions(int letterPosition, int numberPosition, unsigned int *sizeOfArray) {
    int possibilities = checkNumberOfAvailableMoves(letterPosition, numberPosition);
    chessPos *possiblePositions = builtSpecificSquareKnightPossibilitiesArray(possibilities);
    int positionCount = ZERO;

    // Define the order of moves based on the priority (up-up-right, left-left-up, clockwise)
    const int knightMoves[8][2] = {
            {-2, +1}, // Up-Up-Right
            {-1, +2}, // Right-Right-Up
            {+1, +2}, // Right-Right-Down
            {+2, +1}, // Down-Down-Right
            {+2, -1}, // Down-Down-Left
            {+1, -2}, // Left-Left-Down
            {-1, -2}, // Left-Left-Up
            {-2, -1}  // Up-Up-Left
    };

    // Iterate over the defined move order and check each move's validity
    for (int i = 0; i < 8; i++) {
        int newLetterPos = letterPosition + knightMoves[i][0];
        int newNumberPos = numberPosition + knightMoves[i][1];

        // Ensure the new position is within the bounds of the board
        if (newLetterPos >= START_OF_COLUMN && newLetterPos < END_OF_COLUMN &&
            newNumberPos >= START_OF_ROW && newNumberPos < END_OF_ROW) {
            // Add the valid move to the possible positions array
            enterChessMoveToArray(&possiblePositions[positionCount], letters[newLetterPos], numbers[newNumberPos]);
            positionCount++;
        }
    }

    *sizeOfArray = positionCount;
    return possiblePositions;
}
