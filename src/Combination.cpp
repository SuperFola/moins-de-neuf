#include <Combination.hpp>

#include <algorithm>  // std::transform, std::sort, std::remove
#include <iterator>  // std::back_inserter

static std::optional<Combination> Combination::make_from_cards(std::initializer_list<Card> cards)
{
    // a combination has at least 2 cards
    if (cards.size() < 2)
        return {};

    std::vector<Card> temp(cards);
    Combination::Type guess = Combination::Type::Invalid;

    switch (temp.size())
    {
        case 2:
            // check for pairs
            if (temp[0].hasSameSuit(temp[1]))
                guess = Combination::Type::Pair;
            break;

        case 3:
            // check for three of a kind
            if (temp[0].hasSameValue(temp[1]) && temp[1].hasSameValue(temp[2]))
                guess = Combination::Type::ThreeOfAKind;
            // check for straight flush
            else if (temp[0].hasSameSuit(temp[1]) && temp[1].hasSameSuit(temp[2]) &&
                    Combination::isStraight(cards))
                guess = Combination::Type::StraightFlush;
            break;

        case 4:
            // check for four of a kind
            if (temp[0].hasSameValue(temp[1]) && temp[1].hasSameValue(temp[2]) &&
                temp[2].hasSameValue(temp[3]))
                guess = Combination::Type::FourOfAKind;
            // check for straight flush
            else if (temp[0].hasSameSuit(temp[1]) && temp[1].hasSameSuit(temp[2]) &&
                    temp[2].hasSameSuit(temp[3]) && Combination::isStraight(cards))
                guess = Combination::Type::StraightFlush;
            break;

        // more than 4 cards
        default:
        {
            bool same_suit = true;
            Card::Suit last_suit = temp[0].getSuit();
            for (std::size_t i = 1; i < temp.size(); ++i)
            {
                if (temp[i].getSuit() != last_suit)
                {
                    same_suit = false;
                    break;
                }
            }

            if (same_suit && Combination::isStraight(cards))
                guess = Combination::Type::StraightFlush;
        }
    }

    if (type != Combination::Type::Invalid)
        return Combination(type, cards);
    return {};
}

static bool Combination::isStraight(std::initializer_list<Card> cards)
{
    if (cards.size() < 2)
        return false;

    std::vector<int> points;
    std::transform(cards.begin(), cards.end(), std::back_inserter(points),
                    [](const Card& c) -> int { return c.getPoints(); });
    std::sort(points.begin(), points.end());

    int i = points[0];
    for (std::size_t j = 1; j < points.size(); ++j)
    {
        if (points[j] == i + 1)
            ++i;
        else
            return false;
    }

    return true;
}

Combination::Type Combination::getType() const noexcept
{
    return m_type;
}

int Combination::getPoints() const noexcept
{
    int total = 0;
    for (const Card& c : m_cards)
        total += c.getPoints();

    return total;
}

Combination::Combination(Combination::Type type, std::initializer_list<Card> cards) noexcept :
    m_cards(cards), m_type(type)
{}

bool Combination::has(const Card& c) const noexcept
{
    if (m_cards.size() == 0)
        return false;

    for (const Card& card : m_cards)
    {
        if (card == c)
            return true;
    }

    return false;
}

bool Combination::try_remove(const Card& c) noexcept
{
    if (!has(c))
        return false;

    std::remove(m_cards.begin(), m_cards.end(), c);
    // no need to check for the return value, because with has() we know
    // that the value was in the combination
    return true;
}

std::ostream& operator<<(std::ostream& os, const Combination& comb)
{
    switch (comb.getType())
    {
        case Combination::Type::StraightFlush:
            os << "Straight Flush";
            break;

        case Combination::Type::FourOfAKind:
            os << "Four of a kind (" << comb.m_cards[0] << ")";
            break;

        case Combination::Type::ThreeOfAKind:
            os << "Three of a kind (" << comb.m_cards[0] << ")";
            break;

        case Combination::Type::Pair:
            os << "Pair (" << comb.m_cards[0] << ", " << comb.m_cards[1] << ")";
            break;

        case Combination::Type::Invalid:
            // this can not happen because the constructor is private
            // and a combination can only be constructed by using
            // Combination::make_from_cards({cards...})
            os << "Invalid combination";
            break;
    }

    return os;
}