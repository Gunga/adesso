/*
	Computer Project Number 5
	Program 1
	Joan Torres
	Inge3016-080
	Lenguaje C
	Prof. Jaime Ramirez Vick
	5 de diciembre de 2007
*/
/* Morse Code
	This programs prompts the user for text then through
	the user's choice makes the encoding or decoding to or
	from morse code.
	Varibles:
	text : array that holds the text the user enters
	choice : number choice so as to either encode or decode
	words : receives the line of text to be encoded
	codes : receives the line of code to be decoded
	i, j : variables used for counting in loops
	temp1 : holds codes in an array
	codebreak : used to hold temporary code "tokens"
	encode : function used to encode words in morse code
	decode : function used to decode into words
	Code : a struct holding letters and the morse code for each
*/


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define NUM 37


  

int main () {
	
	void encode(char *words), decode(char *codes);
	char text[80]={0};
	int choice;
	
	printf("Enter a line of text\n");  /*prompts the user for the text*/
	gets( text );

	printf("Enter 1 for encoding into morse code and 2 for decoding into words\n");
	scanf("%d", &choice);

	switch(choice){				/*switch condition in order to know whether to encode or decode*/
		case 1:
			{
			encode(text);		/*call encode and send the text*/
			break;
			}
		case 2:
			decode(text);		/*call decode and send the text*/
			break;
		default:
			printf("Try again");/*used if anything but a one or two is found in choice*/
	}		
			
	return 0;
}/*End main*/

void encode( char *words){
	
	int i,j=0;
	
	   struct		/*struct is initialized*/
 {
   char letter, *morse;
 } Code[NUM] =
 {
   {'A', ".- "},{'B', "-... "}, {'C', "-.-. "}, {'D', "-.. "},
   {'E', ". "}, {'F', "..-. "}, {'G', "--. "}, {'H', ".... "},
   {'I', ".. "},{'J', ".--- "}, {'K', ".-.- "}, {'L', ".-.. "},
   {'M', "-- "}, {'N', "-. "}, {'O', "--- "}, {'P', ".--. "},
   {'Q', "--.- "}, {'R', ".-. "}, {'S', "... "}, {'T', "- "},
   {'U', "..- "}, {'V', "...- "}, {'W', ".-- "}, {'X', "-..- "},
   {'Y', "-.-- "}, {'Z', "--.. "}, {' ', " "}, {'1', ".---- "},
   {'2', "..--- "}, {'3', "...-- "}, {'4', "....- "}, {'5', "..... "},
   {'6', "-.... "}, {'7', "--... "}, {'8', "---.. "}, {'9', "----. "},
   {'0', "----- "},
  };
	
	for ( i = 0; words[i]!='\0'; i++ )				/*For loop which makes each letter it*/ 
			words[ j++ ] = toupper( words[ i ]);	/*finds an uppercase letter*/ 
		  
	for (i=0; words[i]!='\0'; i++){					/*For loops made to look for each indiviual character*/
		for(j=0; j<37; j++){						/*in the letters of Code, then if found, it prints the*/
			if(words[i]==Code[j].letter){			/*code for each letter or character it finds*/
				printf("%s",Code[j].morse);
				break;
			}
		}
	}	

}/*End encode*/




void decode( char *codes){

	char *codebreak;
	int i;
	char temp1[80]={0};

		   struct
 {
   char letter, *morse;
 } Code[NUM] =
 {
   {'A', ".-"},{'B', "-..."}, {'C', "-.-."}, {'D', "-.."},
   {'E', "."}, {'F', "..-."}, {'G', "--."}, {'H', "...."},
   {'I', ".."},{'J', ".---"}, {'K', ".-.-"}, {'L', ".-.."},
   {'M', "--"}, {'N', "-."}, {'O', "---"}, {'P', ".--."},
   {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
   {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"},
   {'Y', "-.--"}, {'Z', "--.."}, {' ', " "}, {'1', ".----"},
   {'2', "..---"}, {'3', "...--"}, {'4', "....-"}, {'5', "....."},
   {'6', "-...."}, {'7', "--..."}, {'8', "---.."}, {'9', "----."},
   {'0', "-----"},
  };
	
	strcpy(temp1, codes);			/*Copy what is in 'codes' into an array*/
	codebreak=strtok(temp1, " ");	/*then make the first token with all   */
									/*until a space is found			   */
	do{
		for(i=0; i<37; i++){				          /*For loop which looks for the same string  */
			if(strcmp(codebreak, Code[i].morse)==0){  /*in the morse part of Code and if they are */
				printf("%c ",Code[i].letter);		  /*the same, print the letter part of it     */
				break;
			}
		}
		codebreak=strtok(NULL," ");			/*continue tokenizing*/

	}while(codebreak!=NULL);	

}/*End decode, end program*/