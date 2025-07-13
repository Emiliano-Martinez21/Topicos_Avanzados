#pragma once
#include <iostream>
#include <cmath>
#include <string>
using namespace std;

// Clase base abstracta
class Figura
{
protected:
    string nombre;

public:
    Figura(string name) : nombre(name) {}
    virtual ~Figura() {}

    virtual float CalcularArea() = 0;        // Métodos obligatorio
    virtual float CalcularPerimetro() = 0;  

    const string& ObtenerNombreDeFigura() { return nombre; }
};

// Círculo 
class Circulo : public Figura
{
private:
    float radio;

public:
    Circulo(float r) : Figura("Círculo"), radio(r) {}

    float CalcularArea() override { return 3.1416f * radio * radio; }
    float CalcularPerimetro() override { return 2 * 3.1416f * radio; }
};

// Cuadrado 
class Cuadrado : public Figura
{
protected:
    float lado;

public:
    Cuadrado(float l) : Figura("Cuadrado"), lado(l) {}

    float CalcularArea() override { return lado * lado; }
    float CalcularPerimetro() override { return 4 * lado; }
};

// Cubo
class Cubo : public Cuadrado
{
public:
    Cubo(float l) : Cuadrado(l) { nombre = "Cubo"; }

    float Volumen() { return lado * lado * lado; }
    float Surface() { return 6 * lado * lado; }
};

// Figura con N lados 
class FiguraNLados : public Figura
{
private:
    int n;
    float lado;

public:
    FiguraNLados(int lados, float tamLado)
        : Figura("Figura de " + to_string(lados) + " lados"), n(lados), lado(tamLado) {}

    float CalcularArea() override
    {
        return (n * lado * lado) / (4 * tan(3.1416f / n));
    }

    float CalcularPerimetro() override
    {
        return n * lado;
    }
};

// Línea ----------------
class Linea : public Figura
{
private:
    float* segmentos;
    int cantidad;

public:
    Linea(float* segmentosArray, int n) : Figura("Línea"), cantidad(n)
    {
        // Reservamos memoria y copiamos los valores
        segmentos = new float[cantidad];
        for (int i = 0; i < cantidad; i++)
            segmentos[i] = segmentosArray[i];
    }

    ~Linea()
    {
        // Liberamos la memoria
        delete[] segmentos;
    }

    float CalcularArea() override { return 0.0f; }

    float CalcularPerimetro() override
    {
        float suma = 0;
        for (int i = 0; i < cantidad; i++)
            suma += segmentos[i];
        return suma;
    }
};
