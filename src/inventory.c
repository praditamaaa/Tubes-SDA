#include "inventory.h"

void buatItem(addressItem *i){
	*i = (addressItem) malloc(sizeof(tItem));
}

void Isi_item(addressItem *i, char item[], int bag, ItemType type, Effect effect) {
    if (*i != NULL) {
        strcpy((*i)->item, item);
        (*i)->bag = bag; 
        (*i)->Type = type;
        (*i)->effect = effect;
        (*i)->next = NULL;
        (*i)->prev = NULL;
    }
}

void tambahItem(addressItem* head, addressItem iNew){
	if (*head == NULL) { 
        *head = iNew;
    } else {
        addressItem last = *head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = iNew;
        iNew->prev = last;
    }
}

void tampilkanInventory(addressItem head){
	if (head == NULL){
		printf("Inventory Masih Kosong.");
	}else{
		printf("Daftar Item dalam Inventory\n");
		addressItem curr = head;
		int i = 1;
		while (curr != NULL){
			printf("%d. %s (tersisa %d)\n", i, curr->item, curr->bag);
			curr = curr->next;
			i++;
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

void pilihItem(addressItem *head) {
    tampilkanInventory(*head);
    if (*head == NULL) return;

    printf("\nPilih item yang ingin digunakan\n");
    printf("Ketik nama atau nomor item: ");

    char input[50];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    addressItem curr = *head;

    if (isNumber(input)) {
        int nomor = atoi(input);
        int x = 1;
        curr = *head;
        while (curr != NULL && x < nomor) {
            curr = curr->next;
            x++;
        }

        if (curr == NULL) {
            printf("Nomor item tidak ditemukan.\n");
            return;
        }
    } else {
        while (curr != NULL && strcmp(curr->item, input) != 0) {
            curr = curr->next;
        }

        if (curr == NULL) {
            printf("Item dengan nama '%s' tidak ditemukan.\n", input);
            return;
        }
    }

    printf("Menggunakan item: %s\n", curr->item);
    curr->bag--;

    if (curr->bag == 0) {
        hapusItem(head, curr);
    }
}

void hapusItem(addressItem* head, addressItem curr){
	printf("Item '%s' habis dan dihapus dari inventory.\n", curr->item);

    if (curr->prev != NULL) {
            curr->prev->next = curr->next;
        } else {
            *head = curr->next; 
        }

        if (curr->next != NULL) {
            curr->next->prev = curr->prev;
        }

    free(curr);
}
