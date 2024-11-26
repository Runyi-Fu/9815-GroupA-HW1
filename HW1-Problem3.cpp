/*
Exercise 3
Write a hash table class that maps keys to values. Define the following classes:
template <typename K, typename V>
class Hashtable;
template <typename K>
class Hasher;
template <typename K>
class EqualityPredicate;
The Hasher and EqualityPredicate classes should be base classes with pure virtual functions. They can be overridden to provide concrete implementations of a hashing function and equality predicate function, respectively.
*/

#include <iostream>
#include <string>

// abstract class for Hasher
template <typename K>
class Hasher 
{
public:
    virtual size_t hashFunction(const K& key) const = 0;
    virtual ~Hasher() {}
};

// abstract class for EqualityPredicate
template <typename K>
class EqualityPredicate 
{
public:
    virtual bool equals(const K& key1, const K& key2) const = 0;
    virtual ~EqualityPredicate() {}
};

// abstract class for Hashtable
template <typename K, typename V>
class Hashtable 
{
public:

    Hashtable(size_t tableSize, Hasher<K>* hasher, EqualityPredicate<K>* equality) : TABLE_SIZE(tableSize), hasher(hasher), equality(equality) 
    {
        keys = new K[TABLE_SIZE];
        values = new V[TABLE_SIZE];
    }

    // destructor
    ~Hashtable() 
    {
        delete[] keys;
        delete[] values;
    }

    // insert a pair
    void insertItem(const K& key, const V& value) 
    {
        size_t index = hasher->hashFunction(key) % TABLE_SIZE;

            keys[index] = key;
            values[index] = value;

    }

    // delete a pair
    void deleteItem(const K& key) 
    {
        size_t index = hasher->hashFunction(key) % TABLE_SIZE;

    }

    // Displays the key and value of Hashtable
    void displayHash() const 
{
    for (size_t i = 0; i < TABLE_SIZE; ++i)
    {
        std::cout << i << ": ";
        if (!equality->equals(keys[i], K()))
        {
            std::cout << keys[i] << ", " << values[i] << std::endl;
        }
        else
        {
            std::cout << "empty" << std::endl;
        }
    }
}

private:

    size_t TABLE_SIZE;   
    K* keys;             
    V* values;           
    Hasher<K>* hasher;
    EqualityPredicate<K>* equality;

};

// CCreate Hasher for int keys that indicate asset order
class IntHasher : public Hasher<int> 
{
public:
    size_t hashFunction(const int& key) const override 
    {
        return key; 
    }
};

class IntEquality : public EqualityPredicate<int> 
{
public:
    bool equals(const int& key1, const int& key2) const override 
    {
        return key1 == key2;
    }
};

int main() 
{
    IntHasher hasher;
    IntEquality equality;


    // Create Hashtable portfolio with 4 assets
    Hashtable<int, std::string> h(4, &hasher, &equality);

    std::pair<int, std::string> data[] = 
    {
        {0, "NVDA"},
        {1, "IBKR"},
        {2, "PLTR"},
        {3, "QQQ"}
    };

    // insert pairs
    for (const auto& kv : data) 
    {
        h.insertItem(kv.first, kv.second);
    }

    // display pairs
    h.displayHash();

    return 0;
}
