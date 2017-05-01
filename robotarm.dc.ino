#define bluetooth Serial

#define joyMid 510
#define joyMax 1020
#define joyMin 0

const int baseMotorEnablePin = 2;
const int baseMotorPin1 = 30; 
const int baseMotorPin2 = 31;
const int shoulderMotorEnablePin = 3;
const int shoulderMotorPin1 = 36;
const int shoulderMotorPin2 = 37; 
const int elbowMotorEnablePin = 4;
const int elbowMotorPin1 = 32; 
const int elbowMotorPin2 = 33;
const int wristMotorEnablePin = 5;
const int wristMotorPin1 = 35;
const int wristMotorPin2 = 34;
const int handMotorEnablePin = 6;
const int handMotorPin1 = 38; 
const int handMotorPin2 = 39;


const int joy_x = A9;
const int joy_y = A8;
const int joy_x_2 = A6;
const int joy_y_2 = A5;

const int robot_led = 43;
const int photo_sensor = A0;

int photo_value = 0;
int photo_input = 20;

int motor_max = 255;
int motor_min = 100;
int motor_speed = 0;

int joy_pusterom_opp = joyMid + 30;
int joy_pusterom_ned = joyMid - 30;

int in_data;

int joyX;
int joyY;
int joyX_2;
int joyY_2;

void setup() {
  // put your setup code here, to run once:
  
  pinMode(baseMotorPin1, OUTPUT);
  pinMode(baseMotorPin2, OUTPUT);
  pinMode(baseMotorEnablePin, OUTPUT);
  digitalWrite(baseMotorEnablePin, LOW);
  pinMode(shoulderMotorPin1, OUTPUT);
  pinMode(shoulderMotorPin2, OUTPUT);
  pinMode(shoulderMotorEnablePin, OUTPUT);
  digitalWrite(shoulderMotorEnablePin, LOW);
  pinMode(elbowMotorPin1, OUTPUT);
  pinMode(elbowMotorPin2, OUTPUT);
  pinMode(elbowMotorEnablePin, OUTPUT);
  digitalWrite(elbowMotorEnablePin, LOW);
  pinMode(wristMotorPin1, OUTPUT);
  pinMode(wristMotorPin2, OUTPUT);
  pinMode(wristMotorEnablePin, OUTPUT);
  digitalWrite(wristMotorEnablePin, LOW);
  pinMode(handMotorPin1, OUTPUT);
  pinMode(handMotorPin2, OUTPUT);
  pinMode(handMotorEnablePin, OUTPUT);
  digitalWrite(handMotorEnablePin, LOW);

 
  pinMode(joy_y, INPUT);
  pinMode(joy_x, INPUT);
  pinMode(robot_led, OUTPUT);
  digitalWrite(robot_led, LOW);
  
    Serial.begin(9600);
  bluetooth.begin(9600);
  Serial.print("Start");

}

void loop() {
  // put your main code here, to run repeatedly:
  phSensor();
  bluetooth_control();
  joy_controller_x();
  joy_controller_y();
  
  joy_controller_x_v2();
  joy_controller_y_v2();

 }

void phSensor(){

  photo_value = analogRead(photo_sensor);
  Serial.println("Photo: ");
  Serial.println(photo_value);
  delay(1000);

  if(photo_value < photo_input){
    digitalWrite(robot_led, HIGH);
  }else{
    digitalWrite(robot_led, LOW);
  }
   
}

void joy_controller_y_v2(){

  joyY_2 = analogRead(joy_y_2);
  
  
  if(joyY_2 > joy_pusterom_opp){

    motor_speed = map(joyY_2, joy_pusterom_opp, joyMax, motor_min, motor_max);

    digitalWrite(wristMotorPin1, HIGH);
    digitalWrite(wristMotorPin2, LOW);
    analogWrite(wristMotorEnablePin, motor_speed);
    Serial.println(motor_speed);
    
  }else if(joyY_2 < joy_pusterom_ned){
    motor_speed = map(joyY_2, joy_pusterom_ned, joyMin, motor_min, motor_max);
    digitalWrite(wristMotorPin1, LOW);
    digitalWrite(wristMotorPin2, HIGH);
    analogWrite(wristMotorEnablePin, motor_speed);
    Serial.println(motor_speed);
  }else{
    analogWrite(wristMotorEnablePin, 0);
  }
  
}

void joy_controller_x_v2(){
  
  joyX_2 = analogRead(joy_x_2);
  

  if(joyX_2 > joy_pusterom_opp){

    motor_speed = map(joyX_2, joy_pusterom_opp, joyMax, motor_min, motor_max);

    digitalWrite(elbowMotorPin1, HIGH);
    digitalWrite(elbowMotorPin2, LOW);
    analogWrite(elbowMotorEnablePin, motor_speed);
    Serial.println(motor_speed);
    
  }else if(joyX_2 < joy_pusterom_ned){
    motor_speed = map(joyX_2, joy_pusterom_ned, joyMin, motor_min, motor_max);
    digitalWrite(elbowMotorPin1, LOW);
    digitalWrite(elbowMotorPin2, HIGH);
    analogWrite(elbowMotorEnablePin, motor_speed);
    Serial.println(motor_speed);
  }else{
    analogWrite(elbowMotorEnablePin, 0);
  }
 
}

