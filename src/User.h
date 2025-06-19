#ifndef USER_H
#define USER_H

/*
	File : user.h 
	desc : menangani segala hal berkaitan dengan CRUD user
	Made by: Praditama Ajmal Hasan
*/

#include<stdio.h>
#include<string.h>
#include"common.h"

#define Nil NULL
#define FILE_NAME "database/users.txt"
#define MAX_STRING 100
#define name(user) ((user)->name)
#define password(user) ((user)->password)
#define score(user) ((user)->score) 
#define next(user) ((user)->next)

addressUser createUser(addressUser head, const STRING name, const STRING password);
void readAllUsers(addressUser head);
void saveToFile(addressUser head, const char* filename);
addressUser loadFromFile(const char* filename);
addressUser deleteUser(addressUser head, const STRING username, const STRING password, const char* filePath);
boolean isUserValid(addressUser head, const STRING username, const STRING password);

#endif
