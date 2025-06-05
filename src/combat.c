#include "combat.h"

const StatusEffect STATUS_EFFECT[STATUS_COUNT] = {
	{STATUS_BURN, 15, 3},
	{STATUS_FREEZE, 0, 3}
};

/* AKSI PEMAIN */
void doAttack(User *user, Enemy *enemy){
	int damageDealt, Attack, Defense;
	Attack = user->playablechar->Att;
	Defense = getEnemyDef(enemy);
	
	if(enemy->isDefending == 1){
		damageDealt = Attack - Defense;
		damageDealt = damageDealt / 2;
		if(damageDealt < 1){
			damageDealt = 1;
		}
		
		enemy->isDefending = 0;
	}else{
		damageDealt = Attack - Defense;
		if(damageDealt < 1){
			damageDealt = 1;
		}
	}
	
	enemy->Hp -= damageDealt
	
	// Tampilkan LOG bahwa Playablehar melakukan DAMAGE kepada Enemy
}

void doDefense(User *user, Enemey *enemy){
	user->playablechar->isDefending = 1;
	printf("ANDA memilih Bertahan! Damage yang diterima akan Berkurang!");
}

void useSkill(User *user, Enemy *enemy){
	// Variabel yang menyimpan SKILL ????
}

void useItem(User *user, Enemy *enemy, ){
	// M
}

void doEscape(User *player){
	printf("ANDA memilih untuk Kabur!\n");
}

/* AKSI MUSUH */
void enemyAttack(Enemy *enemy, User *user){
	int Attack = getEnemyAtt(enemy);
	int Defense = user->playablechar->Def;
	int damageDealt;
	
	// BAGAIMANA JIKA PLAYER MELAKUKAN doDefense ???
	if(user->playablechar->isDefending == 1){
		damageDealt = Attack - Defense;
		damageDealt = damageDealt / 2;
		if(damageDealt < 1){
			damageDealt = 1;
		}
		
		user->playablechar->isDefending = 0;
	}else{
		damageDealt = Attack - Defense;
		if(damageDealt < 1){
			damageDealt = 1;
		}
	}
	
	user->playablechar->Hp -= damage;
	
	// Masukkan ke dalam Stack Gerakan
	
	// Tampilkan LOG bahwa Enemy melakukan DAMAGE kepada Playablechar
}

void enemyDefense(Enemy *enemy, User *user){
	enemy->isDefending = 1;
	printf("Musuh memilih bertahan! Damage yang diterima akan Berkurang!\n");
}

void enemySkill(Enemy *enemy, User *user){
	int move = rand() %3;
	Skill chosen = enemy->skills[move];
	switch (chosen.type){
		case SKILL_ATTACK{
			int damageDealt, damageSkill;
			
			damageSkill =(int)(chosen.power * chosen.scale);
			
			if(user->playablechar->isDefending == 1){
				damageDealt = damageSkill - user->playablechar->Def;
				damageDealt = damageDealt / 2;
				if(damageDealt < 1){
					damageDealt = 1;
				}
				user->playablechar->isDefending = 0;
			}else{
				damageDealt = damageSkill - user->playablechar->Def;
				if(damageDealt < 1){
					damageDealt = 1;
				}
			}
			
			user->playablechar->Hp -= damageDealt;
			// Tampilkan LOG bahwa Enemy menggunakan SKILL dan melakukan Damage kepada Playablechar
			break;
		}
		case SKILL_DEFENSE{
			int buff;
			
			buff = (int)(chosen.power * chosen.scale);
			enemy->DefBuff.value = buff;
			enemy->DefBuff.duration = 1;
			
			// Tampilkan LOG bahwa Enemy menggunakan SKILL untuk meningkatkan DEF
			break;
		}
		case SKILL_HEAL{
			int heal;
			
			heal = (int)(chosen.power * chosen.scale);
			enemy->Hp += heal
			
			// Tampilkan LOG bahwa Enemy menggunakan SKILL untuk memulihkan HP
			break;
		}
	}
	
}

/* CONSOLE */
