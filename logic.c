#include <stdio.h>
#include <stdlib.h>
#include "types.h"

char *colors[] = {"red", "green", "yellow", "blue"};

int value(){
	return (rand() % 6) + 1;
}

//function for choose clockwise or counter clockwise 
int clock1(){
	return (rand() % 2) + 1;
}

int newMystery(){
	return (rand() % 52) + 0;
}

//---------red player function this is included red player's behavior-----------------------
void redPlayer(Red *red, Green *green, Yellow *yellow, Blue *blue, int* blueStarting){
	if(!red->starting){
		int r = value();
		printf("Color %s rolls %d\n", colors[0], r);
		int ht = clock1();
		if(r == 6 && ht == 1){
			red->starting = 1;
			red->clockwise[red->index-1] = 1;
			red->piece[red->index-1] = 28;
			printf("Color %s player moves piece %d to the starting point and receives Head so it's going clockwise\n", colors[0], red->index);
		}else if(r == 6 && ht == 2){
			red->starting = 1;
			red->clockwise[red->index-1] = 2;
			red->piece[red->index-1] = 28;
			printf("Color %s player moves piece %d to the starting point and receives Tail so it's going counter clockwise\n", colors[0], red->index);
		} 
	}else{
		int rr = value();
		red->count[red->index-1] += rr;
		printf("Color %s rolls %d\n", colors[0], rr);	
		if((red->count[red->index-1] >= 50 && red->clockwise[red->index-1] == 1 )|| (red->count[red->index-1] >= 54 && red->clockwise[red->index-1] == 2)){
			red->piece[red->index-1] = 100;
			if(red->homePath[red->index-1] >= 0){
				if(rr == 6 - red->homePath[red->index-1]){
					red->homePath[red->index-1] += rr;
					printf("Color %s player moves piece %d to %s homepath %d\n", colors[0], red->index, colors[0], red->homePath[red->index-1]);
				}
			}else{
				if(red->clockwise[red->index-1] == 1){
					red->homePath[red->index-1] = red->count[red->index-1] - 50;
				}else if(red->clockwise[red->index-1] == 2){
					red->homePath[red->index-1] = red->count[red->index-1] - 54;
				}
				printf("Color %s player moves piece %d to %s homepath %d\n", colors[0], red->index, colors[0], red->homePath[red->index-1]);
			}
		}else{
			if(red->clockwise[red->index-1] == 1){
				red->piece[red->index-1] = (red->piece[red->index-1] + rr) % 52;
				printf("Color %s player moves piece %d to %d in clockwise\n", colors[0], red->index, red->piece[red->index-1]);
			}else if(red->clockwise[red->index-1] == 2){
				if(red->piece[red->index-1] < rr){
					red->piece[red->index-1] = red->piece[red->index-1] - rr + 52;
				}else{
					red->piece[red->index-1] = red->piece[red->index-1] - rr;
				}
				printf("Color %s player moves piece %d to %d in counter clockwise\n", colors[0], red->index, red->piece[red->index-1]);
			}
			
		}
		//capturePieces(&red, &green, &yellow, &blue);
	 
			for(int i = 0; i < NUM_PLAYERS; i++){
				for(int j = 0; j < NUM_PLAYERS; j++){
					if(red->piece[i] == green->piece[j]){
						printf("Color %s piece %d captures Color %s piece %d and return it to the base\n", colors[0], i+1, colors[1], j+1);
						green->piece[j] = -2;
						green->starting = 0; 
						green->count[green->index-1] = 0;
						redPlayer(red,green,yellow,blue,blueStarting);
					}else if(red->piece[i] == yellow->piece[j]){
						printf("Color %s piece %d captures Color %s piece %d and return it to the base\n", colors[0], i+1, colors[2], j+1);
						yellow->piece[j] = -3; 
						yellow->starting = 0;
						yellow->count[yellow->index-1] = 0;
						redPlayer(red,green,yellow,blue,blueStarting);
					}else if(red->piece[i] == blue->piece[j]){
						printf("Color %s piece %d captures Color %s piece %d and return it to the base\n", colors[0], i+1, colors[3], j+1);
						blue->piece[j] = -4;
						blueStarting[j] = 0;
						blue->count[blue->index-1] = 0; 
						blue->index++;
						redPlayer(red,green,yellow,blue,blueStarting);
					}
				}
			}

		if(red->homePath[3] == 6){
			printf("\nred wins!!\n");
			end();
		}

		if(red->homePath[red->index-1] == 6){
			red->index++;
			red->count[red->index-1] = 0;
			red->starting = 0;
		}
		if(rr == 6)redPlayer(red,green,yellow,blue,blueStarting);
	}
}

