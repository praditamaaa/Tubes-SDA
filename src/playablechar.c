/*
.| Program : playablechar.c
.| Berisi logika atau isi modul dari data header playablechar.h 
.|
.| Tujuan : Membuat karakter yang bisa digunakan oleh user 
.|			dengan atributnya masing - masing
.| 
.| Oleh : Afriza Choirie Saputra
*/


#include "playablechar.h"

int inputCharUser() {
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
	return pilihan;
}

void pilihKarakter(addressChar* k, int input){
    if (*k != NULL) {
        return; 
    }

    switch (input) {
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
    if (*k == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    const char* nama = "Warrior";
    int Hp = 1500; //150
    int Exp = 0;
    int Gold = 0;
    int Att = 100; //10
    int Def = 200; //8
    int Lvl = 0;
    CharType charType = CHAR_A;    
    Isi_Stat(k, &Hp, &Att, &Def, &Lvl, charType, nama);
}

void karakterM(addressChar* k){
    *k = (addressChar) malloc(sizeof(tChar));
    if (*k == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    const char* nama = "Mage";
    int Hp = 100;
    int Exp = 0;
    int Gold = 0;
    int Att = 15;
    int Def = 5;
    int Lvl = 0;
    CharType charType = CHAR_M;
    Isi_Stat(k, &Hp, &Att, &Def, &Lvl, charType, nama);
}

void karakterD(addressChar* k){
    *k = (addressChar) malloc(sizeof(tChar));
    if (*k == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    const char* nama = "Defender";
    int Hp = 180;
    int Exp = 0;
    int Gold = 0;
    int Att = 7;
    int Def = 12;
    int Lvl = 0;
    CharType charType = CHAR_D;
    Isi_Stat(k, &Hp, &Att, &Def, &Lvl, charType, nama);
}

// FIX: Pass CharType by value, not pointer
void Isi_Stat(addressChar* k, int *Hp, int *Att, int *Def, int *Lvl, CharType charType, const char* nama) {
    if (*k != NULL) {
        strncpy((*k)->nama, nama, sizeof((*k)->nama) - 1);
        (*k)->nama[sizeof((*k)->nama) - 1] = '\0';
        (*k)->Hp = *Hp;
        (*k)->Exp = 3000;
        (*k)->Gold = 100;
        (*k)->Att = *Att;
        (*k)->Def = *Def;
        (*k)->Lvl = *Lvl;
        (*k)->isDefending = DEFAULT;
        (*k)->inventory.count = 0;
        (*k)->charType = charType;
        
        (*k)->skilltree = initSkillTree(charType);
        resetSkillTree((*k)->skilltree);
        efekSkill(*k, 0);
    }
}

//===================== SKILLLLLL =============================
int expLevel(addressChar k){
	return (k->Lvl + 1) * 100;
}
	
void levelUp(addressChar k){
	if (k == NULL) return;
	
	int skillId = 1;
	int NextLvlExp = expLevel(k);
	
	while(k->Exp >= NextLvlExp){
		k->Exp -= NextLvlExp;
		k->Lvl += 1;
		unlockNode(k->skilltree, skillId);
		efekSkill(k, skillId); 
		NextLvlExp = expLevel(k);
		skillId++;
	}
}


void efekSkill(addressChar k, int skillId) {
    if (k == NULL) return;

    int valueEfek = 0;
    float persentase = 0.0f;
    char* tipeEfek;

    SkillTree *target = getNodeById(k->skilltree, skillId);

    if (target != NULL) {
        printf("Node ID %d ditemukan!\n", skillId);

        switch (target->node->nodeType) {
            case BASIC_ADDITION:
                tipeEfek = target->node->data.basic->description;
                valueEfek = target->node->data.basic->value;

                if (strcmp(tipeEfek, "HP Up+") == 0) k->Hp += valueEfek;
                else if (strcmp(tipeEfek, "DEF Up+") == 0) k->Def += valueEfek;
                else if (strcmp(tipeEfek, "Attack Up+") == 0) k->Att += valueEfek;
                else if (strcmp(tipeEfek, "All Stats Up++") == 0) {
                    k->Hp += valueEfek;
                    k->Def += valueEfek;
                    k->Att += valueEfek;
                }
                break;

            case PERCENTAGE_ADDITION:
                tipeEfek = target->node->data.percentage->description;
                persentase = target->node->data.percentage->percentage;

                if (strcmp(tipeEfek, "HP Up+") == 0) k->Hp += (int)(k->Hp * persentase);
                else if (strcmp(tipeEfek, "DEF Up+") == 0) k->Def += (int)(k->Def * persentase);
                else if (strcmp(tipeEfek, "Attack Up+") == 0) k->Att += (int)(k->Att * persentase);
                break;

            case SKILL_UNLOCK:
                printf("Skill: %s (Power: %d, Scale: %.1f)\n",
                    target->node->data.skill->skillName,
                    target->node->data.skill->power,
                    target->node->data.skill->scale);
                simpanSkill(k, target);
                break;
        }
    } else {
        printf("Node ID %d tidak ditemukan.\n", skillId);
    }
}

void simpanSkill(addressChar k, SkillTree *node) {
    if (k == NULL || node == NULL || node->node->nodeType != SKILL_UNLOCK) return;

    if (k->skillCount >= MAX_SKILL) {
        printf("Skill tidak bisa ditambahkan. Jumlah maksimal skill tercapai.\n");
        return;
    }

    SkillList *target = &k->skills[k->skillCount]; 

    strncpy(target->skillName, node->node->data.skill->skillName, sizeof(target->skillName) - 1);
    target->skillName[sizeof(target->skillName) - 1] = '\0';

    target->power = node->node->data.skill->power;
    target->scale = node->node->data.skill->scale;

    k->skillCount++;  // Tambahkan jumlah skill
}

//=========================INVENTORY=============================
void tambahItemKeKarakter(addressChar karakter, tItem* I){
    if (karakter->inventory.count >= MAX_INVENTORY) {
        printf("Inventory karakter penuh!\n");
        return;
    }
    tambahItem(&(karakter->inventory), *I);
}

void tampilkanInventoryKarakter(addressChar karakter) {
    int startX = 92;  
    int startY = 9;
    int maxY = 28; 
	   
    for (int y = startY; y < maxY; y++) {
        gotoxy(startX, y);
        printf("                          "); 
    }

    tampilkanInventory(&(karakter->inventory), startX, startY);
}

void pilihItemKarakter(addressChar karakter) {
    tItem *dipilih = pilihItem(&(karakter->inventory));
    if (dipilih == NULL) return;
    
    gotoxy(30, HEIGHT + 10);
    printf("Menggunakan item: %s\n", dipilih->item);

    if (dipilih->Type == HealPotion) {
        karakter->Hp += dipilih->effect.heal.amount;
        gotoxy(30, HEIGHT + 11);
        printf("HP bertambah %d\n", dipilih->effect.heal.amount);
    } 
	
	if (dipilih->Type == BurnPotion || dipilih->Type == FreezePotion ) {
    	gotoxy(30, HEIGHT + 11);
        printf("Item ini hanya bisa digunakan saat bertarung dengan musuh.\n");
        Sleep(1500);
        return;
    }

    dipilih->bag--;
    if (dipilih->bag == 0) {
        // Hapus dari inventory jika habis
        int index = dipilih - karakter->inventory.items;
        hapusItem(&(karakter->inventory), index);
    }

    Sleep(1500);
}

int getPower(addressChar k){
    int attack, hp, defense, level;
    int power, tempPow;

    attack =  k->Att;
    hp = k->Hp;
    defense = k->Def;
    level = k->Lvl;

    power = hp/defense;
    tempPow = level/10;

    power += attack;
    power = power * tempPow;

    return power;
}
