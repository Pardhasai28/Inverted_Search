#include "main.h"

int update_database(mainnode **arr, int *created, flist **uhead)
{
    *uhead = NULL; // Initialize updated file list

    char filename[50]; // Buffer to store database filename

    printf(BBLUE "\nEnter The Database File Name : " RESET); // Input prompt

failure:

    scanf("%s", filename); // Read filename from user

    if(check_exist(filename) == FAILURE) // Check whether file exists
    {

        printf(YELLOW "Please Enter A Valid File Name : " RESET); // Retry prompt

        goto failure; // Retry input
    }

    FILE *fp = fopen(filename, "r"); // Open backup file

    if(fp == NULL)
    {
        printf(RED "Failed To Open File\n" RESET); // File open failure
        return FAILURE;
    }

    if(check_file_empty(fp) == 0) // Check whether file is empty
    {
        printf(RED "File Is Empty\n" RESET); // Empty file message

        fclose(fp); // Close file

        goto failure; // Retry input
    }

    if(validate_backup_file(fp) == FAILURE) // Validate backup file format
    {
        printf(RED "Updating Database Failed\n" RESET); // Validation failure
        return FAILURE;
    }

    printf(GREEN "\nBackup File Validation Successful\n" RESET); // Validation success

    fseek(fp, 0, SEEK_SET); // Reset file pointer to beginning

    int index; // Variable to store hash index

    while(fscanf(fp, "#%d;", &index) == 1) // Read index from backup file
    {
        mainnode *new = malloc(sizeof(mainnode)); // Allocate memory for mainnode

        if(new == NULL)
        {
            printf(RED "Memory Allocation Failed For Mainnode\n" RESET); // Allocation failure

            fclose(fp);

            return FAILURE;
        }

        new->sublink = NULL; // Initialize sublink
        new->mainlink = NULL; // Initialize mainlink

        fscanf(fp, "%[^;];%d;", new->word, &new->f_count); // Read word and file count
        if(arr[index] == NULL) // Insert first node at index
        {
            arr[index] = new;
        }
        else
        {
            mainnode *temp = arr[index]; // Traverse existing nodes

            while(temp->mainlink != NULL)
            {
                temp = temp->mainlink;
            }

            temp->mainlink = new; // Attach new node at end
        }

        for(int i = 0; i < new->f_count; i++) // Read all subnodes
        {
            subnode *newsub = malloc(sizeof(subnode)); // Allocate memory for subnode

            if(newsub == NULL)
            {
                printf(RED "Memory Allocation Failed For Subnode\n" RESET); // Allocation failure

                fclose(fp);

                return FAILURE;
            }

            newsub->nextsub = NULL; // Initialize next pointer

            fscanf(fp, "%[^;];%d;", newsub->f_name, &newsub->w_count); // Read filename and count

            insert_flist(uhead, newsub->f_name); // Store filename in updated list

            if(new->sublink == NULL) // Insert first subnode
            {
                new->sublink = newsub;
            }
            else
            {
                subnode *temp = new->sublink; // Traverse subnodes

                while(temp->nextsub != NULL)
                {
                    temp = temp->nextsub;
                }

                temp->nextsub = newsub; // Attach subnode at end
            }
        }

        fscanf(fp, "#\n"); // Skip ending delimiter
    }

    fclose(fp); // Close backup file

    *created = 1; // Mark database as updated

    return SUCCESS;
}

void insert_flist(flist **head, char *name)
{
    if(check_duplicate(name, *head) == FAILURE) // Check duplicate filename
    {
        return;
    }

    flist *new = malloc(sizeof(flist)); // Allocate memory for file node

    if(new == NULL)
    {
        printf(RED "Memory Allocation Failed For File List\n" RESET); // Allocation failure
        return;
    }

    new->fname = malloc(strlen(name) + 1); // Allocate memory for filename

    if(new->fname == NULL)
    {
        printf(RED "Memory Allocation Failed For Filename\n" RESET); // Allocation failure

        free(new);

        return;
    }

    strcpy(new->fname, name); // Copy filename

    new->link = NULL; // Initialize link

    if(*head == NULL) // Insert first node
    {
        *head = new;
    }
    else
    {
        flist *temp = *head; // Traverse file list

        while(temp->link)
        {
            temp = temp->link;
        }

        temp->link = new; // Attach new node
    }
}