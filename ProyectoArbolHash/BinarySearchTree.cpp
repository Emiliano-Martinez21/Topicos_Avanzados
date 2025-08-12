#include <cmath>                        
#include "BinarySearchTree.h"           

double log_base_n(double x, double base) // log base 'base' de x
{
    if (x <= 0.0) return 0.0;           // Proteger dominio
    if (base <= 0.0 || base == 1.0) base = 2.0; // Base segura
    return std::log(x) / std::log(base);        // Cambio de base
}

int MinimaAlturaDeArbol(int numeroDeNodos, int maximoDeHijosPorNodo)
{
    if (numeroDeNodos <= 0) return 0;   // Árbol vacío

    int b = (maximoDeHijosPorNodo < 2) ? 2 : maximoDeHijosPorNodo; // Asegurar b>=2
    double capacityArg = static_cast<double>(numeroDeNodos) * (b - 1) + 1.0; // N*(b-1)+1
    double h = std::ceil( log_base_n(capacityArg, static_cast<double>(b)) ) - 1.0; // Fórmula
    if (h < 0.0) h = 0.0;               // Seguridad numérica
    return static_cast<int>(h);         // Entero
}
