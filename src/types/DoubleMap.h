#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

template <typename _type>
class DoubleMap
{
public:
    DoubleMap();
    DoubleMap(int size, string baseKey = "k");
    DoubleMap(const initializer_list<pair<string, _type>>& initList);

    _type & operator[](const string & key);
    _type & operator[](int index);

    void erase(int index);
    void append(const string & key, const _type & value);
    int length();
    string keyAtIndex(int index);
    int indexAtKey(string key);

private:
    std::map<string, _type*> m;
    vector<_type*> v;
    int size = 0;
};

#include "DoubleMap.cpp"