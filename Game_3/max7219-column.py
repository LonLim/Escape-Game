from luma.core.interface.serial import spi, noop
from luma.core.render import canvas
from luma.led_matrix.device import max7219
import time

serial = spi(port=0, device=0, gpio=noop())
device = max7219(serial)


while True:
    
 with canvas(device) as draw:
    draw.line((0, 0, 0, device.height), fill="red")
    time.sleep(0.5)
    draw.line((1, 0, 1, device.height), fill="orange")
    time.sleep(0.5)
    draw.line((2, 0, 2, device.height), fill="yellow")
    time.sleep(0.5)
    draw.line((3, 0, 3, device.height), fill="green")
    time.sleep(0.5)
    draw.line((4, 0, 4, device.height), fill="blue")
    time.sleep(0.5)
    draw.line((5, 0, 5, device.height), fill="indigo")
    time.sleep(0.5)
    draw.line((6, 0, 6, device.height), fill="violet")
    time.sleep(0.5)
    draw.line((7, 0, 7, device.height), fill="white")    
    time.sleep(0.5)
