#include "logicalboard.hpp"
#include "king.hpp"
#include "tower.hpp"
#include "knight.hpp"

namespace chess {
   

    void LogicalBoard::initializeBoard() {
        plateau_.resize(8);
        for (int i = 0; i < 8; ++i) {
            plateau_[i].resize(8);
        }
    }

    LogicalBoard::LogicalBoard() {
        initializeBoard();  
    }
    Case& LogicalBoard::getCase(const Position& position) {
        return *plateau_[position.getX()][position.getY()];
    }

    void LogicalBoard::setCase(const Position& position, std::unique_ptr<Piece> piece) {
        getCase(position).setPiece(std::move(piece));
    }

    bool LogicalBoard::isEmptyCase(const Position& position) {
        return getCase(position).getPieceInfo() == nullptr;
    }

    Color LogicalBoard::getInverseColor(const Color& color) {
        return (color == Color::White) ? Color::Black : Color::White;
    }

    Position LogicalBoard::kingPosition(const Color& color) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Position pos(i, j);
                if ((getCase(pos).getPieceInfo() != nullptr) && (getCase(pos).getPieceInfo()->getColor() == color)
                    && (getCase(pos).getPieceInfo()->getTypePiece() == TypePiece::King)) {
                    return pos;
                }
            }
        }
        return {};
    }

    bool LogicalBoard::isCheck(const Color& color) {
        std::unordered_set<Position, PositionHash> positions = getAllMovements(getInverseColor(color));
        return positions.find(kingPosition(color)) != positions.end();
    }

    bool LogicalBoard::isCheckMate() {
        std::unordered_set<Position, PositionHash> positions = getAllMovements(joueur_);
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Position pos(i, j);
                if ((getCase(pos).getPieceInfo() != nullptr) && (getCase(pos).getPieceInfo()->getColor() == joueur_)) {
                    lastSelected_ = std::make_unique<Position>(pos);
                    if (!getFilteredMovement().empty()) {
                        lastSelected_ = nullptr;
                        return false;
                    }
                }
            }
        }
        lastSelected_ = nullptr;
        return true;
    }

    std::unordered_set<Position, PositionHash> LogicalBoard::getFilteredMovement() {
        std::unordered_set<Position, PositionHash> positions = getCase(*lastSelected_).getPieceInfo()->getMovementsList(*lastSelected_, *this);
        std::erase_if(positions, [&](const Position& pos) {
            std::unique_ptr<Piece> piece = getCase(pos).getPiece();
            moveTo(*lastSelected_, pos);
            if (isCheck(joueur_)) {
                moveTo(pos, *lastSelected_);
                getCase(pos).setPiece(std::move(piece));
                return true;
            }
            moveTo(pos, *lastSelected_);
            getCase(pos).setPiece(std::move(piece));
            return false;
            });
        return positions;
    }

    void LogicalBoard::moveTo(const Position& start, const Position& destination, bool) {
        getCase(destination).setPiece(getCase(start).getPiece());
        getCase(start).setPiece(nullptr);
    }

    void LogicalBoard::moveToValid(const Position& start, const Position& destination) {
        std::unordered_set<Position, PositionHash> positions = getFilteredMovement();
        auto it = positions.find(destination);
        if (it != positions.end()) {
            getCase(destination).setPiece(getCase(start).getPiece());
            getCase(start).setPiece(nullptr);
            joueur_ = getInverseColor(joueur_);
        }
    }

    bool LogicalBoard::isColor(Color color, const Position& position) {
        return getCase(position).getPieceInfo()->getColor() == color;
    }

    std::unordered_set<Position, PositionHash> LogicalBoard::getAllMovements(const Color& color) {
        std::unordered_set<Position, PositionHash> positions;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Position pos(i, j);
                if ((getCase(pos).getPieceInfo() != nullptr) && getCase(pos).getPieceInfo()->getColor() == color) {
                    auto tempPositions = getCase(pos).getPieceInfo()->getMovementsList(pos, *this);
                    positions.insert(tempPositions.begin(), tempPositions.end());
                }
            }
        }
        return positions;
    }

    void LogicalBoard::emptyBoard() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                plateau_[i][j]->setPiece(nullptr);
            }
        }
    }

    void LogicalBoard::setBoard(int modifier) {
        using std::make_unique;
        emptyBoard();
        ready_ = true;
        if (modifier == 0) {
            plateau_[0][4]->setPiece(make_unique<King>(Color::Black));
            plateau_[1][5]->setPiece(make_unique<Knight>(Color::Black));
            plateau_[1][2]->setPiece(make_unique<Knight>(Color::Black));
            plateau_[0][0]->setPiece(make_unique<Tower>(Color::Black));
            plateau_[0][7]->setPiece(make_unique<Tower>(Color::Black));

            plateau_[7][4]->setPiece(make_unique<King>(Color::White));
            plateau_[6][5]->setPiece(make_unique<Knight>(Color::White));
            plateau_[6][2]->setPiece(make_unique<Knight>(Color::White));
            plateau_[7][0]->setPiece(make_unique<Tower>(Color::White));
            plateau_[7][7]->setPiece(make_unique<Tower>(Color::White));
        }
        // Tu peux rajouter les autres configurations de board si besoin ici...
    }

    void LogicalBoard::endGame() {
        ready_ = false;
        checkMate_ = true;
    }

    bool LogicalBoard::isValidClick(const Position& position) {
        if (checkMate_) return false;
        if (lastSelected_ == nullptr) {
            if (getCase(position).getPieceInfo() && getCase(position).getPieceInfo()->getColor() == joueur_) {
                lastSelected_ = std::make_unique<Position>(position);
                gameInProgress_ = true;
            }
            return false;
        }
        else if (*lastSelected_ == position) {
            lastSelected_ = nullptr;
            return false;
        }
        else if (getCase(position).getPieceInfo() && getCase(position).getPieceInfo()->getColor() == getCase(*lastSelected_).getPieceInfo()->getColor()) {
            lastSelected_ = std::make_unique<Position>(position);
            return false;
        }
        return true;
    }
}
