/*
  Author:  Esmit Perez  (@esmitperez)
  Fecha:   Jul 10 2013

  Inspirado en http://playground.arduino.cc/Code/StopWatchClass y http://arduino.cc/en/Hacking/LibraryTutorial

*/


#ifndef Eldicino_Frames_h
#define Eldicino_Frames_h


#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <avr/pgmspace.h>


// *****************************************************
// http://www.quinapalus.com/hd44780udg.html

byte bellFrame[FRAME_SIZE] = {
    B00100,
    B01110,
    B01110,
    B01110,
    B11111,
    B0,
    B00100,
    B0
};


byte eldicino_front[FRAME_SIZE] = {
    B01110,
    B01110,
    B01110,
    B00100,
    B11111,
    B00100,
    B01010,
    B11011
};


byte eldicino_tapFootR[FRAME_SIZE] = {
    B01110,
    B01110,
    B01110,
    B00100,
    B01110,
    B10101,
    B11010,
    B01011
};


byte eldicino_walk_l1[FRAME_SIZE] = {
    B01110,
    B01110,
    B01110,
    B10100,
    B01110,
    B00101,
    B01010,
    B11001
};

byte eldicino_walk_l2[FRAME_SIZE] = {
    B01110,
    B01110,
    B01110,
    B00101,
    B01110,
    B10100,
    B01010,
    B11001
};


byte eldicino_walk_r1[FRAME_SIZE] = {
    B01110,
    B01110,
    B01110,
    B00101,
    B01110,
    B10100,
    B01010,
    B10011
};

byte eldicino_walk_r2[FRAME_SIZE] = {
    B01110,
    B01110,
    B01110,
    B10100,
    B01110,
    B00101,
    B01010,
    B10011
};



byte eldicino_helloL1[FRAME_SIZE] = {
    B01110,
    B01110,
    B01110,
    B00101,
    B01110,
    B10100,
    B01010,
    B11011
};

byte eldicino_helloL2[FRAME_SIZE] = {
    B01110,
    B01110,
    B01110,
    B00100,
    B01111,
    B10100,
    B01010,
    B11011
};

byte eldicino_helloR1[FRAME_SIZE] = {
    B01110,
    B01110,
    B01110,
    B10100,
    B01110,
    B00101,
    B01010,
    B11011
};

byte eldicino_helloR2[FRAME_SIZE] = {
    B01110,
    B01110,
    B01110,
    B00100,
    B11110,
    B00101,
    B01010,
    B11011
};

byte eldicino_rest[FRAME_SIZE] = {
    B01110,
    B01110,
    B01110,
    B00100,
    B01110,
    B10101,
    B01010,
    B11011
};


byte eldicino_happy1[FRAME_SIZE] = {
    B01110,
    B01110,
    B01110,
    B10101,
    B01110,
    B00100,
    B01010,
    B11011
};
byte eldicino_happy2[FRAME_SIZE] =
{B1110,B1110,B1110,B10101,B1110,B10101,B11011,B0};



byte eldicino_sit[FRAME_SIZE] = {
    B0,B1110,B1110,B1110,B100,B11111,B1110,B11011
};

byte eldicino_bumpR[FRAME_SIZE] = {B11,B10011,B1011,B10,B111,B10,B10010,B1001};

byte eldicino_bumpL[FRAME_SIZE] = {B11000,B11001,B11010,B1000,B11100,B1000,B1001,B10010};


byte emptyFrame[FRAME_SIZE] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000
};




#endif

