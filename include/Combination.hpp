#ifndef GAME_COMBI_HPP
#define GAME_COMBI_HPP

#include <Card.hpp>

#include <initializer_list>
#include <vector>
#include <optional>
#include <ostream>

class Combination
{
public:
    enum class Type
    {
        StraightFlush,  ///< A "couleur" in French
        FourOfAKind,    ///< A "carré" in French
        ThreeOfAKind,   ///< A "brelan" in French
        Pair,           ///< A "pair" in French
        Invalid
    };

    /**
     * @brief Try to make a combination from a given set of cards
     * @details Will return an empty optional<Combination> if it's impossible.
     * 
     * @param cards 
     * @return std::optional<Combination> 
     */
    static std::optional<Combination> make_from_cards(std::initializer_list<Card> cards);

    /**
     * @brief Checks if a sequence of cards if a straight
     * 
     * @param cards 
     * @return true 
     * @return false 
     */
    static bool isStraight(std::initializer_list<Card> cards);

    /**
     * @brief Get the Type of the combination
     * 
     * @return Type 
     */
    Type getType() const noexcept;

    /**
     * @brief Get the Points accumulated by the combination
     * 
     * @return int 
     */
    int getPoints() const noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Combination& comb);

private:
    /**
     * @brief Construct a new Combination object
     * 
     * @param type 
     * @param cards 
     */
    Combination(Type type, std::initializer_list<Card> cards) noexcept;

    std::vector<Card> m_cards;
    Type m_type;  ///< The combination type
};

#endif  // GAME_COMBI_HPP