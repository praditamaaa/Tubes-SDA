#ifndef SKILLTREE_BUILDER_H
#define SKILLTREE_BUILDER_H

#inlcude "skilltree.h"

SkillTree *newBasicNode(CharType type, const char *desc, int value);
SkillTree *newPrecentageNode(CharType type, const char *desc, float precentage);
SkillTree *newSkillNode(CharType type, const char *skillName, int power, int scale);
SkillTree *connectChild(SkillTree *parent, SkillTree *child);
SkillTree *connectBrother(SkillTree *left, SkillTree *right);

#endif
