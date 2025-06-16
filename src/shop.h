#ifndef shop_h
#define shop_h
#include "playablechar.h"
#include "common.h"

typedef struct tIshop addressShopItem;

typedef struct tIshop {
    ItemType Type;          // Changed from Type to type (lowercase)
    infotype item;
    Effect effect;
    int stock;
    int price;              // Added price field
} tIshop;

void tambahkanItem(addressShopItem shop[]);
void tampilkanItem(addressShopItem shop[]);
void pakaiItem(addressShopItem i);
void tambahkanItemKeInventoryKarakter(addressChar* karakter, addressShopItem shop, int jumlahDibeli);
int inputUser();
int inputJumlahItem();
void pembelianItemShop(addressChar* karakter, addressShopItem shop[]);

#endif
