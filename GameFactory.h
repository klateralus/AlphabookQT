#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "IGameMode.h"
#include "Item.h"


using namespace std;


struct UGameFactory
{

    UGameFactory();

    shared_ptr<IGameMode> GameMode(const wstring& name) const;
    vector<wstring> Modes() const;

    friend wostream& operator<<(wostream& os, const UGameFactory& factory);
    
private:
    unordered_map<wstring, ItemMap> modes;

};
