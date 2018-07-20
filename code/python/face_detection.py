import sensor
import time
import image
from pyb import LED
import pyb

sensor.reset()
led=LED(1)
led.toggle()

sensor.set_contrast(1)
sensor.set_gainceiling(16)

sensor.set_framesize(sensor.HQVGA)
sensor.set_pixformat(sensor.RGB565)

face_cascade = image.HaarCascade("frontalface", stages=25)
print(face_cascade)

clock = time.clock()

while (True):
    clock.tick()
    led.off()
    img = sensor.snapshot()

    objects = img.find_features(face_cascade, threshold=0.75, scale_factor=1.25)

    for r in objects:
        img.draw_rectangle(r)
        led.on()
        pyb.delay(1000)
