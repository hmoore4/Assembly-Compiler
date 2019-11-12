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

//FUNCTION COMMENTS. ADD COMMA. AMOUNT OF  ARGS
void read(int data, char arg2[], int memory[], int of[]);
void prints(int registers[], int memory[], int of[], int sf[], int zf[]);
void write(char arg1[], int registers[], int memory[]);
void comp(char arg1[], char arg2[], int register1[], int register2[], int zf[], int sf[]);
void add(char arg1[], char arg2[], int registers[], int memory[], int of[], int zf[], int sf[]);
void sub(char arg1[], char arg2[], int registers[], int memory[], int of[], int zf[], int sf[]);
void mult(char arg1[], char arg2[], int registers[], int memory[], int of[], int zf[], int sf[]);
void div(char arg1[], char arg2[], int registers[], int memory[], int of[], int zf[], int sf[]);
void mod(char arg1[], char arg2[], int registers[], int memory[], int of[], int zf[], int sf[]);
void move(char arg1[], char arg2[], int registers[], int memory[]);

void main(void){
	char command[20];																								//Input arrays
	char arg1[20];
	char arg2[20];
	int registers[4] = {150, 150, 150, 150};												//Initialize values of array to values out of bounds
	int memory[8] = {150, 150, 150, 150, 150, 150, 150, 150};
	int zf[1] = {0};																								//Flag arrays
	int sf[1] = {0};
	int of[1] = {0};

	scanf("%s", command);

//strtok
	while(strcasecmp("quit", command) != 0){
	if(strcasecmp("read", command) == 0){
		scanf("%s", arg1);
		scanf("%s", arg2);
		read(atoi(arg1), arg2, memory, of);
	}

	if(strcasecmp("write", command) == 0){
		scanf("%s", arg1);
		write(arg1, registers, memory);
	}

	if(strcasecmp("prints", command) == 0){
		prints(registers, memory, of, sf, zf);
	}

	if(strcasecmp("comp", command) == 0){
		scanf("%s", arg1);
		scanf("%s", arg2);
		comp(arg1, arg2, registers, registers, zf, sf);
	}

	if(strcasecmp("add", command) == 0){
		scanf("%s", arg1);
		scanf("%s", arg2);
		add(arg1, arg2, registers, memory, of, zf, sf);
	}
	
	if(strcasecmp("sub", command) == 0){
		scanf("%s", arg1);
		scanf("%s", arg2);
		sub(arg1, arg2, registers, memory, of, zf, sf);
	}
	if(strcasecmp("mult", command) == 0){
		scanf("%s", arg1);
		scanf("%s", arg2);
		mult(arg1, arg2, registers, memory, of, zf, sf);
	}
	if(strcasecmp("div", command) == 0){
		scanf("%s", arg1);
		scanf("%s", arg2);
		div(arg1, arg2, registers, memory, of, zf, sf);
	}
	if(strcasecmp("mod", command) == 0){
		scanf("%s", arg1);
		scanf("%s", arg2);
		mod(arg1, arg2, registers, memory, of, zf, sf);
	}
	if(strcasecmp("move", command) == 0){
		scanf("%s", arg1);
		scanf("%s", arg2);
		move(arg1, arg2, registers, memory);
	}
	else{
		printf("???\n");
	}

	scanf("%s", command);
	}
}
//SET OF FLAG
/* IN: Data is the number that is being read in to the memory
 * IN: arg2 is the input of where the data will be held
 * IN: memory accesses the array that holds the values of memory locations
 * IN: of sets the overflow flag
 * OUT: returns nothing
 * SIDE EFFECT: OF flag set if output is too high/low. Memory array updated.
 * This function updates the overflow flag if necessary and updates value of memory locations
 * 
*/
void read(int data, char arg2[], int memory[], int of[]){
	of[0] = 0;
	if(data > 127 || data < -128){				//If the input is too high or too low, update the overflow flag
		of[0] = 1;
	}
	if(strcasecmp(arg2, "m0") == 0){			//If argument equal to memory location, set the memory location to the data
		memory[0] = data;
	}
	if(strcasecmp(arg2, "m1") == 0){
		memory[1] = data;
	}
	if(strcasecmp(arg2, "m2") == 0){
		memory[2] = data;
	}
	if(strcasecmp(arg2, "m3") == 0){
		memory[3] = data;
	}
	if(strcasecmp(arg2, "m4") == 0){
		memory[4] = data;
	}
	if(strcasecmp(arg2, "m5") == 0){
		memory[5] = data;
	}
	if(strcasecmp(arg2, "m6") == 0){
		memory[6] = data;
	}
	if(strcasecmp(arg2, "m7") == 0){
		memory[7] = data;
	}

}

