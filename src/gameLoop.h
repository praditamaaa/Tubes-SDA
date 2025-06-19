#ifndef gameloop_h
#define gameloop_h
#include "display.h"
#include "playablechar.h"
#include "combat.h"
#include "common.h"

void combatLoop(addressChar player, Enemy *enemy);
void gameLoop();
void pauseGame();
void exitGame(int *running);

#endif

