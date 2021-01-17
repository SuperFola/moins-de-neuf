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

std::ostream& operator<<(std::ostream& os, const Fold& fold)
{
    if (fold.isCard())
        os << fold.getCard();
    else
        os << fold.getCombination();

    return os;
}