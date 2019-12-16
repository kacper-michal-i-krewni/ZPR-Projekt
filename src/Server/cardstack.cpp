#include "cardstack.h"
#include <algorithm>
#include <random>
#include <../../Mutual/actions/allactions.h>
#include <../../Mutual/card.h>
#include "player.h"
CardStack::CardStack()
{
    for(int i = 0; i < 3; ++i)
    {
        _stack.push_back(std::shared_ptr<Card>(new Card(std::shared_ptr<Action>(new Russia()) )));
    }

    for(int i = 0; i < 3; ++i)
    {
        _stack.push_back(std::shared_ptr<Card>(new Card(std::shared_ptr<Action>(new Protest()) )));
    }

    for(int i = 0; i < 3; ++i)
    {
        _stack.push_back(std::shared_ptr<Card>(new Card(std::shared_ptr<Action>(new Media()) )));
    }

    for(int i = 0; i < 3; ++i)
    {
        _stack.push_back(std::shared_ptr<Card>(new Card(std::shared_ptr<Action>(new ONZ()) )));
    }

    for(int i = 0; i < 3; ++i)
    {
        _stack.push_back(std::shared_ptr<Card>(new Card(std::shared_ptr<Action>(new Police()) )));
    }

    for(int i = 0; i < 3; ++i)
    {
        _stack.push_back(std::shared_ptr<Card>(new Card(std::shared_ptr<Action>(new EU()) )));
    }
    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(_stack.begin(), _stack.end(), rng);
}


std::shared_ptr<Card> CardStack::takeCard()
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(_stack.begin(), _stack.end(), rng);
    return _stack.takeFirst();
}
void CardStack::putCard(std::shared_ptr<Card> card)
{
    _stack.push_back(card);
}

void CardStack::dealCards(std::shared_ptr<Player> player)
{
    player->takeCard(CardStack::takeCard());
    player->takeCard(CardStack::takeCard());
}
