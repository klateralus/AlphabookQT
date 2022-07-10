#pragma once

#include <string>

#include "Item.h"

using namespace std;

namespace Digits
{
    static const wstring Name = L"digits";

    static const wstring Decimals = L"0123456789";

    static const ItemMap Digits = make_itemmap(Decimals);
}