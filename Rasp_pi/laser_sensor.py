from gpiozero import LightSensor
ldr = LightSensor(17)
print(ldr.value)

## Pause until no light is detected
wait_for_dark()
## Pause until light is detected
wait_for_light()
## Return True if light is detected
light_detected
## Function to run when it is dark
when_dark = my_function
## Function to run when it is light
when_light = my_function

Used wait_for_light() to call our function
For more information, check https://projects.raspberrypi.org/en/projects/laser-tripwire/3
