#pragma once                          
#include "HashTableChaining.h"        

// Conjunto sin duplicados heredando de HashTableChaining
template <typename T>
class HashSet : public HashTableChaining<T>
{
public:
    explicit HashSet(unsigned int size) : HashTableChaining<T>(size) {} // Reusar ctor base

    void Add(T element) override       // Override real (base::Add es virtual)
    {
        if (!this->Contains(element))  // Solo insertamos si NO existe
        {
            this->HashTableChaining<T>::Add(element); // Llamar Add del padre
        }
        
    }
};
