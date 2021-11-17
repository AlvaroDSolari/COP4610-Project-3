#include <iostream>
#include <sstream>
#include <vector> 

std::vector<int> fillVectorWithCylinders(std::string userInput); 
std::vector<int> getGreaterThanCurrentLocation (int currentLocation, std::vector<int> myLocations); 
std::vector<int> getLessThanCurrentLocation (int currentLocation, std::vector<int> myLocations); 
void sortAscending (std::vector<int>& greaterLocations); 
void sortDescending (std::vector<int>& lowerLocations); 
void performSCAN (int directionOfArm, int startingLocation, std::vector<int> myCylinders); 
void performCSCAN (int startingLocation, std::vector<int> myCylinders, int flybackTime); 

int main() {
    
    int currentLocation; 
    int armDirection; 
    int flybackTime; 
    
    std::string extraWhiteSpace; 
    std::string listOfCylinders;
    std::string userChoice; 
    
    std::cout << "This disk scheduler tries to optimize on seek time for disk accesses." << std::endl << std::endl; 
    
    std::cout << "Please enter the current location of the arm: "; 
    std::cin >> currentLocation; 
    std::cout << "Please enter the travel direction of the arm (1: Going towards higher numbers, 2: Going towards lower numbers): "; 
    std::cin >> armDirection; 
    std::cout << "Please enter flyback time in number of cylinders: "; 
    std::cin >> flybackTime; 
    std::cout << "Please enter the list of cylinder numbers for the file: ";  
    std::getline(std::cin, extraWhiteSpace); 
    std::getline(std::cin, listOfCylinders); 
    std::vector<int> myCylinders = fillVectorWithCylinders(listOfCylinders); 
    std::cout << std::endl; 
    
    do {
        
        std::cout << "------------------------------------------------------------------" << std::endl; 
        std::cout << "Please enter a choice: 1. SCAN     2. C-SCAN     3. QUIT\t"; 
        std::cin >> userChoice; 
        std::cout << std::endl; 
        
        if (userChoice == "1"){
            performSCAN(armDirection, currentLocation, myCylinders); 
        } else if (userChoice == "2"){
            performCSCAN(currentLocation, myCylinders, flybackTime); 
        }
        
    } while (userChoice != "3"); 
    
    std::cout << "Ending the program now...";
    
    return 0; 
    
}

std::vector<int> fillVectorWithCylinders (std::string userInput){
    
    std::vector<int> myCylinders; 
    std::stringstream myStream(userInput); 
    int cylinderNumber; 
    
    while (myStream >> cylinderNumber){
        myCylinders.push_back(cylinderNumber); 
    }
    
    return myCylinders; 
}

std::vector<int> getGreaterThanCurrentLocation (int currentLocation, std::vector<int> myLocations){
    
    std::vector<int> resultingVector; 
    for (int theCounter = 0; theCounter < (signed)myLocations.size(); theCounter++){
        if(myLocations.at(theCounter) > currentLocation){
            resultingVector.push_back(myLocations.at(theCounter));
        }
    }
    
    return resultingVector; 
    
}

std::vector<int> getLessThanCurrentLocation (int currentLocation, std::vector<int> myLocations){
    
    std::vector<int> resultingVector; 
    for (int theCounter = 0; theCounter < (signed)myLocations.size(); theCounter++){
        if(myLocations.at(theCounter) < currentLocation){
            resultingVector.push_back(myLocations.at(theCounter)); 
        }
    }
    
    return resultingVector; 
    
}

void sortAscending (std::vector<int>& greaterLocations){
    
    std::vector<int> sortedVector; 
    
    while (!greaterLocations.empty()){
        
        int minValue = greaterLocations.at(0); 
        int indexOfMinValue = 0; 
        for (int theCounter = 1; theCounter < (signed)greaterLocations.size(); theCounter++){
            if (greaterLocations.at(theCounter) < minValue){
                minValue = greaterLocations.at(theCounter); 
                indexOfMinValue = theCounter; 
            }
        }
        
        greaterLocations.erase(greaterLocations.begin() + indexOfMinValue); 
        sortedVector.push_back(minValue); 
        
    }

    for (int theCounter = 0; theCounter < (signed)sortedVector.size(); theCounter++){
        greaterLocations.push_back(sortedVector.at(theCounter)); 
    }
    
}

void sortDescending(std::vector<int>& lowerLocations){
    
    std::vector<int> sortedVector; 
    
    while (!lowerLocations.empty()){
        
        int maxValue = lowerLocations.at(0); 
        int indexOfMaxValue = 0; 
        for (int theCounter = 1; theCounter < (signed)lowerLocations.size(); theCounter++){
            if (lowerLocations.at(theCounter) > maxValue){
                maxValue = lowerLocations.at(theCounter); 
                indexOfMaxValue = theCounter; 
            }
        }
        
        lowerLocations.erase(lowerLocations.begin() + indexOfMaxValue); 
        sortedVector.push_back(maxValue); 
        
    }

    for (int theCounter = 0; theCounter < (signed)sortedVector.size(); theCounter++){
        lowerLocations.push_back(sortedVector.at(theCounter)); 
    }
    
}

