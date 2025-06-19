/*
.| Program : skilltree_utils.c
.| Implementasi fungsi utility tambahan untuk skilltree
.| 
.| Oleh : Radhitya Maulana Arrafi
*/

#include "skilltree_utils.h"

void freeSkillTree(SkillTree *root) {
    if (root == NULL) return;
    
    // Free semua anak terlebih dahulu
    SkillTree *child = root->firstSon;
    while (child != NULL) {
        SkillTree *nextChild = child->nextBrother;
        freeSkillTree(child);
        child = nextChild;
    }
    
    // Free data node
    if (root->node != NULL) {
        switch (root->node->nodeType) {
            case BASIC_ADDITION:
                if (root->node->data.basic != NULL) {
                    free(root->node->data.basic);
                }
                break;
            case PERCENTAGE_ADDITION:
                if (root->node->data.percentage != NULL) {
                    free(root->node->data.percentage);
                }
                break;
            case SKILL_UNLOCK:
                if (root->node->data.skill != NULL) {
                    free(root->node->data.skill);
                }
                break;
        }
        free(root->node);
    }
    
    // Free node itu sendiri
    free(root);
}

SkillTree* getNodeById(SkillTree *root, int nodeId) {
    int currentId = 0;
    return findNodeById(root, nodeId, &currentId);
}

int canUnlockNode(SkillTree *root, int nodeId) {
    SkillTree *targetNode = getNodeById(root, nodeId);
    
    if (targetNode == NULL) {
        return 0; // Node tidak ditemukan
    }
    
    if (targetNode->isUnlocked) {
        return 0; // Sudah di-unlock
    }
    
    // Cek apakah parent sudah di-unlock
    if (targetNode->parent != NULL && !targetNode->parent->isUnlocked) {
        return 0; // Parent belum di-unlock
    }
    
    return 1; // Bisa di-unlock
}

int unlockNode(SkillTree *root, int nodeId) {
    if (!canUnlockNode(root, nodeId)) {
        return 0; // Tidak bisa di-unlock
    }
    
    SkillTree *targetNode = getNodeById(root, nodeId);
    if (targetNode != NULL) {
        targetNode->isUnlocked = 1;
        return 1;
    }
    
    return 0;
}

void printSkillTreeStatus(SkillTree *root, int level) {
    if (root == NULL) return;
    
    // Print indentasi berdasarkan level
    int i = 0;
    while(i < level){
        printf("  ");
        i++;
    }
    
    // Print status node
    printf("[%s] ", root->isUnlocked ? "UNLOCKED" : "LOCKED");
    
    // Print informasi node berdasarkan tipe
    switch (root->node->nodeType) {
        case BASIC_ADDITION:
            printf("Basic: %s (+%d)\n", 
                   root->node->data.basic->description, 
                   root->node->data.basic->value);
            break;
        case PERCENTAGE_ADDITION:
            printf("Percentage: %s (%.1f%%)\n", 
                   root->node->data.percentage->description, 
                   root->node->data.percentage->percentage * 100);
            break;
        case SKILL_UNLOCK:
            printf("Skill: %s (Power: %d, Scale: %.1f)\n", 
                   root->node->data.skill->skillName, 
                   root->node->data.skill->power, 
                   root->node->data.skill->scale);
            break;
    }
    
    // Print semua anak
    SkillTree *child = root->firstSon;
    while (child != NULL) {
        printSkillTreeStatus(child, level + 1);
        child = child->nextBrother;
    }
}

int getUnlockableNodes(SkillTree *root, int *unlockableIds, int maxId) {
    int count = 0;
    int totalNodes = countNodes(root);

    int i = 0;
    while(i < totalNodes && count < maxId){
        if (canUnlockNode(root, i)) {
            unlockableIds[count] = i;
            count++;
        }
    }
    
    return count;
}

void resetSkillTree(SkillTree *root) {
    if (root == NULL) return;
    
    // Reset node saat ini
    root->isUnlocked = (root->parent == NULL) ? 1 : 0; // Hanya root yang unlocked
    
    // Reset semua anak
    SkillTree *child = root->firstSon;
    while (child != NULL) {
        resetSkillTree(child);
        child = child->nextBrother;
    }
}
