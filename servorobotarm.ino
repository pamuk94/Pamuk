#include <Servo.h>
#define bluetooth Serial

#define minimumBase 0  //Define arm positions at max, min and mid value
#define minimumSkulder 60
#define minimumAlbue 64
#define minimumGrip 20


#define midBasePosisjon 90
#define midSkulderPosisjon 140
#define midAlbuePosisjon 100
#define midGripPosisjon 60;

#define maximumBase 170
#define maximumSkulder 180
#define maximumAlbue 160
#define maximumGrip 160

Servo servoBase, servoSkulder, servoAlbue, servoGrip;
const int grip_Pin = 11;
const int Base_Pin = 6;
const int Skulder_Pin = 5;
const int Albue_Pin = 9;

const int potPin1 = A0;
const int potPin2 = A1;
const int potPin3 = A2;
const int potPin4 = A3;

const int GREEN_LED = 13;
const int BLUE_LED = 2;
const int RED_LED = 3;

const int run_program_button = 12;
const int reset_program_button = 4;
const int lagre_posisjon_Pin = 7;

int base_Pot_ny;
int skulder_Pot_ny;
int albue_Pot_ny;
int grip_Pot_ny;

int base_Pot_gammel;
int skulder_Pot_gammel;
int albue_Pot_gammel;
int grip_Pot_gammel;

int gripPosisjon[100];
int basePosisjon[100];
int skulderPosisjon[100];
int albuePosisjon[100];

int tall_index = 0;

int lagre_posisjon;
int reset_knapp = 0;
int sjekk_bevegelse;
int fjernStyrt = 0;
int kjorLagretProgram = 0;

String command;
String device;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bluetooth.begin(9600);
  servoBase.attach(Base_Pin);
  servoSkulder.attach(Skulder_Pin);
  servoAlbue.attach(Albue_Pin);
  servoGrip.attach(grip_Pin);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, LOW);

  reset_robotPos();
  delay(2000);

  serial_pos();

}

void loop() {

  
  sjekk_om_bluetooth_verdi();
  lokalt_eller_fjernstyrt();

  kjorLagretProgram = digitalRead(run_program_button);
  if (kjorLagretProgram == HIGH || command == "runon") {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, HIGH);
    kjor_program_lagret();

    digitalWrite(RED_LED, LOW);
    serial_pos();

  }
  else {
    lagre_bevegelser();


    command = "";
  }
}


void sjekk_om_bluetooth_verdi() { 


  while(bluetooth.available()) { //kan også brukes if løkke her!
    delay(100);
    char lagre_verdi = bluetooth.read();
    Serial.println(lagre_verdi);
    device += lagre_verdi;

  }
  if(device.length()>0) {
    Serial.print("Command: ");
    Serial.print(device);
    command = device;
    device = "";
  }
  
}


void lokalt_eller_fjernstyrt() {
  if(command == "alarmon")
  {
    command = "remote";
    fjernStyrt = 0;
  }
  if (command == "remote") {  
    fjernStyrt = !fjernStyrt;

  }
}

bool les_potentiometer() { //bruker denne funksjonen for å lese potensiometer verdiene og finne ut posisjonen til roboten


  base_Pot_ny = analogRead(potPin1);
  skulder_Pot_ny = analogRead(potPin2);
  albue_Pot_ny = analogRead(potPin3);
  grip_Pot_ny = analogRead(potPin4);

  base_Pot_ny = map(base_Pot_ny, 0, 1023, 0, 180);
  skulder_Pot_ny = map(skulder_Pot_ny, 0, 1023, 0, 180);
  albue_Pot_ny  = map(albue_Pot_ny, 0, 1023, 0, 180);
  grip_Pot_ny = map(grip_Pot_ny, 0, 1023, 0, 180);

  servoBase.write(base_Pot_ny);
  servoSkulder.write(skulder_Pot_ny);
  servoAlbue.write(albue_Pot_ny);
  servoGrip.write(grip_Pot_ny);

  if (base_Pot_ny != base_Pot_gammel || skulder_Pot_ny != skulder_Pot_gammel || albue_Pot_ny != albue_Pot_gammel) {

    sjekk_bevegelse = true;
  } else {
    sjekk_bevegelse = false;
  }
  return sjekk_bevegelse;
  
}
/*
void potentiometer(){
  
  base_Pot_ny = analogRead(potPin1);
  skulder_Pot_ny = analogRead(potPin2);
  albue_Pot_ny = analogRead(potPin3);

  base_Pot_ny = map(base_Pot_ny, 0, 1023, 0, 180);
  skulder_Pot_ny = map(skulder_Pot_ny, 0, 1023, 0, 180);
  albue_Pot_ny  = map(albue_Pot_ny, 0, 1023, 0, 180);

  servoBase.write(base_Pot_ny);
  servoSkulder.write(skulder_Pot_ny);
  servoAlbue.write(albue_Pot_ny);
}
*/
void serial_pos(){ //brukte dette til å finne initial posisjonene til robotarmen

  Serial.print("Base: ");
  Serial.print(base_Pot_ny);
  delay(100);
  Serial.print("Shoulder: ");
  Serial.print(skulder_Pot_ny);
  delay(100);
  Serial.print("Elbow: ");
  Serial.print(albue_Pot_ny);
  delay(100);

  }

