#include <Card.hpp>

Card::Card(Card::Suit suit, Card::Value value) :
    m_suit(suit), m_value(value)
{}

const Card::Suit Card::getSuit() const noexcept
{
    return m_suit;
}

const Card::Value Card::getValue() const noexcept
{
    return m_value;
}

int Card::getPoints() const noexcept
{
    return static_cast<int>(m_value);
}

bool Card::hasSameSuit(const Card& card) const noexcept
{
    return m_suit == card.m_suit;
}

bool Card::hasSameValue(const Card& card) const noexcept
{
    return m_value == card.m_value;
}

bool Card::operator==(const Card& card) const noexcept
{
    return m_value == card.m_value && m_suit == card.m_suit;
}

std::ostream& operator<<(std::ostream& os, const Card& card)
{
    int points = card.getPoints();
    switch (points)
    {
        case 1:
            os << "Ace";
            break;

        case 11:
            os << "Jack";
            break;

        case 12:
            os << "Queen";
            break;

        case 13:
            os << "King";
            break;

        default:
            os << points;
            break;
    }

    os << " of ";

    switch (card.getSuit())
    {
        case Card::Suit::Tiles:
            os << "tiles";
            break;

        case Card::Suit::Clovers:
            os << "clovers";
            break;

        case Card::Suit::Hearts:
            os << "hearts";
            break;

        case Card::Suit::Pikes:
            os << "pikes";
            break;
    }

    return os;
}