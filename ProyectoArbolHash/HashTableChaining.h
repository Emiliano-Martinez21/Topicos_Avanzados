#pragma once                                 

#include <iostream>                            
#include <cmath>                            
#include <vector>                               
using namespace std;                           


double log_base_n(double x, double base);       // log en base n
int MinimaAlturaDeArbol(int numeroDeNodos, int maximoDeHijosPorNodo); // altura mínima teórica

template <typename T>
class BinarySearchTree
{
    // Nodo del árbol 
    template <typename T>
    class TreeNode
    {
    public:
        TreeNode() { parent = leftChild = rightChild = nullptr; data = {}; } // Ctor default
        TreeNode(T data) { parent = leftChild = rightChild = nullptr; this->data = data; } // Ctor con valor
        T data;                          // Valor del nodo
        TreeNode<T>* parent;             // Puntero al padre
        TreeNode<T>* leftChild;          // Hijo izquierdo
        TreeNode<T>* rightChild;         // Hijo derecho
    };

public:
    BinarySearchTree() { root = nullptr; count = 0; } // Árbol vacío

    void AddWithAddRecursive(T value)      // Inserción que delega a recursivo
    {
        if (root == nullptr)               // Si está vacío
        {
            root = new TreeNode<T>(value); // Crear raíz
            count++;                       // Contar nodo
            return;                        // Salir
        }
        TreeNode<T>* currentNode = root;   // Desde la raíz
        AddRecursive(value, currentNode);  // Insertar recursivo
    }

    void InsertarNode(TreeNode<T>* currentNode, bool isLeftChild, T value) // Crea y conecta nodo
    {
        TreeNode<T>* newNode = new TreeNode<T>(value); // Nuevo nodo
        newNode->parent = currentNode;                 // Apunta al padre
        if (isLeftChild) currentNode->leftChild = newNode;  // Colgar a izquierda
        else             currentNode->rightChild = newNode; // o derecha
        count++;                                       // Incrementar tamaño
    }

 
    void AddRecursive(T value, TreeNode<T>* currentNode)
    {
        if (value > currentNode->data)                 // Va a la derecha?
        {
            if (currentNode->rightChild == nullptr)    // Lugar libre
            {
                InsertarNode(currentNode, false, value); // Insertar derecha
                return;                                 
            }
            else return AddRecursive(value, currentNode->rightChild); // Bajar a derecha
        }
        else                                           // value <= data → izquierda (incluye duplicados)
        {
            if (currentNode->leftChild == nullptr)     // Lugar libre
            {
                InsertarNode(currentNode, true, value); // Insertar izquierda
                return;                                  
            }
            else return AddRecursive(value, currentNode->leftChild); // Bajar a izquierda
        }
    }

    // Inserción iterativa (sin recursión)
    void Add(T value)
    {
        if (root == nullptr)                   // Árbol vacío
        {
            root = new TreeNode<T>(value);     // Crear raíz
            count++;                            // Contar
            return;                             
        }

        TreeNode<T>* currentNode = root;       // Desde la raíz
        while (currentNode != nullptr)         // Mientras haya donde comparar
        {
            if (value > currentNode->data)     // Derecha?
            {
                if (currentNode->rightChild == nullptr) { InsertarNode(currentNode, false, value); return; } // Insertar
                else currentNode = currentNode->rightChild; // Bajar
            }
            else                                // value <= data → izquierda
            {
                if (currentNode->leftChild == nullptr) { InsertarNode(currentNode, true, value); return; }  // Insertar
                else currentNode = currentNode->leftChild; // Bajar
            }
        }
    }

    void InOrderWithRecursive() { InOrderRecursive(root); } // In-order (wrapper)

    int MinimaAltura() { return MinimaAlturaDeArbol(count, 2); } // Altura mínima teórica

    TreeNode<T>* root;                 // Raíz del árbol
    int count;                         // Número de nodos

    bool SearchWithRecursive(T value)  // Búsqueda recursiva (bool)
    {
        TreeNode<T>* resultNode = SearchRecursive(root, value); // Encontrar nodo
        return resultNode != nullptr;                           // Existe?
    }

    bool Search(T value)               // Búsqueda iterativa (bool)
    {
        TreeNode<T>* current = root;   // Desde raíz
        while (current != nullptr)     // Mientras haya nodos
        {
            if (value == current->data) return true;                      // Encontrado
            current = (value < current->data) ? current->leftChild        // Menor-izquierda
                                              : current->rightChild;      // Mayor - derecha
        }
        return false;                  // No encontrado
    }

