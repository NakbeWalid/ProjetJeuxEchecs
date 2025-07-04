#pragma once
#include "knight.hpp"
#include "board.hpp"
#include <ranges>


namespace chess {
    Knight::Knight(Color couleur) : Piece(TypePiece::Knight,
        couleur, "nd.png", "nl.png") {
    }



    std::unordered_set<Position, PositionHash> Knight::getMovementsList(const Position& start, ui::Board& echiquier) const {
        std::unordered_set<Position, PositionHash> positions;
        positions.insert(Position(start.getX() + 2, start.getY() + 1));
        positions.insert(Position(start.getX() + 1, start.getY() + 2));
        positions.insert(Position(start.getX() + 2, start.getY() - 1));
        positions.insert(Position(start.getX() + 1, start.getY() - 2));

        positions.insert(Position(start.getX() - 2, start.getY() - 1));
        positions.insert(Position(start.getX() - 1, start.getY() - 2));
        positions.insert(Position(start.getX() - 2, start.getY() + 1));
        positions.insert(Position(start.getX() - 1, start.getY() + 2));
        erase_if(positions, [&echiquier, this](const Position& pos) {
            if (pos.estValide()) {
                if (!echiquier.isEmptyCase(pos)) {
                    return echiquier.isColor(Piece::getColor(), pos);
                }
                return false;
            }
            return true;

            });
        return positions;
    }
}
