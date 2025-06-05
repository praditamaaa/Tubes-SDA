#ifndef NAVIGASI_H
#define NAVIGASI_H

#include "map.h"
#include "enemy.h"	// Setiap kali pengguna bergerak, akan ada kemungkinan untuk bertemu dengan musuh (menggunakan sistem randomize)
#include "shop.h"
#include "quest.h"

typedef enum{
	UP,
	RIGHT,
	DOWN,
	LEFT,
}Direction;

void movePlayer(Map *map, Direction dir);

#endif
