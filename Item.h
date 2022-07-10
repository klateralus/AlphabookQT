#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>

using namespace std;

struct UItem;
typedef shared_ptr<UItem> ItemP;
typedef unordered_map<wstring, shared_ptr<UItem>> ItemMap;
typedef vector<ItemP> ItemVector;


struct UItem
{
    UItem(const wstring& name);
    wstring Name{L"Item"};
};

ItemMap make_itemmap(const wstring& string);
ItemMap make_itemmap(const vector<wstring>& strings);
