#include "Arac.h"
//yapıcı fonksiyon :türüne göre bir araç oluştururken bunlarla beraber oluşur.
//bir araç boş oluşturulamaz.Daima bu özellikleri barındırır!
//bu sınıftan araç oluşmama sebebi soyut temel sınıf olmasıdır
Arac::Arac(int _id,string _marka,string _model,double _ucret)
    :id(_id),marka(_marka),model(_model),gunlukUcret(_ucret),musaitlikDurumu(true){}

//Aracın musaitlikDurumu değişkenini parametre olarak
//gelen değer ile günceller.
void Arac::setMusaitlik(bool durum){
    musaitlikDurumu=durum;}

bool Arac::isMusait() const {   //Müsaitlik durumunu (true/false)
    return musaitlikDurumu ;}   //çağrıldığı yere döndürür.

int Arac::getId() const{        //araç id döndürür
    return id;}

//arac detaylarını kontrol ederek string olarak döndürür.
string Arac :: getDetay() const {                
    string durum = musaitlikDurumu ? "Musait" : "Kirada";
    return to_string(id) + "-" + marka + "-" + model + "(" + durum + ")" ;}

//araca ait verileri döndürür
string Arac :: veriDondur() const {
    return to_string(id) + " " + marka + " " + model + " " + to_string(gunlukUcret);}

string Arac :: getMarka() const {       //arac markası döndürür
    return marka ; }

string Arac :: getModel() const {       //arac modeli dondurur
    return model ;}

double Arac :: getGunlukUcret() const { //araca ait gunluk ucret dondurur
    return gunlukUcret ;}
