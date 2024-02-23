using namespace std;

#include <iostream>
#include <random>
#include <thread>
#include <mutex>

const int GUEST_COUNT = 100;

int uniqueViews = 0;
int currentGuestID = -1;

mutex entrance; // a mutex representing the entrance to the showroom

void enterShowroom(int id) {
    bool firstViewing = true;

    while (uniqueViews < GUEST_COUNT) {
        this_thread::sleep_for(chrono::milliseconds(rand() % 100)); // walk around the party for some random time from 0-100ms

        if (currentGuestID == id && entrance.try_lock()) {
            // guest enters showroom and enjoys the vase

            if (firstViewing) {
                uniqueViews++;
                cout << "Guest " << id << " sees the crysal vase for the first time! " << endl;
            }

            firstViewing = false;
            entrance.unlock();
        }
    }
}

int main() {
    auto start_time = chrono::high_resolution_clock::now();

    vector<thread> guests;

    // represent the guests as threads attempting to "enterShowroom"
    for (int i = 0; i < GUEST_COUNT; i++) {
        guests.push_back(thread(enterShowroom, i));
    }

    // if not all guests have seen the vase, random guests will enter the showroom to look at it
    while (uniqueViews < GUEST_COUNT) {
        currentGuestID = rand() % GUEST_COUNT;
    }

    for (thread &guest : guests)
        guest.join();

    // calculate runtime and print result
    auto end_time = chrono::high_resolution_clock::now();
    int runtime_ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();

    cout << endl;
    cout << "All " << GUEST_COUNT << " guests have seen the vase in " << runtime_ms << " milliseconds!" << endl;
}