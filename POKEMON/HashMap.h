//
//  HashMap.h
//  Lab 09: Pokémon
//
#ifndef HASHMAP_H
#define HASHMAP_H
#include "HashMapInterface.h"
#include <iostream>
#include <math.h>
using namespace std;

template <typename K, typename V>
class HashMap : public HashMapInterface<K,V> {
private:
    pair<K,V>** hashMapArray;
    size_t arraySize = 0;
public:
    HashMap() {
        hashMapArray = new pair<K,V>*[DEFAULT_MAP_HASH_TABLE_SIZE];
        for (int i = 0; i < DEFAULT_MAP_HASH_TABLE_SIZE; ++i) {
            hashMapArray[i] = NULL;
        }
    }
    ~HashMap() {
        for (int i = 0; i < DEFAULT_MAP_HASH_TABLE_SIZE; ++i) {
            if (hashMapArray[i] != NULL) delete hashMapArray[i];
        }
        delete[] hashMapArray;
    }
    
    //Hashes
    long long hash(const K& key) {
        long long hashResult = 0;
        for (int i = 0; i < key.size(); ++i) {
            hashResult += key[i] * pow(HASH_CONSTANT, key.size() - (i + 1));
        }
        hashResult = hashResult % DEFAULT_MAP_HASH_TABLE_SIZE;
        return hashResult;
    }
    
    /** Read/write index access operator.
     If the key is not found, an entry is made for it.
     @return: Read and write access to the value mapped to the provided key.
     Return the value at the correct key in thsi function USE probing too */
    V& operator[](const K& key) {
        long long value = hash(key);
        int i = 0;
        long long tempValue = value;
        bool found = false;
        while (!found) {
            if (hashMapArray[tempValue] == NULL) {
                V vValue;
                arraySize++;
                hashMapArray[tempValue] = new pair<K,V>(key,vValue);
                found = true;
            }
            else if (hashMapArray[tempValue]->first != key) {
                tempValue = (value + (long long)pow((i + 1), 2)) % DEFAULT_MAP_HASH_TABLE_SIZE;
            }
            else {
                break;
            }
            i++;
        }
        return hashMapArray[tempValue]->second;
    }
    
    /** @return: the number of elements that matchthe key in the Map. WILL EITHER RETURN ONE OR ZERO DEPENDING ON IF THE KEY EXISTS. 1 if you find the key and 0 if its not there*/
    size_t count(const K& key) {
        return -1; //Placeholder
    }
    
    /** Removes all items from the Map. */
    void clear() {}
    
    /** @return: number of Key-Value pairs stored in the Map. */
    size_t size() const {
        return arraySize;
    }
    
    /** @return: maximum number of Key-Value pairs that the Map can hold. */
    size_t max_size() const {
        return DEFAULT_MAP_HASH_TABLE_SIZE;
    }
    
    /** @return: string representation of Key-Value pairs in Map. */
    string toString() const {
        ostringstream oSS;
        for (int i = 0; i < max_size(); ++i) {
            if (hashMapArray[i] != NULL) {
                oSS << "  [" << i << ":" << hashMapArray[i]->first << "->" << hashMapArray[i]->second << "]" << endl;
            }
        }
        return oSS.str(); //Placeholder
        
    }
};

#endif /* HASHMAP_H */
