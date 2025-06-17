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
    if (*k == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    const char* nama = "Warrior";
    int Hp = 150;
    int Exp = 0;
    int Gold = 0;
    int Att = 10;
    int Def = 8;
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
        (*k)->Exp = 0;
        (*k)->Gold = 100;
        (*k)->Att = *Att;
        (*k)->Def = *Def;
        (*k)->Lvl = *Lvl;
        (*k)->isDefending = DEFAULT;
        (*k)->inventory.count = 0;
        (*k)->charType = charType;
        
        (*k)->skilltree = initSkillTree(charType);
        resetSkillTree((*k)->skilltree);
        efekSkill(*k);
    }
}

//===================== SKILLLLLL =============================
int expLevel(addressChar k){
	return k->Lvl * 100;
}
	
void levelUp(addressChar k){
	if (k == NULL) return;
	
	int NextLvlExp = expLevel(k);
	int skillId = 1;
	
	while(k->Exp > NextLvlExp){
		k->Exp -= NextLvlExp;
		k->Lvl += 1;
		unlockNode(k->skilltree, skillId);
		efekSkill(k);
		NextLvlExp = expLevel(k);
		skillId++;
	}
}

void efekSkill(addressChar k) {
    if (k == NULL) return;

    int skillId = 0;
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
                skillId++;
                break;

            case PERCENTAGE_ADDITION:
                tipeEfek = target->node->data.percentage->description;
                persentase = target->node->data.percentage->percentage;

                if (strcmp(tipeEfek, "HP Up+") == 0) k->Hp += (int)(k->Hp * persentase);
                else if (strcmp(tipeEfek, "DEF Up+") == 0) k->Def += (int)(k->Def * persentase);
                else if (strcmp(tipeEfek, "Attack Up+") == 0) k->Att += (int)(k->Att * persentase);

                skillId++;
                break;

            case SKILL_UNLOCK:
                printf("Skill: %s (Power: %d, Scale: %.1f)\n",
                    target->node->data.skill->skillName,
                    target->node->data.skill->power,
                    target->node->data.skill->scale);

                simpanSkill(k, target);
                skillId++;
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

    SkillList *target = &k->skills[k->skillCount];  // Ambil pointer ke elemen berikutnya

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
    // Koordinat awal untuk tampilkan di kanan layar
    int startX = 92;  
    int startY = 9;
    int maxY = 28; 
	   
    // Bersihkan area inventory dulu
    for (int y = startY; y < maxY; y++) {
        gotoxy(startX, y);
        printf("                          "); 
    }

    tampilkanInventory(&(karakter->inventory), startX, startY);
}

void pilihItemKarakter(addressChar karakter) {
    tItem *dipilih = pilihItem(&(karakter->inventory));
    if (dipilih == NULL) return;

    printf("Menggunakan item: %s\n", dipilih->item);

    if (dipilih->Type == HealPotion) {
        karakter->Hp += dipilih->effect.heal.amount;
        printf("HP bertambah %d\n", dipilih->effect.heal.amount);
    } else if (dipilih->Type == BurnPotion || dipilih->Type == FreezePotion) {
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
