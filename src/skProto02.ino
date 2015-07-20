const int ON = 66; //66
const int OFF = 0;

const int playPin = 11;
const int recPin = 10;

//For Timer
const long duration = 4000; //playback duration
const long ignore_time = 150;
const long double_click = 400;
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

  //Start Serial Communication
  Serial.begin(9600);
  //Init Pins
  digitalWrite(playPin, LOW); //AnalogWrite → DigitalWrite 
  //Rec when stary
  // rec();

}

void loop() {
  //Get now time
  now = millis();

//rec by Serial message
  if (Serial.read() > 0) {

    rec();

  }


//Timer Process(Normal Stop of sample)
if(playing==true){ //Check should stop or not the playbacking sound


  if( timer(duration) ){ //If played 3sec, stop
    Serial.println("timer stop");
    digitalWrite(playPin, LOW);
    playing = false;
  }

}


//play by
  int shock = analogRead(A0);
  if (shock > shock_sense) {

      if(playing==false){
        /*Serial.println("Shocked");*/
        Serial.print(F("SHOCK: ")); Serial.println(shock);
        triggerSound();

      }else{

          if( playing==true && timer(ignore_time) && !timer(double_click)){
            int foo = now -st;
            Serial.print(F("rec:"));  Serial.println(foo);
            rec();

          }else if( timer(ignore_time) ){
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
            digitalWrite(playPin, LOW);
            delay(100);        
            triggerSound();

}


void triggerSound(){

      Serial.println(F("triggerSound"));
      playing = true;
      st = now;
      count++;
      Serial.println(count);
      digitalWrite(playPin, HIGH);

}


void rec(){

  playing = false;
  analogWrite(recPin, ON);
  delay(5000);
  analogWrite(recPin, OFF);

}