//---------------green player behavior is the same as red-------------------------------
void greenPlayer(Red *red, Green *green, Yellow *yellow, Blue *blue, int* blueStarting){
	if(!green->starting){
		int g = value();
		printf("Color %s rolls %d\n", colors[1], g);
		int ht = clock1();
		if(g == 6 && ht == 1){
			green->starting = 1;
			green->clockwise[green->index-1] = 1;
			green->piece[green->index-1] = 41;
			printf("Color %s player moves piece %d to the starting point and receives Head so it's going clockwise\n", colors[1], green->index);
		}else if(g == 6 && ht == 2){
			green->starting = 1;
			green->clockwise[green->index-1] = 2;
			green->piece[green->index-1] = 41;
			printf("Color %s player moves piece %d to the starting point and receives Tail so it's going counter clockwise\n", colors[1], green->index);
		}
	}else{
		int gg = value();
		green->count[green->index-1] += gg;
		printf("Color %s rolls %d\n", colors[1], gg);
		
		if((green->count[green->index-1] >= 50 && green->clockwise[green->index-1] == 1 )|| (green->count[green->index-1] >= 54 && green->clockwise[green->index-1] == 2 ) ){
			green->piece[green->index-1] = 200;
			if(green->homePath[green->index-1] >= 0){
				if(gg == 6 - green->homePath[green->index-1]){
					green->homePath[green->index-1] += gg;
					printf("Color %s player moves piece %d to %s homepath %d\n", colors[1], green->index, colors[1], green->homePath[green->index-1]);
				}
			}else{
				if(green->clockwise[green->index-1] == 1){
					green->homePath[green->index-1] = green->count[green->index-1] - 50;
				}else if(green->clockwise[green->index-1] == 2){
					green->homePath[green->index-1] = green->count[green->index-1] - 54;
				}
				printf("Color %s player moves piece %d to %s homepath %d\n", colors[1], green->index, colors[1], green->homePath[green->index-1]);
			}
		}else{
			if(green->clockwise[green->index-1] == 1){
				green->piece[green->index-1] = (green->piece[green->index-1] + gg) % 52;
				printf("Color %s player moves piece %d to %d in clockwise\n", colors[1], green->index, green->piece[green->index-1]);
			}else if(green->clockwise[green->index-1] == 2){
				if(green->piece[green->index-1] < gg){
					green->piece[green->index-1] = green->piece[green->index-1] -gg + 52;
				}else{
					green->piece[green->index-1] = green->piece[green->index-1] - gg;
				}
				printf("Color %s player moves piece %d to %d in counter clockwise\n", colors[1], green->index, green->piece[green->index-1]);
			}
		}		
		
		//capturePieces(&red, &green, &yellow, &blue);
		for(int i = 0; i < NUM_PLAYERS; i++){
			for(int j = 0; j < NUM_PLAYERS; j++){
				if(green->piece[i] == red->piece[j]){
					printf("Color %s piece %d captures Color %s piece %d and return it to the base\n", colors[1], i+1, colors[0], j+1);
					red->piece[j] = -1;
					red->starting = 0; 
					red->count[red->index-1] = 0;
					greenPlayer(red,green,yellow,blue,blueStarting);
				}else if(green->piece[i] == yellow->piece[j]){
					printf("Color %s piece %d captures Color %s piece %d and return it to the base\n", colors[1], i+1, colors[2], j+1);
					yellow->piece[j] = -3; 
					yellow->starting = 0;
					yellow->count[yellow->index-1] = 0;
					greenPlayer(red,green,yellow,blue,blueStarting);
				}else if(green->piece[i] == blue->piece[j]){
					printf("Color %s piece %d captures Color %s piece %d and return it to the base\n", colors[1], i+1, colors[3], j+1);
					blue->piece[j] = -4;
					blueStarting[j] = 0;
					blue->count[blue->index-1] = 0; 
					blue->index++;
					greenPlayer(red,green,yellow,blue,blueStarting);
				}
			}
		}
		
		if(green->homePath[3] == 6){
			printf("\ngreen wins!!\n");
			end();
		}
		
		if(green->homePath[green->index-1] == 6){
			green->index++;
			green->count[green->index-1] = 0;
			green->starting = 0;
		}
		if(gg == 6)greenPlayer(red,green,yellow,blue,blueStarting);
	}
}

