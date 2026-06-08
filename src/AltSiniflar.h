#ifndef ALTSINIFLAR_H
#define ALTSINIFLAR_H

#include "Arac.h"
/*
arac sınıfından miras alan 3 alt sınıf bulunuyor
override olan fonksiyonlar ebeveyn sınıfa ait kodları 
miras alır,ezer ve kendilerine gore calıstırır
*/

/*
Bu sınıflarda özel bir yıkıcı fonksiyon (destructor) tanımlanmamasının sebebi,
bu alt sınıfların kendilerine ait dinamik bellek yönetimi (new/delete) yapmamalarıdır.
Varsayılan yıkıcı yeterlidir.
*/

//1.alt sınıf:araba 
class Araba : public Arac {
public:
    //yapıcı fonksiyon
    Araba(int _id , string _marka , string _model , double _ucret);
    //araba kiralama ücreti hesaplar
    double hesaplaUcret(int gun) const override ;
    //araç türünü döndürür
    string getTur() const override ; 
};

//2.alt sınıf:kamyonet
class Kamyonet : public Arac {
public:
    //yapıcı fonksiyon
    Kamyonet(int _id,string _marka,string _model,double _ucret);
    //kamyonet kiralama ücreti hesaplar
    double hesaplaUcret(int gun) const override;
    //araç türünü döndürür
    string getTur() const override ;
} ;

//alt sınıf:motosiklet
class Motosiklet : public Arac {
public :
    //yapıcı fonksiyon
    Motosiklet (int _id , string _marka ,string _model , double _ucret);
    //motor kiralama ücreti hesaplar
    double hesaplaUcret(int gun) const override;
    //araç türünü döndürür
    string getTur() const override ;
};
#endif