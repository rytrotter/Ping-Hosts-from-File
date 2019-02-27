#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED "\033[0;31m"
#define GREEN "\033[3;32m"
#define RESET "\033[0;0m"


int countLines(FILE *file);

int main() {
	system("clear");
	FILE *hostFile;
	int numOfLines, index;
	int numUp = 0;
	int numDown = 0;

	//Attempt to open file and check for errors
	hostFile = fopen("PATH_TO_HOST_FILE", "r");
	if(hostFile == NULL) {
		perror("Error opening file.");
		return -1;
	}
	
	numOfLines = countLines(hostFile);
	char pingList[numOfLines][38];
	char commandList[numOfLines][100];
	char garbage[255];	
	rewind(hostFile); //Resets pointer to top of file to get hostnames
	
	while(!feof(hostFile)) {
		for(index = 0; index < numOfLines; index++) {
			fgets(pingList[index], 38, hostFile);
			fgets(garbage, 255, hostFile);
		}
	}
	
	for(index = 0; index < numOfLines; index++) {
		char command[100] = "ping -w 1 ";
		strcat(command, pingList[index]);
		strcat(command, " > /dev/null ");
		strcat(commandList[index], command);
		memset(command, 0, sizeof(command)); //Erase contents of command
	}
	
	for(index = 0; index < numOfLines; index++) {
		if(system(commandList[index]) == 0) {
			numUp++;
			printf("%s%s is up.\n", GREEN, pingList[index]);
		}
		else {
			numDown++;
			printf("%s%s is down.\n", RED, pingList[index]);
		}
	}	
		
	printf("%s\n\nYou have %d hosts up and %d hosts down!\nCongrats!\n\n", RESET, numUp, numDown);

	fclose(hostFile);
	return 0;
}

int countLines(FILE *file) {
	int amntLines = 0;
	char character;
	while(!feof(file)) {
		character = fgetc(file);
		if(character == '\n') {
			amntLines++;
		}
	}
	return amntLines;
}
