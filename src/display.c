#include "display.h"

void drawBorder() {
    setColor(15); // PUTIH
    
    // border atas dan bawah
    int x, y;
    while(x <= WIDTH + 1){
    	gotoxy(x, 0);
        printf(WHITE_BG " " RESET);
        gotoxy(x, HEIGHT + 1);
        printf(WHITE_BG " " RESET);
        x++;
	}
    
    // border kiri dan kanan
    while(y <= HEIGHT + 5){
    	gotoxy(0, y);
        printf(WHITE_BG " " RESET);
        gotoxy(WIDTH + 1, y);
        printf(WHITE_BG " " RESET);
        y++;
	}
}

void drawMap(const Map *map) {
    for (int screenY = 0; screenY < HEIGHT; screenY++) {
        gotoxy(1, screenY + 1);
        for (int screenX = 0; screenX < WIDTH; screenX++) {
            // Konversi koordinat screen ke koordinat map
            int worldX = map->cameraX + screenX;
            int worldY = map->cameraY + screenY;
            
            TileType tile;
            
            // Get tile from world (with bounds checking)
            if (worldX >= 0 && worldX < WORLD_WIDTH && 
                worldY >= 0 && worldY < WORLD_HEIGHT) {
                tile = map->tiles[worldY][worldX];
            } else {
                tile = TILE_WALL;  
            }
            
            switch(tile) {
                case TILE_WALL:
                    setColor(8);  // ABU ua
                    break;
                case TILE_PLAYER:
                    setColor(14); // kunging
                    break;
                case TILE_SHOP:
                    setColor(10); //  hijau
                    break;
                case TILE_QUEST:
                    setColor(13); // magenta
                    break;
                case TILE_ENEMY:
                    setColor(12); // Merah
                    break;
                default:
                    setColor(7);  // Abu Mud
                    break;
            }
            
            printf("%c", (char)tile);
        }
    }
}

void drawUI(const Map *map, addressChar karakter) {
    setColor(11); // biru muda
    gotoxy(2, HEIGHT + 2);
    printf(" Use WASD or arrow keys to move, 'Z' to interact.");
    gotoxy(2, HEIGHT + 3);
    printf(" Press 'ESC' to pause, 'Q' to quit.              ");
    gotoxy(0, HEIGHT + 5);
    for (int i = 0; i <= WIDTH + 1; i++) {
        printf(WHITE_BG " " RESET);
    }
    
    int x = WIDTH + 2;
    int y = 0;
    
    gotoxy(86,0);
    printf(WHITE_BG " " RESET); 
    gotoxy(86, HEIGHT + 1);
	printf(WHITE_BG " " RESET);	
    
    gotoxy(x, 6);
    printf("HP : %d\n", karakter->Hp);
	gotoxy(x, 7);
	printf("LEVEL : %d\n", karakter->Lvl);
    
    // border atas bawah
    while(x <= 85){
    	gotoxy(x, 0);
        printf(WHITE_BG " " RESET);
        gotoxy(x, 5);
        printf(WHITE_BG " " RESET);
        gotoxy(x, HEIGHT + 5);
        printf(WHITE_BG " " RESET);
        x++;
	}
    
    // border kiri kanan
    while(y <= HEIGHT + 5){
    	//gotoxy(WIDTH + 3, y + 1);
        //printf("|");
        gotoxy(86, y);
        printf(WHITE_BG " " RESET);
        y++;
	}
       
    // info kamera dan koordinat player
    setColor(14); //kuning
    gotoxy(0, HEIGHT + 6);
    printf("# Player: (%d,%d) | Camera: (%d,%d) | World: %dx%d         #", 
           map->playerX, map->playerY, map->cameraX, map->cameraY, WORLD_WIDTH, WORLD_HEIGHT);
}

void drawBox(int startX, int startY, int width, int height) {
    // Gambar border horizontal
    int x = startX;
    int y = startY;
    while (x < startX + width){
    	gotoxy(x, startY);
        printf("-");
        gotoxy(x, startY + height - 1);
        printf("-");
        x++;
	}
    
    // Gambar border vertikal
    while(y < startY + height){
    	gotoxy(startX, y);
        printf("|");
        gotoxy(startX + width - 1, y);
        printf("|");
        y++;
	}
    
    // Gambar sudut
    gotoxy(startX, startY);
    printf("+");
    gotoxy(startX + width - 1, startY);
    printf("+");
    gotoxy(startX, startY + height - 1);
    printf("+");
    gotoxy(startX + width - 1, startY + height - 1);
    printf("+");
}

