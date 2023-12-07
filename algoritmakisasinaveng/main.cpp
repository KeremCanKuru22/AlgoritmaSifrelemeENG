#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <wchar.h>

void encrypt(char password[], int scroll){
    unsigned int lenght = strlen(password);  //Dizinin uzunluğunu tuttuğumuz değer.
    char character;
    for (int i = 0; i < lenght; i++) {           //Şifreleme Operasyonumuz
        if(isalpha(password[i])){                   //isalpha fonksiyonuyla girilen harfin alfabede olup olmadığını kontrol ediyoruz.
            character = islower(password[i])? 'a':'A';         //islower fonksiyonuyla harfin büyük ya da küçük olduğunu kontrol ediyoruz. Eğer küçükse a harfini değilse A harfini character değişkenine atıyoruz.
            password[i]= character+(password[i]-character +scroll%26+26)%26;                     //Önce a harfini çıkarıyoruz sonra öteleme miktarını buluyoruz ve a harfine ekliyoruz.
        }
    }
}

void deencrypt(char text[], int key) {
    encrypt(text, -key);
}
char fileusing(char text[]){     //Dosyadan okuma veya dosyaya yazma operasyonu.
    FILE *fp;
    char c;
    int i=0,answer;
    printf("Dosya Olusturup Okutmak Icin : 1\nDosyayi Okutmak Icin : Herhangi Bir Tusa Basin \n");
    scanf("%d",&answer);

    if(answer == 1){                                 //Cevaba göre sadece okuyor veya hem yazıp hem de okuyoruz.
        fp= fopen("input.txt","w");   //Yazma işlemi için dosyayı w(write) şeklinde açıyoruz.
        //Buradaki dosya adını isteğinize göre değiştirebilirsiniz.
        if(fp==NULL){
            printf("Dosya Acilamadi\n");        //Dosyanın geçerliliğini kontrol ediyoruz.
            return 1;
        }
        printf("Lutfen Dosyanin Icerigini Giriniz\n");
        gets(text);                         //gets fonksiyonlarıyla metnimizi alıyoruz.
        gets(text);                          //Kullanıcıdan metni alıyoruz.
        fputs(text,fp);         	    //Aldığımız metni dosyaya yazıyoruz.
        fclose(fp);                               //Ve dosyayı kapatıyoruz.
    }

    fp=fopen("input.txt","r");          //Okuma işlemi için dosyayı r(read) şeklinda açıyoruz.
    if(fp==NULL){
        printf("Dosya Bulunamadi\n");
        return 2;
    }


    while((c= fgetc(fp))!=EOF){  //Dosya bitene kadar her bir harfi text değişkenine atıyoruz.
        text[i]=c;
        ++i;
    }
    fclose(fp);
    return 0;
}

char encryptsystem(){
    //Degişken tanımlama
    char text[600];
    int answer, key;
    //İşlem seçimini sorma ve öğrenme
    printf("Sifrelemeyi Sectiniz\nLutfen Kullanmak Istediginiz Yontemi Seciniz:\n Dosya Ile Yapmak Icin: 1\n Metin Girerek Kullanmak Icin Herhangi Bir Tusa Basiniz:");
    scanf("%d",&answer);
    if (answer==1) {
        fileusing(text);
        if (strlen(text) == 0) {
            return 1;
        }
    }
    if(answer!=1){
        // Kullanıcıdan şifrelenecek metni alma
        printf("Lutfen Sifrelenmesini Istediginiz Metni Giriniz: \n");
        getpasswordagain:
        gets(text); gets(text);
        // Metin uzunluğunu kontrol etme
        if(strlen(text)>600){
            printf("Metin En Fazla 600 Karakter Olabilir!\n");
            fflush(stdin);
            goto getpasswordagain;

        }
    }
    // Kullanıcıdan anahtar değeri alma
    printf("Lutfen Oteleme Miktarini Giriniz: ");
    getkeyagain:
    if(scanf("%d", &key)!=1){
        fflush(stdin);
        printf("Lutfen Sadece Sayi Degeri Giriniz!\n");
        goto getkeyagain;
    }

    // Şifreleme
    encrypt(text, key);
    printf("Sifrelenmis Metniniz: %s\n", text);
}
char deencryptsystem(){
    //Degişken tanımlama
    char text[600];
    int answer, key;
    //İşlem seçimini sorma ve öğrenme
    printf("Desifrelemeyi Sectiniz\nLutfen Kullanmak Istediginiz Yontemi Seciniz:\n Dosya Ile Yapmak Icin: 1\n Metin Girerek Kullanmak Icin Herhangi Bir Tusa Basiniz:");
    scanf("%d",&answer);
    if (answer==1) {
        //Dosya fonksiyonuna gönderme
        fileusing(text);
        if (strlen(text) == 0) {
            return 1;
        }
    }
    if(answer!=1){
        // Kullanıcıdan şifrelenecek metni alma
        printf("Lutfen Desifrelenmesini Istediginiz Metni Giriniz: \n");
        getpasswordagain:
        gets(text); gets(text);
        if(strlen(text)>600){
            printf("Metin En Fazla 600 Karakter Olabilir!\n");
            fflush(stdin);
            goto getpasswordagain;
        }
    }
    // Kullanıcıdan anahtar değeri alma
    printf("Lutfen Geri Oteleme Miktarini Giriniz: ");
    getkeyagain:
    if(scanf("%d", &key)!=1){
        fflush(stdin);
        printf("Lutfen Sadece Sayi Degeri Giriniz!\n");
        goto getkeyagain;
    }

    // Şifreleme
    deencrypt(text, key);
    printf("Desifrelenmis Metniniz: %s\n", text);
    return 0;
}
int main() {
    int key;
    char text[600];
    int choice,answer;
    // Kullanıcıya şifreleme veya deşifreleme işlemlerinden hangi seçeneği seçeceğini sorma
    printf("Yapilacak Islemi Seciniz:\n");
    choosingpart:
    printf("  1 - Metin Sifreleme\n");
    printf("  2 - Metin Desifreleme\n");
    printf("  3 - Programi Sonlandir\n");
    printf("Lutfen Seciminizi Yapiniz (1/2/3): ");
    //scanf("%d", &choice);
    if(scanf("%d", &choice)!=1){         //Girilen değerin sayı olup olmadığını kontrol ediyoruz.
        printf("Lutfen Sadece Belirtilen Sayi Degerlerini Giriniz!\n\n");
        fflush(stdin);
        goto choosingpart;}


    switch (choice) {
        case 1:
            encryptsystem();
            printf("Program Basa Donuyor\n\n");
            goto choosingpart;

        case 2:
            // Deşifreleme
            deencryptsystem();
            printf("Program Basa Donuyor\n\n");
            goto choosingpart;

        case 3:
            //Programı sonlandırma
            printf("Cikisiniz Yapildi.\n\n");
            break;

        default:
            //Tanımlanmayan değerlerde hata verme
            printf("Hatali Secim. Lutfen Gecerli Bir Islem Seciniz.\n\n");
            goto choosingpart;
    }

    return 0;
}
