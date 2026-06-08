#ifndef YONETICISISTEMI_H
#define YONETICISISTEMI_H

#include <vector>
#include "Arac.h"
#include "AltSiniflar.h"
#include "Musteri.h"

using namespace std;

/*
Tüm sistemin kalbi olan sınıf:Yönetici sistemi
Bu sınıf, araçları ve müşterileri yönetir, kiralama işlemlerini yapar
*/

//yönetici sistemi sınıfını oluşturduk;değişken ve methodlar
class YoneticiSistemi {
private:
    //neden pointer? Arac soyut bir sınıf olduğu için nesnesi oluşturulamaz
    //Polimorfizm sayesinde Araba, Kamyonet gibi alt sınıfları burada tutabiliriz
    vector<Arac*> araclar ;          //tüm araçları liste olarak tutar
    
    vector<Musteri> musteriler;      //tüm müşterileri liste olarak tutar

    //Yardımcı fonksiyonlar (Private): Sadece sınıf içindeki diğer fonksiyonlar kullanabilir.
    Arac* aracBul (int id);          //ID'ye göre araç pointer'ı döndürür-pointer sebebi:veriye bellekten ulasmak
    Musteri* musteriBul(int id);     //ID'ye göre müşteri pointer'ı döndürür

public:
    YoneticiSistemi();               //yapıcı fonksiyon
    ~YoneticiSistemi();              //yıkıcı fonksiyon
    
    void aracEkle ();                //kullanıcıdan bilgi alıp uygun türde araç ekler
    void musteriEkle ();             //yeni müşteri kaydı oluşturur
    void araclariListele();          //sistemdeki tüm araçları ekrana yazar
    void aracKirala ();              //müşteri ve araç eşleşmesi ile kiralama yapar
    void musteriGecmisiniSorgula();  //belirli bir müşterinin eski işlemlerini gösterir
    
    void verileriKaydet();           //sistem kapanırken verileri dosyaya yazar
    void verileriYukle();            //sistem açılırken verileri dosyadan okur

};

//sistemdeki mantıksal hataları (örn: olmayan araç, müsait olmayan araç) 
//yakalamak ve yönetmek için oluşturduğumuz özel hata sınıfı.
class KiralamaHatasi : public exception {
private:
    string hataMesaji;
public:
    KiralamaHatasi(string mesaj);    //hata mesajını alır
    const char* what() const noexcept override;  //hata mesajını döndürür
};

#endif 