#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11);

int rightxPosition;
int rightyPosition;
int leftxPosition;
int leftyPosition;
int mapX;
int mapY;

int current1 = 90;
int current2 = 90;
int current3 = 90;
int current4 = 90;

bool past = false;
String lastEdit;
char lastEdit1[9];
bool isClawOpen = true;

int button2 = LOW;
int button3 = LOW;
int button4 = LOW;
int button5 = LOW;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);

  pinMode(0, INPUT);
  pinMode(1, INPUT);

  lastEdit[1] = '%';

}

void loop() {

  

  if (digitalRead(2) == HIGH && button2 == LOW) {
    // turn LED on:
    Serial.println("2");
    button2 = HIGH;

    button2f();
    
  }
  else if (digitalRead(2) == LOW) {
      button2 = LOW;
    }

    
  if (digitalRead(3) == HIGH && button3 == LOW) {
    // turn LED on:
    Serial.println("3");
    button3 = HIGH;

    button3f();
    
  }
  else if (digitalRead(3) == LOW) {
      button3 = LOW;
    }

    
  if (digitalRead(4) == HIGH && button4 == LOW) {
    // turn LED on:
    Serial.println("4");
    button4 = HIGH;
    button4f();
  }  
  else if (digitalRead(4) == LOW) {
      button4 = LOW;
    }

    
  if (digitalRead(5) == HIGH && button5 == LOW) {
    // turn LED on:
    Serial.println("5");
    button5 = HIGH;

    button5f();
    
  }
  else if (digitalRead(5) == LOW) {
      button5 = LOW;
    }

  rightxPosition = analogRead(1);
  rightyPosition = 1023-analogRead(0);

  leftxPosition = 1023 - analogRead(2);
  leftyPosition = analogRead(3);

  Serial.print(leftxPosition);
  Serial.print(" ");
  Serial.println(leftyPosition); 
  movement();
  clawMovement();

}

void button2f(){
    Serial.println("button2f"); 
  }
void button3f(){
    Serial.println("button3f"); 
    claw();
    
  }
void button4f(){
    Serial.println("button4f"); 
  }
void button5f(){
    Serial.println("button5f"); 
  }

void send(char number, String pos){
    Serial.println("button2f"); 
  }

void movement(){
    if (rightxPosition < 50){
        past = true;
        if (rightyPosition < 80){
            Serial.println("Bottom Left");
            sendDirections('S', "A");
          }
         else if (rightyPosition > 870){
            Serial.println("Top Left");
            sendDirections('W', "A");
          }
         else {
            Serial.println("Left");
            if (button2 == HIGH){
                sendDirections('T', "L");
              }
            else{
                sendDirections('L', "Q");
            }          }
      }
    else if (rightxPosition > 900){
        past = true;
        if (rightyPosition < 80){
            Serial.println("Bottom Right");
            sendDirections('S', "D");
          }
         else if (rightyPosition > 870){
            Serial.println("Top Right");
            sendDirections('W', "D");
          }
         else {
            Serial.println("Right");
            if (button2 == HIGH){
                sendDirections('T', "R");
              }
            else{
                sendDirections('R', "Q");
            }
          }
      }

     else if (rightyPosition > 900){
         past = true;
        Serial.println("Top");
        sendDirections('F', "0");
      }
     else if (rightyPosition < 50) {
        past = true;
        Serial.println("Bottom");
        sendDirections('B', "0");
      }
     else if (past == true){
        past = false;
        sendDirections('Q', "0");
      }
  }

void clawMovement(){
    if (leftxPosition < 20){
        Serial.println("Left");
        sendDirections('1', String(current1));
        current1 += 3;
        if (current1 <= 0){
            current1 = 0;
          }
      }
    else if (leftxPosition > 900){
        Serial.println("right");
        current1 -= 3;
        sendDirections('1', String(current1));
        if (current1 >= 180){
            current1 = 180;
          }
      }

     else if (leftyPosition > 900){
        Serial.println("Top");
        current3 += 3;
        sendDirections('3', String(current3));
        if (current3 >= 120){
            current3 = 120;
          }
      }
     else if (leftyPosition < 20) {
        Serial.println("Bottom");
        current3 -= 3;
        sendDirections('3', String(current3));
        if (current3 <= 9){
            current3 = 9;
          }
      }

  }

void sendDirections(char f, String s){

    lastEdit = s + "%";
    lastEdit.toCharArray(lastEdit1, lastEdit.length() + 1);
    BTSerial.write(f);
    BTSerial.write(lastEdit1);
  }
void claw(){
    if (isClawOpen == true){
        sendDirections('4', "120");
        isClawOpen = false;
      }
    else if (isClawOpen == false){
        sendDirections('4', "50");
        isClawOpen = true;
      }
    
  }
