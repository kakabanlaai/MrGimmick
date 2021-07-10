#pragma once
#include "BotState.h"

class BotStandingState : public BotState
{
public:
    BotStandingState(BotData* botData);
    ~BotStandingState();

    void HandleKeyboard(std::map<int, bool> keys);
    
    virtual StateName GetState();

protected:
};

