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
#include "User.h"

void menuUser(addressUser* userList, addressUser* loggedUser);
void welcomeScreen(addressUser* loggedUser);
void tampilkanASCII();
void inputNama();
void newGameChoice(addressUser* userList, addressUser* loggedUser);
void loadGameChoice(addressUser* userList, addressUser* loggedUser);

void drawBorder();
void drawMap(const Map *map);
void drawUI(const Map *map, addressChar karakter);
void drawBox(int startX, int startY, int width, int height);
int drawCombatUi(addressChar *k, Enemy *enemy);
void drawShopUI(addressChar *k, addressShopItem shop);

#endif
