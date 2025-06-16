#ifndef DISPLAY_H
#define DISPLAY_H
#include "common.h"
#include "enemy.h"
#include "input.h"
#include "map.h"
#include "shop.h"
#include "navigasi.h"
#include "playablechar.h"
#include "figure.h"

void drawBorder();
void drawMap(const Map *map);
void drawUI(const Map *map, addressChar karakter);
void drawBox(int startX, int startY, int width, int height);
void drawCombatUi(addressChar *k, Enemy *enemy);
void drawShopUI(addressChar *k, addressShopItem shop[]);
void gameLoop(Map *map, addressChar k, addressShopItem shop[]);

#endif

