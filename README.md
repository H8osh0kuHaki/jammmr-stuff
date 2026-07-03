# ESP32 Wi-Fi Jamming Tool - Drone Disruption
NASA CYBER HACKES 
## Overview

This tool floods the 2.4 GHz spectrum with raw 802.11 frames to disrupt drone control and video links. It uses the ESP32's `esp_wifi_80211_tx()` function to transmit directly at the hardware level, bypassing normal protocol handling.

## Hardware Requirements

- ESP32 development board (any variant with 2.4 GHz radio)
- Micro-USB cable for power and programming
- Optional: External 2.4 GHz antenna with higher gain (5-8 dBi) for extended range

## Software Requirements

- Arduino IDE or PlatformIO
- ESP32 board package (Espressif Systems official package)
- `esp_wifi.h` library (included in board package)

## Flashing Instructions

1. Open the `.ino` file in Arduino IDE
2. Select your ESP32 board under Tools > Board
3. Set Upload Speed to 921600 for faster flashing
4. Connect the ESP32 via USB and select the correct port
5. Click Upload

## Configuration

| Parameter | Description | Default |
|-----------|-------------|---------|
| `channel` | Wi-Fi channel 1-13 (2.4 GHz) | 1 |
| `delay(ms)` | Delay between transmissions in milliseconds | 10 |
| Frame type | 0x80 = Beacon, 0x48 = Null Data, 0xD0 = Probe Response | Beacon |
| Payload size | Random noise bytes per frame | 32 |

## Tuning for Maximum Disruption

- **Remove the delay** in `loop()` for back-to-back transmission
- **Set channel to 6 or 11** (most drones operate in mid-band)
- **Increase payload size** to 128-256 bytes for longer airtime per frame
- **Use Null Data frames** (0x48 header) which consume less CPU but occupy airtime
- **Deploy multiple ESP32s** on channels 1, 6, and 11 simultaneously

## Range Estimates

| Condition | Effective Range |
|-----------|----------------|
| Internal antenna, no obstructions | 30-50 meters |
| External 5 dBi antenna, line of sight | 80-120 meters |
| Multiple units synchronized | 100-150 meters |

## Troubleshooting

- **No transmission** - Verify ESP32 board package is version 2.0.0 or newer
- **Compiler error on `esp_wifi_80211_tx`** - Wrap the include in `extern "C" {}`
- **Weak effect on drone** - Move closer, remove delay, or add more units on different channels
- **Board crashes** - Reduce packet rate by adding a small delay (1-2 ms)

## Limitations

- Operates only on 2.4 GHz band. For 5.8 GHz drones, use an ESP32-S2, HackRF, or Raspberry Pi with nexmon
- Single ESP32 on one channel may not disrupt channel-hopping drones reliably
- Range is limited by ESP32 transmit power (~20 dBm / 100 mW)
- Drones with strong spread-spectrum filtering (military-grade or high-end commercial) are significantly more resistant
