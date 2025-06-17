#include "inventory.h"

void Isi_item(tItem *item, char nama[], int bag, ItemType type, Effect effect) {
    strcpy(item->item, nama);
    item->bag = bag;
    item->Type = type;
    item->effect = effect;
}

void tambahItem(Inventory* inv, tItem item) {
    if (inv->count < MAX_INVENTORY) {
        inv->items[inv->count++] = item;
    } else {
        printf("Inventory penuh!\n");
    }
}


void tampilkanInventory(Inventory *inv) {
    if (inv->count == 0) {
        printf("Inventory Masih Kosong.\n");
    } else {
        printf("Daftar Item dalam Inventory\n");
        for (int i = 0; i < inv->count; i++) {
            printf("%d. %s (tersisa %d)\n", i + 1, inv->items[i].item, inv->items[i].bag);
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

void pilihItem(Inventory *inv) {
    tampilkanInventory(inv);
    if (inv->count == 0) return;

    printf("\nPilih item yang ingin digunakan\n");
    printf("Ketik nama atau nomor item: ");

    char input[50];
    fgets(input, sizeof(input), stdin);
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
        printf("Item tidak ditemukan.\n");
        return;
    }

    printf("Menggunakan item: %s\n", inv->items[index].item);
    inv->items[index].bag--;

    if (inv->items[index].bag == 0) {
        hapusItem(inv, index);
    }
}

void hapusItem(Inventory *inv, int index) {
    printf("Item '%s' habis dan dihapus dari inventory.\n", inv->items[index].item);
    for (int i = index; i < inv->count - 1; i++) {
        inv->items[i] = inv->items[i + 1];
    }
    inv->count--;
}
