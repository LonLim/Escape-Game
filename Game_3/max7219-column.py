from luma.core.legacy import text
from luma.core.legacy.font import proportional, CP437_FONT, LCD_FONT
from luma.core.interface.serial import spi, noop
from luma.core.render import canvas
from luma.led_matrix.device import max7219
import time

serial = spi(port=0, device=0, gpio=noop())
device = max7219(serial)

while True:
    with canvas(device) as draw:
        text(draw, (0, 0), "1", fill="white", font=proportional(CP437_FONT))
time.sleep(0.1)
