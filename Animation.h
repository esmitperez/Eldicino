/*
  Author:  Esmit Perez  (@esmitperez)
  Fecha:   Jul 10 2013

  Inspirado en http://playground.arduino.cc/Code/StopWatchClass y http://arduino.cc/en/Hacking/LibraryTutorial

*/


#ifndef Animation_h
#define Animation_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define ANIMATION_SIZE 50

#define DEFAULT_MELODY_SPEED 100
#define DEFAULT_MELODY_DELAY 20
#define DEFAULT_ANIMATION_PAUSE 30


class Animation {
public:
    char* name;
    int numFrames;
    int direction; // -1 left, 0 static, +1 right
    byte* frames;
    //byte **frames;
    int animationPause = DEFAULT_ANIMATION_PAUSE;
    bool makeSound = false;
    int melodySize =0;
    int* melody;
    int melodySpeed = DEFAULT_MELODY_SPEED;
    int melodyDelay = DEFAULT_MELODY_DELAY;
    bool mirrorFrames = false;

    Animation(char* name);

    Animation(char* name,int numFrames, int direction);

    Animation(char* name,int numFrames, int direction, byte* frames[]);

    Animation(char* name,int numFrames, int direction, byte* frames[],bool makeSound,int melodySize,int melody[]);

};


#endif
