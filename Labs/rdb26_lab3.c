#include <stdio.h>
#include <stdlib.h>

struct Node{
	int grade;
	struct Node *next;
};

int main()
{
	int stop = 0;
	struct Node *grade_list = NULL;
	struct Node *grade_ptr;
	double avg = 0;
	int count = 0;

	grade_list = malloc(sizeof(struct Node));
	grade_ptr = grade_list;
	grade_list->next = NULL;

	/*Storing into the linked list*/
	while(!stop)
	{
		printf("Enter grade: ");
		scanf("%d", &grade_ptr->grade);
		if(grade_ptr->grade == -1)
		{
			stop = 1;
		}
		else
		{
			grade_ptr->next = malloc(sizeof(struct Node));
			grade_ptr = grade_ptr->next;
		}
	}
	grade_ptr->next = NULL;

	/*Getting the average*/
	while(grade_list->next != NULL )
	{
		avg += grade_list->grade;
		count++;
		grade_list = grade_list->next;
	}

	avg = avg/count; 
	printf("The average of the grades is %.1f\n", avg);

	return 0;
}