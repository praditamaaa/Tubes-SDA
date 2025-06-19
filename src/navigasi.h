#ifndef NAVIGASI_H
#define NAVIGASI_H

#include "User.h"
#include "common.h"
#include "map.h"
#include "shop.h"
#include "enemy.h"	// Setiap kali pengguna bergerak, akan ada kemungkinan untuk bertemu dengan musuh (menggunakan sistem randomize)

void movePlayer(Map *map, Direction dir, addressChar* k, addressShopItem shop[], addressUser loggedUser);
bool checkEncounter();

#endif
