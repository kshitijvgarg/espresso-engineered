# Espresso, Engineered: High-End Brewing at a Low Cost ☕🔧

## Overview

This project is an attempt to bridge the gap between high-end espresso machines and affordability. Inspired by professional automatic espresso machines, our goal was to achieve similar functionality at a fraction of the cost by leveraging custom hardware and efficient programming.

## Features

- **Precision Brewing**: Custom brewing time for single and double shots.
- **Cost-Effective Design**: Achieves professional-level brewing without expensive components.
- **Automation**: Relay-controlled brewing and purging process.
- **Minimalist Control**: Button-based operation for ease of use.

## Hardware Used

- **Microcontroller**: Arduino (compatible board)
- **Pump & Relay Module**: Controls water flow for espresso extraction
- **Push Buttons**: Single shot, double shot, purge, and stop functions
- **Power Supply**: 12V (or as per pump requirements)

## Software & Logic

- Programmed in **C++** using the Arduino framework.
- Implements brewing and purging functions in an efficient loop.
- Designed for minimal latency and optimal performance.

## Installation & Usage

1. **Upload the Arduino Sketch** from the `src/` folder to your board.
2. **Connect the relay module** to control the espresso pump.
3. **Press the buttons** to initiate the desired operation.
4. **Enjoy your espresso! ☕**

## Future Improvements

- PID temperature control for precision heating.
- Pressure profiling for enhanced extraction.
- Integration with an LCD screen for status updates.

## Contributing

Feel free to fork this repository and contribute! Any improvements to efficiency, hardware integration, or automation are welcome.

## License

This project is licensed under the MIT License.

---
