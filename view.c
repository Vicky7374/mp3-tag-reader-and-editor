#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

// ANSI Color Codes


int check_extension_fun(char *argv[])
{
    int len = strlen(argv[2]);
    if (len < 5)
    {
        printf(BOLD_RED "\n[ERROR] INVALID MP3 FILE NAME\n" RESET);
        exit(FAILURE);
    }
    if (!(argv[2][len - 4] == '.' && argv[2][len - 3] == 'm' && argv[2][len - 2] == 'p' && argv[2][len - 1] == '3'))
    {
        printf(BOLD_RED "\n[ERROR] INVALID MP3 FILE NAME: EXTENSION MISSING\n" RESET);
        exit(FAILURE);
    }
    return 1; // if all ok
}

void viewfunction(char *argv[])
{
    CLEAR_SCREEN();
    // First check .mp3 extension present in given file name or not
    if (check_extension_fun(argv))
    {
        // all ok so do next process
    }
    
    FILE *fp = fopen(argv[2], "rb");
    if (fp == NULL)
    {
        printf(BOLD_RED "\n[ERROR] Cannot open file\n" RESET);
        return;
    }

    fseek(fp, 10, SEEK_SET);
    char tag[5];
    unsigned int size = 0, count = 0;

    printf(BOLD_CYAN "\n---------------------------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "                      MP3 TAG INFORMATION                            \n" RESET);
    printf(BOLD_CYAN "---------------------------------------------------------------------\n" RESET);

    while (count < 6)
    {
        if (fread(tag, 1, 4, fp) != 4) break; // End of file/tags safety check
        tag[4] = '\0';

        fread(&size, 4, 1, fp); // first store size which is in bigendians form

        char *ptr = (char *)&size;
        for (int i = 0; i < 2; i++) // bigendian to little
        {
            char temp = ptr[i];
            ptr[i] = ptr[4 - i - 1];
            ptr[4 - i - 1] = temp;
        }

        fseek(fp, 3, SEEK_CUR);

        char data[size];          // allocate correct size to include null-terminator
        fread(data, 1, size - 1, fp);
        data[size - 1] = '\0';    // Null-terminate the string for safe printing

        // Print aligned and colored tags
        if (strcmp(tag, "TIT2") == 0)
        {
            printf(BOLD_GREEN "%-10s : " RESET "%s\n", "Title", data);
            count++;
        }
        else if (strcmp(tag, "TYER") == 0)
        {
            printf(BOLD_GREEN "%-10s : " RESET "%s\n", "Year", data);
            count++;
        }
        else if (strcmp(tag, "TPE1") == 0)
        {
            printf(BOLD_GREEN "%-10s : " RESET "%s\n", "Artist", data);
            count++;
        }
        else if (strcmp(tag, "TALB") == 0)
        {
            printf(BOLD_GREEN "%-10s : " RESET "%s\n", "Album", data);
            count++;
        }
        else if (strcmp(tag, "TCON") == 0)
        {
            printf(BOLD_GREEN "%-10s : " RESET "%s\n", "Genre", data);
            count++;
        }
        else if (strcmp(tag, "COMM") == 0)
        {
            printf(BOLD_GREEN "%-10s : " RESET "%s\n", "Comment", data);
            count++;
        }
    }
    
    printf(BOLD_CYAN "---------------------------------------------------------------------\n\n" RESET);
    fclose(fp);
}

void helpfunction()
{
    CLEAR_SCREEN();
    printf(BOLD_CYAN "---------------------------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "                   Mp3 TAG Reader and Editor                       \n" RESET);
    printf(BOLD_CYAN "---------------------------------------------------------------------\n" RESET);
    
    printf(BOLD MAGENTA "Usage :" RESET " ./out [options] <changing_text> <filename.mp3>\n\n");
    
    printf(BOLD_GREEN "Options :\n" RESET);
    // %-16s aligns the description beautifully next to the options
    printf("  " YELLOW "%-16s" RESET " Display this help menu\n", "-h");
    printf("  " YELLOW "%-16s" RESET " View MP3 tags\n", "-v");
    printf("  " YELLOW "%-16s" RESET " Modify Title tag\n", "-e -t <value>");
    printf("  " YELLOW "%-16s" RESET " Modify Artist tag\n", "-e -a <value>");
    printf("  " YELLOW "%-16s" RESET " Modify Album tag\n", "-e -A <value>");
    printf("  " YELLOW "%-16s" RESET " Modify Year tag\n", "-e -y <value>");
    printf("  " YELLOW "%-16s" RESET " Modify Genre tag\n", "-e -g <value>");
    printf("  " YELLOW "%-16s" RESET " Modify Comment tag\n", "-e -c <value>");
    
    printf(BOLD_CYAN "---------------------------------------------------------------------\n" RESET);
}