void joy_controller_x(){
  
  joyX = analogRead(joy_x);
  

  if(joyX > joy_pusterom_opp){

    motor_speed = map(joyX, joy_pusterom_opp, joyMax, motor_min, motor_max);

    digitalWrite(baseMotorPin1, HIGH);
    digitalWrite(baseMotorPin2, LOW);
    analogWrite(baseMotorEnablePin, motor_speed);
    Serial.println(motor_speed);
    
  }else if(joyX < joy_pusterom_ned){
    motor_speed = map(joyX, joy_pusterom_ned, joyMin, motor_min, motor_max);
    digitalWrite(baseMotorPin1, LOW);
    digitalWrite(baseMotorPin2, HIGH);
    analogWrite(baseMotorEnablePin, motor_speed);
    Serial.println(motor_speed);
  }else{
    analogWrite(baseMotorEnablePin, 0);
  }
  
}

void joy_controller_y(){

  joyY = analogRead(joy_y);
  
  
  if(joyY > joy_pusterom_opp){

    motor_speed = map(joyY, joy_pusterom_opp, joyMax, motor_min, motor_max);

    digitalWrite(shoulderMotorPin1, HIGH);
    digitalWrite(shoulderMotorPin2, LOW);
    analogWrite(shoulderMotorEnablePin, motor_speed);
    Serial.println(motor_speed);
    
  }else if(joyY < joy_pusterom_ned){
    motor_speed = map(joyY, joy_pusterom_ned, joyMin, motor_min, motor_max);
    digitalWrite(shoulderMotorPin1, LOW);
    digitalWrite(shoulderMotorPin2, HIGH);
    analogWrite(shoulderMotorEnablePin, motor_speed);
    Serial.println(motor_speed);
  }else{
    analogWrite(shoulderMotorEnablePin, 0);
  }
  
}

void finn_joy_pos(){


  Serial.print("\n");
  Serial.print("x-axis: ");
  Serial.print(analogRead(joy_x));
  Serial.print("\n");
  Serial.print("y-axis: ");
  Serial.println(analogRead(joy_y));
  Serial.print("\n");
  delay(2000);
   
      
  
}

void bluetooth_control(){
  if(bluetooth.available()>0){
  in_data = Serial.read();
  switch(in_data){
    case '1':
    digitalWrite(baseMotorEnablePin, 255);
    digitalWrite(baseMotorPin1, HIGH);
    digitalWrite(baseMotorPin2, LOW);
    Serial.println("BASE venstre");
    delay(200);
    digitalWrite(baseMotorPin1, LOW);
    digitalWrite(baseMotorPin2, LOW);
    break;
    case '2':
    digitalWrite(baseMotorEnablePin, 255);
    digitalWrite(baseMotorPin1, LOW);
    digitalWrite(baseMotorPin2, HIGH);
    Serial.println("BASE høyre");
    delay(200);
    digitalWrite(baseMotorPin1, LOW);
    digitalWrite(baseMotorPin2, LOW);
    
    break;
    case '3':
    digitalWrite(shoulderMotorEnablePin, 255);
    digitalWrite(shoulderMotorPin1, LOW);
    digitalWrite(shoulderMotorPin2, HIGH);
    Serial.println("SKULDER Framover");
    delay(200);
    digitalWrite(shoulderMotorPin1, LOW);
    digitalWrite(shoulderMotorPin2, LOW);
    break;
    case '4':
    digitalWrite(shoulderMotorEnablePin, 255);
    digitalWrite(shoulderMotorPin1, HIGH);
    digitalWrite(shoulderMotorPin2, LOW);
    Serial.println("SKULDER bakover");
    delay(200);
    digitalWrite(shoulderMotorPin1, LOW);
    digitalWrite(shoulderMotorPin2, LOW);
    break;
    case '5':
    digitalWrite(baseMotorEnablePin, LOW);
    digitalWrite(elbowMotorEnablePin, LOW);
    digitalWrite(shoulderMotorPin2, LOW);
    digitalWrite(wristMotorPin1, LOW);
    Serial.println("STOP");
    break;
    case 'C':
    digitalWrite(elbowMotorEnablePin, 255);
    digitalWrite(elbowMotorPin1, HIGH);
    digitalWrite(elbowMotorPin2, LOW);
    Serial.println("Albue framover");
    delay(200);
    digitalWrite(elbowMotorPin1, LOW);
    digitalWrite(elbowMotorPin2, LOW);
    break;
    case 'D':
    digitalWrite(elbowMotorEnablePin, 255);
    digitalWrite(elbowMotorPin1, LOW);
    digitalWrite(elbowMotorPin2, HIGH);
    Serial.println("Albue bakover");
    delay(200);
    digitalWrite(elbowMotorPin1, LOW);
    digitalWrite(elbowMotorPin2, LOW);
    break;
    case 'E':
    digitalWrite(wristMotorEnablePin, 255);
    digitalWrite(wristMotorPin1, HIGH);
    digitalWrite(wristMotorPin2, LOW);
    Serial.println("Albue framover");
    delay(200);
    digitalWrite(wristMotorPin1, LOW);
    digitalWrite(wristMotorPin2, LOW);
    break;
    case 'F':
    digitalWrite(wristMotorEnablePin, 255);
    digitalWrite(wristMotorPin1, LOW);
    digitalWrite(wristMotorPin2, HIGH);
    Serial.println("Håndledd framover");
    delay(200);
    digitalWrite(wristMotorPin1, LOW);
    digitalWrite(wristMotorPin2, LOW);
 }
  
  }}

