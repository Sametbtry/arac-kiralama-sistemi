#ifndef ARAC_H
#define ARAC_H

#include <string>
#include <iostream>

using namespace std;

//arac sınıfına ait özellikler ve methodlar tanımlandı.
class Arac {
protected:
    int id;
    string marka;
    string model;
    double gunlukUcret;
    bool musaitlikDurumu;
public:
    //yapıcı fonksiyon ve yıkıcı fonksiyon
    Arac(int _id,string _marka,string _model,double _ucret); 
    virtual ~Arac(){}
    
    //'...method = 0' ifadesi bunun bir SAF SANAL (Pure Virtual) fonksiyon olduğunu belirtir.
    //Bu sayede Arac sınıfı SOYUT (Abstract) sınıf olur ve nesnesi oluşturulamaz.
    //Alt sınıflar bu fonksiyonları ezmek (override) zorundadır.
    
    virtual double hesaplaUcret(int gun) const = 0;    //alt sınıflar tarafından ezilir ve türe göre fiyat hesaplanır
    virtual string getTur() const = 0;                 //araca ait türü döndürür  
    void setMusaitlik(bool durum);                     //Aracın müsaitliğini ayarlar
    bool isMusait() const ;                            //aracın müsaitlik durumunu (true/false) döndürür
    int getId() const ;                                //arac id'sini döndürür. 
    string getDetay() const ;                          //arac detayini kontrol eder ve döndürür.
    string getMarka() const ;                          //arac markası döndürür
    string getModel() const ;                          //arac modeli döndürür
    double getGunlukUcret() const ;                    //araca ait gunluk ucreti dondurur
    string veriDondur() const ;                        //araca ait verileri döndürür.
};

#endif