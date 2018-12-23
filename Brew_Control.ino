/* This section controls the activation of the pump, brew valve, and steam valve
*/

const uint32_t debounceTime = 5;  // 5 mSec, enough for most switches
const bool switchOn  = false;     // using INPUT_PULLUP
const bool switchOff = true;
int timer = 0;
secTimer shotTimer;

//for brew
bool lastStateB   = switchOff;
bool newStateB    = switchOff;
bool toggleStateB = false;

//for steam
bool lastStateS   = switchOff;
bool newStateS   = switchOff;
bool toggleStateS = false;

void setupControls() {
  pinMode(BREWBUT, INPUT_PULLUP);
  pinMode(STEAMBUT, INPUT_PULLUP);
  pinMode(BREW, OUTPUT);
  pinMode(STEAM, OUTPUT);
  pinMode(PUMP, OUTPUT);
}

void updateBrewControl()
{
  newStateB = digitalRead(BREWBUT);
  if ( lastStateB != newStateB ) // state changed
  {
    delay( debounceTime );
    lastStateB = newStateB;
    // push on, push off
    if ( newStateB == switchOn && toggleStateB == false )
    {
      toggleStateB = true;
      shotTimer.startTimer();
      digitalWrite(BREWLED, HIGH);
      digitalWrite(BREW, HIGH );
      delay(PREINF_DELAY);
      digitalWrite(PUMP, HIGH );
    }
    else if ( newStateB == switchOn && toggleStateB == true )
    {
      toggleStateB = false;
      digitalWrite(PUMP, LOW );
      digitalWrite(BREW, LOW );
      digitalWrite(BREWLED, LOW);
      shotTimer.stopTimer();

    }
  }
}

void updateSteamControl()
{
  newStateS = digitalRead(STEAMBUT);
  if ( lastStateS != newStateS ) // state changed
  {
    delay( debounceTime );
    lastStateS = newStateS;
    // push on, push off
    if ( newStateS == switchOn && toggleStateS == false )
    {
      toggleStateS = true;
      digitalWrite(STEAM, HIGH );
      digitalWrite(STEAMLED, HIGH);
    }
    else if ( newStateS == switchOn && toggleStateS == true )
    {
      toggleStateS = false;
      digitalWrite(STEAM, LOW );
      digitalWrite(STEAMLED, LOW);
    }
  }
}


