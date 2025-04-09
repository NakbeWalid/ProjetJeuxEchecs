#include "ProjetJeuxEchecs.h"
#include <QPushButton>
#include <QGridLayout>
#include "Echiquier.hpp"

ProjetJeuxEchecs::ProjetJeuxEchecs(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::ProjetJeuxEchecsClass())
{
    ui->setupUi(this);
    setupPanel();

    echiquier = new Echiquier(this);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(echiquier);
    ui->centralWidget->setLayout(layout);
}

ProjetJeuxEchecs::~ProjetJeuxEchecs()
{
    delete ui;
}

void ProjetJeuxEchecs::setupPanel() {
    setFixedSize(800, 600);
}