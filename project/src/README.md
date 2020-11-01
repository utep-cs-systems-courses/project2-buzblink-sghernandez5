## Lab Description
My project generates a song, and dynamically changes LEDS from dim requirement
in the lab. The buttons are used to changed from states.The button state
description is described below:



## Lab Instructions
To load code into MSP430, connect the MSP430 to the vm, and enter make.
Then you are ready to run and enter make load.



##How to use MSP430 description

Button S1: When pressed, leds transition from state state. Red leds transition
from dimness. This is shown in my led_advance() method, the red LED goes from
25 to 75, to turning on the green LED and to red 50.This state will contine
the transition of LEDS in a loop.

Button S2: When pressed, will genereate a sound pattern. This is shown in my
buzz_advance method. The sound pattern will repeat in a loop.

Button S3: When pressed, the LEDS and sound pattern are in sync. This is shown
with my transition method and state_advance method. However, the more it
repeats the more the LEDS get out of sync. The first two repeats the LEDS are
in sync.

Button S4:When pressed, both LEDS and buzzer are turn off. This is to cut off
any loops from the pressed buttons from S1-S3.


  








