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
        (*k)->inventory = NULL;
        (*k)->charType = charType;
        
        (*k)->skiltree = initSkillTree(charType);
        loadSkillTree((*k)->skiltree, charType); 
        applySkillEffects(*k);
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

// Fungsi untuk menerapkan efek skill ke stats karakter
void applySkillEffects(addressChar character) {
    if (character == NULL || character->skiltree == NULL) return;
    
    // Simpan base stats berdasarkan tipe karakter
    int baseHP, baseAttack, baseDefense;
    
    switch(character->charType) {
        case CHAR_A: // Warrior
            baseHP = 150; baseAttack = 10; baseDefense = 8;
            break;
        case CHAR_M: // Mage
            baseHP = 100; baseAttack = 15; baseDefense = 5;
            break;
        case CHAR_D: // Defender
            baseHP = 180; baseAttack = 7; baseDefense = 12;
            break;
        default:
            baseHP = 100; baseAttack = 10; baseDefense = 10;
            break;
    }
    
    // Reset stats ke base value
    character->Hp = baseHP;
    character->Att = baseAttack;
    character->Def = baseDefense;
    
    // Apply semua skill yang sudah di-unlock
    applyNodeEffects(character, character->skiltree);
}

// Fungsi rekursif untuk menerapkan efek dari semua node yang unlocked
void applyNodeEffects(addressChar character, SkillTree* node) {
    if (node == NULL || !node->isUnlocked || character == NULL) return;
    
    // Apply efek dari node ini
    if (node->node != NULL) {
        switch (node->node->nodeType) {
            case BASIC_ADDITION:
                if (node->node->data.basic != NULL) {
                    applyBasicEffect(character, node->node->data.basic);
                }
                break;
            case PERCENTAGE_ADDITION:
                if (node->node->data.percentage != NULL) {
                    applyPercentageEffect(character, node->node->data.percentage);
                }
                break;
            case SKILL_UNLOCK:
                // Skill unlock akan ditangani terpisah dalam sistem combat
                break;
        }
    }
    
    // Apply effects ke semua child nodes
    SkillTree* child = node->firstSon;
    while (child != NULL) {
        applyNodeEffects(character, child);
        child = child->nextBrother;
    }
}

// Fungsi untuk menerapkan efek basic addition
void applyBasicEffect(addressChar character, BasicAddition* effect) {
    if (character == NULL || effect == NULL) return;
    
    if (strstr(effect->description, "HP Up") || strstr(effect->description, "Health")) {
        character->Hp += effect->value;
    }
    else if (strstr(effect->description, "Attack Up") || strstr(effect->description, "Damage")) {
        character->Att += effect->value;
    }
    else if (strstr(effect->description, "DEF Up") || strstr(effect->description, "Defense")) {
        character->Def += effect->value;
    }
    else if (strstr(effect->description, "All Stats Up") || strstr(effect->description, "All")) {
        character->Hp += effect->value;
        character->Att += effect->value;
        character->Def += effect->value;
    }
}

// Fungsi untuk menerapkan efek percentage addition
void applyPercentageEffect(addressChar character, PercentageAddition* effect) {
    if (character == NULL || effect == NULL) return;
    
    if (strstr(effect->description, "HP Up%") || strstr(effect->description, "Health%")) {
        character->Hp = (int)(character->Hp * effect->percentage);
    }
    else if (strstr(effect->description, "Attack Up%") || strstr(effect->description, "Damage%")) {
        character->Att = (int)(character->Att * effect->percentage);
    }
    else if (strstr(effect->description, "DEF Up%") || strstr(effect->description, "Defense%")) {
        character->Def = (int)(character->Def * effect->percentage);
    }
}

void showAvailableSkills(addressChar character) {
    if (character == NULL || character->skiltree == NULL) {
        printf("Invalid character!\n");
        return;
    }

    printf("\n=== Unlockable Skills for %s (Level %d) ===\n", character->nama, character->Lvl);

    int unlockableIds[20];
    int count = getUnlockableNodes(character->skiltree, unlockableIds, 20);

    if (count == 0) {
        printf("No skills available to unlock.\n");
        return;
    }

    printf("Skills that meet parent/unlocked condition (based on node logic):\n");
    for (int i = 0; i < count; i++) {
        SkillTree* node = getNodeById(character->skiltree, unlockableIds[i]);
        if (node != NULL && node->node != NULL) {
            printf("Node ID %d: ", unlockableIds[i]);
            printNodeInfo(node);
        }
    }
}


