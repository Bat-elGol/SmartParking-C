#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "smartparking.h"

#define DEFAULT_FLOORS 3
#define DEFAULT_SPOTS_PER_FLOOR {10, 15, 20}


ParkingSpot* createParkingSpot() 
{
    ParkingSpot* spot = (ParkingSpot*)malloc(sizeof(ParkingSpot)); 
    if (!spot) 
    {
        printf("Error: Memory allocation failed for parking spot\n");
        return NULL;
    }
    memset(spot->licensePlate, 0, MAX_LICENSE_PLATE); 
    spot->next = NULL;
    return spot; 
}

void initializeFloor(ParkingFloor* floor, int numberOfSpots) 
{
    floor->spots = NULL; 
    ParkingSpot* last = NULL; 
    int j; 
    for (j = 0; j < numberOfSpots; j++)
    {
        ParkingSpot* spot = createParkingSpot(); 
        if (!spot) 
        {
            printf("Error: Memory allocation failed for parking spot\n");
            return;
        }

        if (floor->spots == NULL) 
        {
            floor->spots = spot; 
        }
        else
        {
            last->next = spot;  
        }
        last = spot; 
    }
}


SmartParkingLot* initializeParkingLot()
{
    int defaultSpots[] = DEFAULT_SPOTS_PER_FLOOR; 
    int i;
    SmartParkingLot* parkingLot = (SmartParkingLot*)malloc(sizeof(SmartParkingLot)); 
    if (!parkingLot)
    {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }

    parkingLot->numberOfFloors = DEFAULT_FLOORS; 
    parkingLot->floors = (ParkingFloor*)malloc(parkingLot->numberOfFloors * sizeof(ParkingFloor)); 
    if (!parkingLot->floors)
    {
        printf("Error: Memory allocation failed\n");
        free(parkingLot);
        return NULL;
    }

    for (i = 0; i < parkingLot->numberOfFloors; i++) 
    {
        parkingLot->floors[i].floorNumber = i + 1;
        parkingLot->floors[i].numberOfSpots = defaultSpots[i];
        initializeFloor(&parkingLot->floors[i], parkingLot->floors[i].numberOfSpots);  
    }

    return parkingLot;
}


