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
    	printf("inventory masih kosong");
        return 0;
    }
    
    gotoxy(6, 23);
    printf("Pilih item yang ingin digunakan");
    gotoxy(6, 24);
    printf("Ketik nama atau nomor item: ");

    // Bersihkan stdin buffer
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

	gotoxy(57, HEIGHT + 10);
    char input[50];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // hapus newline dari fgets

    int index = -1;

    // Cek apakah input berupa angka
    if (isNumber(input)) {
        int nomor = atoi(input);
        if (nomor >= 1 && nomor <= inv->count) {
            index = nomor - 1;
        }
    } else {
        // Cocokkan dengan nama item
        for (int i = 0; i < inv->count; i++) {
            if (strcmp(inv->items[i].item, input) == 0) {
                index = i;
                break;
            }
        }
    }

    if (index == -1) {
        printf("Item tidak ditemukan.\n");
        Sleep(1500);
        return NULL;
    }

    return &inv->items[index];
}

void hapusItem(Inventory *inv, int index) {
    printf("Item '%s' habis dan dihapus dari inventory.\n", inv->items[index].item);
    for (int i = index; i < inv->count - 1; i++) {
        inv->items[i] = inv->items[i + 1];
    }
    inv->count--;
}
