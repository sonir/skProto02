const int ON = 66; //66
const int OFF = 0;

const int playPin = 11;
const int recPin = 10;
const int stopPin = 6;

//For Timer
const long duration = 3000;
const long ignore_time = 500;
unsigned long st = 0;
unsigned long now = 0;
//State
byte playing = false;


//Parameters
const int shock_sense = 30;

//My Variables
int count = 0;

void setup() {

  //Setup Pins' Mode
  pinMode(playPin, OUTPUT);
  pinMode(recPin, OUTPUT);
  pinMode(stopPin, OUTPUT);

  //Start Serial Communication
  Serial.begin(9600);
  //Init Pins
  analogWrite(playPin, OFF);
  analogWrite(stopPin, OFF);

  //rec once
  analogWrite(recPin, ON);
  delay(5000);
  analogWrite(recPin, OFF);
}

void loop() {
  //Get now time
  now = millis();

//rec by Serial message
  if (Serial.read() > 0) {
    analogWrite(recPin, ON);
    delay(5000);
    analogWrite(recPin, OFF);
  }


//Timer Process(Normal Stop of sample)
if(playing==true){ //Check should stop or not the playbacking sound


  if( timer(duration) ){ //If played 3sec, stop
    Serial.println("timer stop");
    analogWrite(playPin, OFF);
    playing = false;
  }

}


//play by
  int shock = analogRead(A0);
  if (shock > shock_sense) {

      if(playing==false){
        /*Serial.println("Shocked");*/
        Serial.println(shock);
      triggerSound();

      }else {

          if( timer(ignore_time) ){
              interruppt();
          }
    }

  }


} //end of loop


boolean timer(long span){

  if( playing && ( now - st  >= span) ) return true;
  else return false;

}

void interruppt(){

            Serial.println("interruppt");
            analogWrite(playPin, OFF);

            analogWrite(stopPin, ON);
            delay(100);        
            analogWrite(stopPin, OFF);

            // st = now; //update the time
            // analogWrite(playPin,ON);
            triggerSound();

}


void triggerSound(){

      playing = true;
      st = now;
      count++;
      Serial.println(count);
      analogWrite(playPin, ON);

}