/*Project 2 Mystrings
Reggie Barnett
rdb26@pitt.edu*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE *filename;
	char ascii_string[100];
	char read_byte;
	int str_length=0; 
	int count;

	filename = fopen(argv[1], "rb");

	while(!feof(filename))
	{
		fread(&read_byte,sizeof(char),1,filename);
		/*Checking for printable characters*/
		if(read_byte >= 0x20 && read_byte <= 0x7E)
		{
			ascii_string[str_length] = read_byte;
			str_length++;
		}
		else /*falls outside of range of printable chars*/
		{
			/*Prints the string if it is longer than 4*/
			if(str_length >= 4)
			{
				printf("%s\n", ascii_string);
			}
			/*Resetting the string*/
			for(count = 0;count<str_length;count++)
			{
				ascii_string[count] = 0;
			}
			str_length = 0;
		}
	}
	return 0;
}