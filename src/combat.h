#ifndef COMBAT_H
#define COMBAT_H

#include "user.h"
#include "enemy.h"

typedef enum{
	STATUS_BURN,
	STATUS_FREEZE
}StatusType;

typedef struct{
	StatusType effect;
	int damage;
	int duration;
}StatusEffect;

typedef struct{
	StatusType effect;
	struct EffectNode* next;
}EffectNode;

typedef struct{
	EffectNode *first;
	EffectNode *last;
}EffectQueue;

/* MODUL YANG BERPERAN UNTUK MEKANISME PERTARUNGAN */
/* Kalkulasi stats akan dimasukkan sekalian di dalam setiap modul terkait */
void doAttack(User *user, Enemy *enemy);
void doDefense(User *user, Enemy *enemy);
void useSkill(User *user, Enemy *enemy);
void useItem(User *user, Enemy *enemy);
void doEscape(User *player);

void enemyAttack(Enemy *enemy, User *user);
void enemyDefense(Enemy *enemy, User *user);
void enemySkill(Enemy *enemy, User *user);



/* MODUL YANG BERPERAN UNTUK MEKANISME STATUS EFEK */
void enqueue(EffectQueue *List, StatusType type)
void updateEffect(EffectQueue *List, int *targetHP)

#endif
