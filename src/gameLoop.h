#ifndef gameloop_h
#define gameloop_h
#include "playablechar.h"
#include "combat.h"
#include "common.h"
#include "display.h"

void combatLoop(addressChar player, Enemy *enemy);
void gameLoop();
void pauseGame();
void exitGame(int *running);

#endif

