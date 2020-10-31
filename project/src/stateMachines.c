#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

static char transition = -1; 
char toggle_red()		/* always toggle! */
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
    red_on = 0;
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
    red_on = 1;
    statep = 0;
    break; 
  }
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
  return 1;
}

void transition_advance()
{
  int i;
  for (i =0; i != 251; i++){
    if(i==250){
      transition++;
      state_advance();
    }
  }
}



void state_advance()		/* alternate between toggling red & green */
{
  char changed = 0;  

  switch(transition){
  case 0:
    changed=toggle_red25();
    buzzer_set_period(2000000/147); 
    break;
  case 1:
    changed = toggle_red75();
    break;
  case 2:
    changed = toggle_green();
    break;
  case 3:
    changed = toggle_red50();
    break;
  default:
    break;
  }
  led_changed = changed;
  led_update();
}



