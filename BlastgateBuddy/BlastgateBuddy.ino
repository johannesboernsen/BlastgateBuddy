/*
 * Projektname: BlastgateBuddy
 * Version: 1.0
 * Ersteller: Johannes Boernsen
 * Datum: 28. November 2024
 * Beschreibung:
 * Dieser Sketch erkennt mittels eine ACS712-Sensors den Betriebszustand von Holzbearbeitungsmaschinen. 
 * Bei eingeschalteter Maschine wird ein Relais eingeschaltet, über das eine Steuerspannung für einen Pneumatik-Absperrschieber gesteuert werden kann.
 *
 * Lizenz: GNU GPLv3
 * Repository: https://github.com/johannesboernsen/BlastgateBuddy
 */

// Pinbelegung
const int sensorPin = A0;       // Analoger Pin, an den der ACS712 angeschlossen ist
const int ledPin = 13;          // Eingebaute LED auf dem Arduino Nano
const int relayPin = 8;         // Digitaler Pin zum Steuern des Relais

// Einstellbarer Schwellwert
int threshold = 30;             // Anpassen basierend auf Ihren Messungen

// Nullpunktwert für den ACS712
int zeroPoint = 0;

// Variablen für den gleitenden Mittelwert
const int numSamples = 10;      // Anzahl der Messungen für den gleitenden Mittelwert
int sensorValues[numSamples];   // Array zur Speicherung der letzten Messungen
int currentIndex = 0;           // Aktueller Index für die Speicherung der Messungen

// Ausschaltverzögerung in Millisekunden (einstellbar)
unsigned long offDelay = 15000; // 10 Sekunden Ausschaltverzögerung

// Variablen für die Verzögerungslogik
unsigned long lastBelowThresholdTime = 0;
bool isBelowThreshold = false;
bool ledState = false;          // Aktueller Zustand der LED und des Relais (true = ein, false = aus)

void setup() {
  pinMode(ledPin, OUTPUT);      // Setzt den LED-Pin als Ausgang
  pinMode(relayPin, OUTPUT);    // Setzt den Relais-Pin als Ausgang
  Serial.begin(9600);           // Initialisiert die serielle Kommunikation

  // Nullpunkt-Kalibrierung durchführen
  zeroPoint = calibrateSensor();
  Serial.print("Kalibrierter Nullpunkt: ");
  Serial.println(zeroPoint);

  // Initialisiert das Array mit dem Nullpunktwert
  for (int i = 0; i < numSamples; i++) {
    sensorValues[i] = zeroPoint;
  }

  // LED und Relais initial ausschalten
  digitalWrite(ledPin, LOW);
  digitalWrite(relayPin, LOW);
}

void loop() {
  int sensorValue = analogRead(sensorPin);  // Liest den analogen Wert des Sensors

  // Berechnet den aktuellen Stromwert (Abweichung vom Nullpunkt)
  int currentValue = abs(sensorValue - zeroPoint);

  // Aktualisiert den Array mit der neuesten Messung (für den gleitenden Mittelwert)
  sensorValues[currentIndex] = currentValue;
  currentIndex = (currentIndex + 1) % numSamples;

  // Berechnet den gleitenden Mittelwert
  long sum = 0;
  for (int i = 0; i < numSamples; i++) {
    sum += sensorValues[i];
  }
  int averageValue = sum / numSamples;

  // Gibt den aktuellen Sensorwert und den Durchschnittswert auf dem seriellen Monitor aus
  Serial.print("Aktueller Wert: ");
  Serial.print(currentValue);
  Serial.print(" | Durchschnittswert: ");
  Serial.println(averageValue);

  unsigned long currentTime = millis();

  // **LED und Relais sofort einschalten, wenn der aktuelle Wert über dem Schwellwert liegt**
  if (currentValue > threshold) {
    if (!ledState) {
      ledState = true;
      digitalWrite(ledPin, HIGH);
      digitalWrite(relayPin, HIGH);  // Relais einschalten
    }
    // Ausschaltverzögerung abbrechen, falls sie läuft
    isBelowThreshold = false;
    lastBelowThresholdTime = 0;
  } else {
    // **Überprüfen, ob die Ausschaltverzögerung gestartet werden muss**
    if (!isBelowThreshold) {
      // Gerade unter den Schwellwert gefallen, Verzögerung starten
      isBelowThreshold = true;
      lastBelowThresholdTime = currentTime;
    } else {
      // **Überprüfen, ob die Verzögerungszeit abgelaufen ist**
      if (currentTime - lastBelowThresholdTime >= offDelay) {
        if (ledState) {
          ledState = false;
          digitalWrite(ledPin, LOW);
          digitalWrite(relayPin, LOW);  // Relais ausschalten
        }
        // Verzögerungsvariablen zurücksetzen
        isBelowThreshold = false;
        lastBelowThresholdTime = 0;
      }
    }
  }

  delay(100); // Wartezeit von 100 ms für eine schnellere Reaktionszeit
}

int calibrateSensor() {
  long sum = 0;
  int samples = 100;

  // Mehrere Messungen durchführen, um den Mittelwert (Nullpunkt) zu berechnen
  for (int i = 0; i < samples; i++) {
    sum += analogRead(sensorPin);
    delay(10);  // Kleine Wartezeit zwischen den Messungen
  }

  // Gibt den Durchschnittswert zurück
  return sum / samples;
}
