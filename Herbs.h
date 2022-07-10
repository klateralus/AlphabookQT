#pragma once

#include <string>
#include <vector>

#include "Item.h"

using namespace std;

namespace Herbs
{
    static const wstring Name = L"herbs";

    static const vector<wstring> MostPopular{ L"Basil", L"Cilantro", L"Dill", L"Mint", L"Oregano",
                                             L"Parsley ", L"Curly", L"Rosemary", L"Sage", L"Thyme" };

    static const ItemMap Herbs = make_itemmap(MostPopular);
}