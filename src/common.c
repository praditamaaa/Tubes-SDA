#include "common.h"

void clearScreen() {
    system("cls");
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void getTerminalSize(int *width, int *height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        *width = csbi.srWindow.Right - csbi.srWindow.Left;
        *height = csbi.srWindow.Bottom - csbi.srWindow.Top;
    }
}

// Versi tanpa newline dan dengan posisi baris
void printCenteredAtRow(const char* text, int row) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    GetConsoleScreenBufferInfo(hOut, &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    
    // Bersihkan seluruh baris dulu
    COORD pos = { 0, (SHORT)row };
    SetConsoleCursorPosition(hOut, pos);
    int i;
    for(i = 0; i < columns; i++) printf(" ");
    
    // Baru print teks yang diinginkan
    int padding = (columns - (int)strlen(text)) / 2;
    if (padding < 0) padding = 0;
    pos.X = (SHORT)padding;
    SetConsoleCursorPosition(hOut, pos);
    printf("%s", text);
    fflush(stdout);
}

// Fungsi untuk membersihkan area input
void clearInputArea() {
    int i;
	for(i = 20; i <= 26; i++) {
        gotoxy(113, i);
        printf("  ");
    }
}
