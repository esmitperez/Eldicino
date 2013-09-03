/*
  Author:  Esmit Perez  (@esmitperez)
  Fecha:   Jul 10 2013

  Inspirado en http://playground.arduino.cc/Code/StopWatchClass y http://arduino.cc/en/Hacking/LibraryTutorial

*/

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

typedef struct AnimationS {
    String name;
    int numFrames;
    int direction; // -1 left, 0 static, +1 right
    unsigned char* frames[30];
    int animationPause;
    bool makeSound;
    int melodySize;
    int melody[10];
    int melodySpeed;
    int melodyDelay;

} ;


typedef struct ActorS {
    String name;
    int pos_curr_x;
    int pos_curr_y;

    int pos_prev_x;
    int pos_prev_y;

    int bubble_x;
    int bubble_y;
    int bubble_size;

};




