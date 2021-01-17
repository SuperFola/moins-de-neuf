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

    /**
     * @brief Checks if the fold contains a given card
     * 
     * @param c 
     * @return true 
     * @return false 
     */
    bool has(const Card& c) const noexcept;

    /**
     * @brief Remove a given card from the fold if it's in
     * 
     * @param c 
     * @return true If it was successfully removed
     * @return false 
     */
    bool try_remove(const Card& c);

    /**
     * @brief Checks if the fold is empty.
     * 
     * @return true 
     * @return false 
     */
    bool empty() const noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Fold& fold);

private:
    std::variant<Card, Combination> m_content;  ///< A fold is either a single card or a combination of cards
    bool m_empty = false;  ///< Set to true when we remove all the cards in it
};

#endif  // GAME_FOLD_HPP