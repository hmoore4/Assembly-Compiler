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

//FUNCTION COMMENTS
void error();
void read(int data, char arg2[], int memory[], int registers[]);
void prints(int registers[], int memory[], int of, int sf, int zf);
void write(char arg1[], int registers[], int memory[]);

void main(void){
	char command[20];
	char arg1[20];
	char arg2[20];
	int registers[4] = {150, 150, 150, 150};
	int memory[8] = {150, 150, 150, 150, 150, 150, 150, 150};
	int zf = 0;
	int sf = 0;
	int of = 0;
	int i, length;
	scanf("%s", command);

//strcasecmp
//strtok
	while(command != "quit"){
	if(strcmp("read", command) == 0){
		scanf("%s", arg1);
		scanf("%s", arg2);
		read(atoi(arg1), arg2, memory, registers);
	}
	
	if(strcmp("write", command) == 0){
		scanf("%s", arg1);
		write(arg1, registers, memory);				
	}
	
	if(strcmp("prints", command) == 0){
		prints(registers, memory, of, sf, zf);
	}
	scanf("%s", command);
	}
}
//SET OF FLAG
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

void prints(int registers[], int memory[], int of, int sf, int zf){

	int i, j, k;
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
	printf("\n");
	for(k = 0; k < 15; k++){
		printf("--\t");
	}
	printf("\n");
	for(i = 0; i < 4; i++){
		printf("R%d\t", i);
	}
	for(j = 0; j < 8; j++){
		printf("M%d\t", j);
	}
	printf("ZF\t");
	printf("SF\t");
	printf("OF");

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



void write(char arg1[], int registers[], int memory[]){
	if(strcmp(arg1, "m0") == 0){
		printf("%d\n", memory[0]);
	}
	if(strcmp(arg1, "m1") == 0){
		printf("%d\n", memory[1]);
	}
	if(strcmp(arg1, "m2") == 0){
		printf("%d\n", memory[2]);
	}
	if(strcmp(arg1, "m3") == 0){
		printf("%d\n", memory[3]);
	}
	if(strcmp(arg1, "m4") == 0){
		printf("%d\n", memory[4]);
	}
	if(strcmp(arg1, "m5") == 0){
		printf("%d\n", memory[5]);
	}
	if(strcmp(arg1, "m6") == 0){
		printf("%d\n", memory[6]);
	}
	if(strcmp(arg1, "m7") == 0){
		printf("%d\n", memory[7]);
	}
	if(strcmp(arg1, "r0") == 0){
		printf("%d\n", registers[0]);
	}
	if(strcmp(arg1, "r1") == 0){
		printf("%d\n", registers[1]);
	}
	if(strcmp(arg1, "r2") == 0){
		printf("%d\n", registers[2]);
	}
	if(strcmp(arg1, "r3") == 0){
		printf("%d\n", registers[3]);
	}
}