//-------------------------yellow player behavior is same as the red and green-----------------------
void yellowPlayer(Red *red, Green *green, Yellow *yellow, Blue *blue, int* blueStarting){
	if(!yellow->starting){
		int y = value();
		printf("Color %s rolls %d\n", colors[2], y);
		int ht = clock1();
		if(y == 6 && ht == 1){
			yellow->starting = 1;
			yellow->clockwise[yellow->index-1] = 1;
			yellow->piece[yellow->index-1] = 2;
			printf("Color %s player moves piece %d to the starting point and receives Head so it's going clockwise\n", colors[2], yellow->index);
		}else if(y == 6 && ht == 2){
			yellow->starting = 1;
			yellow->clockwise[yellow->index-1] = 2;
			yellow->piece[yellow->index-1] = 2;
			printf("Color %s player moves piece %d to the starting point and receives Tail so it's going counter clockwise\n", colors[2], yellow->index);
		}
	}else{
		int yy = value();
		yellow->count[yellow->index-1] += yy;
		printf("Color %s rolls %d\n", colors[2], yy);	
		
		if((yellow->count[yellow->index-1] >= 50 && yellow->clockwise[yellow->index-1] == 1) || (yellow->count[yellow->index-1] >= 54 && yellow->clockwise[yellow->index-1] == 2) ){
			yellow->piece[yellow->index-1] = 300;
			if(yellow->homePath[yellow->index-1] >= 0){
				if(yy == 6 - yellow->homePath[yellow->index-1]){
					yellow->homePath[yellow->index-1] += yy;
					printf("Color %s player moves piece %d to %s homepath %d\n", colors[2], yellow->index, colors[2], yellow->homePath[yellow->index-1]);
				}
			}else{
				if(yellow->clockwise[yellow->index-1] == 1){
					yellow->homePath[yellow->index-1] = yellow->count[yellow->index-1] - 50;
				}else if(yellow->clockwise[yellow->index-1] == 2){
					yellow->homePath[yellow->index-1] = yellow->count[yellow->index-1] - 54;
				}
				printf("Color %s player moves piece %d to %s homepath %d\n", colors[2], yellow->index, colors[2], yellow->homePath[yellow->index-1]);
			}
		}else{
			if(yellow->clockwise[yellow->index-1] == 1){
				yellow->piece[yellow->index-1] = (yellow->piece[yellow->index-1] + yy) % 52;
				printf("Color %s player moves piece %d to %d in clockwise\n", colors[2], yellow->index, yellow->piece[yellow->index-1]);
			}else if(yellow->clockwise[yellow->index-1] == 2){
				if(yellow->piece[yellow->index-1] < yy){
					yellow->piece[yellow->index-1] = yellow->piece[yellow->index-1] - yy + 52; 
				}else{
					yellow->piece[yellow->index-1] = yellow->piece[yellow->index-1] - yy;
				}
				printf("Color %s player moves piece %d to %d in counter clockwise\n", colors[2], yellow->index, yellow->piece[yellow->index-1]);
			}
		}
		
		//capturePieces(&red, &green, &yellow, &blue);
		for(int i = 0; i < NUM_PLAYERS; i++){
			for(int j = 0; j < NUM_PLAYERS; j++){
				if(yellow->piece[i] == red->piece[j]){
					printf("Color %s piece %d captures Color %s piece %d and return it to the base\n", colors[2], i+1, colors[0], j+1);
					red->piece[j] = -1;
					red->starting = 0; 
					red->count[red->index-1] = 0;
					yellowPlayer(red,green,yellow,blue,blueStarting);
				}else if(yellow->piece[i] == green->piece[j]){
					printf("Color %s piece %d captures Color %s piece %d and return it to the base\n", colors[2], i+1, colors[1], j+1);
					green->piece[j] = -2; 
					green->starting = 0;
					green->count[green->index-1] = 0;
					yellowPlayer(red,green,yellow,blue,blueStarting);
				}else if(yellow->piece[i] == blue->piece[j]){
					printf("Color %s piece %d captures Color %s piece %d and return it to the base\n", colors[2], i+1, colors[3], j+1);
					blue->piece[j] = -4;
					blueStarting[j] = 0;
					blue->count[blue->index-1] = 0; 
					blue->index++;
					yellowPlayer(red,green,yellow,blue,blueStarting);
				}
			}
		}


		if(yellow->homePath[3] == 6){
			printf("\nyellow wins!!\n");
			end();
		}
		
		if(yellow->homePath[yellow->index-1] == 6){
			yellow->index++;
			yellow->count[yellow->index-1] = 0;
			yellow->starting = 0;
		}
		if(yy == 6)yellowPlayer(red,green,yellow,blue,blueStarting);
	}
}

