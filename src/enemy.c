#inlcude "enemy.h"

void initEnemy(Enemy *enemy, EnemyType Type, const Shape *player){
	srand(time(NULL));
	
	enemy->Type = Type
	
	int playerLv = player->Lvl;	//Mengambil data Lv struct Shape
	
	int minLv = (playerLv - 10 > 0) ? (playerLv - 10) : 1;
	int maxLv = playerLv + 10;

	enemy->Lv = minLv + rand() % (maxLv - minLv + 1);
	
	switch (Type){
		case SLIME{
			enemy->Hp = 150 + 30 * enemy->Lv;
			enemy->Att = 20 + 5 * enemy->Lv;
			enemy->Def = 50 + 10 * enemy->Lv;
			enemy->isDefending = 0;
			
			// Skill SLIME : Heavy Attack (ATTACK), Absorb (DEFENSE), Taunt (HEAL)
			enemy->skills[0] = createSkill("HEAVY ATTACK", SKILL_ATTACK, getEnemyAtt(enemy), 1.2)
			enemy->skills[1] = createSkill("ABSORB", SKILL_DEFENSE, getEnemyDef(enemy), 1.1);
			enemy->skills[2] = createSkill("TAUNT", SKILL_HEAL, 10, 1.0);
			
			break;
		}
			
		case WOLF{
			enemy->Hp = 80 + 15 * enemy->Lv;
			enemy->Att = 70 * 15 * enemy->Lv;
			enemy->Def = 20 + 5 * enemy->Lv;
			enemy->isDefending = 0;
			
			// Skill WOLF : Slash (ATTACK), Hard Fur (DEFENSE), Howl (HEAL)
			enemy->skills[0] = createSkill("SLASH", SKILL_ATTACK, getEnemyAtt(enemy), 1.1);
			enemy->skills[1] = createSkill("HARD FUR", SKILL_DEFENSE, getEnemyDef(enemy), 1.2);
			enemy->skills[2] = createSkill("HOWL", SKILL_HEAL, 10, 1.0);
			
			break;
		}
		
		case GOBLIN{
			enemy->Hp = 100 + 20 * enemy->Lv;
			enemy->Att = 50 + 10 * enemy->Lv;
			enemy->Def = 40 + 5 * enemy->Lv;
			enemy->isDefending = 0;
			
			// Skill GOBLIN : Charge (ATTACK), Spin (DEFENSE), Eat (HEAL)
			enemy->skills[0] = createSkill("CHARGE", SKILL_ATTACK, getEnemyAtt(enemy), 1.1);
			enemy->skills[1] = createSkill("SPIN", SKILL_DEFENSE, getEnemyDef(enemy), 1.1);
			enemy->skills[2] = createSkill("EAT", SKILL_HEAL, 15, 1.1);
			
			break;
		}
	}
	
	
}

Skill createSkill(const char *name, SkillType type, int power, float scale){
    Skill skill;

    // Salin nama skill
    strncpy(skill.name, name, sizeof(skill.name));
    skill.name[sizeof(skill.name) - 1] = '\0'; // Pastikan null-terminated

    // Set data lainnya
    skill.type = type;
    skill.power = power;
    skill.scale = scale;

    return skill;
}

int getEnemyHP(const Enemy *enemy){
	return enemy->Hp;
}

int getEnemyAtt(const Enemy *enemy){
	return enemy->Att;
}

int getEnemyDef(const Enemy *enemy){
	return enemy->Def;
}

int encounter(){
	int chance = 25;
	
	int roll = rand() % 100;
	return (roll < chance) ? 1 : 0;
}

