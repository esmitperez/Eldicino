/*
  Author:  Esmit Perez
  Fecha:   Jul 10 2013

  Inspirado en http://playground.arduino.cc/Code/StopWatchClass y http://arduino.cc/en/Hacking/LibraryTutorial

*/
#include <LiquidCrystal.h>


#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Animation.h"
#include "Player.h"
#include "constants.h"

Player::Player(int buzzer, int numRows, int numCols, int howManyActors, Vector<Actor> actrs) {
    buzzerPin = buzzer;
    lcdRows = numRows;
    lcdCols = numCols;
    numActors = howManyActors;
    
    /*
    int l =  sizeof(Actor*)  * numActors;
    actors = (Actor*) malloc(l);
    */
    
    actors = actrs;
}

void Player::showFrameFor(Actor *actor) {
    /*
    if (DEBUG_ON) {
        Serial.print("METHOD: showFrameFor");
        Serial.print("Actor: ");
        Serial.print(actor.name);
        Serial.println();
    }<
    */

    lcd->setCursor(actor->pos_curr_x, actor->pos_curr_y);
    lcd->write(byte(actor->actorCharNumber));
}

void Player::clearBubble(Actor *actor) {
    lcd->setCursor(actor->bubble_x,actor->bubble_y);
    for (int i=0; i<actor->bubble_size; i++) {
        lcd->print(" ");
    }
    lcd->setCursor(actor->bubble_x,actor->bubble_y);
}



void Player::gotoPos(Actor *actor,int x,int y) {
    lcd->setCursor(actor->pos_curr_x, actor->pos_curr_y);
    lcd->print(" ");

    actor->pos_prev_x = actor->pos_curr_x;
    actor->pos_prev_y = actor->pos_curr_y;

    actor->pos_curr_x = x%lcdCols;
    actor->pos_curr_y = y%lcdRows;

    lcd->setCursor(actor->pos_curr_x, actor->pos_curr_y);
}

void Player::info() {
    #if DEBUG_ON == true
        Serial.print("Num actors");
        Serial.println(actors.size());
    #endif

    for (int i=0; i<numActors; i++) {
        Actor actor = actors[i];
        Animation *clip = actor.currentAnimation;
        
        #if DEBUG_ON == true
          actor.info();
        #endif
    }

}


void Player::render() {

    for (int i=0; i<numActors; i++) {
        Actor *actor = &actors[i];
        Animation *clip = actor->currentAnimation;
        #if DEBUG_ON == true
            actor->info();

            Serial.print(" Movie: ");
            Serial.print(clip->name);
            Serial.print(" Num Frames:");
            Serial.print(clip->numFrames);
            Serial.println();
        #endif

        for (int j = 0; j < clip->numFrames; j++) {

            int byteOffset= (j * FRAME_SIZE);

            /* inefficient since it allocates memory for data we already &have loadaed
            byte* frame = (byte*) malloc(sizeof(byte) * FRAME_SIZE);
            int byteOffset= (i * FRAME_SIZE);

            for (int i=0; i<FRAME_SIZE;i++){
                frame[i] = clip.frames[byteOffset+i];
            }
            */
            //&clip->frames[byteOffset]

            lcd->createChar(actor->actorCharNumber, &clip->frames[byteOffset]);
         
            showFrameFor(actor);

            
            #if DEBUG_ON == true
            //    Serial.print("Frame: ");
            //    Serial.println(i);
            #endif

            if (clip->makeSound) {

                tone(buzzerPin, clip->melody[i%clip->melodySize], clip->melodySpeed);
                delay(clip->melodyDelay);
                noTone(buzzerPin);
            }


            delay(clip->animationPause);
            if (clip->direction == 0 || i==0 ) continue;

            int posMultiplier = clip->direction * 1;
            int x = actor->pos_curr_x+posMultiplier;
            int y = actor->pos_curr_y;
            
            actor->info();
            gotoPos(actor,x, y);
            actor->info();
        }
    }

}
