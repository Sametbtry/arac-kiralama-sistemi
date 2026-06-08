#include "AltSiniflar.h"
/*
Araba::Araba(int x,int y)  -> yapıcı fonksiyon
      :Arac(x,y) -> Temel sınıfın (Arac) yapıcısını çağırarak miras alınan özellikleri başlatır.
--Her bir alt sınıf için yapıcı fonk. yazarız. Türetilen sınıf,
temel sınıfın özelliklerini kurmak için onun yapıcısını çağırmalıdır.--
 */

/*
getTur() ve hesaplaUcret fonksiyonları override fonksiyonlardır
aslında temel sınıfta bulunur fakat alt sınıflar bunu ezer
ve kendilerine göre şekillendirirler.
Ayrıca tek bir fonksiyon farklı sınıflarda farklı şekilde çalışması
POLİMORFİZM örneğidir.
*/
Araba:: Araba(int _id,string _marka,string _model,double _ucret) //yapıcı
      :Arac (_id,_marka,_model,_ucret){}                         //temel sınıf yapıcısı
double Araba::hesaplaUcret(int gun) const{   //araba kiralama ücreti hesaplar
    return gun*gunlukUcret ;}                
    string Araba::getTur() const {     //Araca ait türü döndürür : araba          
    return "Araba";}                            

Kamyonet :: Kamyonet(int _id,string _marka , string _model,double _ucret) //yapıcı
          :Arac(_id,_marka,_model,_ucret){}                               //temel sınıf yapıcısı
double Kamyonet::hesaplaUcret(int gun) const {      //kamyonet kiralama ücreti hesaplar
    return gun*gunlukUcret*1.5;}
string Kamyonet::getTur() const {
    return "Kamyonet";}             //Araca ait türü döndürür : Kamyonet

Motosiklet::Motosiklet(int _id,string _marka,string _model,double _ucret)//yapıcı
           :Arac( _id , _marka , _model , _ucret ){}                     //temel sınıf yapıcısı
double Motosiklet::hesaplaUcret(int gun) const {    //motosiklet kiralama ücreti hesaplar
    return gun*gunlukUcret*0.8;}
string Motosiklet::getTur() const {     //Araca ait türü döndürür:Motosiklet
    return "Motosiklet";}