void destroyParkingLot(SmartParkingLot* parkingLot) 
{
    int i;
    for (i = 0; i < parkingLot->numberOfFloors; i++) 
    {
        ParkingSpot* current = parkingLot->floors[i].spots;  
        while (current) 
        {
            ParkingSpot* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(parkingLot->floors); 
    free(parkingLot); 
}


int findFirstAvailableSpot(SmartParkingLot* parkingLot, int* floor, int* spot) 
{
    int i;
    for (i = 0; i < parkingLot->numberOfFloors; i++) 
    {
        int spotCounter = 1;
        ParkingSpot* current = parkingLot->floors[i].spots;
        while (current)
        {
            if (strcmp(current->licensePlate, "") == 0)
            {
                *floor = i + 1;
                *spot = spotCounter;
                return 1;
            }
            spotCounter++;
            current = current->next;
        }
    }
    *floor = -1;
    *spot = -1;
    return 0; 
}


void parkCar(SmartParkingLot* parkingLot, const char* licensePlate) //  מאפשרת חניה של רכב בחניה פנויה על ידי שמירת לוחית הרישוי בחניה
{
    int floor, spot;
    int i;
    if (findFirstAvailableSpot(parkingLot, &floor, &spot))
    {
        ParkingSpot* current = parkingLot->floors[floor - 1].spots;
        for (i = 1; i < spot; i++)
        {
            current = current->next;
        }
      
        strncpy_s(current->licensePlate, sizeof(current->licensePlate), licensePlate, MAX_LICENSE_PLATE - 1);
        current->licensePlate[MAX_LICENSE_PLATE - 1] = '\0'; 
        printf("Car %s parked at floor %d, spot %d\n", licensePlate, floor, spot);
    }
    else
    {
        printf("No available spots.\n");
    }
}


void releaseCar(SmartParkingLot* parkingLot, const char* licensePlate) // הפונקציה משחררת חניה תפוסה על ידי מחיקת לוחית הרישוי ושחרור החניה.
{
    int i;
    for (i = 0; i < parkingLot->numberOfFloors; i++)
    {
        ParkingSpot* current = parkingLot->floors[i].spots;
        while (current)
        {
            if (strcmp(current->licensePlate, licensePlate) == 0)
            {
                memset(current->licensePlate, 0, MAX_LICENSE_PLATE); 
                printf("Car %s released from floor %d\n", licensePlate, i + 1);
                return;
            }
            current = current->next;
        }
    }
    printf("Car %s not found.\n", licensePlate);
}


void printParkingLot(SmartParkingLot* parkingLot) // מציגה את מצב החניון – האם חניה מסוימת פנויה או תפוסה
{
    int i;
    for (i = 0; i < parkingLot->numberOfFloors; i++)
    {
        printf("Floor %d:\n", i + 1);
        ParkingSpot* current = parkingLot->floors[i].spots;
        int spotCounter = 1;
        while (current)
        {
            if (strcmp(current->licensePlate, "") != 0)
            {
                printf("  Spot %d: %s\n", spotCounter, current->licensePlate);
            }
            else
            {
                printf("  Spot %d: [empty]\n", spotCounter);
            }
            spotCounter++;
            current = current->next;
        }
    }
}

void saveParkingLotToTextFile(SmartParkingLot* parkingLot, const char* filename) //  שומרת את מצב החניון הנוכחי לקובץ טקסט, כולל מידע על כל החניות והקומות.
{
    FILE* file = fopen(filename, "w");
    if (!file)
    {
        printf("Error: Could not open file %s for writing\n", filename);
        return;
    }


    fprintf(file, "Number of Floors: %d\n", parkingLot->numberOfFloors);

    int i;
    for (i = 0; i < parkingLot->numberOfFloors; i++)
    {
        fprintf(file, "Floor %d: %d spots\n", parkingLot->floors[i].floorNumber, parkingLot->floors[i].numberOfSpots);

        ParkingSpot* current = parkingLot->floors[i].spots;
        int spotCounter = 1;
        while (current)
        {
            if (strcmp(current->licensePlate, "") != 0)
            {
                fprintf(file, "Spot %d: %s\n", spotCounter, current->licensePlate);
            }
            else
            {
                fprintf(file, "Spot %d: [empty]\n", spotCounter);
            }
            spotCounter++;
            current = current->next;
        }
    }

    fclose(file);
    printf("Parking lot state saved to text file %s successfully.\n", filename);
}


SmartParkingLot* loadParkingLotFromTextFile(const char* filename) // טוענת את מצב החניון מקובץ טקסט שנשמר בעבר ומבצעת שחזור של הקומות והחניות
{
    FILE* file = fopen(filename, "r"); 
    if (!file)
    {
        printf("Error: Could not open file %s for reading\n", filename);
        return NULL;
    }

    SmartParkingLot* parkingLot = (SmartParkingLot*)malloc(sizeof(SmartParkingLot));
    if (!parkingLot)
    {
        printf("Error: Memory allocation failed\n");
        fclose(file); 
        return NULL;
    }

    if (fscanf_s(file, "Number of Floors: %d\n", &parkingLot->numberOfFloors) == EOF)
    {
        printf("Error: Unexpected end of file while reading number of floors.\n");
        free(parkingLot);
        fclose(file);
        return NULL;
    }

    parkingLot->floors = (ParkingFloor*)malloc(parkingLot->numberOfFloors * sizeof(ParkingFloor)); 
    if (!parkingLot->floors)
    {
        printf("Error: Memory allocation failed\n");
        free(parkingLot);
        fclose(file);
        return NULL;
    }

    int i, j;
    for (i = 0; i < parkingLot->numberOfFloors; i++)
    {
  
        if (fscanf_s(file, "Floor %d: %d spots\n", &parkingLot->floors[i].floorNumber, &parkingLot->floors[i].numberOfSpots) == EOF)
        {
            printf("Error: Unexpected end of file while reading floor data.\n");
            free(parkingLot->floors);
            free(parkingLot);
            fclose(file);
            return NULL;
        }

        parkingLot->floors[i].spots = NULL; 

        for (j = 0; j < parkingLot->floors[i].numberOfSpots; j++)
        {
            ParkingSpot* spot = createParkingSpot(); 
            if (!spot)
            {
                printf("Error: Memory allocation failed\n");
                free(parkingLot->floors);
                free(parkingLot);
                fclose(file);
                return NULL;
            }

            char status[20];
            if (fscanf_s(file, "Spot %*d: %19s\n", status, (unsigned)_countof(status)) == EOF)
            {
                printf("Error: Unexpected end of file while reading spot data.\n");
                free(parkingLot->floors);
                free(parkingLot);
                fclose(file);
                return NULL;
            }

            status[sizeof(status) - 1] = '\0';

            if (strcmp(status, "[empty]") != 0)
            {
                strncpy_s(spot->licensePlate, sizeof(spot->licensePlate), status, MAX_LICENSE_PLATE - 1);
                spot->licensePlate[MAX_LICENSE_PLATE - 1] = '\0';
            }
            else
            {
                memset(spot->licensePlate, 0, MAX_LICENSE_PLATE); 
            }
            spot->next = parkingLot->floors[i].spots; 
            parkingLot->floors[i].spots = spot;
        }
    }

    fclose(file); 
    return parkingLot;
}
