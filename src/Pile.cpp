#include <Pile.hpp>

#include <stdexcept>  // std::runtime_error

Pile::Pile()
{}

Pile::Pile(const std::vector<Fold>& cards) :
    m_cards(cards)
{}

Pile::Pile(std::initializer_list<Fold> cards) :
    m_cards(cards)
{}

bool Pile::empty() const noexcept
{
    return m_cards.empty();
}

std::size_t Pile::size() const noexcept
{
    return m_cards.size();
}

void Pile::put(const Fold& f)
{
    m_cards.push_back(f);
}

std::optional<Fold> Pile::consultTop() const noexcept
{
    if (m_cards.size() == 0)
        return {};
    return m_cards.back();
}

std::optional<Card> Pile::take(const Card&)
{
    /*
        This method is in Pile, not DiscardPile.
        Thus we can assume that every fold only holds a
        single card.
        Argument is ignored.
    */
    if (empty())
        return {};

    Fold f = m_cards.back();
    m_cards.pop_back();
    return f.getCard();
}

std::ostream& operator<<(std::ostream& os, const Pile& pile)
{
    os << "Pile (" << pile.m_cards.size() << ")\n";
    for (auto it = pile.m_cards.rbegin(); it != pile.m_cards.rend(); ++it)
        os << " - " << (*it) << "\n";

    return os;
}

DiscardPile::DiscardPile()
{}

DiscardPile::DiscardPile(Fold visible_card) :
    Pile({ visible_card })
{}

std::size_t DiscardPile::size() const noexcept
{
    std::size_t s = 0;
    for (const Fold& f : m_cards)
    {
        if (f.isCard())
            ++s;
        else
            s += f.getCombination().size();
    }

    return s;
}

std::optional<Card> DiscardPile::take(const Card& from_fold)
{
    if (empty())
        return {};

    Fold& f = m_cards.back();

    // check that the wanted card is in the fold
    if (!f.try_remove(from_fold))
        return {};
    // check if we should remove the fold (if empty)
    if (f.empty())
        m_cards.pop_back();

    return from_fold;
}

std::ostream& operator<<(std::ostream& os, const DiscardPile& pile)
{
    os << "DiscardPile (" << pile.m_cards.size() << ")\n";
    for (auto it = pile.m_cards.rbegin(); it != pile.m_cards.rend(); ++it)
        os << " - " << (*it) << "\n";

    return os;
}