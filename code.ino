#include <SPI.h>
#include <printf.h>

const char endMarker = '.';

const int LEFT_SWITCH_INPUT_PIN = 22;
const int REAR_SWITCH_INPUT_PIN = 23;
const int RIGHT_SWITCH_INPUT_PIN = 24;
const int FRONT_SWITCH_INPUT_PIN = 25;

const int HOVERBOARD_DIRECTION_1_OUTPUT_PIN = 2;
const int HOVERBOARD_DIRECTION_2_OUTPUT_PIN = 3;

const int HOVERBOARD_PWN_1_OUTPUT_PIN = 4;
const int HOVERBOARD_PWN_2_OUTPUT_PIN = 5;

const int HOVERBOARD_VELOCITY_PWN_VALUE = 100;

int leftInputSwitchState = 0;
int rearInputSwitchState = 0;
int frontInputSwitchState = 0;
int rightInputSwitchState = 0;

void setup() {
  // Inputs
  pinMode(LEFT_SWITCH_INPUT_PIN, INPUT);
  pinMode(REAR_SWITCH_INPUT_PIN, INPUT);
  pinMode(RIGHT_SWITCH_INPUT_PIN, INPUT);
  pinMode(FRONT_SWITCH_INPUT_PIN, INPUT);
  // Outputs
  pinMode(HOVERBOARD_DIRECTION_1_OUTPUT_PIN, OUTPUT);
  pinMode(HOVERBOARD_DIRECTION_2_OUTPUT_PIN, OUTPUT);
  pinMode(HOVERBOARD_PWN_1_OUTPUT_PIN, OUTPUT);
  pinMode(HOVERBOARD_PWN_2_OUTPUT_PIN, OUTPUT);
}

void loop() {
  // Read inputs
  leftInputSwitchState = digitalRead(LEFT_SWITCH_INPUT_PIN);
  rearInputSwitchState = digitalRead(REAR_SWITCH_INPUT_PIN);
  rightInputSwitchState = digitalRead(RIGHT_SWITCH_INPUT_PIN);
  frontInputSwitchState = digitalRead(FRONT_SWITCH_INPUT_PIN);
  
  String receivedMessage = readMessageFromSerial();
  
  // Write outputs
  if(frontInputSwitchState == HIGH || (!isEmpty(receivedMessage) && receivedMessage.equals(String("UP")))) {
    analogWrite(HOVERBOARD_PWN_1_OUTPUT_PIN, HOVERBOARD_VELOCITY_PWN_VALUE);
    analogWrite(HOVERBOARD_PWN_2_OUTPUT_PIN, HOVERBOARD_VELOCITY_PWN_VALUE);
    digitalWrite(HOVERBOARD_DIRECTION_1_OUTPUT_PIN, HIGH);
    digitalWrite(HOVERBOARD_DIRECTION_2_OUTPUT_PIN, LOW);
  } else if(rearInputSwitchState == HIGH || (!isEmpty(receivedMessage) && receivedMessage.equals(String("DOWN")))) {
    analogWrite(HOVERBOARD_PWN_1_OUTPUT_PIN, HOVERBOARD_VELOCITY_PWN_VALUE);
    analogWrite(HOVERBOARD_PWN_2_OUTPUT_PIN, HOVERBOARD_VELOCITY_PWN_VALUE);
    digitalWrite(HOVERBOARD_DIRECTION_1_OUTPUT_PIN, LOW);
    digitalWrite(HOVERBOARD_DIRECTION_2_OUTPUT_PIN, HIGH);
  } else if(leftInputSwitchState == HIGH || (!isEmpty(receivedMessage) && receivedMessage.equals(String("LEFT")))) {
    analogWrite(HOVERBOARD_PWN_1_OUTPUT_PIN, HOVERBOARD_VELOCITY_PWN_VALUE);
    analogWrite(HOVERBOARD_PWN_2_OUTPUT_PIN, HOVERBOARD_VELOCITY_PWN_VALUE);
    digitalWrite(HOVERBOARD_DIRECTION_1_OUTPUT_PIN, LOW);
    digitalWrite(HOVERBOARD_DIRECTION_2_OUTPUT_PIN, LOW);
  } else if(rightInputSwitchState == HIGH || (!isEmpty(receivedMessage) && receivedMessage.equals(String("RIGHT")))) {
    analogWrite(HOVERBOARD_PWN_1_OUTPUT_PIN, HOVERBOARD_VELOCITY_PWN_VALUE);
    analogWrite(HOVERBOARD_PWN_2_OUTPUT_PIN, HOVERBOARD_VELOCITY_PWN_VALUE);
    digitalWrite(HOVERBOARD_DIRECTION_1_OUTPUT_PIN, HIGH);
    digitalWrite(HOVERBOARD_DIRECTION_2_OUTPUT_PIN, HIGH);
  } else {
    analogWrite(HOVERBOARD_PWN_1_OUTPUT_PIN, 0);
    analogWrite(HOVERBOARD_PWN_2_OUTPUT_PIN, 0);
  }
}

String readMessageFromSerial() {
  String ret = "";
  char receivedChar =  '-';
  while(receivedChar != endMarker) {
    while(Serial.available() > 0) {
      receivedChar = Serial.read();
      if(receivedChar != endMarker) {
        ret.concat(receivedChar);
      }
    }
  }
  return ret;
}

boolean isEmpty(String message) {
  return message == NULL || message.equals("");
}
