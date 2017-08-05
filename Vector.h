#pragma once

#include <iostream>

using namespace std;

/**
 *
 * The Vector class contains the functions and variables that
 * reflect the vector class in the standard C++ library. This
 * Vector class will be mainly used as a replacement for the
 * standard vector class in CSE 2341.
 *
 * An Vector offers flexibility in terms of expandability and size,
 * unlike an array which has a fixed size after it is created.
 * (While the Vector class uses an array as the underpinned
 *  data structure, the user does not see this.)
 *
 * By using different values for capacity and length, the Vector can cut
 * down on add times. The capacity value is the actual size of the arr array,
 * while the length is the size of the user's usable part of the array.
 * This allows the user to retrieve values and add values most of the time
 * at constant time, but the time to add an object to the end of the array
 * will change when the length and capacity are equal.
 *
*/

template<class T>
class Vector
{
    private:

        int length;     //user's known size of the array
        int capacity;   //actual size of the array
        T* arr;


        //Resizes the array based on the newCapacity,
        //and sets the capacity variable to the newCapacity
        void resize(int newCapacity);

        //Checks if the index is in bounds, otherwise throws
        //an out_of_bounds exception
        bool inBounds(int index, const char funcName[] = __FUNCTION__) const;

    public:

        //Constructors
        Vector();
        Vector(const Vector<T>&);               //Copy constructor


        //Operator= functions
        Vector& operator= (const Vector<T>&);   //Copy assignment operator

        //Accessor functions
        T& operator[] (int index) const;
        T& at(int index) const;
        T& front() const;
        T& back() const;

        //Functions to add to array
        void pushBack(const T& data);
        void insert(int index, const T& data);
        void assign(int index, const T& data);

        //Removal functions
        void popBack();
        void remove(int index);

        //Size functions
        int size() const;
        bool empty() const;
        void clear();

        //Insertion sort functions, using the insertion sort algorithm
        void insertionSortHigh();
        void insertionSortLow();

        //Destructor
        ~Vector();
};


/**
 * Resizes the array to the newCapacity, and changes the
 * capacity variable to newCapacity. This function allows
 * all resizing of the array to remain in one function.
 *
 * @param newCapacity - the new size of the array and new value of capacity
 *
*/
template<class T>
void Vector<T>::resize(int newCapacity)
{
    T* newArray = new T[newCapacity];   //create new array

    for(int i{}; i < length; i++)       //copy data
        newArray[i] = arr[i];

    delete[] arr;                       //deleting array to stop memory leaks
    arr = newArray;
    newArray = nullptr;

    capacity = newCapacity;             //set new capacity
}

/**
 * inBounds returns true if the index is within the bounds of the
 * array. Otherwise it throws an out_of_range exception using
 * the function name that called the function
 *
 * @param index - the index to check against the function
 * @param funcName - the name of the function that called inBounds for
 *                   easier debugging
 * @return true if the index is within the bounds of the array, otherwise
 *         and exception will be thrown
 */
template<class T>
bool Vector<T>::inBounds(int index, const char funcName[]) const
{
    if ((index >= 0) & (index < length)) //checks if the index is within the array
    {
        return true;
    }
    throw std::out_of_range(funcName);
}

/**
 *  Default constructor
 */
template<class T>
Vector<T>::Vector() : length{0}, capacity{10}, arr{new T[capacity]}
{}


/**
 *
 * Copy constructor
 *
 * @param list - a const Vector reference to copy to this Vector
 *
 */
template<class T>
Vector<T>::Vector(const Vector<T>& list) : length{list.length}, capacity{list.capacity}, arr{new T[capacity]}
{
    for(int i{}; i < length; i++)   //copy all data
    {
        arr[i] = list[i];
    }
}

/**
 * Copy assignment operator
 *
 * @param list - a const Vector reference containing the data to copy to this
 */
template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& list)
{
    delete[] arr;                        //delete data to stop leaks
    length = list.length;                //copy all data from list
    capacity = list.capacity;
    arr = new T[capacity];

    for(int i{}; i < list.size(); i++)   //copy data
    {
        arr[i] = list[i];
    }

    return *this;
}



/**
 * access operator
 *
 * @param index to retrieve data from array
 * @return the object if the index is within bounds,
 *         will throw exception otherwise
 */
template<class T>
T& Vector<T>::operator[](int index) const
{
    inBounds(index, __FUNCTION__);
    return arr[index];
}


/**
 * at() - accessor function
 *
 * @param index to retrieve data from array
 * @return the object if the index is within bounds,
 *         will throw exception otherwise
 */
template<class T>
T& Vector<T>::at(int index) const
{
    inBounds(index, __FUNCTION__);
    return arr[index];
}


/**
 * access operator
 *
 * @return the first object in the list
 */
template<class T>
T& Vector<T>::front() const
{
    return arr[0];
}

