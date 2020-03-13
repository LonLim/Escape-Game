#!/usr/bin/env python

import spi

### Initialize an SPI connection using BCM-mode pins 21, 20, and 16
max7219 = spi.SPI(clk=21, cs=20, mosi=16, miso=None, verbose=True)

### Zero out all registers
for cmd in range(16):
    packet = cmd << 8
    max7219.put(packet,12)

### Enable all columns via the scan limit register
max7219.put(int("101100000111",2),12)

### Disable shutdown mode
max7219.put(int("110000000001",2),12)

### Illuminate column 2 with a specific pattern
max7219.put(int("001000100111",2),12)

try:
    input("Press return to continue")
except:
    pass