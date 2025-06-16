#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

//kebutuhan border layar
#define WHITE_BG "\033[47m"  
#define RESET    "\033[0m"   

// dimensi layar (ukuran camera)
#define WIDTH 60
#define HEIGHT 20

// dimensi dunia (ukuran rill mapnya) Increased map size for camera system
#define WORLD_WIDTH 100
#define WORLD_HEIGHT 100

#define ITEM 3

typedef char infotype[100];

typedef struct tItem* addressItem;
typedef struct tChar* addressChar;

typedef enum{
	UP,
	RIGHT,
	DOWN,
	LEFT,
}Direction;

typedef enum {
    HealPotion,
    BurnPotion,     
    FreezePotion
} ItemType;

typedef enum{
	STATUS_BURN,
	STATUS_FREEZE
}StatusType;

typedef struct {
    int amount;
} EffectHeal;

typedef struct{
	StatusType type;
	int damage;
	int duration;
}StatusEffect;

typedef struct {
    EffectHeal heal;
    StatusEffect status;
}Effect;

typedef struct tItem {
    infotype item;
    int bag; 
    ItemType Type;
    Effect effect;
    addressItem next;
    addressItem prev;
} tItem;

void clearScreen();
void gotoxy(int x, int y);
void setColor(int color);
void hideCursor();
void getTerminalSize(int *width, int *height);
void printCenteredAtRow(const char* text, int row);
void clearInputArea();

#endif
