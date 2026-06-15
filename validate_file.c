#include"main.h"
int validate_backup_file(FILE *fp)
{
    int index, f_count, w_count;
    char word[50], fname[50];
    char ch;

    rewind(fp);

    while (1)
    {
        // MUST start with '#'
        if (fscanf(fp, "%c", &ch) != 1)
            break;   // EOF

        if (ch != '#')
        {
            printf("Missing starting #\n");
            return FAILURE;
        }

        // read index
        if (fscanf(fp, "%d", &index) != 1)
        {   
            printf("index missing\n");
            return FAILURE;
        }
        // MUST have ';'
        if (fscanf(fp, "%c", &ch) != 1 || ch != ';')
        {
            printf("Missing ';' after index\n");
            return FAILURE;
        }

        if (index < 0 || index > 26)
            return FAILURE;

        // read word
        if (fscanf(fp, "%49[^;]", word) != 1)
            return FAILURE;

        // MUST have ';'
        if (fscanf(fp, "%c", &ch) != 1 || ch != ';')
        {
            printf("Missing ';' after word\n");
            return FAILURE;
        }

        if (strlen(word) == 0)
            return FAILURE;

        // read file count
        if (fscanf(fp, "%d", &f_count) != 1)
            return FAILURE;

        //  MUST have ';'
        if (fscanf(fp, "%c", &ch) != 1 || ch != ';')
        {
            printf("Missing ';' after file count\n");
            return FAILURE;
        }

        if (f_count <= 0)
            return FAILURE;

        //  read subnodes
        for (int i = 0; i < f_count; i++)
        {
            // filename
            if (fscanf(fp, "%49[^;]", fname) != 1)
                return FAILURE;

            if (validate_txt(fname) == FAILURE)
                return FAILURE;

            // must have ';'
            if (fscanf(fp, "%c", &ch) != 1 || ch != ';')
            {
                printf("Missing ';' after filename\n");
                return FAILURE;
            }

            // word count
            if (fscanf(fp, "%d", &w_count) != 1)
                return FAILURE;

            if (w_count <= 0)
                return FAILURE;

            // must have ';'
            if (fscanf(fp, "%c", &ch) != 1 || ch != ';')
            {
                printf("Missing ';' after word count\n");
                return FAILURE;
            }
        }

        //  MUST end with '#'
        if (fscanf(fp, "%c", &ch) != 1 || ch != '#')
        {
            printf("Missing ending #\n");
            return FAILURE;
        }

        // skip newline (optional)
        fscanf(fp, "\n");
    }
    
    rewind(fp);
    return SUCCESS;
}