/*
.| Program : skilltree_utils.h
.| Header untuk fungsi utility tambahan untuk skilltree
.| 
.| Oleh : Radhitya Maulana Arrafi
*/

#ifndef SKILLTREE_UTILS_H
#define SKILLTREE_UTILS_H

#include "skilltree.h"
#include "skilltree_save.h"

// Fungsi untuk membebaskan memory skilltree
void freeSkillTree(SkillTree *root);

// Fungsi untuk unlock node (dengan validasi parent)
int unlockNode(SkillTree *root, int nodeId);

// Fungsi untuk mengecek apakah node bisa di-unlock
int canUnlockNode(SkillTree *root, int nodeId);

// Fungsi untuk menampilkan status skilltree
void printSkillTreeStatus(SkillTree *root, int level);

// Fungsi untuk mendapatkan node berdasarkan ID (wrapper yang lebih mudah)
SkillTree* getNodeById(SkillTree *root, int nodeId);

// Fungsi untuk mendapatkan semua node yang bisa di-unlock
int getUnlockableNodes(SkillTree *root, int *unlockableIds, int maxIds);

// Fungsi untuk reset skilltree (unlock hanya root)
void resetSkillTree(SkillTree *root);

#endif
