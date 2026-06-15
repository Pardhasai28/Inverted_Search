#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define SUCCESS 1
#define FAILURE 0

#define RED       "\033[1;31m"
#define RESET     "\033[0m"
#define GREEN     "\033[1;32m"
#define BBLUE     "\033[1;94m"
#define BCYAN     "\033[1;96m"
#define BMAGENTA  "\033[1;95m"
#define ORANGE    "\033[38;5;208m"
#define YELLOW    "\033[1;33m"

typedef struct filename
{
    char *fname;
    struct filename *link;
}flist;
typedef struct sub
{
    char f_name[50];
    int w_count;
    struct sub *nextsub;
}subnode;
typedef struct mainn
{
    char word[100];
    int f_count;
    subnode *sublink;
    struct mainn *mainlink;
}mainnode;
int validate_argv(char *argv[],flist **fhead);
int validate_txt(char arr[]);
int check_exist(char arr[]);
int check_duplicate(char arr[],flist *fdd);
int create_database(mainnode **arr,flist *fhead,int *created);
mainnode * insert_first_mainnode(mainnode **address,char word[],char fileaddress[]);
int insert_first_subnode(mainnode *address,char fileaddress[]);
int display_database(mainnode **arr);
int search_database(mainnode **arr,char word[]);
int save_database(mainnode **arr,flist *fhead);
int check_file_empty(FILE *fp);
int update_database(mainnode **arr,int *,flist **);
void insert_flist(flist **head, char *name);
int delete_duplicates(flist **fhead, flist *uhead);
int validate_backup_file(FILE *fp);