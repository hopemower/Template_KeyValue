#include <iostream>
#include "key_value.h"

using namespace std;
const int kSize = 5;

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
        cout << "Current Array\n" << key << endl;
    }
    else
    {
        cout << "RemoveOne function did not find the key" << endl;
    }

    try {
        cout << "RemovingAll function has removed " << key.RemoveAll(12) << " occurrences of the key 12." << endl;
        cout << "Current Array\n" << key << endl;
        cout << "RemovingAll function has removed " << key.RemoveAll(12) << " occurrences of the key 12." << endl;
        cout << "Current Array\n" << key << endl;
        cout << "RemovingAll function has removed " << key.RemoveAll(14) << " occurrences of the key 14." << endl;
        cout << "Current Array\n" << key << endl;
    } catch (out_of_range e) {
        cout << e.what() << endl;
    }

    cout << "KeyValue Size: " << key.GetSize() << endl;

    //testing empty method
    KeyValue<int, int, kSize> key_value;

    if (key_value.Empty())
    {
        cout << "Current Size of KeyValue " << key_value.GetSize() << endl; //should be 0
        key_value.Add(7, 22);
        cout << "Adding last value..." << endl;
        if (!key_value.Empty())
        {
            cout << "Current Size of KeyValue " << key_value.GetSize() << endl; // should be 1
            cout << "Removing Value at 7, new size of array: ";
            if (key_value.RemoveOne(7)) {
                cout << key_value.GetSize() << endl; // should be 0
            }
        }
    }

    return 0;
}