    void Delete(T value)               // Borrar un valor (3 casos)
    {
        TreeNode<T>* nodeToDelete = SearchRecursive(root, value); // Buscar nodo
        if (nodeToDelete == nullptr) { cout << "no existe el valor value en este árbol." << endl; return; } // No está

        // Caso 1: hoja (sin hijos)
        if (nodeToDelete->leftChild == nullptr && nodeToDelete->rightChild == nullptr)
        {
            if (nodeToDelete->parent->leftChild == nodeToDelete) nodeToDelete->parent->leftChild = nullptr; // Desconectar izq
            else                                                 nodeToDelete->parent->rightChild = nullptr; // o der
            count--; delete nodeToDelete; return; // Liberar y salir
        }

        // Caso 2a: solo hijo derecho
        if (nodeToDelete->leftChild == nullptr && nodeToDelete->rightChild != nullptr)
        {
            if (nodeToDelete->parent->leftChild == nodeToDelete) nodeToDelete->parent->leftChild = nodeToDelete->rightChild; // Reenlazar
            else                                                 nodeToDelete->parent->rightChild = nodeToDelete->rightChild;
            nodeToDelete->rightChild->parent = nodeToDelete->parent; // Ajustar parent
            delete nodeToDelete; count--; return; 
        }
        // Caso 2b: solo hijo izquierdo
        else if (nodeToDelete->leftChild != nullptr && nodeToDelete->rightChild == nullptr)
        {
            if (nodeToDelete->parent->leftChild == nodeToDelete) nodeToDelete->parent->leftChild = nodeToDelete->leftChild; // Reenlazar
            else                                                 nodeToDelete->parent->rightChild = nodeToDelete->leftChild;
            nodeToDelete->leftChild->parent = nodeToDelete->parent; // Ajustar parent
            delete nodeToDelete; count--; return; // Liberar y salir
        }

        // Caso 3: dos hijos → usar sucesor (mínimo del subárbol derecho)
        TreeNode<T>* successorNode = Successor(nodeToDelete);       // Buscar sucesor
        successorNode->leftChild = nodeToDelete->leftChild;         // Hereda hijo izq
        nodeToDelete->leftChild->parent = successorNode;            // Ajustar parent del hijo izq

        // Desacoplar sucesor de su padre original
        if (successorNode->parent->leftChild == successorNode)      // Si era hijo izq
            successorNode->parent->leftChild = successorNode->rightChild; // Enlazar con su der
        else                                                        // Si era hijo der
            successorNode->parent->rightChild = successorNode->rightChild;

        if (successorNode->rightChild != nullptr)                   // Bugfix: checar nullptr
            successorNode->rightChild->parent = successorNode->parent; // Ajustar parent del nuevo enlace

        successorNode->rightChild = nodeToDelete->rightChild;       // Hereda hijo der del borrado
        nodeToDelete->rightChild->parent = successorNode;           // Ajustar parent del hijo der

        successorNode->parent = nodeToDelete->parent;               // Sucesor toma el lugar del borrado
        if (nodeToDelete->parent->leftChild == nodeToDelete)        // Reenlazar desde el padre del borrado
            nodeToDelete->parent->leftChild = successorNode;
        else
            nodeToDelete->parent->rightChild = successorNode;

        count--; delete nodeToDelete;                               // Contar y liberar
    }

    void Clear()                        // Borrar todo el árbol (iterativo post-orden)
    {
        ClearIterative(root);           // Borrar nodos
        root = nullptr;                 // Vaciar raíz
        count = 0;                      // Resetear tamaño
    }

    void PostOrderIterative()           // Imprimir post-orden sin recursión
    {
        if (root == nullptr) return;    // Nada que imprimir
        vector<TreeNode<T>*> s1, s2;    // Dos pilas (vectores)
        s1.push_back(root);             // Empezar en raíz
        while (!s1.empty())             // Mientras haya por procesar
        {
            TreeNode<T>* node = s1.back(); s1.pop_back(); // Tomar tope
            s2.push_back(node);                            // Apilar para invertir
            if (node->leftChild)  s1.push_back(node->leftChild);   // Primero izq
            if (node->rightChild) s1.push_back(node->rightChild);  // Luego der
        }
        for (auto it = s2.rbegin(); it != s2.rend(); ++it)         // Recorrer invertido
            cout << (*it)->data << endl;                           // Visitar nodo
    }

private:
    TreeNode<T>* Minimum(TreeNode<T>* node)    // Mínimo desde node
    {
        TreeNode<T>* minimum = node;           // Comenzar en node
        while (minimum->leftChild != nullptr)  // Ir lo más a la izquierda
            minimum = minimum->leftChild;
        return minimum;                         // Retornar mínimo
    }

    TreeNode<T>* Successor(TreeNode<T>* node)  // Sucesor in-order
    {
        if (node->rightChild != nullptr)       // Si hay subárbol derecho
            return Minimum(node->rightChild);  // Mínimo de ese subárbol
        TreeNode<T>* ancestor = node->parent;  // Subir por ancestros
        while (ancestor != nullptr && node == ancestor->rightChild) // Hasta que seamos hijo izq
        {
            node = ancestor;                   // Subir
            ancestor = node->parent;           // Seguir subiendo
        }
        return ancestor;                       // Puede ser nullptr (sin sucesor)
    }

    TreeNode<T>* SearchRecursive(TreeNode<T>* currentNode, T value) // Búsqueda nodo*
    {
        if (currentNode == nullptr) return nullptr;       // No existe
        if (currentNode->data == value) return currentNode; // Encontrado
        if (value < currentNode->data) return SearchRecursive(currentNode->leftChild, value); // Izq
        return SearchRecursive(currentNode->rightChild, value); // Der
    }

    void InOrderRecursive(TreeNode<T>* node)  // In-order recursivo
    {
        if (node != nullptr)                  // Si hay nodo
        {
            InOrderRecursive(node->leftChild); // Izq
            cout << node->data << endl;        // Visitar
            InOrderRecursive(node->rightChild);// Der
        }
    }

    void ClearIterative(TreeNode<T>* start)   // Borrar subárbol en post-orden (iterativo)
    {
        if (start == nullptr) return;         // Nada que borrar
        vector<TreeNode<T>*> s1, s2;          // Dos pilas
        s1.push_back(start);                  // Empezar
        while (!s1.empty())                   // Procesar todos
        {
            TreeNode<T>* node = s1.back(); s1.pop_back(); // Tomar tope
            s2.push_back(node);                            // Apilar para inversión
            if (node->leftChild)  s1.push_back(node->leftChild);   // Izq
            if (node->rightChild) s1.push_back(node->rightChild);  // Der
        }
        for (auto it = s2.rbegin(); it != s2.rend(); ++it) // Recorrer invertido
            delete *it;                                    // Borrar nodos
    }
};
