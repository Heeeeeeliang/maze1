#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#define MAXX 10
#define MAXY 10
char map[MAXX][MAXY];
int playerX;
int playerY;
int startX;
int startY;
#ifndef BOOL_DEFINED
#define BOOL_DEFINED
typedef enum { false, true } bool;
#endif
bool attemptMove(int newX, int newY);
void loadMaze(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file:\n");
        return;
    }
    char c;
    int x = 0, y = 0;
    while ((c = fgetc(file)) != EOF && x < MAXX) {
        if (c == '\n') {
            x++;
            y = 0;
        } else {
            map[x][y] = c;
            if (c == 'S') {
                startX = x;
                startY = y;
            }
            y++;
        }
    }
    playerX = startX;
    playerY = startY;
    map[playerX][playerY] = 'X';
    fclose(file);
}

bool attemptMove(int newX, int newY) {
    if (newX >= 0 && newX < MAXX && newY >= 0 && newY < MAXY &&
        (map[newX][newY] == ' ' || map[newX][newY] == 'E')) {
        map[playerX][playerY] = ' ';
        map[startX][startY] = 'S';
        map[newX][newY] = 'X';
        playerX = newX;
        playerY = newY;
        return true;
    }
    return false;
}
void showMap(void) {
    for (int i = 0; i < MAXX; i++) {
        for (int j = 0; j < MAXY; j++) {
            if (map[i][j] == 'X') map[i][j] = ' ';
        }
    }
    map[playerY][playerX] = 'X';
    for (int i = 0; i < MAXX; i++) {
        for (int j = 0; j < MAXY; j++) {
            printf("%c", map[i][j] ? map[i][j] : ' ');
        }
        printf("\n");
    }
}
int main() {
//    char filename[] = "reg_5x5(1).txt";
//    char filename[] = "reg_10x6(1).txt";
    char filename[1024] = { 0 };
    printf("filename: ");
    scanf("%s", filename);
    getchar();
    loadMaze(filename);
    int width, height;
    playerX = startX;
    playerY = startY;
    map[playerY][playerX] = 'X';

    while (true) {
        printf("Enter (w/a/s/d)or(W/A/S/D)to move and M to view the map.\n");
        printf("Enter (q/Q) to quit\n");
        char action;
        action = getchar();
        getchar();
        if (action == 'q' || action == 'Q') {
            break;
        }
        if (action == 'M' || action == 'm') {
            printf("map\n");
            showMap();
            continue;
        }
        int newplayerX = playerX;
        int newplayerY = playerY;
        switch (action) {
        case 'W': case 'w':
            newplayerY--;
            break;
        case 'A': case 'a':
            newplayerX--;
            break;
        case 'S': case 's':
            newplayerY++;
            break;
        case 'D': case 'd':
            newplayerX++;
            break;
        default:
            printf("Invalid move. Use W, A, S, D to move.\n");
            break;
        }
        if (newplayerX >= MAXX || newplayerY >= MAXY || map[newplayerY][newplayerX] == '#') {
            printf("Move blocked by a wall or boundary.\n");
            continue;
        }
        if (map[newplayerY][newplayerX] == 'E') {
            printf("win!!!\n");
            return 0;
        }
        playerX = newplayerX;
        playerY = newplayerY;
    }
    return 0;
}