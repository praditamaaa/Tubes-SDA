/*
.| Program : skilltree_save.c
.| Implementasi modul penyimpanan dan pemuatan data unlock status skilltree
.| 
.| Oleh : Radhitya Maulana Arrafi
*/

#include "skilltree_save.h"

const char* getFileName(CharType charType) {
    switch(charType) {
        case CHAR_A:
            return SAVE_FILE_CHAR_A;
        case CHAR_M:
            return SAVE_FILE_CHAR_M;
        case CHAR_D:
            return SAVE_FILE_CHAR_D;
        default:
            return NULL;
    }
}

int countNodes(SkillTree *root) {
    if (root == NULL) return 0;
    
    int count = 1; // Hitung node saat ini
    
    // Hitung semua anak
    SkillTree *child = root->firstSon;
    while (child != NULL) {
        count += countNodes(child);
        child = child->nextBrother;
    }
    
    return count;
}

void assignNodeIds(SkillTree *root, int *currentId) {
    if (root == NULL) return;
    
    // Assign ID untuk node saat ini
    // Kita akan menggunakan alamat node sebagai identifier sementara
    // dan menyimpan ID dalam urutan traversal
    
    // Traverse anak-anak
    SkillTree *child = root->firstSon;
    while (child != NULL) {
        (*currentId)++;
        assignNodeIds(child, currentId);
        child = child->nextBrother;
    }
}

SkillTree* findNodeById(SkillTree *root, int targetId, int *currentId) {
    if (root == NULL) return NULL;
    
    if (*currentId == targetId) {
        return root;
    }
    
    (*currentId)++;
    
    // Cari di anak-anak
    SkillTree *child = root->firstSon;
    while (child != NULL) {
        SkillTree *found = findNodeById(child, targetId, currentId);
        if (found != NULL) return found;
        child = child->nextBrother;
    }
    
    return NULL;
}

void saveNodeData(SkillTree *root, FILE *file, int *currentId) {
    if (root == NULL) return;
    
    NodeSaveData data;
    data.nodeId = *currentId;
    data.isUnlocked = root->isUnlocked;
    data.nodeType = root->node->nodeType;
    
    fwrite(&data, sizeof(NodeSaveData), 1, file);
    (*currentId)++;
    
    // Simpan data anak-anak
    SkillTree *child = root->firstSon;
    while (child != NULL) {
        saveNodeData(child, file, currentId);
        child = child->nextBrother;
    }
}

int saveSkillTree(SkillTree *root, CharType charType) {
    if (root == NULL) {
        printf("Error: SkillTree root is NULL\n");
        return 0;
    }
    
    const char *filename = getFileName(charType);
    if (filename == NULL) {
        printf("Error: Invalid CharType\n");
        return 0;
    }
    
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error: Cannot open file %s for writing\n", filename);
        return 0;
    }
    
    // Hitung jumlah node dan tulis ke file
    int nodeCount = countNodes(root);
    fwrite(&nodeCount, sizeof(int), 1, file);
    
    // Tulis CharType untuk validasi
    fwrite(&charType, sizeof(CharType), 1, file);
    
    // Simpan data setiap node
    int currentId = 0;
    saveNodeData(root, file, &currentId);
    
    fclose(file);
    printf("SkillTree data saved successfully to %s\n", filename);
    return 1;
}

void loadNodeData(SkillTree *root, FILE *file, int nodeCount) {
    NodeSaveData data;
    
    for (int i = 0; i < nodeCount; i++) {
        if (fread(&data, sizeof(NodeSaveData), 1, file) != 1) {
            printf("Error reading node data\n");
            return;
        }
        
        // Cari node dengan ID yang sesuai
        int currentId = 0;
        SkillTree *targetNode = findNodeById(root, data.nodeId, &currentId);
        
        if (targetNode != NULL && targetNode->node->nodeType == data.nodeType) {
            targetNode->isUnlocked = data.isUnlocked;
        } else {
            printf("Warning: Node with ID %d not found or type mismatch\n", data.nodeId);
        }
    }
}

int loadSkillTree(SkillTree *root, CharType charType) {
    if (root == NULL) {
        printf("Error: SkillTree root is NULL\n");
        return 0;
    }
    
    const char *filename = getFileName(charType);
    if (filename == NULL) {
        printf("Error: Invalid CharType\n");
        return 0;
    }
    
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Save file %s not found, creating default file\n", filename);
        return createDefaultSaveFile(charType);
    }
    
    // Baca jumlah node
    int nodeCount;
    if (fread(&nodeCount, sizeof(int), 1, file) != 1) {
        printf("Error reading node count from %s\n", filename);
        fclose(file);
        return 0;
    }
    
    // Baca dan validasi CharType
    CharType savedCharType;
    if (fread(&savedCharType, sizeof(CharType), 1, file) != 1) {
        printf("Error reading CharType from %s\n", filename);
        fclose(file);
        return 0;
    }
    
    if (savedCharType != charType) {
        printf("Error: CharType mismatch in save file %s\n", filename);
        fclose(file);
        return 0;
    }
    
    // Muat data node
    loadNodeData(root, file, nodeCount);
    
    fclose(file);
    printf("SkillTree data loaded successfully from %s\n", filename);
    return 1;
}

int createDefaultSaveFile(CharType charType) {
    const char *filename = getFileName(charType);
    if (filename == NULL) {
        printf("Error: Invalid CharType\n");
        return 0;
    }
    
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error: Cannot create default save file %s\n", filename);
        return 0;
    }
    
    // Buat skilltree default untuk menghitung node
    SkillTree *tempTree = initSkillTree(charType);
    int nodeCount = countNodes(tempTree);
    
    // Tulis header
    fwrite(&nodeCount, sizeof(int), 1, file);
    fwrite(&charType, sizeof(CharType), 1, file);
    
    // Tulis data default (semua node locked kecuali root)
    for (int i = 0; i < nodeCount; i++) {
        NodeSaveData data;
        data.nodeId = i;
        data.isUnlocked = (i == 0) ? 1 : 0; // Hanya root yang unlocked
        data.nodeType = BASIC_ADDITION; // Default type
        fwrite(&data, sizeof(NodeSaveData), 1, file);
    }
    
    fclose(file);
    
    // Cleanup temporary tree (perlu implementasi free function)
    // freeSkillTree(tempTree);
    
    printf("Default save file %s created\n", filename);
    return 1;
}
