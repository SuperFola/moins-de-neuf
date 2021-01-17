#ifndef GAME_REFEREE_HPP
#define GAME_REFEREE_HPP

#include <Pile.hpp>
#include <Strategy.hpp>

#include <vector>
#include <memory>  // std::unique_ptr, std::make_unique
#include <string>
#include <utility>  // std::forward
#include <stdexcept>  // std::runtime_error

class Referee
{
public:
    /**
     * @brief Construct a new Referee object, in charge of launching the strategies and checking for cheaters
     * 
     */
    Referee();

    /**
     * @brief Add and create a new strategy in place
     * 
     * @tparam StrategyType 
     * @tparam Args 
     * @param strategy_name 
     * @param args 
     */
    template <typename StrategyType, typename... Args>
    void addPlayer(const std::string& strategy_name, Args&&... args)
    {
        if (m_strategies.size() >= 7)
            throw std::runtime_error("Can not play with more than 7 players");

        m_strategies.emplace_back(
            std::make_unique<StrategyType>(strategy_name, std::forward<Args>(args)...);
        );
        m_points.emplace_back(0);
    }

    /**
     * @brief Run the strategies for a given number of games
     * 
     * @param game_count 
     */
    void run_for(unsigned game_count);

private:
    /**
     * @brief Play a single round, from a starting position
     * 
     * @param from The player to starts playing from
     * @param skip The player to skip (because they announced)
     * @return std::optional<std::size_t> The position of the player who announced
     */
    std::optional<std::size_t> play_round(std::size_t from=0, std::size_t skip=1337);

    Pile m_deck;  ///< The main drawing deck
    DiscardPile m_discard1;  ///< The first discard pile
    DiscardPile m_discard2;  ///< The second discard pile

    std::vector<std::unique_ptr<Strategy>> m_strategies;  ///< A polymorphic collection of strategies
    std::vector<unsigned> m_points;  ///< A 1-to-1 mapping for the points per strategy
    std::vector<Hand_t> m_hands;
};

#endif  // GAME_REFEREE_HPP