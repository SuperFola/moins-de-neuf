#ifndef GAME_REFEREE_HPP
#define GAME_REFEREE_HPP

#include <Pile.hpp>
#include <Strategy.hpp>

#include <vector>
#include <memory>  // std::unique_ptr, std::make_unique
#include <string>
#include <utility>  // std::forward

class Referee
{
public:
    Referee();

    template <typename StrategyType, typename... Args>
    void addPlayer(const std::string& strategy_name, Args&&... args)
    {
        m_strategies.emplace_back(
            std::make_unique<StrategyType>(strategy_name, std::forward<Args>(args)...);
        );
    }

private:
    Pile m_deck;  ///< The main drawing deck
    DiscardPile m_discard1;  ///< The first discard pile
    DiscardPile m_discard2;  ///< The second discard pile

    std::vector<std::unique_ptr<Strategy>> m_strategies;  ///< A polymorphic collection of strategies
};

#endif  // GAME_REFEREE_HPP