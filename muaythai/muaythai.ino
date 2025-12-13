// Buttons (6 buttons total)
const int b2 = 2;
const int b3 = 3;
const int b4 = 4;
const int b5 = 5;
const int b6 = 6;
const int b7 = 7;

// RGB LED pins
const int rPin = 10;
const int gPin = 11;
const int bPin = 12;

// Debounce tracking
bool lastBlue = false;
bool lastRed = false;
bool lastGreen = false;
bool lastYellow = false;

unsigned long lastDebounceBlue = 0;
unsigned long lastDebounceRed = 0;
unsigned long lastDebounceGreen = 0;
unsigned long lastDebounceYellow = 0;
const unsigned long debounceDelay = 50;

// Timer
unsigned long lastColorChangeTime = 0;
const unsigned long colorInterval = 5000;

// Current target color
String targetColor;

void setup() {
  Serial.begin(9600);

  pinMode(b2, INPUT_PULLUP);
  pinMode(b3, INPUT_PULLUP);
  pinMode(b4, INPUT_PULLUP);
  pinMode(b5, INPUT_PULLUP);
  pinMode(b6, INPUT_PULLUP);
  pinMode(b7, INPUT_PULLUP);

  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);

  randomSeed(analogRead(0));
  pickRandomColor();
  lastColorChangeTime = millis();
}

void loop() {
  unsigned long currentMillis = millis();

  // ⏱ Auto change every 5 seconds
  if (currentMillis - lastColorChangeTime >= colorInterval) {
    pickRandomColor();
    lastColorChangeTime = currentMillis;
  }

  // BLUE = (b2, b6)
  bool blueCombo = (!digitalRead(b2) && !digitalRead(b6));
  if (blueCombo && !lastBlue && currentMillis - lastDebounceBlue > debounceDelay) {
    checkColor("BLUE");
    lastDebounceBlue = currentMillis;
  }
  lastBlue = blueCombo;

  // RED = (b4, b6)
  bool redCombo = (!digitalRead(b4) && !digitalRead(b6));
  if (redCombo && !lastRed && currentMillis - lastDebounceRed > debounceDelay) {
    checkColor("RED");
    lastDebounceRed = currentMillis;
  }
  lastRed = redCombo;

  // GREEN = (b3, b7)
  bool greenCombo = (!digitalRead(b3) && !digitalRead(b7));
  if (greenCombo && !lastGreen && currentMillis - lastDebounceGreen > debounceDelay) {
    checkColor("GREEN");
    lastDebounceGreen = currentMillis;
  }
  lastGreen = greenCombo;

  // YELLOW = (b5, b7)
  bool yellowCombo = (!digitalRead(b5) && !digitalRead(b7));
  if (yellowCombo && !lastYellow && currentMillis - lastDebounceYellow > debounceDelay) {
    checkColor("YELLOW");
    lastDebounceYellow = currentMillis;
  }
  lastYellow = yellowCombo;
}

// Pick random color
void pickRandomColor() {
  int r = random(0, 4);
  switch (r) {
    case 0: targetColor = "RED"; break;
    case 1: targetColor = "GREEN"; break;
    case 2: targetColor = "BLUE"; break;
    case 3: targetColor = "YELLOW"; break;
  }

  Serial.print("Target color: ");
  Serial.println(targetColor);
  showColor(targetColor);
}

// Show RGB color
void showColor(String color) {
  digitalWrite(rPin, HIGH);
  digitalWrite(gPin, HIGH);
  digitalWrite(bPin, HIGH);

  if (color == "RED") {
    digitalWrite(rPin, LOW);
  } else if (color == "GREEN") {
    digitalWrite(gPin, LOW);
  } else if (color == "BLUE") {
    digitalWrite(bPin, LOW);
  } else if (color == "YELLOW") {
    digitalWrite(rPin, LOW);
    digitalWrite(gPin, LOW);
  }
}

// Check result
void checkColor(String pressedColor) {
  if (pressedColor == targetColor) {
    Serial.print("Correct: ");
    Serial.println(pressedColor);

    pickRandomColor();
    lastColorChangeTime = millis();
  } else {
    Serial.print("Wrong: ");
    Serial.println(pressedColor);
  }
}