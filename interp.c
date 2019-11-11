

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

//FUNCTION COMMENTS. ADD COMMA. IF WRITE A UNENTERED REG, PRINT ???, CHANGE READ TO NOT DO REGISTERS, AMOUNT OF  ARGS, CASE SENSITIVITY
void error();
void read(int data, char arg2[], int memory[], int registers[], int of[]);
void prints(int registers[], int memory[], int of[], int sf[], int zf[]);
void write(char arg1[], int registers[], int memory[]);
void comp(char arg1[], char arg2[], int register1[], int register2[], int zf[], int sf[]);
void add(char arg1[], char arg2[], int registers[], int memory[], int of[], int zf[], int sf[]);
void sub(char arg1[], char arg2[], int registers[], int memory[], int of[], int zf[], int sf[]);
void div(char arg1[], char arg2[], int registers[], int memory[], int of[], int zf[], int sf[]);
void mod(char arg1[], char arg2[], int registers[], int memory[], int of[], int zf[], int sf[]);
void move(char arg1[], char arg2[], int registers[], int memory[]);


int main(void){
	char command[20];
	char arg1[20];
	char arg2[20];
	int registers[4] = {150, 150, 150, 150};
	int memory[8] = {150, 150, 150, 150, 150, 150, 150, 150};
	int zf[1] = {0};
	int sf[1] = {0};
	int of[1] = {0};

	scanf("%s", command);

//strcasecmp
//strtok
	while(strcmp("quit", command) != 0){
	if(strcmp("read", command) == 0){
		scanf("%s", arg1);
		scanf("%s", arg2);
		read(atoi(arg1), arg2, memory, registers, of);
	}

	if(strcmp("write", command) == 0){
		scanf("%s", arg1);
		write(arg1, registers, memory);
	}

	if(strcmp("prints", command) == 0){
		prints(registers, memory, of, sf, zf);
	}

	if(strcmp("comp", command) == 0){
		scanf("%s", arg1);
		scanf("%s", arg2);
		comp(arg1, arg2, registers, registers, zf, sf);
	}

	if(strcmp("add", command) == 0){
		scanf("%s", arg1);
		scanf("%s", arg2);
		//if(strcmp arg1, "r0/1/2/3"
			//add(refister)
		add(arg1, arg2, registers, memory, of, zf, sf);
	}
	
	if(strcmp("sub", command) == 0){
		scanf("%s", arg1);
		scanf("%s", arg2);
		sub(arg1, arg2, registers, memory, of, zf, sf);
	}
	if(strcmp("div", command) == 0){
		scanf("%s", arg1);
		scanf("%s", arg2);
		div(arg1, arg2, registers, memory, of, zf, sf);
	}
	if(strcmp("mod", command) == 0){
		scanf("%s", arg1);
		scanf("%s", arg2);
		mod(arg1, arg2, registers, memory, of, zf, sf);
	}
	if(strcmp("move", command) == 0){
		scanf("%s", arg1);
		scanf("%s", arg2);
		move(arg1, arg2, registers, memory);
	}

	scanf("%s", command);
	}
}
//SET OF FLAG
void read(int data, char arg2[], int memory[], int registers[], int of[]){
	of[0] = 0;
	if(data > 127 || data < -128){
		of[0] = 1;
	}
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
}

