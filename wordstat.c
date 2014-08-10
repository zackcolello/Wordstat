#include "wordstat.h"

struct node *head = NULL;
struct node *temp = NULL;
struct node *temp2 = NULL;
struct node *newnode = NULL;


/*Main takes in the arguments wordstat and the text file being scanned.
Main loops through an input file by character with fgets(), and creates a char* str composed of only numbers and letters.
After a word is created, it is sent to a function chopdigits() that removes any potential digits in the beginning of the char*.
Finally, main calls printResult() which prints out the words in the file and its total and its case sensitive versions.
*/
int main(int argc, char *argv[])
{
	FILE *pFile;
	int fileS;
	char* str;
	int i=0, j=0, c;
	if (argc != 2) {
		printf("Please enter one input text file after the program. Type -h as an argument for more help.\n");
		return -1;
	}


	pFile = fopen(argv[1], "r");
	if(strcmp(argv[1], "-h") == 0){
		helpMenu();
		/* return 0; */
	}

	else if(pFile == NULL)
	{
		printf("The file could not be opened.\n");
	}else
	{

	
	fseek(pFile, 0, SEEK_END);
	fileS = ftell(pFile);
	fseek(pFile, 0, SEEK_SET); 
	str = (char*)malloc(sizeof(char)*fileS+1);
	/*char* str = (char*)malloc(100000000);
	*/
	
	while((c = fgetc(pFile)) != EOF)
	{
	
		if(isalpha(c) || isdigit(c)){
			str[j]= c;
			j++;
		}else{
			str[j+1] = '\0';
			chopdigits(str);
			j = 0;
			str = (char*)malloc(sizeof(char)*fileS+1);
		}
		i++;
		
	}
	
	fclose(pFile);

	printResult();	
	return 0;
	}
return 0;
}

int helpMenu()
{

printf("\n");
printf("This is the wordstat help menu.\n");
printf("How to use this program:\n");
printf("\tEnter 'wordstat <text file>'. Make sure the text file is valid. Do not use more than one text file.\n");
printf("What this program does:\n");
printf("\tThis wordstat program will take an input that contains digits, letters, and symbols and create words.\n");
printf("It will then output the unique words in lexicographical order, as well as the total\n"); 
printf("number of times the word appeared in the file, and the number of different case sensitive versions of that word.\n");
printf("\n");

return 0;	
}

/*chopdigits takes in a char* word, which consists of a word thay may contain digits in the beginning of the string.
chopdigits removes the digits from the beginning of a string, and calls processStr() to place the word in a Linked List.
*/
void chopdigits(char* word){

	if(!strlen(word) >= 1 || !(isalpha(word[0]) || isdigit(word[0]))){
		return;
	} 


	if(!isalpha(word[0])){
	int i = 0;

		while(isdigit(word[i])){
			i++;
		}
 
	word = &word[i];
	}

	processStr(word);
	return;
}

int i;

/*processStr receives a string, creates a node for the string and places it appropriately in an alphabetized linked list.
The linked list 
*/
void processStr(char* str)
{
	char *lcstr;
	struct node *newheadnode;
	int len = strlen(str);
	struct node *tempprev;
	int i;

	lcstr = (char*)malloc((len)+1);
	
	

	if(!strlen(str) >= 1 || (!isalpha(str[0]) )){
		return;
	}

	newnode = (struct node* )malloc(sizeof(struct node));

	newnode->word = str;

	if (head == NULL){

		/*convert word to lowercase to use as head node*/
		for (i = 0; i<= strlen(str)+1; i++) {
			lcstr[i] = tolower(str[i]);
		}		

		/*make a new head node with the case sensitive version as its next*/
		newheadnode = (struct node*)malloc(sizeof(struct node));
		newheadnode->word = lcstr;
		newheadnode->next = newnode;
		newnode->next = NULL;
		newheadnode->neighbor = NULL;
		newheadnode->csnum = 1;
		newheadnode->num = 1;	
		head = newheadnode;	
		return;
	}else{
		/*Grab case insensitive version of word to use*/
		char *lcstr;
		lcstr = malloc(sizeof(str)+1);

		for (i = 0; i<= strlen(str)+1; i++) {
			lcstr[i] = tolower(str[i]);
		}	

		temp = head;
		tempprev = (struct node*)malloc(sizeof(struct node));
		tempprev = NULL;

		/*cycle through neighbors to find match*/
		while(temp != NULL){
			/*if word  already exists, add to end of temp's next list*/
			if(strcmp(temp->word, lcstr) == 0){
				
				temp2 = temp;
				temp->num++;
				i = 1;

				while(temp->next != NULL){
					temp = temp->next;	

					if(strcmp(temp->word, str) == 0){
						i = 0;
					}

				}
				
				if(i == 1){
					temp2->csnum++;
				}

				temp->next = newnode;
				newnode->next = NULL;
				return; /*was break added last*/
			}

			else if(strcmp(lcstr, temp->word) < 0){ /*new word node made and placed before temp*/
				struct node *newbeforenode;
				newbeforenode = (struct node*)malloc(sizeof(struct node));
				newbeforenode->word = lcstr;
				newbeforenode->next = newnode;
				newbeforenode->neighbor = temp;
				newbeforenode->num = 1;
				newbeforenode->csnum = 1;	
				newnode->next = NULL;
			
				if(tempprev != NULL){
					tempprev->neighbor = newbeforenode;
				}	
				

				if(head == temp){
					head = newbeforenode;

				}
				return;

			}
			else if(temp->neighbor == NULL){
		
				struct node *newafternode;
				newafternode = (struct node*)malloc(sizeof(struct node));
				newafternode->word = lcstr;
				newafternode->next = newnode;
				temp->neighbor = newafternode;
				newafternode->num = 1;
				newafternode->csnum = 1;
				newafternode->neighbor = NULL;
				newnode->next = NULL;
				return;
			}

			tempprev = temp;
			temp = temp->neighbor;

		}
	free(lcstr);
		
	}
	return;

}

void printResult()
{
	printf("Word\tTotal No. Occurences\tNo. Case-Sensitive Versions\n");

	temp = head;

	while(temp){

	printf("%s\t%d\t%d\n", temp->word, temp->num, temp->csnum);
	temp = temp->neighbor;
	
	}

	return; 
}

