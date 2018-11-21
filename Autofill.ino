//Start Autofill

//Set states
int autofill_state = 0;
long autofill_time = 0;

void setupAutofill() {
  pinMode(AUTOFILL, OUTPUT);
  digitalWrite(AUTOFILL, LOW);
}

void toggle_autofill(int state) {
  if (state == autofill_state) {
    return;
  }
  if (state == 0) {
    if ((millis() - autofill_time) > AUTOFILL_DELAY) {
      digitalWrite(AUTOFILL, HIGH); // High is off
      autofill_state = state;
    }
  } else {
    digitalWrite(AUTOFILL, LOW);
    autofill_state = state;
  }
  return;
}

void updateAutofill() {
  // Read level sensor
  boiler.check();
  // If boiler water is low turn on autofill valve
  if (boiler.value == 0) {
    toggle_autofill(0);
  } else {
    toggle_autofill(1);
  }
}
//end Autofill
