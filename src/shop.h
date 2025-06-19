/*
.| Program : skilltree_builder.h
.| Header yang berisikan modul untuk membuat dan membeli item di shop
.| dengan data dari playablechar dan common
.|
.| Oleh : Afriza Choirie Saputra
*/

#ifndef shop_h
#define shop_h
#include "playablechar.h"
#include "common.h"

typedef struct tIshop* addressShopItem;

typedef struct tIshop {
    ItemType Type;
    infotype item;
    Effect effect;
    int stock;
    int price;
    addressShopItem next;
    addressShopItem prev;
} tIshop;

void buatShopItem(addressShopItem* i);
void isiShopItem(addressShopItem* i, char item[], int stock, int price, ItemType type, Effect effect);
void tambahItemShop(addressShopItem* head, addressShopItem newItem);
void inisialisasiShop(addressShopItem* shop);
void tampilkanItem(addressShopItem shop);
addressShopItem pilihItemShop(addressShopItem shop, int nomor);
void tambahkanItemKeInventoryKarakter(addressChar karakter, addressShopItem shop, int jumlahDibeli);
void tampilkanGold(addressChar* karakter, int x, int y);
int hitungTotalHarga(addressShopItem shop, int jumlah);
int prosesPembayaran(addressChar* karakter, int totalHarga);
int inputUser();
int inputJumlahItem();
void pembelianItemShop(addressChar* karakter, addressShopItem shop);

#endif
