#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct Book{				//Creates a structure in which we can reuse multiple parameters
	char title[100];
	char author[100];
	char genre[20]; 
	char stack[10]; 
	char language[50]; 
};

void CommandList(void); //Declaring functions ** Commandlist is for the UI and gives a list of command hot keys
void AddBook(FILE *lib, struct Book *books); // AddBook uses the struct declared above and appends the data to file
void ViewList(FILE *view); //Uses the created file to view declared structs (books)
void RemoveFile(FILE *remove); //Removes/clears the file 
//The output paramteres are 'void' because there is no output

int main(int argc, char **argv)
{
	FILE *Library; //Creating the Library variable file
	char Command; //Command hot key
	struct Book Add; //Declaring struct
	
	printf("==============================================Library==============================================\n");
	printf("Press 'C' to list commands \n"); 
	
	do{ //Using a switch statement in a do loop gives a simple and clean looking interface and code
	scanf("%s",&Command);  //scan the command variable hot key
	
		switch(Command){ //Switch statment for the Command variable
			case 'A': 	Library=fopen("LibraryFile.txt","a+"); //In the case of capital 'A' press, open the library file, if there isn't one, create it and append to it
						AddBook(Library, &Add); //use the function addbook, with inputparameters of the file and the struct
						fclose(Library); //Close the library file for appending
				break;
			case 'V': 	if((Library=fopen("LibraryFile.txt","r"))!= NULL){ //V hot key gives the list of books, opens the file for only read mode
						ViewList(Library); //use function view list
						}else{ //if in case there isn't a file created, therefore the above statement of !=NULL, then print out the following statement below...
							printf("The library is empty\n");
						} 
				break;
			case 'R': RemoveFile(Library); //Clear the file using the removefile function
				break;
			case 'E': printf("Exiting\n"); //E hot key gives us a break from the loop, for UI sake, add the text Exiting to confirm to the user that the program has exited safely
				break;
			case 'C': CommandList();//a predefined text function that gives the set of command hot keys
				break;
			default: printf("Character Invalid\n"); //for any default value, just print out the following statement
				break;
		}
	
	}while(Command!='E');
	
	return 0;
}


void CommandList (void){ //Commandlist function is containing the command hot keys, no input and output needed
	printf("Press 'A' to add book\n");
	printf("Press 'V' to list books in library\n");
	printf("Press 'R' to remove library\n");
	printf("Press 'E' to exit library\n");
}

void AddBook (FILE *lib, struct Book *books){ //Addbook function needs the input value of file and the struct, therefore it is declared and used in the following function
	char InternalSeparator= '|'; //used as a separator in file
	fflush(stdin); //flush 
	printf("Book Title: ");  
	gets(books->title); //scan the input.title of the book 
	fputs(books->title, lib); //put the scanned value into the file 
	fputc(InternalSeparator, lib); //add the separator
	printf("Author of the book: "); 
	gets(books->author);
	fputs(books->author, lib);
	fputc(InternalSeparator, lib); 
	printf("Book genre: "); 
	gets(books->genre); 
	fputs(books->genre, lib);
	fputc(InternalSeparator, lib); 
	printf("What stack is the book located at: "); 
	gets(books->stack);
	fputs(books->stack, lib); 
	fputc(InternalSeparator, lib); 
	printf("Book language: "); 
	fgets(books->language, sizeof books->language,stdin); //fgets creates a dent in the file, i.e new line
	fputs(books->language, lib);  
	
	printf("Following book added to library: \n"); //Confirmation to the user that the book has been added
	printf("%s\t",books->title);
	printf(" By %s\t\n",books->author);
}

void ViewList (FILE *view){ //View the list of books, only input paramter needed is the file becaue we don't need to use the struct
	char filecontent[1000000]; //content holder variable
	int i=1; //For ui purposes
	printf("Book title | Book author | Book genre | Section | Language\n\n");
	while(fscanf(view, "%s",filecontent)!=EOF){ //scan and loop the lines until the end of file (EOF) has been reached
		printf("%d. %s\n\n",i,filecontent); //print according to the following print statement
		i++; //increment the counter 
		}
		printf("In total %d books available in library \n", i-1);
}

void RemoveFile (FILE *remove){ // same as ViewList function, because we are clearing the file, only the file variable is needed
	char command; //a internal command key for RemoveFile function
	printf("This function will delete your library (press 'Y' to coninue, press 'N' to exit): ");
	scanf("%s", &command);
	if(command =='Y'){
		printf("Are you sure you wish to delete your library ('Y' - to delete, 'N' - to exit remove function):");
	scanf("%s",&command);
	}else{
		printf("Exited remove function\n"); 
	}
			if(command=='Y'){
				remove=fopen("LibraryFile.txt","w"); //Basically opens a new file but with the old filename, "w" write mode always clears anyfile and is filled only once, when exited the data if replaced, replaces old values. 
				//In our case we open it for "w" only once which clears all text, but doesn't allow to write anything within the R command hot key, only way to append a list is using 'A' 
				printf("Your library has been successfully deleted\n"); 
			}else{
		printf("Exited remove function\n"); 
	}
		}
	
	
	