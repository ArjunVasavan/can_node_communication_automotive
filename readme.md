# can_node_communication_automotive

CAN bus communication between three PIC18F4580 ECU nodes, simulating an automotive dashboard network.

## Nodes
| Node | Role |
|---|---|
| **ECU1** | Reads speed (ADC) and gear position (matrix keypad), transmits over CAN |
| **ECU2** | Reads RPM (ADC) and processes indicator status (digital keypad), displays on 7-segment |
| **ECU3** | Receives all CAN messages, displays data on LCD, controls indicator LEDs |

## Hardware
- MCU: PIC18F4580 | IDE: MPLAB X v6.25 | Compiler: XC8 v3.10
- 16x2 LCD, 7-segment display, Matrix/Digital Keypad, ADC

## CAN Message IDs
| ID | Parameter |
|---|---|
| `0x10` | Speed |
| `0x20` | Gear |
| `0x30` | RPM |
| `0x40` | Engine Temp |
| `0x50` | Indicator |

## Build
Open each `.X` folder in MPLAB X and build separately. Flash to individual boards.

```
ECU1.X  →  Sensor node (speed + gear)
ECU2.X  →  Sensor node (RPM + indicators)
ECU3.X  →  Dashboard display node
```
