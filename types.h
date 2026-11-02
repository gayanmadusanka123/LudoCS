#ifndef TYPES_H
#define TYPES_H

#define NUM_PLAYERS 4
#define R_BASE -1
#define G_BASE -2
#define Y_BASE -3
#define B_BASE -4

extern char *colors[];

typedef struct {
    int piece[4];
    int starting;
    int index; 
    int count[4];
    int homePath[4];
    int clockwise[4];
} Red, Green, Yellow, Blue;

int value();
int clock1();
void end(void);
int newMystery();

void redPlayer(Red *red, Green *green, Yellow *yellow, Blue *blue, int* blueStarting);
void greenPlayer(Red *red, Green *green, Yellow *yellow, Blue *blue, int* blueStarting);
void yellowPlayer(Red *red, Green *green, Yellow *yellow, Blue *blue, int* blueStarting);
void bluePlayer(Red *red, Green *green, Yellow *yellow, Blue *blue, int* blueStarting);

#endif

