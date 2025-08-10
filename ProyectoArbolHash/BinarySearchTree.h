#pragma once                       

#include <iostream>                
#include <cmath>                   
#include <vector>                  
using namespace std;               

// Declaraciones funciones externas 
double log_base_n(double x, double base); 
int MinimaAlturaDeArbol(int numeroDeNodos, int maximoDeHijosPorNodo); // Calcula altura mínima teórica de un árbol 

// Plantilla para permitir que el árbol funcione 
template <typename T>
class BinarySearchTree
{
    // Clase interna para representar un nodo del árbol binario de búsqueda
    template <typename T>
    class TreeNode
    {
    public:
        // Constructor por defecto: inicializa punteros a nullptr y data con valor por defecto de T
        TreeNode()
        {
            parent = leftChild = rightChild = nullptr; // Todo puntero arranca en null
            data = {};                                 // Data en su estado por defecto
        }

        // Constructor que recibe el dato a guardar en el nodo.
        TreeNode(T data)
        {
            parent = leftChild = rightChild = nullptr; // Sin conexiones al inicio
            this->data = data;                         // Asignamos el valor recibido
        }

        // Campos del nodo
        T data;                    // Valor almacenado en el nodo
        TreeNode<T>* parent;       // Puntero al nodo padre
        TreeNode<T>* leftChild;    // Puntero al hijo izquierdo
        TreeNode<T>* rightChild;   // Puntero al hijo derecho
    };

public:
    // Constructor del árbol: arranca vacío
    BinarySearchTree()
    {
        root = nullptr; // Sin raíz aún
        count = 0;      // Sin nodos aún
    }

    // Inserta usando el helper recursivo AddRecursive.
    void AddWithAddRecursive(T value)
    {
        if (root == nullptr)                 // Si el árbol está vacío
        {
            root = new TreeNode<T>(value);   // Creamos la raíz con ese valor
            count++;                         // Aumenta el conteo de nodos
            return;                          // Terminamos
        }
        TreeNode<T>* currentNode = root;     // Si no está vacío, empezamos desde la raíz
        AddRecursive(value, currentNode);    // Delegamos la inserción a la función recursiva
    }

    // Crea un nuevo nodo como hijo izquierdo o derecho del currentNode
    void InsertarNode(TreeNode<T>* currentNode, bool isLeftChild, T value)
    {
        TreeNode<T>* newNode = new TreeNode<T>(value); // Reservamos un nuevo nodo con el valor
        newNode->parent = currentNode;                  // Su padre es el currentNode
        if (isLeftChild)                                // Dependiendo del flag colgamos a la izquierda o a la derecha.
            currentNode->leftChild = newNode;           // 
        else
            currentNode->rightChild = newNode;         
        count++;                                        // Aumenta el conteo total de nodos
    }

    // Lógica recursiva para insertar un valor respetando el orden BST
    void AddRecursive(T value, TreeNode<T>* currentNode)
    {
        if (value > currentNode->data)                          // Si el valor es mayor, debe ir a la derecha.
        {
            if (currentNode->rightChild == nullptr)             // Si no hay hijo derecho
            {
                InsertarNode(currentNode, false, value);        
                return;                                         
            }
            else
            {
                return AddRecursive(value, currentNode->rightChild); // Si sí hay, bajamos a la derecha
            }
        }
        else if (value < currentNode->data)                     // Si el valor es menor, debe ir a la izquierda
        {
            if (currentNode->leftChild == nullptr)              // Si no hay hijo izquierdo
            {
                InsertarNode(currentNode, true, value);         
                return;                                         
            }
            else
            {
                return AddRecursive(value, currentNode->leftChild); // Si sí hay, bajamos a la izquierda.
            }
        }
        // Si es igual, no se hace nada (este árbol no maneja duplicados por inserción).
    }

