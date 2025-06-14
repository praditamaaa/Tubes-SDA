#ifndef playablechar_h
#define playablechar_h
#include "common.h"
#include "inventory.h"
#include "welcomesc.h"
#include "skilltree.h"

#define DEFAULT 0

typedef struct tChar{
	int Hp;
	int Att;
	int Def;
	int Lvl;
	int isDefending;
	Skilltree skillChar;
	addressItem inventory;
}tChar;

void inputCharUser(addressChar* k);
void pilihKarakter(addressChar* k, int pilihan);
void karakterA(addressChar* k);
void karakterM(addressChar* k);
void karakterD(addressChar* k);
void Isi_Stat(addressChar* k, int *Hp, int *Att,int *Def,int *Lvl);
void tambahItemKeKarakter(addressChar* karakter, addressItem* I);
void tampilkanInventoryKarakter(addressChar karakter);
void pilihItemKarakter(addressChar karakter);
void upgradeStat(addressChar k);

#endif
