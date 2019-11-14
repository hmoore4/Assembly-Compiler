/* Hunter Moore
 * 10/31/19
 * CPSC275 F
 * This program acts a compiler for a pseudo assembly language.
 * It recognizes a few commands and moves information to a set of registers and memory locations.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_ARG_LENGTH 20
#define REGISTER_LENGTH 4
#define MEMORY_LENGTH 8
#define FLAG_LENGTH 1

// ADD COMMA.
void read(int data, char arg2[], int memory[], int of[]);
void prints(int registers[], int memory[], int of[], int sf[], int zf[]);
void write(char arg1[], int registers[], int memory[]);
void comp(char arg1, char arg2, int index1, int index2, int registers[], int zf[], int sf[]);
void add(char arg1[], char arg2[], int registers[], int memory[], int of[], int zf[], int sf[]);
void sub(char arg1[], char arg2[], int registers[], int memory[], int of[], int zf[], int sf[]);
void mult(char arg1[], char arg2[], int registers[], int memory[], int of[], int zf[], int sf[]);
void div(char arg1[], char arg2[], int registers[], int memory[], int of[], int zf[], int sf[]);
void mod(char arg1[], char arg2[], int registers[], int memory[], int of[], int zf[], int sf[]);
void move(char arg1[], char arg2[], int registers[], int memory[]);
int checkinput(int num1, int num2);

void main(void){

  char command[MAX_ARG_LENGTH];																								//Input arrays
  char arg1[MAX_ARG_LENGTH];
  char arg2[MAX_ARG_LENGTH];
  char arg3;
  char arg4;
  int registers[REGISTER_LENGTH] = {150, 150, 150, 150};												//Initialize values of array to values out of bounds
  int memory[MEMORY_LENGTH] = {150, 150, 150, 150, 150, 150, 150, 150};
  int zf[FLAG_LENGTH] = {0};																								//Flag arrays
  int sf[FLAG_LENGTH] = {0};
  int of[FLAG_LENGTH] = {0};
  int index1;
  int index2;
  printf("SM$: ");
  scanf("%s", command);

  while(strcasecmp("quit", command) != 0){												//Compares user input to instructions. Calls function if appropriate

    if(strcasecmp("read", command) == 0){
      scanf("%s", arg1);
      scanf("%s", arg2);
      read(atoi(arg1), arg2, memory, of);
    }

    else if(strcasecmp("write", command) == 0){
      scanf("%s", arg1);
      write(arg1, registers, memory);
    }

    else if(strcasecmp("prints", command) == 0){
      prints(registers, memory, of, sf, zf);
    }

    else if(strcasecmp("comp", command) == 0){
      scanf(" %c", &arg3);
      scanf("%d", &index1);
      scanf(" %c", &arg4);
      scanf(" %c", &arg4);
      
      scanf("%d", &index2);
      comp(arg3, arg4, index1, index2, registers, zf, sf);
    }

    else if(strcasecmp("add", command) == 0){
      scanf("%s", arg1);
      scanf("%s", arg2);
      add(arg1, arg2, registers, memory, of, zf, sf);
    }
	
    else if(strcasecmp("sub", command) == 0){
      scanf("%s", arg1);
      scanf("%s", arg2);
      sub(arg1, arg2, registers, memory, of, zf, sf);
    }
    else if(strcasecmp("mult", command) == 0){
      scanf("%s", arg1);
      scanf("%s", arg2);
      mult(arg1, arg2, registers, memory, of, zf, sf);
    }
    else if(strcasecmp("div", command) == 0){
      scanf("%s", arg1);
      scanf("%s", arg2);
      div(arg1, arg2, registers, memory, of, zf, sf);
    }
    else if(strcasecmp("mod", command) == 0){
      scanf("%s", arg1);
      scanf("%s", arg2);
      mod(arg1, arg2, registers, memory, of, zf, sf);
    }
    else if(strcasecmp("move", command) == 0){
      scanf("%s", arg1);
      scanf("%s", arg2);
      move(arg1, arg2, registers, memory);
    }
    else{																										//Otherwise invalid, trigger "???"
      printf("???\n");
    }
  printf("SM$: ");
  scanf("%s", command);
  }
}

/* IN: Data is the number that is being read in to the memory
 * IN: arg2 is the input of where the data will be held
 * IN: memory accesses the array that holds the values of memory locations
 * IN: of sets the overflow flag
 * OUT: returns nothing
 * SIDE EFFECT: OF flag set if output is too high/low. Memory array updated.
 * This function updates the overflow flag if necessary and updates value of memory locations
*/
void read(int data, char arg2[], int memory[], int of[]){
  of[0] = 0;
  if(data > 127 || data < -128){				//If the input is too high or too low, update the overflow flag
    of[0] = 1;
  }
  if(strcasecmp(arg2, "m0") == 0){			//If argument equal to memory location, set the memory location to the data
    memory[0] = data;
  }
  else if(strcasecmp(arg2, "m1") == 0){
    memory[1] = data;
  }
  else if(strcasecmp(arg2, "m2") == 0){
    memory[2] = data;
  }
  else if(strcasecmp(arg2, "m3") == 0){
    memory[3] = data;
  }
  else if(strcasecmp(arg2, "m4") == 0){
    memory[4] = data;
  }
  else if(strcasecmp(arg2, "m5") == 0){
    memory[5] = data;
  }
  else  if(strcasecmp(arg2, "m6") == 0){
    memory[6] = data;
  }
  else if(strcasecmp(arg2, "m7") == 0){
    memory[7] = data;
  }
  else{
  	printf("???\n");
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
  for(i = 0; i < 4; i++){																//Prints registers
    if(registers[i] > 127 || registers[i] < -128){
      printf("?\t");
    }
    else{
      printf("%d\t", registers[i]);
    } 
  }
  for(j = 0; j < 8; j++){															//Prins memory
    if(memory[j] > 127 || memory[j] < -128){
      printf("?\t");
    }
    else{
      printf("%d\t", memory[j]);
    }
  }
  printf("%d\t", of[0]);
  printf("%d\t", sf[0]);														//Prints flags
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
 * SIDE EFFECT: This function doesn't change anything, it just prints out the value at an index, if it exists.
 * Prints out the value at the register/memory location
*/
void write(char arg1[], int registers[], int memory[]){	
  if(strcasecmp(arg1, "m0") == 0){
    if(memory[0] > 127 || memory[0] < -128){		//If overflow
      printf("???\n");													//Print ???
    }
    else{
      printf("%d\n", memory[0]);								//Else print value
    }
  }
  else if(strcasecmp(arg1, "m1") == 0){
    if(memory[1] > 127 || memory[1] < -128){
      printf("???\n");
    }
    else{
      printf("%d\n", memory[1]);
    }
  }
  else if(strcasecmp(arg1, "m2") == 0){
    if(memory[2] > 127 || memory[2] < -128){
      printf("???\n");
    }
    else{
      printf("%d\n", memory[2]);
    }
  }
  else  if(strcasecmp(arg1, "m3") == 0){
    if(memory[3] > 127 || memory[3] < -128){
      printf("???\n");
    }
    else{
      printf("%d\n", memory[3]);
    }
  }
  else if(strcasecmp(arg1, "m4") == 0){
    if(memory[4] > 127 || memory[4] < -128){
       printf("???\n");
    }
    else{
      printf("%d\n", memory[4]);
    }
  }
  else if(strcasecmp(arg1, "m5") == 0){
    if(memory[5] > 127 || memory[5] < -128){
      printf("???\n");
    }
    else{
      printf("%d\n", memory[5]);
    }
  }
  else if(strcasecmp(arg1, "m6") == 0){
    if(memory[6] > 127 || memory[6] < -128){
      printf("???\n");
    }
    else{
      printf("%d\n", memory[6]);
    }
  }
  else if(strcasecmp(arg1, "m7") == 0){
    if(memory[7] > 127 || memory[7] < -128){
      printf("???\n");
    }
    else{
      printf("%d\n", memory[7]);
    }
  }
  else if(strcasecmp(arg1, "r0") == 0){
    if(registers[0] > 127 || registers[0] < -128){
      printf("???\n");
    }
    else{
      printf("%d\n", registers[0]);
    }
  }
  else if(strcasecmp(arg1, "r1") == 0){
    if(registers[1] > 127 || registers[1] < -128){
      printf("???\n");
    }
    else{	
      printf("%d\n", registers[1]);
    }
  }  
  else if(strcasecmp(arg1, "r2") == 0){
    if(registers[2] > 127 || registers[2] < -128){
      printf("???\n");
    }
    else{
      printf("%d\n", registers[2]);
    }
  }
  else if(strcasecmp(arg1, "r3") == 0){
    if(registers[3] > 127 || registers[3] < -128){
      printf("???\n");
    }
    else{
      printf("%d\n", registers[3]);
    }
  }
  else{
  	printf("???\n");
  }
}

/* IN: arg1, arg2 are inputs from user. Register1, register2 are the two registers being compared. Zf, sf set the flags
 * OUT: Nothing is being returned
 * SIDE EFFECT: Flags are being changed based on the comparison
 * Compares two register values and sets flags accordingly.
 */
void comp(char arg1, char arg2, int index1, int index2, int registers[], int zf[], int sf[]){
  if(arg1 == 'm' || arg2 == 'm'){				//Cannot do memory -> memory	
    printf("???\n");	
  }

  else if(arg1 == 'r'){			//Determines correct input
    if(index1 >= 0 && index1 <= 3){
    	if(arg2 == 'r'){
    	  if(index2 >= 0 && index2 <= 3){
    	    if(checkinput(registers[index1], registers[index2])){
		  	    if(registers[index1] > registers[index2]){									//Sets flags accordingly								
		          zf[0] = 0;
		          sf[0] = 1;
		        }
		         if(registers[index1] == registers[index2]){
		           zf[0] = 1;
		           sf[0] = 0;
		         }
		         if(registers[index1] < registers[index2]){
		           zf[0] = 0;
		           sf[0] = 0;
		  	     }
    	   }
    	   else{
    	     printf("???\n");
    	   }
    	 }
     }
   }
 }
}

/* IN: arg1, arg2 are input from user. Registers, memory are register and memory arrays. Of, zf, sf are flag arrays
 * OUT: returns nothing
 * SIDE EFFECTS: Updates registers[0]
 * Adds two location values together. Cannot add two memory locations. Result stored in register[0]
 */
void add(char arg1[], char arg2[], int registers[], int memory[], int of[], int zf[], int sf[]){
  int data1 = arg1[1]- '0';																	//Find index
  int data2 = arg2[1] - '0';
  int input1;
  int input2;
  of[0] = 0;																					//Reset flag
  zf[0] = 0;
  sf[0] = 0;

  if(arg1[0] == 'm' && arg2[0] == 'm'){
    printf("???\n");																							//Cannot do memory->memory
  }

	if(arg1[0] == 'r' && arg2[0] == 'm'){														//Calculations
		input1 = registers[data1];
		input2 = memory[data2];
		if(checkinput(input1, input2)){
	  	registers[0] =  registers[data1] + memory[data2];
	  }
	  else{
	    printf("???\n");
	    of[0] = 0;
	  }
	}																	
	else if(arg1[0] == 'r' && arg2[0] == 'r'){
    input1 = registers[data1];
		input2 = registers[data2];
		if(checkinput(input1, input2)){
	    registers[0] =  registers[data1] + registers[data2];
	  }
	  else{
	    printf("???\n");
	    of[0] = 0;
	  } 
	}
	else if(arg1[0] == 'm' && arg2[0] == 'r'){
    input1 = memory[data1];
		input2 = registers[data2];
		if(checkinput(input1, input2)){
	     registers[0] =  memory[data1] + registers[data2];
	  }
	  else{
	    printf("???\n");
	    of[0] = 0;
	  } 		  
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

/* IN: arg1, arg2 are input from user. Registers, memory are register and memory arrays. Of, zf, sf are flag arrays
 * OUT: returns nothing
 * SIDE EFFECTS: Updates registers[0]
 * Subtracts two location values together. It subtracts the first input from the second. Cannot subtact two memory locations. Result stored in register[0]
 */
void sub(char arg1[], char arg2[], int registers[], int memory[], int of[], int zf[], int sf[]){
  int data1 = arg1[1]- '0';																	//Find index
  int data2 = arg2[1] - '0';
  int input1;
  int input2;
  of[0] = 0;
  zf[0] = 0;																								//Reset flag
  sf[0] = 0;

  if(arg1[0] == 'm' && arg2[0] == 'm'){											//Cannot do memory->memory
    printf("???\n");
  }
	
  if(arg1[0] == 'r' && arg2[0] == 'm'){
  	input1 = registers[data1];
		input2 = memory[data2];
		if(checkinput(input1, input2)){
	  	registers[0] =  memory[data2] - registers[data1];
	  }
	  else{
	    printf("???\n");
	  }
  }
  else if(arg1[0] == 'r' && arg2[0] == 'r'){
    input1 = registers[data1];
		input2 = registers[data2];
		if(checkinput(input1, input2)){
	    registers[0] =  registers[data2] - registers[data1];
	  }
	  else{
	    printf("???\n");
	  } 
  }
  else if(arg1[0] == 'm' && arg2[0] == 'r'){
    input1 = memory[data1];
		input2 = registers[data2];
		if(checkinput(input1, input2)){
	     registers[0] =  registers[data2] - memory[data1];
	  }
	  else{
	    printf("???\n");
	  }
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
/* IN: arg1, arg2 are input from user. Registers, memory are register and memory arrays. Of, zf, sf are flag arrays
 * OUT: returns nothing
 * SIDE EFFECTS: Updates registers[0]
 * Multiplies two location values together. Cannot multiply two memory locations. Result stored in register[0]
 */
void mult(char arg1[], char arg2[], int registers[], int memory[], int of[], int zf[], int sf[]){
  int data1 = arg1[1]- '0';
  int data2 = arg2[1] - '0';								//Finds index
  int input1;
  int input2;
  of[0] = 0;
  zf[0] = 0;																//Reset flag
  sf[0] = 0;
	
  if(arg1[0] == 'm' && arg2[0] == 'm'){												//Cannot do memory->memory
    printf("???\n");
  }
	
  if(arg1[0] == 'r' && arg2[0] == 'm'){										//Calculations
  	input1 = registers[data1];
		input2 = memory[data2];
		if(checkinput(input1, input2)){
	  	registers[0] =  registers[data1] * memory[data2];
	  }
	  else{
	    printf("???\n");
	  }
  }
  if(arg1[0] == 'r' && arg2[0] == 'r'){
    input1 = registers[data1];
		input2 = registers[data2];
		if(checkinput(input1, input2)){
	    registers[0] =  registers[data1] * registers[data2];
	  }
	  else{
	    printf("???\n");
	  } 
  }
  if(arg1[0] == 'm' && arg2[0] == 'r'){
    input1 = memory[data1];
		input2 = registers[data2];
		if(checkinput(input1, input2)){
	     registers[0] =  memory[data1] * registers[data2];
	  }
	  else{
	    printf("???\n");
	  }
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

/* IN: arg1, arg2 are input from user. Registers, memory are register and memory arrays. Of, zf, sf are flag arrays
 * OUT: returns nothing
 * SIDE EFFECTS: Updates registers[0]
 * Dvidies two location values together. Cannot divide two memory locations. Result stored in register[0]
 */
void div(char arg1[], char arg2[], int registers[], int memory[], int of[], int zf[], int sf[]){
  int data1 = arg1[1]- '0';										//Finds index
  int data2 = arg2[1] - '0';
  int input1;
  int input2;
  of[0] = 0;
  zf[0] = 0;																	//Reset flag
  sf[0] = 0;
	
  if(arg1[0] == 'm' && arg2[0] == 'm'){											//Cannot do memory->memory
    printf("???\n");
  }
	
  if(arg1[0] == 'r' && arg2[0] == 'm'){												//Calculations
  	if(memory[data2] != 0){
      input1 = registers[data1];
		  input2 = memory[data2];
		  if(checkinput(input1, input2)){
	  	  registers[0] =  registers[data1] / memory[data2];
	    }
	    else{
	      printf("???\n");
	    }
    }
    else{
      printf("???\n");
    }
  }
  
  if(arg1[0] == 'r' && arg2[0] == 'r'){
   if(registers[data2] != 0){
      input1 = registers[data1];
	  	input2 = registers[data2];
		  if(checkinput(input1, input2)){
	      registers[0] =  registers[data1] / registers[data2];
	    }
	    else{
	      printf("???\n");
	    } 
    }
    else{
      printf("???\n");
    }
  }
  
  if(arg1[0] == 'm' && arg2[0] == 'r'){
    if(registers[data2] != 0){
      input1 = memory[data1];
		  input2 = registers[data2];
		  if(checkinput(input1, input2)){
	       registers[0] =  memory[data1] / registers[data2];
	    }
	    else{
	      printf("???\n");
	    }
    }
    else{
      printf("???\n");
    }
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
/* IN: arg1, arg2 are input from user. Registers, memory are register and memory arrays. Of, zf, sf are flag arrays
 * OUT: returns nothing
 * SIDE EFFECTS: Updates registers[0]
 * Modulos two location values together. Cannot mod two memory locations. Result stored in register[0]
 */
void mod(char arg1[], char arg2[], int registers[], int memory[], int of[], int zf[], int sf[]){
  int data1 = arg1[1]- '0';			//Finds index
  int data2 = arg2[1] - '0'; 
  int input1;
  int input2;
  of[0] = 0;										//Reset flag
  zf[0] = 0;
  sf[0] = 0;
	
  if(arg1[0] == 'm' && arg2[0] == 'm'){										//Cannot do memory->memory
    printf("???\n");
  }
	
  if(arg1[0] == 'r' && arg2[0] == 'm'){										//Calculations
      input1 = registers[data1];
		  input2 = memory[data2];
		  if(checkinput(input1, input2)){
	  	  registers[0] =  registers[data1] % memory[data2];
	    }
	    else{
	      printf("???\n");
	    }
  }
  if(arg1[0] == 'r' && arg2[0] == 'r'){
      input1 = registers[data1];
	  	input2 = registers[data2];
		  if(checkinput(input1, input2)){
	      registers[0] =  registers[data1] % registers[data2];
	    }
	    else{
	      printf("???\n");
	    } 
  }
  if(arg1[0] == 'm' && arg2[0] == 'r'){
      input1 = memory[data1];
		  input2 = registers[data2];
		  if(checkinput(input1, input2)){
	       registers[0] =  memory[data1] % registers[data2];
	    }
	    else{
	      printf("???\n");
	    }
  }
  if (registers[0] > 127 || registers[0] < -128){				//Set flags
    of[0] = 1;
  }
  if(registers[0] == 0){
    zf[0] = 1;
  }
  if(registers[0] < 0){
    sf[0] = 1;
  }
}
/* IN: arg1, arg2 are input from user. Registers, memory are register and memory arrays.
 * OUT: returns nothing
 * SIDE EFFECTS: Updates either register or memory location
 * Moves values from either memory or register to another location. Cannot move memory to memory but all others are ok
 */
void move(char arg1[], char arg2[], int registers[], int memory[]){
  int data1 = arg1[1]- '0';										//Finds index
  int data2 = arg2[1] - '0';
  if(arg1[0] == 'm' && arg2[0] == 'm'){				//Cannot do memory -> memory	
    printf("???\n");	
  }
	
  else if(arg1[0] == 'r' && arg2[0] == 'm'){				//Transfers data
  	if(registers[data1] >= -127 && registers[data1]<= 128){
      memory[data2] = registers[data1]; 
    }
    else{
      printf("???\n");
    }
  }
	
  else if(arg1[0] == 'm' && arg2[0] == 'r'){
  	if((memory[data1] >= -127 && memory[data1] <= 128)){
    	registers[data2] = memory[data1];
    }
    else{
      printf("???\n");
    }
  }
		
  else if(arg1[0] == 'r' && arg2[0] == 'r'){
    if(registers[data1] >= -127 && registers[data1] <= 128){
      registers[data2] = registers[data1];
    }
    else{
      printf("???\n");
    }
  }
  else{
    printf("???\n");
  }
}

/* IN: Num1, num2 are the values of the index of an array
 * OUT: returns 0 or 1. 0 is bad input 1 is good input
 * SIDE EFFECT: Nothing is changed
 * This function checks output to make sure it is in the range
 */
int checkinput(int num1, int num2){
	if((num1 > 127 || num1 < -128) || (num2 > 127 || num2 < -128)){
		return 0;
	}
	else{
		return 1;
	}
}
