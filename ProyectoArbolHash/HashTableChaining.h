#pragma once                     
#include <stdexcept> 
#include <iostream>               
                                  

#include <forward_list>           
#include <string>                 
using namespace std;              

// Hacemos una clase template para que funcione con distintos tipos T 
template <typename T>
class HashTableChaining
{
	// data: arreglo dinámico de listas 
	forward_list<T>* data;        // Puntero al primer elemento del arreglo de listas 
	unsigned int arraySize;       // Tamaño del arreglo 
	// unsigned = no acepta valores negativos (solo 0, 1, 2, ...)

	// size_t es un entero sin signo de 64 bits en la mayoría de plataformas 

public:

	// Constructor que recibe el tamaño de la tabla 
	HashTableChaining(unsigned int size)
	{
		// Reservamos memoria para 'size' listas. Cada data[i] es una forward_list<T> vacía
		data = new forward_list<T>[size];
		arraySize = size;          // Guardamos el tamaño para calcular índices y loops
	}

	// Función hash: toma una llave 'key' de tipo T y la mapea a un índice [0, arraySize)
	// Este hash asume que T soporta el operador % (módulo). O sea, típicamente T debe ser un entero
	int HashFunction(T key)
	{
		return key % arraySize;   // Regresamos el residuo de dividir entre arraySize
	}

	// Insertar un elemento en la tabla
	void Add(T element)
	{
		int index = HashFunction(element); // Calculamos en qué bucket cae el elemento
		// Insertamos al frente de la lista del bucket
		data[index].push_front(element);

	}

	// Eliminar un elemento de la tabla (si existe). Complejidad: depende del largo de la lista en ese bucket
	void Remove(T element)
	{
		int index = HashFunction(element);        // Vemos en qué bucket debería estar
		forward_list<T>& listAtIndex = data[index]; // Referencia a la lista de ese bucket 
		for (auto i : listAtIndex)                // For-each para recorrer la lista y buscar coincidencia
		{
			if (i == element)                     // Si encontramos el elemento
			{
				// forward_list tiene .remove(valor) que borra todas las coincidencias de ese valor
				listAtIndex.remove(i);            
				return;                           
			}
		}
		// Si no se encontró, lanzamos error
		throw runtime_error("no element " + to_string(element) + " in this hash table.");
	}

	// Búsqueda: regresa true si el elemento está, false si no
	bool Contains(T element)
	{
		int index = HashFunction(element);        // Calculamos el bucket correcto
		forward_list<T>& listAtIndex = data[index]; // Tomamos referencia a la lista del bucket
		for (auto i : listAtIndex)                // Recorremos esa lista
		{
			if (i == element)                     // Si encontramos el valor
			{
				return true;                      // Ya estuvo, sí contiene
			}
		}
		return false;                              // Si llegamos aquí, no estaba en esa lista
	}

	// Imprimir la tabla completa: todos los buckets y el contenido de sus listas.
	void Print()
	{
		// Iteramos por cada índice del arreglo
		for (int i = 0; i < arraySize; i++)
		{
			// Mostramos el número de bucket para entender la dispersión
			cout << "lista del índice: " << std::to_string(i) << ": ";
			// Recorremos la forward_list en ese bucket e imprimimos cada elemento.
			for (auto j : data[i])                // For-each para todos los nodos de la lista
				cout << j << ", ";

			cout << endl;                         // Fin de línea para el bucket actual
		}
	}

};
void HashTableChainingExample();
