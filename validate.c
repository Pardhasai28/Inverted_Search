#include "main.h"

int validate_argv(char *argv[], flist **fhead)
{
    int i = 1; // Start from first command line argument

    while(argv[i])
    {
        printf(BBLUE "\nChecking File : %s\n" RESET, argv[i]); // Display current file

        if(validate_txt(argv[i]) == SUCCESS) // Validate .txt extension
        {
            if(check_exist(argv[i]) == SUCCESS) // Check file existence and emptiness
            {
                if(check_duplicate(argv[i], *fhead) == SUCCESS) // Check duplicate file
                {
                    flist *new = (flist *)malloc(sizeof(flist)); // Allocate memory for file node

                    if(new == NULL)
                    {
                        printf(RED "Memory Allocation Failed\n" RESET); // Allocation failure
                        return FAILURE;
                    }

                    new->fname = argv[i]; // Store filename
                    new->link = NULL; // Initialize link

                    if(*fhead == NULL) // Insert first node
                    {
                        *fhead = new;
                    }
                    else
                    {
                        new->link = *fhead; // Insert at beginning
                        *fhead = new;
                    }

                    printf(GREEN "%s Added Successfully\n" RESET, argv[i]); // Success message
                }
            }
        }

        i++; // Move to next argument
    }

    return SUCCESS;
}

int validate_txt(char arr[])
{
    char *p = strstr(arr, "."); // Find extension

    if(p == NULL || strcmp(p, ".txt") != 0) // Check for .txt extension
    {
        printf(RED "%s Is Not In Correct File Format\n" RESET, arr); // Invalid format message
        return FAILURE;
    }
    return SUCCESS;
}

int check_exist(char arr[])
{
    FILE *fp = fopen(arr, "r"); // Open file in read mode

    if(fp == NULL)
    {
        printf(RED "%s Does Not Exist\n" RESET, arr); // File missing message
        return FAILURE;
    }

    fseek(fp, 0, SEEK_END); // Move file pointer to end

    if(ftell(fp) == 0) // Check file size
    {
        printf(YELLOW "%s Is Empty\n" RESET, arr); // Empty file warning

        fclose(fp); // Close file

        return FAILURE;
    }

    fclose(fp); // Close file after validation
    return SUCCESS;
}

int check_duplicate(char arr[], flist *fdd)
{
    if(fdd == NULL) // No nodes present
    {
        return SUCCESS;
    }

    while(fdd)
    {
        if(strcmp(fdd->fname, arr) == 0) // Duplicate file check
        {
            printf(ORANGE "%s Already Present In List\n" RESET, arr); // Duplicate detected

            return FAILURE;
        }

        fdd = fdd->link; // Move to next node
    }

    return SUCCESS; // No duplicate found
}