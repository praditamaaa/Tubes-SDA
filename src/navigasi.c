#include "navigasi.h"
#include "display.h"

void movePlayer(Map *map, Direction dir, addressChar* k, addressShopItem shop[], addressUser loggedUser) {
    int currX = map->playerX;
    int currY = map->playerY;
    
    int newX = currX;
    int newY = currY;
    
    switch (dir) {
        case UP:
            newY -= 1;
            break;
        case RIGHT:
            newX += 1;
            break;
        case DOWN:
            newY += 1;
            break;
        case LEFT:
            newX -= 1;
            break;
    }
    
    // Check boundaries and collision in world coordinates
    if (newX >= 0 && newX < WORLD_WIDTH && newY >= 0 && newY < WORLD_HEIGHT && 
        getTile(map, newX, newY) != TILE_WALL) {
        
        // Check encounter
        if (checkEncounter()) {
            gotoxy(30, HEIGHT + 6);
            setColor(12); // Red
            printf("Musuh muncul! Masuk mode battle.                    ");
            Sleep(1500);
            
            // Buat enemy dan mulai battle
            Enemy enemy;
            EnemyType randomType = rand() % 3; // 0=SLIME, 1=WOLF, 2=GOBLIN
            initEnemy(&enemy, randomType, *k);
             
            // Mulai battle 
			drawCombatUi(k, &enemy); //ini ketika musuh lari atau kita escape loop berhenti
            clearScreen();
            gotoxy(30, HEIGHT + 6);
            printf("                                                    ");
            return;
        } 
        else if (getTile(map, newX, newY) == TILE_SHOP) {
            gotoxy(30, HEIGHT + 6);
            setColor(10); // Green
            printf("Entering shop...                                    ");
            Sleep(1000);
			drawShopUI(k, shop); 
            clearScreen();
            gotoxy(30, HEIGHT + 6);
            printf("                                                    ");
            return;
        } 
        else if (getTile(map, newX, newY) == TILE_QUEST) {
            gotoxy(30, HEIGHT + 6);
            setColor(13); // Magenta
            printf("Quest found!                                        ");
            Sleep(1000);
            assignRandomQuest(loggedUser); 
    		Sleep(1000);
            gotoxy(30, HEIGHT + 6);
            printf("                                                    ");
        }
        
        // PERGERKAN 
        setTile(map, currX, currY, TILE_EMPTY);
        setTile(map, newX, newY, TILE_PLAYER);
        map->playerX = newX;
        map->playerY = newY;
        
        // UPDATE KAMERA AGAR IKUT PLAYER
        updateCamera(map);
    }
}

bool checkEncounter() {
    return (rand() % 100) < 25; 
}
