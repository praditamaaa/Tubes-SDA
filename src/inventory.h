#ifndef inventory_h
#define inventory_h
#include "common.h"

void buatItem(addressItem *i);
void Isi_item(addressItem *i, char item[], int bag, ItemType type, Effect effect);
void tambahItem(addressItem* i, addressItem iNew);
void tampilkanInventory(addressItem head);
int isNumber(const char *str);
void pilihItem(addressItem *head);
void hapusItem(addressItem* head, addressItem curr);

#endif
