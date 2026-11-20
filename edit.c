#include<stdio.h>
#include<string.h>
#include "header.h"
#include <errno.h>
#include <stdlib.h>
void target_tag_fun(char *argv[],char target_tag[])
{
    if (strcmp(argv[2], "-t") == 0) 
    {
        strcpy(target_tag, "TIT2"); // Title tag
    }
    else if (strcmp(argv[2], "-a") == 0)
    {
        strcpy(target_tag, "TPE1"); // Artist tag
    }
    else if (strcmp(argv[2], "-A") == 0)
    {
        strcpy(target_tag, "TALB"); // song album tag
    }
    else if (strcmp(argv[2], "-c") == 0)
    {
        strcpy(target_tag, "COMM"); // comment tag
    }
    else if (strcmp(argv[2], "-g") == 0)
    {
        strcpy(target_tag, "TCON"); // Song genre tag
    }
    else if (strcmp(argv[2], "-y") == 0)
    {
        strcpy(target_tag, "TYER"); // year tag
    }else
    {
        printf("\nINVALID TAG\n");
        exit(FAILURE);//close program
    }
    target_tag[4]='\0';
    return;
}
int check_extension_func(char *argv[])
{
    if(argv[4]==NULL)
    {
        printf("\nFILE NAME NOT PRESENT\n");
        exit(FAILURE);
    }
    int len=strlen(argv[4]);
    if(len<5)
    {
        printf("\nINVALID MP3 FILE NAME");
        exit(FAILURE);
    }
    if(!(argv[4][len-4]=='.' && argv[4][len-3]=='m' && argv[4][len-2]=='p' && argv[4][len-1]=='3'))
    {
        printf("\nINVALID MP3 FILE NAME (EXTENSION MISSING)\n");
        exit(FAILURE);
    }
    return 1; // if all ok
}
void editfunction(char *argv[])
{
    char target_tag[5];
    target_tag_fun(argv,target_tag);
    //first check .mp3 extension present in given file name or not
    if(check_extension_func(argv))
    {
        //all ok so do next process
    }
    FILE* fp = fopen(argv[4], "rb");
    FILE* fp2 = fopen("temp.mp3", "wb");
    if (fp == NULL || fp2 == NULL)
    {
        perror("\nError opening file\n"); // This prints the EXACT system reason (e.g., "No such file or directory")
        if (fp) fclose(fp);
        return;
    }
    // Write Header
    char header_buffer[10];
    fread(header_buffer, 1, 10, fp);
    fwrite(header_buffer, 1, 10, fp2);
    char tag[5];
    unsigned int size=0;
    
    char flag[2];
    char choice;
    while(1){

    //Break if we fail to read 4 bytes or hit padding(empty spaces) (null bytes)
    if (fread(tag, 1, 4, fp) != 4 || tag[0] == '\0') {
            if (tag[0] == '\0') {
                fseek(fp, -4, SEEK_CUR); // Step back to copy empty space also properly
            }
            break; 
        }
    tag[4]='\0';

    
    
    
    fread(&size,4,1,fp);    // first store size of data which is in bigendians form

    
    char* ptr=(char*)&size;
    for(int i=0;i<2;i++)        // bigendian to little
    {
        char temp=ptr[i];
        ptr[i]=ptr[4-i-1];
        ptr[4-i-1]=temp;
    }
    
    fread(flag,1,2,fp);   // reading flag

    char data[size];      //creating memory for data
       
    fread(data, 1, size, fp); //storing data from file
    
    if(strcmp(tag,target_tag)==0)// if tag is eqaul to given tag
    {
       
        fwrite(tag,1,4,fp2);   //writing the tag as it is
        
        unsigned int size_=(strlen(argv[3])+1); // +1 for starting null character
       
        char* ptr1=(char*)&size_;
        for(int i=0;i<2;i++)        // little to big
        {
            char temp=ptr1[i];
            ptr1[i]=ptr1[4-i-1];
            ptr1[4-i-1]=temp;
        }
        
            fwrite(&size_, 4, 1, fp2);
            fwrite(flag, 1, 2, fp2);  //writing the flag as it is
            
            // (1 byte text encoding + string data)
            char encoding = 0x00; 
            fwrite(&encoding, 1, 1, fp2);
            fwrite(argv[3], 1, strlen(argv[3]), fp2);//writing data given by user
            
            break; //task done so break and copy the remaining things
    }else
    {
        //if given tag not matched with song tag then copy the fetched data as it is. 
        fwrite(tag,1,4,fp2);  
        
            unsigned int little_endian_size = size;// keeping record of little endian size
                                                  // so we can use while writing data
            for(int i = 0; i < 2; i++) // Convert size back to Big Endian
            {
                char temp = ptr[i];
                ptr[i] = ptr[4 - i - 1];
                ptr[4 - i - 1] = temp;
            }
        fwrite(&size, 4, 1, fp2);
        fwrite(flag,1,2,fp2);
        fwrite(data,1,little_endian_size,fp2);
        
    }
 }
 
char buffer[1000]; // creating temporary buffer for data copy
size_t bytes_read; // variable for keep count for read data byte

// we must separate the reading and writing steps
while ((bytes_read=fread(buffer,1,sizeof(buffer), fp))>0) {
    fwrite(buffer,1,bytes_read,fp2);
}

fclose(fp);
fclose(fp2);

remove(argv[4]);
rename("temp.mp3",argv[4]);

      
}