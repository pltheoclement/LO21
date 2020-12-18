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
#include <QLabel>
#include <QComboBox>
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
    map<string,QPushButton*> buttons_secondary_view;
    map<string,QVBoxLayout*> layout_Vertical;
    map<string,QHBoxLayout*> layout_Horizontal;
    map<string,QWidget*> secondary_view;
    map<string,QLineEdit*> Line_Edit;
    map<string,QLabel*> label;
    map<string,QComboBox*> list;

    QTabWidget *tab;

    Stack* stack;
    Controleur* controleur;


public:
    explicit QCompUT(QWidget *father = 0);
    void creation();
    void Initialisation();
    void Initialisation_Stack();


public slots:
    void refresh();
    void getNextCommande();
    void slot1();void slot2();void slot3();void slot4();void slot5();void slot6();void slot7();void slot8();void slot9();void slot0();
    void slotPlus();void slotMoins();void slotMult();void slotDiv();void slotEqual();
    void slotOpen1();
    void slotOpen2();
    void slotReduce1();
    void slotReduce2();

    void slotNewVariable(); void slotModifVariable(); void slotDeleteVariable();
    void slotNewProg(); void slotModifProg(); void slotDeleteProg();

};


#endif // QCOMPUT_H
