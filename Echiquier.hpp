#pragma once
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QList>
#include <vector>
#include <memory>
#include "Piece.hpp"

using std::vector;

class Echiquier : public QWidget {
    Q_OBJECT

public:
    Echiquier(QWidget* parent);
    vector<vector<QPushButton*>> matriceBoutons;
    vector<Piece*> pieces;

private:
    void setupEchiquier();

};
