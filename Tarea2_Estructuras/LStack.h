#pragma once
#include <forward_list>
#include <iostream>
using namespace std;

// Clase LStack que simula una pila 
template <typename T>
class LStack
{
private:
    forward_list<T> data; // Lista simple de STL
    int count;

public:
    LStack() { count = 0; }

    // Agrega un nuevo elemento al tope
    void Push(T value)
    {
        data.push_front(value);
        count++;
    }

    // Quita el elemento del tope
    T Pop()
    {
        if (count == 0)
        {
            cout << "Pila vacía\n";
            return {};
        }

        T top = data.front();
        data.pop_front();
        count--;
        return top;
    }

    // Muestra el tope sin quitarlo
    T Peek()
    {
        if (count == 0)
        {
            cout << "Pila vacía\n";
            return {};
        }
        return data.front();
    }

    // Devuelve cuántos elementos hay
    int Count() { return count; }
};
