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
void tampilkanInventory(Inventory *inv); 
int isNumber(const char *str);
void pilihItem(Inventory *inv);
void hapusItem(Inventory *inv, int index);

#endif
