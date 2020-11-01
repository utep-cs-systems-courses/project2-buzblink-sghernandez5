
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

//the method below is used to make the red LED dimness at 25%
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


// the method below wil be used to make the red LED dimmness at 50%
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

// the method below wil be used to make the red LED dimness at 75%
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
/* alternate between toggling red and green
   red LED will differe in dimness based on the method calls
   this method will be used for S1, button 1
*/
void led_advance()	      
{
  static char changed = 0;
  static char count = 0;
  static char transition = 0;
  static char cases = 0;
  /* the if statement will give enough time, 1 sec, to see the LED transition from different states
  ex: toggle_red25(), wait 60 seconds, turn off red, wait 60 seconds toggle_red75()... */
  if(++count != 250){
  switch(transition){
  case 0: 
    led_changed = toggle_red25();
    break;

  case 1:
    red_on = 0;
    led_changed = 1;
    led_update(); 
    break; 
  case 2:
    led_changed = toggle_red75(); 
    break;
    
  case 3: 
    led_changed = toggle_green();
    red_on = 0;
    led_update();
    break; 
  case 4:
    changed =  toggle_red50();
    break;
  default:
    //turn off both LEDS  at the end of the LED state transition 
    red_on = 0;
    green_on =0; 
    led_changed = 1;
    led_update(); 
    break;
  }
  }
  // go back to the beginning of the "loop" else increment the state transition to go through states
  else{
    if(transition == 4){
      transition = 0;
      count = 0;
        }
    else{
      transition++;
    }
  }  
} 

/*
  The method below will be used for button 2 or S2, buzz_advance() will go generate a buzzer tune. 
  The notes will transition from state to state. And the notes will be played for one second, by the the if statement. 
 */
void buzz_advance()
{
  static char sb = 0;
  static char blink_count=0;
  // play buzzer through here
    if(++blink_count==250){
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
	//turn off buzzer at the end and repeat tune again
	buzzer_set_period(0);
	sb=0;
	break; 
      }
      blink_count = 0;
    }
}
/*
  The method below, transition advance wil be used for button3, this button will play the buzzer tune and the leds at the same time. 
  Transition advance focuses on the buzzer and will play each note for one second,(not the double notes per case this will be very fast), and will call the state_advance metho to start the LED states. 
 */
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
	sb=0; 
	break; 
      }
      blink_count = 0;
    }
}


/*  The method below will be called by transition advance, this method focused on the LEDS. The red LED will transition in dimness based on the toggle method called and the green LED will be based on the toggle green method. 
 */
void state_advance()	  
{
  static char changed = 0;
  static char blink_count = 0;
  static char transition = 0;
  static char cases = 0; 
  switch(transition){
  case 0:
    blink_count =0;
    /* to keep up with the note that is being played by the buzzer, and for the LED to have enough time to enable toggle red 25, i use a loop. So i can see the red LED dimmness. Without the loop, it happens so fast because it is based on the time of the buzzer.*/ 
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
    //turn off both LEDS and repeat state advance by setting transition to 0. 
    transition =0;  
    red_on = 0;
    green_on =0; 
    led_changed = 1;
    led_update(); 
    break;
  }
  blink_count = 0;  
} 




