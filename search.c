#include "main.h"

int search_database(mainnode **arr, char word[])
{
    int index = 0; // Variable to store hash index

    if(isalpha(word[0])) // Check whether first character is alphabet
    {
        index = tolower(word[0]) - 'a'; // Calculate index from a-z
    }
    else
    {
        index = 26; // Special index for symbols/numbers
    }

    printf(BBLUE "\nSearching For Word : %s\n" RESET, word); // Search heading

    mainnode *temp = arr[index]; // Get corresponding index node

    if(temp == NULL) // No node present at index
    {

        return FAILURE;
    }

    while(temp != NULL) // Traverse mainnode linked list
    {
        if(strcmp(word, temp->word) == 0) // Word found
        {
            printf(GREEN "\n%s Is Found In The Database\n" RESET, word); // Success message


            printf(BCYAN "\n================ WORD DETAILS ================\n" RESET); // Details heading

            subnode *subtemp = temp->sublink; // Traverse subnode list

            while(subtemp != NULL)
            {
                printf(ORANGE "%-20s -> %-20s : %-5d Times\n" RESET,
                       temp->word,
                       subtemp->f_name,
                       subtemp->w_count); // Display file and word count

                subtemp = subtemp->nextsub; // Move to next subnode
            }

            printf(BCYAN "================================================\n" RESET); // Footer line

            return SUCCESS;
        }

        temp = temp->mainlink; // Move to next mainnode
    }

    printf(RED "\n%s Is Not Found In Database\n" RESET, word); // Word not found message

    return FAILURE;
}