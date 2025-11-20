#pragma once
#ifndef SMARTPARKING_H
#define SMARTPARKING_H

#define MAX_LICENSE_PLATE 12 

typedef struct ParkingSpot //spots parking
{
    char licensePlate[MAX_LICENSE_PLATE]; 
    struct ParkingSpot* next; 
} ParkingSpot;

typedef struct ParkingFloor
{
    int floorNumber; 
    int numberOfSpots;
    ParkingSpot* spots; 
} ParkingFloor;

typedef struct SmartParkingLot
{
    int numberOfFloors;
    ParkingFloor* floors;
} SmartParkingLot;

ParkingSpot* createParkingSpot();

void initializeFloor(ParkingFloor* floor, int numberOfSpots);

SmartParkingLot* initializeParkingLot();

void destroyParkingLot(SmartParkingLot* parkingLot);

int findFirstAvailableSpot(SmartParkingLot* parkingLot, int* floor, int* spot);

void parkCar(SmartParkingLot* parkingLot, const char* licensePlate);

void releaseCar(SmartParkingLot* parkingLot, const char* licensePlate);

void printParkingLot(SmartParkingLot* parkingLot);

void saveParkingLotToTextFile(SmartParkingLot* parkingLot, const char* filename);

SmartParkingLot* loadParkingLotFromTextFile(const char* filename);

void runParkingLot();

#endif 

