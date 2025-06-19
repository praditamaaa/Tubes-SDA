/*
.| Program : playablechar.h
.| Header yang berisikan modul untuk membuat karakter
.| dengan data dari common.h, inventory.h, dan skilltree.h
.|
.| Oleh : Afriza Choirie Saputra
*/

#ifndef playablechar_h
#define playablechar_h
#include "common.h"
#include "inventory.h"
#include "skilltree.h"
#include "skilltree_utils.h"
#include "skilltree_save.h"
#define DEFAULT 0

#define MAX_SKILL 6

typedef struct SkillList {
    char skillName[50];
    int power;
    float scale;
} SkillList;

typedef struct tChar{
    char nama[50];
    int Hp;
    int Exp;
    int Gold;
    int Att;
    int Def;
    int Lvl;
    int isDefending;
    Inventory inventory;
    SkillTree* skilltree;       
    CharType charType;
	SkillList skills[MAX_SKILL];
    int skillCount;  
} tChar;

// ciptakan karakter
int inputCharUser();
void pilihKarakter(addressChar* k, int pilihan);
void karakterA(addressChar* k);
void karakterM(addressChar* k);
void karakterD(addressChar* k);
void Isi_Stat(addressChar* k, int* Hp, int* Att, int* Def, int* Lvl, CharType charType, const char* nama);

// skill
int expLevel(addressChar k);
void levelUp(addressChar k);
void efekSkill(addressChar k, int skillId);
void simpanSkill(addressChar k, SkillTree *node);

// Inventory
void tambahItemKeKarakter(addressChar karakter, tItem* I);
void tampilkanInventoryKarakter(addressChar karakter);
void pilihItemKarakter(addressChar karakter);

int getPower(addressChar k);

#endif
