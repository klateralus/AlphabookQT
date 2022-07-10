#pragma once

struct IGameMode
{
    virtual void StartGame() = 0;
    virtual void FinishGame() = 0;
};