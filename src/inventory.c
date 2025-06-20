/*
.| Program : inventory.c
.| Berisi logika atau isi modul dari data header shop.h
.|
.| Tujuan : Membuat item yang akan dijual di shop dan bisa 
.|		dibeli oleh user yang kemudian disimpan 
.|		di inventory untuk dapat digunakan di combat
.|		di permainan.
.| 
.| Oleh : Afriza Choirie Saputra
*/

#include "inventory.h"

void Isi_item(tItem *item, char nama[], int bag, ItemType type, Effect effect) {
    strcpy(item->item, nama);
    item->bag = bag;
    item->Type = type;
    item->effect = effect;
}

void tambahItem(Inventory* inv, tItem item) {
    int i = 0;

    // Cek apakah item sudah ada
    while (i < inv->count) {
        if (strcmp(inv->items[i].item, item.item) == 0 &&
            inv->items[i].Type == item.Type &&
            memcmp(&inv->items[i].effect, &item.effect, sizeof(Effect)) == 0) {
            
            inv->items[i].bag += item.bag;
            return;
        }
        i++;
    }

    // Jika belum ada, tambahkan baru
    if (inv->count < MAX_INVENTORY) {
        inv->items[inv->count++] = item;
    } else {
        printf("Inventory penuh!\n");
    }
}

void tampilkanInventory(Inventory *inv, int x, int y) {
    if (inv->count == 0) {
        gotoxy(x, y);
        printf("Inventory Masih Kosong.");
    } else {
        for (int i = 0; i < inv->count; i++) {
            gotoxy(x, y + i);
            printf("%d. %s (%d)", i + 1, inv->items[i].item, inv->items[i].bag);
        }
    }
}

int isNumber(const char *str) {
	int i = 0;
	while(str[i] != '\0'){
		if (!isdigit(str[i])) return 0;
		i++;
	}
    return 1;
}

tItem* pilihItem(Inventory *inv) {
    if (inv->count == 0) {
        gotoxy(6, 22);
        printf("Inventory masih kosong");
        return NULL;
    }

    gotoxy(6, 22);
    printf("Pilih item yang ingin digunakan");
    gotoxy(6, 23);
    printf("Ketik nama atau nomor item: ");
    
    gotoxy(33, 23);
    char input[50];
    fgets(input, sizeof(input), stdin);
    
    // Hapus newline dari fgets
    input[strcspn(input, "\n")] = '\0';

    int index = -1;

    if (isNumber(input)) {
        int nomor = atoi(input);
        if (nomor >= 1 && nomor <= inv->count) {
            index = nomor - 1;
        }
    } else {
        for (int i = 0; i < inv->count; i++) {
            if (strcmp(inv->items[i].item, input) == 0) {
                index = i;
                break;
            }
        }
    }

    if (index == -1) {
        gotoxy(6, 27);
        printf("Item tidak ditemukan.\n");
        Sleep(1500);
        return NULL;
    }

    return &inv->items[index];
}


void hapusItem(Inventory *inv, int index) {
    for (int i = index; i < inv->count - 1; i++) {
        inv->items[i] = inv->items[i + 1];
    }
    inv->count--;
}
