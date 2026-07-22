# 📝 Note_App v0.7.3-beta

C++ ile geliştirilmiş, tamamen terminal (komut satırı) üzerinden çalışan, hızlı ve pratik bir not alma uygulamasıdır. Kullanıcıların yerel bilgisayarlarında kolayca not tutmasını, düzenlemesini ve yönetmesini sağlar.

## 🚀 Uygulama Özellikleri (Tamamlananlar)
Uygulama şu anda stabil olarak çalışmaktadır ve şu özellikleri barındırır:
* ➕ **Not Ekleme:** Yeni notlarınızı hızlıca sisteme kaydedin.
* 👁️ **Notları Görüntüleme:** Eklediğiniz tüm notları listeleyin.
* ❌ **Not Silme:** İhtiyacınız kalmayan notları güvenle kaldırın.
* ✏️ **Not Düzenleme:** Mevcut notlarınızın içeriğini güncelleyin.
* 📋 **Gelişmiş Not Yapısı:** Her nota otomatik benzersiz ID, özel Başlık, İçerik alanı ve notun yazıldığı anı kaydeden Zaman Damgası (Tarih/Saat) entegrasyonu.
* **🔍Gelismis arama:** Notları başlık, içerik ve oluşturulma tarihine göre hızlı ve kolay bir şekilde bulabilirsiniz.
* 💾 **Masaüstüne Aktarma:** Seçtiğiniz bir notu doğrudan bilgisayarınızın masaüstüne .txt dosyası olarak kaydedin.
* 🚪 **Çıkış ve Otomatik Kaydetme:** Uygulamadan güvenli çıkış yapma seçeneği; program kapatılırken tüm verileriniz çökme riski olmadan otomatik olarak kaydedilir.
* 🛡️ **Hatalı Giriş Kontrolü:** Menüde yanlış bir tuşa basıldığında uygulamanın çökmesini engelleyen güvenli kontrol sistemi.
* 🔄 **Geri Yükleme ve Okuma:** Kaydedilen .txt dosyalarını otomatik olarak okuyarak verilerinizi uygulamada tekrar çalıştırın.
* 🛡️ **Hata Korumalı Dosya Okuma:** Geri yükleme sırasında bozuk veya yanlış formatlı .txt dosyalarına karşı alınan önlem; hatalı verilerin sistemi çökeltmesini engelleyen güvenli okuma sistemi.
* 🚪 **Çıkış:** Uygulamadan güvenli çıkış yapma seçeneği.

## 📂 Proje Yapısı
* `src/` - Kaynak kodları (.cpp ve .h dosyaları)
* `CMakeLists.txt` - Projenin derleme ve bağımlılık ayarları
* `README.md` - Proje açıklama ve kullanım kılavuzu

## 🤖 AI Collaboration / Yapay Zeka Kullanımı
I used an AI assistant as a pair programmer and learning tool during this project. 
It helped me understand complex C++ concepts, debug code, and optimize structural logic while building my foundational skills.

*Bu projeyi geliştirirken C++ kavramlarını daha iyi anlamak, hataları çözmek ve mantıksal yapıyı kurmak adına bir yapay zeka asistanından destek aldım.

## ⚙️ Lisans ve Telif Hakkı
* **Telif Hakkı:** Copyright (c) 2026 bhalitgil
* **Lisans:** Licensed under MIT / GPLv3 / Apache 2.0

## 🛠️ Terminalden Derleme ve Çalıştırma (Build)

Uygulamayı kaynak kodundan derlemek için terminali açıp proje ana klasörüne gidin ve işletim sisteminize uygun olan adımları takip edin:

### 🪟 Windows İçin (Terminal / PowerShell)
Windows üzerinde terminalden derleme yapmak için bilgisayarınızda **CMake** ve **MinGW (g++)** kurulu olmalıdır.

```bash
# 1. Derleme klasörü oluşturun ve içine girin
mkdir build
cd build

# 2. CMake ile Windows (MinGW) ayarlarını yapın
cmake -G "MinGW Makefiles" ..

# 3. Projeyi derleyin
cmake --build .

# 4. Uygulamayı çalıştırın
.\Note_App.exe
```

### 🐧 Linux İçin (Terminal)
Linux üzerinde derleme yapmak için bilgisayarınızda `cmake`, `make` ve `g++` paketlerinin kurulu olması gerekir (`sudo apt install build-essential cmake`).

```bash
# 1. Derleme klasörü oluşturun ve içine girin
mkdir build
cd build

# 2. CMake ayarlarını yapın
cmake ..

# 3. Projeyi derleyin
cmake --build .

# 4. Uygulamayı çalıştırın
./Note_App
```

## 📥 Doğrudan Çalıştırma (.exe)
Kod derlemekle uğraşmak istemiyorsanız, web sitemiz üzerindeki bağlantıdan doğrudan derlenmiş **Note_App.exe** dosyasını indirip çift tıklayarak terminal arayüzünü kullanmaya başlayabilirsiniz.

## ✉️ İletişim ve Geri Bildirim
Uygulama hakkında sorularınız veya hata bildirimleriniz için web sitemizdeki buton üzerinden veya doğrudan **bhalitgil250708@gmail.com** adresinden bana ulaşabilirsiniz.
