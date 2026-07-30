# STM32 Pulse-Width Distance Sensor Driver
(insert gif here)

A bare-metal STM32G070 driver for measuring distance from a pulse-width encoded sensor using timer input capture.

The project measures the duration of each sensor output pulse, converts the pulse width into a distance in millimeters, and reports valid measurements or no-detection conditions over UART.

No STM32 HAL functions are used. Peripheral configuration is implemented directly with CMSIS register access.

## Hardware

- STM32 Nucleo-G070RB
- Pololu pulse-width distance sensor
- USB-to-UART connection through the Nucleo virtual COM port
- Onboard LED used as a non-blocking heartbeat indicator

## Features

- Bare-metal GPIO and timer configuration
- Timer input capture with 1 microsecond resolution
- Rising- and falling-edge pulse measurement
- Runtime input-capture polarity switching
- Timer-overflow-safe pulse-width calculation
- Pulse-width-to-distance conversion
- No-target detection
- Status-based error handling
- Rate-limited UART logging
- Non-blocking heartbeat LED

## Driver Architecture

```text
Application
    |
Initialization
    |
Device Driver
    |
Peripheral Drivers
    |
STM32 Registers
```
The pulse-width sensor device driver depends on the reusable timer input-capture driver.

## Pulse Measurement

The timer is configured with a 1 MHz counter frequency:
```
1 timer tick = 1 microsecond
```

The driver initially waits for a rising edge. After capturing the rising-edge timestamp, it switches the channel polarity and waits for a falling edge.

```
WAITING_FOR_RISING
        |
        | Rising edge
        v
WAITING_FOR_FALLING
        |
        | Falling edge
        v
Measurement ready
```

The pulse duration is calculated as:
```
high_ticks = falling_timestamp - rising_timestamp;
```

Timer overflow is handled when the falling timestamp is numerically smaller than the rising timestamp.

## Distance Conversion

The sensor encodes distance using:
```
distance_mm = ((pulse_width_us - 1000U) * 3U) / 4U;
```

A pulse near 2000 microseconds represents no detected target. Since the measured pulse may differ slightly from the nominal value, the driver uses a no-detection threshold rather than requiring exactly 2000 microseconds.

## Example Output
```
[PULSE_WIDTH_SENSOR] Distance (mm): 90
[PULSE_WIDTH_SENSOR] Distance (mm): 72
[PULSE_WIDTH_SENSOR] Distance (mm): 45
[PULSE_WIDTH_SENSOR] Distance (mm): 21
[PULSE_WIDTH_SENSOR] Nothing detected
```

## Project Structure
```
Drivers/
├── gpio/
├── systick/
├── timer/
│   └── timer_input_capture/
└── uart/

Devices/
└── pulse_width_sensor/

device_instances/
init/
Src/
└── main.c
```

## Current Implementation
The application continuously polls the input-capture status. UART output is rate-limited so the main loop remains responsive, while the heartbeat LED demonstrates that the application is not blocked by sensor processing or logging.

## Future Improvements
- Add stricter pointer and configuration validation
- Improve initialization error propagation
- Add optional interrupt-driven capture
- Add distance filtering
- Add automated host-side unit tests for conversion and overflow calculations
