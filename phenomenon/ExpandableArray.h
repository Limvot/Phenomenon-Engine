#ifndef EXPANDABLEARRAY_H
#define EXPANDABLEARRAY_H

#define ARRAY_INCREASE_AMMOUNT 1

#ifndef NULL
#define NULL 0
#endif //NULL

///////////////////////////
//NOTE:
///////////////////////////
//This class is not that safe, it does not check that mem alloc was sucessful.
//TODO: Check if mem alloc is sucessful.

template <class T>
class ExpandableArray
{
    T *Array;
    T *tmp_Array;
    unsigned int NumArraySlots;
    unsigned int UsedSlots;

    public:

    ExpandableArray();
    ~ExpandableArray();

    T getArrayMember(unsigned int);
    unsigned int setArrayMember(unsigned int,T);
    unsigned int addArrayMember(T);
    unsigned int removeArrayEnd(unsigned int);
};

template <class T>
ExpandableArray<T>::ExpandableArray()
{
    Array = new T[1];
    NumArraySlots = 1;
    UsedSlots = 0;
    tmp_Array = NULL;
}

template <class T>
ExpandableArray<T>::~ExpandableArray()
{
    if (Array != NULL)
    {
        delete [] Array;
        Array = NULL;
    }

    if (tmp_Array != NULL)
    {
        delete [] tmp_Array;
        tmp_Array = NULL;
    }
}

template <class T>
T ExpandableArray<T>::getArrayMember(unsigned int index)
{
    return Array[index];
}

template <class T>
unsigned int ExpandableArray<T>::setArrayMember(unsigned int index, T item)
{
    if (index >= NumArraySlots)
    {
        return 1;
    } else {
        Array[index] = item;
        return 0;
    }
}

template <class T>
unsigned int ExpandableArray<T>::addArrayMember(T item)
{
    if (NumArraySlots > UsedSlots)          //If we have extra allocated slots, use one
    {
        Array[UsedSlots] = item;
        UsedSlots += 1;

        return (UsedSlots - 1);             //Return index number

    }

    for (unsigned int i = 0; i < NumArraySlots; i++)        //If we have an empty slot were something was deleted, use it
    {
        if (Array[i] == NULL)
        {
            Array[i] = item;
            return (i);
        }
    }

    tmp_Array = new T[UsedSlots + ARRAY_INCREASE_AMMOUNT];      //If neither of the above, add on to the end of the array.
    unsigned int i = 0;
    while (i<UsedSlots)
    {
        tmp_Array[i] = Array[i];
        i += 1;
    }
    delete [] Array;
    Array = tmp_Array;
    tmp_Array = NULL;

    NumArraySlots += ARRAY_INCREASE_AMMOUNT;
    Array[UsedSlots] = item;
    UsedSlots += 1;

    return (UsedSlots - 1);             //Return index number
}

template <class T>
unsigned int ExpandableArray<T>::removeArrayEnd(unsigned int numToDelete)
{
        tmp_Array = new T[UsedSlots - numToDelete];
        unsigned int i = 0;
        while (i<(UsedSlots-numToDelete))
        {
            tmp_Array[i] = Array[i];
            i += 1;
        }
        delete [] Array;
        Array = tmp_Array;
        tmp_Array = NULL;

        NumArraySlots -= numToDelete;
        UsedSlots -= numToDelete;

        return 0;
}

#endif // EXPANDABLEARRAY_H
