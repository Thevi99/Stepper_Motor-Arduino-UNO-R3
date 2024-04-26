#define Pin1  8
#define Pin2  9
#define Pin3  10
#define Pin4  11

int Motor_Step = 0; 
int Step_Delay = 5; 

bool cw = true;
bool ccw = false;

void setup()
{
  pinMode(Pin1, OUTPUT);
  pinMode(Pin2, OUTPUT);
  pinMode(Pin3, OUTPUT);
  pinMode(Pin4, OUTPUT);

  Serial.begin(9600);
  
}

void stopMotor(){
  digitalWrite(Pin1, LOW);
  digitalWrite(Pin2, LOW);
  digitalWrite(Pin3, LOW);
  digitalWrite(Pin4, LOW);
}

void OneStep2Phase(bool dir) {
  if (!dir && Motor_Step == 0) { // หากมอเตอร์หมุนถอยหลังและอยู่ที่ตำแหน่ง 0
    return; 
  }

  switch(Motor_Step){
    case 0:
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, LOW);
      digitalWrite(Pin4, LOW);
    break;
    case 1:
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, HIGH);
      digitalWrite(Pin4, LOW);
    break;
    case 2:
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, HIGH);
      digitalWrite(Pin4, HIGH);
    break;
    case 3:
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
      digitalWrite(Pin4, HIGH);
    break;
  }
  if (dir){
    Motor_Step++;
    if (Motor_Step > 3){
      Motor_Step = 0;
    }
  }else {
    Motor_Step--;
    if (Motor_Step < 0){
      Motor_Step = 3;
    }
  }
}

void FullStepOnePhase(bool dir) {
  switch(Motor_Step) {
    case 0:
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
      digitalWrite(Pin4, HIGH);
    break;

    case 1:
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, HIGH);
      digitalWrite(Pin4, LOW);
    break;

    case 2:
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, LOW);
      digitalWrite(Pin4, LOW);
    break;

    case 3:
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
      digitalWrite(Pin4, LOW);
    break;
  }

  if (dir) {
    Motor_Step++;
    if (Motor_Step > 3) {
        Motor_Step = 0;
    }
  } else {
      Motor_Step--;
      if (Motor_Step < 0) {
          Motor_Step = 3;
      }
  }
}

void HalfStep2Phase(bool dir) {
  switch(Motor_Step) {
    case 0:
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
      digitalWrite(Pin4, LOW);
    break;

    case 1:
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, LOW);
      digitalWrite(Pin4, LOW);
    break;

    case 2:
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, LOW);
      digitalWrite(Pin4, LOW);
    break;

    case 3:
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, HIGH);
      digitalWrite(Pin4, LOW);
    break;

    case 4:
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, HIGH);
      digitalWrite(Pin4, LOW);
    break;

    case 5:
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, HIGH);
      digitalWrite(Pin4, HIGH);
    break;

    case 6:
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
      digitalWrite(Pin4, HIGH);
    break;

    case 7:
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
      digitalWrite(Pin4, HIGH);
    break;
  }

  if (dir) {
    Motor_Step++;
    if (Motor_Step > 7){
      Motor_Step = 0;
    }
  } else {
    Motor_Step--;
    if (Motor_Step < 0) {
      Motor_Step = 7;
    }
  }
}


void loop(){
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    Serial.println(input);

    if ( input.substring(0, 1) == "!"){
      input.remove(0, 1);
      int val = input.toInt();
      float result = val * 5.625;
      Serial.println(String(val) + " Degree Angle");
      Serial.println(String(result) + " Steps");

      // Debug กัน Motor_Step เคลื่อน
      while (Motor_Step != 0) {
        //OneStep2Phase(!cw);
        FullStepOnePhase(!cw); 
        //HalfStep2Phase(!cw);
        delay(Step_Delay);
      }

      for (int i = 0; i < result; i++) {
        //OneStep2Phase(!cw);
        FullStepOnePhase(!cw); 
        //HalfStep2Phase(!cw);
        delay(Step_Delay);
      }
    } else if(input == "Set") {
        while (Motor_Step != 0) {
          //OneStep2Phase(cw);
          FullStepOnePhase(cw); 
          //HalfStep2Phase(cw);
          delay(Step_Delay);
        }
    } else if( input.substring(0, 5) == "swing") {
      while (Motor_Step != 0) {
        //OneStep2Phase(cw);
        FullStepOnePhase(cw); 
        //HalfStep2Phase(cw);
        delay(Step_Delay);
      }

      input.remove(0, 5);
      int val = input.toInt();
      float result = val * 5.625;
      Serial.println(String(val) + " Degree Angle");
      Serial.println(String(result) + " Steps");

      for (int i = 0; i < result; i++) {
        //OneStep2Phase(cw);
        FullStepOnePhase(cw); 
        //HalfStep2Phase(cw);
        delay(Step_Delay);
      }

      for (int i = 0; i < result; i++) {
        //OneStep2Phase(cw);
        FullStepOnePhase(!cw); 
        //HalfStep2Phase(cw);
        delay(Step_Delay);
      }

    } else {

      int val = input.toInt();
      float result = val * 5.625;
      Serial.println(String(val) + " Degree Angle");
      Serial.println(String(result) + " Steps");

      while (Motor_Step != 0) {
        //OneStep2Phase(cw);
        FullStepOnePhase(cw); 
        //HalfStep2Phase(cw);
        delay(Step_Delay);
      }

      for (int i = 0; i < result; i++) {
        //OneStep2Phase(cw);
        FullStepOnePhase(cw); 
        //HalfStep2Phase(cw);
        delay(Step_Delay);
      }
    }

    stopMotor();
    delay(1500);
  }
}