void drawCombatUi(addressChar *k, Enemy *enemy){
    int lastWidth = 0, lastHeight = 0;
    int termWidth, termHeight;
    
    clearScreen();
    
    while(1) {
        getTerminalSize(&termWidth, &termHeight);
            
        // Hitung ukuran dan posisi kotak berdasarkan ukuran terminal
        int marginX = 2;
        int marginY = 2;
        int availableWidth = termWidth - (marginX * 2);
        int availableHeight = termHeight - (marginY * 2);
            
        // Kotak besar di atas (sekitar 60% dari tinggi yang tersedia)
        int bigBoxHeight = (availableHeight * 6) / 10;
        int bigBoxWidth = availableWidth - 2;
                    
        // Gambar border horizontal
        int x = marginX + 1;
        int y = marginY + 18;
        while (x < marginX + 1 + bigBoxWidth + 1){
            gotoxy(x, y);
            printf(WHITE_BG " " RESET);
            gotoxy(x, y + 2 + bigBoxHeight - 13);
            printf(WHITE_BG " " RESET);
            x++;
        }
            
        // Gambar border vertikal
        while(y < marginY + 20 + bigBoxHeight - 12){
            gotoxy(marginX + 1, y);
            printf(WHITE_BG " " RESET);
            gotoxy(marginX + 1 + bigBoxWidth, y);
            printf(WHITE_BG " " RESET);
            y++;
        }
        
        drawCombatAt(marginX + (availableWidth / 2 - 15), 0);
        
        // ====== TAMPILKAN ENEMY FIGURE DI TENGAH KOTAK BESAR ======
        int enemyX = marginX + (availableWidth / 2 - 15);
        int enemyY = marginY + 7; // Posisi Y untuk enemy
        
        // Tampilkan ASCII art berdasarkan tipe enemy
        switch(enemy->Type) {
            case SLIME:
                drawSlimeAt(enemyX, enemyY);
                break;
            case WOLF:
                drawWolfAt(enemyX, enemyY);
                break;
            case GOBLIN:
                drawGoblinAt(enemyX, enemyY);
                break;
        }
        
        // ====== TAMPILKAN STATUS PLAYER & ENEMY ======
        // Status Player (kiri atas)
        gotoxy(marginX + 3, marginY + 1);
        printf("=== YOUR STATUS ===");
        gotoxy(marginX + 3, marginY + 3);
        printf("Level: %d", (*k)->Lvl);
        gotoxy(marginX + 3, marginY + 4);
        printf("HP: %d", (*k)->Hp);
        gotoxy(marginX + 3, marginY + 5);
        printf("ATT: %d", (*k)->Att);
        gotoxy(marginX + 3, marginY + 6);
        printf("DEF: %d", (*k)->Def);
        
        // Status Enemy (kanan atas)
        int enemyStatusX = marginX + availableWidth - 25;
        gotoxy(enemyStatusX, marginY + 1);
        printf("=== ENEMY STATUS ===");
        gotoxy(enemyStatusX, marginY + 2);
        printf("Type: %s", 
               (enemy->Type == SLIME) ? "SLIME" :
               (enemy->Type == WOLF) ? "WOLF" : "GOBLIN");
        gotoxy(enemyStatusX, marginY + 3);
        printf("Level: %d", enemy->Lv);
        gotoxy(enemyStatusX, marginY + 4);
        printf("HP: %d", enemy->Hp);
        gotoxy(enemyStatusX, marginY + 5);
        printf("ATT: %d", enemy->Att);
        gotoxy(enemyStatusX, marginY + 6);
        printf("DEF: %d", enemy->Def);
                
        //4 kotak kecil di bawah
        int smallBoxHeight = availableHeight - bigBoxHeight - 6;
        int smallBoxWidth = (availableWidth - 6) / 4;
        int smallBoxY = marginY + bigBoxHeight + 1 + 7;
                
        // Kotak 1-4
        drawBox(marginX + 2, smallBoxY, smallBoxWidth, smallBoxHeight);
        drawBox(marginX + 2 + smallBoxWidth + 1, smallBoxY, smallBoxWidth, smallBoxHeight);
        drawBox(marginX + 2 + (smallBoxWidth + 1) * 2, smallBoxY, smallBoxWidth, smallBoxHeight);
        drawBox(marginX + 2 + (smallBoxWidth + 1) * 3, smallBoxY, smallBoxWidth, smallBoxHeight);
        
        // Label untuk setiap kotak action
        gotoxy(marginX + 2 + smallBoxWidth/2 - 3, smallBoxY + 1);
        printf("ATTACK");
        gotoxy(marginX + 2 + smallBoxWidth + 1 + smallBoxWidth/2 - 4, smallBoxY + 1);
        printf("DEFENSE");
        gotoxy(marginX + 2 + (smallBoxWidth + 1) * 2 + smallBoxWidth/2 - 4, smallBoxY + 1);
        printf("USE ITEM");
        gotoxy(marginX + 2 + (smallBoxWidth + 1) * 3 + smallBoxWidth/2 - 3, smallBoxY + 1);
        printf("ESCAPE");
        
        // Tampilkan skill enemy di bawah figure
        gotoxy(enemyStatusX, marginY + 7);
        printf("Skills: %s | %s | %s", 
               enemy->skills[0].name,
               enemy->skills[1].name, 
               enemy->skills[2].name);
        
        // Instruksi input
        gotoxy(marginX + 4, termHeight - 15);
        printf("Press 1-4 to select action, or Q to quit");
                
        // Update ukuran terakhir
        lastWidth = termWidth;
        lastHeight = termHeight;
        
        // Input handling
        if(kbhit()) {
            char input = getch();
            switch(input) {
                case '1':
                    gotoxy(0, termHeight - 1);
                    printf("Attack selected! Press any key to continue...");
                    getch(); 
                    clearScreen(); 
                    return; 
                case '2':
                    gotoxy(0, termHeight - 1);
                    printf("Defense selected! Press any key to continue...");
                    getch();
                    clearScreen();
                    return;
                case '3':
                    gotoxy(0, termHeight - 1);
                    printf("Use Item selected! Press any key to continue...");
                    getch();
                    clearScreen();
                    return;
                case '4':
                case 'e':
                case 'E':
                    gotoxy(0, termHeight - 1);
                    printf("Escape selected! Press any key to continue...");
                    getch();
                    clearScreen();
                    drawBorder();
                    return;
                case 'q':
                case 'Q':
                case 27: 
                    gotoxy(0, termHeight - 1);
                    printf("Exiting combat... Press any key to continue...");
                    getch();
                    clearScreen();
                    drawBorder();
                    return;
            }
        }
        Sleep(100);
    }
}

