#ifndef USER_H
#define USER_H

/*
	File : user.h 
	desc : menangani segala hal berkaitan dengan CRUD user
	Made by: Praditama Ajmal Hasan
*/

#include<stdio.h>
#include<string.h>
#include "common.h"
#include "quest.h"
#include "runtime.h"
#include "playablechar.h"

typedef struct user* addressUser;
typedef struct user {
	STRING name;
	STRING password;	
	int score;
	runTimeStats stats;          
    addressQuest questList;      
    addressChar character;
	addressUser next;
} User;

#define Nil NULL
#define FILE_NAME "database/users.txt"
#define USER_SAVE_FOLDER "./database/users/"
#define MAX_STRING 100
#define name(user) ((user)->name)
#define password(user) ((user)->password)
#define score(user) ((user)->score) 
#define stats(user) ((user)->stats)
#define questList(user) ((user)->questList)
#define character(user) ((user)->character)
#define next(user) ((user)->next)

addressUser createUser(addressUser head, const STRING name, const STRING password);
void readAllUsers(addressUser head);
void saveToFile(addressUser head, const char* filename);
addressUser loadFromFile(const char* filename);
addressUser deleteUser(addressUser head, const STRING username, const STRING password, const char* filePath);
boolean isUserValid(addressUser head, const STRING username, const STRING password);
addressChar loadCharacterFromFile(addressUser user);
void saveCharacterToFile(addressUser user);
void saveUserQuests(addressUser user);
void loadUserQuests(addressUser user);
void saveUserStats(addressUser user);
void loadUserStats(addressUser user);
void saveUser(addressUser user);
void loadUser(addressUser user);

#endif
