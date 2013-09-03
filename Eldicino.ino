/*
Author:  Esmit Perez
Fecha:   Jul 10 2013

Inspirado en http://playground.arduino.cc/Code/StopWatchClass y http://arduino.cc/en/Hacking/LibraryTutorial

*/

// include the library code:
#include <LiquidCrystal.h>
#include <Wire.h>

// http://playground.arduino.cc/Code/AvailableMemory

#include <avr/pgmspace.h>

//#include "structures.h"

#include "constants.h"
#include "pitches.h"
#include "Animation.h"
#include "Eldicino_Frames.h"
#include "Actor.h"
#include "Player.h"
#include "Vector.h"

// PINs
#define REDLITE 3
#define GREENLITE 5
#define BLUELITE 6


#define LCD_ROWS 2
#define LCD_COLS 16
#define LCD_MAX_CHARS 8 // LCD library max is 8


#define SELECT_PIN 2
#define BTN_1_PIN 12
#define BTN_2_PIN 11
#define BTN_3_PIN 10


#define JOYSTICK_X_PIN A0
#define JOYSTICK_Y_PIN A1
#define BUZZER_PIN 4

#define DEFAULT_INACTIVITY_TRESHOLD 15

// initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
LiquidCrystal lcd(0); // Adafruit's LCD lib for I2C

// JOYSTICK
int oldX = 0;
int oldY = 0;
int oldSelect = 0;
int oldSelect1 = 0;
int oldSelect2 = 0;
int oldSelect3 = 0;


int joystick_x;
int joystick_y;
int select;

int select1;
int select2;
int select3;


byte* movie[] = {eldicino_walk_r1,eldicino_walk_r2};
int melody[] = {NOTE_F2,NOTE_E1};
Animation eldicinoWalkR ("eldicinoWalkR",2,1, movie,true,2,melody);


byte* movieeldicinoWalkL[] = {eldicino_walk_l1,eldicino_walk_l2};
int melodyeldicinoWalkL[] = {NOTE_E1,NOTE_F2};
Animation eldicinoWalkL ("eldicinoWalkL",2,-1, movieeldicinoWalkL,true,2,melodyeldicinoWalkL);

byte* movie3[] = {eldicino_rest};
int melody3[] = {NOTE_C3};
Animation eldicinoRest ("eldicinoRest",1,0, movie3,false,0,melody3);


byte* movieeldicinoBumpR[] = {eldicino_walk_r2,eldicino_bumpR};
int melodyeldicinoBumpR[] = {NOTE_A1,NOTE_A1,NOTE_A1,NOTE_A1};
Animation eldicinoBumpR ("eldicinoBumpR",2,0, movieeldicinoBumpR,true,4,melodyeldicinoBumpR);

byte* movieeldicinoBumpL[] = {eldicino_walk_l2,eldicino_bumpL};
int melodyeldicinoBumpL[] = {NOTE_A1,NOTE_A1,NOTE_A1,NOTE_A1};

Animation eldicinoBumpL ("eldicinoBumpL",2,0, movieeldicinoBumpL,true,4,melodyeldicinoBumpL);


byte* movieeldicinoHappy[] = {eldicino_rest,eldicino_happy1,eldicino_happy2,eldicino_happy2};
int melodyeldicinoHappy[] = {NOTE_C6,NOTE_D6,NOTE_E6};

Animation eldicinoHappy ("eldicinoHappy",4,0, movieeldicinoHappy,true,3,melodyeldicinoHappy);


byte* movieeldicinoSit[] = {eldicino_sit,eldicino_sit,eldicino_sit,eldicino_sit};
int melodyeldicinoSit[] = {NOTE_E6,NOTE_D6,NOTE_C6};
Animation eldicinoSit ("eldicinoSit",4,0, movieeldicinoSit,true,3,melodyeldicinoSit);


byte* movieeldicinoImpatient[] = {eldicino_rest,eldicino_tapFootR,eldicino_tapFootR,eldicino_rest};
int melodyeldicinoImpatient[] = {NOTE_A3};

Animation eldicinoImpatient ("eldicinoImpatient",4,0,movieeldicinoImpatient,true,1,melodyeldicinoImpatient);

byte* movieeldicinoHelloR[] = {
    eldicino_rest,
    eldicino_helloR1,
    eldicino_helloR2,
    eldicino_helloR1,
    eldicino_helloR2,
    eldicino_rest
};

