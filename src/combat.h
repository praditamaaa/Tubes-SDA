#ifndef COMBAT_H
#define COMBAT_H

#include "playablechar.h"
#include "enemy.h"
#include "common.h"
#include "display.h"

typedef struct EffectNode {
    StatusEffect effect;
    struct EffectNode* next;
} EffectNode;

typedef struct{
	EffectNode *first;
	EffectNode *last;
}EffectQueue;


/* MODUL YANG BERPERAN UNTUK MEKANISME PERTARUNGAN */
/* Kalkulasi stats akan dimasukkan sekalian di dalam setiap modul terkait */
void doPlayerAttack(addressChar player, Enemy *enemy);
void doPlayerDefense(addressChar player);
void usePlayerSkill(addressChar player, Enemy *enemy);
void pakeItem(addressChar karakter, Enemy *enemy, EffectQueue *queue);
bool doPlayerEscape();

void EnemyAttack(Enemy *enemy, addressChar player);
void EnemyDefense(Enemy *enemy);
void EnemySkill(Enemy *enemy, addressChar player);

/* MODUL YANG BERPERAN UNTUK MEKANISME STATUS EFEK */
void enqueue(EffectQueue *List, StatusEffect effect);
void updateEffect(EffectQueue *List, int *targetHP);

#endif
