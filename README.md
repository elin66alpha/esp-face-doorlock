# esp-face-doorlock
face recognition door lock, communicate with esp8266
esp8266 controls a servo to unlock the door, wifi-sta receive a signal from esp32
esp32-cam records 5 face picture(manually) in sd card at start, using these 5 pictore recognize face.
if correct face, tells esp8266 to unlock the door.
