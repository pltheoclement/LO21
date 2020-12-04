#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QFont>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "qCompUT.h"



int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QCompUT fenetre;
    fenetre.show();

    return app.exec();
}
