#ifndef GAME_CARD_HPP
#define GAME_CARD_HPP

#include <ostream>
#include <vector>

/**
 * @brief Defines a card in the game
 * 
 */
class Card
{
public:
    /**
     * @brief The different suits for the cards
     * 
     */
    enum class Suit
    {
        Tiles,    // ♦
        Clovers,  // ♣
        Hearts,   // ♥
        Pikes     // ♠
    };

    /**
     * @brief The existing values for each card
     * 
     */
    enum class Value
    {
        Ace = 1,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten,
        Jack,
        Queen,
        King
    };

    static std::vector<Card> generate_deck()
    {
        std::vector<Card> deck(52);
        for (std::size_t i = 0; i < 52; ++i)
        {
            deck[i] = Card(
                static_cast<Suit>((i / 13) % 4),
                // + 1 because Ace is = 1
                static_cast<Value>(1 + (i % 13))
            );
        }

        return deck;
    }

    /**
     * @brief Construct a new Card object
     * 
     */
    Card();

    /**
     * @brief Construct a new Card object
     * 
     * @param suit 
     * @param value 
     */
    Card(Suit suit, Value value);

    /**
     * @brief Get the Suit object
     * 
     * @return const Suit 
     */
    const Suit getSuit() const noexcept;

    /**
     * @brief Get the Value object
     * 
     * @return const Value 
     */
    const Value getValue() const noexcept;

    /**
     * @brief Calculate the number of points a given card is worth of
     * 
     * @return int 
     */
    int getPoints() const noexcept;

    /**
     * @brief Check if this card has the same suit as the other
     * 
     * @param card 
     * @return true 
     * @return false 
     */
    bool hasSameSuit(const Card& card) const noexcept;

    /**
     * @brief Check if this card has the value as the other
     * 
     * @param card 
     * @return true 
     * @return false 
     */
    bool hasSameValue(const Card& card) const noexcept;

    /**
     * @brief Checks if two cards are the same
     * 
     * @param card 
     * @return true 
     * @return false 
     */
    bool operator==(const Card& card) const noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Card& card);

private:
    Suit m_suit;
    Value m_value;
};

using Hand_t = std::vector<Card>;

#endif  // GAME_CARD_HPP