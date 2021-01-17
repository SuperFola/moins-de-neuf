#ifndef GAME_STRAT_HPP
#define GAME_STRAT_HPP

#include <Pile.hpp>
#include <Fold.hpp>
#include <Card.hpp>  // Hand_t

#include <utility>  // std::pair
#include <string>
#include <ostream>

class Strategy
{
public:
    /**
     * @brief Construct a new Strategy object
     * 
     * @param name the name of the strategy
     */
    Strategy(const std::string& name);

    /**
     * @brief Get the Name of the strategy
     * 
     * @return const std::string& 
     */
    const std::string& getName() const noexcept;

    /**
     * @brief Called when it's the strategy's turn and it has to discard a fold
     * 
     * @param hand the player hand
     * @param pile the pile
     * @param dp1 the first discard pile
     * @param dp2 the second discard pile
     * @return std::pair<Fold, DiscardPile*> the fold it's discard, and where
     */
    virtual std::pair<Fold, DiscardPile*> discard(const Hand_t& hand, Pile* pile, DiscardPile* dp1, DiscardPile* dp2) = 0;

    /**
     * @brief Called when it's the strategy's turn and it has to draw a card
     * 
     * @param hand the player hand
     * @param pile the pile
     * @param dp1 the first discard pile
     * @param dp2 the second discard pile
     * @return std::pair<Card, Pile*> the card it's drawing, and it's origin
     */
    virtual std::pair<Card, Pile*> draw(const Hand_t& hand, Pile* pile, DiscardPile* dp1, DiscardPile* dp2) = 0;

    /**
     * @brief Called when it's the strategy's turn and it can announce
     * @details Will be called before discarding and drawing, if it's true then
     *          the strategy won't play.
     * 
     * @param hand the player hand
     * @param pile the pile
     * @param dp1 the first discard pile
     * @param dp2 the second discard pile
     * @return true The strategy wants to announce "moins de neuf"
     * @return false The strategy don't want to announce
     */
    virtual bool announce(const Hand_t& hand, Pile* pile, DiscardPile* dp1, DiscardPile* dp2) = 0;

    friend std::ostream& operator<<(std::ostream& os, const Strategy& strat);

protected:
    const std::string m_name;  ///< The strategy's name to be displayed when playing
};

#endif  // GAME_STRAT_HPP