// Fungsi untuk mencetak informasi node skill
void printNodeInfo(SkillTree* node) {
    if (node == NULL || node->node == NULL) {
        printf("Invalid node\n");
        return;
    }
    
    switch (node->node->nodeType) {
        case BASIC_ADDITION:
            if (node->node->data.basic != NULL) {
                printf("%s (+%d)\n", 
                       node->node->data.basic->description, 
                       node->node->data.basic->value);
            }
            break;
        case PERCENTAGE_ADDITION:
            if (node->node->data.percentage != NULL) {
                printf("%s (%.1f%% bonus)\n", 
                       node->node->data.percentage->description, 
                       (node->node->data.percentage->percentage - 1.0) * 100);
            }
            break;
        case SKILL_UNLOCK:
            if (node->node->data.skill != NULL) {
                printf("Skill: %s (Power: %d)\n", 
                       node->node->data.skill->skillName, 
                       node->node->data.skill->power);
            }
            break;
        default:
            printf("Unknown skill type\n");
            break;
    }
}

void showCharacterStats(addressChar character) {
    if (character == NULL) {
        printf("Invalid character!\n");
        return;
    }
    
    printf("\n=== %s Stats ===\n", character->nama);
    printf("HP: %d\n", character->Hp);
    printf("Attack: %d\n", character->Att);
    printf("Defense: %d\n", character->Def);
    printf("Level: %d\n", character->Lvl);
    printf("Experience: %d\n", character->Exp);
    printf("Gold: %d\n", character->Gold);
    printf("Character Type: %d\n", character->charType);
}

void destroyCharacter(addressChar character) {
    if (character != NULL) {
        // Save skill tree sebelum destroy
        if (character->skiltree != NULL) {
            saveSkillTree(character->skiltree, character->charType);
            freeSkillTree(character->skiltree);
        }
        
        // Free inventory jika ada
        if (character->inventory != NULL) {
            // MISAL ada fungsi untuk free inventory
            // freeInventory(character->inventory);
        }
        
        // Free character
        free(character);
    }
}

int unlockSkillForCharacter(addressChar character, int nodeId) {
    if (character == NULL || character->skiltree == NULL) {
        printf("Invalid character or skill tree!\n");
        return 0;
    }

    if (!canUnlockNode(character->skiltree, nodeId)) {
        printf("Cannot unlock this skill yet! Prerequisites not met.\n");
        return 0;
    }

    if (unlockNode(character->skiltree, nodeId)) {
        applySkillEffects(character); // Recalculate stats

        // Save progress
        if (saveSkillTree(character->skiltree, character->charType)) {
            printf("Skill unlocked successfully (Node ID: %d)!\n", nodeId);
        } else {
            printf("Skill unlocked but failed to save progress.\n");
        }

        return 1;
    }

    printf("Failed to unlock skill!\n");
    return 0;
}


void autoUnlockByLevel(addressChar character) {
    if (character == NULL || character->skiltree == NULL) return;

    int level = character->Lvl;

    if (level >= 0) unlockNode(character->skiltree, 0); 
    if (level >= 1) unlockNode(character->skiltree, 1);
    if (level >= 2) unlockNode(character->skiltree, 2);
    if (level >= 3) unlockNode(character->skiltree, 3);
    if (level >= 4) unlockNode(character->skiltree, 4);
    if (level >= 5) unlockNode(character->skiltree, 5);
    if (level >= 6) unlockNode(character->skiltree, 6);
    if (level >= 7) unlockNode(character->skiltree, 7);
    if (level >= 8) unlockNode(character->skiltree, 8);
    if (level >= 9) unlockNode(character->skiltree, 9);
    if (level >= 10) unlockNode(character->skiltree, 10);
    // Tambah sesuai struktur skilltree-mu

    applySkillEffects(character);
}

void gainExp(addressChar character, int gainedExp) {
    if (character == NULL) return;

    character->Exp += gainedExp;

    int previousLevel = character->Lvl;
    character->Lvl = character->Exp / 100;
    if (character->Lvl > previousLevel) {
        printf("Level Up! %s naik ke level %d!\n", character->nama, character->Lvl);
        autoUnlockByLevel(character);
        saveSkillTree(character->skiltree, character->charType);
    }
}
