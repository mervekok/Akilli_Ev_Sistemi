#include <DHT.h>
#include <LiquidCrystal.h>
#define DHTPIN 47
#define DHTTYPE DHT11

LiquidCrystal lcd(8,9,4,5,6,7);
int redLed = 30;
int greenLed = 31;
int buzzer = 32;
int smokeA0 = A8;
int fanRedPin=53;
int fanGreenPin=51;
int sicaklikGreenLed = 38;
int sicaklikRedLed=36;
int ledPin = 37; // led pin

// Eşik değeri, hassasiyeti buradan da ayarlayabilirsiniz.
int sensorThres = 180;
int inputPin = 24; // hareket sensör sinyal pin
int pirState = LOW; // hareket durumu
int val = 0; // hareket sensöründen okunan değer
int pinSpeaker = 22; //buzzer pin
int sicaklik;
int deger=0;
String gelen;
int sayac=0;
int fanSayac=0;
int fanSayac2=0;
int istenilenSicaklik;
int istenilenSicaklik2;
int i=0;
int a=0;

DHT dhtBaglan(DHTPIN, DHTTYPE);

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  pinMode(ledPin, OUTPUT); //led pin çıkış tanımlama
  pinMode(inputPin, INPUT); // hareket sensör pini giriş tanımlama
  pinMode(pinSpeaker, OUTPUT);
  pinMode(sicaklikGreenLed, OUTPUT);
  pinMode(sicaklikRedLed, OUTPUT);
  pinMode(fanRedPin,OUTPUT);
  pinMode(fanGreenPin,OUTPUT);
  lcd.begin(16,2);
  //Serial.begin(9600);
  //Serial.setTimeout(50);
  dhtBaglan.begin();
  Serial.begin(57600);
}
void loop() {
  sayac++;
  int analogSensor = analogRead(smokeA0);
  val = digitalRead(inputPin); // hareket sensöründen değer okuma
  sicaklik = dhtBaglan.readTemperature();
  gelen =Serial.readString();
 
          if(gelen.equals("1") && (sicaklik<22)){
                lcdSifirla();
                lcd.setCursor(0,0);
                lcd.print("İsitici Fan Aktif");
                digitalWrite(fanRedPin,HIGH);
                digitalWrite(fanGreenPin,LOW);
            }
        else if(gelen.equals("2") && sicaklik>22){
              lcdSifirla();
              lcd.setCursor(0,0);
              lcd.print("Otomatik Ayar");
              lcd.setCursor(0,1);
              lcd.print("Sogutucu Fan Aktif");
              digitalWrite(fanRedPin,LOW);
              digitalWrite(fanGreenPin,HIGH);
        }
        else if(gelen.equals("3"))//manuelAyar
        {   
              fanSayac++;
              lcdSifirla();
              lcd.setCursor(0,0);
              lcd.print("Manuel Ayar");
              lcd.setCursor(0,1);
              lcd.print("Isitici Fan Aktif");
              digitalWrite(fanRedPin,HIGH);
              digitalWrite(fanGreenPin,LOW);
              istenilenSicaklik=sicaklik+fanSayac;
            
        }   else if(gelen.equals("4"))//manuelAyar
        {   
              fanSayac2++;
              lcdSifirla();
              lcd.setCursor(0,0);
              lcd.print("Manuel Ayar");
              lcd.setCursor(0,1);
              lcd.print("Sogutucu Fan Aktif");
              digitalWrite(fanRedPin,LOW);
              digitalWrite(fanGreenPin,HIGH);
              istenilenSicaklik2=sicaklik-fanSayac2;
        } 
        else if(gelen.equals("5")){
              sayac=0;
        }
        else if(gelen.equals("6"))//manuelAyar
        {   
              lcdSifirla();
              lcd.setCursor(0,0);
              lcd.print("Hizli Sogutucu 10*C");
              lcd.setCursor(0,1);
              lcd.print("Sogutucu Fan Aktif");
              digitalWrite(fanRedPin,LOW);
              digitalWrite(fanGreenPin,HIGH); 
        } 
      else if(gelen.equals("7"))//manuelAyar
      {   
          lcdSifirla();
          lcd.setCursor(0,0);
          lcd.print("Hizli Isitma 30*C");
          lcd.setCursor(0,1);
          lcd.print("İsitici Fan Aktif");
          digitalWrite(fanRedPin,HIGH);
          digitalWrite(fanGreenPin,LOW); 
      }
      else if(gelen.equals("8"))//manuelAyar
          {   
              ManuelYap();
              i=1;
              a=0;
          }
  
          if(gelen.equals("9")&& a==1)//manuelAyar
          {   
              lcdSifirla();
              lcd.setCursor(0,0);
              lcd.print("Isik Yakildi");
              digitalWrite(ledPin,HIGH);
              i=1;
              
           }
                          
            else if(gelen.equals("10")&& a==1)//manuelAyar
            {   
                lcdSifirla();
                lcd.setCursor(0,0);
                lcd.print("Isik sonduruldu");
                digitalWrite(ledPin,LOW);
                i=1;
                
            }

            else if(gelen.equals("11"))
            {
                     i=0;
                     sayac=0;
                     loop();
             }
            else if(gelen.equals("12")){
                  sayac=0;
            }
   
      else if(gelen.equals("") && sayac==1){
      if (analogSensor > sensorThres)
      {
          digitalWrite(redLed, HIGH);
          digitalWrite(greenLed, LOW);
          tone(buzzer, 1000, 200);
          lcdSifirla();
          lcd.setCursor(0,0);
          lcd.print("Kapilar Acildi");
      
      }
      else
      {
        digitalWrite(redLed, LOW);
        digitalWrite(greenLed, HIGH);
        noTone(buzzer);
          
          lcdSifirla();
          lcd.setCursor(0,0);
          lcd.print("Gaz Sensor");
          lcd.setCursor(0,1);
          String degerYeni="Degeri: "+(String)analogSensor;
          lcd.print(degerYeni);
      }
      }
    
    else if(gelen.equals("") && sayac==2){
        if(sicaklik<=20){
          lcdSifirla();
          lcd.setCursor(0,0);
          lcd.print("Oda Sogudu");
          lcd.setCursor(0,1);
          lcd.print(sicaklik); 
          digitalWrite(sicaklikRedLed,HIGH);
          digitalWrite(sicaklikGreenLed,LOW);
    
        }
      else if (sicaklik > 21 && sicaklik < 30){
          lcdSifirla();
          lcd.setCursor(0,0);
          lcd.print("Oda *C : Normal");
          lcd.setCursor(0,1);
          lcd.print(sicaklik);
          digitalWrite(sicaklikGreenLed, HIGH);
          digitalWrite(sicaklikRedLed,LOW);
      
        }
        else{
          lcdSifirla();
          lcd.setCursor(0,0);
          lcd.print("Oda Sicak");
          lcd.setCursor(0,1);
          lcd.print(sicaklik);
          }
          
      }
       if((sicaklik == istenilenSicaklik)&& fanSayac==1 ){
                digitalWrite(fanRedPin,LOW);
                digitalWrite(fanGreenPin,LOW);
                lcdSifirla();
                lcd.setCursor(0,0);
                lcd.print("Isitma Basarili");
                fanSayac=0;
                  sayac=0;
         }
        if((sicaklik == istenilenSicaklik2)&& fanSayac==1 ){
                digitalWrite(fanRedPin,LOW);
                digitalWrite(fanGreenPin,LOW);
                lcdSifirla();
                lcd.setCursor(0,0);
                lcd.print("Sogutma Basarili");
                fanSayac2=0;
                  sayac=0;
          }
           if(i==1){
            ManuelYap();
          }
          else if((gelen.equals("")&& sayac==3)||(gelen.equals("11")) )
          {   
              if ( i==0 && val == HIGH) { // okunan değer high ise
                  digitalWrite(ledPin, HIGH); // ledi yak
                  lcdSifirla();
                  lcd.setCursor(0,0);
                  lcd.print("Hareket Var");
              if (pirState == LOW) { // hareket sensör durumu low ise
                  pirState = HIGH; // Hareket sensör durumunu hıgh yap
                }
            i=0;
        }  
              if(i==0 && val == LOW) 
               {
                  digitalWrite(ledPin, LOW); //ledi söndür
                    lcdSifirla();
                    lcd.setCursor(0,0);
                    lcd.print("Hareket Yok");
                  if (pirState == HIGH){ 
                    pirState = LOW;
                  }
                  i=0;
                }
                sayac=0; 
      }
          
    
          
          
      Serial.print(val);
      Serial.print(";");
      Serial.print(analogSensor);
      Serial.print(";");
      Serial.println(sicaklik);
      
      delay(1000);
     }
 
 void lcdSifirla(){
    
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("                ");
  }
  void hizliSogut(){
    if(sicaklik==10)
    {
      lcd.setCursor(0,0);
      lcd.print("Hizli Sogutma Basarili");
      sayac=0;
    }
  }
    void hizliIsit(){
        if(sicaklik==30)
        {
          lcd.setCursor(0,0);
          lcd.print("Hizli İsitma Basarili");
          sayac=0;
        }
    }
    void ManuelYap(){
      if(a==0){  
      if(gelen.equals("10"))
         {
             lcdSifirla();
             lcd.setCursor(0,0);
             lcd.print("Isik Kapatildi");
             sayac=0;
             digitalWrite(ledPin,LOW);
             i=1;
             a=1;
         } 
          else if(gelen.equals("9"))
         {
             lcdSifirla();
             lcd.setCursor(0,0);
             lcd.print("Isik Acildi"); 
             sayac=0;
             digitalWrite(ledPin,HIGH);
             i=1;
             a=1;
         }
   }else{
         loop();
        }
}
   
     
  
