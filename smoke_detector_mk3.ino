/*
  SMOKE / FIRE DETECTOR 
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Pins 
#define MQ2_AOUT   A0   // MQ-2 analog output                           A0=A0
#define FLAME_PIN  3    // Flame sensor digital output                  D0=D3 
#define DHT_PIN    4    // DHT11 data pin                               DATA=D4
#define BUZZER_PIN 5    // Active buzzer                                +ive=D5
#define RELAY_PIN  6    // Relay module IN pin                          IN=D6

#define DHT_TYPE   DHT11

// Thresholds 
const int SMOKE_THRESHOLD = 300;  
const bool FLAME_ACTIVE_LOW = false; 

// Objects 
LiquidCrystal_I2C lcd(0x27, 16, 2); 
DHT dht(DHT_PIN, DHT_TYPE);

//  State 
unsigned long lastReadTime = 0;
const unsigned long READ_INTERVAL = 2000; 
float temperature = 0;
float humidity = 0;

void setup() {
  Serial.begin(9600);

  pinMode(FLAME_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(RELAY_PIN, LOW);   

  dht.begin();

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Smoke Detector");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
  delay(10500);
  lcd.clear();
}

void loop() {
  int smokeValue   = analogRead(MQ2_AOUT);
  bool flameRaw    = digitalRead(FLAME_PIN);
  bool flameDetected = FLAME_ACTIVE_LOW ? (flameRaw == LOW) : (flameRaw == HIGH);
  bool smokeDetected = (smokeValue > SMOKE_THRESHOLD);

  
  if (millis() - lastReadTime > READ_INTERVAL) {
    lastReadTime = millis();
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (!isnan(h) && !isnan(t)) {
      humidity = h;
      temperature = t;
    }
  }

  bool alarm = smokeDetected || flameDetected;

  // Buzzer + Relay
  digitalWrite(BUZZER_PIN, alarm ? HIGH : LOW);
  digitalWrite(RELAY_PIN, alarm ? HIGH : LOW); 

  // LCD
  lcd.setCursor(0, 0);
  if (alarm) {
    lcd.print("!! DANGER !!     ");
  } else {
    lcd.print("------SAFE------");
  }

  lcd.setCursor(0, 1);
  lcd.print((int)temperature);
  lcd.write(223);
  lcd.print("C H:");
  lcd.print((int)humidity);
  lcd.print("% S:");
  lcd.print(smokeValue);
  lcd.print("   "); 

  //Serial Monitor
  Serial.print("Smoke: "); Serial.print(smokeValue);
  Serial.print(" | Flame: "); Serial.print(flameDetected ? "YES" : "no");
  Serial.print(" | Temp: "); Serial.print(temperature);
  Serial.print(" C | Hum: "); Serial.print(humidity);
  Serial.print(" % | ALARM: "); Serial.println(alarm ? "ON" : "off");

  delay(300);
}
