#include <Pile.hpp>

#include <stdexcept>  // std::runtime_error

Pile::Pile()
{}

Pile::Pile(std::initializer_list<Fold> cards) :
    m_cards(cards)
{}

bool Pile::empty() const noexcept
{
    return m_cards.empty();
}

std::optional<Fold> Pile::consultTop() const noexcept
{
    if (m_cards.size() == 0)
        return {};
    return m_cards[m_cards.size() - 1];
}

virtual std::optional<Card> Pile::take()
{
    /*
        This method is only in Pile, not DiscardPile.
        Thus we can assume that every fold only holds a
        single card.
    */
    if (empty())
        return {};

    Fold f = m_cards[m_cards.size() - 1];
    m_cards.pop_back();
    return f.getCard();
}

virtual std::optional<Card> Pile::take(const Card& from_fold)
{
    throw std::runtime_error("This function doesn't work for pile (take(card))");
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

virtual std::optional<Card> Pile::take()
{
    throw std::runtime_error("This function doesn't work for discard pile (take())");
}

virtual std::optional<Card> Pile::take(const Card& from_fold)
{
    if (empty())
        return {};

    Fold& f = m_cards[m_cards.size() - 1];

    // check that the wanted card is in the fold
    if (!f.has(from_fold))
        return {};
    f.remove(from_fold);
    // check if we should remove the fold (if empty)
    if (f.empty())
        m_cards.pop_back();

    return from_fold;

std::ostream& operator<<(std::ostream& os, const DiscardPile& pile)
{
    os << "DiscardPile (" << pile.m_cards.size() << ")\n";
    for (auto it = pile.m_cards.rbegin(); it != pile.m_cards.rend(); ++it)
        os << " - " << (*it) << "\n";

    return os;
}