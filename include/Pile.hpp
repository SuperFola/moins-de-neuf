#ifndef GAME_PILE_HPP
#define GAME_PILE_HPP

#include <Fold.hpp>

#include <vector>
#include <initializer_list>
#include <ostream>
#include <optional>

/**
 * @brief A drawing deck.
 * @details Strategies will draw from the end of the deck.
 * 
 */
class Pile
{
public:
    /**
     * @brief Construct a new Pile object
     * 
     */
    Pile();

    /**
     * @brief Construct a new drawing deck from a collection of cards
     * 
     * @param cards the cards to have on the drawing deck
     */
    Pile(std::initializer_list<Fold> cards);

    /**
     * @brief Checks if the pile is empty
     * 
     * @return true If the pile is empty
     * @return false 
     */
    bool empty() const noexcept;

    /**
     * @brief Get the last fold put on the pile
     * @details Returned as an optional because the pile can be empty.
     * 
     * @return std::optional<Fold> 
     */
    std::optional<Fold> consultTop() const noexcept;

    /**
     * @brief Take the last card from the pile
     * @details Only works for pile, not discard pile. Returns an optional
     *          because the pile can be empty.
     * 
     * @return std::optional<Card> 
     */
    virtual std::optional<Card> take();

    /**
     * @brief Unimplemented (throws an exception) for the pile.
     * 
     * @param from_fold 
     * @return std::optional<Card> 
     */
    virtual std::optional<Card> take(const Card& from_fold);

    friend std::ostream& operator<<(std::ostream& os, const Pile& pile);

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
     */
    DiscardPile();

    /**
     * @brief Construct a new Discard Pile object
     * 
     * @param visible_card the first visible card on the pile
     */
    DiscardPile(Fold visible_card);

    /**
     * @brief Unimplemented (throws an exception) for the discard pile.
     * 
     * @return std::optional<Card> 
     */
    virtual std::optional<Card> take();

    /**
     * @brief Unimplemented (throws an exception) for the pile.
     * 
     * @param from_fold 
     * @return std::optional<Card> 
     */
    virtual std::optional<Card> take(const Card& from_fold);

    friend std::ostream& operator<<(std::ostream& os, const DiscardPile& pile);
};

#endif  // GAME_PILE_HPP