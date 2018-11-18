/* This section controls the activation of the pump/brew valve
    including preinfusion
    Also included is the activation of the steam valve
*/
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

void setupBrewControl() {
  pinMode(BREWBUT, INPUT_PULLUP);
  pinMode(STEAMBUT, INPUT_PULLUP);
  pinMode(BREW, OUTPUT);
  pinMode(STEAM, OUTPUT);
  pinMode(PUMP, OUTPUT);
}

void brewControl() {
  int reading = digitalRead(BREWBUT); // read the state of the switch into a local variable:
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:
  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      // only toggle the LED if the new button state is HIGH
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

