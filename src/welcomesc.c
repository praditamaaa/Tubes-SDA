#include "welcomesc.h"

/*void tampilkanASCII() {
    printCenteredAtRow("                                                                                                    ",1);
    printCenteredAtRow("                                                                                                    ",2);
    printCenteredAtRow("                                                                                                    ",3);
    printCenteredAtRow(":::::      :::::  ::::::  :::: :::::::::::: :::::   ::::::   :::::::::    :::::::::        :::::    ",4);
    printCenteredAtRow(" :::::    ::::::    ::::  ::   ::  ::::  ::  :::     ::::  ::::     ::::   :::  ::::      ::::::    ",5);
    printCenteredAtRow(" :;::::  ;:;:::;     ::::::        ::::      :::     ;:::  ::::     ;::;;  :::  ::::     ;:: ::::   ",6);
    printCenteredAtRow(" ;; ;;;;;;;:;;;;       ;;;         ;;;;      ;;;;::;;;;;; ;;;;;      ;;;;  ;;;;;;;       ;;  ;;;;;  ",7);
    printCenteredAtRow(" ;;  ;;;;; ;;;;;       ;;;         ;;;;      ;;;     ;;;;  ;;;;      ;;;   ;;; ;;;;;    ;;;   ;;;;  ",8);
    printCenteredAtRow(" ;;  ;;;;  ;;;;;      ;;;;         ;;;;      ;;;;    ;;;;   ;;;;;  ;;;;   ;;;;; ;;;;;  ;;;     ;;;; ",9);
    printCenteredAtRow(";;;;   ;   ;;;;;     ;;;;;;       ;;;;;;    ;;;;;   ;;;;;;     ;;;;;      ;;;;;   ;;;;;;;;;   ;;;;;;",10);
    printCenteredAtRow("                                                                                                    ",11);
    printCenteredAtRow("                                                                                                    ",12);
    printCenteredAtRow("                                                                                                    ",13);
}

void welcomeScreen(addressChar* k) {
	const char* loadingFrames[] = {
        "Tekan Enter untuk Memulai   ",
        "Tekan Enter untuk Memulai.  ",
        "Tekan Enter untuk Memulai.. ",
        "Tekan Enter untuk Memulai...",
    };
    int frame = 0;

    // Tentukan baris tempat teks akan ditampilkan (di bawah ASCII art)
    int row = 16; 

    int numFrames = sizeof(loadingFrames) / sizeof(loadingFrames[0]); // frame = 3

    while (1) {
        char fullText[100];
        snprintf(fullText, sizeof(fullText), "%s", loadingFrames[frame]);
        
        tampilkanASCII();
        printCenteredAtRow(fullText, row);

        Sleep(1000);
        frame = (frame + 1) % numFrames;

        if (_kbhit()) {
            if (_getch() == '\r') { 
            	inputNama(k);
                break;
            }
        }
    }
}

void inputNama(addressChar* k){
    int frame = 0;
    int row = 16; 
    char Nama[100];
    printCenteredAtRow("Input Nama: ", row);
    scanf("%99s", Nama); 
    getchar(); 
    
    menuUser(k); 
}
*/
