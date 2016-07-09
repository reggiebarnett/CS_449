/*Project 1 RPS
Reggie Barnett
rdb26@pitt.edu*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


int main()
{
	char playgame[10];
	int user_wins = 0;
	int comp_wins = 0;
	char user_choice[10];
	char comp_choice[10];
	int comp_num = 0;
	/*Done declaring variables*/

	srand((unsigned int)time(NULL));
	
	printf("Welcome to Rock, Paper, Scissors\n\nWould you like to play? ");
	fgets(playgame, sizeof(playgame), stdin);
	while(strcmp(playgame,"yes\n") == 0)
	{
		user_wins = 0; /*Reset wins before each game*/
		comp_wins = 0;
		while(user_wins<3 && comp_wins<3)
		{
			printf("\nWhat is your choice? ");
			fgets(user_choice, 10, stdin);
			comp_num = rand()%3+1;
			if(comp_num == 1)
				strcpy(comp_choice,"rock\n");
			else if(comp_num == 2)
				strcpy(comp_choice,"paper\n");
			else
				strcpy(comp_choice,"scissors\n");
			printf("The computer chooses: %s", comp_choice); 

			if(strcmp(user_choice,comp_choice)==0)
				printf("You tied!\n\nThe score is now You: %d Comp: %d", user_wins,comp_wins);
			else if(strcmp(user_choice,"rock\n") == 0 && strcmp(comp_choice,"paper\n") == 0)
			{
				comp_wins++;
				printf("You lost!\n\nThe score is now You: %d Comp: %d", user_wins,comp_wins);
			}
			else if(strcmp(user_choice,"rock\n") == 0 && strcmp(comp_choice,"scissors\n") == 0)
			{
				user_wins++;
				printf("You won!\n\nThe score is now You: %d Comp: %d", user_wins,comp_wins);
			}
			else if(strcmp(user_choice,"paper\n") == 0 && strcmp(comp_choice,"rock\n") == 0)
			{
				user_wins++;
				printf("You won!\n\nThe score is now You: %d Comp: %d", user_wins,comp_wins);
			}
			else if(strcmp(user_choice,"paper\n") == 0 && strcmp(comp_choice,"scissors\n") == 0)
			{
				comp_wins++;
				printf("You lost!\n\nThe score is now You: %d Comp: %d", user_wins,comp_wins);
			}
			else if(strcmp(user_choice,"scissors\n") == 0 && strcmp(comp_choice,"rock\n") == 0)
			{
				comp_wins++;
				printf("You lost!\n\nThe score is now You: %d Comp: %d", user_wins,comp_wins);
			}
			else if(strcmp(user_choice,"scissors\n") == 0 && strcmp(comp_choice,"paper\n") == 0)
			{
				user_wins++;
				printf("You won!\n\nThe score is now You: %d Comp: %d", user_wins,comp_wins);
			}
		}
		if(user_wins==3)
			printf("\nYou won Rock Paper Scissors!");
		else
			printf("\nThe computer won Rock Paper Scissors!");
		printf("\nWould you like to play again? "); /*asks user to play again*/
		fgets(playgame, sizeof(playgame), stdin);
	}
	printf("\nGoodbye");
	return 0;
}