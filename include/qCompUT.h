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
#include <QFileDialog>
#include <algorithm>

#include "computer.h"
#include "operator.h"

using namespace std;

class QCompUT : public QWidget{
    Q_OBJECT

    QString text;
    size_t Nbr_Line = 8;
    QSpinBox* Nbr_Line_Stack;
    QTabWidget *tab;

    QMap<QString,QPushButton*> buttons_First_keyboard;
    QMap<QString,QPushButton*> buttons_Second_keyboard;
    QMap<QString,QPushButton*> buttons_secondary_view;
    QMap<QString,QPushButton*> buttons_var;
    QMap<QString,QPushButton*> buttons_prog;
    QMap<QString,QPushButton*> buttons_settings;
    QMap<QString,QVBoxLayout*> layout_Vertical;
    QMap<QString,QHBoxLayout*> layout_Horizontal;
    QMap<QString,QWidget*> secondary_view;
    QMap<QString,QLineEdit*> Line_Edit;
    QMap<QString,QLabel*> label;
    QMap<QString,QComboBox*> list;
    QMap<QString,QTableWidget*> table;

public:
    explicit QCompUT(QWidget *father = 0);
    void creation();
    void Initialisation();
    void Initialisation_Stack();
    void Update_Var_Prog();

public slots:
    void refresh_stack();
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
    void slotSave(); void slotLoad();


};

#endif // QCOMPUT_H
