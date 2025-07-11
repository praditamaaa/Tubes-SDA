/*
.| Program : inventory.h
.| Header yang berisikan modul untuk kelola item player
.| dengan data dari common.h
.|
.| Oleh : Afriza Choirie Saputra
*/

#ifndef inventory_h
#define inventory_h
#include "common.h"

#define MAX_INVENTORY 20

typedef struct {
    tItem items[MAX_INVENTORY];
    int count;
} Inventory;

void buatItem(addressItem *i);
void Isi_item(tItem *item, char nama[], int bag, ItemType type, Effect effect);
void tambahItem(Inventory* inv, tItem item);
void tampilkanInventory(Inventory *inv, int x, int y);
int isNumber(const char *str);
tItem* pilihItem(Inventory *inv);
void hapusItem(Inventory *inv, int index);

#endif
