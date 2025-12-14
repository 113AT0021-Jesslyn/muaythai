// Button pairs
const int b2 = 2, b3 = 3;   // BLUE
const int b4 = 4, b5 = 5;   // RED
const int b6 = 6, b7 = 7;   // GREEN

// RGB LED pins
const int rPin = 10;
const int gPin = 11;
const int bPin = 12;

// Debounce tracking
bool lastBlue = false;
bool lastRed = false;
bool lastGreen = false;
bool lastAnj = false;

unsigned long lastDebounceBlue = 0;
unsigned long lastDebounceRed = 0;
unsigned long lastDebounceGreen = 0;
unsigned long lastDebounceAnj = 0;
const unsigned long debounceDelay = 50;

// Current target color
String targetColor;

void setup() {
  Serial.begin(9600);

  pinMode(b7, INPUT_PULLUP);
  pinMode(b3, INPUT_PULLUP);
  pinMode(b4, INPUT_PULLUP);
  pinMode(b5, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  pinMode(b6, INPUT_PULLUP);

  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);

  randomSeed(analogRead(0));
  pickRandomColor(); // Pick first color
}

void loop() {
  unsigned long currentMillis = millis();

  // BLUE combo
  bool blueCombo = (!digitalRead(b2) && !digitalRead(b6));
  if(blueCombo && !lastBlue && (currentMillis - lastDebounceBlue > debounceDelay)) {
    checkColor("BLUE");
    lastDebounceBlue = currentMillis;
  }
  lastBlue = blueCombo;

  // RED combo
  bool redCombo = (!digitalRead(b3) && !digitalRead(b7));
  if(redCombo && !lastRed && (currentMillis - lastDebounceRed > debounceDelay)) {
    checkColor("RED");
    lastDebounceRed = currentMillis;
  }
  lastRed = redCombo;

  // GREEN combo
  bool greenCombo = (!digitalRead(b4) && !digitalRead(b6));
  if(greenCombo && !lastGreen && (currentMillis - lastDebounceGreen > debounceDelay)) {
    checkColor("GREEN");
    lastDebounceGreen = currentMillis;
  }
  lastGreen = greenCombo;

  // ANJ combo (YELLOW)
  bool anjCombo = (!digitalRead(b5) && !digitalRead(b7));
  if(anjCombo && !lastAnj && (currentMillis - lastDebounceAnj > debounceDelay)) {
    checkColor("YELLOW");
    lastDebounceAnj = currentMillis;
  }
  lastAnj = anjCombo;
}

// Pick a random color from RED, GREEN, BLUE, YELLOW
void pickRandomColor() {
  int r = random(0, 4);
  switch(r) {
    case 0: targetColor = "RED"; break;
    case 1: targetColor = "GREEN"; break;
    case 2: targetColor = "BLUE"; break;
    case 3: targetColor = "YELLOW"; break;
  }
  Serial.print("Target color: ");
  Serial.println(targetColor);
  showColor(targetColor);
}

// Turn on/off RGB LED using digital pins
void showColor(String color) {
  // Turn all off first
  digitalWrite(rPin, LOW);
  digitalWrite(gPin, LOW);
  digitalWrite(bPin, LOW);

  if (color == "RED") {
    digitalWrite(rPin, LOW);
    digitalWrite(gPin, HIGH);
    digitalWrite(bPin, HIGH);
  } 
  else if (color == "GREEN") {
    digitalWrite(rPin, HIGH);
    digitalWrite(gPin, LOW);
    digitalWrite(bPin, HIGH);
  } 
  else if (color == "BLUE") {
    digitalWrite(rPin, HIGH);
    digitalWrite(gPin, HIGH);
    digitalWrite(bPin, LOW);
  } 
  else if (color == "YELLOW") { // RED + GREEN
    digitalWrite(rPin, LOW);
    digitalWrite(gPin, LOW);
    digitalWrite(bPin, HIGH);
  }
}

// Check if pressed combo matches the target color
void checkColor(String pressedColor) {
  if(pressedColor == targetColor) {
    Serial.print("Correct! You pressed: ");
    Serial.println(pressedColor);
    pickRandomColor(); // Next round
  } else {
    Serial.print("Wrong! You pressed: ");
    Serial.println(pressedColor);
  }
}
