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
#include <QMap>
#include <QVector>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QObject>
#include <QDebug>
#include <algorithm>

//#include "CompUT.h"
#include "include/computer.h"

using namespace std;


class QCompUT : public QWidget{
    Q_OBJECT

    QLineEdit* message;
    QTableWidget* viewStack;
    QLineEdit* commande;
    QString text;
    size_t Nbr_Line;

    //map<tuple<QString,QString>,QPushButton*> buttons_var;
    //pair<tuple<QString,QString>,QPushButton*> bt_var;
    //tuple<QString,QString>t;

    map<QString,QPushButton*> buttons_First_keyboard;
    map<QString,QPushButton*> buttons_Second_keyboard;
    map<QString,QPushButton*> buttons_secondary_view;
    map<QString,QPushButton*> buttons_var;
    map<QString,QPushButton*> buttons_prog;
    map<QString,QVBoxLayout*> layout_Vertical;
    map<QString,QHBoxLayout*> layout_Horizontal;
    map<QString,QWidget*> secondary_view;
    map<QString,QLineEdit*> Line_Edit;
    map<QString,QLabel*> label;
    map<QString,QComboBox*> list;
    map<QString,QTableWidget*> table;
    QVector<QTableWidgetItem *>listeItemsVar;
    QVector<QTableWidgetItem *>listeItemsProg;

    QTabWidget *tab;

    //Stack stack;
    //Computer computer;


    QSpinBox* Nbr_Line_Stack;


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

    void slotVariable();
    void slotProgram();

    void slot_Nbr_Line_view_Stack();

};


#endif // QCOMPUT_H
