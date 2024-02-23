using namespace std;

#include <iostream>
#include <random>
#include <thread>
#include <mutex>

const int GUEST_COUNT = 100;

bool allCompleted = false;
int currentGuestID = -1;
bool isPlateEmpty = false;

mutex entrance; // a mutex representing the entrance to the labyrinth

void solveLabyrinth(int id) {
    bool cupcakeEaten = false;
    int solveCount = 0; // only for the first guest to worry about

    while (!allCompleted) {
        entrance.lock();

        if (currentGuestID == id) {
            // Designates first guests as a checker
            if (id == 0) {
                if (isPlateEmpty) {
                    solveCount++;
                    cout << solveCount+1 << " out of " << GUEST_COUNT << " have completed the labyrinth!" << endl;
                    isPlateEmpty = false; // ask for a new cupcake
                }

                // Tell the mintaur that everyone has finished the labyrinth (ending the party)
                if (solveCount == GUEST_COUNT - 1)
                    allCompleted = true;
            }
            else if (!isPlateEmpty && !cupcakeEaten) {
                cupcakeEaten = true;
                isPlateEmpty = true;
            }
        }

        entrance.unlock();
    }
}

int main() {
    auto start_time = chrono::high_resolution_clock::now();

    vector<thread> guests;

    // represent the guests as threads running "solveLabyrinth"
    for (int i = 0; i < GUEST_COUNT; i++) {
        guests.push_back(thread(solveLabyrinth, i));
    }

    // if all have yet to complete the labyrinth, the minotaur will keep randomly picking guests
    while (!allCompleted) {
        currentGuestID = rand() % GUEST_COUNT;
    }

    // once all have completed the labyrinth, we'll have all the guests "join" up together
    for (thread &guest : guests)
        guest.join();

    // calculate runtime and print result
    auto end_time = chrono::high_resolution_clock::now();
    int runtime_ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();

    cout << endl;
    cout << "All " << GUEST_COUNT << " guests have completed the labyrinth in " << runtime_ms << " milliseconds!" << endl;
}