int melodyeldicinoHelloR[] = {NOTE_F6,NOTE_F5,NOTE_F6};
Animation eldicinoHelloR("eldicinoHelloR",6,0, movieeldicinoHelloR,true,3,melodyeldicinoHelloR);


byte* mvemptyAnimation[] = {emptyFrame};
int mlemptyAnimation[] = {NOTE_A1};
Animation emptyAnimation ("emptyAnimation",1,0, mvemptyAnimation,false,0,mlemptyAnimation);


byte* bellMovie[] = {bellFrame};
Animation campanaDefault ("campanaDefault",1,0,bellMovie);

Actor eldicino("Eldicino",0,0,1,eldicinoRest);
Actor campana("Campana",10,1,2,campanaDefault);
Vector<Actor> actores;

Player player(BUZZER_PIN, LCD_ROWS, LCD_COLS, 2, actores);


// notes in the melody:
int themeMelody[] = {
    NOTE_C5, NOTE_C5,NOTE_C5, NOTE_C5, NOTE_D5,NOTE_F5,NOTE_F5
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
    4,4,4,4,4,4,4
};

boolean gameIntroShown = false;
double lastActionTime = millis();
bool introCleared = 0;

void setup() {
    // set up the LCD's number of rows and columns:
    lcd.begin(LCD_COLS, LCD_ROWS);

    if (DEBUG_ON) {
        Serial.begin(9600);
    }

    pinMode(REDLITE, OUTPUT);
    pinMode(GREENLITE, OUTPUT);
    pinMode(BLUELITE, OUTPUT);

    pinMode(SELECT_PIN, INPUT);
    pinMode(BTN_1_PIN, INPUT);
    pinMode(BTN_2_PIN, INPUT);
    pinMode(BTN_3_PIN, INPUT);

    pinMode(BUZZER_PIN,OUTPUT);


    digitalWrite(SELECT_PIN, HIGH);
    digitalWrite(BTN_1_PIN, HIGH);
    digitalWrite(BTN_2_PIN, HIGH);
    digitalWrite(BTN_3_PIN, HIGH);

 //   eldicino.currentAnimation = &eldicinoRest;
  //  campana.currentAnimation = &campanaDefault;
    
    player.actors.push_back(eldicino);
    player.actors.push_back(campana);

    
    player.lcd = &lcd;

}


void loop() {
  playerModeLoop(player.actors[0]);
}


void demoLoop(Actor &actor) {
    walkR(actor,15);
    jumpDown(actor);
    walkL(actor,15);
    jumpUp(actor);
}

int inactivityThreshold = DEFAULT_INACTIVITY_TRESHOLD;
void playerModeLoop(Actor &toPlayWith) {

    //lcd.setCursor(0,0);
    int joystick_x = map(analogRead(JOYSTICK_X_PIN), 0, 1023, 1, 20);
    int joystick_y = map(analogRead(JOYSTICK_Y_PIN), 0, 1023, 1, 20);


    if ((millis() - lastActionTime)/1000  > DEFAULT_INACTIVITY_TRESHOLD) {
        doRandomAction(toPlayWith);
        lastActionTime = millis();
        inactivityThreshold = random(DEFAULT_INACTIVITY_TRESHOLD*random(1,10));
    }

    select = !digitalRead(SELECT_PIN);
    select1 = !digitalRead(BTN_1_PIN);
    select2 = !digitalRead(BTN_2_PIN);
    select3 = !digitalRead(BTN_3_PIN);

    if((oldX != joystick_x) ||  (oldY != joystick_y) ||  (oldSelect != select) ||  (oldSelect1 != select1) ||  (oldSelect2 != select2) ||  (oldSelect3 != select3)) {
        lastActionTime = millis(); // flag that something happened

        oldX = joystick_x;
        oldY = joystick_y;
        oldSelect = select;
        oldSelect1 = select1;
        oldSelect2 = select2;
        oldSelect3 = select3;

        if (joystick_x == 10) {
            rest(toPlayWith,1);

        }
    }

    // FIX GAME INTRO
    if (!gameIntroShown) {
        playGameIntro();
    }

    if (introCleared==0) {
        lcd.clear();
        introCleared=1;
    }

    if (joystick_x > 10) {
        if (toPlayWith.bubble_size > 0) {
            clearBubble(toPlayWith);
        }
        walkR(toPlayWith,1);
    }

    if (joystick_x < 10) {
        if (toPlayWith.bubble_size > 0) {
            clearBubble(toPlayWith);
        }

        walkL(toPlayWith,1);
    }

    // UP
    if (joystick_y < 9) {
        jumpUp(toPlayWith);
    }

    // DOWN
    if (joystick_y > 11) {
        player.clearBubble(&toPlayWith);
        toPlayWith.currentAnimation = &eldicinoSit;
        player.render();
        
        if (toPlayWith.pos_curr_y < LCD_ROWS-1) {
            player.gotoPos(&toPlayWith,toPlayWith.pos_curr_x+0, toPlayWith.pos_curr_y+1 );
            
            //player.gotoPos(actor,actor.pos_curr_x, actor.pos_curr_y+1 );
            toPlayWith.currentAnimation = &eldicinoRest;
            player.render();
            
            //char m[] = "Wee!";
            //saySomething(toPlayWith,m);
        }        
        
        //jumpDown(toPlayWith);
    }

    if(select) {
        if (toPlayWith.bubble_size > 0) {
            clearBubble(toPlayWith);
        }

        // play(campana,campanaDefault);

    }

    if(select1) {
        if (toPlayWith.bubble_size > 0) {
            clearBubble(toPlayWith);
            tapFoot(eldicino,3);
        }

        // play(campana,campanaDefault);

    }

    if(select2) {
        if (toPlayWith.bubble_size > 0) {
            saySomething(toPlayWith,"Hola!");
            happy(eldicino,3);
            clearBubble(toPlayWith);
        }

        // play(campana,campanaDefault);

    }


    if(select3) {
        if (toPlayWith.bubble_size > 0) {
            saySomething(toPlayWith,"Sing!");
            playThemeSong();
            clearBubble(toPlayWith);
        }
        
        // play(campana,campanaDefault);
    }
    
    player.render();

}

