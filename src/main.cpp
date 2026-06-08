#include <iostream>
#include "YoneticiSistemi.h"
#include "Arac.h"
#include "Musteri.h"
#include "AltSiniflar.h"

using namespace std;

/*
Sistem çalıştığında yöneticinin sistemi kullanabilmesi için 
menü oluşturduk.Ve işlemlere sayılar atadık.
Çıkış yap kısmına tıklanmadığı sürece while ile menü
kullanıcın ekranına tekrar döndürülüyor.
*/

void menuGoster() {
    cout << "\n--- ARAC KIRALAMA YONETICI SISTEMI ---\n";
    cout << "1. Yeni Arac Ekle\n";
    cout << "2. Yeni Musteri Ekle\n";
    cout << "3. Arac Listele\n";
    cout << "4. Arac Kirala\n";
    cout << "5. Musteri Gecmisi\n";
    cout << "6. Kaydet ve Cikis\n";
    cout << "Seciminiz: ";
}

int main() {
    YoneticiSistemi sistem; //Yönetici sistemi sınıfından bir nesne oluşturduk.
    int secim;              //menüde gezinebilmek için seçim adında bir integer oluşturduk.

    while (true) {              
        menuGoster();
        cin >> secim;

                // cin başarısız olursa (string girilirse) hata durumunu temizle
        if (cin.fail()) {
            cin.clear();                    // Hata bayrağını temizle
            cin.ignore(10000, '\n');        // Yanlış girişi temizle
            cout << "Lutfen bir sayi giriniz!\n";
            continue;                       // Döngüyü yeniden başlat
        }

        try {
            switch (secim) {
                case 1:
                    sistem.aracEkle();
                    break;
                case 2:
                    sistem.musteriEkle();
                    break;
                case 3:
                    sistem.araclariListele();
                    break;
                case 4: 
                    sistem.aracKirala();
                    break;
                case 5: 
                    sistem.musteriGecmisiniSorgula();
                    break;
                case 6: 
                    sistem.verileriKaydet();
                    cout << "Cikis yapiliyor...\n";
                    return 0;
                default: 
                    cout << "Gecersiz secim!\n";
            }
        }
        catch (const exception& e) {           //Hata (exception) fırlatıldığında hatayı yakalayıp ekrana yazan blok
            cerr << "\nHATA OLUSTU: " << e.what() << "\n";
        }
    }
}