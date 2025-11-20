#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "smartparking.h"

void runParkingLot()
{
    SmartParkingLot* parkingLot = NULL;
    const char* textFilename = "parking_smart_state.txt";

    FILE* file = fopen(textFilename, "r");
    if (file)
    {
        fclose(file);
        parkingLot = loadParkingLotFromTextFile(textFilename);
        if (!parkingLot)
        {
            parkingLot = initializeParkingLot();
        }
    }
    else
    {
        parkingLot = initializeParkingLot();
    }

    int choice;
    char licensePlate[MAX_LICENSE_PLATE];
    int floor, spot;

    do {
        printf("\n--- Smart Parking Lot Management System ---\n");
        printf("1. Find the first available parking spot\n");
        printf("2. Reserve a parking spot\n");
        printf("3. Release a parking spot\n");
        printf("4. Display parking lot state\n");
        printf("5. Save parking lot to text file\n");
        printf("6. Load parking lot from text file\n");
        printf("7. Exit\n");
        printf("Choose an option: ");

        if (scanf_s("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            if (findFirstAvailableSpot(parkingLot, &floor, &spot))
            {
                printf("First available spot: Floor %d, Spot %d\n", floor, spot);
            }
            else
            {
                printf("No available spots.\n");
            }
            break;

        case 2:
            printf("Enter license plate to park: ");
            if (scanf_s("%11s", licensePlate, (unsigned)_countof(licensePlate)) != 1)
            {
                printf("Failed to read license plate.\n");
                break;
            }
            licensePlate[MAX_LICENSE_PLATE - 1] = '\0';
            parkCar(parkingLot, licensePlate);
            break;

        case 3:
            printf("Enter license plate to release: ");
            if (scanf_s("%11s", licensePlate, (unsigned)_countof(licensePlate)) != 1)
            {
                printf("Failed to read license plate.\n");
                break;
            }
            licensePlate[MAX_LICENSE_PLATE - 1] = '\0';
            releaseCar(parkingLot, licensePlate);
            break;

        case 4:
            printParkingLot(parkingLot);
            break;

        case 5:
            saveParkingLotToTextFile(parkingLot, textFilename);
            break;

        case 6:
            destroyParkingLot(parkingLot);
            parkingLot = loadParkingLotFromTextFile(textFilename);
            if (!parkingLot)
            {
                parkingLot = initializeParkingLot();
            }
            break;

        case 7:
            saveParkingLotToTextFile(parkingLot, textFilename);
            destroyParkingLot(parkingLot);
            printf("Exiting...\n");
            return;

        default:
            printf("Invalid choice, please try again\n");
        }
    } while (choice != 7);

    destroyParkingLot(parkingLot);
}


int main()
{
    runParkingLot(); // מפעילה את התוכנית הראשית, הכוללת את כל הפונקציות הנ"ל ומאפשרת למשתמש לנהל את החניון 
    return 0;
}
