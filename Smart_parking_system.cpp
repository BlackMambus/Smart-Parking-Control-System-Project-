#include <iostream>
#include <vector>
#include <string>
#include <ctime>

class ParkingSpot {
public:
    int spotNumber;
    bool isOccupied;
    std::string vehiclePlate;
    time_t entryTime;
    
    ParkingSpot(int number) : spotNumber(number), isOccupied(false), vehiclePlate(""), entryTime(0) {}

    void occupy(std::string plate) {
        isOccupied = true;
        vehiclePlate = plate;
        entryTime = std::time(nullptr); // Record entry time
    }

    void vacate() {
        isOccupied = false;
        vehiclePlate = "";
        entryTime = 0;
    }

    double calculateFee() {
        if (!isOccupied) return 0;
        
        time_t exitTime = std::time(nullptr); // Current time as exit time
        double duration = std::difftime(exitTime, entryTime) / 3600; // Duration in hours
        return duration * 2.5; // Assume parking fee is $2.5 per hour
    }

    void displayInfo() {
        std::cout << "Spot " << spotNumber << ": ";
        if (isOccupied) {
            std::cout << "Occupied by " << vehiclePlate << "\n";
        } else {
            std::cout << "Available\n";
        }
    }
};

class ParkingLot {
private:
    std::vector<ParkingSpot> spots;

public:
    ParkingLot(int totalSpots) {
        for (int i = 1; i <= totalSpots; ++i) {
            spots.push_back(ParkingSpot(i));
        }
    }

    void displayLotStatus() {
        for (auto& spot : spots) {
            spot.displayInfo();
        }
    }

    bool findAndOccupySpot(std::string vehiclePlate) {
        for (auto& spot : spots) {
            if (!spot.isOccupied) {
                spot.occupy(vehiclePlate);
                std::cout << "Spot " << spot.spotNumber << " occupied by vehicle " << vehiclePlate << "\n";
                return true;
            }
        }
        std::cout << "No available spots.\n";
        return false;
    }

    void vacateSpot(int spotNumber) {
        if (spotNumber > 0 && spotNumber <= spots.size()) {
            ParkingSpot& spot = spots[spotNumber - 1];
            if (spot.isOccupied) {
                double fee = spot.calculateFee();
                std::cout << "Vehicle " << spot.vehiclePlate << " is vacating spot " << spot.spotNumber << ". Total fee: $" << fee << "\n";
                spot.vacate();
            } else {
                std::cout << "Spot is already empty.\n";
            }
        }
    }
};

int main() {
    ParkingLot lot(5); // Initialize parking lot with 5 spots
    lot.displayLotStatus();

    // Simulate vehicle parking and vacating
    lot.findAndOccupySpot("ABC123");
    lot.findAndOccupySpot("XYZ789");
    lot.displayLotStatus();

    // Simulate vacating a spot
    lot.vacateSpot(1);
    lot.displayLotStatus();

    return 0;
}





