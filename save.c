#include "main.h"

int save_database(mainnode **arr, flist *fhead)
{
    printf(BBLUE "\nEnter The Filename To Save Database : " RESET); // Input prompt

    char filename[50]; // Buffer to store filename

failure:

    scanf("%s", filename); // Read filename

    if(validate_txt(filename) == FAILURE) // Validate .txt extension
    {
        printf(RED "Please Enter Valid .txt Filename\n" RESET); // Invalid format message

        goto failure; // Retry input
    }

    if(check_duplicate(filename, fhead) == FAILURE) // Check if filename already exists in database
    {
        printf(RED "This File Is Present In The Database\n" RESET); // Duplicate filename message

        printf(YELLOW "Please Enter New Filename\n" RESET); // Retry prompt

        goto failure; // Retry input
    }

    FILE *fp = fopen(filename, "r"); // Open file in read mode

    if(fp != NULL && check_file_empty(fp) != 0) // Check whether file is non-empty
    {
        printf(ORANGE "\nFile Is Not Empty\n" RESET); // File not empty message

        printf(YELLOW "1. Create New File\n" RESET); // Option 1
        printf(YELLOW "2. Overwrite Existing File\n" RESET); // Option 2

        printf(BCYAN "\nEnter Your Choice : " RESET); // Choice prompt

        int option; // Variable to store option

        scanf("%d", &option);

        fclose(fp); // Close file

        if(option == 1)
        {
            goto failure; // Ask for another filename
        }
    }
    else if(fp != NULL)
    {
        fclose(fp); // Close empty file
    }

    fp = fopen(filename, "w"); // Open file in write mode

    if(fp == NULL)
    {
        printf(RED "Failed To Open File In Write Mode\n" RESET); // File open failure

        return FAILURE;
    }

    printf(GREEN "\nSaving Database...\n" RESET); // Saving process started

    for(int i = 0; i < 27; i++) // Traverse hash table indexes
    {
        mainnode *temp = arr[i];

        while(temp != NULL) // Traverse mainnodes
        {
            fprintf(fp, "#%d;%s;%d;", i, temp->word, temp->f_count); // Store mainnode data
            subnode *subtemp = temp->sublink;

            while(subtemp != NULL) // Traverse subnodes
            {
                fprintf(fp, "%s;%d;", subtemp->f_name, subtemp->w_count); // Store subnode data


                subtemp = subtemp->nextsub;
            }

            fprintf(fp, "#\n"); // End of one record

            temp = temp->mainlink; // Move to next mainnode
        }
    }

    fclose(fp); // Close saved file

    printf(GREEN "\nDatabase Saved Successfully Into %s\n" RESET, filename); // Success message

    return SUCCESS;
}

int check_file_empty(FILE *fp)
{
    fseek(fp, 0, SEEK_END); // Move pointer to end of file

    long size = ftell(fp); // Get file size

    return size; // Return file size
}