#include <iostream>
#include "key_value.h"
#include "carton.h"
#include <array>
#include <string>

using namespace std;

int main() {

    cout << "KeyValue testing\nFirst Key\n";

    KeyValue<int, int, 12> key;

    try {
        key.Add(1, 31);
        key.Add(2, 28);
        key.Add(3, 31);
        key.Add(12, 30);
        key.Add(5, 31);
        key.Add(6, 30);
        key.Add(7, 31);
        key.Add(12, 31);
        key.Add(9, 30);
        key.Add(10, 31);
        key.Add(11, 30);

    } catch (out_of_range e) {
        cout << e.what() << endl;
    }

    cout << "After Exception" << endl;
    cout << "KeyValue Size: " << key.GetSize() << endl;

    cout << "Adding last value..." << endl;

    if (key.Full())
    {
        cout << "Too full\n";
    } else
    {
        key.Add(12, 31);
    }

    cout << "KeyValue Size: " << key.GetSize() << endl;

    if (key.KeyExists(12))
    {
        cout << "Value for Key 12: " << key.ValueAt(12) << endl;
    }

    try {
        cout << "Value for Key 13: " << key.ValueAt(13) << endl;
    } catch (out_of_range e) {
        cout << e.what() << endl;
    }

    if (key.RemoveOne(12)) {
        cout << "Removing Value at 12, new size of array: " << key.GetSize() << endl;
    }
    else
    {
        cout << "RemoveOne function did not find the key" << endl;
    }

    try {
        cout << "RemovingAll function has removed " << key.RemoveAll(12) << " occurrences of the key 12." << endl;
    } catch (out_of_range e) {
        cout << e.what() << endl;
    }

    cout << "KeyValue Size: " << key.GetSize() << endl;

    return 0;
}