/*
.| Program : skilltree_builder.c
.| Berisi logika atau isi modul skilltree_builder.h 
.| menggunakan data-data dari header skilltree.h
.|
.| Tujuan : Mebuat logika yang berkaitan dengan 
.| 			pembuatan SkillTree di skilltree.c
.|
.| Oleh : Radhitya Maulana Arrafi
*/

#include "skilltree_builder.h"

SkillTree *newBasicNode(CharType type, const char *desc, int value){
    SkillTree *node = malloc(sizeof(SkillTree));
    
    node->charType = type;
    node->isUnlocked = 0;
    node->parent = NULL;
    node->firstSon = NULL;
    node->nextBrother = NULL;

    node->node = malloc(sizeof(TreeNode));
    node->node->nodeType = BASIC_ADDITION;
    node->node->data.basic = malloc(sizeof(BasicAddition));
    strcpy(node->node->data.basic->description, desc);
    node->node->data.basic->value = value;

    return node;
}

SkillTree *newPercentageNode(CharType type, const char *desc, float percentage) {
    SkillTree *node = malloc(sizeof(SkillTree));
    node->charType = type;
    node->isUnlocked = 0;
    node->parent = NULL;
    node->firstSon = NULL;
    node->nextBrother = NULL;

    node->node = malloc(sizeof(TreeNode));
    node->node->nodeType = PERCENTAGE_ADDITION;
    node->node->data.percentage = malloc(sizeof(PercentageAddition));

    strcpy(node->node->data.percentage->description, desc);
    node->node->data.percentage->percentage = percentage;

    return node;
}

SkillTree *newSkillNode(CharType type, const char *skillName, int power, float scale) {
    SkillTree *node = malloc(sizeof(SkillTree));
    node->charType = type;
    node->isUnlocked = 0;
    node->parent = NULL;
    node->firstSon = NULL;
    node->nextBrother = NULL;

    node->node = malloc(sizeof(TreeNode));
    node->node->nodeType = SKILL_UNLOCK;
    node->node->data.skill = malloc(sizeof(SkillUnlock));

    strcpy(node->node->data.skill->skillName, skillName);
    node->node->data.skill->power = power;
    node->node->data.skill->scale = scale;

    return node;
}

void connectChild(SkillTree *parent, SkillTree *child) {
    parent->firstSon = child;
    child->parent = parent;
}

void connectBrother(SkillTree *left, SkillTree *right) {
    left->nextBrother = right;
    right->parent = left->parent; // Asumsikan satu parent
}
