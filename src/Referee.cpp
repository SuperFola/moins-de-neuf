#include <Referee.hpp>
#include <Card.hpp>

#include <algorithm>  // std::shuffle
#include <random>  // std::random_device, std::mt19937

using namespace std::string_literals;

Referee::Referee()
{}

void Referee::run_for(unsigned game_count)
{
    const std::vector<Card> deck = Card::generate_deck();
    const std::size_t player_count = m_strategies.size();

    std::random_device rd;
    std::mt19937 g(rd());

    // 0 because we don't have any last loser, the first player starts
    std::size_t last_loser = 0;

    for (unsigned game = 0; game < game_count; ++game)
    {
        // create a new deck
        std::vector<Card> new_deck(deck);
        std::shuffle(new_deck.begin(), new_deck.end(), g);

        // generate players' hands
        m_hands.clear();
        for (std::size_t i = 0; i < player_count; ++i)
        {
            for (std::size_t j = 0; j < 7; ++j)
            {
                m_hands.emplace_back(new_deck.back());
                new_deck.pop_back();
            }
        }

        // we can ensure that we have at least 3 cards left in the deck
        // because the number of players is blocked at 7 (included)
        // thus we give away 7*7 = 49 cards
        m_discard1 = DiscardPile(new_deck.back());
        new_deck.pop_back();
        m_discard2 = DiscardPile(new_deck.back());
        new_deck.pop_back();
        m_deck = Pile(new_deck);

        // first turn, the last loser starts
        auto p = play_round(last_loser);
        if (p.has_value())
            play_round(p.value(), /* skip */ p.value());

        // play until we have an announcer
        while (!p.has_value())
        {
            p = play_round();
            if (p.has_value())
            {
                play_round(p.value(), /* skip */ p.value());
                break;
            }
        }

        // count points
        std::vector<int> temp_points(m_hands.size());
        int mini = 9999, maxi = 0;

        for (std::size_t i = 0; i < m_hands.size(); ++i)
        {
            temp_points[i] = 0;
            for (const Card& c : m_hands[i])
                temp_points[i] += c.getPoints();

            if (temp_points[i] < mini)
                mini = temp_points[i];
            if (temp_points[i] > maxi)
                maxi = temp_points[i];
        }

        // give 1 to everyone else who has more than mini
        // and avoid giving 1 to the announcer if it losts
        for (std::size_t i = 0; i < m_hands.size(); ++i)
        {
            // if announcer won
            if (i == p.value() && temp_points[p.value()] == mini)
                m_points[p.value()] += 2;
            else if (temp_points[i] != mini && temp_points[i] != maxi)
                m_points[i] += 1;
            else if (temp_points[i] == mini)
                m_points[i] += 2;

            // attribute loser position
            if (temp_points[i] == maxi)
                last_loser = i;
        }
    }

    for (std::size_t i = 0; i < player_count; ++i)
        std::cout << "Strategy " << m_strategies[i]->getName() << " has " << m_points[i] << " points" << std::endl;
}

#define ANTI_CHEAT_DECK(player, code)          \
    {                                          \
        std::size_t deck_size = m_deck.size(); \
        code;                                  \
        if (m_deck.size() != deck_size)        \
            throw std::runtime_error(          \
                "The strategy "s + player->getName() + " cheated by using the deck while it wasn't allowed to"s);                 \
    }

#define ANTI_CHEAT_USE_DISCARDS(player, code)  \
    {                                          \
        std::size_t d1 = m_discard1.size();    \
        std::size_t d2 = m_discard2.size();    \
        code;                                  \
        if (m_discard1.size() != d1 || m_discard2.size() != d2) \
            throw std::runtime_error(          \
                "The strategy "s + player->getName() + " cheated by using the discard piles while it wasn't allowed to"s);       \
    }

std::optional<std::size_t> Referee::play_round(std::size_t from, std::size_t skip)
{
    const std::size_t player_count = m_strategies.size();
    std::size_t announcer = 1337;

    for (std::size_t i = from; i < player_count; ++i)
    {
        const std::size_t player_pos = i % player_count;
        if (player_pos == skip)
            continue;

        Strategy* player = m_strategies[player_pos];

        auto do_discard = [&, this](){
            std::pair<Fold, DiscardPile*> discarded = player->discard(m_hands[player_pos], &m_deck, &m_discard1, &m_discard2);
            Fold f = discarded.first;

            if (f.isCard())
            {
                auto end = std::remove(m_hands[player_pos].begin(), m_hands[player_pos].end(), f.getCard());
                if (end != m_hands[player_pos].end())
                    throw std::runtime_error("The player "s + player->getName() + " tried to discard a card it didn't own");
            }
            else
            {
                std::vector<Card> cards = f.getCombination().getCards();
                for (const Card& c : cards)
                {
                    auto end = std::remove(m_hands[player_pos].begin(), m_hands[player_pos].end(), c);
                    if (end != m_hands[player_pos].end())
                        throw std::runtime_error("The player "s + player->getName() + " tried to discard a card it didn't own");
                }
            }

            discarded.second->put(f);
        };

        auto do_draw = [&, this](){
            std::pair<Card, Pile*> drawn = player->draw(m_hands[player_pos], &m_deck, &m_discard1, &m_discard2);
            Card c = drawn.first;

            std::optional<Fold> top = drawn.second->consultTop();
            if (!top || !top.value().has(c))
                throw std::runtime_error("The player "s + player->getName() + " tried to take a card from a pile where it wasn't available"s);

            std::optional<Card> opt_c = draw.second->take(card);
            if (!opt_c)
                throw std::runtime_error("The player "s + player->getName() + " tried to take a card from an empty pile");

            m_hands[player_pos].push_back(opt_c.value());
        };

        auto do_announce = [&, this](){
            std::size_t hand_points = 0;
            for (const Card& c : m_hands[player_pos])
                hand_points += c.getPoints();

            if (hand_points >= 9)
                throw std::runtime_error("The player "s + player->getName() + " tried to announce but it had more than 9 points");
            announcer = player_pos;
        };

        ANTI_CHEAT_DECK(player, do_discard())
        ANTI_CHEAT_USE_DISCARDS(player, do_draw())
        ANTI_CHEAT_DECK(player, ANTI_CHEAT_USE_DISCARDS(player, do_announce()))

        if (announcer < player_count)
            return announcer;
    }

    return {};
}