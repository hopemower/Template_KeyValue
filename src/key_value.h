#ifndef KEY_VALUE
#define KEY_VALUE
#include <array>

template<typename K, typename V, int max_size>

class KeyValue
{
private:
    std::array<K, max_size> keys_;
    std::array<V, max_size> values_;
    int size_;
    int FindIndex(K key) const;

public:
    //constructor
    KeyValue();
    //destructor
    ~KeyValue() {}

    //getters
    int GetSize() const { return size_; }

    //other methods
    bool KeyExists(K key) const;
    void Add(K key, V item);
    V ValueAt(K key) const;
    bool Full() const;
    bool Empty() const;
    bool RemoveOne(K key);
    int RemoveAll(K key);
    friend std::ostream& operator << (std::ostream& out, const KeyValue<K, V, max_size>& rhs) {
        for (int i = 0; i < rhs.size_; ++i) {
            out << rhs.keys_[i] << ": " << rhs.values_[i] << "\n";
        }

        return out;
    }
};

/**
 * @brief - initialize size_ to 0
 *
 * @tparam K - variable type for keys
 * @tparam V - variable type for values
 * @tparam max_size - users array max size
 */

template<typename K, typename V, int max_size>
KeyValue<K, V, max_size>::KeyValue()
{
    size_ = 0;
}

/**
 * @brief - function to add values to array
 *
 * @tparam K - variable for type key
 * @tparam V - variable for type value
 * @tparam max_size - users array max size
 * @param key - key to be added
 * @param item - item to be added
 */

template<typename K, typename V, int max_size>
void KeyValue<K, V, max_size>::Add(K key, V item)
{
    if (size_ == max_size)
    {
        throw std::out_of_range("The array is full, item was not added");
    }

    keys_[size_] = key;
    values_[size_] = item;
    size_++;
}

/**
 * @brief - function to find the current position of the given key
 *
 * @tparam K - variable for key
 * @tparam V - variable for value
 * @tparam max_size - users given max size of the array
 * @param key - key to find the position of
 * @return - the current position of key
 */

template<typename K, typename V, int max_size>
int KeyValue<K, V, max_size>::FindIndex(K key) const
{
    int i = 0;
    while (i < size_) {
        if (keys_[i] == key) {
            break;
        }
        i++;
    }
    if (i < size_) {
        return i;
    }
    else
    {
        return -1;
    }
}

/**
 * @brief - function to check if the key exists in the current array
 *
 * @tparam K - variable for keys
 * @tparam V - variable for values
 * @tparam max_size - users max size
 * @param key - key to check if it is in the array
 * @return - true if the key is found or false if it is not
 */

template<typename K, typename V, int max_size>
bool KeyValue<K, V, max_size>::KeyExists(K key) const
{
    if (FindIndex(key) == -1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/**
 * @brief - function to find the value at the current key
 *
 * @tparam K - variable for keys
 * @tparam V - variable for values
 * @tparam max_size - users given max size
 * @param key - key to use index of for value
 * @return - the value at the key's index
 */

template<typename K, typename V, int max_size>
V KeyValue<K, V, max_size>::ValueAt(K key) const
{
    if (FindIndex(key) == -1)
    {
        throw std::out_of_range("The key was not found.");
    }
    V value = values_[FindIndex(key)];
    return value;
}

/**
 * @brief - method to check if the array is empty
 *
 * @tparam T - variable type
 * @tparam max_size - max size of the given array
 * @return - true if the array is empty and false if it array has data
 */

template<typename K, typename V, int max_size>
bool KeyValue<K, V, max_size>::Empty() const
{
    if (size_ == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief - method to check if the array is full
 *
 * @tparam T - variable type
 * @tparam max_size - max size of the array
 * @return - true if the array is equal to the max_size and false if it is not equal to max_size
 */

template<typename K, typename V, int max_size>
bool KeyValue<K, V, max_size>::Full() const
{
    if (size_ == max_size)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief - Function to remove one key value pair in the array
 *
 * @tparam K - variable for keys
 * @tparam V - variable for values
 * @tparam max_size - users given max size
 * @param key - key to remove
 * @return - true if key was removed, false if the key could not be found
 */

template<typename K, typename V, int max_size>
bool KeyValue<K, V, max_size>::RemoveOne(K key)
{
    if (KeyExists(key))
    {
        int i = FindIndex(key);
        for (int j = i; j < size_ - 1; ++j) {
            keys_[j] = keys_[j + 1];
            values_[j] = values_[j + 1];
        }
        size_--;
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief - function to remove all given keys in the array
 *
 * @tparam K - variable for keys
 * @tparam V - variable for value
 * @tparam max_size - users given max size
 * @param key - key to remove duplicates of
 * @return - the number of keys that were removed
 */

template<typename K, typename V, int max_size>
int KeyValue<K, V, max_size>::RemoveAll(K key)
{
    int index = 0;
    while (RemoveOne(key)) {
        index++;
    }
    return index;
}

#endif