void performSCAN (int directionOfArm, int startingLocation, std::vector<int> myCylinders){
    
    std::vector<int> greaterLocations = getGreaterThanCurrentLocation(startingLocation, myCylinders); 
    std::vector<int> lowerLocations = getLessThanCurrentLocation(startingLocation, myCylinders); 
    sortAscending(greaterLocations); 
    sortDescending(lowerLocations); 
    
    std::cout << "Running the SCAN algorithm now..." << std::endl << std::endl; 
    std::cout << "The sequence of visits to the cylinders:" << std::endl << std::endl; 
    
    if(directionOfArm == 1){
        
        int distanceToLastLocation; 
        int distanceToFirstLocation; 
        int totalDistance; 
        
        std::cout << "\t" << startingLocation; 
        
        while(!greaterLocations.empty()){
            std::cout << "\t" << greaterLocations.at(0); 
            greaterLocations.erase(greaterLocations.begin());
        }
        std::cout << "\t299"; 
        
        while (!lowerLocations.empty()){
            std::cout << "\t" << lowerLocations.at(0); 
            distanceToFirstLocation = lowerLocations.at(0); 
            lowerLocations.erase(lowerLocations.begin()); 
        }
        
        distanceToLastLocation = 299 - startingLocation; 
        distanceToFirstLocation = 299 - distanceToFirstLocation; 
        totalDistance = distanceToLastLocation + distanceToFirstLocation; 
        
        std::cout << std::endl << std::endl; 
        std::cout << "Total cylinder travel for SCAN, arm going toward higher numbers before start: " << totalDistance << std::endl << std::endl; 
        
    } else { /* If the arm movement is not 1, then that must mean that it is 2. */ 
        
        int distanceToLastLocation;
        int distanceToFirstLocation; 
        int totalDistance; 
        
        std::cout << "\t" << startingLocation; 
        
        while (!lowerLocations.empty()){
            std::cout << "\t" << lowerLocations.at(0);
            lowerLocations.erase(lowerLocations.begin()); 
        }
        std::cout << "\t0";
        
        while (!greaterLocations.empty()){
            std::cout << "\t" << greaterLocations.at(0);
            distanceToLastLocation = greaterLocations.at(0); 
            greaterLocations.erase(greaterLocations.begin()); 
        }
        
        distanceToFirstLocation = startingLocation - 0; 
        distanceToLastLocation = distanceToLastLocation - 0; 
        totalDistance = distanceToFirstLocation + distanceToLastLocation; 
        
        std::cout << std::endl << std::endl; 
        std::cout << "Total cylinder travel for SCAN, arm going toward lower numbers before start: " << totalDistance << std::endl << std::endl; 
        
    }
    
}

void performCSCAN (int startingLocation, std::vector<int> myCylinders, int flybackTime){ 
    
    std::vector<int> greaterLocations = getGreaterThanCurrentLocation(startingLocation, myCylinders); 
    std::vector<int> lowerLocations = getLessThanCurrentLocation(startingLocation, myCylinders); 
    sortAscending(greaterLocations); 
    sortAscending(lowerLocations);
    
    std::cout << "Running the C-SCAN algorithm now..." << std::endl << std::endl; 
    std::cout << "The sequence of visits to the cylinders:" << std::endl << std::endl;
    
    int lastCylinder; 
    int distanceToLastLocation;
    int distanceFromBeginningToLastCylinder; 
    int totalDistance; 
    
    std::cout << "\t" << startingLocation; 
    
    while(!greaterLocations.empty()){
        std::cout << "\t" << greaterLocations.at(0); 
        greaterLocations.erase(greaterLocations.begin());
    }
    
    std::cout << "\t299\t0"; 
    
    while(!lowerLocations.empty()){
        std::cout << "\t" << lowerLocations.at(0); 
        lastCylinder = lowerLocations.at(0); 
        lowerLocations.erase(lowerLocations.begin()); 
    }
    
    distanceToLastLocation = 299 - startingLocation; 
    distanceFromBeginningToLastCylinder = lastCylinder - 0; 
    totalDistance = distanceToLastLocation + flybackTime + distanceFromBeginningToLastCylinder; 
    
    std::cout << std::endl << std::endl; 
    std::cout << "Total cylinder travel for C-SCAN: " << totalDistance << std::endl << std::endl; 
    
}