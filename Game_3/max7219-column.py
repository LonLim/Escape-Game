from adafruit_max7219 import matrices
from board import TX, RX, A2
import busio
import digitalio
import time

clk = 23
din = 19
cs = digitalio.DigitalInOut(24)

spi = busio.SPI(clk, MOSI=din)
display = matrices.Matrix8x8(spi, cs)
while True:
    display.brightness(3)

    display.fill(1)
    display.pixel(3, 3)
    display.pixel(3, 4)
    display.pixel(4, 3)
    display.pixel(4, 4)
    display.show()
    time.sleep(3.0)

    display.clear_all()
    s = 'Hello, World!'
    for c in range(len(s)*8):
        display.fill(0)
        display.text(s,-c,0)
        display.show()
        time.sleep(0.25)
