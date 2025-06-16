#ifndef MAP_H
#define MAP_H
#include "common.h"

typedef enum {
    TILE_EMPTY = ' ',
    TILE_WALL = 'X',
    TILE_PLAYER = '@',
    TILE_ENEMY = 'E',
    TILE_SHOP = '+',
    TILE_QUEST = '?'
} TileType;

typedef struct {
    TileType tiles[WORLD_HEIGHT][WORLD_WIDTH];
    int playerX, playerY;  
    int cameraX, cameraY;  
} Map;

void initMap(Map *map);
void setTile(Map *map, int x, int y, TileType newTiles);
TileType getTile(const Map *map, int x, int y);
void updateCamera(Map *map);  

#endif
