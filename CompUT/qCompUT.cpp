#include <qCompUT.h>

QCompUT::QCompUT(QWidget* father) : QWidget(father){
    stack = new Stack;
    controleur = new Controleur(ExpressionManager::getInstance(), *stack);

    message   = new QLineEdit;
    viewStack = new QTableWidget(stack->getNbItemsToAffiche(),1);
    commande  = new QLineEdit;

    tab = new QTabWidget(this);
    QWidget* Principal = new QWidget;secondary_view["Principal"] = Principal;
    QWidget* Variable = new QWidget; secondary_view["Variable"] = Variable;
    QWidget* Program = new QWidget;  secondary_view["Program"] = Program;
    QWidget* Settings = new QWidget; secondary_view["Settings"] = Settings;

    //Déclaration des boutons chiffres dans un vecteur
    QPushButton* b1 = new QPushButton("1"); buttons_First_keyboard["b1"] = b1; buttons_First_keyboard["b1"]->setFixedSize(40,40);
    QPushButton* b2 = new QPushButton("2"); buttons_First_keyboard["b2"] = b2; buttons_First_keyboard["b2"]->setFixedSize(40,40);
    QPushButton* b3 = new QPushButton("3"); buttons_First_keyboard["b3"] = b3; buttons_First_keyboard["b3"]->setFixedSize(40,40);
    QPushButton* b4 = new QPushButton("4"); buttons_First_keyboard["b4"] = b4; buttons_First_keyboard["b4"]->setFixedSize(40,40);
    QPushButton* b5 = new QPushButton("5"); buttons_First_keyboard["b5"] = b5; buttons_First_keyboard["b5"]->setFixedSize(40,40);
    QPushButton* b6 = new QPushButton("6"); buttons_First_keyboard["b6"] = b6; buttons_First_keyboard["b6"]->setFixedSize(40,40);
    QPushButton* b7 = new QPushButton("7"); buttons_First_keyboard["b7"] = b7; buttons_First_keyboard["b7"]->setFixedSize(40,40);
    QPushButton* b8 = new QPushButton("8"); buttons_First_keyboard["b8"] = b8; buttons_First_keyboard["b8"]->setFixedSize(40,40);
    QPushButton* b9 = new QPushButton("9"); buttons_First_keyboard["b9"] = b9; buttons_First_keyboard["b9"]->setFixedSize(40,40);
    QPushButton* b0 = new QPushButton("0"); buttons_First_keyboard["b0"] = b0; buttons_First_keyboard["b0"]->setFixedSize(40,40);
    QPushButton* bPlus  = new QPushButton("+"); buttons_First_keyboard["plus"] = bPlus; buttons_First_keyboard["plus"]->setFixedSize(40,40);
    QPushButton* bMoins = new QPushButton("-"); buttons_First_keyboard["moins"]= bMoins; buttons_First_keyboard["moins"]->setFixedSize(40,40);
    QPushButton* bMult  = new QPushButton("*"); buttons_First_keyboard["mult"] = bMult; buttons_First_keyboard["mutl"]->setFixedSize(40,40);
    QPushButton* bDiv   = new QPushButton("/"); buttons_First_keyboard["div"]  = bDiv; buttons_First_keyboard["div"]->setFixedSize(40,40);
    QPushButton* bEqual = new QPushButton("="); buttons_First_keyboard["equal"]= bEqual; buttons_First_keyboard["equal"]->setFixedSize(40,40);

    QPushButton* prog1 = new QPushButton(""); buttons_Second_keyboard["prog1"] = prog1; buttons_Second_keyboard["prog1"]->setFixedSize(60,40);
    QPushButton* prog2 = new QPushButton(""); buttons_Second_keyboard["prog2"] = prog2; buttons_Second_keyboard["prog2"]->setFixedSize(60,40);
    QPushButton* prog3 = new QPushButton(""); buttons_Second_keyboard["prog3"] = prog3; buttons_Second_keyboard["prog3"]->setFixedSize(60,40);
    QPushButton* prog4 = new QPushButton(""); buttons_Second_keyboard["prog4"] = prog4; buttons_Second_keyboard["prog4"]->setFixedSize(60,40);
    QPushButton* prog5 = new QPushButton(""); buttons_Second_keyboard["prog5"] = prog5; buttons_Second_keyboard["prog5"]->setFixedSize(60,40);
    QPushButton* prog6 = new QPushButton(""); buttons_Second_keyboard["prog6"] = prog6; buttons_Second_keyboard["prog6"]->setFixedSize(60,40);
    QPushButton* prog7 = new QPushButton(""); buttons_Second_keyboard["prog7"] = prog7; buttons_Second_keyboard["prog7"]->setFixedSize(60,40);
    QPushButton* prog8 = new QPushButton(""); buttons_Second_keyboard["prog8"] = prog8; buttons_Second_keyboard["prog8"]->setFixedSize(60,40);
    QPushButton* prog9 = new QPushButton(""); buttons_Second_keyboard["prog9"] = prog9; buttons_Second_keyboard["prog9"]->setFixedSize(60,40);
    QPushButton* prog10 = new QPushButton(""); buttons_Second_keyboard["prog10"] = prog10; buttons_Second_keyboard["prog10"]->setFixedSize(60,40);
    QPushButton* prog11 = new QPushButton(""); buttons_Second_keyboard["prog11"] = prog11; buttons_Second_keyboard["prog11"]->setFixedSize(60,40);
    QPushButton* prog12 = new QPushButton(""); buttons_Second_keyboard["prog12"] = prog12; buttons_Second_keyboard["prog12"]->setFixedSize(60,40);

    QPushButton* open_keyboard_one = new QPushButton("reduce"); buttons_First_keyboard["open_keyboard_one"] = open_keyboard_one; buttons_First_keyboard["open_keyboard_one"]->setFixedSize(40,40);
    QPushButton* open_keyboard_two = new QPushButton("reduce"); buttons_Second_keyboard["open_keyboard_two"] = open_keyboard_two; buttons_Second_keyboard["open_keyboard_two"]->setFixedSize(40,40);

    //Déclaration des différents onglets



/*------------------------------------------------------------------*/
/*---------Création de layout HORIZONTAUX sous forme de Map---------*/
/*------------------------------------------------------------------*/
    QHBoxLayout* layout123 = new QHBoxLayout; layout_Horizontal["layout123"] = layout123;
    QHBoxLayout* layout456 = new QHBoxLayout; layout_Horizontal["layout456"] = layout456;
    QHBoxLayout* layout789 = new QHBoxLayout; layout_Horizontal["layout789"] = layout789;
    QHBoxLayout* layout0 = new QHBoxLayout; layout_Horizontal["layout0"] = layout0;

    QHBoxLayout* layout_key_one = new QHBoxLayout; layout_Horizontal["layout_key_one"] = layout_key_one;

    //Création des couches pour les programmes et variables
    QHBoxLayout* layout_prog123 = new QHBoxLayout; layout_Horizontal["layout_prog123"] = layout_prog123;
    QHBoxLayout* layout_prog456 = new QHBoxLayout; layout_Horizontal["layout_prog456"] = layout_prog456;
    QHBoxLayout* layout_prog789 = new QHBoxLayout; layout_Horizontal["layout_prog789"] = layout_prog789;
    QHBoxLayout* layout_prog1012 = new QHBoxLayout; layout_Horizontal["layout_prog1012"] = layout_prog1012;

    //Création de la couche avec le clavier N°1 et N°2
    QHBoxLayout* layout_keyboard_one_two = new QHBoxLayout; layout_Horizontal["layout_keyboard_one_two"] = layout_keyboard_one_two;

    //Création de la couche de l'affichage avec la couche du clavier N°1
    QHBoxLayout* layout_display_and_keyboard = new QHBoxLayout; layout_Horizontal["layout_display_and_keyboard"] = layout_display_and_keyboard;


/*------------------------------------------------------------------*/
/*----------Création de layout VERTICAUX sous forme de Map----------*/
/*------------------------------------------------------------------*/
    //Déclaration de la couche Stack, viewStack et message avec ajout des widgets
    QVBoxLayout* layout_stack = new QVBoxLayout; layout_Vertical["layout_stack"] = layout_stack;

    //Création de la couche de tous les chiffres
    QVBoxLayout* layout_number = new QVBoxLayout; layout_Vertical["layout_number"] = layout_number;
    //Création de la couche de tous les opérateurs
    QVBoxLayout* layout_operator = new QVBoxLayout; layout_Vertical["layout_operator"] = layout_operator;

    //Création de la couche pour le clavier N°1 + Open et Close
    QVBoxLayout* layout_keyboard_one = new QVBoxLayout; layout_Vertical["layout_keyboard_one"] = layout_keyboard_one;

    //Création de la couche du clavier N°2 + Open et Close
    QVBoxLayout* layout_key_two = new QVBoxLayout; layout_Vertical["layout_key_two"] = layout_key_two;
    QVBoxLayout* layout_keyboard_two = new QVBoxLayout; layout_Vertical["layout_keyboard_two"] = layout_keyboard_two;

    QVBoxLayout* layout_general = new QVBoxLayout; layout_Vertical["layout_general"] = layout_general;

/*------------------------------------------------------------------*/
/*---------------Initialisation des différents layout---------------*/
/*------------------------------------------------------------------*/

    layout_Vertical["layout_stack"]->addWidget(message);
    layout_Vertical["layout_stack"]->addWidget(viewStack);
    layout_Vertical["layout_stack"]->addWidget(commande);

    layout_Horizontal["layout123"]->addWidget(buttons_First_keyboard["b1"]); layout_Horizontal["layout123"]->addWidget(buttons_First_keyboard["b2"]); layout_Horizontal["layout123"]->addWidget(buttons_First_keyboard["b3"]);
    layout_Horizontal["layout456"]->addWidget(buttons_First_keyboard["b4"]); layout_Horizontal["layout456"]->addWidget(buttons_First_keyboard["b5"]); layout_Horizontal["layout456"]->addWidget(buttons_First_keyboard["b6"]);
    layout_Horizontal["layout789"]->addWidget(buttons_First_keyboard["b7"]); layout_Horizontal["layout789"]->addWidget(buttons_First_keyboard["b8"]); layout_Horizontal["layout789"]->addWidget(buttons_First_keyboard["b9"]);
    layout_Horizontal["layout0"]->addWidget(buttons_First_keyboard["b0"]);

    layout_Vertical["layout_number"]->addLayout(layout_Horizontal["layout123"]);
    layout_Vertical["layout_number"]->addLayout(layout_Horizontal["layout456"]);
    layout_Vertical["layout_number"]->addLayout(layout_Horizontal["layout789"]);
    layout_Vertical["layout_number"]->addLayout(layout_Horizontal["layout0"]);

    layout_Vertical["layout_operator"]->addWidget(buttons_First_keyboard["plus"]);
    layout_Vertical["layout_operator"]->addWidget(buttons_First_keyboard["moins"]);
    layout_Vertical["layout_operator"]->addWidget(buttons_First_keyboard["mult"]);
    layout_Vertical["layout_operator"]->addWidget(buttons_First_keyboard["div"]);
    layout_Vertical["layout_operator"]->addWidget(buttons_First_keyboard["equal"]);

    layout_Horizontal["layout_key_one"]->addLayout(layout_Vertical["layout_number"]); layout_Horizontal["layout_key_one"]->addLayout(layout_Vertical["layout_operator"]);

    layout_Vertical["layout_keyboard_one"]->addWidget(buttons_First_keyboard["open_keyboard_one"]); layout_Vertical["layout_keyboard_one"]->addLayout(layout_Horizontal["layout_key_one"]);

    layout_Horizontal["layout_prog123"]->addWidget(buttons_Second_keyboard["prog1"]);
    layout_Horizontal["layout_prog123"]->addWidget(buttons_Second_keyboard["prog2"]);
    layout_Horizontal["layout_prog123"]->addWidget(buttons_Second_keyboard["prog3"]);

    layout_Horizontal["layout_prog456"]->addWidget(buttons_Second_keyboard["prog4"]);
    layout_Horizontal["layout_prog456"]->addWidget(buttons_Second_keyboard["prog5"]);
    layout_Horizontal["layout_prog456"]->addWidget(buttons_Second_keyboard["prog6"]);

    layout_Horizontal["layout_prog789"]->addWidget(buttons_Second_keyboard["prog7"]);
    layout_Horizontal["layout_prog789"]->addWidget(buttons_Second_keyboard["prog8"]);
    layout_Horizontal["layout_prog789"]->addWidget(buttons_Second_keyboard["prog9"]);

    layout_Horizontal["layout_prog1012"]->addWidget(buttons_Second_keyboard["prog10"]);
    layout_Horizontal["layout_prog1012"]->addWidget(buttons_Second_keyboard["prog11"]);
    layout_Horizontal["layout_prog1012"]->addWidget(buttons_Second_keyboard["prog12"]);

    layout_Vertical["layout_key_two"]->addLayout(layout_Horizontal["layout_prog123"]); layout_Vertical["layout_key_two"]->addLayout(layout_Horizontal["layout_prog456"]);
    layout_Vertical["layout_key_two"]->addLayout(layout_Horizontal["layout_prog789"]); layout_Vertical["layout_key_two"]->addLayout(layout_Horizontal["layout_prog1012"]);
    layout_Vertical["layout_keyboard_two"]->addWidget(buttons_Second_keyboard["open_keyboard_two"]); layout_Vertical["layout_keyboard_two"]->addLayout(layout_Vertical["layout_keyboard_two"]);

    layout_Horizontal["layout_keyboard_one_two"]->addLayout(layout_Vertical["layout_keyboard_one"]); layout_Horizontal["layout_keyboard_one_two"]->addLayout(layout_Vertical["layout_keyboard_two"]);


    Principal->setLayout(layout_Horizontal["layout_keyboard_one_two"]); tab->addTab(secondary_view["Principal"], "Keyboard");
    /*Variable->setLayout(NULL);*/ tab->addTab(secondary_view["Variable"], "Variable");
    /*Program->setLayout(NULL);*/ tab->addTab(secondary_view["Program"], "Program");
    /*Settings->setLayout(NULL);*/ tab->addTab(secondary_view["Settings"], "Settings");

    layout_Horizontal["layout_display_and_keyboard"]->addLayout(layout_Vertical["layout_stack"]); layout_Horizontal["layout_display_and_keyboard"]->addWidget(tab);


/*------------------------------------------------------------------*/


    setLayout(layout_Horizontal["layout_keyboard_one_two"]);
    setWindowTitle("Comp'UT");

    message->setReadOnly(true);
    message->setText("Bonjour et bienvenu dans CompUT");

    //viewStack->setStyleSheet("color: white");
    viewStack->horizontalHeader()->setVisible(false);
    //Ajuster la taille des colone
    viewStack->horizontalHeader()->setStretchLastSection(true);
    viewStack->setFixedHeight(stack->getNbItemsToAffiche()*viewStack->rowHeight(0)+2);
    //Vérouiller l'écriture au clavier dans le tableau
    viewStack->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //Affichage inverse indice tableau
    QStringList labels;
    for(size_t i=stack->getNbItemsToAffiche(); i>0; i--){
        QString str = QString::number(i);
        str+=" :";
        labels << str;
        viewStack->setItem(i-1,0,new QTableWidgetItem(""));
    }
    viewStack->setVerticalHeaderLabels(labels);


    connect(buttons_First_keyboard["b1"],SIGNAL(clicked()),this,SLOT(slot1()));
    connect(buttons_First_keyboard["b2"],SIGNAL(clicked()),this,SLOT(slot2()));
    connect(buttons_First_keyboard["b3"],SIGNAL(clicked()),this,SLOT(slot3()));
    connect(buttons_First_keyboard["b4"],SIGNAL(clicked()),this,SLOT(slot4()));
    connect(buttons_First_keyboard["b5"],SIGNAL(clicked()),this,SLOT(slot5()));
    connect(buttons_First_keyboard["b6"],SIGNAL(clicked()),this,SLOT(slot6()));
    connect(buttons_First_keyboard["b7"],SIGNAL(clicked()),this,SLOT(slot7()));
    connect(buttons_First_keyboard["b8"],SIGNAL(clicked()),this,SLOT(slot8()));
    connect(buttons_First_keyboard["b9"],SIGNAL(clicked()),this,SLOT(slot9()));
    connect(buttons_First_keyboard["b0"],SIGNAL(clicked()),this,SLOT(slot0()));

    connect(buttons_First_keyboard["plus"],SIGNAL(clicked()),this,SLOT(slotPlus()));
    connect(buttons_First_keyboard["moins"],SIGNAL(clicked()),this,SLOT(slotMoins()));
    connect(buttons_First_keyboard["mult"],SIGNAL(clicked()),this,SLOT(slotMult()));
    connect(buttons_First_keyboard["div"],SIGNAL(clicked()),this,SLOT(slotDiv()));
    connect(buttons_First_keyboard["equal"],SIGNAL(clicked()),this,SLOT(slotEqual()));

    connect(buttons_First_keyboard["open_keyboard_one"],SIGNAL(clicked()),this,SLOT(slotOpen1()));
    connect(buttons_Second_keyboard["open_keyboard_two"],SIGNAL(clicked()),this,SLOT(slotOpen2()));


    //Focus a un composant
    commande->setFocus(Qt::OtherFocusReason);

    connect(stack,SIGNAL(modificationEtat()),this,SLOT(refresh()));
    connect(commande,SIGNAL(returnPressed()),this,SLOT(getNextCommande()));

    setFixedSize(800,350);

}

