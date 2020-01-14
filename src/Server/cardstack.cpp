#include "cardstack.h"
#include <algorithm>
#include <random>
#include <card.h>
#include "player.h"
CardStack::CardStack()
{
    for(int i = 0; i < 3; ++i)
    {
        _stack.push_back(std::shared_ptr<Card>(new Card(QStringLiteral("russia")) ));
    }

    for(int i = 0; i < 3; ++i)
    {
        _stack.push_back(std::shared_ptr<Card>(new Card(QStringLiteral("protest")) ));
    }

    for(int i = 0; i < 3; ++i)
    {
        _stack.push_back(std::shared_ptr<Card>(new Card(QStringLiteral("media")) ));
    }

    for(int i = 0; i < 3; ++i)
    {
        _stack.push_back(std::shared_ptr<Card>(new Card(QStringLiteral("onz")) ));
    }

    for(int i = 0; i < 3; ++i)
    {
        _stack.push_back(std::shared_ptr<Card>(new Card(QStringLiteral("police")) ));
    }

    for(int i = 0; i < 3; ++i)
    {
        _stack.push_back(std::shared_ptr<Card>(new Card(QStringLiteral("eu")) ));
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
