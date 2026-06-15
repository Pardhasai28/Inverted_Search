/*
Name : V.PARDHA SAI(25040_056)
Date : 17/05/2026
Description : 
main : Controls the complete flow of the Inverted Search project by validating files, displaying the menu, and calling database operations like create, display, search, save, and update.

validate_argv : Validates all command line arguments by checking file format, existence, emptiness, and duplicates before adding them to the file linked list.

validate_txt : Checks whether the given file has a valid .txt extension.

check_exist : Verifies whether the file exists and ensures that the file is not empty.

check_duplicate : Checks whether the given filename is already present in the linked list to avoid duplicate entries.

create_database : Reads words from all valid files and creates the inverted search database using hash indexing and linked lists.

display_database : Displays the complete database contents in a structured tabular format showing words, file count, filenames, and word counts.

search_database : Searches for a specific word in the database and displays the files where the word is present along with occurrence counts.

save_database : Stores the complete database into a backup text file so that it can be reused later without recreating the database.

update_database : Restores the database contents from a previously saved backup file into memory.*/


#include "main.h"

int main(int argc, char *argv[])
{
    mainnode *arr[27]; // Array of mainnode pointers

    for (int i = 0; i < 27; i++)
    {
        arr[i] = NULL; // Initialize all indexes to NULL
    }

    flist *fhead = NULL; // Head pointer for file linked list
    flist *uhead; // Head pointer for updated files list

    if(argc < 2) // Check minimum arguments
    {
        printf(RED "\nERROR : Insufficient Arguments\n" RESET); // Error heading
        printf(YELLOW "\nUSAGE :\n" RESET); // Usage heading
        printf(BCYAN "./result.exe file1.txt file2.txt file3.txt ...etc\n" RESET); // Proper command format
        printf(ORANGE "\nEXAMPLE :\n" RESET); // Example heading
        printf(GREEN "./result.exe f1.txt f2.txt\n\n" RESET); // Example command
        return FAILURE;
    }

    if(validate_argv(argv, &fhead) == FAILURE) // Validate command line arguments
    {
        printf(RED "Validation Failed\n" RESET); // Validation failure message
        return FAILURE;
    }

    int created = 0, updated = 0; // Flags for database status

    while(1)
    {
        printf(BBLUE "\n================== MENU ==================\n" RESET); // Menu heading

        printf(YELLOW "1. Create Database\n" RESET); // Menu option 1
        printf(YELLOW "2. Display Database\n" RESET); // Menu option 2
        printf(YELLOW "3. Search Database\n" RESET); // Menu option 3
        printf(YELLOW "4. Save Database\n" RESET); // Menu option 4
        printf(YELLOW "5. Update Database\n" RESET); // Menu option 5
        printf(YELLOW "6. Exit\n" RESET); // Menu option 6

        printf(ORANGE "\nEnter Your Choice : " RESET); // Prompt for choice

        int option; // Variable to store user option
        scanf("%d", &option);

        switch(option)
        {
            case 1:
            {
                if(fhead == NULL) // Check whether valid files exist
                {
                    printf(RED "There Are No Valid Files\n" RESET); // No files message
                    break;
                }

                if(created == 1) // Database already created check
                {
                    printf(RED "Database Is Already Created\n" RESET); // Already created message
                    break;
                }

                if(updated == 1) // Remove duplicates after update
                {
                    delete_duplicates(&fhead, uhead); // Delete duplicate files
                }

                if(create_database(arr, fhead, &created) == FAILURE) // Create database
                {
                    printf(RED "Creating Database Failed\n" RESET); // Failure message
                }
                else
                {
                    printf(GREEN "\nDatabase Created Successfully\n" RESET); // Success message
                }

                break;
            }

            case 2:
            {
                if(created == 0 && updated == 0) // Database existence check
                {
                    printf(RED "Database Is Not Created Yet\n" RESET); // Error message
                    printf(YELLOW "First Create Or Update Database\n" RESET); // Suggestion
                    break;
                }

                printf(BMAGENTA "\nDisplaying Database...\n" RESET); // Display heading

                display_database(arr); // Display database contents

                break;
            }

            case 3:
            {
                if(created == 0 && updated == 0) // Database existence check
                {
                    printf(RED "Database Is Not Created Yet\n" RESET); // Error message
                    printf(YELLOW "First Create Or Update Database\n" RESET); // Suggestion
                    break;
                }

                char word[20]; // Buffer for search word

                printf(ORANGE "Enter The Word You Have To Search : " RESET); // Input prompt
                scanf("%s", word);

                if(search_database(arr, word) == FAILURE) // Search operation
                {
                    printf(RED "%s Is Not Found In The Database\n" RESET, word); // Not found message
                }
                

                break;
            }

            case 4:
            {
                if(created == 0 && updated == 0) // Database existence check
                {
                    printf(RED "Database Is Not Created Yet\n" RESET); // Error message
                    printf(YELLOW "First Create Or Update Database\n" RESET); // Suggestion
                    break;
                }

                printf(BMAGENTA "\nSaving Database...\n" RESET); // Save heading

                save_database(arr, fhead); // Save database into file

                printf(GREEN "Database Saved Successfully\n" RESET); // Save success message

                break;
            }

            case 5:
            {
                if(created == 1 || updated==1) // Check if database already created
                {
                    printf(RED "Database Is Already Created\n" RESET); // Already created message
                    break;
                }

                printf(BMAGENTA "\nUpdating Database...\n" RESET); // Update heading

                if(update_database(arr, &updated, &uhead) == FAILURE) // Update database
                {
                    updated = 0; // Reset update flag

                    printf(RED "Database Update Failed\n" RESET); // Failure message
                }
                else
                {
                    printf(GREEN "Database Updated Successfully\n" RESET); // Success message
                }

                break;
            }

            case 6:
            {
                printf(GREEN "\nExiting Program...\n" RESET); // Exit message
                return SUCCESS;
            }

            default:
            {
                printf(RED "Invalid Choice\n" RESET); // Invalid option message
            }
        }
    }
}