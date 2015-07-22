/*
 * Connections
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS to ground
 * LCD VDD to 5v
 * LCD V0 to wiper of 10K resistor (otherwires to 5v and ground)
 * LCD A to 5v
 * LCD K to ground
 */
#include <SPI.h>
#include <LiquidCrystal.h>
#include <string.h>

#define teamName1 "Red"
#define teamName2 "Blue"
#define sensorTeam1Pin 8
#define sensorTeam2Pin 9

#define SECS_PER_MIN  (60UL)
#define numberOfMinutes(_time_) ((_time_ / SECS_PER_MIN) % SECS_PER_MIN)
#define numberOfSeconds(_time_) (_time_ % SECS_PER_MIN)

int score1 = 0;
int score2 = 0;
int senseTeam1 = 0;
int senseTeam2 = 0;
int sensorTeam1State = 0;
int sensorTeam2State = 0;

// init with interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {

    pinMode(sensorTeam1Pin, INPUT);
    sensorTeam1State = digitalRead(sensorTeam1Pin);
    pinMode(sensorTeam2Pin, INPUT);
    sensorTeam2State = digitalRead(sensorTeam2Pin);

    // define columns and rows
    lcd.begin(16, 2);

    // display the team names
    lcd.print( teamName1 );
    lcd.setCursor(0, 1);
    lcd.print( teamName2 );
}

void loop() {

    int newTeam1State = digitalRead(sensorTeam1Pin);
    if( newTeam1State != sensorTeam1State ) {
        sensorTeam1State = newTeam1State;
        score1++; // @todo this needs to be debounced
    }

    int newTeam2State = digitalRead(sensorTeam2Pin);
    if( newTeam2State != sensorTeam2State ) {
        sensorTeam2State = newTeam2State;
        score2++; // @todo this needs to be debounced
    }

    updateScore();
    updateGameTime();

    delay(10);
}

void updateScore() {

    // print score 1
    lcd.setCursor(strlen(teamName1) + 1, 0);
    lcd.print( score1 );

    // print score 2
    lcd.setCursor(strlen(teamName2) + 1, 1);
    lcd.print( score2 );
}

void updateGameTime() {
    int gameTime = millis()/1000;
    lcd.setCursor(11, 0);
    lcd.print( time(gameTime) );
}

/**
 * Convert seconds into clock format
 * @param  val number of seconds
 * @return
 */
String time(int val){
    int minutes = numberOfMinutes(val);
    int seconds = numberOfSeconds(val);
    String secondsPrefix = String( seconds < 10 ? "0" : "" );
    String minutesPrefix = String( minutes < 10 ? "0" : "" );
    return minutesPrefix + minutes + ":" + secondsPrefix + String(seconds);
}
