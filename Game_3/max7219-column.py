from luma.core.legacy import text
from luma.core.legacy.font import proportional, CP437_FONT, LCD_FONT

with canvas(device) as draw:
    text(draw, (0, 0), "1", fill="white", font=proportional(CP437_FONT))
