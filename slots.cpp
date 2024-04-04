#include <iostream>
#include <chrono>
#include <map>
#include <cstdlib>
#include <vector>
#include <future>

using namespace std;

int spin(map<int, string> wheel, int timeElapsed) {
    map<int, string>::iterator it;
    bool isSpinning = true;
    int key;

    chrono::time_point beg = chrono::steady_clock::now();

    while (isSpinning == true) {
        key = rand() % 9;
        chrono::time_point stop = chrono::steady_clock::now();

        for (it = wheel.begin(); it != wheel.end(); it++) {
            if (it->first == key) {
                cout << it->second;
                break;
            }
        }

        int time_diff = chrono::duration_cast<chrono::milliseconds>(stop - beg).count();
        if (time_diff > timeElapsed) {
            isSpinning = false;
        } else {
            cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
        }
    }

    return key;
}

int main() {
    srand(time(NULL));

    map<int, string> machine;

    machine[0] = "Bell          ";
    machine[1] = "Cherries      ";
    machine[2] = "Orange        ";
    machine[3] = "Grapes        ";
    machine[4] = "Watermelon    ";
    machine[5] = "Bar           ";
    machine[6] = "BarBar        ";
    machine[7] = "BarBarBar     ";
    machine[8] = "Seven         ";

    future<int> wheel1 = async(spin, machine, 3800);
    future<int> wheel2 = async(spin, machine, 4200);
    future<int> wheel3 = async(spin, machine, 4600);

    int sym1 = wheel1.get();
    int sym2 = wheel2.get();
    int sym3 = wheel3.get();

    cout << endl;

    if (sym1 == sym2 && sym2 == sym3) {
        cout << "Winner, winner! Chicken dinner!" << endl;
    } else {
        cout << "Try again." << endl;
    }

    // FOR machineING RUNTIME VIA MAP VS BST
    // chrono::time_point end = chrono::steady_clock::now();

    return 0;
}