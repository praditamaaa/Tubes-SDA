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
    
    gotoxy(6,23);
    setColor(10);
    printf("KAmu mmeneyrang dengan %d damage!", damage);
}

void doPlayerDefense(addressChar player) {
    player->isDefending = 1;
    gotoxy(6,23);
    setColor(10);
    printf("kamu bertahan!");
}

void usePlayerSkill(addressChar player, Enemy *enemy) {
    if (player->skillCount == 0) {
        gotoxy(6, 22);
        printf("Kamu belum memiliki skill!");
        return;
    }

	gotoxy(6, 22);
	setColor(10);
    printf("Pilih Skill:\n");

    for (int i = 0; i < player->skillCount; i++) {
    	gotoxy(6,22 + i);
        printf("%d. %s (Power: %d, Scale: %.2f)\n",
               i + 1,
               player->skills[i].skillName,
               player->skills[i].power,
               player->skills[i].scale);
    }

    int pilihan;
    gotoxy(6, 26);
    printf("Pilihan: ");
    scanf("%d", &pilihan);
    getchar();

    // Validasi input
    if (pilihan < 1 || pilihan > player->skillCount) {
        gotoxy(6, 26);
        printf("Pilihan tidak valid!");
        return;
    }

    SkillList *skill = &player->skills[pilihan - 1];

    int damage = (int)(skill->power * skill->scale) - (enemy->Def / 2);
    if (damage < 1) damage = 1;

    enemy->Hp -= damage;
    if (enemy->Hp < 0) enemy->Hp = 0;

    gotoxy(6, 27);
    setColor(10);
    printf("Kamu menggunakan skill %s dan memberikan %d damage ke musuh!\n", 
           skill->skillName, damage);

    Sleep(1200);
}


void pakeItem(addressChar karakter, Enemy *enemy, EffectQueue *queue) {
    tItem *dipilih = pilihItem(&(karakter->inventory));
    if (dipilih == NULL) return;	

    gotoxy(6, 25);
    printf("Menggunakan item: %s", dipilih->item);

    switch (dipilih->Type) {
        case HealPotion:
            karakter->Hp += dipilih->effect.heal.amount;
            gotoxy(6, 27);
            setColor(10);
            printf("HP bertambah %d", dipilih->effect.heal.amount);
            break;

        case BurnPotion:
        case FreezePotion:
            enqueue(queue, dipilih->effect.status);
            gotoxy(6, 26);
            printf("Efek %s diterapkan pada musuh!", 
                   dipilih->Type == BurnPotion ? "Burn" : "Freeze");
            break;
    }

    dipilih->bag--;
    if (dipilih->bag == 0) {
        int index = dipilih - karakter->inventory.items;
        hapusItem(&(karakter->inventory), index);
    }

    Sleep(2000);
}


bool doPlayerEscape() {
    int escapeChance = 50;
    int roll = rand() % 100;
    
    if (roll < escapeChance) {
    	gotoxy(6,23);
    	setColor(10);
        printf("berhasil kabur");
        return true;
    } else {
    	gotoxy(6,23);
    	setColor(10);
        printf("gagal kabur!");
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
    
    gotoxy(6,24);
    setColor(12);
    printf("Musuh menyerang dengan %d damage!", damage);
}

void EnemyDefense(Enemy *enemy) {
    enemy->isDefending = 1;
    gotoxy(6,24);
    setColor(12);
    printf("Musuh bertahan!                          ");
}

void EnemySkill(Enemy *enemy, addressChar player) {
    int skillIndex = rand() % 3;
    Skill *skill = &enemy->skills[skillIndex];
    
    gotoxy(6,24);
    setColor(12);
    printf("Musuh menggunakna %s!                    ", skill->name);
    
    switch(skill->type) {
        case SKILL_ATTACK: {
            int damage = (int)(skill->power * skill->scale) - (player->Def / 2);
            if (player->isDefending) {
                damage = damage / 2;
                player->isDefending = 0;
            }
            if (damage < 1) damage = 1;
            
            player->Hp -= damage;
            gotoxy(6,25);
            setColor(12);
            printf("Musush menyerang dengan skill -%dhp", damage);
            
            if (player->Hp < 0) player->Hp = 0;
            break;
        }
        case SKILL_DEFENSE:
            enemy->isDefending = 1;
            gotoxy(6,25);
            setColor(12);
            printf("Defend mussuh naik                         ");
            break;
        case SKILL_HEAL: {
            int heal = (int)(skill->power * skill->scale);
            enemy->Hp += heal;
            gotoxy(6,25);
            setColor(12);
            printf("musuh ngeheal +%dhp                        ", heal);
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
    //gotoxy(6,27);
    //printf("\nEfek %d (durasi: %d) ditambahkan.", effect.type, effect.duration);
}

void updateEffect(EffectQueue *List, int *targetHP) {
    if (List->first == NULL) return;

    StatusEffect *efek = &List->first->effect;

    switch (efek->type) {
        case STATUS_BURN:
        	gotoxy(6,27);
        	setColor(14);// warna merah 
            printf("Musuh terbakar! -%d HP                 ", efek->damage);
            *targetHP -= efek->damage;
            if (*targetHP < 0) *targetHP = 0;
            Sleep(2000);
            break;

        case STATUS_FREEZE:
        	gotoxy(6,27);
        	setColor(14); //warna biru terang
            printf("Musuh beku! Tidak bisa menyerang.        ");
            Sleep(2000);
            break;
    }

    efek->duration--;
    
    if (efek->duration <= 0) {
        EffectNode *hapus = List->first;
        List->first = List->first->next;
        if (List->first == NULL) List->last = NULL;
        free(hapus);
        gotoxy(6,27);
        setColor(10);
        printf("Efek selesai.                          ");
        Sleep(2000);
    }
}
