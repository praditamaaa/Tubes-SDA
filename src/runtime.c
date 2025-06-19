#include "runtime.h"

int getTotalKill(runTimeStats* stats) {
    int i; 
	int total = 0;
    for (i = 0; i < MAX_ENEMY_TYPE; i++) {
        total += stats->killCountPerType[i];
    }
    return total;
}
