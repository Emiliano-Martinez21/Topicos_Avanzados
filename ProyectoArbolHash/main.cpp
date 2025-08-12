#include <iostream>                    
#include "BinarySearchTree.h"           
#include "HashTableChaining.h"          
#include "HashSet.h"                    

int main()
{
    std::cout << "==== Pruebas BinarySearchTree ====\n";

    BinarySearchTree<int> bst;          // Árbol de enteros

    // Insertar valores (incluye duplicado 30 para probar <= izquierda)
    bst.Add(50); bst.Add(30); bst.Add(70);
    bst.Add(20); bst.Add(40); bst.Add(60); bst.Add(80);
    bst.Add(30);                          // Duplicado → va a la izquierda

    // Búsqueda iterativa
    std::cout << "Search(60): " << (bst.Search(60) ? "true" : "false") << "\n";
    std::cout << "Search(99): " << (bst.Search(99) ? "true" : "false") << "\n";

    // Post-order iterativo
    std::cout << "PostOrderIterative:\n";
    bst.PostOrderIterative();

    // Borrados:
    bst.Delete(20);                       // Caso 1: hoja
    bst.Delete(30);                       // Caso 2: un hijo (tras duplicado)
    bst.Delete(70);                       // Caso 3: dos hijos (evita borrar raíz)

    std::cout << "PostOrderIterative (despues de deletes):\n";
    bst.PostOrderIterative();

    // Limpiar árbol completo
    bst.Clear();
    std::cout << "Arbol limpiado. PostOrderIterative (no imprime nada):\n";
    bst.PostOrderIterative();

    //********************************************* */
    std::cout << "\n==== Pruebas HashTableChaining ====\n";

    HashTableChaining<int> ht(7);         // 7 buckets (primo)
    ht.Add(14); ht.Add(21); ht.Add(28);   // Colisionan en 0
    ht.Add(5);                            // Bucket 5
    std::cout << "Contains(21): " << (ht.Contains(21) ? "true" : "false") << "\n";
    std::cout << "Contains(100): " << (ht.Contains(100) ? "true" : "false") << "\n";
    ht.Print();                           // Ver distribución

    //******************************************* */
    std::cout << "\n==== Pruebas HashSet (sin repetidos) ====\n";

    HashSet<int> hset(7);                 // Hereda de HashTableChaining
    hset.Add(14); hset.Add(21); hset.Add(28);
    hset.Add(14);                          // Repetido → ignorado
    hset.Add(35);                          // Mismo bucket que 0 (35%7=0)
    std::cout << "Contains(14): " << (hset.Contains(14) ? "true" : "false") << "\n";
    std::cout << "Contains(35): " << (hset.Contains(35) ? "true" : "false") << "\n";
    hset.Print();                          // No debe repetir 14

    std::cout << "\nListo.\n";
    return 0;                             
}
