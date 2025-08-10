#include <iostream>                 
#include "BinarySearchTree.h"       
#include "HashTableChaining.h"      
#include "HashSet.h"                

int main()
{
    std::cout << "==== Pruebas BinarySearchTree ====\n"; 

    BinarySearchTree<int> bst;      // Creamos un árbol binario de búsqueda de enteros

    // Insertamos algunos valores 
    bst.Add(50);                    // Raíz
    bst.Add(30);                    // Va a la izquierda de 50
    bst.Add(70);                    // Va a la derecha de 50
    bst.Add(20);                    // Izq de 30 
    bst.Add(40);                    // Der de 30
    bst.Add(60);                    // Izq de 70
    bst.Add(80);                    // Der de 70

    // Probamos la búsqueda ITERATIVA:
    std::cout << "Search(60): " << (bst.Search(60) ? "true" : "false") << "\n"; // Debería ser true.
    std::cout << "Search(99): " << (bst.Search(99) ? "true" : "false") << "\n"; // Debería ser false.

    // Probamos el Post-Order iterativo (imprime en orden: izq, der, nodo
    std::cout << "PostOrderIterative:\n";
    bst.PostOrderIterative();       // Debe listar los nodos en post-orden

    
    // Caso 1: borrar hoja (20 es hoja)
    bst.Delete(20);
    // Caso 2: borrar nodo con un solo hijo (30 ahora tiene solo un hijo: 40)
    bst.Delete(30);
    // Caso 3: borrar nodo con dos hijos (50 tiene 40 como izq y 70 como der)
    // Aquí se ejercita el uso del sucesor
    bst.Delete(50);

    // Volvemos a imprimir post-orden para ver cómo quedó la estructura
    std::cout << "PostOrderIterative (despues de deletes):\n";
    bst.PostOrderIterative();

    // Limpiamos todo el árbol usando borrado post-orden iterativo
    bst.Clear();
    std::cout << "Arbol limpiado. PostOrderIterative (no imprime nada):\n";
    bst.PostOrderIterative();       // Ya no debería imprimir nada

    // =========================
    std::cout << "\n==== Pruebas HashTableChaining ====\n";

    HashTableChaining<int> ht(7);   // Creamos una tabla hash con 7 buckets (7 es primo, suele ir bien)

    // Insertamos valores que seguramente colisionan (módulo 7)
    ht.Add(14);   // 14 % 7 = 0
    ht.Add(21);   // 21 % 7 = 0 colisiona con 14
    ht.Add(28);   // 28 % 7 = 0 colisiona con 14 y 21
    ht.Add(5);    //  5 % 7 = 5 otro bucket

    // Probamos Contains:
    std::cout << "Contains(21): " << (ht.Contains(21) ? "true" : "false") << "\n";   // true
    std::cout << "Contains(100): " << (ht.Contains(100) ? "true" : "false") << "\n"; // false

    // Vemos la distribución de buckets e items:
    ht.Print();

    std::cout << "\n==== Pruebas HashSet (sin repetidos) ====\n";

    HashSet<int> hset(7);           // Nuestro set con 7 buckets (usa la hash del padre).

    hset.Add(14);
    hset.Add(21);
    hset.Add(28);
    hset.Add(14);                   // Repetido: el set debe ignorar esto.
    hset.Add(35);                   // 35 % 7 = 0 (misma lista, pero no repetido).

    // Verificamos elementos:
    std::cout << "Contains(14): " << (hset.Contains(14) ? "true" : "false") << "\n"; // true
    std::cout << "Contains(35): " << (hset.Contains(35) ? "true" : "false") << "\n"; // true

    // Reutilizamos Print del padre para ver cómo quedó (debería no repetir 14).
    hset.Print();

    std::cout << "\nListo.\n";      // Mensaje final.
    return 0;                        
}
