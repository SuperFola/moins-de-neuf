#ifndef GAME_PILE_HPP
#define GAME_PILE_HPP

#include <Fold.hpp>

#include <vector>
#include <initializer_list>

/**
 * @brief A drawing deck.
 * @details Strategies will draw from the end of the deck.
 * 
 */
class Pile
{
public:
    /**
     * @brief Construct a new drawing deck from a collection of cards
     * 
     * @param cards the cards to have on the drawing deck
     */
    Pile(std::initializer_list<Fold> cards);

protected:
    std::vector<Fold> m_cards;  ///< Represented as a pile of fold of 1 card each
};

/**
 * @brief A discard pile.
 * @details Strategies will draw/put cards/folds from the end of the pile.
 * 
 */
class DiscardPile : public Pile
{
public:
    /**
     * @brief Construct a new Discard Pile object
     * 
     * @param visible_card the first visible card on the pile
     */
    DiscardPile(Fold visible_card);
};

#endif  // GAME_PILE_HPP