    // Inserción ITERATIVA 
    void Add(T value)
    {
        if (root == nullptr)                     // Caso árbol vacío
        {
            root = new TreeNode<T>(value);       // La raíz es el primer nodo
            count++;                              // Contamos el nodo
            return;                               
        }

        TreeNode<T>* currentNode = root;         // Empezamos a recorrer desde la raíz

        while (currentNode != nullptr)           // Mientras haya nodo donde comparar
        {
            if (value > currentNode->data)       // Si el valor va a la derecha
            {
                if (currentNode->rightChild == nullptr)       // Si está libre ese lugar
                {
                    InsertarNode(currentNode, false, value);  // Insertamos a la derecha.
                    return;                                  
                }
                else
                {
                    currentNode = currentNode->rightChild;    // Si no, bajamos a la derecha
                }
            }
            else if (value < currentNode->data)                // Si el valor va a la izquierda
            {
                if (currentNode->leftChild == nullptr)         // Si está libre ese lugar
                {
                    InsertarNode(currentNode, true, value);    // Insertamos a la izquierda.
                    return;                                    
                else
                {
                    currentNode = currentNode->leftChild;      // Si no, bajamos a la izquierda.
                }
            }
            // Si es igual, no hace nada y el while continúa, pero realmente nunca cambia currentNode; en práctica no se insertan duplicados
        }
    }

    // Wrapper para recorrer en-orden usando la versión recursiva privada
    void InOrderWithRecursive()
    {
        InOrderRecursive(root); // Manda a imprimir izquierda -> nodo -> derecha
    }

    // Altura mínima teórica de un BST con 'count' nodos
    int MinimaAltura()
    {
        return MinimaAlturaDeArbol(count, 2); // Llama a la función externa con base=2
    }

    // Campos públicos del árbol:
    TreeNode<T>* root; // Puntero a la raíz del BST
    int count;         // Conteo total de nodos insertados

    // Búsqueda recursiva que devuelve bool 
    bool SearchWithRecursive(T value)
    {
        TreeNode<T>* resultNode = SearchRecursive(root, value); // Busca el nodo
        return resultNode != nullptr;                           // True si lo encontró
    }

    
    bool Search(T value)
    {
        TreeNode<T>* current = root;                // Comenzamos en la raíz
        while (current != nullptr)                  // Mientras haya nodo para comparar
        {
            if (value == current->data) return true;                    // Encontrado
            current = (value < current->data) ?                         // Si es menor vamos a la izquierda, si no, a la derecha.
                      current->leftChild :                              
                      current->rightChild;                              
        }
        return false;                            
    }

    // Borra un nodo que contenga 'value' manejando los 3 casos clásicos
    void Delete(T value)
    {
        TreeNode<T>* nodeToDelete = SearchRecursive(root, value); // Buscamos el nodo por valor

        if (nodeToDelete == nullptr)                              // Si no existe
        {
            cout << "no existe el valor value en este árbol." << endl; // Mensaje informativo
            return;                                                    // No hay nada que borrar
        }

        // Caso 1: no tiene hijos
        if (nodeToDelete->leftChild == nullptr && nodeToDelete->rightChild == nullptr)
        {
            if (nodeToDelete->parent->leftChild == nodeToDelete) // Si soy hijo izquierdo del padre desconecta por la izquierda.
                nodeToDelete->parent->leftChild = nullptr;       // si no, por la derecha.
            else
                nodeToDelete->parent->rightChild = nullptr;      

            count--;                     // Decrementa el conteo de nodos
            delete nodeToDelete;         // Libera memoria del nodo
            return;                      
        }

        // Caso 2a: solo tiene hijo derech
        if (nodeToDelete->leftChild == nullptr && nodeToDelete->rightChild != nullptr)
        {
            if (nodeToDelete->parent->leftChild == nodeToDelete)       // Reasigna el enlace en el padre
                nodeToDelete->parent->leftChild = nodeToDelete->rightChild;
            else
                nodeToDelete->parent->rightChild = nodeToDelete->rightChild;

            nodeToDelete->rightChild->parent = nodeToDelete->parent;   // Ajusta el parent del hijo derecho
            delete nodeToDelete;                                       // Borra el nodo actual
            count--;                                                   // Decrementa conteo
            return;                                                    
        }
        // Caso 2b: solo tiene hijo izquierdo
        else if (nodeToDelete->leftChild != nullptr && nodeToDelete->rightChild == nullptr)
        {
            if (nodeToDelete->parent->leftChild == nodeToDelete)       // Reasigna el enlace en el padre
                nodeToDelete->parent->leftChild = nodeToDelete->leftChild;
            else
                nodeToDelete->parent->rightChild = nodeToDelete->leftChild;

            nodeToDelete->leftChild->parent = nodeToDelete->parent;    // Ajusta el parent del hijo izquierdo
            delete nodeToDelete;                                       // Borra el nodo actual
            count--;                                                   // Decrementa conteo
            return;                                                    
        }

        // Caso 3: tiene dos hijos -> buscamos el sucesor
        TreeNode<T>* successorNode = Successor(nodeToDelete);          // Nunca debería ser nullptr aquí

        successorNode->leftChild = nodeToDelete->leftChild;            // El sucesor hereda el hijo izquierdo
        nodeToDelete->leftChild->parent = successorNode;               // y ese hijo ahora apunta al sucesor como padre

        // Desconectamos al sucesor de su padre original conectando al hijo derecho del sucesor 
        if (successorNode->parent->leftChild == successorNode)         // Si el sucesor era hijo izquierdo
        {
            successorNode->parent->leftChild = successorNode->rightChild; // Su padre ahora apunta al hijo derecho del sucesor
        }
        else
        {
            successorNode->parent->rightChild = successorNode->rightChild; // Igual pero si era hijo derecho.
        }
      
        if (successorNode->rightChild != nullptr)
        {
            successorNode->rightChild->parent = successorNode->parent; // El nuevo hijo se enlaza con el antiguo padre del sucesor
        }

        successorNode->rightChild = nodeToDelete->rightChild;          // El sucesor también hereda el hijo derecho del borrado
        nodeToDelete->rightChild->parent = successorNode;              // Ajustamos el parent de ese hijo derecho.

        successorNode->parent = nodeToDelete->parent;                  // El sucesor se colocará donde estaba el borrado
        if (nodeToDelete->parent->leftChild == nodeToDelete)           // Y conectamos desde el padre del borrado
            nodeToDelete->parent->leftChild = successorNode;           // a izquierda o
        else
            nodeToDelete->parent->rightChild = successorNode;          // a derecha según corresponda.

        count--;                               // Disminuimos conteo de nodos
        delete nodeToDelete;                   // Liberamos memoria del nodo borrado
    }

    
    void Clear()
    {
        ClearIterative(root);  // Borra todos los nodos con técnica de dos pilas
        root = nullptr;        // Árbol vacío
        count = 0;             // Reinicia contador
    }

    // 🔹 4) Imprime Post-Order (izq, der, nodo) de forma iterativa
    void PostOrderIterative()
    {
        if (root == nullptr) return;           // Nada que imprimir si el árbol está vacío.
        vector<TreeNode<T>*> s1, s2;           
