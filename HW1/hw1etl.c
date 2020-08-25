/// Jensly Francisco
/// COP 3502C
/// 6/1/17

// Preprocessors Directives
#include <stdio.h>
#include <stdlib.h> // exit() is here
#include <string.h>
#include "airPdata.h"

#define DATA 50

// Function Prototype
void PrintData (airPdata *airport);

int main(int argc, char **argv)
{
    char filename[21];
    char buffer[8773];  // Word Count for florida_out.txt (largest file) is 8772 + 1 for null terminator
    char *tok;
    const char c[2] = ",";
    int i = 0;

    // Check For Arguments
    if (argc != 2)
    {
        printf("ERROR: We need 2 arguments, you inputted the following: \n");

        for (i = 0; i < argc; i++)
        {
           printf("argc[%d] = %s\n", i, argv[i]);
        }
    }

    else
    {
        // Declare struct and allocate memory to it
        airPdata *a = malloc(sizeof(airPdata));

        // Initialize variables in struct
        a ->siteNumber = malloc(sizeof(char) * (DATA + 1));
        a ->LocID = malloc(sizeof(char) * (DATA + 1));
        a ->fieldName = malloc(sizeof(char) * (DATA + 1));
        a ->city = malloc(sizeof(char) * (DATA + 1));
        a ->state = malloc(sizeof(char) * (DATA + 1));
        a ->latitude = malloc(sizeof(char) * (DATA + 1));
        a ->longitude = malloc(sizeof(char) * (DATA + 1));
        /// Control Tower is a Y/N question (also only member that's not a pointer)

        // Declaring file pointer
        FILE *ifp = NULL;

        // Variable to store name of input file in case I need to print error messages about the file
        strncpy(filename, argv[1], 21);

        // Check for NULL file
        if ((ifp = fopen(filename, "r")) == NULL)
        {
            fprintf(stderr, "etl ERROR: File %s not found\n", filename);
            exit(0);
        }

        // Print Header
        printf("%-12s %-11s %-42s %-34s %-3s %-15s %-16s Tower\n",
               "FAA Site", "Short Name", "Airport Name", "City", "ST",
               "Latitude", "Longitude");

        printf("%-12s %-11s %-42s %-34s %-3s %-15s %-16s =====\n",
               "========", "==========", "============", "====", "==",
               "========", "=========");



         // Read in a line of the file
        while(fgets(buffer, sizeof(buffer), ifp) != NULL)
        {
            char *bufCopy = buffer;

            // SiteNumber
            tok = strsep (&bufCopy, c);
            strcpy(a->siteNumber, tok);

            // LocID
            tok = strsep (&bufCopy, c);
            strcpy(a->LocID, tok);

            // fieldName
            tok = strsep (&bufCopy, c);
            strcpy(a->fieldName, tok);

            // city
            tok = strsep (&bufCopy, c);
            strcpy(a->city, tok);

            // state
            tok = strsep (&bufCopy, c);
            strcpy(a->state, tok);

            // UNWANTED
            tok = strsep (&bufCopy, c);
            tok = strsep (&bufCopy, c);
            tok = strsep (&bufCopy, c);

            // Latitude
            tok = strsep (&bufCopy, c);
            strcpy(a->latitude, tok);

            // Longitude
            tok = strsep (&bufCopy, c);
            strcpy(a->longitude, tok);

            // UNWANTED
            tok = strsep (&bufCopy, c);
            tok = strsep (&bufCopy, c);
            tok = strsep (&bufCopy, c);
            tok = strsep (&bufCopy, c);

            // Control Tower
            tok = strsep (&bufCopy, c);
            a->controlTower = tok[0];

            // Print Data
			PrintData(a);

        }

	    // Close file
        fclose(ifp);

        // Set to NULL
        ifp = NULL;

        // Free Allocated Memory
        free(a ->siteNumber);
        free(a ->LocID);
        free(a ->fieldName);
        free(a ->city);
        free(a ->state);
        free(a ->latitude);
        free(a ->longitude);
        free(a);
	}

    return 0;
}

void PrintData(airPdata *airport)
{
    if (airport == NULL)
    {
       fprintf(stderr, "ERROR: NULL pointer");
       return;
    }

    printf("%-13s",airport ->siteNumber);
    printf("%-12s",airport ->LocID);
    printf("%-43s",airport ->fieldName);
    printf("%-35s",airport ->city);
    printf("%-4s",airport ->state);
    printf("%-16s",airport ->latitude);
    printf("%-17s",airport ->longitude);
    printf("%c\n",airport ->controlTower);

    return;
}
