#pragma once
#include "SentinelLinkedList.h"
#include <iostream>
using namespace std;

// Clase LQueue que funciona como una cola 
template <typename T>
class LQueue
{
private:
    SentinelLinkedList<T> data;  // Usamos lista ligada

public:
    LQueue() {}

    // Cantidad de elementos
    int GetCount() { return data.GetCount(); }

    // Encola un elemento (lo pone al final)
    void Enqueue(T value) { data.PushBack(value); }

    // Desencola (quita el primero)
    T Dequeue() { return data.PopFront(); }

    // Muestra el primero sin quitarlo
    T Front() { return data.Front(); }
};
