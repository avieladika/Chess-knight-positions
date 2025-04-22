#include "files.h"


// fun 3

// Create a new tree node with a given position
treeNode* createNewTreeNode(chessPos pos) {
    treeNode *newTreeNode;
    newTreeNode = (treeNode *)malloc(sizeof(treeNode));
    if (newTreeNode == NULL)
        exit(1);
    newTreeNode->position[0] = pos[0];
    newTreeNode->position[1] = pos[1];
    newTreeNode->next_possible_positions.head = newTreeNode->next_possible_positions.tail = NULL;
    return newTreeNode;
}

// Add a tree node to the list of possible moves
void addTreeNodeListCell(treeNodeList *list, treeNode *node) {
    treeNodeListCell *newCell = (treeNodeListCell *)malloc(sizeof(treeNodeListCell));
    if (!newCell) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }
    newCell->node = node;
    newCell->next = NULL;
    if (list->head == NULL) {
        list->head = newCell;
        list->tail = newCell;
    } else {
        list->tail->next = newCell;
        list->tail = newCell;
    }
}

// Check if two chess positions are equal
bool areChessPosEqual(chessPos *pos1, chessPos *pos2) {
    return ((*pos1)[0] == (*pos2)[0] && (*pos1)[1] == (*pos2)[1]);
}

// Check if a chess position is in an array of positions
bool isChessPosInArray(chessPos *chessPosCells, int cellsLen, chessPos *pos) {
    for (int i = 0; i < cellsLen; i++)
        if (areChessPosEqual(&chessPosCells[i], pos))
            return true;
    return false;
}

// Recursively build the knight's path in a tree structure
void buildKnightPath(treeNode *root, chessPosArray ***arrPos, chessPos *path, int pathLen) {
    int row = root->position[1] - '1';
    int col = root->position[0] - 'A';
    chessPosArray *moves = arrPos[col][row];

    for (int i = 0; i < moves->size; i++) {
        if (!isChessPosInArray(path, pathLen, &moves->positions[i])) {
            treeNode *child = createNewTreeNode(moves->positions[i]);
            addTreeNodeListCell(&root->next_possible_positions, child);

            path[pathLen][0] = moves->positions[i][0];
            path[pathLen][1] = moves->positions[i][1];

            buildKnightPath(child, arrPos, path, pathLen + 1);
        }
    }
}

// Find all possible knight paths from a starting position
pathTree findAllPossibleKnightPaths(chessPos *startingPosition) {
    chessPosArray ***arrPos = validKnightMoves();
    pathTree tree;
    tree.root = createNewTreeNode(*startingPosition);

    chessPos *path = (chessPos *)malloc(ROW_LENGTH * COLUMN_LENGTH * sizeof(chessPos));
    if (!path) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }
    path[0][0] = (*startingPosition)[0];
    path[0][1] = (*startingPosition)[1];

    buildKnightPath(tree.root, arrPos, path, 1);

    for (int i = 0; i < ROW_LENGTH; i++) {
        for (int j = 0; j < COLUMN_LENGTH; j++) {
            free(arrPos[i][j]->positions);
            free(arrPos[i][j]);
        }
        free(arrPos[i]);
    }
    free(arrPos);
    free(path);

    return tree;
}
