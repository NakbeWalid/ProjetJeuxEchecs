#pragma once
#include <vector>
#include <string>
#include <utility> // pour std::pair

using std::vector;
using std::string;
using std::pair;

class Piece {
public:
    enum class Couleur { Blanc, Noir };

    Piece(Couleur couleur, int x, int y);
    virtual ~Piece() = default;

    Couleur getCouleur() const;
    pair<int, int> getPosition() const;
    void setPosition(int x, int y);
    virtual char getSymbole() const = 0;

    virtual vector<pair<int, int>> deplacementsPossibles() const = 0;

    bool mouvementValide(int x, int y) const;

protected:
    Couleur couleur;
    int x;
    int y;
};
