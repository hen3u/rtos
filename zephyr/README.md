# Build Zephyr for STM32 "bluepill"

## Hardware
- Linux host computer
- STM32F103C8T6 (STM32 "bluepill")
- ST-LINK/V2

## Setup and wiring
BOOT0 = 0
BOOT1 = 0

| STM32 | ST-LINK/V2 |
| ----- | ---------- |
| R     | RST        |
| GND   | GND        |
| SWCLK | SWCLK      |
| SWIO  | SWDIO      |
| 3.3V  | 3.3V       |

## Getting started

```sh
$ ./install.sh
$ source .venv/bin/activate
$ west init zephyr-project
$ cd zephyr-project
$ west update hal_stm32
$ pip install -r zephyr/scripts/requirements.txt
$ cd zephyr
$ west build -b stm32_min_dev samples/basic/blinky
$ west flash
```

## Debugging
NOTE: RX = green, TX = white

| STM32 | FTDI |
| ----- | ---- |
| 5V    | VCC  |
| GND   | GND  |
| A9    | RX   |
| A10   | TX   |

```
$ sudo picocom -b 115200 /dev/ttyUSB0
```

## Troubleshoot

```sh
# Error: libusb_open() failed with LIBUSB_ERROR_ACCESS
# Error: open failed

sudo cp ~/zephyr-sdk-0.17.0/sysroots/x86_64-pokysdk-linux/usr/share/openocd/contrib/60-openocd.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules
sudo usermod -aG plugdev $USER
# unplug replug ST-LINK/V2 if necessary
```

## References
[1] https://docs.zephyrproject.org/latest/boards/others/stm32_min_dev/doc/index.html<br>
[2] https://github.com/zephyrproject-rtos/docker-image<br>
[3] https://www.blaess.fr/christophe/2024/10/15/zephir-os-et-raspberry-pico-premiere-prise-en-main/<br>
