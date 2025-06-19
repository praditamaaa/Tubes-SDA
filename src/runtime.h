#ifndef RUNTIME_H
#define RUNTIME_H

/*
	file: runtime.h
	desc: Meniympan statistik runtime character, untuk progress quest
	Made by: Praditama Ajmal Hasan
*/

#define MAX_ENEMY_TYPE 3

typedef struct RuntimeStats {
    int killCountPerType[MAX_ENEMY_TYPE];
    int totalEscape;
    int completedQuests;
} runTimeStats;

int getTotalKill(runTimeStats* stats);

#endif
