#include "YoneticiSistemi.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

// hata sınıfına ait yapıcı fonksiyon
KiralamaHatasi::KiralamaHatasi(string mesaj) : hataMesaji(mesaj) {}

// what() metodunu implement ediyoruz
const char* KiralamaHatasi::what() const noexcept {
    return hataMesaji.c_str();
}

YoneticiSistemi::YoneticiSistemi(){
    verileriYukle(); // sistem nesnesi oluşur oluşmaz eski verileri dosyadan çekeriz.
}

YoneticiSistemi::~YoneticiSistemi(){
    // ÖNEMLİ: 'new' ile oluşturduğumuz araçlar bellekte yer kaplar.
    // bellek sızıntısını (memory leak) önlemek için her birini tek tek siliyoruz.
    for (auto arac: araclar){
        delete arac;
    }
    araclar.clear(); // listeyi tamamen boşaltıyoruz.
}

// kullanıcıdan alınan bilgilere göre çalışma anında (runtime) nesne oluşturur.
void YoneticiSistemi::aracEkle(){
    int tip , id;
    string marka,model;
    double ucret;

    cout << "Arac Tipi Sec (1:Araba, 2:Kamyonet, 3:Motor): "; cin >> tip;
    cout << "ID: "; 
    cin >> id;
    
    // Aynı ID'ye sahip araç var mı kontrol eder
    if (aracBul(id) != nullptr) {
        cout << "Bu ID'ye sahip arac zaten mevcut!\n";
        return;
    }
    
    cout << "Marka: "; 
    cin >> marka;
    cout << "Model: "; 
    cin >> model;
    cout << "Gunluk Ucret: "; 
    cin >> ucret;

    // polimorfizm burada devreye giriyor: Farklı türleri 'Arac*' listesine ekleyebiliyoruz.
    if (tip==1) araclar.push_back(new Araba(id,marka,model,ucret));
    else if(tip==2) araclar.push_back(new Kamyonet(id,marka,model,ucret));
    else if(tip==3) araclar.push_back(new Motosiklet(id,marka,model,ucret));
    else {
        cout<<"Gecersiz arac tipi secildi!\n";
        return;
    }

    cout<<"Arac eklendi!\n";
}

// yeni bir müşteri nesnesi oluşturup listeye ekler.
// burada Composition (Kompozisyon) gereği Musteri nesnesi listenin içine kopyalanır.
void YoneticiSistemi::musteriEkle(){
    int id;
    string ad,soyad;
    cout<< "Musteri ID (Iptal icin -1): ";
    cin >> id;
    
    // Kullanıcı işlemi iptal etmek isterse
    if (id == -1) {
        cout << "Islem iptal edildi.\n";
        return;
    }
    
    // Aynı ID'ye sahip müşteri var mı kontrol etmek icin
    if (musteriBul(id) != nullptr) {
        cout << "Bu ID'ye sahip musteri zaten mevcut!\n";
        return;
    }
    
    cout<<"Ad: ";
    cin >> ad;
    cout<<"Soyad: "; 
    cin >> soyad;
    musteriler.push_back(Musteri(id,ad,soyad));
    cout << "Musteri eklendi!\n";
}

// sanal fonksiyonlar sayesinde her araç kendi türüne göre detay yazdırır.
void YoneticiSistemi::araclariListele(){
    cout << "\n---Arac Listesi---\n" ;
    for (const auto& arac:araclar){ 
        // arac->getTur() çağrıldığında Araba mı Motor mu olduğu otomatik anlaşılır.
        cout<<arac->getDetay()<<" [" << arac->getTur() << "]\n";   
    }
}

