#include <stdio.h>
#include <string.h>
#include "header.h"


int main(int argc,char* argv[]) 
{
    int choice;
    if(argc==1)
    {
        CLEAR_SCREEN();
        printf("-------------------------------------------------------------------");
        printf(BOLD_RED"\nERROR: ./a.out : INVALID ARGUMENTS"RESET);
        printf(BOLD_GREEN"\nUSAGE : "RESET);
        printf("\nTo view please pass like: ./a.out -v mp3filename");
        printf("\nTo edit please pass like : ./a.out -e -t/-a/-A/-y/-g/-c changing_text mp3filename");
        printf("\nTo get help pass like : ./a.out --help");
        printf("\n------------------------------------------------------------------\n");
        return 0;
    }
    if(strcmp(argv[1],"-v")==0)
    {
        viewfunction(argv);
    }
    else if(strcmp(argv[1],"--help")==0)
    {
        helpfunction();
    }
    else if(strcmp(argv[1],"-e")==0)
    {
        editfunction(argv);
    }else
    {
        printf("\nERROR: ./a.out : INVALID ARGUMENTS\n");
    }
    return 0;
}
