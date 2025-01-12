#include "DoubleMap.h"

template <typename _type>
DoubleMap<_type>::DoubleMap() {}

template <typename _type>
DoubleMap<_type>::DoubleMap(int _size, string baseKey)
{
    for (int i = 0; i < _size; i++)
    {
        string key = baseKey + to_string(i);
        _type* value = new _type();
        m[key] = value;
        v.push_back(value);
    }
    size = _size;
}

template <typename _type>
DoubleMap<_type>::DoubleMap(const initializer_list<pair<string, _type>>& initList)
{
    for (const auto & pair : initList)
    {
        _type* value = new _type(pair.second);
        m[pair.first] = value;
        v.push_back(value);
        size++;
    }
}

template <typename _type>
_type & DoubleMap<_type>::operator[](const string & key)
{
    return *(m[key]);
}

template <typename _type>
_type & DoubleMap<_type>::operator[](int index)
{
    return *(v.at(index));
}

template <typename _type>
void DoubleMap<_type>::append(const string & key, const _type & value)
{
    size++;
    _type* newValue = new _type(value);
    m[key] = newValue;
    v.push_back(newValue);
}

template <typename _type>
void DoubleMap<_type>::erase(int index)
{
    if (index < v.size())
    {
        m.erase(keyAtIndex(index));
        v.erase(v.begin() + index);
        size--;
    }
}

template <typename _type>
int DoubleMap<_type>::length()
{
    return size;
}

template <typename _type>
string DoubleMap<_type>::keyAtIndex(int index)
{
    if (index < v.size())
    {
        int i = 0;
        for (const auto& pair : m)
        {
            if (i == index)
                return pair.first;
            i++;
        }
    }
    return "";
}

template <typename _type>
int DoubleMap<_type>::indexAtKey(string key)
{
    if (m.find(key) != m.end())
    {
        int i = 0;
        for (const auto& pair : m)
        {
            if (pair.first == key)
                return i;
            i++;
        }
    }
    return -1;
}