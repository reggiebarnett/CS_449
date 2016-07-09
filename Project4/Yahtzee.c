//Reggie Barnett
//Project 4
//Yahtzee

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ones;
int twos;
int threes;
int fours;
int fives;
int sixes;
int bonus;
int toak;
int foak;
int small;
int large;
int full;
int yahtzee;
int chance;
int upper;
char eatnewline;
int dice[5];
int total_score = 0;

void roll_dice();
void placement();
void printscore();
int threeofakind();
int fourofakind();
int small_straight();
int large_straight();
int full_house();
int compare(const void *,const void *);
int rand_dice();

int main()
{
	int count = 0;
	//Done declaring variables in main	
	while(count<13)
	{
		roll_dice();
		qsort(dice,5,sizeof(int),compare);
		placement();
		printscore();
		count++;
	}
	total_score = total_score + bonus;
	printf("\n\nGame over!\n\nYour final score: %d\n\n",total_score);
	return 0;
}//End of main

//Rolls the dice
void roll_dice()
{
	int i;
	int j;
	int roll = 0;
	char reroll[11];
	int new_roll[5];
	//Done declaring variables in roll_dice
	//srand((unsigned int)time(NULL));

	roll=0;
	printf("\n\nYour roll:\n\n"); //Initial roll
	for(i=0;i<5;i++){

		dice[i] = rand_dice();
		printf("%d ", dice[i]);
	}
	roll++;
	while(roll<3) //Only allows 2 rerolls
	{
		j=0;
		printf("\n\nWhich dice to reroll? ");
		fgets(reroll,sizeof(reroll),stdin);

		if(reroll[0]== '0') //No reroll
			break;
		for(i=0;i<strlen(reroll)-1;i++){ //loop is converting from chars to ints
			if(reroll[i] != ' ')
			{
				new_roll[j] = reroll[i] - '0';
				j++;
			}
		}		
		//Rerolling the dice
		if(roll == 1)
			printf("\n\nYour second roll:\n\n");
		else
			printf("\n\nYour third roll:\n\n");
		j=0;
		for(i=0;i<5;i++){
			if(i+1 == new_roll[j]){
				dice[i] = rand_dice();
				j++;
			}
			printf("%d ", dice[i]);
		}
		//Resetting the new_roll array
		for(i=0;i<5;i++)
			new_roll[i] = 0;
		roll++;
	}
}//End of roll_dice

//Places dice in desired section and calculates score
void placement()
{
	int sel;
	int i;
	int round_score = 0;
	//Done declaring variables in placement
	while(sel != 1 && sel != 2)
	{
		printf("\n\nPlace dice into:\n1) Upper Section\n2) Lower Section\n\nSelection: ");
		scanf("%d", &sel);
	}
	if(sel == 1) //Placing into Upper Section
	{
		sel=0;
		while(sel != 1 && sel != 2 && sel != 3 && sel != 4 && sel != 5 && sel != 6)
		{
			printf("\n\nPlace dice into:\n1) Ones\n2) Twos\n3) Threes\n4) Fours\n5) Fives\n6) Sixes\n\nSelection: ");
			scanf("%d", &sel);
			scanf("%c",&eatnewline);
		}
		if(sel == 1) //Ones
		{
			for(i=0;i<5;i++){
				if(dice[i] == 1)
					round_score++;
			}
			ones = round_score;
		}
		else if(sel == 2) //Twos
		{
			for(i=0;i<5;i++){
				if(dice[i] == 2)
					round_score = round_score + 2;
			}
			twos = round_score;
		}
		else if(sel == 3) //Threes
		{
			for(i=0;i<5;i++){
				if(dice[i] == 3)
					round_score = round_score + 3;
			}
			threes = round_score;
		}
		else if(sel == 4) //Fours
		{
			for(i=0;i<5;i++){
				if(dice[i] == 4)
					round_score = round_score + 4;
			}
			fours= round_score;
		}
		else if(sel == 5) //Fives
		{
			for(i=0;i<5;i++){
				if(dice[i] == 5)
					round_score = round_score + 5;
			}
			fives = round_score;
		}
		else //Sixes
		{
			for(i=0;i<5;i++){
				if(dice[i] == 6)
					round_score = round_score + 6;
			}
			sixes = round_score;
		}
		upper = upper + round_score;
	}
	else //Placing into Lower Section
	{
		sel=0;
		while(sel != 1 && sel != 2 && sel != 3 && sel != 4 && sel != 5 && sel != 6 && sel != 7)
		{
			printf("\n\nPlace dice into:\n1) Three of a kind\n2) Four of a Kind\n3) Small Straight\n");
			printf("4) Large Straight\n5) Full House\n6) Yahtzee\n7) Chance\n\nSelection: ");
			scanf("%d", &sel);
			scanf("%c",&eatnewline);
		}
		if(sel == 1) //Three of a kind
		{
			round_score = threeofakind();
		}
		else if(sel == 2) //Four of a kind
		{
			round_score = fourofakind();
		}
		else if(sel == 3) //Small Straight
		{
			round_score = small_straight();
		}
		else if(sel == 4) //Large Straight
		{
			round_score = large_straight();
		}
		else if(sel == 5) //Full House
		{
			round_score = full_house();
		}
		else if(sel == 6) //Yahtzee
		{
			if(dice[0]==dice[1] && dice[1]==dice[2] && dice[2]==dice[3] && dice[3]==dice[4])
			{
				yahtzee = 50;
				round_score = yahtzee;
			}
		}
		else //Chance
		{
			chance = dice[0]+dice[1]+dice[2]+dice[3]+dice[4];
			round_score = chance;
		}
	}
	if(upper >= 63)
	{
		bonus = 35;
	}
	total_score = total_score + round_score;
	printf("\nYour score so far is: %d", total_score);
}//End of placement

