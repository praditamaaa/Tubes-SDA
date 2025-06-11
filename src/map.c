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
	int questQ = rand() % 20 + 1;			// Menentukan Kuantitas TILE_QUEST
	int questLocX, questLocY, countQuest = 0;
	bool usedRows[HEIGHT] = {false};	// Menyimpan info baris yang sudah dipakai

	while (countQuest < questQ && countQuest < HEIGHT) {  // Maksimal = jumlah baris
    		questLocY = rand() %HEIGHT;

    		// Jika baris sudah dipakai, cari baris lain
    		while (usedRows[questLocY]) {
        		questLocY = rand() %HEIGHT;
    		}

    		questLocX = rand() %WIDTH;

    		// Pastikan tile kosong dan bukan di posisi start
    		while (map->tiles[questLocX][questLocY] != TILE_EMPTY || questLocX == map->startX && questLocY == map->startY)) {
        		questLocX = rand() %WIDTH;
    		}

    		// Set tile quest
    		setTile(map, questLocX, questLocY, TILE_QUEST);

    		// Tandai baris ini sudah digunakan
    		usedRows[questLocY] = true;
	    	countQuest++;
	}
	
	// Proses Penambahan Tile untuk SHOP
	int shopQ = rand() % 20 + 1;			// Menentukan Kuantitas TILE_SHOP
	int shopLocX, shopLocY, countShop = 0;
	bool usedRows[HEIGHT] = {false};	// Menyimpan info baris yang sudah dipakai

	while (countShop < shopQ && countShop < HEIGHT) {  // Maksimal = jumlah baris
    		shopLocY = rand() %HEIGHT;

    		// Jika baris sudah dipakai, cari baris lain
    		while (usedRows[shopLocY]) {
        		shopLocY = rand() %HEIGHT;
    		}

    		shopLocX = rand() %WIDTH;

    		// Pastikan tile kosong dan bukan di posisi start
    		while (map->tiles[shopLocX][shopLocY] != TILE_EMPTY || shopLocX == map->startX && shopLocY == map->startY)) {
        		shopLocX = rand() %WIDTH;
    		}

    		// Set tile shop
    		setTile(map, shopLocX, shopLocY, TILE_QUEST);

    		// Tandai baris ini sudah digunakan
    		usedRows[shopLocY] = true;
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
