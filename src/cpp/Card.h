#pragma once

#include <list>
/**
 * Vitrual class representation of every card in the game.
*/
class Card
{
	/**
	 * A variable to contain image of card.
	 */
	char* image;
	/**
	 * In this list there will be cards that can block this exacly card. Here we must check types of pointers.
	 */
	std::list<Card*> Blockers;


private:
	/**
	 * Action that can card perform.
	 * @return 0 if action happened and non 0 if action didnt happen.
	 */
	int action(void) = 0;


}