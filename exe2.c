#include "files.h"


// fun 2

// Delete a node from the chess position list
chessPosCell* deleteNode(chessPosList *lst, chessPosCell *cell, chessPosCell *prev) {
    if (lst->head == lst->tail) {
        lst->head = lst->tail = NULL;
        free(cell);
        return NULL;
    } else if (prev == NULL) {
        lst->head = cell->next;
        free(cell);
        return lst->head;
    } else if (cell->next == NULL) {
        lst->tail = prev;
        prev->next = NULL;
        free(cell);
        return lst->tail;
    } else
        prev->next = cell->next;
    free(cell);
    return prev;
}

// Allocate and initialize a matrix for representing the chessboard
void myMalloc(int ***mat) {
    *mat = (int **)malloc(ROW_LENGTH * sizeof(int *));
    for (int i = START_OF_ROW; i < END_OF_ROW; i++) {
        (*mat)[i] = (int *)malloc(COLUMN_LENGTH * sizeof(int));
        for (int j = START_OF_COLUMN; j < END_OF_COLUMN; j++) {
            (*mat)[i][j] = ZERO;
        }
    }
}

// Convert a letter (A-E) to its corresponding index (0-4)
int convertLetterIntoInt(char ch) {
    return ch - 'A';
}

// Convert a number character (1-5) to its corresponding index (0-4)
int convertCharIntIntoInt(char ch) {
    return ch - '1';
}

// Build a matrix representing the knight's path
int **builtRepresentingArray(chessPosList *lst) {
    int **matOfChess, count = ONE;
    chessPosCell *chs1 = lst->head, *prev = NULL;
    myMalloc(&matOfChess);
    while (chs1 != NULL) {
        if (matOfChess[convertLetterIntoInt(chs1->position[FIRST_PLACE])][convertCharIntIntoInt(chs1->position[SECOND_PLACE])] > ZERO)
            chs1 = deleteNode(lst, chs1, prev);
        else {
            matOfChess[convertLetterIntoInt(chs1->position[FIRST_PLACE])][convertCharIntIntoInt(chs1->position[SECOND_PLACE])] = count;
            count++;
            prev = chs1;
        }
        if (chs1 != NULL)
            chs1 = chs1->next;
    }
    return matOfChess;
}

// Print the matrix representation of the knight's path
void printMatt(int **matt, int row, int col) {
    for (int i = ONE; i < SIX; i++)
        printf(" %d   ", i);
    printf("\n");
    for (int i = ZERO; i < row; i++) {
        for (int j = ZERO; j < col; j++) {
            if (j == ZERO)
                printf("|%c| ", letters[i]);
            printf("%d| ", matt[i][j]);
        }
        printf("\n");
    }
}

// Display the knight's tour in matrix form
void display(chessPosList *lst) {
    int **matOfChess = builtRepresentingArray(lst);
    printMatt(matOfChess, ROW_LENGTH, COLUMN_LENGTH);
    freeMatrix(matOfChess, ROW_LENGTH);
}
