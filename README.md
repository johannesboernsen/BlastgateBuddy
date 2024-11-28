# BlastgateBuddy

This project controls a relay based on current measurements from an ACS712 sensor module. The system reads the current, calculates a moving average, and toggles a relay and an LED on or off depending on whether the current exceeds a user-defined threshold. Additionally, it features a customizable delay before the relay is switched off when the current drops below the threshold.

## Features

- **Current Measurement**: Uses the ACS712 current sensor module to measure current.
- **Relay Control**: Toggles a relay based on the current readings.
- **Adjustable Threshold**: Users can set a threshold to activate the relay.
- **Moving Average**: Reduces noise by calculating a moving average of the current readings.
- **Off Delay**: Implements a configurable delay before switching off the relay after the current drops below the threshold.
- **Built-in LED Control**: Provides visual feedback using the LED on the Arduino Nano.
- **Calibration**: Automatically calibrates the ACS712 to establish a zero point.

## Components

- **Arduino Nano**
- **ACS712 Current Sensor Module**
- **Relay Module**
- **LED (integrated on the Arduino Nano)**

## Pinout

| Component      | Arduino Pin |
|----------------|-------------|
| ACS712         | A0          |
| Relay          | 8           |
| Built-in LED   | 13          |

## Adjustable Parameters

- **`threshold`**: Sets the current threshold for switching on the relay (default: `30`).
- **`offDelay`**: Sets the delay (in milliseconds) before switching off the relay after the current drops below the threshold (default: `10000` milliseconds).

## Code Explanation

The project revolves around reading the ACS712 current sensor, calculating the deviation from a calibrated zero point, and using this data to control a relay and an LED. Key elements include:

1. **Moving Average**: Smooths out readings by storing the last 10 measurements and averaging them.
2. **Threshold Logic**: The relay and LED switch on immediately when the current exceeds the threshold and switch off with a delay once the current drops below the threshold.
3. **Calibration**: At startup, the sensor calibrates itself to determine the zero point used for current deviation calculations.

## Setup

1. Connect the components according to the pinout.
2. Upload the code to your Arduino Nano.
3. Adjust the `threshold` and `offDelay` values in the code as needed.
4. Use the serial monitor to observe the raw and averaged sensor readings.

## Usage

Once powered on:

1. The ACS712 sensor automatically calibrates itself.
2. The system continuously monitors the current and updates the moving average.
3. The relay and LED turn on when the current exceeds the set threshold.
4. The relay remains on as long as the current stays above the threshold and switches off after the delay once the current drops below the threshold.

## License

This project is licensed under the [GNU General Public License v3.0](LICENSE).

> **Note**: A copy of the license is included in the project. For more information about the license, visit the [GNU GPLv3 website](https://www.gnu.org/licenses/gpl-3.0.html).
