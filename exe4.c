#include "files.h"

const char letters[COLUMN_LENGTH] = {'A', 'B', 'C', 'D', 'E'};
const char numbers[ROW_LENGTH] = {'1', '2', '3', '4', '5'};

// fun 4

// Initialize an empty list of chess positions
void makeEmptyList(chessPosList *list) {
    list->head = list->tail = NULL;
}

// Add a new node to the end of the chess position list
void addNodeToEnd(chessPosList *lst, chessPosCell *newNode) {
    if (lst->tail == NULL) {
        lst->head = lst->tail = newNode;
    } else {
        lst->tail->next = newNode;
        lst->tail = newNode;
    }
    newNode->next = NULL;
}

// Add data (position) to the end of the chess position list
void addDataToEnd(chessPosList *lst, chessPos pos) {
    chessPosCell *newNode = (chessPosCell *)malloc(sizeof(chessPosCell));
    newNode->position[FIRST_PLACE] = pos[FIRST_PLACE];
    newNode->position[SECOND_PLACE] = pos[SECOND_PLACE];
    newNode->next = NULL;
    addNodeToEnd(lst, newNode);
}

// Mark a position as visited in the matrix
void addDataToMat(int **mat, chessPos pos) {
    int row = pos[1] - '1'; // Converts character to integer
    int col = pos[0] - 'A'; // Converts character to integer
    mat[row][col] = FULL;
}

// Free the memory allocated for the matrix
void freeMatrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]); // Frees each row
    }
    free(matrix); // Frees the array of pointers
}

// Check if all positions on the board have been visited
bool checkMatIndication(int **mat) {
    for (int i = 0; i < ROW_LENGTH; i++) {
        for (int j = 0; j < COLUMN_LENGTH; j++) {
            if (mat[i][j] == EMPTY) {
                return false;
            }
        }
    }
    return true;
}

// Create a copy of a chess position list
chessPosList *createAndCopyList(chessPosList *list) {
    chessPosList *newList;
    chessPosCell *cell = list->head;
    newList = (chessPosList *)malloc(sizeof(chessPosList));
    makeEmptyList(newList);
    while (cell != NULL) {
        addDataToEnd(newList, cell->position);
        cell = cell->next;
    }
    return newList;
}

// Free the memory allocated for the chess position list
void freeList(chessPosList *list) {
    chessPosCell *cell = list->head;
    chessPosCell *cellHelp;
    while (cell != NULL) {
        cellHelp = cell;
        cell = cell->next;
        free(cellHelp);
    }
    free(list);
}

// Check if a position on the board is empty
bool checkChessPos(chessPos pos, int **matrix) {
    int row = pos[1] - '1'; // Converts character to integer
    int col = pos[0] - 'A'; // Converts character to integer
    return (matrix[row][col] == EMPTY);
}

// Find a knight's tour that covers the entire board
chessPosList *findKnightPathCoveringAllBoard(pathTree *path_tree) {
    int **matOfIndex = (int **)calloc(ROW_LENGTH, sizeof(int *));
    for (int i = 0; i < ROW_LENGTH; i++) {
        matOfIndex[i] = (int *)calloc(COLUMN_LENGTH, sizeof(int)); // Initialize with 0
    }

    chessPosList *list = (chessPosList *)malloc(sizeof(chessPosList));
    makeEmptyList(list);

    list = findKnightPathCoveringAllBoardRec(path_tree->root, list, matOfIndex);

    freeMatrix(matOfIndex, ROW_LENGTH);
    return list;
}

// Recursive function to find a knight's tour that covers the entire board
chessPosList *findKnightPathCoveringAllBoardRec(treeNode *node, chessPosList *list, int **matOfInd) {
    treeNodeListCell *current;
    chessPosList *newList;
    chessPosList *result;

    // Mark the current position on the matrix
    if (!checkChessPos(node->position, matOfInd)) {
        return NULL;
    }

    // Create a copy of the current list and matrix state
    newList = createAndCopyList(list);
    addDataToEnd(newList, node->position);
    addDataToMat(matOfInd, node->position);

    // Check if the entire board is covered after adding the current position
    if (checkMatIndication(matOfInd)) {
        return newList;
    }

    // Recursively explore all possible moves
    current = node->next_possible_positions.head;
    while (current != NULL) {
        result = findKnightPathCoveringAllBoardRec(current->node, newList, matOfInd);
        if (result != NULL) {
            freeList(newList); // Free the temporary list
            return result;
        }
        current = current->next;
    }

    // If no valid path found, backtrack: remove the current position from the matrix
    matOfInd[node->position[1] - '1'][node->position[0] - 'A'] = EMPTY;
    freeList(newList);
    return NULL;
}
