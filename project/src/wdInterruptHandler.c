
#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"
#include "buzzer.h"
#include "led.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  // the switch staement will transition through buttons 
  switch(buttonPressed){
  case 1:
    //turn on dim red leds with green
    led_advance();
    break;
  case 2:
    //turn on music only
    buzz_advance();
    break; 
  case 3:
    //sync music and leds
    transition_advance();
    break;
  case 4:
    //automatically turn off both leds and buzzer
    buzzer_set_period(0);
    red_on = 0;
    green_on = 0;
    led_changed = 1;
    led_update();
    break; 
  } 
}
  

