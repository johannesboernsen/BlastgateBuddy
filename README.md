# BlastgateBuddy

This project controls a relay based on current measurements from an ACS712 sensor module. The system reads the current, calculates a moving average, and toggles a relay and an LED on or off depending on whether the current exceeds a user-defined threshold. Additionally, it features a customizable delay before the relay is switched off when the current drops below the threshold.

## Integration in a Woodworking Shop

This system is designed for integration into a woodworking shop to automate the operation of blast gates for dust collection. Each Arduino is dedicated to monitoring a single machine. When the machine is powered on, the system activates the relay, supplying power to a pneumatic valve. The valve then controls a pneumatic cylinder, which opens the corresponding blast gate.

The system does **not** include a centralized control for the dust collection unit itself. This must be managed separately, for example:
- Using a power outlet that is build into a shop vacuum
- Implementing an automatic start system for larger dust collection units

## Machine-Specific Setup

Each Arduino is limited to monitoring a single machine. As a result:
- The described setup must be replicated for each machine in the workshop.
- This ensures independent control of blast gates for every machine without complex wiring or interference.

## Electrical Considerations

The power supply of the machine is connected to the ACS712 current sensor. The machine's load passes through the sensor, so it is essential to select the appropriate sensor version based on the machine's power requirements. The provided code uses the 20A version of the ACS712 sensor. Alternative versions with 5A and 30A capacity are also available. 

If a different version is used, the code may need to be adjusted to account for the sensor's output characteristics. Carefully verify the current rating of your machines and ensure the selected sensor version can handle the expected load safely.

## Safety and Legal Notice

When working with electrical systems, it is essential to comply with the legal regulations and safety standards of your country. The creator of this project does not provide any warranty or assume responsibility for the correct or safe use of this code or hardware. In many countries, electrical work must be carried out or inspected by a qualified professional. Failure to adhere to these regulations can result in serious injury or death due to electrical hazards. Always ensure that the system is installed and operated safely and that appropriate precautions are taken to protect both people and equipment.

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
