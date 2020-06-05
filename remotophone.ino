//Author: Joey Corbett
//Github: sparpo
//Date: 06/06/2020
//This is a musical instrument which you can play with your TV remote control. It uses the numbers on the remote.

//TV Remotophone

// IR Receiver Code...
#include <IRremote.h>

//These codes at based on a LG TV remote.
// initialize the library with the numbers of the interface pins
#define repeat 4294967295
#define R0 551487735
#define R1 551520375
#define R2 551504055
#define R3 551536695
#define R4 551495895
#define R5 551528535
#define R6 551512215
#define R7 551544855
#define R8 551491815
#define R9 551524455

#define pageUp 551485695
#define pageDown 551518335


//note freqencies in millihertz
#define C 261626
#define D 293665
#define E 329628
#define F 349228
#define G 391995
#define A 440000
#define B 493883


unsigned long previousMillis = 0;
const long interval = 120;

int RECV_PIN = 6; //reciever at pin 6
IRrecv irrecv(RECV_PIN);

decode_results results;
int buzzerPin = 5; //buzzer at pin 5
uint32_t currentNote = A;
int transpose = 0;

int playing = 0;

void playNote(uint32_t f) {// input frequency in millihertz
  uint32_t d = (1000000 / ((f / 1000) * pow(2, transpose))) / 2; //((1000000us)/(44000cHz/100))/2
  digitalWrite(buzzerPin, HIGH);
  delayMicroseconds(d);
  digitalWrite(buzzerPin, LOW);
  delayMicroseconds(d);

}

void setup()
{
  Serial.begin(9600);

  irrecv.enableIRIn(); // Start the receiver

  pinMode(9, OUTPUT); // Led outputs ...
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.print("IR Waiting...");
}
void turnoff() {
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}
void loop() {

  unsigned long currentMillis = millis();
  //playing = 0;
  if (currentMillis - previousMillis >= interval) {
    if (irrecv.decode(&results)) {
      Serial.println(1);
      switch (results.value) {

        case pageUp: //increase octave
          transpose++;
          Serial.println(transpose);
          break;

        case pageDown://decrease octave
          transpose--;
          Serial.println(transpose);
          break;

        case repeat:
          playing = 1;

          break;

        case R1:
          currentNote = C;
          playing = 1;
          break;

        case R2:
          currentNote = D;
          playing = 1;
          break;

        case R3:
          currentNote = E;
          playing = 1;
          break;

        case R4:
          currentNote = F;
          playing = 1;
          break;
          
        case R5:
          currentNote = G;
          playing = 1;
          break;

        case R6:
          currentNote = A;
          playing = 1;
          break;

        case R7:
          currentNote = B;
          playing = 1;
          break;
          
        case R8:
          currentNote = C * 2; //high C
          playing = 1;
          break;
      }

      irrecv.resume(); // Receive the next value
    } else {
      playing = 0;
      Serial.println(0);
    }

    previousMillis = currentMillis;
  }
  if (playing) {
    playNote(currentNote);
  }
}
