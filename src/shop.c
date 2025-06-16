#include "shop.h"

void tambahkanItem(addressShopItem shop[]){
	shop[0].Type = HealPotion;
    strcpy(shop[0].item, "Healing Potion");
    shop[0].effect.heal.amount = 50;
    shop[0].stock = 5;
    shop[0].price = 25;

    shop[1].Type = BurnPotion;
    strcpy(shop[1].item, "Fire Potion");
    shop[1].effect.status.type = STATUS_BURN;
    shop[1].effect.status.damage = 15;
    shop[1].effect.status.duration = 3;
    shop[1].stock = 4;
    shop[1].price = 45;

    shop[2].Type = FreezePotion;
    strcpy(shop[2].item, "Ice Potion");
    shop[2].effect.status.type = STATUS_FREEZE;
    shop[2].effect.status.damage = 10;
    shop[2].effect.status.duration = 2;
    shop[2].stock = 3;
    shop[2].price = 50;
}
	
void pakaiItem(addressShopItem i){
    switch (i.Type) {
        case HealPotion:
            printf(">> Menyembuhkan HP sebanyak %d poin.\n", i.effect.heal.amount);
            break;
        case BurnPotion:
        	printf(">> Membakar musuh selama %d turn.\n", i.effect.status.duration);
            break;
        case FreezePotion:
        	printf(">> Membekukan musuh selama %d turn.\n", i.effect.status.duration);
            break;
        default:
            printf(">> Tidak ada efek.\n");
    }
}

void tampilkanItem(addressShopItem shop[]) {   
    int Xawal = 113;  
    int Yawal = 10;  
    
    for (int i = 0; i < ITEM; i++) {
        gotoxy(Xawal, Yawal + i);  // setiap item turun 1 baris
        printf("%d. %s (Stok: %d)", i + 1, shop[i].item, shop[i].stock);
    }
}

void tambahkanItemKeInventoryKarakter(addressChar* karakter, addressShopItem shop, int jumlahDibeli){
    addressItem newItem;
    buatItem(&newItem);
    Isi_item(&newItem, shop.item, jumlahDibeli, shop.Type, shop.effect);
    tambahItem(&((*karakter)->inventory), newItem);
}

// Fungsi untuk menampilkan gold karakter
void tampilkanGold(addressChar* karakter, int x, int y) {
    gotoxy(x, y);
    printf("Gold Anda: %d", (*karakter)->Gold);
}

// Fungsi untuk menghitung total harga
int hitungTotalHarga(addressShopItem shop, int jumlah) {
    return shop.price * jumlah;
}

// Fungsi untuk memproses pembayaran
int prosesPembayaran(addressChar* karakter, int totalHarga) {
    if ((*karakter)->Gold >= totalHarga) {
        (*karakter)->Gold -= totalHarga;
        return 1; // Pembayaran berhasil
    }
    return 0; // Gold tidak cukup
}

int inputUser(){
    int pilihan;
    gotoxy(113, 20); // Posisi input di area yang kosong
    printf("Pilih nomor item (1-%d): ", ITEM);
    scanf("%d", &pilihan);
    return pilihan;
}

int inputJumlahItem(){
    int jumlahDibeli;
    gotoxy(113, 21); // Posisi input di bawah pilihan item
    printf("Masukkan jumlah: ");
    scanf("%d", &jumlahDibeli);
    return jumlahDibeli;
}

void pembelianItemShop(addressChar* karakter, addressShopItem shop[]) {
    int pilihan = inputUser();
    
    if(pilihan < 1 || pilihan > ITEM){
        gotoxy(113, 22);
        printf("Pilihan tidak valid!        ");
        Sleep(2000);
        return;
    }
    
    if (shop[pilihan - 1].stock == 0) {
        gotoxy(113, 22);
        printf("Stok item habis!           ");
        Sleep(2000);
        return;
    }
    
    int jumlahDibeli = inputJumlahItem();
    if(jumlahDibeli < 1 || jumlahDibeli > shop[pilihan - 1].stock){
        gotoxy(113, 22);
        printf("Jumlah tidak valid! (Max: %d)", shop[pilihan - 1].stock);
        Sleep(2000);
        return;
    }
    
    // Hitung total harga
    int totalHarga = hitungTotalHarga(shop[pilihan - 1], jumlahDibeli);
    
    // Tampilkan total harga
    gotoxy(113, 22);
    printf("Total Harga: %d Gold       ", totalHarga);
    Sleep(1000);
    
    // Konfirmasi pembayaran
    gotoxy(113, 23);
    printf("Lanjutkan? (Y/N): ");
    char konfirmasi;
    scanf(" %c", &konfirmasi);
    
    if(konfirmasi != 'Y' && konfirmasi != 'y') {
        gotoxy(113, 24);
        printf("Pembelian dibatalkan.      ");
        Sleep(2000);
        return;
    }
    
    // Proses pembayaran
    if(!prosesPembayaran(karakter, totalHarga)) {
        gotoxy(113, 24);
        printf("Gold tidak cukup! Butuh %d Gold", totalHarga);
        Sleep(2000);
        return;
    }
    
    // Berhasil membeli
    gotoxy(113, 24);
    printf("Berhasil"); 
    gotoxy(113, 25);
    printf("membeli %dx %s!", jumlahDibeli, shop[pilihan - 1].item);
    
    shop[pilihan - 1].stock -= jumlahDibeli;
    tambahkanItemKeInventoryKarakter(karakter, shop[pilihan - 1], jumlahDibeli);
    
    Sleep(2000);
}
