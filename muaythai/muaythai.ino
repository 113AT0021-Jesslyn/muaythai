const int button1Pin = 2;
const int button2Pin = 3;
const int button3Pin = 4;

const int redLedPin  = 9;
const int blueLedPin = 10;

void setup() {
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);

  pinMode(redLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);

  digitalWrite(redLedPin, LOW);
  digitalWrite(blueLedPin, LOW);
}

void loop() {
  bool b1 = (digitalRead(button1Pin) == LOW);  // pressed = LOW
  bool b2 = (digitalRead(button2Pin) == LOW);
  bool b3 = (digitalRead(button3Pin) == LOW);

  // --- EXACT CONDITIONS ---

  // Only Button1 + Button2
  if (b1 && b2 && !b3) {
    digitalWrite(redLedPin, HIGH);
    digitalWrite(blueLedPin, LOW);
  }
  // Only Button1 + Button3
  else if (b1 && b3 && !b2) {
    digitalWrite(redLedPin, LOW);
    digitalWrite(blueLedPin, HIGH);
  }
  // Anything else → all off
  else {
    digitalWrite(redLedPin, HIGH);
    digitalWrite(blueLedPin, HIGH);
  }
}