//Prints out score
void printscore()
{
	printf("\n\nOnes: %d\t\t\tFours: %d",ones,fours);
	printf("\nTwos: %d\t\t\tFives: %d",twos,fives);
	printf("\nThrees: %d\t\tSixes: %d",threes,sixes);
	printf("\nUpper Section Bonus: %d",bonus);
	printf("\nThree of a Kind: %d\tFour of a Kind: %d",toak,foak);
	printf("\nSmall Straight: %d\tLarge Straight: %d",small,large);
	printf("\nFull House: %d\t\tYahtzee: %d",full,yahtzee);
	printf("\nChance: %d",chance);
}//End of print score

//Calculates score for Three of a Kind
int threeofakind()
{
	if(dice[0]==dice[1] && dice[1]==dice[2]) //Dice 1,2,3
	{
		toak = dice[0]+dice[1]+dice[2]+dice[3]+dice[4];
	}
	else if(dice[1]==dice[2] && dice[2]==dice[3]) //Dice 2,3,4
	{
		toak = dice[0]+dice[1]+dice[2]+dice[3]+dice[4];
	}
	else if(dice[2]==dice[3] && dice[3]==dice[4]) //Dice 3,4,5
	{
		toak = dice[0]+dice[1]+dice[2]+dice[3]+dice[4];
	}
	return toak;
}//End of three of a kind

//Calculates score for Four of a Kind
int fourofakind()
{
	if(dice[0]==dice[1] && dice[1]==dice[2] && dice[2]==dice[3]) //Dice 1,2,3,4,
	{
		foak = dice[0]+dice[1]+dice[2]+dice[3]+dice[4];
	}
	else if(dice[1]==dice[2] && dice[2]==dice[3] && dice[3]==dice[4]) //Dice 2,3,4,5
	{
		foak = dice[0]+dice[1]+dice[2]+dice[3]+dice[4];
	}
	return foak;
}//End of four of a kind

//Gives score for a small straight
int small_straight()
{
	if(dice[0]==1 && dice[1]==2 && dice[2]==3 && dice[3]==4) //1,2,3,4,4
	{
		small = 30;
	}
	else if(dice[1]==1 && dice[2]== 2 && dice[3]==3 && dice[4]==4) //1,1,2,3,4
	{
		small = 30;
	}
	else if(dice[0]==1 && dice[1]==2 && dice[2]== 2 && dice[3]==3 && dice[4]==4) //1,2,2,3,4
	{
		small = 30;
	}
	else if(dice[0]==1 && dice[1]==2 && dice[2]==3 && dice[3]==3 && dice[4]==4) //1,2,3,3,4
	{
		small = 30;
	}
	else if(dice[0]==2 && dice[1]==3 && dice[2]==4 && dice[3]==5) //2,3,4,5,5
	{
		small = 30;
	}
	else if(dice[1]==2 && dice[2]==3 && dice[3]==4 && dice[4]==5) //2,2,3,4,5
	{
		small = 30;
	}
	else if(dice[0]==2 && dice[1]==3 && dice[2]== 3 && dice[3]==4 && dice[4]==5) //2,3,3,4,5
	{
		small = 30;
	}
	else if(dice[0]==2 && dice[1]==3 && dice[2]==4 && dice[3]==4 && dice[4]==5) //2,3,4,4,5
	{
		small = 30;
	}
	else if(dice[0]==3 && dice[1]==4 && dice[2]==5 && dice[3]==6) //3,4,5,6,6
	{
		small = 30;
	}
	else if(dice[1]==3 && dice[2]==4 && dice[3]==5 && dice[4]==6) //3,3,4,5,6
	{
		small = 30;
	}
	else if(dice[0]==3 && dice[1]==4 && dice[2]== 4 && dice[3]==5 && dice[4]==6) //3,4,4,5,6
	{
		small = 30;
	}
	else if(dice[0]==3 && dice[1]==4 && dice[2]==5 && dice[3]==5 && dice[4]==6) //3,4,5,5,6
	{
		small = 30;
	}
	return small;
}//End of small straight

//Gives score for a large straight
int large_straight()
{
	if(dice[0]==1 && dice[1]==2 && dice[2]==3 && dice[3]==4 && dice[4]==5) //1,2,3,4,5
	{
		large = 40;
	}
	else if(dice[0]==2 && dice[1]==3 && dice[2]==4 && dice[3]==5 && dice[4]==6) //2,3,4,5,6
	{
		large = 40;
	}
	return large;
}//End of large straight

//Gives score for a full house
int full_house()
{
	if(dice[0]==dice[1] && dice[2]==dice[3] && dice[3]==dice[4]) //Dice 1,2--3,4,5
	{
		full = 25;
	}
	else if(dice[3]==dice[4] && dice[0]==dice[1] && dice[1]==dice[2]) //Dice 4,5--1,2,3
	{
		full = 25;
	}
	return full;
}//End of full house

//Compare for qsort
int compare (const void * a, const void * b) 
{
  return ( *(int*)a - *(int*)b );
}//End of compare

//Using the driver to give you random dice
int rand_dice(){
	int new_dice;
	FILE * opendice;
	opendice = fopen("/dev/dice","r");
	fread((void *)&new_dice,sizeof(int),1,opendice);
	fclose(opendice);
	return new_dice;
}


//End
