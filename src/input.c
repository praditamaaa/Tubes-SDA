/*
.| Program : input.c
.| Berisi logika atau isi modul dari data header input.h 
.|
.| Tujuan : menghandle input keyboard
.| 
.| Oleh : Afriza Choirie Saputra
*/

#include "input.h"
char getInput() {
    return getch();
}

Direction inputToDirection(char input) {
    switch(input) {
        case 'w': case 'W': case 72: 
            return UP;
        case 's': case 'S': case 80: 
            return DOWN;
        case 'a': case 'A': case 75: 
            return LEFT;
        case 'd': case 'D': case 77: 
            return RIGHT;
        default:
            return UP; 
    }
}

bool isValidInput(char key) {
    return (key == 'w' || key == 'W' || key == 72 ||  // ATAS
            key == 's' || key == 'S' || key == 80 ||  // BWH
            key == 'a' || key == 'A' || key == 75 ||  // KIRI
            key == 'd' || key == 'D' || key == 77 ||  // KAAN
            key == 'z' || key == 'Z' ||               // INTERAKSI
            key == 27 ||                              // ESC
            key == 'q' || key == 'Q');                // QUIT
}
