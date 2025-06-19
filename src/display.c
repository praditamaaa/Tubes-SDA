#include "display.h"

void tampilkanASCII() {
    printCenteredAtRow("                                                                                                    ",1);
    printCenteredAtRow("                                                                                                    ",2);
    printCenteredAtRow("                                                                                                    ",3);
    printCenteredAtRow(":::::      :::::  ::::::  :::: :::::::::::: :::::   ::::::   :::::::::    :::::::::        :::::    ",4);
    printCenteredAtRow(" :::::    ::::::    ::::  ::   ::  ::::  ::  :::     ::::  ::::     ::::   :::  ::::      ::::::    ",5);
    printCenteredAtRow(" :;::::  ;:;:::;     ::::::        ::::      :::     ;:::  ::::     ;::;;  :::  ::::     ;:: ::::   ",6);
    printCenteredAtRow(" ;; ;;;;;;;:;;;;       ;;;         ;;;;      ;;;;::;;;;;; ;;;;;      ;;;;  ;;;;;;;       ;;  ;;;;;  ",7);
    printCenteredAtRow(" ;;  ;;;;; ;;;;;       ;;;         ;;;;      ;;;     ;;;;  ;;;;      ;;;   ;;; ;;;;;    ;;;   ;;;;  ",8);
    printCenteredAtRow(" ;;  ;;;;  ;;;;;      ;;;;         ;;;;      ;;;;    ;;;;   ;;;;;  ;;;;   ;;;;; ;;;;;  ;;;     ;;;; ",9);
    printCenteredAtRow(";;;;   ;   ;;;;;     ;;;;;;       ;;;;;;    ;;;;;   ;;;;;;     ;;;;;      ;;;;;   ;;;;;;;;;   ;;;;;;",10);
    printCenteredAtRow("                                                                                                    ",11);
    printCenteredAtRow("                                                                                                    ",12);
    printCenteredAtRow("                                                                                                    ",13);
}

void welcomeScreen() {
	const char* loadingFrames[] = {
        "Tekan Enter untuk Memulai   ",
        "Tekan Enter untuk Memulai.  ",
        "Tekan Enter untuk Memulai.. ",
        "Tekan Enter untuk Memulai...",
    };
    int frame = 0;

    // Tentukan baris tempat teks akan ditampilkan (di bawah ASCII art)
    int row = 16; 

    int numFrames = sizeof(loadingFrames) / sizeof(loadingFrames[0]); // frame = 3

    while (1) {
        char fullText[100];
        snprintf(fullText, sizeof(fullText), "%s", loadingFrames[frame]);
        
        tampilkanASCII();
        printCenteredAtRow(fullText, row);

        Sleep(1000);
        frame = (frame + 1) % numFrames;

        if (_kbhit()) {
            if (_getch() == '\r') { 
            	inputNama();
                break;
            }
        }
    }
}

void inputNama(){
    int frame = 0;
    int row = 16; 
    char Nama[100];
    printCenteredAtRow("Input Nama: ", row);
    scanf("%99s", Nama); 
    getchar(); 
    
    menuUser(); 
}

void menuUser() {
	int pilihan;
	printCenteredAtRow("Mythora Turn Based RPG", 13);
	printCenteredAtRow("#===================================================================================================#", 14);
	printCenteredAtRow("| 1. New Game                                                                                       |", 15);
	printCenteredAtRow("| 2. Load Game                                                                                      |", 16);
	printCenteredAtRow("| 3. Exit                                                                                           |", 17);
	printCenteredAtRow("#===================================================================================================#", 18);
	printCenteredAtRow("Pilihan:", 19);
	scanf("%d", &pilihan);
	getchar(); 
	pilihMenu(pilihan);
}

void pilihMenu(int pilihan){
    switch (pilihan) {
        case 1:
            inputCharUser();
            break;
        case 2: 
            printf("Buat lanjut progress");
            break;
        case 3:
        	exit(0);
            break;
        default:
            printf("Pilihan tidak valid\n");
            break;
    }
}

void drawBorder() {
    setColor(15); // PUTIH
    
    // border atas dan bawah
    int x, y;
    while(x <= WIDTH + 1){
    	gotoxy(x + 30, 0);
        printf(WHITE_BG " " RESET);
        gotoxy(x + 30, HEIGHT + 1);
        printf(WHITE_BG " " RESET);
        x++;
	}
    
    // border kiri dan kanan
    while(y <= HEIGHT + 5){
    	gotoxy(30, y);
        printf(WHITE_BG " " RESET);
        gotoxy(WIDTH + 31, y);
        printf(WHITE_BG " " RESET);
        y++;
	}
}

