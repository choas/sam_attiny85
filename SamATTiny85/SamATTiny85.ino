const int ledPin0   = 0;
const int ledPin1   = 1;
const int touchPin  = 3;
const long interval = 4000;

int ledState0 = LOW;
int ledState1 = LOW;

unsigned long previousMillis = 0;

unsigned long touchMillis = 0;
bool touchState = false;

int mode = 0;

int sosa[] = {1,1,1,0,3,3,3,0,1,1,1,0};
int sosp = 0;
int sosv = -1;

void setup() {
  pinMode(ledPin0, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(touchPin, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (touchMillis == 0 || digitalRead(touchPin) == LOW) {
    touchMillis = currentMillis;
  }

  if (currentMillis - touchMillis > interval * 2) {
    if (!touchState) {
      touchState = true;
      mode += 1;
      if (mode > 4) {
        mode = 0;
      }
      sosp = 0;
    }
  } else {
      touchState = false;
  }

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    switch(mode) {
      case 0:
        ledState0 = !ledState0;
        ledState1 = ledState0;
        break;
        
      case 1:
        ledState0 = !ledState0;
        ledState1 = !ledState0;
        break;
        
      case 2:
        ledState0 = HIGH;
        ledState1 = HIGH;
        break;

      case 3:
        ledState0 = LOW;
        ledState1 = LOW;
        break;
        
      case 4:
        if (sosv < 0) {
          sosv = sosa[sosp];
        }
        
        if (sosv > 0) {
          ledState0 = HIGH;
        } else {
          ledState0 = LOW;
          sosp += 1;
          if (sosp >= 12) {
            sosp = 0;
          }
        }
        sosv -= 1;
        ledState1 = ledState0;
        break;

    }
  }

  digitalWrite(ledPin0, ledState0);
  digitalWrite(ledPin1, ledState1);
}
