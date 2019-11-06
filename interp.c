/* Hunter Moore
 * 10/31/19
 * CPSC275 F
 * This program acts a compiler for a pseudo assembly language.
 * It recognizes a few commands and moves information to a set of registers and memory locations.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char* deblank(char* array);
void error();
void read(int data, char arg2[], int memory[], int registers[]);
void prints();

void main(void){
	char command[20];
	char arg1[20];
	char arg2[20];
	int registers[4] = {150, 150, 150, 150};
	int registerVal[4];
	int memory[8] = {150, 150, 150, 150, 150, 150, 150, 150};
	int zf = 8;
	int sf = 7;
	int of = 6;
	int i, length;
	scanf("%s", command);
		//scanf("%s", arg1);
//strcasecmp
//strtok
	while(command != "quit"){
	if(strcmp("read", command) == 0){
		scanf("%s", arg1);
		scanf("%s", arg2);
		read(atoi(arg1), arg2, memory, registers);
		}
	if(strcmp("prints", command) == 0){
		prints(registers, memory, of, sf, zf);
	}
	scanf("%s", command);
	}
}

void read(int data, char arg2[], int memory[], int registers[]){

	int i, j;
	if(strcmp(arg2, "m0") == 0){
		memory[0] = data;
	}
	if(strcmp(arg2, "m1") == 0){
		memory[1] = data;
	}
	if(strcmp(arg2, "m2") == 0){
		memory[2] = data;
	}
	if(strcmp(arg2, "m3") == 0){
		memory[3] = data;
	}
	if(strcmp(arg2, "m4") == 0){
		memory[4] = data;
	}
	if(strcmp(arg2, "m5") == 0){
		memory[5] = data;
	}
	if(strcmp(arg2, "m6") == 0){
		memory[6] = data;
	}
	if(strcmp(arg2, "m7") == 0){
		memory[7] = data;
	}
	if(strcmp(arg2, "r0") == 0){
		registers[0] = data;
	}
	if(strcmp(arg2, "r1") == 0){
		registers[1] = data;
	}
	if(strcmp(arg2, "r2") == 0){
		registers[2] = data;
	}
	if(strcmp(arg2, "r3") == 0){
		registers[3] = data;
	}
	for(i = 0; i < 4; i++){
		if(registers[i] > 128){
			error();
		}
		else{
			printf("%d\t", registers[i]);
		}
	}
	for(j = 0; j < 8; j++){
		if(memory[j] > 128){
			printf("???\t");
		}
		else{
			printf("%d\t", memory[j]);
		}
	}
	/*for(i = 0; i < 8; i++){
		if(array[i] > 128){
			printf("???\t");
		}
		else{
			printf("%d\t", array[i]);
		}
	}*/
}

void prints(char registers[], char memory[], int of, int sf, int zf){
	int i, j;
	for(i = 0; i < 4; i++){
		if(registers[i] > 128){
			printf("???\t");
		}
		else{
			printf("%d\t", registers[i]);
		}
	}
	for(j = 0; j < 8; j++){
		if(memory[j] > 128){
			printf("???\t");
		}
		else{
			printf("%d\t", memory[j]);
		}
	}
	printf("%d\t", of);
printf("%d\t", sf);
printf("%d\t", zf);
}

char* deblank(char* array){
	int i, j;
	char *output = array;
	for(i = 0, j = 0; i<MAX; i++, j++){
		if(array[i] != ' ')
			output[j]=array[i];
		else
			j--;
	}
	output[j]=0;
	return output;
}

void error(){
	printf("???");
}


