#include <Fold.hpp>

Fold::Fold()
{}

Fold::Fold(const Card& card) :
    m_content(card)
{}

Fold::Fold(const Combination& combination) :
    m_content(combination)
{}

bool Fold::isCard() const noexcept
{
    return std::holds_alternative<Card>(m_content);
}

const Card& Fold::getCard() const
{
    return std::get<Card>(m_content);
}

const Combination& Fold::getCombination() const
{
    return std::get<Combination>(m_content);
}

int Fold::getPoints() const
{
    if (isCard())
        return getCard().getPoints();
    else
        return getCombination().getPoints();
}

bool Fold::has(const Card& c) const noexcept
{
    if (isCard())
        return c == getCard();
    else
        return getCombination().has(c);
}

bool Fold::try_remove(const Card& c)
{
    if (isCard() && c == getCard())
    {
        m_empty = true;
        return true;
    }
    else if (!isCard() && std::get<Combination>(m_content).try_remove(c))
    {
        m_empty = getCombination().empty();
        return true;
    }

    return false;
}

bool Fold::empty() const noexcept
{
    return m_empty;
}

std::ostream& operator<<(std::ostream& os, const Fold& fold)
{
    if (fold.isCard())
        os << fold.getCard();
    else
        os << fold.getCombination();

    return os;
}