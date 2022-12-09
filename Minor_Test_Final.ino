#include <Servo.h>

#define numOfValsRec 5
#define digitsPerValRec 1

//static const uint8_t D0   = 0;
//static const uint8_t D1   = 1;
//static const uint8_t D2   = 2;
//static const uint8_t D3   = 3;
//static const uint8_t D4   = 4;

Servo servoThumb;
Servo servoIndex;
Servo servoMiddle;
Servo servoRing;
Servo servoPinky;

int valsRec[numOfValsRec];
int stringLength = numOfValsRec * digitsPerValRec + 1; //$00000
int counter = 0;
bool counterStart = false;
String receivedString;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600) ;
  servoThumb.attach(7) ;
  servoIndex.attach(9) ;
  servoMiddle.attach(11);
  servoRing.attach(10);
  servoPinky.attach(8);
  for(int i = 0 ; i<numOfValsRec; i ++)
  {
    valsRec[i]  = 0 ;
  }

//  servoThumb.write(0) ;
//  servoIndex.write(0) ;
//  servoMiddle.write(0);
//  servoRing.write(0) ;
//  servoPinky.write(0);
}
void servoMovement(Servo s, int x)
{
  s.write(x);

 


}
void receiveData() {
  while(Serial.available())
  {
    char c = Serial.read() ;
    if(c =='$'){
      counterStart = true;
    }
    if (counterStart) {
      if (counter < stringLength){
        receivedString = String(receivedString+c) ;
        counter ++;
      }
      if (counter >=stringLength) {
        //$00000
        for(int i = 0 ; i<numOfValsRec; i ++)
        {
          int num = (i*digitsPerValRec) +1;
          valsRec[i]  = receivedString.substring(num, num + digitsPerValRec).toInt() ;
        }
        receivedString = "";
        counter = 0;
        counterStart = false;
      }
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  receiveData();
  if (valsRec[0] == 0){servoMovement(servoThumb,180) ; }else{servoMovement(servoThumb,0) ;}
  if (valsRec[1] == 0){servoMovement(servoIndex,180) ; } else{servoMovement(servoIndex,0);}
  if (valsRec[2] == 0){servoMovement(servoMiddle,180) ;}else{servoMovement(servoMiddle,0); }
  if (valsRec[3] == 0){servoMovement(servoRing,180) ; }else{servoMovement(servoRing,0) ;}
  if (valsRec[4] == 0){servoMovement(servoPinky,180); }else{servoMovement(servoPinky,0); }
}