void playGameIntro() {
    doRandomAction(eldicino);
    saySomething(eldicino," Soy Eldicino!",false);
    gameIntroShown=true;

}

void playThemeSong() {
// iterate over the notes of the melody:
    for (int thisNote = 0; thisNote < 8; thisNote++) {

        // to calculate the note duration, take one second
        // divided by the note type.
        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int noteDuration = 1000/noteDurations[thisNote];
        tone(BUZZER_PIN, themeMelody[thisNote],noteDuration);

        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = noteDuration ;
        delay(pauseBetweenNotes);
        // stop the tone playing:
        noTone(8);
    }
}


void jumpUp(Actor &actor) {
    if (actor.bubble_size > 0) {
        clearBubble(actor);
    }

    happy(actor,1);
    if (actor.pos_curr_y > 0) {
        gotoPos(actor,actor.pos_curr_x, actor.pos_curr_y-1 );
        rest(actor,1);
    }
}



void jumpDown(Actor &actor) {
    //if (actor.bubble_size > 0) {
    //    clearBubble(actor);
    //}

    sit(actor,1);
    if (actor.pos_curr_y < LCD_ROWS-1) {
        gotoPos(actor,actor.pos_curr_x, actor.pos_curr_y+1 );
        
        //player.gotoPos(actor,actor.pos_curr_x, actor.pos_curr_y+1 );
        rest(actor,1);
        char m[] = "Wee!";
        saySomething(actor,m);
    }
}

void rest(Actor &actor,int seconds) {
    actor.currentAnimation = &eldicinoRest;

    play(actor,eldicinoRest);
}


void happy(Actor &actor,int seconds) {
    actor.currentAnimation = &eldicinoHappy;

    play(actor,eldicinoHappy);
}


void sit(Actor &actor,int seconds) {
    actor.currentAnimation = &eldicinoSit;
    play(actor,eldicinoSit);
}

void tapFoot(Actor &actor,int times) {
    actor.currentAnimation = &eldicinoImpatient;
    for (int i=0; i<times; i++) {
        play(actor,eldicinoImpatient);
    }
}


void doMagic(Actor &actor) {
    //play(eldicino,eldicinoMagic);
    //saySomething("back!");
    //starGate(actor);
    tapFoot(actor,3);
}

void doRandomAction(Actor &actor) {
    int what = random(1,5);

    if (gameIntroShown) {
        char m[] = "hey!";
        saySomething(actor,m);
    }

    switch(what) {
    case 1:
        happy(actor,random(3));
        break;
    case 2:
        sit(actor,random(4));
        break;
    case 3:
        doMagic(actor);
        break;
    case 4:
        tapFoot(actor,2);
        break;
    default:
        waveHello(actor);
    }

    rest(actor,1);

};

void waveHello(Actor &actor) {
    actor.currentAnimation = &eldicinoHelloR;
    play(actor,eldicinoHelloR);
}




