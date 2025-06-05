#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>

#define WIDTH 20
#define HEIGHT 20

typedef enum {
    TILE_EMPTY,
    TILE_WALL,
    TILE_PLAYER,
    TILE_QUEST,
    TILE_SHOP,
}TileType;

typedef struct {
    TileType tiles[HEIGHT][WIDTH];
    int startX, startY;
}Map;

void initMap(Map *map);
void setTile(Map *map, int x, int y, TilesType type);
TileType getTile(const Map *map, int x, int y,);
// Fungsi Menampilkan Peta akan berada di header Display

#endif
