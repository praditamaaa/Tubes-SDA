#include "combat.h" 

void doPlayerAttack(addressChar player, Enemy *enemy) {
    int damage;

    if (enemy->isDefending) {
        damage = player->Att - enemy->Def; 
        enemy->isDefending = 0;            
    } else {
        damage = player->Att - (enemy->Def / 2); 
    }

    if (damage < 1) damage = 1;

    enemy->Hp -= damage;
    if (enemy->Hp < 0) enemy->Hp = 0;

    printf(" KAmu menyerang dengan %d damage!\n", damage);
}

void doPlayerDefense(addressChar player) {
    player->isDefending = 1;
    printf("kamu bertahan! \n");
}

void usePlayerSkill(addressChar player, Enemy *enemy) {
	int i;
	
	if (player->skillCount == 0) {
        printf("Kamu belum memiliki skill!\n");
        return;
    }

    printf("Pilih Skill:\n");
    for (i = 0; i < player->skillCount; i++) {
        printf("%d. %s (Power: %d, Scale: %.2f)\n", i + 1, 
               player->skills[i]->skillName); // . menjadi ->
    }

    int pilihan;
    printf("Pilihan: ");
    scanf("%d", &pilihan);
    getchar();

    if (pilihan < 1 || pilihan > player->skillCount) {
        printf("Pilihan tidak valid!\n");
        return;
    }

    SkillList *skill = player->skills[pilihan - 1]; //menghapus &

    int damage = (int)(skill->power * skill->scale) - (enemy->Def / 2);
    if (damage < 1) damage = 1;

    player->Hp -= damage;
    if (player->Hp < 0) player->Hp = 0;

    printf("Kamu menggunakan skill %s memberikan %d damage!\n", 
           skill->skillName, damage);
}

void pakeItem(addressChar karakter, Enemy *enemy, EffectQueue *queue) {
    tItem *dipilih = pilihItem(&(karakter->inventory));
    if (dipilih == NULL) return;

    gotoxy(30, HEIGHT + 10);
    printf("Menggunakan item: %s\n", dipilih->item);

    switch (dipilih->Type) {
        case HealPotion:
            karakter->Hp += dipilih->effect.heal.amount;
            gotoxy(30, HEIGHT + 11);
            printf("HP bertambah %d\n", dipilih->effect.heal.amount);
            break;

        case BurnPotion:
        case FreezePotion:
            enqueue(queue, dipilih->effect.status);
            gotoxy(30, HEIGHT + 11);
            printf("Efek %s dimasukkan ke queue!\n",
                   dipilih->Type == BurnPotion ? "Burn" : "Freeze");
            break; 
    }

    dipilih->bag--;
    if (dipilih->bag == 0) {
        int index = dipilih - karakter->inventory.items;
        hapusItem(&(karakter->inventory), index);
    }

    Sleep(1500);
}


bool doPlayerEscape() {
    int escapeChance = 50;
    int roll = rand() % 100;
    
    if (roll < escapeChance) {
        printf("berhasil kabur\n");
        return true;
    } else {
        printf("gagal kabur!\n");
        return false;
    }
}

void EnemyAttack(Enemy *enemy, addressChar player) {
    int damage;

    if (player->isDefending) {
        damage = enemy->Att - player->Def;
        player->isDefending = 0;
    } else {
        damage = enemy->Att - (player->Def / 2);
    }

    if (damage < 1) damage = 1;

    player->Hp -= damage;  
    if (player->Hp < 0) player->Hp = 0;

    printf("Musuh menyerang dengan %d damage!\n", damage);
}

void EnemyDefense(Enemy *enemy) {
    enemy->isDefending = 1;
    printf("Musuh bertahan!\n");
}

void EnemySkill(Enemy *enemy, addressChar player) {
    int skillIndex = rand() % 3;
    Skill *skill = &enemy->skills[skillIndex];
    
    printf("Musuh menggunakna %s!\n", skill->name);
    
    switch(skill->type) {
        case SKILL_ATTACK: {
            int damage = (int)(skill->power * skill->scale) - (player->Def / 2);
            if (player->isDefending) {
                damage = damage / 2;
                player->isDefending = 0;
            }
            if (damage < 1) damage = 1;
            
            player->Hp -= damage;
            printf("Musush menyerang dengan skill -%dhp\n", damage);
            
            if (player->Hp < 0) player->Hp = 0;
            break;
        }
        case SKILL_DEFENSE:
            enemy->isDefending = 1;
            printf("Defend mussuh naik\n");
            break;
        case SKILL_HEAL: {
            int heal = (int)(skill->power * skill->scale);
            enemy->Hp += heal;
            printf("musuh ngeheal +%dhp\n", heal);
            break;
        }
    }
}

void enqueue(EffectQueue *List, StatusEffect effect) {
    EffectNode *newNode = malloc(sizeof(EffectNode));
    newNode->effect = effect;
    newNode->next = NULL;

    if (List->last == NULL) {
        List->first = List->last = newNode;
    } else {
        List->last->next = newNode;
        List->last = newNode;
    }

    printf("[QUEUE] Efek %d (durasi: %d) ditambahkan.\n", effect.type, effect.duration);
}

void updateEffect(EffectQueue *List, int *targetHP) {
    if (List->first == NULL) return;

    StatusEffect *efek = &List->first->effect;

    switch (efek->type) {
        case STATUS_BURN:
            printf("[EFFECT] Musuh terbakar! -%d HP\n", efek->damage);
            *targetHP -= efek->damage;
            if (*targetHP < 0) *targetHP = 0;
            break;

        case STATUS_FREEZE:
            printf("[EFFECT] Musuh beku! Tidak bisa menyerang.\n");
            
            break;
    }

    efek->duration--;
    
    if (efek->duration <= 0) {
        EffectNode *hapus = List->first;
        List->first = List->first->next;
        if (List->first == NULL) List->last = NULL;
        free(hapus);
        printf("[EFFECT] Efek selesai.\n");
    }
}
