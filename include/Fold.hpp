#ifndef GAME_FOLD_HPP
#define GAME_FOLD_HPP

#include <Card.hpp>

#include <variant>
#include <ostream>

class Fold
{
public:
    /**
     * @brief Construct a new Fold object
     * 
     */
    Fold();

    /**
     * @brief Construct a new Fold object
     * 
     * @param card 
     */
    Fold(const Card& card);

    /**
     * @brief Construct a new Fold object
     * 
     * @param combination 
     */
    Fold(const Combination& combination);

    /**
     * @brief Checks if it's holding a single card or a combination
     * 
     * @return true 
     * @return false 
     */
    bool isCard() const noexcept;

    /**
     * @brief Get the Card object
     * 
     * @return const Card& 
     */
    const Card& getCard() const;

    /**
     * @brief Get the Combination object
     * 
     * @return const Combination& 
     */
    const Combination& getCombination() const;

    /**
     * @brief Get the Points of the fold
     * 
     * @return int 
     */
    int getPoints() const;

    friend std::ostream& operator<<(std::ostream& os, const Fold& fold);

private:
    std::variant<Card, Combination> m_content;  ///< A fold is either a single card or a combination of cards
};

#endif  // GAME_FOLD_HPP