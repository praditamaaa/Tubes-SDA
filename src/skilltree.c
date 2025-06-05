#include "skilltree.h"

SkillTree *initSkillTree(CharType Type){
	SkillTree *root = NULL;
	
	switch(Type){
		case CHAR_A{
			// ROOT or LV 0
			root = newBasicNode(Type, "Attack Up+", 20);

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
			SkillTree *child1c = newBasicNode(Type, "Attack Up+", 15);
			connectBrother(child1b, child1c);
			
			/*+==================================================+*/
			/*|                     Level 2                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child2a = newSkillNode(Type, "Continous Attack", 20, 1.2);
			connectChild(child1a, child2a);
			
			/*+==================================================+*/
			/*|                     Level 1                      |*/
			/*+==================================================+*/
			// Anak 1
			SkillTree child3a = newBasicNode(Type, "All Stats Up+", 10);
			connectChild(child2a, child3a);
			
			// Anak 2
			SkillTree child3b = newBasicNode(Type, "HP Up+", 20);
			connectBrother(child3a, child3b);
			
			// Anak 3
			SkillTree child3c = newBasicNode 
			
			
			
			break;
		}
		case CHAR_M{
			break;
		}
		case CHAR_D{
			break;
		}
	}
}


