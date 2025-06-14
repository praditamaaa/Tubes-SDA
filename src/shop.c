#include "shop.h"

void tambahkanItem(addressShopItem shop[]){
    shop[0].Type = HealPotion;
    strcpy(shop[0].item, "Potion of Healing");
    shop[0].effect.heal.amount = 50;
    shop[0].stock = 5;

    shop[1].Type = SPBoost;
    strcpy(shop[1].item, "SP Elixir");
    shop[1].effect.sp.amount = 40;
    shop[1].stock = 3;

    shop[2].Type = AttackUp;
    strcpy(shop[2].item, "Attack Potion");
    shop[2].effect.attack.amount = 30;
    shop[2].stock = 2;
    
    shop[3].Type = DefenseUp;
    strcpy(shop[3].item, "Defense Potion");
    shop[3].effect.defense.amount = 30;
    shop[3].stock = 5;

    shop[4].Type = StunItem;
    strcpy(shop[4].item, "Stun Item");
    shop[4].effect.stun.duration = 1;
    shop[4].stock = 3;

    shop[5].Type = ExtraTurnBoots;
    strcpy(shop[5].item, "Boots");
    shop[5].effect.extraTurn.turns = 2;
    shop[5].stock = 2;
    
    shop[6].Type = SplashPoison;
    strcpy(shop[6].item, "Potion Splash");
    shop[6].effect.burn.active = 1;
    shop[6].stock = 5;
}

void tampilkanItem(addressShopItem shop[]) {
	printf("======== SHOP ========\n");
    for (int i = 0; i < ITEM; i++) {
        printf("%d. Nama Item: %s (Stok: %d)\n", i + 1, shop[i].item, shop[i].stock);
    }
}
	
void pakaiItem(addressShopItem i){
    switch (i.Type) {
        case HealPotion:
            printf(">> Menyembuhkan HP sebanyak %d poin.\n", i.effect.heal.amount);
            break;
        case SPBoost:
            printf(">> Menambah SP sebanyak %d poin.\n", i.effect.sp.amount);
            break;
        case AttackUp:
            printf(">> Meningkatkan Attack sebanyak %d poin.\n", i.effect.attack.amount);
            break;
        case DefenseUp:
            printf(">> Meningkatkan Defense sebanyak %d poin.\n", i.effect.defense.amount);
            break;
        case StunItem:
            printf(">> Musuh terkena stun selama %d giliran.\n", i.effect.stun.duration);
            break;
        case ExtraTurnBoots:
            printf(">> Mendapat tambahan %d giliran beruntun.\n", i.effect.extraTurn.turns);
            break;
        case SplashPoison:
            if (i.effect.burn.active)
                printf(">> Musuh terkena racun!\n");
            else
                printf(">> Racun gagal aktif.\n");
            break;
        default:
            printf(">> Tidak ada efek.\n");
    }
}

void tambahkanItemKeInventoryKarakter(addressChar* karakter, addressShopItem shop, int jumlahDibeli){
	addressItem newItem;
    buatItem(&newItem);
    Isi_item(&newItem, shop.item, jumlahDibeli, shop.Type, shop.effect);
    tambahItem(&((*karakter)->inventory), newItem);
}

int inputUser(){
    int pilihan;
    printf("Masukkan nomor item yang ingin dibeli: ");
    scanf("%d", &pilihan);
    return pilihan;
}

int inputJumlahItem(){
    int jumlahDibeli;
    printf("Masukkan jumlah item yang ingin dibeli: ");
    scanf("%d", &jumlahDibeli);
    return jumlahDibeli;
}

void pembelianItemShop(addressChar* karakter, addressShopItem shop[]) {
    tampilkanItem(shop);
    int pilihan = inputUser();
	
    if(pilihan < 1 || pilihan > ITEM){
    	printf("Pilihan tidak valid.\n");
        return;
	}
	
	if (shop[pilihan - 1].stock == 0) {
	    printf("Stok item habis!\n");
	    return;
	}
	
	int jumlahDibeli = inputJumlahItem();
	if(jumlahDibeli < 1 || jumlahDibeli > shop[pilihan - 1].stock){
		printf("Jumlah tidak valid (tersedia: %d).\n", shop[pilihan - 1].stock);
        return;
	}

	printf("Kamu membeli %s!\n", shop[pilihan - 1].item);
            
    shop[pilihan - 1].stock -= jumlahDibeli;
            
    tambahkanItemKeInventoryKarakter(karakter, shop[pilihan - 1], jumlahDibeli);

}


