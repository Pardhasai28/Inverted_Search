#include "main.h"
int create_database(mainnode **arr, flist *fhead, int *created)
{
    printf(BBLUE "\nCreating Database...\n" RESET); // Database creation started
    while(fhead)
    {
        printf(BCYAN "Processing File : %s\n" RESET, fhead->fname); // Display current file name

        FILE *fp = fopen(fhead->fname, "r"); // Open file in read mode

        if(fp == NULL)
        {
            printf(RED "ERROR : Unable to open file %s\n" RESET, fhead->fname); // File open failure
            return FAILURE;
        }

        char str[100]; // Buffer to store words from file

        while(fscanf(fp, "%s", str) == 1) // Read words one by one
        {
            if(isalpha(str[0])) // Check whether first character is alphabet
            {
                int index = tolower(str[0]) - 'a'; // Calculate index from a-z

                mainnode *node = insert_first_mainnode(&arr[index], str, fhead->fname); // Insert/search main node

                if(node != NULL)
                {
                    insert_first_subnode(node, fhead->fname); // Insert/update subnode
                }
            }
            else
            {
                int index = 26; // Special index for symbols/numbers

                mainnode *node = insert_first_mainnode(&arr[index], str, fhead->fname); // Insert/search main node

                if(node != NULL)
                {
                    insert_first_subnode(node, fhead->fname); // Insert/update subnode
                }
            }
        }

        fclose(fp); // Close current file
        fhead = fhead->link; // Move to next file
    }

    *created = 1; // Mark database as created
    return SUCCESS;
}

mainnode *insert_first_mainnode(mainnode **address, char word[], char fileaddress[])
{
    if(*address == NULL) // If no node exists at index
    {
        *address = (mainnode *)malloc(sizeof(mainnode)); // Allocate memory for main node

        if(*address == NULL)
        {
            printf(RED "Memory Allocation Failed For Mainnode\n" RESET); // Allocation failure
            return NULL;
        }

        strcpy((*address)->word, word); // Copy word into node
        (*address)->f_count = 0; // Initialize file count
        (*address)->mainlink = NULL; // Initialize next pointer
        (*address)->sublink = NULL; // Initialize subnode pointer
    }
    else
    {
        mainnode *temp = *address; // Temporary pointer for traversal

        while(temp != NULL)
        {
            if(strcmp(temp->word, word) == 0) // Word already exists
            {
                return temp; // Return existing node
            }

            temp = temp->mainlink; // Move to next node
        }

        mainnode *new = (mainnode *)malloc(sizeof(mainnode)); // Allocate new node

        if(new == NULL)
        {
            printf(RED "Memory Allocation Failed For Mainnode\n" RESET); // Allocation failure
            return NULL;
        }

        strcpy(new->word, word); // Store word
        new->f_count = 0; // Initialize file count
        new->sublink = NULL; // Initialize sublink
        new->mainlink = *address; // Insert at beginning

        *address = new; // Update head pointer
        return new;
    }
}

int insert_first_subnode(mainnode *node, char fileaddress[])
{
    if(node == NULL)
    {
        printf(RED "Invalid Mainnode\n" RESET); // Invalid node check
        return FAILURE;
    }

    if(node->sublink == NULL) // If no subnode exists
    {
        subnode *new = (subnode *)malloc(sizeof(subnode)); // Allocate memory

        if(new == NULL)
        {
            printf(RED "Memory Allocation Failed For Subnode\n" RESET); // Allocation failure
            return FAILURE;
        }

        strcpy(new->f_name, fileaddress); // Store filename
        new->w_count = 1; // Initialize word count
        new->nextsub = NULL; // Initialize next pointer

        node->sublink = new; // Attach subnode
        node->f_count++; // Increment file count
        return SUCCESS;
    }
    else
    {
        subnode *temp = node->sublink; // Traverse subnodes

        while(temp != NULL)
        {
            if(strcmp(temp->f_name, fileaddress) == 0) // File already exists
            {
                temp->w_count++; // Increment word count
                return SUCCESS;
            }

            temp = temp->nextsub; // Move to next subnode
        }

        subnode *new = (subnode *)malloc(sizeof(subnode)); // Allocate memory

        if(new == NULL)
        {
            printf(RED "Memory Allocation Failed For Subnode\n" RESET); // Allocation failure
            return FAILURE;
        }

        strcpy(new->f_name, fileaddress); // Store filename
        new->w_count = 1; // Initialize word count

        new->nextsub = node->sublink; // Insert at beginning
        node->sublink = new; // Update sublink

        node->f_count++; // Increment file count
        return SUCCESS;
    }
}