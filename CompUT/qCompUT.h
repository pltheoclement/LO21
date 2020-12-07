#ifndef QCOMPUT_H
#define QCOMPUT_H
#include <QWidget>
#include <QApplication>
#include <QLineEdit>
#include <QTextEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QDebug>
#include <QString>
#include <vector>
#include <QMap>
#include "CompUT.h"

using namespace std;


class QCompUT : public QWidget{
    Q_OBJECT

    QLineEdit* message;
    QTableWidget* viewStack;
    QLineEdit* commande;
    QString text;

    map<string,QPushButton*> buttons_First_keyboard;
    map<string,QPushButton*> buttons_Second_keyboard;
    map<string,QVBoxLayout*> layout_Vertical;
    map<string,QHBoxLayout*> layout_Horizontal;
    map<string,QWidget*> secondary_view;
//    vector<QPushButton*> buttons_First_keyboard;
//    vector<QPushButton*> buttons_Second_keyboard;
//    vector<QVBoxLayout*> layoutV;
//    vector<QHBoxLayout*> layoutH;
    //vector<QWidget*> secondary_view;

    QTabWidget *tab;

    Stack* stack;
    Controleur* controleur;


public:
    explicit QCompUT(QWidget *father = 0);
    void affichage_Variable();
    //void Initialisation();


public slots:
    void refresh();
    void getNextCommande();
    void slot1();void slot2();void slot3();void slot4();void slot5();void slot6();void slot7();void slot8();void slot9();void slot0();
    void slotPlus();void slotMoins();void slotMult();void slotDiv();void slotEqual();
    void slotOpen1();
    void slotOpen2();

};


#endif // QCOMPUT_H
