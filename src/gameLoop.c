#include "gameLoop.h"
void combatLoop(addressChar player, Enemy *enemy) {
    EffectQueue enemyEffectQueue = {NULL, NULL}; 
    
    while (player->Hp > 0 && enemy->Hp > 0) {
        updateEffect(&enemyEffectQueue, &enemy->Hp);

        if (enemy->Hp <= 0) break;
        
        // GILIRAN PLAYER
        int action = drawCombatUi(&player, enemy);
        switch (action) {
            case 1: doPlayerAttack(player, enemy); break;
            case 2: usePlayerSkill(player, enemy); break;
            case 3: doPlayerDefense(player); break;
            case 4: pakeItem(player, enemy, &enemyEffectQueue); break;
            case 5:
                if (doPlayerEscape()) return;
                break;
        }
        
        if (enemy->Hp <= 0) break;

        Sleep(500);

        // CEK KALO musuh beku
        if (enemyEffectQueue.first != NULL &&
            enemyEffectQueue.first->effect.type == STATUS_FREEZE) {
            printf("Musuh membeku dan tidak bisa menyerang!\n");
            Sleep(1000);
            continue;
        }

        // Giliran Musuh
        int enemyAction = rand() % 3;
        switch (enemyAction) {
            case 0: EnemyAttack(enemy, player); break;
            case 1: EnemyDefense(enemy); break;
            case 2: EnemySkill(enemy, player); break;
        }

        Sleep(1000);

        // Cek kekalahan
        if (player->Hp <= 0) {
            free(player);
            clearScreen();
            
            gotoxy(65,16);
            printf("DEFEAT...");
            getch();
            exit(0);
            clearScreen();
            
        } else if (enemy->Hp <= 0) {
            clearScreen();
            
            int exp = 50 + (enemy->Lv * 5);
            int gold = 40 + (enemy->Lv * 5);
            player->Exp += exp;
            player->Gold += gold;
            
            gotoxy(65, 16);
            printf("VICTORY\n");
            
            gotoxy(60, 17);
            printf("Kamu mendapatkan %d EXP dan %d Gold!\n", exp, gold);
        
            gotoxy(60, 18);
            printf("Total EXP: %d | Level: %d\n", player->Exp, player->Lvl);
            
            levelUp(player);
            
            Sleep(2000);
            return;
        }
    }
}

void handleInput(Map *map, addressChar *k, addressShopItem shop[], char key, int *running) {
    switch (key) {
        case 'w': case 'W': case 72: 
            movePlayer(map, UP, k, shop);
            break;
        case 's': case 'S': case 80:
            movePlayer(map, DOWN, k, shop);
            break;
        case 'a': case 'A': case 75: 
            movePlayer(map, LEFT, k, shop);
            break;
        case 'd': case 'D': case 77: 
            movePlayer(map, RIGHT, k, shop);
            break;
        case 'z': case 'Z':
            clearScreen();
            pilihItemKarakter(*k);
            // Refresh tampilan setelah keluar dari inventory
            clearScreen();
            hideCursor();
            drawBorder();
            drawMap(map);
            drawUI(map, *k);
            break;
        case 't': case 'T':  // TOMBOL T UNTUK INVENTORY
            clearScreen();
            pilihItemKarakter(*k);
            // Refresh tampilan setelah keluar dari inventory
            clearScreen();
            hideCursor();
            drawBorder();
            drawMap(map);
            drawUI(map, *k);
            break;
        case 27:  // ESC - Pause game
            pauseGame();
            break;
        case 'q': case 'Q':  // Quit game
            exitGame(running);
            break;
    }
}

// Fungsi untuk pause game
void pauseGame() {
    gotoxy(30, HEIGHT + 6);
    setColor(12);
    printf("Game paused. Press any key to continue...           ");
    getch();
    gotoxy(30, HEIGHT + 6);
    printf("                                                    ");
    setColor(15); // Reset color
}

// Fungsi untuk exit game
void exitGame(int *running) {
    gotoxy(30, HEIGHT + 6);
    setColor(14); // Yellow
    printf("Are you sure you want to quit? (Y/N):               ");
    char confirm = getch();
    
    if (confirm == 'y' || confirm == 'Y') {
        *running = 0;
        gotoxy(30, HEIGHT + 6);
        setColor(10); // Green
        printf("Thank you for playing! Goodbye!                     ");
        Sleep(1000);
    } else {
        // Clear the quit message
        gotoxy(30, HEIGHT + 6);
        printf("                                                    ");
    }
    setColor(15); // Reset color
}

// Fungsi untuk mengecek apakah perlu redraw
int needsRedraw(char key) {
    return (key == 'w' || key == 'W' || key == 72 ||
            key == 's' || key == 'S' || key == 80 ||
            key == 'a' || key == 'A' || key == 75 ||
            key == 'd' || key == 'D' || key == 77);
}

void gameLoop() {
    int running = 1;
    char key;

    // Inisialisasi semua komponen
    srand(time(NULL));
    Map gameMap;
    addressChar player = NULL;
    addressShopItem shop = NULL;

    inisialisasiShop(&shop);
    hideCursor();
    clearScreen();
    initMap(&gameMap);

    // Welcome screen dan pemilihan karakter
    welcomeScreen(); 

    int pilihan = inputCharUser();
    pilihKarakter(&player, pilihan);

    // Setup awal tampilan
    clearScreen();
    drawBorder();
    drawMap(&gameMap);
    drawUI(&gameMap, player);

    // Main game loop
    while (running) {
        if (_kbhit()) {
            key = getInput();

            if (!isValidInput(key)) continue;

            handleInput(&gameMap, &player, &shop, key, &running);

            if (needsRedraw(key)) {
                drawBorder();
                drawMap(&gameMap);
                drawUI(&gameMap, player);
            } else if (key != 'z' && key != 'Z' && key != 't' && key != 'T') {
                drawBorder();
            }
        } else {
            drawBorder();
        }

        Sleep(50);
    }

    if (player != NULL) free(player);
}