// kiralama işleminin mantıksal kontrol merkezi.
void YoneticiSistemi::aracKirala(){
    int mId,aId,gun;
    cout<<"Musteri ID (Iptal icin -1): ";
    cin >> mId;
    
    // Kullanıcı işlemi iptal etmek isterse
    if (mId == -1) {
        cout << "Islem iptal edildi.\n";
        return;
    }
    
    cout<<"Arac Id: ";
    cin>> aId;
    cout<<"Arac kac gun kiralaniyor?: ";
    cin >> gun ;
    
    Musteri* musteri = musteriBul(mId);
    Arac* arac = aracBul(aId);

    // eğer bir sorun varsa 'throw' ile hatayı fırlatıyoruz.
    // bu hata main.cpp içindeki 'catch' bloğu tarafından yakalanacak.
    if (!musteri || !arac){
        throw KiralamaHatasi("Musteri veya Arac ID bulunamadi!!");
    }
    if (!arac->isMusait()){
        throw KiralamaHatasi("Bu arac kullaniliyor.Musait degil.");
    }

    double tutar = arac->hesaplaUcret(gun); // Araç türüne göre fiyat hesaplanır.
    arac->setMusaitlik(false);              // Araç artık müsait değil.
    musteri->kiralamaEkle(arac->getDetay(),gun,tutar); // Müşterinin geçmişine ekle.
    cout<<"Islem basarili! Toplam Tutar : "<<tutar<<"TL\n";
}

// id üzerinden araç bulma: Pointer döndürüyoruz ki orijinal araç üzerinde işlem yapabilelim.
Arac* YoneticiSistemi::aracBul(int id){
    for(auto arac : araclar){
        if (arac-> getId()==id)
        return arac; // bulunan aracın bellek adresini döndürür.
    }
    return nullptr;
}


Musteri* YoneticiSistemi::musteriBul(int id){
    for (auto& m : musteriler){
        if(m.getId()==id)
        return &m; // müşterinin adresini döndürür.
    }
    return nullptr;
}

// verileri kalıcı hale getirmek için dosyaya yazma işlemi.
void YoneticiSistemi::verileriKaydet(){
    ofstream aracDosya("data/araclar.txt");
    if (!aracDosya.is_open()){
        cout<<"HATA:data/araclar.txt dosyasi acilamadi!!\n";
        return;
    }

    // araç bilgilerini satır satır dosyaya yazar.
    for(const auto& arac : araclar){
        aracDosya<<arac->getTur()<<"|"
        <<arac->getId() << "|"
        <<arac->getMarka()<<"|"
        <<arac->getModel()<<"|"
        <<arac->getGunlukUcret()<<"|"
        <<(arac->isMusait()? 1 : 0 )<<"\n"; 
    }
    aracDosya.close();

    ofstream musteriDosya("data/musteriler.txt");
    if (!musteriDosya.is_open()){
        cout<<"HATA:data/musteriler.txt dosyasi acilamadi!!\n";
        return;
    }
    for (const auto& musteri :musteriler){
        // müşterinin temel bilgileri ve kaç tane kiralama yaptığı yazılır.
        const auto& gecmis = musteri.getIslemGecmisi();
        musteriDosya<<musteri.getId()<<"|"
        <<musteri.getAd()<<"|"
        <<musteri.getSoyad()<<"|"
        <<gecmis.size()<<"\n";


    // müşteriye ait alt kiralama kayıtları (Composition parçaları) yazılır.
    for (const auto& kayit:gecmis){
        musteriDosya<<kayit.aracDetayi<<"|"
                    <<kayit.gun <<"|"
                    <<kayit.odenenUcret<<"\n";
        }    
    }
musteriDosya.close();
cout<<"Veriler dosyaya kaydedildi.\n"<<endl;
}

