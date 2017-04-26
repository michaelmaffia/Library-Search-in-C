/*
Library Search Service
Program Created by: Michael Maffia
*/

#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 40
#define MAX_BOOKS 100

//Book Structure
struct book {
    char title[MAX_LENGTH];
    char authorfname[MAX_LENGTH];
    char authorlname[MAX_LENGTH];
    int numcopies;
} bk;

//Function takes index number, and book struct to print all books by author.
void getBooksByIndex(int j, struct book bks[], int numbooks) {
    int i;
    //Scans the Array of Structs and compares the full names of the Author with set index.
    printf("Names of all Books by %s: \n", bks[j].authorfname);
    printf("----------------------\n");
    for (i = 0; i < numbooks; i++) {
        if (strcmp(bks[j].authorfname, bks[i].authorfname) == 0) {
            printf("%s \nTotal Copies: %d \n\n", bks[i].title, bks[i].numcopies);
        }
    }
    printf("---------------------- \n\n");
}

// Function searches Library by Author First and Last Name
void searchByAuthor(char search[], struct book bks[], int numbooks) {
    int i;
    int found = 0;
    char name[MAX_LENGTH];
    for (i = 0; i < numbooks; i++) {
        //Compares combined author name with user search.
        if (strcmp(search, bks[i].authorfname) == 0) {
            found = 1;
            printf("Good News! Your author has a book is in stock..\n\n");
            getBooksByIndex(i, bks, numbooks);
            break;
        }
    }
    //If no book is found, print.
    if (found == 0) {
        printf("Sorry, couldn't find a book.\n\n");
    }
}

// Function that processes a search by Title
void searchByTitle(char search[], struct book bks[], int numbooks) {
    int i;
    int found = 0;
    //Loop that scans the array of structs and compares each index to the user's search.
    for (i = 0; i < numbooks; i++) {
        if (strcmp(search, bks[i].title) == 0) {
            found = 1;
            printf("Good News! Your book has been found.\n");
            printf("There are %d copies of your book.\n\n", bks[i].numcopies);
            getBooksByIndex(i, bks, numbooks);
            break;
        }
    }
    // If no book is found, print.
    if (found == 0) {
        printf("Sorry, couldn't find a book.\n\n");
    }
}

// Function that takes a user search input, processes by type.
void userSearch(struct book bks[], int numbooks) {
    char choice;
    char search[MAX_LENGTH];
    char lastName[MAX_LENGTH];
    //Print Statements
    printf("Please Enter a Choice: \n");
    printf("---------------------- \n");
    printf("'a' to search by book title.\n");
    printf("'b' to search by author.\n");
    //Scan user choice to search
    scanf(" %c", &choice);
    //Search by Book Title
    if (choice == 'a' || choice == 'A') {
        printf("Enter the title of the book you want to search for? (Case Sensitive) \n");
        printf("Instead of a Space you must use '_' to separate words \n");
        scanf("%s", search);
        printf("\n");
        searchByTitle(search, bks, numbooks);
    }
    //Search by Author
    if (choice == 'b' || choice == 'B') {
        printf("All Entries are Case Sensitive!\n");
        printf("Enter the FIRST name of the Author you'd like to search for: \n");
        scanf("%s", search);
        printf("Enter the LAST name of the Author you'd like to search for: \n");
        scanf("%s", lastName);
        printf("\n");
        strcat(search, " ");
        strcat(search, lastName);
        searchByAuthor(search, bks, numbooks);
    }


}

// Main function. Populates an array of structs from text file. Executes program.
int main() {
    // Opens the input File.
    FILE *input = fopen("library.txt", "r");
    //Default Start Choice
    char choice = 'y';
    //Declared Vars used in loop
    int numBookNames, i;
    //Scan for Number of Book Names
    fscanf(input, "%d", &numBookNames);
    // Declares an Array of book structs.
    struct book bks[numBookNames];
    // Loop scans each line for Book Title, Author First and Last name, and Number.
    for (i = 0; i < numBookNames; i++) {
        fscanf(input, " %s %s %s %d", &bks[i].title, &bks[i].authorfname, &bks[i].authorlname, &bks[i].numcopies);
        //String function to combine author first and last names after scanning from input.
        strcat(bks[i].authorfname, " ");
        strcat(bks[i].authorfname, bks[i].authorlname);
    }
    // Do-while Loop that runs each time the program is run, asks user if they want to continue
    do {
        userSearch(bks, numBookNames);
        printf("Would you like to continue using the Library? \nEnter 'Y' or 'y' to Continue. \n");
        scanf("  %c", &choice);

    } while (choice == 'y');
    //End of Program Message.
    printf("Goodbye.\n");
    //Closes the input File
    fclose(input);
    return 0;
}