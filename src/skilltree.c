/*
.| Program : skilltree.c
.| Berisi logika atau isi modul dari data header skilltree.h 
.| dengan implementasi skilltree_builder.h 
.|
.| Tujuan : Membuat Skill Tree berdasarkan referensi yang telah ada
.| 			untuk setiap tipe karakter berbeda.
.| 
.| Oleh : Radhitya Maulana Arrafi
*/

#include "skilltree_builder.h"

SkillTree *initSkillTree(CharType Type){
	SkillTree *root = NULL;
	
	switch(Type){
		case CHAR_A :
			/*+==================================================+*/
			/*|                     Level 0                      |*/
			/*+==================================================+*/
			root = newBasicNode(Type, "Attack Up+", 20);


			/*+==================================================+*/
			/*|                     Level 1                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Achild1a = newBasicNode(Type, "HP Up+", 20);
            		connectChild(root, Achild1a);
            
            		// Anak 2
            		SkillTree *Achild1b = newBasicNode(Type, "DEF Up+", 5);
            		connectBrother(Achild1a, Achild1b);
			
			// Anak 3
			SkillTree *Achild1c = newBasicNode(Type, "Attack Up+", 15);
			connectBrother(Achild1b, Achild1c);
			
			
			/*+==================================================+*/
			/*|                     Level 2                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Achild2a = newSkillNode(Type, "Continous Attack", 10, 1.1); // Attack
			connectChild(Achild1a, Achild2a);
			
			
			/*+==================================================+*/
			/*|                     Level 3                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Achild3a = newBasicNode(Type, "All Stats Up+", 10);
			connectChild(Achild2a, Achild3a);
			
			// Anak 2
			SkillTree *Achild3b = newBasicNode(Type, "HP Up+", 20);
			connectBrother(Achild3a, Achild3b);
			
			// Anak 3
			SkillTree *Achild3c = newBasicNode(Type, "DEF Up+", 10);
			connectBrother(Achild3b, Achild3c);
			
			
			/*+==================================================+*/
			/*|                     Level 4                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Achild4a = newPrecentageNode(Type, "Attack Up%", 1.1);
			connectChild(Achild3a, Achild4a);
			
			// Anak 2
			SkillTree *Achild4b = newPrecentageNode(Type, "HP Up%", 1.2);
			connectBrother(Achild4a, Achild4b);
			
			// Anak 3
			SkillTree *Achild4c = newPrecentageNode(Type, "DEF Up%", 1.1);
			connectBrother(Achild4b, Achild4c);
			
			
			/*+==================================================+*/
			/*|                     Level 5                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Achild5a = newSkillNode(Type, "Quick Pierce", 50, 1.1); // Attack
			connectChild(Achild4a, Achild5a);
			
			
			/*+==================================================+*/
			/*|                     Level 6                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Achild6a = newBasicNode(Type, "DEF Up+", 20);
			connectChild(Achild5a, Achild6a);
			
			// Anak 2
			SkillTree *Achild6b = newBasicNode(Type, "Attack Up+", 40);
			connectBrother(Achild6a, Achild6b);
			
			// Anak 3
			SkillTree *Achild6c = newBasicNode(Type, "HP Up+", 50);
			connectBrother(Achild6b, Achild6c);
			
			
			/*+==================================================+*/
			/*|                     Level 7                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Achild7a = newPrecentageNode(Type, "DEF Up%", 1.2);
			connectChild(Achild6a, Achild7a);
			
			// Anak 2
			SkillTree *Achild7b = newPrecentageNode(Type, "Attack Up%", 1.3);
			connectBrother(Achild7a, Achild7b);
			
			// Anak 3
			SkillTree *Achild7c = newPrecentageNode(Type, "HP Up%", 1.2);
			connectBrother(Achild7b, Achild7c);
			
			
			/*+==================================================+*/
			/*|                     Level 8                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Achild8a = newSkillNode(Type, "X Slash", 100, 1.1);
			connectChild(Achild7a, Achild8a);
			
			
			/*+==================================================+*/
			/*|                     Level 9                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Achild9a = newBasicNode(Type, "Attack Up+", 80);
			connectChild(Achild8a, Achild9a);
			
			// Anak 2
			SkillTree *Achild9b = newBasicNode(Type, "DEF Up+", 40);
			connectBrother(Achild9a, Achild9b);
			
			// Anak 3
			SkillTree *Achild9c = newBasicNode(Type, "HP Up+", 100);
			connectBrother(Achild9b, Achild9c);
			
			
			/*+==================================================+*/
			/*|                    Level 10                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Achild10a = newSkillNode(Type, "Inner Power", 200, 1.2); // HEAL
			connectChild(Achild9a, Achild10a);
			
			// Anak 2
			SkillTree *Achild10b = newSkillNode(Type, "Channel Nature", 75, 1.2);  // Defense
			connectBrother(Achild10a, Achild10b);
			
			// Anak 3
			SkillTree *Achild10c = newSkillNode(Type, "R.I.P", 300, 1.2); // Attack
			connectBrother(Achild10b, Achild10c);
			
			break;
			
			case CHAR_M :
			/*+==================================================+*/
			/*|                     Level 0                      |*/
			/*+==================================================+*/
			root = newBasicNode(Type, "All Stats Up+", 5);


			/*+==================================================+*/
			/*|                     Level 1                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Mchild1a = newBasicNode(Type, "HP Up+", 20);
            		connectChild(root, Mchild1a);
            
            		// Anak 2
            		SkillTree *Mchild1b = newBasicNode(Type, "DEF Up+", 10);
            		connectBrother(Mchild1a, Mchild1b);
			
			// Anak 3
			SkillTree *Mchild1c = newBasicNode(Type, "Attack Up+", 10);
			connectBrother(Mchild1b, Mchild1c);
			
			
			/*+==================================================+*/
			/*|                     Level 2                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Mchild2a = newSkillNode(Type, "Quick Attack", 20, 1.1); // Attack
			connectChild(Mchild1a, Mchild2a);
			
			
			/*+==================================================+*/
			/*|                     Level 3                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Mchild3a = newBasicNode(Type, "All Stats Up+", 15);
			connectChild(Mchild2a, Mchild3a);
			
			// Anak 2
			SkillTree *Mchild3b = newBasicNode(Type, "HP Up+", 30);
			connectBrother(Mchild3a, Mchild3b);
			
			// Anak 3
			SkillTree *Mchild3c = newBasicNode(Type, "Attack Up+", 10);
			connectBrother(Mchild3b, Mchild3c);
			
			
			/*+==================================================+*/
			/*|                     Level 4                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Mchild4a = newPrecentageNode(Type, "Attack Up%", 1.1);
			connectChild(Mchild3a, Mchild4a);
			
			// Anak 2
			SkillTree *Mchild4b = newPrecentageNode(Type, "HP Up%", 1.2);
			connectBrother(Mchild4a, Mchild4b);
			
			// Anak 3
			SkillTree *Mchild4c = newPrecentageNode(Type, "DEF Up%", 1.1);
			connectBrother(Mchild4b, Mchild4c);
			
			
			/*+==================================================+*/
			/*|                     Level 5                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Mchild5a = newSkillNode(Type, "Holy Grail", 50, 1.1); // Heal
			connectChild(Mchild4a, Mchild5a);
			
			
			/*+==================================================+*/
			/*|                     Level 6                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Mchild6a = newBasicNode(Type, "DEF Up+", 25);
			connectChild(Mchild5a, Mchild6a);
			
			// Anak 2
			SkillTree *Mchild6b = newBasicNode(Type, "Attack Up+", 30);
			connectBrother(Mchild6a, Mchild6b);
			
			// Anak 3
			SkillTree *Mchild6c = newBasicNode(Type, "HP Up+", 45);
			connectBrother(Mchild6b, Mchild6c);
			
			
			/*+==================================================+*/
			/*|                     Level 7                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Mchild7a = newPrecentageNode(Type, "DEF Up%", 1.2);
			connectChild(Mchild6a, Mchild7a);
			
			// Anak 2
			SkillTree *Mchild7b = newPrecentageNode(Type, "Attack Up%", 1.2);
			connectBrother(Mchild7a, Mchild7b);
			
			// Anak 3
			SkillTree *Mchild7c = newPrecentageNode(Type, "HP Up%", 1.3);
			connectBrother(Mchild7b, Mchild7c);
			
			
			/*+==================================================+*/
			/*|                     Level 8                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Mchild8a = newSkillNode(Type, "Flick", 100, 1.1);
			connectChild(Mchild7a, Mchild8a);
			
			
			/*+==================================================+*/
			/*|                     Level 9                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Mchild9a = newBasicNode(Type, "Attack Up+", 60);
			connectChild(Mchild8a, Mchild9a);
			
			// Anak 2
			SkillTree *Mchild9b = newBasicNode(Type, "DEF Up+", 50);
			connectBrother(Mchild9a, Mchild9b);
			
			// Anak 3
			SkillTree *Mchild9c = newBasicNode(Type, "HP Up+", 90);
			connectBrother(Mchild9b, Mchild9c);
			
			
			/*+==================================================+*/
			/*|                    Level 10                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Mchild10a = newSkillNode(Type, "Freedom", 250, 1.2); // Heal
			connectChild(Mchild9a, Mchild10a);
			
			// Anak 2
			SkillTree *Mchild10b = newSkillNode(Type, "Chained Defence", 100, 1.2); // Defense
			connectBrother(Mchild10a, Mchild10b);
			
			// Anak 3
			SkillTree *Mchild10c = newSkillNode(Type, "XX Barrage Attack", 200, 1.2); // Attack
			connectBrother(Mchild10b, Mchild10c);
			break;
			
			case CHAR_D :
			/*+==================================================+*/
			/*|                     Level 0                      |*/
			/*+==================================================+*/
			root = newBasicNode(Type, "DEF Up+", 15);


			/*+==================================================+*/
			/*|                     Level 1                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Dchild1a = newBasicNode(Type, "HP Up+", 20);
            		connectChild(root, Dchild1a);
            
            		// Anak 2
            		SkillTree *Dchild1b = newBasicNode(Type, "DEF Up+", 10);
            		connectBrother(Dchild1a, Dchild1b);
			
			// Anak 3
			SkillTree *Dchild1c = newBasicNode(Type, "Attack Up+", 10);
			connectBrother(Dchild1b, Dchild1c);
			
			
			/*+==================================================+*/
			/*|                     Level 2                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Dchild2a = newSkillNode(Type, "Pressure", 10, 1.1);
			connectChild(Dchild1a, Dchild2a);
			
			
			/*+==================================================+*/
			/*|                     Level 3                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Dchild3a = newBasicNode(Type, "All Stats Up+", 10);
			connectChild(Dchild2a, Dchild3a);
			
			// Anak 2
			SkillTree *Dchild3b = newBasicNode(Type, "HP Up+", 30);
			connectBrother(Dchild3a, Dchild3b);
			
			// Anak 3
			SkillTree *Dchild3c = newBasicNode(Type, "DEF +", 20);
			connectBrother(Dchild3b, Dchild3c);
			
			
			/*+==================================================+*/
			/*|                     Level 4                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Dchild4a = newPrecentageNode(Type, "Attack Up%", 1.1);
			connectChild(Dchild3a, Dchild4a);
			
			// Anak 2
			SkillTree *Dchild4b = newPrecentageNode(Type, "HP Up%", 1.2);
			connectBrother(Dchild4a, Dchild4b);
			
			// Anak 3
			SkillTree *Dchild4c = newPrecentageNode(Type, "DEF Up%", 1.1);
			connectBrother(Dchild4b, Dchild4a);
			
			
			/*+==================================================+*/
			/*|                     Level 5                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Dchild5a = newSkillNode(Type, "Mother Nature", 50, 1.1); // Defense
			connectChild(Dchild4a, Dchild5a);
			
			
			/*+==================================================+*/
			/*|                     Level 6                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Dchild6a = newBasicNode(Type, "DEF Up+", 40);
			connectChild(Dchild5a, Dchild6a);
			
			// Anak 2
			SkillTree *Dchild6b = newBasicNode(Type, "Attack Up+", 30);
			connectBrother(Dchild6a, Dchild6b);
			
			// Anak 3
			SkillTree *Dchild6c = newBasicNode(Type, "HP Up+", 50);
			connectBrother(Dchild6b, Dchild6c);
			
			
			/*+==================================================+*/
			/*|                     Level 7                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Dchild7a = newPrecentageNode(Type, "DEF Up%", 1.3);
			connectChild(Dchild6a, Dchild7a);
			
			// Anak 2
			SkillTree *Dchild7b = newPrecentageNode(Type, "Attack Up%", 1.2);
			connectBrother(Dchild7a, Dchild7b);
			
			// Anak 3
			SkillTree *Dchild7c = newPrecentageNode(Type, "HP Up%", 1.2);
			connectBrother(Dchild7b, Dchild7c);
			
			
			/*+==================================================+*/
			/*|                     Level 8                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Dchild8a = newSkillNode(Type, "Spirit of Will", 100, 1.1);
			connectChild(Dchild7a, Dchild8a);
			
			
			/*+==================================================+*/
			/*|                     Level 9                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Dchild9a = newBasicNode(Type, "Attack Up+", 60);
			connectChild(Dchild8a, Dchild9a);
			
			// Anak 2
			SkillTree *Dchild9b = newBasicNode(Type, "DEF Up+", 60);
			connectBrother(Dchild9a, Dchild9b);
			
			// Anak 3
			SkillTree *Dchild9c = newBasicNode(Type, "HP Up+", 100);
			connectBrother(Dchild9b, Dchild9c);
			
			
			/*+==================================================+*/
			/*|                    Level 10                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *Dchild10a = newSkillNode(Type, "Restore", 200, 1.2); // Heal
			connectChild(Dchild9a, Dchild10a);
			
			// Anak 2
			SkillTree *Dchild10b = newSkillNode(Type, "Prismatic Shield", 999999, 1.2); // Defense
			connectBrother(Dchild10a, Dchild10b);
			
			// Anak 3
			SkillTree *Dchild10c = newSkillNode(Type, "Song of Wind", 200, 1.2); // Attack
			connectBrother(Dchild10b, Dchild10c);
			break;
	}
}

