#pragma once                                // Evita inclusiones múltiples del mismo header
#include "HashTableChaining.h"              // Necesitamos la clase base para heredar

// Implementación de un conjunto (set) sencillo que evita elementos repetidos
// Heredamos de HashTableChaining<T> y sobrescribimos Add para checar duplicados.
template <typename T>
class HashSet : public HashTableChaining<T>
{
public:
    // Constructor: reusamos el del padre para establecer el tamaño de la tabla
    explicit HashSet(unsigned int size)
        : HashTableChaining<T>(size)        // Llamada al constructor de la clase base con 'size'
    {}

    // Add “versión set”: antes de insertar, validamos si ya existe
    void Add(T element)
    {
        // Usamos Contains del padre. Si NO está, ahora sí insertamos
        if (!this->Contains(element))       // this-> para acceder a miembros heredados template
        {
            // Llamamos a Add del padre explícitamente
            this->HashTableChaining<T>::Add(element);
        }
        // Si ya está, no hacemos nada
    }
};
