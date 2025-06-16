#ifndef playablechar_h
#define playablechar_h

#include "common.h"
#include "inventory.h"
#include "welcomesc.h"
#include "skilltree.h"
#include "skilltree_utils.h"
#include "skilltree_save.h"

#define DEFAULT 0

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
    SkillTree* skiltree;       
    CharType charType; 
} tChar;

void inputCharUser(addressChar* k);
void pilihKarakter(addressChar* k, int pilihan);
void karakterA(addressChar* k);
void karakterM(addressChar* k);
void karakterD(addressChar* k);
void Isi_Stat(addressChar* k, int *Hp, int *Att, int *Def, int *Lvl, CharType charType, const char* nama);

// INVENTORO
void tambahItemKeKarakter(addressChar* karakter, addressItem* I);
void tampilkanInventoryKarakter(addressChar karakter);
void pilihItemKarakter(addressChar karakter);

// MANAJEMEN SKIL
void applySkillEffects(addressChar character);
void applyNodeEffects(addressChar character, SkillTree* node);
void applyBasicEffect(addressChar character, BasicAddition* effect);
void applyPercentageEffect(addressChar character, PercentageAddition* effect);
int unlockSkillForCharacter(addressChar character, int nodeId);
void showAvailableSkills(addressChar character);
void printNodeInfo(SkillTree* node);

// INFO KARAKTER
void showCharacterStats(addressChar character);
void destroyCharacter(addressChar character);
addressChar createCharacterWithSkillTree(const char* name, CharType type);

#endif