void drawMap(const Map *map) {
    for (int screenY = 0; screenY < HEIGHT; screenY++) {
        gotoxy(31, screenY + 1);
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
    gotoxy(32, HEIGHT + 2);
    printf(" Use WASD or arrow keys to move, 'Z' to interact.");
    gotoxy(32, HEIGHT + 3);
    printf(" Press 'ESC' to pause, 'Q' to quit.              ");
    gotoxy(31, HEIGHT + 5);
    for (int i = 30; i <= WIDTH + 31; i++) {
        printf(WHITE_BG " " RESET);
    }
    
    int x = WIDTH + 32;
    int y = 0;
    
    gotoxy(86,0);
    printf(WHITE_BG " " RESET); 
    gotoxy(86, HEIGHT + 1);
	printf(WHITE_BG " " RESET);	
    
    gotoxy(x, 1);
    printf("HP    : %d\n", karakter->Hp);
	gotoxy(x, 2);
	printf("LEVEL : %d\n", karakter->Lvl);
	gotoxy(x, 3);
    printf("EXP   : %d\n", karakter->Exp);
    gotoxy(x, 4);
    printf("Gold  : %d\n", karakter->Gold);
    gotoxy(x, 6);
    printf("   === INventory ===");
    gotoxy(x, 7);
    tampilkanInventoryKarakter(karakter);
    // border atas bawah
    while(x <= 115){
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
        gotoxy(116, y);
        printf(WHITE_BG " " RESET);
        y++;
	}
       
    // info kamera dan koordinat player
    setColor(14); //kuning
    gotoxy(30, HEIGHT + 6);
    printf("# Player: (%d,%d) | Camera: (%d,%d) | World: %dx%d         #", 
           map->playerX, map->playerY, map->cameraX, map->cameraY, WORLD_WIDTH, WORLD_HEIGHT);
           
    gotoxy(30, HEIGHT + 7);
    setColor(15);
    printf("Camera/Viewport System - Explore the %dx%d world!", WORLD_WIDTH, WORLD_HEIGHT);
    gotoxy(30, HEIGHT + 8);
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

int drawCombatUi(addressChar *k, Enemy *enemy){
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
        
        //drawCombatAt(marginX + (availableWidth / 2 - 15), 0);
        
        // ====== TAMPILKAN ENEMY FIGURE DI TENGAH KOTAK BESAR ======
        int enemyX = marginX + (availableWidth / 2 - 15); 
        int enemyY = marginY + 7; 
        
        // Tampilkan ASCII art berdasarkan tipe enemy 
        switch(enemy->Type) {
            case SLIME:
                drawSlimeAt(enemyX - 15, enemyY - 5);
                break;
            case WOLF:
                drawWolfAt(enemyX - 5, enemyY - 6);
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
        int enemyStatusX = marginX - 10 + availableWidth - 25;
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
                
        //4 kotak kecil di bawah untk menampilkan log battle
        int smallBoxHeight = availableHeight - bigBoxHeight - 8;
        int smallBoxWidth = (availableWidth - 6) / 5;
        int smallBoxY = marginY + bigBoxHeight + 8;
        
        // Kotak 1-5
        drawBox(marginX + 2, smallBoxY, smallBoxWidth, smallBoxHeight);
        drawBox(marginX + 2 + smallBoxWidth + 1, smallBoxY, smallBoxWidth, smallBoxHeight);
        drawBox(marginX + 2 + (smallBoxWidth + 1) * 2, smallBoxY, smallBoxWidth, smallBoxHeight);
        drawBox(marginX + 2 + (smallBoxWidth + 1) * 3, smallBoxY, smallBoxWidth, smallBoxHeight);
        drawBox(marginX + 2 + (smallBoxWidth + 1) * 4, smallBoxY, smallBoxWidth, smallBoxHeight);
        
        // Label untuk setiap kotak action
        gotoxy(marginX + 2 + smallBoxWidth/2 - 3, smallBoxY + 1);
        printf("ATTACK");
        gotoxy(marginX + 2 + smallBoxWidth + 1 + smallBoxWidth/2 - 4, smallBoxY + 1);
        printf("SKILL");
        gotoxy(marginX + 2 + (smallBoxWidth + 1) * 2 + smallBoxWidth/2 - 4, smallBoxY + 1);
        printf("DEFENSE");
        gotoxy(marginX + 2 + (smallBoxWidth + 1) * 3 + smallBoxWidth/2 - 3, smallBoxY + 1);
        printf("PAKE ITEM");
        gotoxy(marginX + 2 + (smallBoxWidth + 1) * 4 + smallBoxWidth/2 - 3, smallBoxY + 1);
        printf("ESCPAE");
        
        // Tampilkan skill enemy di bawah figure
        gotoxy(enemyStatusX, marginY + 7);
        printf("Skills: %s | %s | %s", 
               enemy->skills[0].name,
               enemy->skills[1].name, 
               enemy->skills[2].name);
        
        // Instruksi input
        gotoxy(marginX + 4, termHeight - 15);
        printf("Press A (Attack), F (Skill), D (Defense), R (Pake Item), E (Escape)");
                
        // Update ukuran terakhir
        lastWidth = termWidth;
        lastHeight = termHeight;
        
        // Input handling
        if(kbhit()) {
            char input = getch();
            switch(input) {
                case 'A': case 'a':
                    return 1;
                case 'F': case 'f':
                	return 2;
                case 'D': case 'd':
                    return 3;
                case 'R': case 'r':
                    return 4;
                case 'E': case 'e':
                    return 5;
            }
        }
        Sleep(100);
    }
}

void drawShopUI(addressChar *k, addressShopItem shop){
    // border atas dan bawah
    int lastWidth = 0, lastHeight = 0;
    int termWidth, termHeight;
    int shopMode = 0; // 0 = display mode, 1 = buying mode
    int selectedIndex = 0;
    
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
            int smallBoxWidth = (availableWidth - 6) / 4; // 6 = spacing antar kotak
            int smallBoxY = marginY + bigBoxHeight + 1 + 7;
            
            // Kotak 1
            drawBox(marginX + 1, smallBoxY, smallBoxWidth + 71, smallBoxHeight);
            
            // Kotak 4
            drawBox(marginX + 2 + (smallBoxWidth + 1) * 3, smallBoxY - 27, smallBoxWidth, smallBoxHeight + 27); 
            
            // Gambar box atas kanan (tempat nama shop) 
            drawBox(marginX + 2 + (smallBoxWidth + 1) * 3, smallBoxY - 27, smallBoxWidth, smallBoxHeight);
            
            //RENDER GAMBAR
            drawShopAt(marginX + 7 + (smallBoxWidth + 1) * 3, smallBoxY - 26);
            
            int xPotion[3] = {marginX + 10, marginX + 40, marginX + 70};
            int yPotion = 7;
            addressShopItem temp = shop;
            
            for (int i = 0; i < 3; i++) {
			    // 1. gambar tetap putih
			    setColor(7);
			    drawpotionAt(xPotion[i], yPotion);
			
			    // 2. lalu beri warna teks sesuai highlight
			    if (i == selectedIndex)setColor(14); // kuning
			    else setColor(7); // putih
			
			    gotoxy(xPotion[i] + 1, 25);
			    printf("%s (%d Gold)", temp->item, temp->price);
			
			    gotoxy(xPotion[i] + 10, 26);
			    printf("Stok: %d", temp->stock);
			
			    temp = temp->next;
			}
			setColor(7); // reset warna
            
			//====== RIGHT BAR TEXT =======       
            gotoxy(marginX + 13 + (smallBoxWidth + 1) * 3, smallBoxY - 20);
            printf("PILIHAN ITEM\n"); 
            
            tampilkanGold(k, 113, smallBoxY + 4);          
            tampilkanItem(shop);
            
            // Tambahkan instruksi kontrol
            gotoxy(marginX + 4, smallBoxY + 2);
            printf("Tekan 'B' untuk membeli");
            gotoxy(marginX + 4, smallBoxY + 3);
            printf("Atau gunakan < dan >");
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
            	case 75: 
        			if (selectedIndex > 0) selectedIndex--;
			        shopMode = 0; 
			        break;
			
			    case 77: 
			        if (selectedIndex < 2) selectedIndex++; 
			        shopMode = 0;
			        break;
            	case 13: 
				    {
				        addressShopItem selected = shop;
				        for (int i = 0; i < selectedIndex; i++) selected = selected->next;
				        pembelianItemShop(k, selected); 
				        clearInputArea();
    					shopMode = 0;
				    }
				    break;
                case 'b': case 'B':
                    pembelianItemShop(k, shop);
                    clearInputArea();
                    shopMode = 0; 
                    break;
                    
                case 'q': case 'Q':
                	clearScreen();
                    return; 
                    
                default:
                	gotoxy(113, 22);
                    Sleep(100);
                    clearInputArea();
                    break;
            }
        }
        Sleep(100); 
    }
}
