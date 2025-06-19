#ifndef ENEMY_H
#define ENEMY_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "playablechar.h"
#include "common.h"

// #include "user.h" / #include "shape.h"
// Mengimplementasikan header user/pemain atau shape/karakter
// untu menentukan level musuh (Berada di rentang 10 Lv dengan user)

typedef enum{
	SLIME,
	WOLF,
	GOBLIN,
}EnemyType;

typedef enum{
	SKILL_ATTACK,
	SKILL_DEFENSE,
	SKILL_HEAL,
}SkillType;

typedef struct{
	char *name;
	SkillType type;
	int power; 		// Raw Attack
	float scale;
}Skill;

typedef struct{
	int value;
	int duration;
}Buff;

typedef struct{
	EnemyType Type;
	int Lv;
	int Hp;
	int Att;
	int Def;
	int isDefending;	// Default value adalah 0 (TIDAK), dan 1 (DEFENDING)
	Buff DefBuff;
	Skill skills[3];
}Enemy;

void initEnemy(Enemy *enemy, EnemyType Type, addressChar player);
Skill createSkill(const char *name, SkillType type, int power, float scale);
int getEnemyHP(const Enemy *enemy);
int getEnemyAtt(const Enemy *enemy);
int getEnemyDef(const Enemy *enemy);
int encounter();

#endif
