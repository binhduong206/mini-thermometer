# STM32 Mini Thermometer

A mini thermometer project using the STM32F103C8T6 microcontroller, DHT11 temperature and humidity sensor, and LCD display.

## Features

- Read temperature and humidity from the DHT11 sensor.
- Display temperature and humidity on an LCD.
- Use STM32 HAL for GPIO and peripheral control.
- Implement a custom LCD driver and DHT11 driver.

## Hardware Requirements

- STM32F103C8T6 (Blue Pill)
- DHT11 temperature and humidity sensor
- LCD 1602
- Jumper wires
- Breadboard
- USB-to-UART adapter or ST-Link for programming, depending on your setup

## Software Requirements

- Visual Studio Code
- PlatformIO IDE
- STM32Cube framework
- C programming language

## Project Structure

```text
mini_thermometer/
├── include/
├── src/
├── lib/
├── test/
├── platformio.ini
└── README.md
```

*Note: Update the project structure above to match the actual files and folders in your repository.*

## How It Works

1. The STM32 sends a start signal to the DHT11 sensor.
2. The sensor responds with temperature and humidity data.
3. The STM32 reads the data and checks the checksum.
4. The LCD displays the measured values.

## Future Improvements

- Improve communication error handling.
- Optimize microsecond timing.
- Add support for additional sensors.
