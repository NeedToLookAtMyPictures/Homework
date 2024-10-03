#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include "StringData.h"
using namespace std;

int linear_search(const vector<string>& data, const string& element)
{
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i] == element)
        {
            return i;
        }
    }
    return -1;
}

int binary_search(const vector<string>& data, const string& element)
{
    int start = 0;
    unsigned long long end = data.size();
    unsigned long long mid = (start + end) / 2;
    do {
        if (data[mid] == element)
        {
            return mid;
        }
        else if (element > data[mid])
        {
            start = ++mid;
            mid = (start + end) / 2;
        }
        else
        {
            end = mid;
            mid = (start + end) / 2;
        }
    } while (end > start);
    return -1;
}

int main()
{
    vector<string> string_data = getStringData();
    auto begin = systemTimeNanoseconds();
    cout << linear_search(string_data, "not_here") << endl;
    auto end = systemTimeNanoseconds();
    cout << "linear - not_here " << (end-begin) << endl;
    begin = systemTimeNanoseconds();
    cout << binary_search(string_data, "not_here") << endl;
    end = systemTimeNanoseconds();
    cout << "binary - not_here " << (end-begin) << endl;
    begin = systemTimeNanoseconds();
    cout << linear_search(string_data, "mzzzz") << endl;
    end = systemTimeNanoseconds();
    cout << "linear - mzzzz " << (end-begin) << endl;
    begin = systemTimeNanoseconds();
    cout << binary_search(string_data, "mzzzz") << endl;
    end = systemTimeNanoseconds();
    cout << "binary - mzzzz " << (end-begin) << endl;
    begin = systemTimeNanoseconds();
    cout << linear_search(string_data, "aaaaa") << endl;
    end = systemTimeNanoseconds();
    cout << "linear - aaaaa " << (end-begin) << endl;
    begin = systemTimeNanoseconds();
    cout << binary_search(string_data, "aaaaa") << endl;
    end = systemTimeNanoseconds();
    cout << "binary - aaaaa " << (end-begin) << endl;
    return 0;
}
