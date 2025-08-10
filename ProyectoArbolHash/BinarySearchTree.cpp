
#include <cmath>   
#include "BinarySearchTree.h"

// Calcula logaritmo en base 'base': log_base(x) = ln(x) / ln(base)
double log_base_n(double x, double base)
{
    // Evitar dominios inválidos
    if (x <= 0.0) return 0.0;
    if (base <= 0.0 || base == 1.0) base = 2.0; // base segura

    return std::log(x) / std::log(base);
}

// Altura mínima h de un árbol b-ario con N nodos:
// máxima capacidad a altura h = (b^(h+1) - 1) / (b - 1)
// Resolver para h: h = ceil( log_b( N*(b-1) + 1 ) ) - 1
int MinimaAlturaDeArbol(int numeroDeNodos, int maximoDeHijosPorNodo)
{
    if (numeroDeNodos <= 0) return 0;

    int b = (maximoDeHijosPorNodo < 2) ? 2 : maximoDeHijosPorNodo;
    double capacityArg = static_cast<double>(numeroDeNodos) * (b - 1) + 1.0;

    double h = std::ceil( log_base_n(capacityArg, static_cast<double>(b)) ) - 1.0;
    if (h < 0.0) h = 0.0; // por seguridad numérica

    return static_cast<int>(h);
}