/**
 * access operator
 *
 * @return the last object in the list
 */
template<class T>
T& Vector<T>::back() const
{
    return arr[length-1];
}

/**
 * back() - removes the last object in the list, and will throw
 * an exception if the function does not contain any objects
 */
template<class T>
void Vector<T>::popBack()
{
    if(length == 0)
        throw std::out_of_range("Length = 0 - popBack in Vector class");
    length--;
}

/**
 * pushBack() - adds the data object to the end of the array
 *
 * @param data - added to the end of the array
 */
template<class T>
void Vector<T>::pushBack(const T& data)
{
    if(length == capacity)
    {
        resize(capacity *= 1.5);
    }
    arr[length] = data;
    length++;
}

/**
 * insert() - adds adds the data to the index of the array,
 * then moves all the data that comes after the new object
 * down towards the end
 *
 * @param index where the data will be added
 * @param data that will be added to the array at the index
 */
template<class T>
void Vector<T>::insert(int index, const T& data)
{
    //uses pushBack if data is at the en
    if(index == length)
        pushBack(data);
    else
    {
        inBounds(index, __FUNCTION__);
        if(length == capacity)
            resize(capacity*= 1.5);

        //moves old data down the list after new data is added
        for(int i{length}; i >= index + 1; i--)
        {
            arr[i] = arr[i-1];
        }
        arr[index] = data;
        length++;
    }

}


/**
 * Sets the object at the index given of the array to the given data
 *
 * @param index where the object will be placed
 * @param data to place at the index
 */
template<class T>
void Vector<T>::assign(int index, const T& data)
{
    inBounds(index, __FUNCTION__);
    arr[index] = data;
}

/**
 * Removes the object at the given index
 *
 * @param index where the object will be removed
 */
template<class T>
void Vector<T>::remove(int index)
{
    inBounds(index, __FUNCTION__);


    //if the index is the end index, then the popBack function can be called
    if(index == length-1)
    {
        popBack();
        return;
    }

    //Clears if there's nothing left in the list
    if(index == 0 && length == 1)
        clear();
    else
    {
        //Resizes the array if the capacity needs to be resized
        if(static_cast<int>(capacity / 1.5) == length && capacity > 10)
            resize(capacity / 1.5);

        //Moves the data down to effectively remove the data
        for (int i{ index }; i < length - 1; i++)
        {
            arr[i] = arr[i + 1];
        }

    }
    length --;

}

/**
 * @return the user size (length) of the array
 */
template<class T>
int Vector<T>::size() const
{
    return length;
}

/**
 * @return true if the length is 0, false otherwise
 */
template<class T>
bool Vector<T>::empty() const
{
    return length == 0;
}

/**
 * Clears the array and resets all variables to their
 * original state
 */
template<class T>
void Vector<T>::clear()
{
    length = 0;
    resize(10);
}

/**
 * insertionSortHigh uses the insertion sort algorithm to sort
 * the objects in the vector with the highest value at the beginning
 * of the list, and the lowest at the end.
 */
template<class T>
void Vector<T>::insertionSortHigh()
{
    int j{};                                //uses j to determine index for swap
    T t{};                                  //temp variable
    for(int i{1}; i < size(); i++)
    {
        for(j = i; j > 0 && arr[j-1] < arr[j]; j--)
        {
            t = arr[j];                     //swap data
            arr[j] = arr[j-1];
            arr[j-1] = t;
        }
    }
}


/**
 * insertionSortLow uses the insertion sort algorithm to sort
 * the objects in the vector with the highest value at the end
 * of the list, and the lowest at the beginning.
 */
template<class T>
void Vector<T>::insertionSortLow()
{

    int j{};                                //uses int to find index to swap
    T t{};                                  //temp variable
    for(int i{1}; i < size(); i++)
    {
        for(j = i; j > 0 && arr[j-1] > arr[j]; j--)
        {
            t = arr[j];                     //swap data
            arr[j] = arr[j-1];
            arr[j-1] = t;
        }
    }
}


/**
 * Destructor that deletes the array when the object will not be called again
 */
template<class T>
Vector<T>::~Vector()
{
    if(arr != nullptr)
    {
        delete[] arr;
    }
}

/**
 * operator<< overload for easier output for the Vector class
 *
 * Example output using an integer Vector:
 * [1 2 3 4 5 6 7 8 9 10
 *  10 11 12 13 14 15]
 *
 * @param o - ostream to place data in
 * @param a - the const Vector reference to get data to place in ostream
 *
 * @return the ostream that will use the operator<< to output data
 *
 */
template<class S>
std::ostream& operator<<(std::ostream& o, const Vector<S>& a)
{

    o << "[" ;
    for(int i{}; i < a.size(); i++)
    {
        if(i % 10 == 0)
            o << endl << "\t";
        o << a[i] << " ";
    }
    o << "\n]" ;
    return o;
}
