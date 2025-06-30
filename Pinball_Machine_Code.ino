#include <Servo.h>

Servo myservo; //Servo for releasing ball into plunger
unsigned char game_state; //State of the game
const int left_flipper_button = 2;
const int right_flipper_button = 6;
const int dcmotorPin = 14;
enum {initialize, start, play, end_game};
//Pins for left flipper
const int D3Pin = 3;
const int D4Pin = 4;
//Pins for right flipper
const int D7Pin = 7;
const int D8Pin = 8;
//Button to start game
const int start_button = 22;

//Scoring display
int score;
int ones;
int tens;
const byte digitMap[10] = {
  0b01111110, // 0
  0b00010010, // 1
  0b10111100, // 2
  0b10110110, // 3
  0b11010010, // 4
  0b11100110, // 5
  0b11101110, // 6
  0b00110010, // 7
  0b11111111, // 8
  0b11110110  // 9
};
const int RCLK = 12;
const int SRCLK = 11;
const int SER = 13;
const int leftseg = 50;
const int rightseg = 52;

//counting losses
int num_losses;
bool update = false;
const int loss_sensor_pin = A10;

int val;

const int buzzerpin = 40;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(left_flipper_button, INPUT);
  pinMode(right_flipper_button, INPUT);
  pinMode(dcmotorPin, OUTPUT);
  pinMode(D3Pin, INPUT);
  pinMode(D4Pin, OUTPUT);
  pinMode(D7Pin, INPUT);
  pinMode(D8Pin, OUTPUT);
  pinMode(start_button, INPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SRCLK, OUTPUT);
  pinMode(SER, OUTPUT);
  digitalWrite(leftseg, LOW);
  digitalWrite(rightseg, LOW);
  pinMode(loss_sensor_pin, INPUT);
  pinMode(buzzerpin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(game_state);
  switch(game_state){
    case initialize:
      score = 0;
      num_losses = 0;
      myservo.attach(30); //attach servo to pin 30
      myservo.write(0);
      if (digitalRead(start_button) == HIGH){
        game_state = start;
        break;
      }
      else{
        break;
      }

    case start:
      digitalWrite(RCLK, LOW);
      shiftOut(SER, SRCLK, LSBFIRST, digitMap[0]);
      digitalWrite(RCLK, HIGH);
      digitalWrite(rightseg, HIGH);
      delay(10);
      myservo.write(90); //release ball and stay released
      analogWrite(dcmotorPin, 360);  //write value to motor
      game_state = play;
      break;

    case play:
      myservo.write(90);
      //Serial.println(digitalRead(D3Pin));
      tone(buzzerpin, 523, 1000);
      if (num_losses < 3){
        //activate flippers
        Serial.println(digitalRead(D3Pin));
        if (digitalRead(D3Pin) == LOW){ //left flipper
          digitalWrite(D4Pin, HIGH);
        }
        else{
          digitalWrite(D4Pin, LOW);
        }
        if (digitalRead(D7Pin) == LOW){ //right flipper
          digitalWrite(D8Pin, HIGH);
        }
        else{
          digitalWrite(D8Pin, LOW);
        }
        //Serial.println(analogRead(loss_sensor_pin)); to debug sensor
        if (analogRead(loss_sensor_pin) < 100 && !update){
          num_losses = num_losses + 1;
          score++;
          update = true;
        }
        if (analogRead(loss_sensor_pin) > 100){
          update = false;
        }
        ones = score % 10;
        tens = (score/10) % 10;
      if (score < 10){
        digitalWrite(RCLK, LOW);
        shiftOut(SER, SRCLK, LSBFIRST, digitMap[ones]);
        digitalWrite(RCLK, HIGH);
        digitalWrite(rightseg, HIGH);
        delay(10);
      }
      else{
          digitalWrite(RCLK, LOW);
          shiftOut(SER, SRCLK, LSBFIRST, digitMap[ones]);
          digitalWrite(RCLK, HIGH);
          digitalWrite(leftseg, LOW);
          digitalWrite(rightseg, HIGH);
          delay(10);
          digitalWrite(RCLK, LOW);
          shiftOut(SER, SRCLK, LSBFIRST, digitMap[tens]);
          digitalWrite(RCLK, HIGH);
          digitalWrite(rightseg, LOW);
          digitalWrite(leftseg, HIGH);
          delay(10);
  }
        break;
      }
      else{
        game_state = end_game;
        break;
      }
    case end_game:
      myservo.write(0);
      analogWrite(dcmotorPin, 0);  //write value to motor
      game_state = initialize;
      break;
  }
}
