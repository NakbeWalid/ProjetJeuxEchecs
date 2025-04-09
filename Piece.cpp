#include "Piece.hpp"

using std::pair;
using std::vector;

Piece::Piece(Couleur couleur, int x, int y)
    : couleur(couleur), x(x), y(y) {
}

Piece::Couleur Piece::getCouleur() const {
    return couleur;
}

pair<int, int> Piece::getPosition() const {
    return { x, y };
}

void Piece::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

bool Piece::mouvementValide(int destX, int destY) const {
    auto mouvements = deplacementsPossibles();
    for (const auto& m : mouvements) {
        if (m.first == destX && m.second == destY)
            return true;
    }
    return false;
}
