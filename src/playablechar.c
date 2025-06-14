#include "playablechar.h"

void inputCharUser(addressChar* k) {
	int pilihan;
	printCenteredAtRow("Pilih Tipe Karakter", 13);
	printCenteredAtRow("#===================================================================================================#", 14);
	printCenteredAtRow("| 1. Warrior                                                                                        |", 15);
	printCenteredAtRow("| 2. Mage                                                                                           |", 16);
	printCenteredAtRow("| 3. Defender                                                                                       |", 17);
	printCenteredAtRow("#===================================================================================================#", 18);
	printCenteredAtRow("Pilihan:", 19);
	scanf("%d", &pilihan);
	getchar(); 
	pilihKarakter(k, pilihan);
}

void pilihKarakter(addressChar* k, int input){
    if (*k != NULL) {
        return; 
    }

    int pilihan = input; 
    switch (pilihan) {
        case 1:
            karakterA(k);
            break;
        case 2:
            karakterM(k);
            break;
        case 3:
            karakterD(k);
            break;
        default:
            printf("Pilihan tidak valid\n");
            break;
    }
}

void karakterA(addressChar* k){
	*k = (addressChar) malloc(sizeof(tChar));
	int Hp = 150;
	int Att = 10;
	int Def = 8;
	int Lvl = 1;
	Isi_Stat(k, &Hp, &Att, &Def, &Lvl);
}

void karakterM(addressChar* k){
	*k = (addressChar) malloc(sizeof(tChar));
	int Hp = 100;
	int Att = 15;
	int Def = 5;
	int Lvl = 1;
	Isi_Stat(k, &Hp, &Att, &Def, &Lvl);
}

void karakterD(addressChar* k){
	*k = (addressChar) malloc(sizeof(tChar));
	int Hp = 180;
	int Att = 7;
	int Def = 12;
	int Lvl = 1;
	Isi_Stat(k, &Hp, &Att, &Def, &Lvl);
}

void Isi_Stat(addressChar* k, int *Hp, int *Att,int *Def,int *Lvl) {
    if (*k != NULL) {
    	(*k)->Hp = *Hp;
        (*k)->Att = *Att;
	    (*k)->Def = *Def;
	    (*k)->Lvl = *Lvl;
	    (*k)->isDefending = DEFAULT;
	    (*k)->skillChar = NULL;
	    (*k)->inventory = NULL;
    }
}

void tambahItemKeKarakter(addressChar* karakter, addressItem* I){
    addressItem baru;
    buatItem(&baru);
    Isi_item(&baru, (*I)->item, (*I)->bag, (*I)->Type, (*I)->effect);
    tambahItem(&((*karakter)->inventory), baru);
}

void tampilkanInventoryKarakter(addressChar karakter) {
    tampilkanInventory(karakter->inventory);
}

void pilihItemKarakter(addressChar karakter) {
    pilihItem(&karakter->inventory); 
}
