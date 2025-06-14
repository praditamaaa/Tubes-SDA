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

#define ITEM 7

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
    SPBoost,
    AttackUp,
    DefenseUp,
    StunItem,
    ExtraTurnBoots,
    SplashPoison
} ItemType;

typedef struct {
    int amount;
} EffectHeal;

typedef struct {
    int amount;
} EffectSP;

typedef struct {
    int amount;
} EffectAttack;

typedef struct {
    int amount;
} EffectDefense;

typedef struct {
    int duration;
} EffectStun;

typedef struct {
    int turns;
} EffectExtraTurn;

typedef struct {
    int active;
} EffectPoison;

typedef struct {
    EffectHeal heal;
    EffectSP sp;
    EffectAttack attack;
    EffectDefense defense;
    EffectStun stun;
    EffectExtraTurn extraTurn;
    EffectPoison burn;
}Effect;


typedef struct tItem {
    infotype item;
    int bag; 
    ItemType Type;
    Effect effect;
    addressItem next;
    addressItem prev;
} tItem;

#endif

