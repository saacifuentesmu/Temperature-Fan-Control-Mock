# Temperature & Air-Quality Fan Controller (STM32F401RE)

A compact, modular STM32 firmware sample: a closed-loop fan controller that reacts
to temperature and air quality with explicit failsafe behaviour and a testable
architecture. Sensors are **mocked with a deterministic profile**, so the whole
system runs on a bare NUCLEO-F401RE with no external hardware — handy for demos and CI.

## Behaviour

- **Auto mode** — a P controller drives fan duty from the temperature error
  (`Kp·(T − setpoint)`, setpoint 28 °C), clamped to 0–100 %.
- **Air-quality override** — forces a minimum duty regardless of temperature:
  ≥ 60 % when AQI > 150, 100 % when AQI > 220.
- **Failsafe** — on an invalid sensor reading the fan holds 35 % and the status
  LED fast-blinks.
- **Manual mode** — one button toggles AUTO/MANUAL; a second steps the manual duty.
- **Status LED** — solid = auto, slow blink = manual, fast blink = sensor fault.
- **UART telemetry** — a 1 Hz status line (mode, temperature, AQI, duty, validity)
  over USART2 at 115200 8N1.

## Architecture

Built so the decision logic is isolated and unit-testable:

- **`control.*`** — the pure function `Control_ComputeAutoDuty()`: no hardware, no
  state, so it runs and can be tested directly on a host.
- **`mock_sensors.*`** — a deterministic 10 s sensor profile (ramps + fault windows)
  behind a sensor interface; swap it for a real driver without touching control or
  app code.
- **`fan.*`, `led_status.*`, `uart_log.*`, `buttons.*`** — thin drivers that wrap
  the HAL; hardware access is confined to these.
- **`app.c`** — a non-blocking cooperative scheduler on `HAL_GetTick()`: 500 ms
  sensor/control tick, 1 Hz UART report.

The separation is the point — the control policy can be exercised and changed
without a board, and the sensor source is mockable.

## Hardware

| Function | Pin |
|----------|-----|
| Fan PWM | TIM3 CH1 |
| Status LED (LD2) | PA5 |
| Mode button (B1) | PC13 (EXTI) |
| Duty button | PB0 (EXTI) |
| UART log | USART2 → ST-Link VCP |

Target **STM32F401RE** (NUCLEO-F401RE). No external sensor required — readings are simulated.

## Build

STM32CubeIDE project: *File → Open Projects from File System…*, select this folder,
build, and flash to a NUCLEO-F401RE. Open a serial terminal at **115200 8N1** on the
ST-Link virtual COM port to watch the 1 Hz status output.
