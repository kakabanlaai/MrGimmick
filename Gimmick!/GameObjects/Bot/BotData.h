#pragma once
//pre define
class BotState;
class Bot;

class BotData
{
public:
    BotData();
    ~BotData();

    Bot      *bot;
    BotState *state;

protected:
    
};

