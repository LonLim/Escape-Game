import time

from luma.led_matrix.device import unicornhathd
from luma.core.interface.serial import spi, noop
from luma.core.render import canvas

serial = spi(port=0, device=0, gpio=noop())
device = unicornhathd(serial)

for y in range(device.height):
    for x in range(device.width):
        with canvas(device) as draw:
            draw.point((x, y), fill="white")
        time.sleep(0.5)
