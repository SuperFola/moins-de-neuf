#ifndef GAME_STRAT_HPP
#define GAME_STRAT_HPP

#include <Pile.hpp>
#include <Fold.hpp>

#include <utility>  // std::pair
#include <string>

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
     * @brief Called when it's the strategy's turn and it has to discard a fold
     * 
     * @return std::pair<Fold, DiscardPile*> the fold it's discard, and where
     */
    virtual std::pair<Fold, DiscardPile*> discard() = 0;

    /**
     * @brief Called when it's the strategy's turn and it has to draw a card
     * 
     * @return std::pair<Card, Pile*> the card it's drawing, and it's origin
     */
    virtual std::pair<Card, Pile*> draw() = 0;

    /**
     * @brief Called when it's the strategy's turn and it can announce
     * @details Will be called before discarding and drawing, if it's true then
     *          the strategy won't play.
     * 
     * @return true The strategy wants to announce "moins de neuf"
     * @return false The strategy don't want to announce
     */
    virtual bool announce() = 0;

protected:
    const std::string m_name;  ///< The strategy's name to be displayed when playing
};

#endif  // GAME_STRAT_HPP