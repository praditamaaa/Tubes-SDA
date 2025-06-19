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

void menuUser(addressUser user);
void pilihMenu(int pilihan);
void welcomeScreen(addressUser user);
void tampilkanASCII();
void inputNama();

void drawBorder();
void drawMap(const Map *map);
void drawUI(const Map *map, addressChar karakter);
void drawBox(int startX, int startY, int width, int height);
int drawCombatUi(addressChar *k, Enemy *enemy);
void drawShopUI(addressChar *k, addressShopItem shop);

#endif
