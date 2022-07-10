#include "Item.h"

UItem::UItem(const wstring& name)
    : Name{ name }
{
};

ItemMap make_itemmap(const wstring& string)
{
    ItemMap result;
    for (const auto& i : string)
    {
        const wstring name{ i };
        result.emplace(name, make_shared<UItem>(name));
    }

    return result;
}

ItemMap make_itemmap(const vector<wstring>& strings)
{
    ItemMap result;
    for (const auto& i : strings)
    {
        result.emplace(i, make_shared<UItem>(i));
    }

    return result;
}