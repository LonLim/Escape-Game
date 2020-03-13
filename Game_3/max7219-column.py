from luma.core.interface.serial import spi, noop
from luma.core.render import canvas
from luma.led_matrix.device import max7219
import time

serial = spi(port=0, device=0, gpio=noop())
device = max7219(serial)


for y in range(device.height):
    for x in range(device.width):
        with canvas(device) as draw:
            draw.point((x, y), fill="white")
        time.sleep(0.5)
