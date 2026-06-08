#include "Musteri.h"

// Yapıcı fonksiyon
Musteri::Musteri(int _id, string _ad, string _soyad)
    : id(_id), ad(_ad), soyad(_soyad) {}

//müşteri geçmişine yeni kiralama eklemek için kullandığımız fonksiyon
void Musteri::kiralamaEkle(string aracBilgi, int gun, double ucret) {
    KiralamaKaydi yeniKayit = {aracBilgi, gun, ucret}; //yeni kayıt nesnesi oluşturup içeriğini doldurduk
    islemGecmisi.push_back(yeniKayit); // Müşterinin işlem geçmişine yeni kayıt eklenir
}

//müşteri geçmişni görüntülememize olanak sağlayan fonksiyon
void Musteri::gecmisiGoruntule() const { //const : bu fonksiyon yalnızca değer okunması içindir bir değişiklik barındırmaz
    cout << "--- " << ad << " " << soyad << " Kiralama Gecmisi ---\n";
    if (islemGecmisi.empty()) {   //geçmişte işlem yok ise empty() = true döndürür ve if içeriğindeki kodlar çalışır
        cout << "Henuz islem yok.\n";
        return;
    }

    //bir müşteriye ait kayıtları teker teker okuyarak yazdırır.
    for (const auto& kayit : islemGecmisi) {  
        // auto turu otomatik anlar.
        // & ile kopyalamayi onler direkt referans adresi kullanir.
        cout << "Arac: " << kayit.aracDetayi 
             << " | Gun: " << kayit.gun 
             << " | Tutar: " << kayit.odenenUcret << " TL\n";
    }
}

int Musteri::getId() const {  //müşteri id'si döndürür
    return id; }

string Musteri::getAd() const { //müşteri adı döndürür
    return ad;}

string Musteri :: getSoyad()const{  //müşteri soyadı döndürür
    return soyad;}

//müşteriye ait işlem geçmişini döndürür
const vector<KiralamaKaydi>& Musteri::getIslemGecmisi() const { 
    return islemGecmisi; 
}

// gecmisiGoruntule metodunun gorevi konsola musterinin kiralama gecmisini yazdirmaktir.
// getIslemGecmisi metodu ise musterinin islem gecmisini dondurur. Sinif disindan bu verilere erisim saglanabilir.