//------------------------blue player function-------------------------------------
void bluePlayer(Red *red, Green *green, Yellow *yellow, Blue *blue, int* blueStarting){
	if(blue->index == NUM_PLAYERS+1)blue->index = 1;
	if(!blueStarting[blue->index-1]){
		int b = value();
		printf("Color %s rolls %d\n", colors[3], b);
		int ht = clock1();
		if(b == 6 && ht == 1){
			blueStarting[blue->index-1] = 1;
			blue->clockwise[blue->index-1] = 1;
			blue->piece[blue->index-1] = 15;
			printf("Color %s player moves piece %d to the starting point and receives Heads so it's going clockwise\n", colors[3], blue->index);
			
		}else if(b == 6 && ht == 2){
			blueStarting[blue->index-1] = 1;
			blue->clockwise[blue->index-1] = 2;
			blue->piece[blue->index-1] = 15;
			printf("Color %s player moves piece %d to the starting point and receives Tail so it's going counter clockwise\n", colors[3], blue->index);
			
		}
	}else{
		int bb = value();
		blue->count[blue->index-1] += bb;
		printf("Color %s rolls %d\n", colors[3], bb);
				
		if((blue->count[blue->index-1] >= 50 && blue->clockwise[blue->index-1] == 1) ||  (blue->count[blue->index-1] >= 54 && blue->clockwise[blue->index-1] == 2)){
			blue->piece[blue->index-1] = 400;
			if(blue->homePath[blue->index-1] >= 0){
				if(bb == 6 - blue->homePath[blue->index-1]){
					blue->homePath[blue->index-1] += bb;
					printf("Color %s player moves piece %d to %s homepath %d\n", colors[3], blue->index, colors[3], blue->homePath[blue->index-1]);
				}
			}else{
				if(blue->clockwise[blue->index-1] == 1){
					blue->homePath[blue->index-1] = blue->count[blue->index-1] - 50; 
				}else if(blue->clockwise[blue->index-1] == 2){
					blue->homePath[blue->index-1] = blue->count[blue->index-1] - 54;
				}
				printf("Color %s player moves piece %d to %s homepath %d\n", colors[3], blue->index, colors[3], blue->homePath[blue->index-1]);
			}
		}else{
			if(blue->clockwise[blue->index-1] == 1){
				blue->piece[blue->index-1] = (blue->piece[blue->index-1] + bb) % 52;
				printf("Color %s player moves piece %d to %d in clockwise\n", colors[3], blue->index, blue->piece[blue->index-1]);
			}else if(blue->clockwise[blue->index-1] == 2){
				if(blue->piece[blue->index-1] < bb){
					blue->piece[blue->index-1] = blue->piece[blue->index-1] - bb + 52;
				}else{
					blue->piece[blue->index-1] = blue->piece[blue->index-1] - bb;
				}
				printf("Color %s player moves piece %d to %d in counter clockwise\n", colors[3], blue->index, blue->piece[blue->index-1]);
			}
			
		}
		
		
		//capturePieces(&red, &green, &yellow, &blue);
		
		for(int i = 0; i < NUM_PLAYERS; i++){
			for(int j = 0; j < NUM_PLAYERS; j++){
				if(blue->piece[i] == red->piece[j]){
					printf("Color %s piece %d captures Color %s piece %d and return it to the base\n", colors[3], i+1, colors[0], j+1);
					red->piece[j] = -1;
					red->starting = 0; 
					red->count[red->index-1] = 0;
					bluePlayer(red,green,yellow,blue,blueStarting);
				}else if(blue->piece[i] == green->piece[j]){
					printf("Color %s piece %d captures Color %s piece %d and return it to the base\n", colors[3], i+1, colors[1], j+1);
					green->piece[j] = -2; 
					green->starting = 0;
					green->count[green->index-1] = 0;
					bluePlayer(red,green,yellow,blue,blueStarting);
				}else if(blue->piece[i] == yellow->piece[j]){
					printf("Color %s piece %d captures Color %s piece %d and return it to the base\n", colors[3], i+1, colors[2], j+1);
					yellow->piece[j] = -3;
					yellow->starting = 0;
					yellow->count[yellow->index-1] = 0; 
					bluePlayer(red,green,yellow,blue,blueStarting);
				}
			}
		}

		if(blue->homePath[0] == 6 && blue->homePath[1] == 6 && blue->homePath[2] == 6 && blue->homePath[3] == 6){
			printf("\nblue wins!!\n");
			end();
		}
		
		if(bb == 6){
			bluePlayer(red,green,yellow,blue,blueStarting);
		}
	}
}



void end(){
	printf("Thank you!!!!\n");
	exit(0);
}