/* IN: Registers and memory array prins out contents of those arrays
 * IN: of, sf, zf also print out contents of those arrays
 * OUT: Returns nothing
 * Side Effect: Nothing changed, just prints out contents of arrays
 * 
*/
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

/* IN: arg1 is the input, registers and memory are the register and memory arrays
 * OUT: Returns nothing
 * SIDE EFFECT: This function doesn't change anything, it just prints out the value at an index, if it exists
 *
*/
void write(char arg1[], int registers[], int memory[]){
	
	if(strcasecmp(arg1, "m0") == 0){
		if(memory[0] > 127 || memory[0] < -128){
			printf("???\n");
		}
		else{
			printf("%d\n", memory[0]);
		}
	}
	if(strcasecmp(arg1, "m1") == 0){
		if(memory[1] > 127 || memory[1] < -128){
			printf("???\n");
		}
		else{
			printf("%d\n", memory[1]);
		}
	}
	if(strcasecmp(arg1, "m2") == 0){
		if(memory[2] > 127 || memory[2] < -128){
			printf("???\n");
		}
		else{
			printf("%d\n", memory[2]);
		}
	}
	if(strcasecmp(arg1, "m3") == 0){
		if(memory[3] > 127 || memory[3] < -128){
			printf("???\n");
		}
		else{
			printf("%d\n", memory[3]);
		}
	}
	if(strcasecmp(arg1, "m4") == 0){
		if(memory[4] > 127 || memory[4] < -128){
			printf("???\n");
		}
		else{
			printf("%d\n", memory[4]);
		}
	}
	if(strcasecmp(arg1, "m5") == 0){
		if(memory[5] > 127 || memory[5] < -128){
			printf("???\n");
		}
		else{
			printf("%d\n", memory[5]);
		}
	}
	if(strcasecmp(arg1, "m6") == 0){
		if(memory[6] > 127 || memory[6] < -128){
			printf("???\n");
		}
		else{
			printf("%d\n", memory[6]);
		}
	}
	if(strcasecmp(arg1, "m7") == 0){
		if(memory[7] > 127 || memory[7] < -128){
			printf("???\n");
		}
		else{
			printf("%d\n", memory[7]);
		}
	}
	if(strcasecmp(arg1, "r0") == 0){
		if(registers[0] > 127 || registers[0] < -128){
			printf("???\n");
		}
		else{
			printf("%d\n", registers[0]);
		}
	}
	if(strcasecmp(arg1, "r1") == 0){
		if(registers[1] > 127 || registers[1] < -128){
			printf("???\n");
		}
		else{	
			printf("%d\n", registers[1]);
		}
	}
	if(strcasecmp(arg1, "r2") == 0){
		if(registers[2] > 127 || registers[2] < -128){
			printf("???\n");
		}
		else{
			printf("%d\n", registers[2]);
		}
	}
	if(strcasecmp(arg1, "r3") == 0){
		if(registers[3] > 127 || registers[3] < -128){
			printf("???\n");
		}
		else{
			printf("%d\n", registers[3]);
		}
	}
}

void comp(char arg1[], char arg2[], int register1[], int register2[], int zf[], int sf[]){
 int data1;
 int data2;
		if(strcasecmp(arg1, "r0") == 0){
			data1 = register1[0];
		}
		 if(strcasecmp(arg1, "r1") == 0){
			data1 = register1[1];
		}
		 if(strcasecmp(arg1, "r2") == 0){
			data1 = register1[2];
		}
		 if(strcasecmp(arg1, "r3") == 0){
			data1 = register1[3];
		}
		if(strcasecmp(arg2, "r0") == 0){
			data2 =	register2[0];
		}
		 if(strcasecmp(arg2, "r1") == 0){
			data2 = register2[1];
		}
		 if(strcasecmp(arg2, "r2") == 0){
			data2 = register2[2];
		}
		 if(strcasecmp(arg2, "r3") == 0){
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

void mult(char arg1[], char arg2[], int registers[], int memory[], int of[], int zf[], int sf[]){
	int data1 = arg1[1]- '0';
  int data2 = arg2[1] - '0';
	of[0] = 0;
	zf[0] = 0;
	sf[0] = 0;
	
	if(arg1[0] == 'm' && arg2[0] == 'm'){
		printf("???\n");
	}
	
	if(arg1[0] == 'r' && arg2[0] == 'm'){
    registers[0] =  registers[data1] * memory[data2];
	}
	if(arg1[0] == 'r' && arg2[0] == 'r'){
		registers[0] =  registers[data2] * registers[data1];
	}
	if(arg1[0] == 'm' && arg2[0] == 'r'){
		registers[0] =  memory[data1] * registers[data2];
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
