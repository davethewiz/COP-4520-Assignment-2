#include <iostream>

#include <random>

#include <thread>
#include <mutex>

#include <random>
#include <chrono>

const int GUEST_COUNT = 8;

bool partyEnded = false;
int currentGuestID = -1;
bool isPlateEmpty = false;


// Runs for all other guests besides the first one
void solveLabyrinth(int id) {
    bool cupcakeEaten = false;

    while (!partyEnded) {
        // mutex locking here
        if (currentGuestID == id && !isPlateEmpty && !cupcakeEaten) {

        }

        // unlock mutex 
    }
}

// Only runs for the first guest as they are designated as the "checker"
void checkCupcake() {
    int solveCount = 0;

    while (!partyEnded) {
        // do some mutex locking here
        if (currentGuestID == 0 && isPlateEmpty) {
            solveCount++;
        }

        if (solveCount == GUEST_COUNT) {
            partyEnded = true; // Think of this as the first guest "telling" the minotaur that the party has ended (all guests have finished the labyrinth)
        }

        // unlock mutex
    }
}

int main() {
    // start all threads at once with the "solveLabyrinth" function (except for first one)
    // Let first thread run the "checkCupcake" function instead (can't we just use main thread? Main thread IS the first checker?)
    // randomly select a guest ID every frame or on some timer
    // if party has ended, print out final time!
}