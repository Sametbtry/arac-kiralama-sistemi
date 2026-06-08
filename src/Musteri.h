#ifndef MUSTERI_H
#define MUSTERI_H

#include <iostream>
#include <string>
#include <vector> //müşterilere ait işlem geçmişi tutmak için liste

using namespace std;

//kiralama kaydı adında bir yapı tanımlandı.Bu yapı 
//müşterilerin kiralama bilgilerini saklar ve kaydetmemize
//olanak sağlar
struct KiralamaKaydi{
    string aracDetayi;
    int gun;
    double odenenUcret;
};

//müşteri sınıfı ve bu sınıfa ait metholar tanımlandı.
class Musteri{
private:
    int id;
    string ad;
    string soyad;
    //müşteri sınıfı, KiralamaKaydi yapısını barındırır (Has-A ilişkisi).
    //bu bir Composition (Kompozisyon) örneğidir.
    vector<KiralamaKaydi> islemGecmisi;     //müşteri işlem geçmişi    
public:
//yapıcı fonksiyon
Musteri(int _id,string ad,string _soyad);

//yönetici -> müşterilere arac kiralamak için bu methodu kullanır.
void kiralamaEkle(string aracBilgi, int gun, double ucret);

void gecmisiGoruntule()  const ;   //müşteri geçmişini görüntülememize olanak sağlar
int getId() const ;                //müşteri id sini döndürür 
string getAd() const;              //müşteri adını döndürür
string getSoyad() const;           //müşteri soyadını döndürür

//müşteri işlem geçmişini referans ile döndürür.
//neden referans? Listenin kopyalanmasını önleyerek performans sağlar.
//const olduğu için liste dışarıdan değiştirilemez (sadece okunabilir).
const vector<KiralamaKaydi>& getIslemGecmisi() const;
};

#endif