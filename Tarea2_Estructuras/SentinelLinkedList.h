#pragma once
#include <iostream>
using namespace std;

// Clase de lista ligada doble con nodo centinela
template <typename T>
class SentinelLinkedList
{
private:
    // Clase interna para el nodo de la lista
    template <typename T>
    class Node
    {
    public:
        Node() { prev = nullptr; next = nullptr; }
        Node(T value) : data(value), prev(nullptr), next(nullptr) {}

        T data;           // Dato que guarda el nodo
        Node<T>* next;    // Apunta al siguiente nodo
        Node<T>* prev;    // Apunta al nodo anterior
    };

    Node<T>* NIL; // Nodo centinela (inicio y fin)
    int count;    // Cuántos elementos hay en la lista

public:
    SentinelLinkedList()
    {
        count = 0;
        NIL = new Node<T>();
        NIL->next = NIL;
        NIL->prev = NIL;
    }

    // Retorna cuántos elementos hay
    int GetCount() { return count; }

    // Agrega un valor al final
    void PushBack(T value)
    {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = NIL;
        NIL->prev->next = newNode;
        newNode->prev = NIL->prev;
        NIL->prev = newNode;
        count++;
    }

    // Elimina y devuelve el último valor
    T PopBack()
    {
        if (count == 0)
        {
            cout << "Cuidado, lista vacía.\n";
            return {};
        }

        Node<T>* penultimate = NIL->prev;
        NIL->prev = penultimate->prev;
        penultimate->prev->next = NIL;

        T value = penultimate->data;
        delete penultimate;
        count--;
        return value;
    }

    // Agrega al inicio de la lista
    void PushFront(T value)
    {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = NIL->next;
        NIL->next->prev = newNode;
        NIL->next = newNode;
        newNode->prev = NIL;
        count++;
    }

    // Elimina y devuelve el primer valor
    T PopFront()
    {
        if (count == 0)
        {
            cout << "Lista vacía, no se puede PopFront.\n";
            return {};
        }

        Node<T>* first = NIL->next;
        NIL->next = first->next;
        first->next->prev = NIL;

        T value = first->data;
        delete first;
        count--;
        return value;
    }

    // Devuelve el primer valor sin eliminarlo
    T Front()
    {
        if (count == 0)
        {
            cout << "Lista vacía.\n";
            return {};
        }
        return NIL->next->data;
    }
};
