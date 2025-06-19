#ifndef QUEST_H
#define QUEST_H

/*
	File: quest.h
	desc: Mengurus segala keperluan untuk fitur quest
	Made by: Praditama Ajmal Hasan
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "runtime.h"
#include "common.h"	

typedef enum {
    QUEST_REACH_LEVEL,
    QUEST_KILL_ENEMY_TOTAL,
    QUEST_KILL_ENEMY_TYPE,
    QUEST_COLLECT_SCORE,
    QUEST_ESCAPE_BATTLE,
    QUEST_REACH_ATTACK,
    QUEST_REACH_HP,
    QUEST_REACH_DEF,
    QUEST_REACH_GOLD,
    QUEST_TOTAL_QUEST_COMPLETED,
} QuestType;

typedef struct Quest* addressQuest;
typedef struct Quest {
    int id;
    QuestType type;
    char description[100];
    int target;
    int progress;
    bool completed;
    int rewardGold;
	int rewardExp;
	int rewardAtt;
	int rewardDef;
    struct Quest* next;
    struct Quest* prev;
} Tquest;

//==========================================MODUL-MODUL=========================================//

addressQuest createQuest(int id, QuestType type, const char* desc, int target);
void addQuest(addressQuest* head, addressQuest newQuest);
void removeQuest(addressQuest* head, int id);
void showAllQuests(addressQuest head);
void updateQuests(addressQuest head, addressChar k, runTimeStats* stats);
void giveQuestReward(addressChar k, addressQuest quest);
void claimQuestReward(addressUser user, int questId);

#endif