// program açıldığında dosyadan verileri okuyup nesneleri tekrar oluşturur.
void YoneticiSistemi::verileriYukle(){
    ifstream aracDosya("data/araclar.txt");
    if (!aracDosya.is_open()){
        cout << "data/araclar.txt bulunamadi. Arac listesi su an bos.\n";
    } else {
        string satir;
        while (getline(aracDosya, satir)){
            stringstream ss(satir);
            string tur, marka, model;
            int id, musaitMi;
            double ucret;
            
            // satırı '|' karakterine göre parçalara ayırıyoruz.
            // neden getline? Çünkü marka veya model isimleri boşluk içerebilir.
            getline(ss, tur, '|'); 
            ss >> id;
            ss.ignore(); // sayıdan sonra gelen '|' karakterini atlamak için kullanılır.
            getline(ss, marka, '|');
            getline(ss, model, '|');
            ss >> ucret;
            ss.ignore(); // son ayırıcıyı atla.
            ss >> musaitMi;

            // POLİMORFİZM: Dosyadan okuduğumuz 'tur' bilgisine göre 
            // bellekte (Heap) uygun alt sınıf nesnesini oluşturuyoruz.
            Arac* yeniArac = nullptr;  
            if (tur == "Araba"){
                yeniArac = new Araba(id, marka, model, ucret);
            } else if (tur == "Kamyonet"){
                yeniArac = new Kamyonet(id, marka, model, ucret);
            } else if (tur == "Motosiklet"){
                yeniArac = new Motosiklet(id, marka, model, ucret);
            }
            
            if (yeniArac) {
                // aracın müsaitlik durumunu dosyadan okuduğumuz değere göre güncelliyoruz.
                yeniArac->setMusaitlik(musaitMi == 1);
                araclar.push_back(yeniArac);
            }
        }
        aracDosya.close();
        cout << araclar.size() << " arac yuklendi.\n";  
    }

    // müşteri verilerini yükleme kısmı:
    ifstream musteriDosya("data/musteriler.txt");
    if (!musteriDosya.is_open()){
        cout << "data/musteriler.txt bulunamadi. Musteri listesi su anda bos.\n";
    } else {
        string satir;
        while (getline(musteriDosya, satir)){
            stringstream ss(satir);
            int id, islemSayisi;
            string ad, soyad;
            
            ss >> id;    // müşteri id'sini al.
            ss.ignore(); // ayırıcıyı geç.
            getline(ss, ad, '|');
            getline(ss, soyad, '|');
            ss >> islemSayisi; // bu müşterinin kaç tane kiralama kaydı olduğunu öğreniyoruz.

            // KOMPOZİSYON: Müşteri nesnesini oluşturuyoruz.
            Musteri yeniMusteri(id, ad, soyad);

            // müşterinin sahip olduğu kiralama kayıtlarını (islemGecmisi) 
            // alt satırlardan tek tek okuyup müşterinin içine ekliyoruz.
            for (int i = 0; i < islemSayisi; i++){
                string kayitSatiri;
                getline(musteriDosya, kayitSatiri);

                size_t ayrac1 = kayitSatiri.find("|");
                size_t ayrac2 = kayitSatiri.rfind("|");
                
                // string parçalama: '|' karakterlerinin yerini bulup aradaki veriyi çekiyoruz.
                if (ayrac1 != string::npos && ayrac2 != string::npos){
                    string aracDetayi = kayitSatiri.substr(0, ayrac1);
                    int gun = stoi(kayitSatiri.substr(ayrac1 + 1, ayrac2 - ayrac1 - 1));
                    double ucret = stod(kayitSatiri.substr(ayrac2 + 1));
                    
                    // müşterinin kendi vektörüne (islemGecmisi) bu kaydı ekliyoruz.
                    yeniMusteri.kiralamaEkle(aracDetayi, gun, ucret);
                }
            }
            musteriler.push_back(yeniMusteri);    
        }
        musteriDosya.close();
        cout << musteriler.size() << " musteri yuklendi.\n";
    }
}

// kullanıcının girdiği ID'ye göre müşteriyi bulup tüm geçmişini listeleyen fonksiyon.
void YoneticiSistemi::musteriGecmisiniSorgula(){
    int id;
    cout << "Musteri ID:",
    cin >> id;
    Musteri* m = musteriBul(id); // Yardımcı fonksiyonumuzla müşteriyi arıyoruz.
    if(m){
    // müşteri bulunduysa, Musteri sınıfındaki görüntüleme metodunu çağırıyoruz.
    m-> gecmisiGoruntule(); 
    }
    else{ 
    cout <<"Musteri bulunamadi.\n";
    }
}
