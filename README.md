# Moins de neuf

This is a simulation of a card game named "moins de neuf".

There are at most 7 players, and 52 cards in the game.

## Rules

Every player is given 7 cards from the deck, then 2 cards are put on 2 discard piles, and the rest creates the deck.

The loser from the last game starts, if none it's the first player to register. A player can discard a single card or a combination of cards from their hand (straight flush, four of a kind, three of a kind, pair) onto a chosen discard pile. Then they have to draw a card from the other discard pile or the deck.

*Nota bene*: When the deck is empty and there is only 1 discard pile left, the player **must** discard on the empty discard pile, and draw from the other.

Combinations are discarded on discard piles, and player can only draw a card from the last combination put on the discard pile before going further down the discard pile.

When a player has strictly less than 9 points with their carts in hand (Ace = 1, 2 = 2, ... King = 13) they can announce "moins de neuf" (less than 9). The game enters the final round: every player **except** for the announcer must play one last time, then we count the points of each players.

If the announcer has the smallest score, they earn 2 points, otherwise 0. All the players earn 1 point if they have more than the smallest score, the player(s) with the maximum score earn 0 points.

## How to use

The project is delivered as is, with:
* a base strategy to inherit from
* a basic referee checking for basic cheating (can be enhanced)

## How to improve

* there isn't anything listing all the combinations in the player hands
* there isn't any primitive strategy to start the game
* more anti cheats could and should be added (checking that the player didn't halter its hand, alter the piles itself...)