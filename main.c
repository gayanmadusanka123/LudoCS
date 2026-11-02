#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "types.h"
#include "logic.c"

int mysteryCell;
int main(){
	srand(time(NULL));
	
	printf("The Red player has four(04) pieces named R1, R2, R3, R4.\n");
	printf("The Yellow player has four(04) pieces named Y1, Y2, Y3, Y4.\n");
	printf("The Green player has four(04) pieces named G1, G2, G3, G4.\n");
	printf("The Blue player has four(04) pieces named B1, B2, B3, B4.\n\n");
	
	int values[NUM_PLAYERS]; //what are values players are rolling to check the order of playing
	char order[NUM_PLAYERS][7]; // After order players store in this array
	int maxIndex;
	
	for (int i = 0; i < NUM_PLAYERS; i++){
		values[i] = (rand() % 6) + 1;
		printf("%s rolls %d\n",colors[i],values[i]);
	}
	 //check who has the highest value and setup the oreder of playing
	if(values[3] >= values[0] && values[3] >= values[1] && values[3] >= values[2]){
		maxIndex = 3;
	}
	if(values[2] >= values[0] && values[2] >= values[1] && values[2] >= values[3]){ 
		maxIndex = 2;
	}
	if(values[1] >= values[0] && values[1] >= values[2] && values[1] >= values[3]){
		maxIndex = 1;
	}
	if(values[0] >= values[1] && values[0] >= values[2] && values[0] >= values[3]){
		maxIndex = 0;
	}
	
	strcpy(order[0], colors[maxIndex]);
		
	for (int i = 1; i < NUM_PLAYERS; i++){
		strcpy(order[i], colors[(maxIndex + i) % 4]);
	}
			
	printf("\n%s player has the highest roll and will begin the game\n", order[0]);
	printf("The order of a single round is ");
	for (int i = 0; i < 4; i++){
		printf("%s, ", order[i]);
	}		
	printf("\n\n");

	//////////////////////////////////////////////////////////////////////////////////////
	static Red red = {{R_BASE,R_BASE,R_BASE,R_BASE}, 0, 1, {0,0,0,0}, {-1,-1,-1,-1},{0,0,0,0}};
	static Green green = {{G_BASE,G_BASE,G_BASE,G_BASE}, 0, 1, {0,0,0,0}, {-2,-2,-2,-2},{0,0,0,0}};
	static Yellow yellow = {{Y_BASE,Y_BASE,Y_BASE,Y_BASE}, 0, 1, {0,0,0,0},{-3,-3,-3,-3},{0,0,0,0}};
	static Blue blue = {{B_BASE,B_BASE,B_BASE,B_BASE}, 0, 1, {0,0,0,0},{-4,-4,-4,-4},{0,0,0,0}};
	static int blueStarting[] = {0,0,0,0};
	int mysteryBegin = 0;
	int newMysteryBegin = 1;
	int count;

	int round;
	for (round = 1; ; round++){
		printf("Round %d\n-----------------\n\n",round);
		if(strcmp(order[0], "red") == 0){
			redPlayer(&red,&green,&yellow,&blue,blueStarting);
			greenPlayer(&red,&green,&yellow,&blue,blueStarting);
			yellowPlayer(&red,&green,&yellow,&blue,blueStarting);
			bluePlayer(&red,&green,&yellow,&blue,blueStarting);
		}
		if(strcmp(order[0], "green") == 0){
			greenPlayer(&red,&green,&yellow,&blue,blueStarting);
			yellowPlayer(&red,&green,&yellow,&blue,blueStarting);
			bluePlayer(&red,&green,&yellow,&blue,blueStarting);
			redPlayer(&red,&green,&yellow,&blue,blueStarting);
		}
		if(strcmp(order[0], "yellow") == 0){
			yellowPlayer(&red,&green,&yellow,&blue,blueStarting);
			bluePlayer(&red,&green,&yellow,&blue,blueStarting);
			redPlayer(&red,&green,&yellow,&blue,blueStarting);
			greenPlayer(&red,&green,&yellow,&blue,blueStarting);
		}
		if(strcmp(order[0], "blue") == 0){
			bluePlayer(&red,&green,&yellow,&blue,blueStarting);
			redPlayer(&red,&green,&yellow,&blue,blueStarting);
			greenPlayer(&red,&green,&yellow,&blue,blueStarting);
			yellowPlayer(&red,&green,&yellow,&blue,blueStarting);
		}
		
		printf("\n");
		
		//-------------------------Location of pieces-------------------------------------
		printf("=====================================\n");
		printf("Location of pieces Color %s\n", colors[0]);
		printf("=====================================\n");
		for(int i = 0; i < NUM_PLAYERS; i++){
			if(red.piece[i] == R_BASE){
				printf("piece %d -> Base\n",i+1);
			}else if(red.homePath[i] >= 0 && red.homePath[i] < 6){
				printf("piece %d -> home path %d\n",i+1,red.homePath[i]);
			}else if(red.homePath[i] == 6){
				printf("piece %d -> Home\n",i+1);
			}else{
				printf("piece %d -> %d\n",i+1,red.piece[i]);
			}
		}
		printf("\n");
		
		printf("=====================================\n");
		printf("Location of pieces Color %s\n", colors[1]);
		printf("=====================================\n");
		for(int i = 0; i < NUM_PLAYERS; i++){
			if(green.piece[i] == G_BASE){
				printf("piece %d -> Base\n",i+1);
			}else if(green.homePath[i] >= 0 && green.homePath[i] < 6){
				printf("piece %d -> home path %d\n",i+1,green.homePath[i]);
			}else if(green.homePath[i] == 6){
				printf("piece %d -> Home\n",i+1);
			}else{
				printf("piece %d -> %d\n",i+1,green.piece[i]);
			}
		}
		printf("\n");
		
		printf("=====================================\n");
		printf("Location of pieces Color %s\n", colors[2]);
		printf("=====================================\n");
		for(int i = 0; i < NUM_PLAYERS; i++){
			if(yellow.piece[i] == Y_BASE){
				printf("piece %d -> Base\n",i+1);
			}else if(yellow.homePath[i] >= 0 && yellow.homePath[i] < 6){
				printf("piece %d -> home path %d\n",i+1,yellow.homePath[i]);
			}else if(yellow.homePath[i] == 6){
				printf("piece %d -> Home\n",i+1);
			}else{
				printf("piece %d -> %d\n",i+1,yellow.piece[i]);
			}
		}
		printf("\n");
		
		printf("=====================================\n");
		printf("Location of pieces Color %s\n", colors[3]);
		printf("=====================================\n");
		for(int i = 0; i < NUM_PLAYERS; i++){
			if(blue.piece[i] == B_BASE){
				printf("piece %d -> Base\n",i+1);
			}else if(blue.homePath[i] >= 0 && blue.homePath[i] < 6){
				printf("piece %d -> homepath %d\n",i+1,blue.homePath[i]);
			}else if(blue.homePath[i] == 6){
				printf("piece %d -> Home\n",i+1);
			}else{
				printf("piece %d -> %d\n",i+1,blue.piece[i]);
			}
		}
		printf("\n");
		
		//=============================Mystery Cell=================================
		int tempRound;
		int temp;
		
		if(!mysteryBegin){
			for(int i = 0; i < NUM_PLAYERS ; i++){
				if(red.piece[i] > 0 || green.piece[i] > 0 || yellow.piece[i] > 0 || blue.piece[i] > 0){
					mysteryBegin = 1;
					newMysteryBegin = 0;
					tempRound = round-1;
					temp = tempRound;
					count = 4;
				}
			}
		}
		

		if(!newMysteryBegin){
			mysteryCell = newMystery();
			newMysteryBegin = 1;
			printf("The Mystery cell is at L%d and will be that for next %d rounds\n\n",mysteryCell,count);
		}
		if(mysteryBegin == 1){
			printf("Mystery cell is at L%d \n\n", mysteryCell);
		}
		temp++;
		count--;
		if(temp == tempRound+5){
			temp = tempRound;
		}
		
		if(count == 0){
			count = 4;		
		}
		if(count == 4) newMysteryBegin = 0;
		
		//blue is going cyclic manner. so blue player has to change it's own pieces one by one---------------
		blue.index++;
		if(blue.index == NUM_PLAYERS+1)blue.index = 1;//if index become 5 and there is no such a piece like that so piece is need to be again 1

	}
	
	return 0;
}