void QCompUT::refresh(){
    message->setText(stack->getMessage());
    for(size_t i=0; i<stack->getNbItemsToAffiche(); i++)
        viewStack->item(i,0)->setText("");
   size_t nb=0;
    for(Stack::iterator it=stack->begin(); it!=stack->end() && nb<stack->getNbItemsToAffiche(); ++it){
        viewStack->item(stack->getNbItemsToAffiche()-nb-1,0)->setText((*it).toString());
        nb++;
    }
}

void QCompUT::getNextCommande(){
    QString c=commande->text();
    controleur->commande(c);
    commande->clear();
    text ="";
}

void QCompUT::slot1(){ text +="1"; commande->setText(text); }
void QCompUT::slot2(){ text +="2"; commande->setText(text); }
void QCompUT::slot3(){ text +="3"; commande->setText(text); }
void QCompUT::slot4(){ text +="4"; commande->setText(text); }
void QCompUT::slot5(){ text +="5"; commande->setText(text); }
void QCompUT::slot6(){ text +="6"; commande->setText(text); }
void QCompUT::slot7(){ text +="7"; commande->setText(text); }
void QCompUT::slot8(){ text +="8"; commande->setText(text); }
void QCompUT::slot9(){ text +="9"; commande->setText(text); }
void QCompUT::slot0(){ text +="0"; commande->setText(text); }
void QCompUT::slotPlus() { text +="+"; commande->setText(text); }
void QCompUT::slotMoins(){ text +="-"; commande->setText(text); }
void QCompUT::slotMult() { text +="*"; commande->setText(text); }
void QCompUT::slotDiv()  { text +="/"; commande->setText(text); }
void QCompUT::slotEqual()  { QCompUT::getNextCommande(); }


void QCompUT::slotOpen1(){ }
void QCompUT::slotOpen2(){ }

void QCompUT::affichage_Variable(){
//    QPushButton* test = new QPushButton("test"); buttons_First_keyboard.push_back(test); test->setFixedSize(40,40);
//    QVBoxLayout* test2 = new QVBoxLayout; layoutV.push_back(test2);
//    test2->addWidget(test);
}


