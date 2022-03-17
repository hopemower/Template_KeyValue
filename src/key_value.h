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
        K key;
        for (int i = 0; i < max_size; ++i) {
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
 * @brief
 *
 * @tparam K
 * @tparam V
 * @tparam max_size
 * @param key
 * @param item
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
 * @brief -
 *
 * @tparam K
 * @tparam V
 * @tparam max_size
 * @param key
 * @return
 */

template<typename K, typename V, int max_size>
int KeyValue<K, V, max_size>::FindIndex(K key) const
{
    int i = 0;
    while (i < max_size) {
        if (keys_[i] == key) {
            break;
        }
        i++;
    }
    if (i < max_size) {
        return i;
    }
    else
    {
        return -1;
    }
}

/**
 * @brief
 *
 * @tparam K
 * @tparam V
 * @tparam max_size
 * @param key
 * @return
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
 * @brief
 *
 * @tparam K
 * @tparam V
 * @tparam max_size
 * @param key
 * @return
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
 *
 * @tparam K
 * @tparam V
 * @tparam max_size
 * @param key
 * @return
 */

template<typename K, typename V, int max_size>
bool KeyValue<K, V, max_size>::RemoveOne(K key)
{
    if (KeyExists(key))
    {
        keys_[FindIndex(key)];
        values_[FindIndex(key)];
        size_--;
        GetSize();
        return true;
    }
    else
    {
        return false;
    }
}

/**
 *
 * @tparam K
 * @tparam V
 * @tparam max_size
 * @param key
 * @return
 */

template<typename K, typename V, int max_size>
int KeyValue<K, V, max_size>::RemoveAll(K key)
{
    int index = 0;
    for (int i = 0; i < max_size; ++i) {
        if (keys_[i] == key)
        {
            i--;
            keys_[i];
            values_[i];
            size_--;
            GetSize();
            i += 2;
            index++;
        }
    }

    return index;
}


#endif