#include "main.h"

int display_database(mainnode **arr)
{
    printf(BBLUE "\n========================= DATABASE CONTENTS =========================\n\n" RESET); // Database heading

    printf(BCYAN "=====================================================================================================\n" RESET);

    printf(YELLOW "%-8s %-20s %-12s %-25s %-10s\n" RESET,
           "Index", "Word", "FileCount", "FileName", "WordCount"); // Table headings

    printf(BCYAN "=====================================================================================================\n" RESET);

    for(int i = 0; i < 27; i++) // Traverse all hash indexes
    {
        mainnode *temp = arr[i]; // Temporary pointer for mainnodes

        while(temp != NULL) // Traverse mainnode linked list
        {
            subnode *subtemp = temp->sublink; // Temporary pointer for subnodes

            int first = 1; // Flag for first row printing

            while(subtemp != NULL) // Traverse subnode linked list
            {
                if(first) // Print full row for first subnode
                {
                    printf(GREEN "%-8d %-20s %-12d " RESET
                           ORANGE "%-25s %-10d\n" RESET,
                           i,
                           temp->word,
                           temp->f_count,
                           subtemp->f_name,
                           subtemp->w_count);

                    first = 0; // Reset flag after first print
                }
                else // Print only subnode details for remaining rows
                {
                    printf("%-8s %-20s %-12s "
                           ORANGE "%-25s %-10d\n" RESET,
                           "",
                           "",
                           "",
                           subtemp->f_name,
                           subtemp->w_count);
                }

                subtemp = subtemp->nextsub; // Move to next subnode
            }

            printf(BCYAN "-----------------------------------------------------------------------------------------------------\n" RESET); // Row separator

            temp = temp->mainlink; // Move to next mainnode
        }
    }

    printf(GREEN "\nDatabase Display Completed Successfully\n" RESET); // Completion message

    return SUCCESS;
}