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
    int NumArraySlots;
    int UsedSlots;

    public:

    ExpandableArray();
    ~ExpandableArray();

    T getArrayMember(int);
    int setArrayMember(int,T);
    int addArrayMember(T);
    int removeArrayEnd(int);
};

template <class T>
ExpandableArray<T>::ExpandableArray()
{
    Array = new T[2];
    NumArraySlots = 2;
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
T ExpandableArray<T>::getArrayMember(int index)
{
    return Array[index];
}

template <class T>
int ExpandableArray<T>::setArrayMember(int index, T item)
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
int ExpandableArray<T>::addArrayMember(T item)
{
    if (NumArraySlots > UsedSlots)
    {
        Array[UsedSlots] = item;
        UsedSlots += 1;

        return (UsedSlots - 1);             //Return index number

    } else {

        tmp_Array = new T[UsedSlots + ARRAY_INCREASE_AMMOUNT];
        int i = 0;
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
}

template <class T>
int ExpandableArray<T>::removeArrayEnd(int numToDelete)
{
        tmp_Array = new T[UsedSlots - numToDelete];
        int i = 0;
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
