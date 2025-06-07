/*
.| Program : skilltree_save.h
.| Header untuk modul penyimpanan dan pemuatan data unlock status skilltree
.| 
.| Oleh : Radhitya Maulana Arrafi
*/

#ifndef SKILLTREE_SAVE_H
#define SKILLTREE_SAVE_H

#include "skilltree.h"

// Konstanta untuk nama file berdasarkan CharType
#define SAVE_FILE_CHAR_A "skilltree_char_a.dat"
#define SAVE_FILE_CHAR_M "skilltree_char_m.dat"
#define SAVE_FILE_CHAR_D "skilltree_char_d.dat"

// Struktur untuk menyimpan data node dalam file
typedef struct {
    int nodeId;         // ID unik untuk setiap node (berdasarkan posisi dalam tree)
    int isUnlocked;     // Status unlock (0 = locked, 1 = unlocked)
    NodeType nodeType;  // Tipe node untuk validasi
} NodeSaveData;

// Fungsi untuk menyimpan skilltree ke file
int saveSkillTree(SkillTree *root, CharType charType);

// Fungsi untuk memuat skilltree dari file
int loadSkillTree(SkillTree *root, CharType charType);

// Fungsi helper untuk mendapatkan nama file berdasarkan CharType
const char* getFileName(CharType charType);

// Fungsi untuk menghitung jumlah node dalam tree
int countNodes(SkillTree *root);

// Fungsi untuk menggenerate ID unik untuk setiap node (traversal pre-order)
void assignNodeIds(SkillTree *root, int *currentId);

// Fungsi untuk mencari node berdasarkan ID
SkillTree* findNodeById(SkillTree *root, int targetId, int *currentId);

// Fungsi untuk membuat file save baru jika belum ada
int createDefaultSaveFile(CharType charType);

#endif
