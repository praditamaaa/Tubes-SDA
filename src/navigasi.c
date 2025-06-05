#include "navigasi.h"

void movePlayer(Map *map, Direction dir){
	// Mendapatkan posisi player saat ini dari map
	int currx, curry;
	currx = map->startX;
	curry = map->startY;
	
	// Membuat variabel baru untuk posisi setelah pemain bergerak
	int newx, newy;
	newx = currx;
	newy = curry;
	
	switch (dir){
	case UP:
		newx -= 1;
		break;
	case RIGHT:
		newy += 1;
		break;
	case DOWN:
		newx += 1;
		break;
	case LEFT:
		newy -= 1;
		break;
	}
	
	if (newx >= 0 && newx < HEIGHT && newy >= 0 && newy < WIDTH && map->tiles[newx][newy] != TILE_WALL) {
        // Cek apakah encounter terjadi
        if (checkEncounter()){
            // Encounter! Tidak pindah, tapi langsung masuk ke mode battle
            setTile(map, newx, newy, TILE_ENEMY);
            printf("Musuh muncul! Masuk mode battle.\n");
            // (Panggil sistem pertarungan di sini)
            return;
        }else if(map->tiles[newx][newy] == TILE_SHOP){
        	// BUKA SHOP
        	return;
		}else if(map->tiles[newx][newy] == TILE_QUEST){
			// ALUR SISTEMATIKA QUEST
			return;
		}

        // Tidak ada encounter, lanjutkan gerakan
        setTile(map, currx, curry, TILE_EMPTY);
        setTile(map, newx, newy, TILE_PLAYER);
        map->startX = newx;
        map->startY = newy;
    }
    
    
	
}
