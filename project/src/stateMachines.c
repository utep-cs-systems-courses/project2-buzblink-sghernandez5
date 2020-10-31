
#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"



char toggle_red()		/* always toggle!
				 */
{
  static char state = 0;

  switch (state) {
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }
  return 1;			/* always changes an led */
}

char toggle_green()	/* only toggle green if red is on!  */
{
  char changed = 0;
  if (red_on) {
    green_on ^= 1;
    changed = 1;
  }
  return changed;
}

char toggle_red25()
{
  static char statep = 0;
  switch (statep){
  case 0:
    red_on = 1;
    statep = 1;
    break; 
  case 1:
    red_on = 0;
    statep = 2;
    break; 
  case 2:
    red_on = 0;
    statep = 3;
    break; 
  case 3:
    red_on = 0;
    statep = 0;
    break; 
  }
  led_changed = 1;
  led_update();
  return 1; 
}

char toggle_red50()
{
  static char statef = 0;
  switch (statef){
  case 0:
    red_on = 0;
    statef = 1;
    break; 
  case 1:
    red_on = 0;
    statef = 2;
    break; 
  case 2:
    red_on = 1;
    statef = 3;
    break; 
  case 3:
    red_on = 1;
    statef = 0;
    break;
  }
  led_changed = 1;
  led_update(); 
  return 1; 
}

char toggle_red75()
{
  static char states =0;
  switch (states){
  case 0:
    red_on = 0;
    states = 1;
    break; 
  case 1:
    red_on = 1;
    states = 2;
    break; 
  case 2:
    red_on = 1;
    states = 3;
    break; 
  case 3:
    red_on = 1;
    states = 0;
    break;
  }
  led_changed = 1;
  led_update(); 
  return 1;
  }
void transition_advance()
{
  static char sb = 0;
  static char blink_count=0;
  // play buzzer through here
    if(++blink_count==250){
      //call state advance which will turn on an LED
      switch(sb){
      case 0:
	buzzer_set_period(2000000/220);
	sb++;
        state_advance();       
	break;
      case 1:
	buzzer_set_period(2000000/400);
	sb++;
	state_advance(); 
	break; 
      case 2:
	buzzer_set_period(2000000/200);
	sb++;
	state_advance(); 
	break;
      case 3:
	buzzer_set_period(2000000/320);
	sb++;
	state_advance(); 
	break;
      case 4: 
	buzzer_set_period(2000000/240);
	sb++;
	state_advance(); 
	break;
      default:
	buzzer_set_period(0);
	state_advance();
	break; 
      }
      blink_count = 0;
    }
}



void state_advance()		/* alternate between toggling red & green */
{
  static char changed = 0;
  static char blink_count = 0;
  static char transition = 0;
  static char cases = 0; 
  switch(transition){
  case 0:
    blink_count =0; 
    while(++blink_count != 62){
    changed = toggle_red25();
    }
    transition++;
    break; 
  case 1:
    blink_count =0; 
    while(++blink_count != 62){
      changed = toggle_red75(); 
    }
    transition++; 
    break;
  case 2:
    blink_count = 0; 
    while (++blink_count != 62){
    changed = toggle_red25();
    }
    transition++;
    break; 
  case 3:
    blink_count = 0; 
    while(++blink_count!= 62){
    changed =  toggle_red25(); 
    }
    transition++;
    break;
  default:
    //turn off
    red_on = 0;
    green_on =0; 
    changed = 1; 
    break;
  }
  blink_count = 0; 
  //led_changed = changed;
  //led_update(); 
} 