void drawShopUI(addressChar *k, addressShopItem shop[]){
    // border atas dan bawah
    int lastWidth = 0, lastHeight = 0;
    int termWidth, termHeight;
    int shopMode = 0; // 0 = display mode, 1 = buying mode
    
    while(1){
        getTerminalSize(&termWidth, &termHeight);
        if(termWidth != lastWidth || termHeight != lastHeight || shopMode == 0){
            if(shopMode == 0) clearScreen();
            
            // Hitung ukuran dan posisi kotak berdasarkan ukuran terminal
            int marginX = 2;
            int marginY = 2;
            int availableWidth = termWidth - (marginX * 2);
            int availableHeight = termHeight - (marginY * 2);
            
            // Kotak besar di atas (sekitar 60% dari tinggi yang tersedia)
            int bigBoxHeight = (availableHeight * 6) / 10;
            int bigBoxWidth = availableWidth - 2;
                
            // Gambar border horizontal
            int x = marginX + 2;
            int y = marginY;
            while (x < bigBoxWidth - 33){
                gotoxy(x, y);
                printf(WHITE_BG " " RESET);
                gotoxy(x, y + 7 + bigBoxHeight);
                printf(WHITE_BG " " RESET);
                x++;
            }
            
            // Gambar border vertikal
            while(y < marginY + 20 + bigBoxHeight - 12){
                gotoxy(marginX + 1, y);
                printf(WHITE_BG " " RESET);
                gotoxy(marginX + bigBoxWidth - 36, y);
                printf(WHITE_BG " " RESET);
                y++;
            }
            
            //4 kotak kecil di bawah
            int smallBoxHeight = availableHeight - bigBoxHeight - 6;
            int smallBoxWidth = (availableWidth - 6) / 4;\
            int smallBoxY = marginY + bigBoxHeight + 1 + 7;
            
            // Kotak 1
            drawBox(marginX + 1, smallBoxY, smallBoxWidth + 71, smallBoxHeight);
            
            // Kotak 4
            drawBox(marginX + 2 + (smallBoxWidth + 1) * 3, smallBoxY - 27, smallBoxWidth, smallBoxHeight + 27); 
            
            // Gambar box atas kanan (tempat nama shop) 
            drawBox(marginX + 2 + (smallBoxWidth + 1) * 3, smallBoxY - 27, smallBoxWidth, smallBoxHeight);
            
            //RENDER GAMBAR
            drawShopAt(marginX + 7 + (smallBoxWidth + 1) * 3, smallBoxY - 26);
            
            //POTION 1
            drawpotionAt(marginX + 10, 7);  
            gotoxy(marginX + 11, 25);
            printf("%s (%d Gold)", shop[0].item, shop[0].price);
            gotoxy(marginX + 20, 26);
            printf("Stok: %d", shop[0].stock);
            //POTION 2
            drawpotionAt(marginX + 40, 7);
            gotoxy(marginX + 43, 25);
            printf("%s (%d Gold)", shop[1].item, shop[1].price);
            gotoxy(marginX + 50, 26);
            printf("Stok: %d", shop[1].stock);
            //POTION 3
            drawpotionAt(marginX + 70, 7);
            gotoxy(marginX + 73, 25);
            printf("%s (%d Gold)", shop[2].item, shop[2].price);
            gotoxy(marginX + 80, 26);
            printf("Stok: %d", shop[2].stock);
            
			//====== RIGHT BAR TEXT =======       
            gotoxy(marginX + 13 + (smallBoxWidth + 1) * 3, smallBoxY - 20);
            printf("PILIHAN ITEM\n"); 
            
            tampilkanGold(k, 113, smallBoxY + 4);          
            tampilkanItem(shop);
            
            // Tambahkan instruksi kontrol
            gotoxy(marginX + 4, smallBoxY + 2);
            printf("Tekan 'B' untuk membeli");
            gotoxy(marginX + 4, smallBoxY + 3);
            printf("Tekan 'Q' untuk keluar");
            
            // Update ukuran terakhir
            lastWidth = termWidth;
            lastHeight = termHeight;
            shopMode = 1; 
        }
        
        // Handle input dari user
        if(kbhit()) {
            char input = getch();
            clearInputArea();
            
            switch(input) {
                case 'b':
                case 'B':
                    pembelianItemShop(k, shop);
                    clearInputArea();
                    shopMode = 0; 
                    break;
                    
                case 'q':
                case 'Q':
                	clearScreen();
                    return; 
                    
                default:
                    gotoxy(113, 22);
                    printf("Tekan 'B' untuk beli, 'Q' keluar");
                    Sleep(1000);
                    clearInputArea();
                    break;
            }
        }
        Sleep(100); 
    }
}

