
// include the library code:
#include <LiquidCrystal.h>
#include <LcdBarGraph.h>


//konstanteak
const int hezetasunaPin = A0;   // Hezetasun sentsorearen PIN analogikoa
const int uraPin =  8;          // Ur bonba aktibatzeko PIN digitala
const int urMantenua = 3;       // 5-etik 1era
const int hezetasunMax = 774;   // Hezetsun sentsorearen balio maximoa
byte lcdNumCols = 16;           // BarGrapph konstantea pantailaren luzeera zehazteko
byte sensorPin = 0;             // -- value for this example


//aldagaiak
int hezetasuna = 0;       
int egoeraBerria = 0;
int egoeraZaharra = 0;
String testua = "";
 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
LcdBarGraph lbg(&lcd, 16, 0, 1);  // -- creating bargraph instance, 
                                    // format is (&lcd, lcdNumCols, start X, start Y). 
                                    // So (&lcd, 16, 0, 1) would set the bargraph length to 16 columns 
                                    // and start the bargraph at column 0 on row 1.
void setup() {
  
  // LCD pantaila hobespenak zehaztu
  lcd.begin(16, 2);
  
  // Hasierako mezua idatzi
  lcd.print("Sistema pizten...");
  
  // PINak zehaztu
  pinMode(hezetasunaPin, INPUT);
  pinMode(uraPin, OUTPUT);

  // Serie komunikazioaren datu transferentzia 9600 bps-tara zehaztu
  Serial.begin(9600);
}

void loop() {

  // Hezetasun sentsorea irakurri: 
  hezetasuna = analogRead(hezetasunaPin);

  // Serie monitorean zerrendatuko ditugu sentsorearen balioak
  Serial.println(hezetasuna);
  
  // Blink efektua ezeztatu (ondoren aktibatuko dugu behar izan ezkero)
  lcd.noBlink();

  // IF blokea: sentsorearen 
  if (hezetasuna >= 700 ) {
    egoeraBerria = 5; 
  }
  
  else if ( hezetasuna >= 500 && 
            hezetasuna < 700 ) { 
    egoeraBerria = 4;  
  }
  
  else if ( hezetasuna >= 300 && 
            hezetasuna < 500 ) { 
    egoeraBerria = 3;
  }
  
  else if ( hezetasuna >= 60 && 
            hezetasuna < 300 ) {
    egoeraBerria = 2;
  }
  
  else if ( hezetasuna < 60 ) {
    egoeraBerria= 1;
    lcd.blink(); 
  }
  
  // egoerak konparatu sentsore erroreak sahiesteko eta 
  // mantendu nahi dugun ur maila baino txikiagoa bada, ur bonba aktibatu 
  if ( (egoeraBerria == egoeraZaharra) &&
       (egoeraBerria < urMantenua) ){
      digitalWrite(uraPin, HIGH);
      delay(2000);
      digitalWrite(uraPin, LOW);    
    }

    switch (egoeraBerria) {
    case 5:
      testua = "I'm singing in the rain!";
      break;
    case 4:
      testua= "Hau hezetasuna";
      break;
    case 3:
      testua= ":D";
      break;
    case 2:
      testua= "Ura mesedez";
      break;
    case 1:
      testua= "SOS";
      break;
    default: 

    break;
  }

    
  // Pantaila garbitu
  lcd.clear();
  // Kurtsorea 0,0 koordenatuetan kokatzen dugu
  lcd.setCursor(0, 0);
  // Pantailan testua idatzi
  lcd.print(testua);
  lbg.drawValue( hezetasuna, hezetasunMax);
  // egoera zaharra gorde
  egoeraZaharra = egoeraBerria;
  
  delay(1000);

}

