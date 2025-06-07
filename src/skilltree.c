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
		case CHAR_A{
			/*+==================================================+*/
			/*|                     Level 0                      |*/
			/*+==================================================+*/
			root = newBasicNode(Type, "Attack Up+", 20);


			/*+==================================================+*/
			/*|                     Level 1                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *child1a = newBasicNode(Type, "HP Up+", 20);
            		connectChild(root, child1a);
            
            		// Anak 2
            		SkillTree *child1b = newBasicNode(Type, "DEF Up+", 5);
            		connectBrother(child1a, child1b);
			
			// Anak 3
			SkillTree *child1c = newBasicNode(Type, "Attack Up+", 15);
			connectBrother(child1b, child1c);
			
			
			/*+==================================================+*/
			/*|                     Level 2                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child2a = newSkillNode(Type, "Continous Attack", 10, 1.1); // Attack
			connectChild(child1a, child2a);
			
			
			/*+==================================================+*/
			/*|                     Level 3                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child3a = newBasicNode(Type, "All Stats Up+", 10);
			connectChild(child2a, child3a);
			
			// Anak 2
			SkillTree child3b = newBasicNode(Type, "HP Up+", 20);
			connectBrother(child3a, child3b);
			
			// Anak 3
			SkillTree child3c = newBasicNode(Type, "DEF Up+", 10);
			connectBrother(child3b, child3c);
			
			
			/*+==================================================+*/
			/*|                     Level 4                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child4a = newPrecentageNode(Type, "Attack Up%", 1.1);
			connectChild(child3a, child4a);
			
			// Anak 2
			SkillTree child4b = newPrecentageNode(Type, "HP Up%", 1.2);
			connectBrother(child4a, child4b);
			
			// Anak 3
			SkillTree child4c = newPrecentageNode(Type, "DEF Up%", 1.1);
			connectBrother(child4b, cbild4a);
			
			
			/*+==================================================+*/
			/*|                     Level 5                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child5a = newSkillNode(Type, "Quick Pierce", 50, 1.1); // Attack
			connectChild(child4a, child5a);
			
			
			/*+==================================================+*/
			/*|                     Level 6                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child6a = newBasicNode(Type, "DEF Up+", 20);
			connectChild(child5a, child6a);
			
			// Anak 2
			SkillTree child6b = newBasicNode(Type, "Attack Up+", 40);
			connectBrother(child6a, child6b);
			
			// Anak 3
			SkillTree child6c = newBasicNode(Type, "HP Up+", 50);
			connectBrother(child6b, child6c);
			
			
			/*+==================================================+*/
			/*|                     Level 7                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child7a = newPrecentageNode(Type, "DEF Up%", 1.2);
			connectChild(child6a, child7a);
			
			// Anak 2
			SkillTree child7b = newPrecentageNode(Type, "Attack Up%", 1.3);
			connectBrother(child7a, child7b);
			
			// Anak 3
			SkillTree child7c = newPrecentageNode(Type, "HP Up%", 1.2);
			connectBrother(child7b, child7c);
			
			
			/*+==================================================+*/
			/*|                     Level 8                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child8a = newSkillNode(Type, "X Slash", 100, 1.1);
			connectChild(child7a, child8a);
			
			
			/*+==================================================+*/
			/*|                     Level 9                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child9a = newBasicNode(Type, "Attack Up+", 80);
			connectChild(child8a, child9a);
			
			// Anak 2
			SkillTree child9b = newBasicNode(Type, "DEF Up+", 40);
			connectBrother(child9a, child9b);
			
			// Anak 3
			SkillTree child9c = newBasicNode(type, "HP Up+", 100);
			connectBrother(child9b, child9c);
			
			
			/*+==================================================+*/
			/*|                    Level 10                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child10a = newSkillNode(Type, "Inner Power", 200, 1.2); // HEAL
			connectChild(child9a, child10a);
			
			// Anak 2
			SkillTree child10b = newSkillNode(Type, "Channel Nature", 75, 1.2);  // Defense
			connectBrother(child10a, child10b);
			
			// Anak 3
			SkillTree child10c = newSkillNode(Type, "R.I.P", 300, 1.2); // Attack
			connectBrother(child10b, child10c);
			
			break;
			}
			case CHAR_M{
			/*+==================================================+*/
			/*|                     Level 0                      |*/
			/*+==================================================+*/
			root = newBasicNode(Type, "All Stats Up+", 5);


			/*+==================================================+*/
			/*|                     Level 1                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *child1a = newBasicNode(Type, "HP Up+", 20);
            		connectChild(root, child1a);
            
            		// Anak 2
            		SkillTree *child1b = newBasicNode(Type, "DEF Up+", 10);
            		connectBrother(child1a, child1b);
			
			// Anak 3
			SkillTree *child1c = newBasicNode(Type, "Attack Up+", 10);
			connectBrother(child1b, child1c);
			
			
			/*+==================================================+*/
			/*|                     Level 2                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child2a = newSkillNode(Type, "Quick Attack", 20, 1.1); // Attack
			connectChild(child1a, child2a);
			
			
			/*+==================================================+*/
			/*|                     Level 3                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child3a = newBasicNode(Type, "All Stats Up+", 15);
			connectChild(child2a, child3a);
			
			// Anak 2
			SkillTree child3b = newBasicNode(Type, "HP Up+", 30);
			connectBrother(child3a, child3b);
			
			// Anak 3
			SkillTree child3c = newBasicNode(Type, "Attack Up+", 10);
			connectBrother(child3b, child3c);
			
			
			/*+==================================================+*/
			/*|                     Level 4                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child4a = newPrecentageNode(Type, "Attack Up%", 1.1);
			connectChild(child3a, child4a);
			
			// Anak 2
			SkillTree child4b = newPrecentageNode(Type, "HP Up%", 1.2);
			connectBrother(child4a, child4b);
			
			// Anak 3
			SkillTree child4c = newPrecentageNode(Type, "DEF Up%", 1.1);
			connectBrother(child4b, cbild4a);
			
			
			/*+==================================================+*/
			/*|                     Level 5                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child5a = newSkillNode(Type, "Holy Grail", 50, 1.1); // Heal
			connectChild(child4a, child5a);
			
			
			/*+==================================================+*/
			/*|                     Level 6                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child6a = newBasicNode(Type, "DEF Up+", 25);
			connectChild(child5a, child6a);
			
			// Anak 2
			SkillTree child6b = newBasicNode(Type, "Attack Up+", 30);
			connectBrother(child6a, child6b);
			
			// Anak 3
			SkillTree child6c = newBasicNode(Type, "HP Up+", 45);
			connectBrother(child6b, child6c);
			
			
			/*+==================================================+*/
			/*|                     Level 7                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child7a = newPrecentageNode(Type, "DEF Up%", 1.2);
			connectChild(child6a, child7a);
			
			// Anak 2
			SkillTree child7b = newPrecentageNode(Type, "Attack Up%", 1.2);
			connectBrother(child7a, child7b);
			
			// Anak 3
			SkillTree child7c = newPrecentageNode(Type, "HP Up%", 1.3);
			connectBrother(child7b, child7c);
			
			
			/*+==================================================+*/
			/*|                     Level 8                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child8a = newSkillNode(Type, "Flick", 100, 1.1);
			connectChild(child7a, child8a);
			
			
			/*+==================================================+*/
			/*|                     Level 9                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child9a = newBasicNode(Type, "Attack Up+", 60);
			connectChild(child8a, child9a);
			
			// Anak 2
			SkillTree child9b = newBasicNode(Type, "DEF Up+", 50);
			connectBrother(child9a, child9b);
			
			// Anak 3
			SkillTree child9c = newBasicNode(type, "HP Up+", 90);
			connectBrother(child9b, child9c);
			
			
			/*+==================================================+*/
			/*|                    Level 10                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child10a = newSkillNode(Type, "Freedom", 250, 1.2); // Heal
			connectChild(child9a, child10a);
			
			// Anak 2
			SkillTree child10b = newSkillNode(Type, "Chained Defence", 100, 1.2); // Defense
			connectBrother(child10a, child10b);
			
			// Anak 3
			SkillTree child10c = newSkillNode(Type, "XX Barrage Attack", 200, 1.2); // Attack
			connectBrother(child10b, child10c);
			break;
			}
			case CHAR_D{
			/*+==================================================+*/
			/*|                     Level 0                      |*/
			/*+==================================================+*/
			root = newBasicNode(Type, "DEF Up+", 15);


			/*+==================================================+*/
			/*|                     Level 1                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree *child1a = newBasicNode(Type, "HP Up+", 20);
            		connectChild(root, child1a);
            
            		// Anak 2
            		SkillTree *child1b = newBasicNode(Type, "DEF Up+", 10);
            		connectBrother(child1a, child1b);
			
			// Anak 3
			SkillTree *child1c = newBasicNode(Type, "Attack Up+", 10);
			connectBrother(child1b, child1c);
			
			
			/*+==================================================+*/
			/*|                     Level 2                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child2a = newSkillNode(Type, "Pressure", 10, 1.1);
			connectChild(child1a, child2a);
			
			
			/*+==================================================+*/
			/*|                     Level 3                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child3a = newBasicNode(Type, "All Stats Up+", 10);
			connectChild(child2a, child3a);
			
			// Anak 2
			SkillTree child3b = newBasicNode(Type, "HP Up+", 30);
			connectBrother(child3a, child3b);
			
			// Anak 3
			SkillTree child3c = newBasicNode(Type, "DEF +", 20);
			connectBrother(child3b, child3c);
			
			
			/*+==================================================+*/
			/*|                     Level 4                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child4a = newPrecentageNode(Type, "Attack Up%", 1.1);
			connectChild(child3a, child4a);
			
			// Anak 2
			SkillTree child4b = newPrecentageNode(Type, "HP Up%", 1.2);
			connectBrother(child4a, child4b);
			
			// Anak 3
			SkillTree child4c = newPrecentageNode(Type, "DEF Up%", 1.1);
			connectBrother(child4b, cbild4a);
			
			
			/*+==================================================+*/
			/*|                     Level 5                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child5a = newSkillNode(Type, "Mother Nature", 50, 1.1); // Defense
			connectChild(child4a, child5a);
			
			
			/*+==================================================+*/
			/*|                     Level 6                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child6a = newBasicNode(Type, "DEF Up+", 40);
			connectChild(child5a, child6a);
			
			// Anak 2
			SkillTree child6b = newBasicNode(Type, "Attack Up+", 30);
			connectBrother(child6a, child6b);
			
			// Anak 3
			SkillTree child6c = newBasicNode(Type, "HP Up+", 50);
			connectBrother(child6b, child6c);
			
			
			/*+==================================================+*/
			/*|                     Level 7                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child7a = newPrecentageNode(Type, "DEF Up%", 1.3);
			connectChild(child6a, child7a);
			
			// Anak 2
			SkillTree child7b = newPrecentageNode(Type, "Attack Up%", 1.2);
			connectBrother(child7a, child7b);
			
			// Anak 3
			SkillTree child7c = newPrecentageNode(Type, "HP Up%", 1.2);
			connectBrother(child7b, child7c);
			
			
			/*+==================================================+*/
			/*|                     Level 8                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child8a = newSkillNode(Type, "Spirit of Will", 100, 1.1);
			connectChild(child7a, child8a);
			
			
			/*+==================================================+*/
			/*|                     Level 9                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child9a = newBasicNode(Type, "Attack Up+", 60);
			connectChild(child8a, child9a);
			
			// Anak 2
			SkillTree child9b = newBasicNode(Type, "DEF Up+", 60);
			connectBrother(child9a, child9b);
			
			// Anak 3
			SkillTree child9c = newBasicNode(type, "HP Up+", 100);
			connectBrother(child9b, child9c);
			
			
			/*+==================================================+*/
			/*|                    Level 10                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child10a = newSkillNode(Type, "Restore", 200, 1.2); // Heal
			connectChild(child9a, child10a);
			
			// Anak 2
			SkillTree child10b = newSkillNode(Type, "Prismatic Shield", 999999, 1.2); // Defense
			connectBrother(child10a, child10b);
			
			// Anak 3
			SkillTree child10c = newSkillNode(Type, "Song of Wind", 200, 1.2); // Attack
			connectBrother(child10b, child10c);
			break;
		}
	}
}

