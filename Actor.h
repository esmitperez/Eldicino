/*
  Author:  Esmit Perez (@esmitperez)
  Fecha:   Jul 10 2013

  Inspirado en http://playground.arduino.cc/Code/StopWatchClass y http://arduino.cc/en/Hacking/LibraryTutorial

*/

#ifndef Actor_h
#define Actor_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Animation.h"


class Actor {

public:
    char* name;
    int actorCharNumber;
    Animation *defaultAnimation;
    Animation *currentAnimation;

    int pos_curr_x;
    int pos_curr_y;

    int pos_prev_x;
    int pos_prev_y;

    int bubble_x;
    int bubble_y;
    int bubble_size;
    boolean speaks = false;
    
    void info();

    Actor(char* name,int initialX, int initialY, int id, Animation &a);

};

#endif
