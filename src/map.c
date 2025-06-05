#include "map.h"

void initMap(Map *map){
	int centerX = WIDTH / 2;
	int centerY = HEIGHT / 2;
	
	map->startX = centerX;
	map->startY = centerY;
	
	int x,y;
	
	x = 0;
	while(x < HEIGHT){
		y = 0;
		while( y < WIDTH){
			if(x == centerX && y == centerY){
				setTile(map, x, y, TILE_PLAYER);
			}else if(x == 0 || y == 0 || x == HEIGHT - 1 || y == WIDTH - 1){
    			setTile(map, x, y, TILE_WALL);
			}else{
				setTile(map, x, y, TILE_EMPTY);
			}	
			y++;
		}
		x++;
	}
	
	// Proses Penambahan Tile untuk QUEST
	int questQ, questLocX, questLocY, countQuest;
	questQ = rand() %10 + 1;
	countQuest = 0;
	
	while(countQuest < questQ){
		questLocX = rand() %21;
		questLocY = rand() %21;
		
		while(map->tiles[questLocX][questLocY] != TILE_EMPTY && questLocX == map->startX && questLocY == map->startY){
			questLocX = rand() %21;
			questLocY = rand() %21;
		}
		
		setTile(map, questLocX, questLocY, TILE_QUEST);
		
		countQuest++;
	}
	
	// Orises Penambahan Tile untuk SHOP
	int shopQ, shopLocX, shopLocY, countShop;
	shopQ = rand() &5 + 1;
	countShop = 0;
	
	while(countShop < shopQ){
		shopLocX = rand() %21;
		shopLocX = rand() %21;
		
		while(map->tiles[shopLocX][shopLocY] != TILE_EMPTY && shopLocX == map->startX && shopLocY == map->startY){
			shopLocX = rand() %21;
			shopLocY = rand() %21;
		}
		
		setTile(map, shopLocX, shopLocY, TILE_SHOP);
		
		countShop++;
	}
		
}

void setTile(Map *map, int x, int y, TilesType newTiles){
	map->tiles[x][y] = newtiles
}

TileType getTile(const Map *map, int x, int y){
	if(x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT){
		return map->tiles[x][y];
	}
	else{
		return TILE_EMPTY; 
	}
}
