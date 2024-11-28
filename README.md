# BlastgateBuddy

Dieses Projekt steuert ein Relais basierend auf den Strommessungen eines ACS712-Sensormoduls. Das System liest den Strom, berechnet einen gleitenden Mittelwert und schaltet ein Relais und eine LED ein oder aus, abhängig davon, ob der Strom einen einstellbaren Schwellwert überschreitet. Zusätzlich verfügt es über eine anpassbare Verzögerung, bevor das Relais ausgeschaltet wird, wenn der Strom unter den Schwellwert fällt.

## Features

- **Strommessung**: Verwendet das ACS712-Stromsensormodul zur Messung des Stroms.
- **Relaissteuerung**: Schaltet ein Relais basierend auf den Strommesswerten.
- **Einstellbarer Schwellwert**: Benutzer können einen Schwellwert einstellen, ab dem das Relais aktiviert wird.
- **Gleitender Mittelwert**: Reduziert Rauschen durch Berechnung eines gleitenden Mittelwerts der Strommessungen.
- **Ausschaltverzögerung**: Implementiert eine konfigurierbare Verzögerung, bevor das Relais ausgeschaltet wird, nachdem der Strom unter den Schwellwert gefallen ist.
- **Eingebaute LED-Steuerung**: Bietet visuelles Feedback mit der LED auf dem Arduino Nano.
- **Kalibrierung**: Kalibriert den ACS712 automatisch, um einen Nullpunkt festzulegen.

## Komponenten

- **Arduino Nano**
- **ACS712 Stromsensormodul**
- **Relaismodul**
- **LED (auf dem Arduino Nano integriert)**

## Pinbelegung

| Komponente    | Arduino-Pin |
|---------------|-------------|
| ACS712        | A0          |
| Relais        | 8           |
| Eingebaute LED| 13          |

## Einstellbare Parameter

- **`threshold`**: Legt den Stromschwellwert fest, ab dem das Relais eingeschaltet wird (Standard: `30`).
- **`offDelay`**: Legt die Verzögerung (in Millisekunden) fest, bevor das Relais ausgeschaltet wird, nachdem der Strom unter den Schwellwert gefallen ist (Standard: `10000` Millisekunden).

## Code-Erklärung

Das Projekt basiert auf dem Auslesen des ACS712-Stromsensors, der Berechnung der Abweichung von einem kalibrierten Nullpunkt und der Verwendung dieser Daten zur Steuerung eines Relais und einer LED. Die zentralen Elemente sind:

1. **Gleitender Mittelwert**: Glättet die Messungen, indem die letzten 10 Messungen gespeichert und gemittelt werden.
2. **Schwellwertlogik**: Das Relais und die LED schalten sich sofort ein, wenn der Strom den Schwellwert überschreitet, und schalten sich mit einer Verzögerung aus, nachdem der Strom unter den Schwellwert fällt.
3. **Kalibrierung**: Beim Start kalibriert sich der Sensor, um den Nullpunkt zu bestimmen, der zur Berechnung der Stromabweichung verwendet wird.

## Aufbau

1. Verbinde die Komponenten gemäß der Pinbelegung.
2. Lade den Code auf deinen Arduino Nano hoch.
3. Passe die Werte für `threshold` und `offDelay` im Code nach Bedarf an.
4. Beobachte die Roh- und Durchschnittswerte des Sensors im seriellen Monitor.

## Verwendung

Nach dem Einschalten:

1. Kalibriert sich der ACS712-Sensor automatisch.
2. Überwacht das System kontinuierlich den Strom und aktualisiert den gleitenden Mittelwert.
3. Schaltet das Relais und die LED ein, wenn der Strom den festgelegten Schwellwert überschreitet.
4. Lässt das Relais eingeschaltet, solange der Strom über dem Schwellwert bleibt, und schaltet es nach Ablauf der Verzögerung aus, sobald der Strom unter den Schwellwert fällt.

## Lizenz

Dieses Projekt steht unter der [GNU General Public License v3.0](LICENSE).

> **Hinweis**: Eine Kopie der Lizenz ist im Projekt enthalten. Für weitere Informationen zur Lizenz besuchen Sie die [GNU GPLv3 Webseite](https://www.gnu.org/licenses/gpl-3.0.html).
