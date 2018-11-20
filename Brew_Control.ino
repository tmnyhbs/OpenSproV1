/* This section controls the activation of the pump/brew valve
    including preinfusion
    Also included is the activation of the steam valve
*/
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime2 = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin 
int buttonState2;             // the current reading from the input pin
int lastButtonState2 = LOW;   // the previous reading from the input pin 

void setupBrewControl() {
  pinMode(BREWBUT, INPUT_PULLUP);
  pinMode(STEAMBUT, INPUT_PULLUP);
  pinMode(BREW, OUTPUT);
  pinMode(STEAM, OUTPUT);
  pinMode(PUMP, OUTPUT);
}

void brewControl() {
  int reading = digitalRead(BREWBUT); // read the state of the switch into a local variable:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      // only toggle the brew cycle if the new button state is HIGH
      if (buttonState == HIGH) {
        lastButtonState = reading; // save the reading. Next time through the loop, it'll be the lastButtonState
        digitalWrite(BREW, HIGH);
        delay(PREINF_DELAY);
        digitalWrite(PUMP, HIGH);
        if ((millis() - lastDebounceTime) > debounceDelay) {
          // whatever the reading is at, it's been there for longer than the debounce
          // delay, so take it as the actual current state:
          // if the button state has changed:
          if (reading != buttonState) {
            buttonState = reading;
            // only toggle the LED if the new button state is HIGH
            if (buttonState == HIGH) {
              digitalWrite(PUMP, LOW);
              digitalWrite(BREW, LOW);
            }
          }
        }
        lastButtonState = reading; // save the reading. Next time through the loop, it'll be the lastButtonState:
      }
    }
  }
}

void steamControl() {
  int reading2 = digitalRead(STEAMBUT); // read the state of the switch into a local variable:
  if (reading2 != lastButtonState2) {
    // reset the debouncing timer
    lastDebounceTime2 = millis();
  }
  if ((millis() - lastDebounceTime2) > debounceDelay) {
    if (reading2 != buttonState2) {
      buttonState2 = reading2;
      // only toggle the brew cycle if the new button state is HIGH
      if (buttonState2 == HIGH) {
        lastButtonState2 = reading2; // save the reading. Next time through the loop, it'll be the lastButtonState
        digitalWrite(STEAM, HIGH);
        if ((millis() - lastDebounceTime2) > debounceDelay) {
          // whatever the reading is at, it's been there for longer than the debounce
          // delay, so take it as the actual current state:
          // if the button state has changed:
          if (reading2 != buttonState2) {
            buttonState2 = reading2;
            // only toggle the LED if the new button state is HIGH
            if (buttonState2 == HIGH) {
              digitalWrite(STEAM, LOW);
            }
          }
        }
        lastButtonState2 = reading2; // save the reading. Next time through the loop, it'll be the lastButtonState:
      }
    }
  }
}
