#include "gmenu.h"

void menuUser(addressChar* k) {
	int pilihan;
	printCenteredAtRow("Mythora Turn Based RPG", 13);
	printCenteredAtRow("#===================================================================================================#", 14);
	printCenteredAtRow("| 1. New Game                                                                                       |", 15);
	printCenteredAtRow("| 2. Load Game                                                                                      |", 16);
	printCenteredAtRow("| 3. Exit                                                                                           |", 17);
	printCenteredAtRow("#===================================================================================================#", 18);
	printCenteredAtRow("Pilihan:", 19);
	scanf("%d", &pilihan);
	getchar(); 
	pilihMenu(pilihan, k);
}

void pilihMenu(int pilihan, addressChar* k){
    switch (pilihan) {
        case 1:
            inputCharUser(k);
            break;
        case 2: 
            printf("Buat lanjut progress");
            break;
        case 3:
            break;
        default:
            printf("Pilihan tidak valid\n");
            break;
    }
}

