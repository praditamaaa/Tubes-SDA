#include "User.h"

addressUser createUser(addressUser head, const STRING name, const STRING password) {
	addressUser newUser = (addressUser) malloc(sizeof(User));
	name(newUser) = strdup(name);
	password(newUser) = strdup(password);
	score(newUser) = 0;
	
	memset(&stats(newUser), 0, sizeof(RuntimeStats));
	questList(newUser) = Nil;
	memset(&character(newUser), 0, sizeof(tChar));
	next(newUser) = Nil;
	
	if(head == Nil) {
		return newUser;
	}
	
	addressUser temp = head;
	while (next(temp) != Nil) {
		temp = next(temp);
	}
	next(temp) = newUser;
	return head;
}

void readAllUsers(addressUser head) {
	if (head == Nil) {
		printf("Belum ada user");
		return;
	}
	
	int i = 1;
	while (head != Nil) {
		printf("%d. Nama: %s | Score: %d\n", 
		i++, name(head), score(head));
		head = next(head);
	}
}

void saveToFile(addressUser head, const char* filename) {
	FILE* fp = fopen(filename, "w");
	
	if(fp == Nil) {
		printf("Gagal menyimpan ke file.\n");
	}
	
	while(head != Nil) {
		fprintf(fp, "%s|%s|%d\n", name(head), password(head), score(head));
		head = next(head);
	}
	
	fclose(fp);
	printf("Data berhasail dismpan.\n");
}

addressUser loadFromFile(const char* filename) {
	FILE* fp = fopen(filename, "r");
	if (fp == Nil) {
		printf("Belum ada user");
		return Nil;
	}
	
	addressUser head = Nil;
	char line[3 * MAX_STRING];
	char name[MAX_STRING];
	char password[MAX_STRING];
	int score;
	
	while (fgets(line, sizeof(line), fp)) {
		if (sscanf(line, "%[^|]|%[^|]|%d", name, password, &score) == 3) {
			name[strcspn(name, "\n")] = '\0';
			password[strcspn(password, "\n")] = '\0';
			
			addressUser newUser = (addressUser)malloc(sizeof(User));
			newUser->name = strdup(name);
			newUser->password = strdup(password);
			newUser->score = score;
			newUser->next = Nil;
			
			memset(&newUser->stats, 0, sizeof(RuntimeStats));
            newUser->questList = Nil;
            memset(&newUser->character, 0, sizeof(tChar));
			
            if (head == NULL) {
                head = newUser;
            } else {
                addressUser temp = head;
                while (temp->next != NULL) temp = temp->next;
                temp->next = newUser;
            }
		}
	}
	
	fclose(fp);
	printf("Data user berhasil dimuat.\n", filename);
	return head;
}

addressUser deleteUser(addressUser head, const STRING username, const STRING password, const char* filePath) {
	if (head == Nil) {
        printf("Tidak ada data user.\n");
        return head;
    }
	
	addressUser current = head;
	addressUser prev = Nil;
	
	while (current != Nil) {
		if (strcmp(name(current), username) == 0) {
			if (strcmp(password(current), password) == 0) {
				if (prev == Nil) {
					head = next(current);
				} else {
					next(prev) = next(current);
				}
				
				printf("Akun '%s' berhasil dihapus.\n", username);
				free(name(current));
				free(password(current));
				free(current);
				
				saveToFile(head, filePath);
                return head;
			} else {
                printf("Password salah. Akun tidak dihapus.\n");
                return head;
            }
        }

        prev = current;
        current = next(current);
    }

    printf("Username tidak ditemukan.\n");
    return head;	
}

boolean isUserValid(addressUser head, const STRING username, const STRING password) {
    while (head != Nil) {
        if (strcmp(name(head), username) == 0 && strcmp(password(head), password) == 0) {
            return true;
        }
        head = next(head);
    }
    return false;
}
