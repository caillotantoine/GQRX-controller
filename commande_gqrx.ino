#include <LiquidCrystal.h>
//#include <string.h>

#define potA A0 // potentiometre pour MHz
#define potB A1// potentiometre pour KHz

#define butP 9  // selection type modulation +
#define butM 6  // selection type modulation -

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int potAVal = 0;
int potBVal = 0;

int freq = 0;
int bufF = 0;
char freq_to_send[10] = {0};
char freq_to_print[10] = {0};

char mod[20] = {0};
int modN = 0;

int butPstate = 0;
int butMstate = 0;

int i = 0;
int j = 0;

bool flagSend = false;


void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);

  Serial.begin(9600);
  
  pinMode(butP, INPUT);
  pinMode(butM, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  bufF = freq;
  potAVal = map(analogRead(potA), 0, 1023, 8, 70);
  potBVal = map(analogRead(potB), 0, 1023, 0, 99);

  butPstate = digitalRead(butP);
  butMstate = digitalRead(butM);

  freq = potAVal*100 + potBVal;

  sprintf(freq_to_send,"F %ld" , freq*100000);

  
  if(freq/10 < 100){
    sprintf(freq_to_print,"0%d.%d MHz" , freq/10, freq - (freq/10)*10);
  }
  else{
    sprintf(freq_to_print,"%d.%d MHz" , freq/10, freq - (freq/10)*10);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(freq_to_print);

  if(butPstate == HIGH){ // sélection de la démodulation
    flagSend = true;
    modN+=1;
    if(modN > 11){
      modN = 0;
    }
  }
  if(butMstate == HIGH){
    flagSend = true;
    modN-=1;
    if(modN < 0){
      modN = 11;
    }
  }
  
  switch(modN){ //types de démodulations
    case 0:
      sprintf(mod, "M OFF");
      lcd.setCursor(0, 1);
      lcd.print("DEMOD: OFF");
      break;

    case 1:
      sprintf(mod, "M RAW");
      lcd.setCursor(0, 1);
      lcd.print("DEMOD: RAW IQ");
      break;

    case 2:
      sprintf(mod, "M AM");
      lcd.setCursor(0, 1);
      lcd.print("DEMOD: AM");
      break;

     case 3:
      sprintf(mod, "M FM");
      lcd.setCursor(0, 1);
      lcd.print("DEMOD: FM");
      break;

     case 4:
      sprintf(mod, "M WFM");
      lcd.setCursor(0, 1);
      lcd.print("DEMOD: Wide FM");
      break;

     case 5:
      sprintf(mod, "M WFM_ST");
      lcd.setCursor(0, 1);
      lcd.print("DEMOD: WFMSTereo");
      break;

     case 6:
      sprintf(mod, "M WFM_ST_OIRT");
      lcd.setCursor(0, 1);
      lcd.print("DEMOD: WFMSTOIRT");
      break;

     case 7:
      sprintf(mod, "M LSB");
      lcd.setCursor(0, 1);
      lcd.print("DEMOD: LSB");
      break;

     case 8:
      sprintf(mod, "M USB");
      lcd.setCursor(0, 1);
      lcd.print("DEMOD: USB");
      break;

     case 9:
      sprintf(mod, "M CW");
      lcd.setCursor(0, 1);
      lcd.print("DEMOD: CW");
      break;

     case 10:
      sprintf(mod, "M CWL");
      lcd.setCursor(0, 1);
      lcd.print("DEMOD: CWL");
      break;

     case 11:
      sprintf(mod, "M CWU");
      lcd.setCursor(0, 1);
      lcd.print("DEMOD: CWU");
      break;
     
    default:
      break;
  }

  if(flagSend){
    Serial.print(mod); //on indique le nouveau type de démodulation
    delay(250);
    flagSend = false;
  }

    Serial.print(freq_to_send);  //on met à jour la fréquence
  delay(250);
}