void reset_robotPos() { //en enkel kode for å komme tilbake til startposisjon

  base_Pot_ny = midBasePosisjon;
  skulder_Pot_ny = midSkulderPosisjon;
  albue_Pot_ny = midAlbuePosisjon;
  grip_Pot_ny = midGripPosisjon;

  servoBase.write(base_Pot_ny);
  delay(20);
  servoSkulder.write(skulder_Pot_ny);
  delay(20);
  servoAlbue.write(albue_Pot_ny);
  delay(20);
  servoGrip.write(grip_Pot_ny);
  delay(20);

  base_Pot_gammel = base_Pot_ny;
  skulder_Pot_gammel = skulder_Pot_ny;
  albue_Pot_gammel = albue_Pot_ny;
  grip_Pot_gammel = grip_Pot_ny;

}

void sett_arm_posisjon(int base, int skulder, int albue, int grip) {

  servoBase.write(base);
  delay(20);
  servoSkulder.write(skulder);
  delay(20);
  servoAlbue.write(albue);
  delay(20);
  servoGrip.write(grip);
  delay(20);

}

bool lesBluetoothVerdi() {

  char val = command[0];
  byte val1 = command[2];

  if(val == 'g'){

    grip_Pot_ny = val1;
    grip_Pot_ny = map(grip_Pot_ny, 0, 255, minimumGrip, maximumGrip);
  }

  if (val == 'b') {

    base_Pot_ny = val1;
    base_Pot_ny = map(base_Pot_ny, 0, 255, minimumBase, maximumBase);

  }
  if (val == 's') {

    skulder_Pot_ny = val1;
    skulder_Pot_ny = map(skulder_Pot_ny, 0, 255, minimumSkulder, maximumSkulder);

  }
  if (val == 'e') {

    albue_Pot_ny = val1;
    albue_Pot_ny = map(albue_Pot_ny, 0, 255, minimumAlbue, maximumAlbue);
  }

  if (base_Pot_ny != base_Pot_gammel || skulder_Pot_ny != skulder_Pot_gammel || albue_Pot_ny != albue_Pot_gammel || grip_Pot_ny != grip_Pot_gammel) {

    sjekk_bevegelse = true;
  } else {
    sjekk_bevegelse = false;
  }
  return sjekk_bevegelse;
}

void kjor_program_lagret() {

  int i;
  reset_knapp = digitalRead(reset_program_button);

  while (reset_knapp == LOW) {
    for (i = 1; i <= tall_index; i++) {

      sett_arm_posisjon(basePosisjon[i], skulderPosisjon[i], albuePosisjon[i], gripPosisjon[i]);
      delay(2000);
    }
    i = 0;
    sjekk_om_bluetooth_verdi();
    Serial.println(command);
    if (command == "rston") {
      reset_knapp = HIGH;

    } else {
      reset_knapp = digitalRead(reset_program_button);
    }
  }

  digitalWrite(RED_LED, HIGH);
  delay(1000);
  digitalWrite(BLUE_LED, LOW);
  tall_index = 0;
  reset_robotPos();

}





void lagre_bevegelser() {

  lagre_posisjon = debounce(lagre_posisjon_Pin);
  if (lagre_posisjon == HIGH || command == "pgmonpgmoff") {

    tall_index++;
    basePosisjon[tall_index] = base_Pot_ny;
    skulderPosisjon[tall_index] = skulder_Pot_ny;
    albuePosisjon[tall_index] = albue_Pot_ny;
    gripPosisjon[tall_index] = grip_Pot_ny;
    digitalWrite(GREEN_LED, HIGH);
    delay(1000);

  }
    if (!fjernStyrt && les_potentiometer()) {

    digitalWrite(GREEN_LED, LOW);
    sett_arm_posisjon(base_Pot_ny, skulder_Pot_ny, albue_Pot_ny, grip_Pot_ny);
    base_Pot_gammel = base_Pot_ny;
    skulder_Pot_gammel = skulder_Pot_ny;
    albue_Pot_gammel = albue_Pot_ny;
    grip_Pot_gammel = grip_Pot_ny;

  }
  if (fjernStyrt && lesBluetoothVerdi()) {

    digitalWrite(GREEN_LED, LOW);
    sett_arm_posisjon(base_Pot_ny, skulder_Pot_ny, albue_Pot_ny, grip_Pot_ny);
    base_Pot_gammel = base_Pot_ny;
    skulder_Pot_gammel = skulder_Pot_ny;
    albue_Pot_gammel = albue_Pot_ny;
    grip_Pot_gammel = grip_Pot_ny;

  }
}

boolean debounce(int knapp) {
  boolean debouncer;
  boolean debouncer1;
  int debouncer3 = 60;
  int k;

  debouncer1 = digitalRead(knapp);
  for (k = 0; k < debouncer3; k++) {
    delay(10);
    debouncer = digitalRead(knapp);
    if (debouncer != debouncer1) {
      k = 0;
      debouncer1 = debouncer;
    }
  }
  return debouncer;
}



