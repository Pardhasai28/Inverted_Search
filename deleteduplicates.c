#include"main.h"
int delete_duplicates(flist **fhead, flist *uhead)
{
    while(uhead != NULL)
    {
        flist *temp = *fhead;
        flist *prev = NULL;

        while(temp != NULL)
        {
            if(strcmp(temp->fname, uhead->fname) == 0)
            {
                // delete node
                if(prev == NULL)   // first node
                {
                    *fhead = temp->link;
                    free(temp);          // ✅ only free node
                    temp = *fhead;
                }
                else
                {
                    prev->link = temp->link;
                    free(temp);          // ✅ only free node
                    temp = prev->link;
                }
            }
            else
            {
                prev = temp;
                temp = temp->link;
            }
        }

        uhead = uhead->link;
    }
    return SUCCESS;
}