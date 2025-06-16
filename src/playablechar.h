#ifndef playablechar_h
#define playablechar_h
#include "common.h"
#include "inventory.h"
#include "welcomesc.h"
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
    addressItem inventory;
    SkillTree* skilltree;       
    CharType charType;
	SkillList* skills[MAX_SKILL];
    int skillCount;  
} tChar;

// ciptakan karakter
void inputCharUser(addressChar* k);
void pilihKarakter(addressChar* k, int pilihan);
void karakterA(addressChar* k);
void karakterM(addressChar* k);
void karakterD(addressChar* k);
void Isi_Stat(addressChar* k, int* Hp, int* Att, int* Def, int* Lvl, CharType charType, const char* nama);

// skill
int expLevel(addressChar k);
void levelUp(addressChar k);
void efekSkill(addressChar k);
void simpanSkill(addressChar k, SkillTree *node);

// Inventory
void tambahItemKeKarakter(addressChar* karakter, addressItem* I);
void tampilkanInventoryKarakter(addressChar karakter);
void pilihItemKarakter(addressChar karakter);


#endif
