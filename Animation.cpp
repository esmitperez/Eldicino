/*
  Author:  Esmit Perez
  Fecha:   Jul 10 2013

  Inspirado en http://playground.arduino.cc/Code/StopWatchClass y http://arduino.cc/en/Hacking/LibraryTutorial

*/


#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "constants.h"
#include "Animation.h"


Animation::Animation(char* n) {
    name = n;
}


Animation::Animation(char* n,int numF, int dir) {
    name = n;
    numFrames = numF;
    direction = dir;
}


Animation::Animation(char* n,int numF, int dir, byte* frms[]) {
    name = n;
    numFrames = numF;
    direction = dir;



    // allocate the memory we need FRAME_SIZE * the number of frames
    int l = sizeof(byte)  * FRAME_SIZE *  numF;
    frames = (byte*) malloc(l);

    // transfer every bit from all our frames, into the single byte[] we use for movies
    int k=0;
    for (int j = 0; j<numF; j++) {
        for (int i = 0; i<FRAME_SIZE; i++) {
            frames[k++] = frms[j][i];
        }
    }

}




Animation::Animation(char* n,int numF, int dir, byte* frms[],bool ms,int mSize,int m[]) {
    name = n;
    numFrames = numF;
    direction = dir;
    makeSound = ms;
    melodySize = mSize;

    /*
    framesN = new byte*[FRAME_SIZE];

     for (int j = 0; j<numF;j++){
       framesN[j] = (byte*) &frms[j];
     }
     */


    /**/

    // allocate the memory we need FRAME_SIZE * the number of frames
    int l = sizeof(byte)  * FRAME_SIZE *  numF;
    frames = (byte*) malloc(l);

    // transfer every bit from all our frames, into the single byte[] we use for movies
    int k=0;
    for (int j = 0; j<numF; j++) {
        for (int i = 0; i<FRAME_SIZE; i++) {
            frames[k++] = frms[j][i];
        }
    }
    //*/

    // same allocation/bit transfer for melodies
    l = sizeof(int) * mSize;
    melody = (int*) malloc(l);

    //melody = new int[mSize];
    for (int j = 0; j<mSize; j++) {
        melody[j] =  m[j];
    }

}


