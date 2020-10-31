
#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"

char buttonPressed = 0; 

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
    red_on = 1;
    statef = 1;
    break; 
  case 1:
    red_on = 1;
    statef = 2;
    break; 
  case 2:
    red_on = 0;
    statef = 3;
    break; 
  case 3:
    red_on = 0;
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
    red_on = 1;
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
    red_on = 0;
    states = 0;
    break;
  }
  led_changed = 1;
  led_update(); 
  return 1;
  }

void led_advance()		/* alternate between toggling red & green */
{
  static char changed = 0;
  static char blink_count = 0;
  static char transition = 0;
  switch(transition){
  case 0:
    blink_count =0; 
    while(++blink_count != 4){
    changed = toggle_red25();
    }
    transition++;
    break;

  case 1:
    blink_count = 0;
    red_on = 0;
    led_changed = 1;
    led_update();
    transition++; 
    break; 
  case 2:
    blink_count =0; 
    while(++blink_count != 4){
      changed = toggle_red75(); 
    }
    transition++; 
    break;
    
  case 3:
    blink_count = 0; 
    changed = toggle_green();
    red_on = 0;
    led_changed = 1;
    led_update(); 
    transition++;
    break; 
  case 4:
    blink_count = 0; 
    while(++blink_count!= 4){
    changed =  toggle_red50(); 
    }
    transition++;
    break;
  default:
    //turn off both LEDS 
    transition++; 
    red_on = 0;
    green_on =0; 
    led_changed = 1;
    led_update(); 
    break;
  }
  blink_count = 0;  
} 



void buzz_advance()
{
  static char sb = 0;
  static char blink_count=0;
  // play buzzer through here
    if(++blink_count==250){
      //call state advance which will turn on an LED in sync with music notes
      switch(sb){
      case 0:
	// D4 and A3
	buzzer_set_period(2000000/294);
	buzzer_set_period(2000000/220); 
	sb++;       
	break;
      case 1:
	//F#4
	buzzer_set_period(2000000/370); ;
	sb++; 
	break; 
      case 2:
	// F#4 and C#5
	buzzer_set_period(2000000/370);
	buzzer_set_period(2000000/554); 
	sb++; 
	break;
      case 3:
	//E4
	buzzer_set_period(2000000/330);
	sb++; 
	break;
      case 4:
	//G4
	buzzer_set_period(2000000/392);
	sb++; 
	break;
      case 5:
	//G4 and D5
	buzzer_set_period(2000000/392);
	buzzer_set_period(2000000/587);
	sb++; 
      default:
	//turn off buzzer
	buzzer_set_period(0);
	break; 
      }
      blink_count = 0;
    }
}




void transition_advance()
{
  static char sb = 0;
  static char blink_count=0;
  // play buzzer through here
    if(++blink_count==250){
      //call state advance which will turn on an LED in sync with music notes
      switch(sb){
      case 0:
	// D4 and A3
	buzzer_set_period(2000000/294);
	buzzer_set_period(2000000/220); 
	sb++;
        state_advance();       
	break;
      case 1:
	//F#4
	buzzer_set_period(2000000/370); ;
	sb++;
	state_advance(); 
	break; 
      case 2:
	// F#4 and C#5
	buzzer_set_period(2000000/370);
	buzzer_set_period(2000000/554); 
	sb++;
	state_advance(); 
	break;
      case 3:
	//E4
	buzzer_set_period(2000000/330);
	sb++;
	state_advance(); 
	break;
      case 4:
	//G4
	buzzer_set_period(2000000/392);
	sb++;
	state_advance(); 
	break;
      case 5:
	//G4 and D5
	buzzer_set_period(2000000/392);
	buzzer_set_period(2000000/587);
	sb++;
	state_advance(); 
      default:
	//turn off buzzer
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
    blink_count = 0;
    red_on = 0;
    led_changed = 1;
    led_update();
    transition++; 
    break; 
  case 2:
    blink_count =0; 
    while(++blink_count != 62){
      changed = toggle_red75(); 
    }
    transition++; 
    break;
    
  case 3:
    blink_count = 0; 
    changed = toggle_green();
    red_on = 0;
    led_changed = 1;
    led_update(); 
    transition++;
    break; 
  case 4:
    blink_count = 0; 
    while(++blink_count!= 62){
    changed =  toggle_red50(); 
    }
    transition++;
    break;
  default:
    //turn off both LEDS 
    transition++; 
    red_on = 0;
    green_on =0; 
    led_changed = 1;
    led_update(); 
    break;
  }
  blink_count = 0;  
} 




