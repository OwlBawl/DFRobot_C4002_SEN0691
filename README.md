# DFRobot C4002 / SEN0691 for ESPHome

ESPHome external component for the DFRobot C4002 (SEN0691) 24 GHz mmWave presence sensor. It exposes motion, presence, target metrics, per-gate thresholds, environmental calibration, and C4002 configuration directly in Home Assistant.

The repository includes a complete reusable package configuration in [`.base_c4002.yaml`](.base_c4002.yaml) and an ESP32-S2 example in [`DFRobot-c4002-test.yaml`](DFRobot-c4002-test.yaml).

## Features

- Native event-driven `Motion` and `Presence` binary sensors.
- Motion/presence distance, motion speed and direction, energy, illuminance, and presence countdown.
- C4002 OUT mode, LEDs, detection range, target delay, lock time, light threshold, and report period.
- `Low`, `Medium`, `High`, and `Custom` threshold groups for Move and Still detection.
- Individual Move and Still threshold sliders for all 25 possible gates.
- Dynamic gate availability: 15 gates at 80 cm resolution, 25 at 20 cm resolution. Unsupported gate entities are reported unavailable.
- Active Gates Track text sensor, disabled by default and automatically disabled after five minutes.
- Read-only `Refresh Parameters` action that reloads the sensor configuration into Home Assistant.
- Guarded UART transactions: command replies are matched by frame type and command; live sensor notifications are preserved.

## Hardware

Use a 5 V supply for the SEN0691 and connect the UART lines crossed:

| C4002 / SEN0691 | ESP32 |
| --- | --- |
| `VIN` | 5 V |
| `GND` | GND |
| `TX` | UART RX |
| `RX` | UART TX |
| `OUT` | Optional GPIO input |

The included ESP32-S2 example uses GPIO16 for TX, GPIO18 for RX, and GPIO33 for the optional OUT pin. UART speed is 115200 baud, 8-N-1.

## Installation

1. Copy [`DFRobot-c4002-test.yaml`](DFRobot-c4002-test.yaml) into your ESPHome configuration directory.
2. Change the `substitutions` at the top: device name, friendly name, C4002 ID, and board/pins as needed.
3. Ensure the secrets referenced by [`.base_c4002.yaml`](.base_c4002.yaml) exist: `wifi_ssid`, `wifi_password`, `ap_wifi_pass`, and `api_key`.
4. Compile and flash from ESPHome.

The example loads this repository as an external component:

```yaml
external_components:
  - source:
      type: git
      url: https://github.com/OwlBawl/DFRobot_C4002_SEN0691.git
      ref: test
      path: .
    components: [dfrobot_c4002]
    refresh: 0s
```

For local development, replace the Git source with a local `external_components` source.

## Home Assistant entities

| Group | Entities |
| --- | --- |
| Binary sensors | Motion, Presence, optional OUT Pin Presence |
| Measurements | Motion Distance, Presence Distance, Motion Speed, Motion/Presence Energy, Illuminance, Presence Countdown |
| Text | Movement Direction, Active Gates Track |
| Selects | OUT Mode, Motion Sensitivity, Presence Sensitivity, Resolution Mode |
| Controls | Detection distance, light threshold, lock time, report period, target disappear delay, exclusion ranges |
| Gate controls | Gate 0–24 Move and Still thresholds |
| Actions | Refresh Parameters, Factory Reset, Sensor Calibration |

## Gates and resolution

| Resolution | Available gates | Gate centres | Maximum gate centre |
| --- | ---: | --- | ---: |
| 80 cm | 0–14 | 0.2 m + 0.8 m per gate | 11.4 m |
| 20 cm | 0–24 | 0.1 m + 0.2 m per gate | 4.9 m |

Home Assistant discovers entities at boot, so all 25 gate pairs are declared in YAML. At 80 cm resolution, gates 15–24 are marked unavailable. Changing resolution refreshes the gate values and availability.

`Active Gates Track` displays active gate numbers separated by spaces and inactive gates as `-`; it also includes the current gate-distance range. Enable it only while tuning because it adds text-state updates. It turns off automatically after five minutes.

## Calibration and thresholds

`Sensor Calibration` starts the sensor's automatic environmental calibration (3 s delay, 15 s collection). Leave the monitored area empty while it runs. Once the C4002 reports completion, the component reads the sensor configuration and all current Move/Still threshold values again.

Changing a sensitivity select uses the C4002's threshold group for that detector and then performs a complete read-back. A manual gate-slider edit writes the full current threshold table to the sensor's `Custom` group, while changing just one value in Home Assistant.

The C4002 firmware may retain environmental-calibration-derived values in its threshold tables after Factory Reset. Factory Reset follows DFRobot's official sequence (`user settings reset`, `factory reset`, restart) and refreshes Home Assistant afterwards; it cannot clear sensor data for which DFRobot exposes no separate public command.

## Troubleshooting

- Set `logger.level: DEBUG` temporarily only when diagnosing UART/configuration issues. The normal package default is `INFO`.
- Keep `logger.baud_rate: 0` when the UART used by C4002 could otherwise be shared with serial logging.
- Use `Refresh Parameters` to query the sensor. It does not overwrite C4002 settings.
- If the component reports a gate-table refresh failure, it intentionally keeps the last verified Home Assistant values rather than publishing stale cached values as new data.
- Confirm TX/RX are crossed and that the sensor receives stable 5 V power before investigating configuration issues.

## References

- [DFRobot C4002 library](https://github.com/DFRobot/DFRobot_C4002)
- [SEN0691 product documentation](https://wiki.dfrobot.com/sen0691/)
- [DFRobot factory-reset example](https://github.com/DFRobot/DFRobot_C4002/blob/main/examples/factoryReset/factoryReset.ino)
