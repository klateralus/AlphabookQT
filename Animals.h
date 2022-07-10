#pragma once

#include <string>
#include <vector>

#include "Item.h"

using namespace std;

namespace Animals
{

    static const wstring Name = L"animals";

    static const vector<wstring> MostPopular{ L"Tiger", L"Lion", L"Elephant", L"Giraffe", L"Leopard",
                                             L"Panda", L"Cheetah", L"Bear", L"Wolf", L"Gorilla" };

    static const ItemMap Animals = make_itemmap(MostPopular);
}
