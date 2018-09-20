//
//  main.c
//
//
//  Created by Ryan Nelson on 13/02/2016.
//  Modified 19/09/18
//  Copyright © 2016-2018 Ryan Nelson. All rights reserved.
//  Symbolic Link
//------------------------------------------------------------------------------------------//


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {

    // Prompt user
    printf("Symbolic Link generator By Ryan Nelson 2016\n");

    // Read the destination path specified in the SL.ini file
    FILE *fp;
    // Path of destination - Example:(/Users/Ryan/Dropbox)
    char *destPath = malloc( sizeof(char) * 1024 );
    size_t len = 0;
    ssize_t read;

    // ini file = SL.ini
    fp = fopen("SL.ini", "r");
    if (fp == NULL){
        printf("Error: File pointer is null (File not found).\n");
        exit(EXIT_FAILURE);
    }
    read = getline(&destPath, &len, fp);
    if (read == -1){
        printf("Error: Failure to read line from SL.ini\n");
        exit(EXIT_FAILURE);
    }

    // Failsafe to remove newline char from input file
    if( destPath[strlen(destPath)-1] == '\n' )
        destPath[strlen(destPath)-1] = 0;

    // Close file
    fclose(fp);
    
    // Prompt user
    printf("Destination path: %s\n", destPath);
    
    // String to store Symbolic link command no path
    char symbolicLinkCommand[7] = "ln -s";
    
    // Store pathname given via command line
    char inputPath[1024];
    printf("Enter source path: ");
    scanf("%s", inputPath);
    
    // Store the concatenated whole command + Malloc mem
    char *fullCommand = malloc( sizeof(char) * strlen(symbolicLinkCommand) + strlen(destPath) + strlen(inputPath) );
 
    // Write formatted data to string
    sprintf(fullCommand, "%s %s %s", symbolicLinkCommand, inputPath, destPath);

    // Execute Command
    system(fullCommand);
    
    // Success Printout
    printf("Successfully Created Symbolic Link\n");
    printf("Source: %s\nDestination: %s\n", inputPath, destPath);

    // Free memory
    free(destPath);
    free(fullCommand);
    
    return 0;
}
