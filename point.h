#pragma once
#include <iostream>
using namespace std;

template <class T>
struct Status	// состояние указателя
{
    T* RealPtr;	// указатель
    int Count;	// счетчик числа ссылок на указатель
};
template <class T>
class Point	// класс-указатель
{
    Status<T>* StatPtr;
public:
    Point(T* ptr = 0);	            // конструктор
    Point(const Point&);	        // копирующий конструктор
    ~Point();                       // деструктор
    Point& operator=(const Point&);	// перегрузка операции =
    T *operator->() const;          // перегрузка операции ->
    template<class U>
    friend ostream& operator<<(ostream& os, const Point<U>& point);
    bool operator==(const Point<T>& point);
};

template <class T> Point<T>::Point(T* ptr)
{
    if (!ptr) StatPtr = NULL;	// указатель на объект пустой
    else
    {
        StatPtr = new Status<T>;

        StatPtr->RealPtr = ptr;	// инициализирует объект указателем
        StatPtr->Count = 1;	    // счетчик «прикрепленных» объектов
    }
}

template <class T>	// описание конструктора копирования
Point<T>::Point(const Point& p) : StatPtr(p.StatPtr)
{
    if (StatPtr) StatPtr->Count++; // только увеличение числа ссылок
}

template <class T>
Point<T>::~Point()	// описание деструктора
{
    if (StatPtr)
    {
        StatPtr->Count--;	        // уменьшается число ссылок на объект
        if (StatPtr->Count <= 0)	// если число ссылок на объект меньше
        {	                        // либо равно нулю, то уничтожается объект
            delete StatPtr->RealPtr;
            delete StatPtr;
        }
    }
}

template <class T>
T* Point<T>::operator->() const
{
    if (StatPtr)
        return StatPtr->RealPtr;
    else
        return NULL;
}
template <class T>
Point<T>& Point<T>::operator=(const Point& p)   // отсоединение объекта,расположенного слева от знака «=» от указателя
{
    if (StatPtr)
    {
        StatPtr->Count--;           	// уменьшаем счетчик «прикрепленных» объектов
        if (StatPtr->Count <= 0)	    // если объектов нет, то так же, как и в
        {                       		// деструкторе выполняется освобождение
            delete StatPtr->RealPtr;    // выделенной под объект динамической памяти
            delete StatPtr;
        }
    }
    StatPtr = p.StatPtr;                // присоединение к новому указателю
    if(StatPtr)
        StatPtr->Count++;               // увеличиваем счетчик «прикрепленных» объектов
    return *this;
}

template<class T>
ostream& operator<<(ostream& os, const Point<T>& point) {
    os << (*point.StatPtr->RealPtr);
    return os;
}

template<class T>
bool Point<T>::operator==(const Point<T>& point) {
    return (*this->StatPtr->RealPtr) == (*point.StatPtr->RealPtr);
}