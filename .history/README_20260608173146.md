# Araç Kiralama Sistemi

**Nesne Yönelimli Programlama Dönem Sonu Projesi**

## Proje Özeti

3 kişilik bu proje, Nesne Yönelimli Programlama (OOP) prensiplerini uygulayarak bir araç kiralama firmasının günlük operasyonlarını dijital ortamda yöneten bir otomasyonu sistemini simüle etmektedir. 

Sistem, **Soyutlama (Abstraction)**, **Kapsülleme (Encapsulation)**, **Miras Alma (Inheritance)** ve **Çok Biçimlilik (Polymorphism)** kavramlarının pratik uygulamasını göstermektedir. Ayrıca verilerin kalıcılığını sağlamak amacıyla dosya okuma/yazma işlemleri ve çalışma zamanı hatalarını yönetmek için exception yönetimi kullanılmıştır.


## Proje Yapısı

```
arac-kiralama-sistemi/
├── src/                      # Kaynak kodlar
│   ├── main.cpp             # Ana program
│   ├── Arac.h/.cpp          # Temel araç sınıfı (Abstract)
│   ├── AltSiniflar.h/.cpp   # Alt sınıflar (Araba, Kamyonet, Motosiklet)
│   ├── Musteri.h/.cpp       # Müşteri sınıfı
│   ├── YoneticiSistemi.h/.cpp # Sistem yönetim sınıfı
├── data/                    # Veri dosyaları
│   ├── araclar.txt          # Araç listesi
│   └── musteriler.txt       # Müşteri ve kiralama geçmişi
├── teslimat/                # Video kayıtları ve test senaryoları
└── README.md
```

## OOP Prensipleri

### 1. **Soyutlama (Abstraction)**
- `Arac` sınıfı abstract olarak tanımlanmış ve saf sanal fonksiyonlar (`hesaplaUcret()`, `getTur()`) içermektedir
- Alt sınıflar için bir şablon görevi görmektedir

### 2. **Miras Alma (Inheritance)**
- `Araba`, `Kamyonet`, `Motosiklet` sınıfları `Arac` sınıfından miras almaktadır
- Her alt sınıf kendi fiyatlandırma politikasına sahiptir

### 3. **Çok Biçimlilik (Polymorphism)**
- `hesaplaUcret()` metodu her alt sınıfta farklı şekilde uygulanmıştır
- `YoneticiSistemi` sınıfı `Arac*` pointer vektörü kullanarak tüm araç türlerini polimorfik olarak yönetir

### 4. **Kapsülleme (Encapsulation)**
- Private ve public erişim belirleyicileriyle veri gizlenmiş, kontrollü erişim sağlanmıştır
- Getter ve setter metodları kullanılmıştır

## Veri Yapıları

- **std::vector**: Araçlar ve müşteriler dinamik olarak depolanır
- **struct KiralamaKaydi**: Müşteri kiralama geçmişini içerir
- **Arac\***: Polimorfik araç nesneleri tek bir listede tutulur
- **Exception (KiralamaHatasi)**: std::exception sınıfından türetilerek özel hata yönetimi sağlanır

## Dosya Yapısı

### araclar.txt
```
AraçTürü|ID|Marka|Model|GünlükÜcret|MüsaitlikDurumu
Araba|1|BMW|i4|100|0
Kamyonet|2|Volvo|FH16|200|1
Motosiklet|30|Harley|Sportster|88|0
```

### musteriler.txt
```
ID|Ad|Soyad|KiralamaSayısı
KiralananAraçDetayı|Gün|Ücret
```

## Gereksinimler

- **C++11** veya üzeri destekli derleyici
- **GCC**, **Clang** veya **MSVC**

## Derleme ve Çalıştırma

### Derleme (Terminal/Command Line)

```bash
g++ src/main.cpp src/Arac.cpp src/AltSiniflar.cpp src/Musteri.cpp src/YoneticiSistemi.cpp -o AracKiralamaSistemi
```

### Çalıştırma

**Windows:**
```bash
./AracKiralamaSistemi.exe
```

**Linux/Mac:**
```bash
./AracKiralamaSistemi
```

## Temel Özellikler

### 1. Polimorfik Ücret Hesaplama
Araç türüne bağlı olarak farklı ücret hesaplanır:
- **Araba**: Günlük fiyat
- **Kamyonet**: Günlük fiyat × 1.5
- **Motosiklet**: Günlük fiyat × 0.8

### 2. Kiralama İşlemi
```
Adımlar:
1. Müşteri ID ve Araç ID alınır
2. isMusait() kontrolü yapılır
3. Araç müsait değilse KiralamaHatasi fırlatılır
4. Araç müsait ise hesaplaUcret() ile fiyat belirlenir
5. Aracın durumu "dolu" olarak güncellenir
6. İşlem müşteri geçmişine eklenir
```

### 3. Dosya I/O
- Uygulama başlatıldığında araçlar ve müşteriler dosyasından okunur
- Yapılan değişiklikler dosyaya yazılır
- `stringstream` ve `|` ayracı kullanılarak veriler işlenir

### 4. Hata Yönetimi
- `KiralamaHatasi` exception sınıfı kullanılarak hata kontrolü sağlanır
- Kiralama sırasında oluşabilecek mantıksal hatalar yakalanır

## Kullanım Örneği

### Örnek Senaryo: Müşteri Ekleme ve Araç Kiralama

**Müşteri Ekleme:**
```
Menü Seçimi: 2
ID: 1
Ad: SAMET
Soyad: BATURAY
```

**Araç Kiralama:**
```
Menü Seçimi: 4
Müşteri ID: 1
Araç ID: 30 (Harley Sportster)
Gün Sayısı: 5
```

**Beklenen Sonuç:**
- Müşteri SAMET BATURAY'ın geçmişine 1 kiralama işlemi eklenir
- Toplam ücret: 88 × 5 × 0.8 = 352 TL (Motosiklet için)

## Sınıf Diyagramı Özeti

```
                    ┌─────────────────┐
                    │     Arac        │ (Abstract)
                    │   (Base Class)  │
                    └────────┬────────┘
                             │
                 ┌───────────┼───────────┐
                 │           │           │
            ┌────┴────┐  ┌───┴────┐  ┌──┴─────┐
            │  Araba  │  │Kamyonet│  │Motosik.│
            └─────────┘  └────────┘  └────────┘
                    
      ┌──────────────────────────────────┐
      │    YoneticiSistemi               │
      │  - vector<Arac*> araclar        │
      │  - vector<Musteri> musteriler   │
      └──────────────────────────────────┘
      
      ┌──────────────────────────────────┐
      │    Musteri                       │
      │  - vector<KiralamaKaydi> gecmis│
      │  - KiralamaHatasi exception     │
      └──────────────────────────────────┘
```

## Yasal Uyarı

Bu proje eğitim amaçlı olarak geliştirilmiştir ve Nesne Yönelimli Programlama dersi kapsamında öğretilen prensipleri göstermektedir.

## Lisans

Bu proje eğitim amaçlıdır.


