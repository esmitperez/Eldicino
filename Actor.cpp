/*
  Author:  Esmit Perez (@esmitperez)
  Fecha:   Jul 10 2013

  Inspirado en http://playground.arduino.cc/Code/StopWatchClass y http://arduino.cc/en/Hacking/LibraryTutorial

*/

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Actor.h"
#include "constants.h"


Actor::Actor(char* n,int initialX, int initialY, int i, Animation &defAnimation) {
    name = n;
    actorCharNumber = i;
    pos_curr_x = initialX;
    pos_curr_y = initialY;
    defaultAnimation = &defAnimation;
    currentAnimation = &defAnimation;
}


void Actor::info() {
 
  #if DEBUG_ON == true
      Serial.print("Actor: ");
      Serial.print(name);
      Serial.print(", actorCharNumber");
      Serial.print(actorCharNumber);
      Serial.print(", X: ");
      Serial.print(pos_curr_x);
      Serial.print(", Y: ");
      Serial.print(pos_curr_y);
      Serial.print(", Current Movie: ");
      Serial.println(currentAnimation->name);  
  #endif
 
}



