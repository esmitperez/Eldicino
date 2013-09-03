/*
  Author:  Esmit Perez
  Fecha:   Jul 10 2013

  Inspirado en http://playground.arduino.cc/Code/StopWatchClass y http://arduino.cc/en/Hacking/LibraryTutorial

*/

#ifndef Player_h
#define Player_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Vector.h"
#include "Actor.h"

class Player {

public:
    LiquidCrystal *lcd;
    int buzzerPin;

    int lcdRows;
    int lcdCols;

    int numActors = 0;
    Vector<Actor> actors;

    void info();
    void render();
    void showFrameFor(Actor *actor);
    void clearBubble(Actor *actor);
    void gotoPos(Actor *actor,int x,int y);

    Player(int buzzerPin, int numRows, int numCols, int howManyActors, Vector<Actor> a);

};

#endif
