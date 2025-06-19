#include "shop.h"

void buatShopItem(addressShopItem* i) {
    *i = (addressShopItem) malloc(sizeof(tIshop));
}

void isiShopItem(addressShopItem* i, char item[], int stock, int price, ItemType type, Effect effect) {
    if (*i != NULL) {
        strcpy((*i)->item, item);
        (*i)->stock = stock;
        (*i)->price = price;
        (*i)->Type = type;
        (*i)->effect = effect;
        (*i)->next = NULL;
        (*i)->prev = NULL;
    }
}

void tambahItemShop(addressShopItem* head, addressShopItem newItem) {
    if (*head == NULL) {
        *head = newItem;
    } else {
        addressShopItem last = *head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newItem;
        newItem->prev = last;
    }
}
	
void inisialisasiShop(addressShopItem* shop) {
    addressShopItem item1, item2, item3;

    buatShopItem(&item1);
    Effect e1 = {.heal.amount = 50};
    isiShopItem(&item1, "Healing Potion", 5, 25, HealPotion, e1);
    tambahItemShop(shop, item1);

    buatShopItem(&item2);
    Effect e2 = {.status = {STATUS_BURN, 15, 3}};
    isiShopItem(&item2, "Fire Potion", 4, 45, BurnPotion, e2);
    tambahItemShop(shop, item2);

    buatShopItem(&item3);
    Effect e3 = {.status = {STATUS_FREEZE, 10, 2}};
    isiShopItem(&item3, "Ice Potion", 3, 50, FreezePotion, e3);
    tambahItemShop(shop, item3);
}


void tampilkanItem(addressShopItem shop) {
    int i = 1;
    int Xawal = 113;
    int Yawal = 10;
    while (shop != NULL) {
        gotoxy(Xawal, Yawal + i - 1);
        printf("%d. %s (Stok: %d)", i, shop->item, shop->stock);
        i++;
        shop = shop->next;
    }
}


addressShopItem pilihItemShop(addressShopItem shop, int nomor) {
    int i = 1;
    while (shop != NULL && i < nomor) {
        shop = shop->next;
        i++;
    }
    return shop;
}

void tambahkanItemKeInventoryKarakter(addressChar karakter, addressShopItem shop, int jumlahDibeli){
    tItem newItem;
    Isi_item(&newItem, shop->item, jumlahDibeli, shop->Type, shop->effect);
    tambahItem(&(karakter->inventory), newItem);
}


void tampilkanGold(addressChar* karakter, int x, int y) {
    gotoxy(x, y);
    printf("Gold Anda: %d", (*karakter)->Gold);
}

int hitungTotalHarga(addressShopItem shop, int jumlah) {
    return shop->price * jumlah;
}


int prosesPembayaran(addressChar* karakter, int totalHarga) {
    if ((*karakter)->Gold >= totalHarga) {
        (*karakter)->Gold -= totalHarga;
        return 1;
    }
    return 0; 
}

int inputJumlahItem(){
    int jumlahDibeli;
    gotoxy(113, 21); 
    printf("Masukkan jumlah: ");
    scanf("%d", &jumlahDibeli);
    return jumlahDibeli;
}

void pembelianItemShop(addressChar* karakter, addressShopItem itemDipilih) {
    if (itemDipilih == NULL) {
        gotoxy(113, 22);
        printf("Pilihan tidak valid!        ");
        Sleep(2000);
        return;
    }

    if (itemDipilih->stock == 0) {
        gotoxy(113, 22);
        printf("Stok item habis!           ");
        Sleep(2000);
        return;
    }
    int jumlahDibeli = inputJumlahItem();
    if (jumlahDibeli < 1 || jumlahDibeli > itemDipilih->stock) {
        gotoxy(113, 22);
        printf("Jumlah tidak valid! (Max: %d)", itemDipilih->stock);
        Sleep(2000);
        return;
    }

    int totalHarga = hitungTotalHarga(itemDipilih, jumlahDibeli);
    gotoxy(113, 22);
    printf("Total Harga: %d Gold       ", totalHarga);
    Sleep(1000);

    gotoxy(113, 23);
    printf("Lanjutkan? (Y/N): ");
    char konfirmasi;
    scanf(" %c", &konfirmasi);

    if (konfirmasi != 'Y' && konfirmasi != 'y') {
        gotoxy(113, 24);
        printf("Pembelian dibatalkan.      ");
        Sleep(2000);
        return;
    }

    if (!prosesPembayaran(karakter, totalHarga)) {
        gotoxy(113, 24);
        printf("Gold tidak cukup! Butuh %d Gold", totalHarga);
        Sleep(2000);
        return;
    }

    gotoxy(113, 24);
    printf("Berhasil");
    gotoxy(113, 25);
    printf("membeli %dx %s!", jumlahDibeli, itemDipilih->item);

    itemDipilih->stock -= jumlahDibeli;
    tambahkanItemKeInventoryKarakter(*karakter, itemDipilih, jumlahDibeli);
    Sleep(2000);
}