void clearBubble(Actor &actor) {
    lcd.setCursor(actor.bubble_x,actor.bubble_y);
    for (int i=0; i<actor.bubble_size; i++) {
        lcd.print(" ");
    }
    lcd.setCursor(actor.bubble_x,actor.bubble_y);
}



void saySomething(Actor &actor,char message[]) {
    saySomething(actor,message,true);
}

void saySomething(Actor &actor, char message[],boolean showLine) {

    if (actor.bubble_size > 0) {
        clearBubble(actor);
    }

    actor.bubble_size = strlen(message) + 1; // -message

    char pre[] = {};
    char pos[] = {};
    if (actor.pos_curr_x + actor.bubble_size <= LCD_COLS) {
        actor.bubble_x = actor.pos_curr_x + 1;
        actor.bubble_y = actor.pos_curr_y;
        lcd.setCursor(actor.bubble_x,actor.bubble_y);
        if (showLine) lcd.print("-");
        lcd.print(message);
    } else {
        actor.bubble_x = actor.pos_curr_x - actor.bubble_size;
        actor.bubble_y = actor.pos_curr_y;
        lcd.setCursor(actor.bubble_x,actor.bubble_y);
        lcd.print(message);
        if (showLine) lcd.print("-");
    }
}

void walkL(Actor &actor,int times) {
    if (actor.pos_curr_x>0) {
        for (int i=0; i<times; i++) {
            play(actor,eldicinoWalkL);
        }
    } else {
        bumpL(actor,1);
        char m[] = "Ouch!";
        saySomething(actor,m);
    }

}

void walkR(Actor &actor,int times) {
    if (actor.pos_curr_x<(LCD_COLS-1)) {
        for (int i=0; i<times; i++) {
            actor.currentAnimation = &eldicinoWalkR;
            play(actor,eldicinoWalkR);
        }

    } else {
        bumpR(actor,1);
        char m[] = "Ouch!";
        saySomething(actor,m);
    }
}


void bumpL(Actor &actor,int times) {
    for (int i=0; i<times; i++) {
        actor.currentAnimation = &eldicinoBumpL;
        play(actor,eldicinoBumpL);
    }
}

void bumpR(Actor &actor,int times) {
    for (int i=0; i<times; i++) {
        actor.currentAnimation = &eldicinoBumpR;
        play(actor,eldicinoBumpR);
    }
}


void gotoPos(Actor &actor,int x,int y) {
    lcd.setCursor(actor.pos_curr_x, actor.pos_curr_y);
    lcd.print(" ");

    actor.pos_prev_x = actor.pos_curr_x;
    actor.pos_prev_y = actor.pos_curr_y;

    actor.pos_curr_x = x%LCD_COLS;
    actor.pos_curr_y = y%LCD_ROWS;

    lcd.setCursor(actor.pos_curr_x, actor.pos_curr_y);
}

void showFrameFor(Actor &actor) {
    lcd.setCursor(actor.pos_curr_x, actor.pos_curr_y);
    lcd.write(byte(actor.actorCharNumber));
}

void play(Actor &actor, Animation &clip) {
    if (DEBUG_ON) {
        Serial.print("Who: ");
        Serial.print(actor.name);
        Serial.print("Movie: ");
        Serial.println(clip.name);
    }
    for (int i = 0; i < clip.numFrames; i++) {

        int byteOffset= (i * FRAME_SIZE);

        /* inefficient since it allocates memory for data we already &have loadaed
        byte* frame = (byte*) malloc(sizeof(byte) * FRAME_SIZE);
        int byteOffset= (i * FRAME_SIZE);

        for (int i=0; i<FRAME_SIZE;i++){
            frame[i] = clip.frames[byteOffset+i];
        }
        */

        // loop all 8 available LiquidCrystal provided registers...coz we can.
        lcd.createChar(actor.actorCharNumber, &clip.frames[byteOffset]);

        showFrameFor(actor);

        if (DEBUG_ON) {
            Serial.print("Frame: ");
            Serial.println(i);
        }

        if (clip.makeSound) {

            tone(BUZZER_PIN, clip.melody[i%clip.melodySize], clip.melodySpeed);
            delay(clip.melodyDelay);
            noTone(BUZZER_PIN);
        }


        delay(clip.animationPause);
        if (clip.direction == 0 || i==0 ) continue;

        int posMultiplier = clip.direction; // * 1;
        int x = actor.pos_curr_x+posMultiplier;
        int y = actor.pos_curr_y;
        gotoPos(actor,x, y);
    }
}

