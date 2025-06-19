#include "map.h"

void initMap(Map *map) {
    // player di tengah map
    int centerX = WORLD_WIDTH / 2;
    int centerY = WORLD_HEIGHT / 2;
    
    map->playerX = centerX;
    map->playerY = centerY;
    
    // pov ke arah player
    map->cameraX = centerX - WIDTH / 2;
    map->cameraY = centerY - HEIGHT / 2;
    
    // Inisialiasi map
    int x;
    for (x = 0; x < WORLD_HEIGHT; x++) {
    	int y;
        for (y = 0; y < WORLD_WIDTH; y++) {
            // buat tembok map
            if (x == 0 || y == 0 || x == WORLD_HEIGHT - 1 || y == WORLD_WIDTH - 1) {
                map->tiles[x][y] = TILE_WALL;
            }
            // set player di tenagh
            else if (x == centerY && y == centerX) {
                map->tiles[x][y] = TILE_PLAYER;
            }
            else {
                map->tiles[x][y] = TILE_EMPTY;
            }
        }
    }
    
    int i;
    // Add random walls throughout the world
    for (i = 0; i < 800; i++) {
        int wallX = 2 + rand() % (WORLD_WIDTH - 4);
        int wallY = 2 + rand() % (WORLD_HEIGHT - 4);
        if (map->tiles[wallY][wallX] == TILE_EMPTY) {
            map->tiles[wallY][wallX] = TILE_WALL;
        }
    }
    
    // tile quest
    int questQ = rand() % 15 + 5;  // 5-19 tile quest
    int countQuest = 0;
    
    while (countQuest < questQ) {
        int questLocX = 2 + rand() % (WORLD_WIDTH - 4);
        int questLocY = 2 + rand() % (WORLD_HEIGHT - 4);
        
        if (map->tiles[questLocY][questLocX] == TILE_EMPTY && 
            !(questLocX == map->playerX && questLocY == map->playerY)) {
            setTile(map, questLocX, questLocY, TILE_QUEST);
            countQuest++;
        }
    }
    
    // tile shop
    int shopQ = rand() % 8 + 3;  // 3-10 tile shop
    int countShop = 0;
    
    while (countShop < shopQ) {
        int shopLocX = 2 + rand() % (WORLD_WIDTH - 4);
        int shopLocY = 2 + rand() % (WORLD_HEIGHT - 4);
        
        if (map->tiles[shopLocY][shopLocX] == TILE_EMPTY && 
            !(shopLocX == map->playerX && shopLocY == map->playerY)) {
            setTile(map, shopLocX, shopLocY, TILE_SHOP);
            countShop++;
        }
    }
}

void setTile(Map *map, int x, int y, TileType newTiles) {
    if (x >= 0 && x < WORLD_WIDTH && y >= 0 && y < WORLD_HEIGHT) {
        map->tiles[y][x] = newTiles;
    }
}

TileType getTile(const Map *map, int x, int y) {
    if (x >= 0 && x < WORLD_WIDTH && y >= 0 && y < WORLD_HEIGHT) {
        return map->tiles[y][x];
    } else {
        return TILE_WALL;
    }
}

void updateCamera(Map *map) {
    // pov player di layar
    map->cameraX = map->playerX - WIDTH / 2;
    map->cameraY = map->playerY - HEIGHT / 2;
    
    // pov player di layar pas di ujung map
    if (map->cameraX < 0) map->cameraX = 0;
    if (map->cameraY < 0) map->cameraY = 0;
    if (map->cameraX + WIDTH > WORLD_WIDTH) map->cameraX = WORLD_WIDTH - WIDTH;
    if (map->cameraY + HEIGHT > WORLD_HEIGHT) map->cameraY = WORLD_HEIGHT - HEIGHT;
}
