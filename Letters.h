#pragma once

#include <string>

#include "Item.h"

using namespace std;

namespace Letters
{
    static const wstring Name = L"letters";

    static const wstring Alphabet = L"ABCDEFGHZXV";

    static const ItemMap Letters = make_itemmap(Alphabet);
}
