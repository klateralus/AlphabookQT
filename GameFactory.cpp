#include "GameFactory.h"

#include "Animals.h"
#include "Digits.h"
#include "Herbs.h"
#include "Letters.h"

#include "GameMode.h"


UGameFactory::UGameFactory()
{
    modes.emplace(Animals::Name, Animals::Animals);
    modes.emplace(Digits::Name, Digits::Digits);
    modes.emplace(Herbs::Name, Herbs::Herbs);
    modes.emplace(Letters::Name, Letters::Letters);
}

vector<wstring> UGameFactory::Modes() const
{
    vector<wstring> result;
    for(const auto& pair: modes)
    {
        result.emplace_back(pair.first);
    }
    return result;
}

shared_ptr<IGameMode> UGameFactory::GameMode(const wstring& name) const
{
    const auto it = modes.find(name);
    
    if (it != modes.end())
    {
        shared_ptr<IGameMode> game_mode = make_shared<UGameMode>(it->first, it->second);
        return game_mode;
    }

    return nullptr;
}

wostream& operator<<(wostream& os, const UGameFactory& factory)
{
    os << L"------------------------------------------------\n";
    os << L"Welcome to the ALPHABET GAME!\n";
    os << L"------------------------------------------------\n\n";
    os << L"You can choose one of the game modes to play: \n";
    auto it = factory.modes.begin();
    auto end = factory.modes.end();
    while (it != end)
    {
        os << it->first;
        if (next(it) != end)
        {
            os << " | ";
        }
        ++it;
    }
    os << "\n";
    os << L"------------------------------------------------\n";
    os << "Type in the name of the game mode: ";
    return os;
}
