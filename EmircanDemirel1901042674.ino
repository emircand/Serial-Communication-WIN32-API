const int ledPin =  13;      // the number of the LED pin
const int buttonPin = 8;

int currentState = 0;
int previouseState = 0;
int count = 0;

String val;
int cho;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin,INPUT);
  Serial.begin(9600);
  Serial.setTimeout(5);
}


void loop() {
  String incoming;
  long int num = 0;

  while (Serial.available()==0){}

  val = Serial.readString();
  cho = val.toInt();

  if(cho == 1){
    digitalWrite(ledPin, HIGH);
    }
  else if(cho == 2){
    digitalWrite(ledPin, LOW);
    }
  else if(cho == 3){
    digitalWrite(ledPin, HIGH);
    delay(175);
    digitalWrite(ledPin, LOW);
    delay(175);
     digitalWrite(ledPin, HIGH);
    delay(175);
    digitalWrite(ledPin, LOW);
    delay(175);
     digitalWrite(ledPin, HIGH);
    delay(175);
    digitalWrite(ledPin, LOW);
    delay(175);
    }
  else if(cho == 4){
    while(Serial.available() == 0){}

      while(num == 0){
          incoming = Serial.readString();
          num = incoming.toInt();
        }

      if(num != 0){
          Serial.print("square of the number: ");
          Serial.println(sq(num));
        }  
    }
  else if (cho == 5){
      while(Serial.available() == 0){
          currentState = digitalRead(buttonPin);
          if(currentState != previouseState){
              if(currentState == HIGH){
                count++;
                Serial.print("buttonCounts: ");
                Serial.println(count);
                delay(199);
                }
            }
         previouseState = currentState; 
        }
    }       
}
