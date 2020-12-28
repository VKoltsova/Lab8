#pragma once
#include <iostream>
using namespace std;

template <class T>
struct Status	// ��������� ���������
{
    T* RealPtr;	// ���������
    int Count;	// ������� ����� ������ �� ���������
};
template <class T>
class Point	// �����-���������
{
    Status<T>* StatPtr;
public:
    Point(T* ptr = 0);	            // �����������
    Point(const Point&);	        // ���������� �����������
    ~Point();                       // ����������
    Point& operator=(const Point&);	// ���������� �������� =
    T *operator->() const;          // ���������� �������� ->
    template<class U>
    friend ostream& operator<<(ostream& os, const Point<U>& point);
    bool operator==(const Point<T>& point);
};

template <class T> Point<T>::Point(T* ptr)
{
    if (!ptr) StatPtr = NULL;	// ��������� �� ������ ������
    else
    {
        StatPtr = new Status<T>;

        StatPtr->RealPtr = ptr;	// �������������� ������ ����������
        StatPtr->Count = 1;	    // ������� ��������������� ��������
    }
}

template <class T>	// �������� ������������ �����������
Point<T>::Point(const Point& p) : StatPtr(p.StatPtr)
{
    if (StatPtr) StatPtr->Count++; // ������ ���������� ����� ������
}

template <class T>
Point<T>::~Point()	// �������� �����������
{
    if (StatPtr)
    {
        StatPtr->Count--;	        // ����������� ����� ������ �� ������
        if (StatPtr->Count <= 0)	// ���� ����� ������ �� ������ ������
        {	                        // ���� ����� ����, �� ������������ ������
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
Point<T>& Point<T>::operator=(const Point& p)   // ������������ �������,�������������� ����� �� ����� �=� �� ���������
{
    if (StatPtr)
    {
        StatPtr->Count--;           	// ��������� ������� ��������������� ��������
        if (StatPtr->Count <= 0)	    // ���� �������� ���, �� ��� ��, ��� � �
        {                       		// ����������� ����������� ������������
            delete StatPtr->RealPtr;    // ���������� ��� ������ ������������ ������
            delete StatPtr;
        }
    }
    StatPtr = p.StatPtr;                // ������������� � ������ ���������
    if(StatPtr)
        StatPtr->Count++;               // ����������� ������� ��������������� ��������
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