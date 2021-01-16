


const int keyPlusA  = 10;
const int keyMinusA = 16;
const int keyBreakA = 5;
const int keyPlusB  = 2;
const int keyMinusB = 3;
const int keyBreakB = 7;


const int pwmAPin = 6; 
const int pwmBPin = 11;
const int dirAPin = 12;
const int dirBPin = 13;
const int brakeAPin = 8;
const int brakeBPin = 9;


int speedA = 0;
int speedB = 0;

void setup()
 {
   pinMode(keyPlusA, INPUT);
   pinMode(keyMinusA, INPUT);
   pinMode(keyBreakA, INPUT);
   pinMode(keyPlusB, INPUT);
   pinMode(keyMinusB, INPUT);
   pinMode(keyBreakB, INPUT);
   

   pinMode(pwmAPin, OUTPUT);
   pinMode(pwmBPin, OUTPUT);
   pinMode(dirAPin, OUTPUT);
   pinMode(dirBPin, OUTPUT);
   pinMode(brakeAPin, OUTPUT);
   pinMode(brakeBPin, OUTPUT);

  

  Serial.begin(9600); 
 }

int oldPlusA  = 0;
int oldMinusA = 0;
int oldBreakA = 0;
int oldPlusB  = 0;
int oldMinusB = 0;
int oldBreakB = 0;

void checkKeys()
 { 
   int plusA = digitalRead(keyPlusA)?0:1;
   if (plusA == oldPlusA)
      plusA = 0;
   else
      oldPlusA = plusA;
   int minusA = digitalRead(keyMinusA)?0:1;
   if (minusA == oldMinusA)
      minusA = 0;
   else
      oldMinusA = minusA;
   int breakA = digitalRead(keyBreakA)?0:1;
   if (breakA == oldBreakA)
      breakA = 0;
   else
      oldBreakA = breakA;
   int plusB = digitalRead(keyPlusB)?0:1;
   if (plusB == oldPlusB)
      plusB = 0;
   else
      oldPlusB = plusB;
   int minusB = digitalRead(keyMinusB)?0:1;
   if (minusB == oldMinusB)
      minusB = 0;
   else
      oldMinusB = minusB;
   int breakB = digitalRead(keyBreakB)?0:1;
   if (breakB == oldBreakB)
      breakB = 0;
   else
      oldBreakB = breakB;


   if (plusA)
    { speedA += 50;
      if (speedA > 250)
         speedA = 250;
    }
   if (minusA)
    { speedA -= 50;
      if (speedA < -250)
         speedA = -250;
    }
   if (breakA)
      speedA = 0;
   if (plusB)
    { speedB += 50;
      if (speedB > 250)
         speedB = 250;
    }
   if (minusB)
    { speedB -= 50;
      if (speedB < -250)
         speedB = -250;
    }
   if (breakB)
      speedB = 0;
 }

void loop()
 { int oldSpeedA = speedA;
   int oldSpeedB = speedB;
      
   checkKeys();
  
   analogWrite(pwmAPin, abs(speedA));
   analogWrite(pwmBPin, abs(speedB));


   digitalWrite(dirAPin, (speedA > 0)?1:0);
   digitalWrite(dirBPin, (speedB > 0)?1:0);


   digitalWrite(brakeAPin, (speedA == 0)?1:0);
   digitalWrite(brakeBPin, (speedB == 0)?1:0);

   if (speedA != oldSpeedA || speedB != oldSpeedB)
    { 
      Serial.print("Speed A = ");
      Serial.print(speedA);
      Serial.print(" B = ");
      Serial.print(speedB);
      Serial.print("\r\n");
    }
      
 }