void gameLoop(Map *map, addressChar k, addressShopItem shop[]) {
    int running = 1;
    char key;
    
    clearScreen();
    hideCursor();
    drawBorder();
    drawMap(map);
    drawUI(map,k);
    
    gotoxy(0, HEIGHT + 7);
    setColor(15);
    printf("Camera/Viewport System Test - Explore the %dx%d world!", WORLD_WIDTH, WORLD_HEIGHT);
    
    while (running) {
        if (_kbhit()) {
            key = getInput();
            
            if (!isValidInput(key)) continue;
            
            switch (key) {
                case 'w': case 'W': case 72: 
                    movePlayer(map, UP, &k, shop);
                    break;
                case 's': case 'S': case 80:
                    movePlayer(map, DOWN, &k, shop);
                    break;
                case 'a': case 'A': case 75: 
                    movePlayer(map, LEFT, &k, shop);
                    break;
                case 'd': case 'D': case 77: 
                    movePlayer(map, RIGHT, &k, shop);
                    break;
                case 'z': case 'Z':
                    gotoxy(0, HEIGHT + 6);
                    setColor(11);
                    printf("Interacting...                                      ");
                    Sleep(1000);
                    gotoxy(0, HEIGHT + 6);
                    printf("                                                    ");
                    break;
                case 27: 
                    gotoxy(0, HEIGHT + 6);
                    setColor(12);
                    printf("Game paused. Press any key to continue...           ");
                    getch();
                    gotoxy(0, HEIGHT + 6);
                    printf("                                                    ");
                    break;
                case 'q': case 'Q':
                    running = 0;
                    break;
            }
            
            drawBorder(); 
            
            // Gambar ulang kalo player bergerak 
            if (key == 'w' || key == 'W' || key == 72 ||
                key == 's' || key == 'S' || key == 80 ||
                key == 'a' || key == 'A' || key == 75 ||
                key == 'd' || key == 'D' || key == 77) {
                drawMap(map);
                drawUI(map, k);
            }
        } else {
            
            drawBorder();
        }
        Sleep(50); 
    }
}
