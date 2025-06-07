/*
.| Program : skilltree.h
.| Berisi data-data variabel yang dibutuhkan untuk Skill Tree
.| 
.| Oleh : Radhitya Maulana Arrafi
*/

#ifndef SKILLTREE_H
#define SKILLTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
	CHAR_A,
	CHAR_M,
	CHAR_D,
}CharType;

typedef enum {
    BASIC_ADDITION,
    PERCENTAGE_ADDITION,
    SKILL_UNLOCK
} NodeType;

typedef struct {
    char description[50];
    int value;
} BasicAddition;

typedef struct {
    char description[50];
    float percentage;
} PercentageAddition;

typedef struct {
    char skillName[50];
    int power;
    float scale;
} SkillUnlock;

typedef struct {
    NodeType nodeType;
    union {
        BasicAddition *basic;
        PercentageAddition *percentage;
        SkillUnlock *skill;
    } data;
} TreeNode;

typedef struct SkillTree SkillTree;

typedef struct SkillTree {
    CharType charType;
    TreeNode *node;
    int isUnlocked;
    struct SkillTree *parent;
    struct SkillTree *firstSon;
    struct SkillTree *nextBrother;
} SkillTree;

SkillTree *initSkillTree(CharType Type);

#endif
