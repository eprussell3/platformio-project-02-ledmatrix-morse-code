Arduino UNO R4 Wifi experimental/demo project that "broadcasts" a text message using morse code.
The morse code is "sent" via the onboard LED and connects to a breadboard with an active buzzer
using Pin 5 GND pin on the DIGITAL PWM connector (see schematic)

Important Notes:
1. This code was written for the Arduino UNO Wifi R4 which has an LED display matrix. The standard UNO does not have the LED matrix, so you will have to delete any of the code that intializes and/or interacts with the matrix
2. I used the smraza S15 component kit (see https://smraza.com) which includes the breadboard, active buzzer, and jumper cables (as well as dozens of other parts)
3. The program "broadcasts" the morse code via the UNO's onboard LED and the active buzzer so that you don't actually need the buzzer as the LED flashes the dots and dashes. No coding changes required
4. The entire project was written using MS Visual Code and the PlatformIO extension (not the Arduino IDE) so there may be some modification required if you are using the IDE
