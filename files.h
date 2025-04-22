

#ifndef PROJECT_TO_UPLOAD_FILES_H
#define PROJECT_TO_UPLOAD_FILES_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROW_LENGTH 5
#define COLUMN_LENGTH 5
#define START_OF_COLUMN 0
#define END_OF_COLUMN 5
#define START_OF_ROW 0
#define END_OF_ROW 5
#define FIRST_PLACE 0
#define SECOND_PLACE 1
#define THIRD_PLACE 2
#define FORTH_PLACE 3
#define TWO_OPTIONS 2
#define THREE_OPTIONS 3
#define FOUR_OPTIONS 4
#define SIX_OPTIONS 6
#define EIGHT_OPTIONS 8
#define ZERO 0
#define ONE 1
#define SIX 6
#define EMPTY 0
#define FULL 1

extern const char letters[COLUMN_LENGTH];
extern const char numbers[ROW_LENGTH];

typedef char chessPos[2]; // Represents a chess position as two characters

struct _treeNodeListCell; // Forward declaration for treeNodeListCell

// Structure to store possible knight moves from a position
typedef struct _chessPosArray {
    unsigned int size; // Number of possible positions
    chessPos *positions; // Array of possible positions
} chessPosArray;

// Structure to represent a cell in the linked list of chess positions
typedef struct _chessPosCell {
    chessPos position; // Chess position
    struct _chessPosCell *next; // Pointer to the next cell
} chessPosCell;

// Structure to represent a list of chess positions
typedef struct _chessPosList {
    chessPosCell *head; // Pointer to the head of the list
    chessPosCell *tail; // Pointer to the tail of the list
} chessPosList;

// Structure to represent a list of tree nodes
typedef struct _treeNodeList {
    struct _treeNodeListCell *head; // Pointer to the head of the list
    struct _treeNodeListCell *tail; // Pointer to the tail of the list
} treeNodeList;

// Structure to represent a tree node for the knight's path
typedef struct _treeNode {
    chessPos position; // Chess position at this node
    treeNodeList next_possible_positions; // List of possible next positions
} treeNode;

// Structure to represent a cell in the list of tree nodes
typedef struct _treeNodeListCell {
    treeNode *node; // Pointer to the tree node
    struct _treeNodeListCell *next; // Pointer to the next cell
} treeNodeListCell;

// Structure to represent the path tree
typedef struct _pathTree {
    treeNode *root; // Root node of the tree
} pathTree;

// Function prototypes
chessPosArray ***validKnightMoves();
void enterChessMoveToArray(chessPos *originalArray, char letter, char number);
chessPosArray ***builtArray();
chessPos *builtSpecificSquareKnightPossibilitiesArray(int options);
int checkNumberOfAvailableMoves(int letter, int number);
chessPos *availableMoveOptions(int letterPosition, int numberPosition, unsigned int *sizeOfArray);
chessPosCell* deleteNode(chessPosList *lst, chessPosCell *cell, chessPosCell *prev);
void myMalloc(int ***mat);
int convertLetterIntoInt(char ch);
int convertCharIntIntoInt(char ch);
int **builtRepresentingArray(chessPosList *lst);
void printMatt(int **matt, int row, int col);
void display(chessPosList *lst);
treeNode* createNewTreeNode(chessPos pos);
void addTreeNodeListCell(treeNodeList *list, treeNode *node);
bool areChessPosEqual(chessPos *pos1, chessPos *pos2);
bool isChessPosInArray(chessPos *chessPosCells, int cellsLen, chessPos *pos);
void buildKnightPath(treeNode *root, chessPosArray ***arrPos, chessPos *path, int pathLen);
pathTree findAllPossibleKnightPaths(chessPos *startingPosition);
void makeEmptyList(chessPosList *list);
void addNodeToEnd(chessPosList *lst, chessPosCell *newNode);
void addDataToEnd(chessPosList *lst, chessPos pos);
void addDataToMat(int **mat, chessPos pos);
void freeMatrix(int **matrix, int rows);
bool checkMatIndication(int **mat);
chessPosList* createAndCopyList(chessPosList *list);
void freeList(chessPosList *list);
bool checkChessPos(chessPos pos, int **matrix);
chessPosList* findKnightPathCoveringAllBoard(pathTree *path_tree);
chessPosList *findKnightPathCoveringAllBoardRec(treeNode *node, chessPosList *list, int **matOfInd);


#endif //PROJECT_TO_UPLOAD_FILES_H
