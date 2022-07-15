#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int left1pin1 = 13;
int left1pin2 = 12;
int left2pin1 = 10;
int left2pin2 = 11;

int right1pin1 = 7;
int right1pin2 = 8;
int right2pin1 = 4;
int right2pin2 = 2;

int pos = 1;

bool currentNum = true;
char current[8];
char *current1 = &current[1];

void setup() {

  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);

//  digitalWrite(11, 1);
//  delay(1000);
//  digitalWrite(11, 0);

  pinMode(13, OUTPUT);

  Serial.begin(9600);
  //Initialize Bluetooth Serial Port
}
void loop() {


  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(9);
  
    
  //Write data from HC06 to Serial Monitor
  while (Serial.available()){
      char incoming = Serial.read();
      if (incoming == '%'){
          doStuff(current);
          currentNum = true;
          current[1] = 0;
          current[2] = 0;
          current[3] = 0;
          current[4] = 0;
          current[5] = 0;
          pos = 1;
        }
      else {
          if (currentNum == true){
              current[0] = incoming;
              currentNum = false;
            }
          else{
              current[pos] = incoming;
              pos += 1;
            }
        }

    }


}

void doStuff(char currentt[]){
    Serial.println(currentt);
    switch (currentt[0]){
        case '1':
          servo1.write(atoi(current1));
          break;
        case '2':
          servo2.write(atoi(current1));
          break;
        case '3':
          servo3.write(atoi(current1));
          break;
        case '4':
          servo4.write(atoi(current1));
          break;
      }
    switch (currentt[0]){
        case 'F':
          lSide(1, 0, 1, 0);
          rSide(1, 0, 1, 0);
          break;
        case 'B':
          lSide(0, 1, 0, 1);
          rSide(0, 1, 0, 1);
          break;
        case 'R':
          lSide(1, 0, 0, 1);
          rSide(0, 1, 1, 0);
          break;
        case 'L':
          lSide(0, 1, 1, 0);
          rSide(1, 0, 0, 1);
          break;
        case 'S':
          if (currentt[1] == 'A'){
              lSide(0, 1, 0, 0);
              rSide(0, 0, 0, 1);
            }
          else if (currentt[1] == 'D'){
              lSide(0, 0, 0, 1);
              rSide(0, 1, 0, 0);
            }
            break;
        case 'W':
          if (currentt[1] == 'A'){
              lSide(0, 0, 1, 0);
              rSide(1, 0, 0, 0);
            }
          else if (currentt[1] == 'D'){
              lSide(1, 0, 0, 0);
              rSide(0, 0, 1, 0);
            } 
            break;
        case 'T':
          if (currentt[1] == 'L'){
              lSide(0, 1, 0, 1);
              rSide(1, 0, 1, 0);
            }
          else if (currentt[1] == 'R'){
              lSide(1, 0, 1, 0);
              rSide(0, 1, 0, 1);
            }
          break;
        default:
          lSide(0, 0, 0, 0);
          rSide(0, 0, 0, 0);
      }

  }
void lSide(int l1, int l2, int l3, int l4){

    digitalWrite(left1pin1, l1);
    digitalWrite(left1pin2, l2);

    digitalWrite(left2pin1, l3);
    digitalWrite(left2pin2, l4);

  }

void rSide(int r1, int r2, int r3, int r4){

    digitalWrite(right1pin1, r1);
    digitalWrite(right1pin2, r2);

    digitalWrite(right2pin1, r3);
    digitalWrite(right2pin2, r4);

  }