void prints(int registers[], int memory[], int of[], int sf[], int zf[]){

	int i, j, k;
	for(i = 0; i < 4; i++){
		if(registers[i] > 127 || registers[i] < -128){
			printf("???\t");
		}
		else{
			printf("%d\t", registers[i]);
		}
	}
	for(j = 0; j < 8; j++){
		if(memory[j] > 127 || memory[j] < -128){
			printf("???\t");
		}
		else{
			printf("%d\t", memory[j]);
		}
	}
	printf("%d\t", of[0]);
	printf("%d\t", sf[0]);
	printf("%d\t", zf[0]);
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
	printf("OF\t");
	printf("SF\t");
	printf("ZF\t");



	printf("\n");
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

void comp(char arg1[], char arg2[], int register1[], int register2[], int zf[], int sf[]){
 int data1;
 int data2;
		if(strcmp(arg1, "r0") == 0){
			data1 = register1[0];
		}
		 if(strcmp(arg1, "r1") == 0){
			data1 = register1[1];
		}
		 if(strcmp(arg1, "r2") == 0){
			data1 = register1[2];
		}
		 if(strcmp(arg1, "r3") == 0){
			data1 = register1[3];
		}
		if(strcmp(arg2, "r0") == 0){
			data2 =	register2[0];
		}
		 if(strcmp(arg2, "r1") == 0){
			data2 = register2[1];
		}
		 if(strcmp(arg2, "r2") == 0){
			data2 = register2[2];
		}
		 if(strcmp(arg2, "r3") == 0){
			data2 = register2[3];
		}

		if(data1 > data2){
			zf[0] = 0;
			sf[0] = 1;
		}
		if(data1 == data2){
			zf[0] = 1;
			sf[0] = 0;
		}
		if(data1 < data2){
			zf[0] = 0;
			sf[0] = 0;
		}
		printf("%d and %d", zf[0], sf[0]);
}
//if arg1[0] == 'm' && arg2[0] == 'm' then error
// if arg1 = r and arg2 = m or vice versa then test arg1/arg2[1] and then check if r is between 0,3 and memory is between 0,7. Then two nums are stored at arrays at index of arg1/2[1]. Then add them. Do same for m,r and r,r (test index again). Test overflow
void add(char arg1[], char arg2[], int registers[], int memory[], int of[], int zf[], int sf[]){
  int data1 = arg1[1]- '0';
  int data2 = arg2[1] - '0';
	of[0] = 0;
	zf[0] = 0;
	sf[0] = 0;



	if(arg1[0] == 'm' && arg2[0] == 'm'){
		printf("???\n");
	}
	
	if(arg1[0] == 'r' && arg2[0] == 'm'){
    registers[0] =  registers[data1] + memory[data2];
	}
	if(arg1[0] == 'r' && arg2[0] == 'r'){
		registers[0] =  registers[data1] + registers[data2];
	}
	if(arg1[0] == 'm' && arg2[0] == 'r'){
		registers[0] =  memory[data1] + registers[data2];
	}
	if (registers[0] > 127 || registers[0] < -128){
		of[0] = 1;
	}
	if(registers[0] == 0){
		zf[0] = 1;
	}
	if(registers[0] < 0){
		sf[0] = 1;
	}
}

//Check flags here
void sub(char arg1[], char arg2[], int registers[], int memory[], int of[], int zf[], int sf[]){
	 int data1 = arg1[1]- '0';
  int data2 = arg2[1] - '0';
	of[0] = 0;
	zf[0] = 0;
	sf[0] = 0;
	

		if(arg1[0] == 'm' && arg2[0] == 'm'){
		printf("???\n");
	}
	
	if(arg1[0] == 'r' && arg2[0] == 'm'){
    registers[0] =  registers[data2] - memory[data1];
	}
	if(arg1[0] == 'r' && arg2[0] == 'r'){
		registers[0] =  registers[data2] - registers[data1];
	}
	if(arg1[0] == 'm' && arg2[0] == 'r'){
		registers[0] =  memory[data2] - registers[data1];
	}
	if (registers[0] > 127 || registers[0] < -128){
		of[0] = 1;
	}
	if(registers[0] == 0){
		zf[0] = 1;
	}
	if(registers[0] < 0){
		sf[0] = 1;
	}
}

void div(char arg1[], char arg2[], int registers[], int memory[], int of[], int zf[], int sf[]){
	int data1 = arg1[1]- '0';
  int data2 = arg2[1] - '0';
	of[0] = 0;
	zf[0] = 0;
	sf[0] = 0;
	
	if(arg1[0] == 'm' && arg2[0] == 'm'){
		printf("???\n");
	}
	
	if(arg1[0] == 'r' && arg2[0] == 'm'){
    registers[0] =  registers[data1] / memory[data2];
	}
	if(arg1[0] == 'r' && arg2[0] == 'r'){
		registers[0] =  registers[data1] / registers[data2];
	}
	if(arg1[0] == 'm' && arg2[0] == 'r'){
		registers[0] =  memory[data1] / registers[data2];
	}
	if (registers[0] > 127 || registers[0] < -128){
		of[0] = 1;
	}
	if(registers[0] == 0){
		zf[0] = 1;
	}
	if(registers[0] < 0){
		sf[0] = 1;
	}
	
}

void mod(char arg1[], char arg2[], int registers[], int memory[], int of[], int zf[], int sf[]){
		int data1 = arg1[1]- '0';
  int data2 = arg2[1] - '0';
	of[0] = 0;
	zf[0] = 0;
	sf[0] = 0;
	
	if(arg1[0] == 'm' && arg2[0] == 'm'){
		printf("???\n");
	}
	
	if(arg1[0] == 'r' && arg2[0] == 'm'){
    registers[0] =  registers[data1] % memory[data2];
	}
	if(arg1[0] == 'r' && arg2[0] == 'r'){
		registers[0] =  registers[data1] % registers[data2];
	}
	if(arg1[0] == 'm' && arg2[0] == 'r'){
		registers[0] =  memory[data1] % registers[data2];
	}
	if (registers[0] > 127 || registers[0] < -128){
		of[0] = 1;
	}
	if(registers[0] == 0){
		zf[0] = 1;
	}
	if(registers[0] < 0){
		sf[0] = 1;
	}
}



void move(char arg1[], char arg2[], int registers[], int memory[]){
	int data1 = arg1[1]- '0';
  int data2 = arg2[1] - '0';
	if(arg1[0] == 'm' && arg2[0] == 'm'){
		printf("???");	
	}
	
	if(arg1[0] == 'r' && arg2[0] == 'm'){
		memory[data2] = registers[data1]; 
	}
	
	
	if(arg1[0] == 'm' && arg2[0] == 'r'){
		registers[data2] = memory[data1];
	}
		
	if(arg1[0] == 'r' && arg2[0] == 'r'){
		registers[data2] = registers[data1];
	}
}
