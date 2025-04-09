#include "Echiquier.hpp"
#include <vector>
using std::vector;



Echiquier::Echiquier(QWidget* parent) {
    setupEchiquier();
}

void Echiquier::setupEchiquier() {
    setFixedSize(400, 400);
    QGridLayout* layout = new QGridLayout;

    for (int lig = 0; lig < 8; lig++) {
        vector <QPushButton*> ligne;

        for (int col = 0; col < 8; ++col) {
            QPushButton* bouton = new QPushButton(this);

            if ((lig + col) % 2 == 0) {
                bouton->setStyleSheet("background-color: white; border: none;");
            }
            else {
                bouton->setStyleSheet("background-color: black; border: none;");
            }

            bouton->setFixedSize(50, 50);
            layout->addWidget(bouton, lig, col);

            ligne.push_back(bouton);
        }
        matriceBoutons.push_back(ligne);
    }

    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    setLayout(layout);
}