#include "LQueue.h"   // Incluimos la cola con lista ligada
#include "LStack.h"   // Incluimos la pila con forward_list
#include "Figuras.h"  // Incluimos la jerarquía de figuras

int main()
{
    // ========================
    // Prueba de LQueue (Cola)
    // ========================
    LQueue<int> cola;        // Creamos una cola de enteros
    cola.Enqueue(10);        
    cola.Enqueue(20);       
    cout << "Front: " << cola.Front() << endl;    // Mostramos el frente
    cout << "Dequeue: " << cola.Dequeue() << endl; // Quitamos el primer elemento


    // Prueba de LStack (Pila)
    LStack<string> pila;     // Creamos una pila de strings
    pila.Push("Hola");       
    pila.Push("Mundo");      
    cout << "Peek: " << pila.Peek() << endl;      // Vemos el elemento de arriba


    // Prueba de figuras: Círculo
    Figura* f1 = new Circulo(5);   // Creamos un círculo con radio 5
    cout << f1->ObtenerNombreDeFigura() << " → Área: " << f1->CalcularArea() << endl;
    delete f1;  // Liberamos memoria

    // Prueba de figuras: Línea segmentada
    float segmentos[] = {2.0, 3.0, 1.5};   // Arreglo con segmentos
    Figura* f2 = new Linea(segmentos, 3); // Creamos una línea con 3 segmentos
    cout << f2->ObtenerNombreDeFigura() << " → Perímetro: " << f2->CalcularPerimetro() << endl;
    delete f2;  // Liberamos memoria

   
    // Prueba de figura hija: Cubo
    
    Cubo cubo(3);  // Creamos un cubo de lado 3
    cout << "Cubo → Volumen: " << cubo.Volumen() << ", Superficie: " << cubo.Surface() << endl;

    return 0; 
}
