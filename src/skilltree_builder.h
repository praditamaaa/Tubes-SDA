/*
.| Program : skilltree_builder.h
.| Header yang berisikan modul untuk membuat SkillTree
.| dengan data dari skilltree.h
.|
.| Oleh : Radhitya Maulana Arrafi
*/

#ifndef SKILLTREE_BUILDER_H
#define SKILLTREE_BUILDER_H

#include "skilltree.h"

SkillTree *newBasicNode(CharType type, const char *desc, int value);
SkillTree *newPrecentageNode(CharType type, const char *desc, float precentage);
SkillTree *newSkillNode(CharType type, const char *skillName, int power, float scale);
SkillTree *connectChild(SkillTree *parent, SkillTree *child);
SkillTree *connectBrother(SkillTree *left, SkillTree *right);

#endif
