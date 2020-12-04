#include <qCompUT.h>

QCompUT::QCompUT(QWidget* father) : QWidget(father){
    stack = new Stack;
    controleur = new Controleur(ExpressionManager::getInstance(), *stack);

    message   = new QLineEdit;
    viewStack = new QTableWidget(stack->getNbItemsToAffiche(),1);
    commande  = new QLineEdit;


    //Déclaration de la couche Stack, viewStack et message avec ajout des widgets
    QVBoxLayout* layout_Stack = new QVBoxLayout; layoutV.push_back(layout_Stack);
    layout_Stack->addWidget(message); layout_Stack->addWidget(viewStack); layout_Stack->addWidget(commande);

    //Déclaration des boutons chiffres dans un vecteur
    QPushButton* b1 = new QPushButton("1"); buttons_First_keyboard.push_back(b1); b1->setFixedSize(40,40);
    QPushButton* b2 = new QPushButton("2"); buttons_First_keyboard.push_back(b2); b2->setFixedSize(40,40);
    QPushButton* b3 = new QPushButton("3"); buttons_First_keyboard.push_back(b3); b3->setFixedSize(40,40);
    QPushButton* b4 = new QPushButton("4"); buttons_First_keyboard.push_back(b4); b4->setFixedSize(40,40);
    QPushButton* b5 = new QPushButton("5"); buttons_First_keyboard.push_back(b5); b5->setFixedSize(40,40);
    QPushButton* b6 = new QPushButton("6"); buttons_First_keyboard.push_back(b6); b6->setFixedSize(40,40);
    QPushButton* b7 = new QPushButton("7"); buttons_First_keyboard.push_back(b7); b7->setFixedSize(40,40);
    QPushButton* b8 = new QPushButton("8"); buttons_First_keyboard.push_back(b8); b8->setFixedSize(40,40);
    QPushButton* b9 = new QPushButton("9"); buttons_First_keyboard.push_back(b9); b9->setFixedSize(40,40);
    QPushButton* b0 = new QPushButton("0"); buttons_First_keyboard.push_back(b0); b0->setFixedSize(150,40);
    QPushButton* bPlus  = new QPushButton("+"); buttons_First_keyboard.push_back(bPlus);  bPlus->setFixedSize(40,40);
    QPushButton* bMoins = new QPushButton("-"); buttons_First_keyboard.push_back(bMoins); bMoins->setFixedSize(40,40);
    QPushButton* bMult  = new QPushButton("x"); buttons_First_keyboard.push_back(bMult);  bMult->setFixedSize(40,40);
    QPushButton* bDiv   = new QPushButton("/"); buttons_First_keyboard.push_back(bDiv);   bDiv->setFixedSize(40,40);
    QPushButton* bEqual = new QPushButton("="); buttons_First_keyboard.push_back(bEqual); bEqual->setFixedSize(40,40);

    QPushButton* prog1 = new QPushButton(""); buttons_Second_keyboard.push_back(prog1); prog1->setFixedSize(60,40);
    QPushButton* prog2 = new QPushButton(""); buttons_Second_keyboard.push_back(prog2); prog2->setFixedSize(60,40);
    QPushButton* prog3 = new QPushButton(""); buttons_Second_keyboard.push_back(prog3); prog3->setFixedSize(60,40);
    QPushButton* prog4 = new QPushButton(""); buttons_Second_keyboard.push_back(prog4); prog4->setFixedSize(60,40);
    QPushButton* prog5 = new QPushButton(""); buttons_Second_keyboard.push_back(prog5); prog5->setFixedSize(60,40);
    QPushButton* prog6 = new QPushButton(""); buttons_Second_keyboard.push_back(prog6); prog6->setFixedSize(60,40);
    QPushButton* prog7 = new QPushButton(""); buttons_Second_keyboard.push_back(prog7); prog7->setFixedSize(60,40);
    QPushButton* prog8 = new QPushButton(""); buttons_Second_keyboard.push_back(prog8); prog8->setFixedSize(60,40);
    QPushButton* prog9 = new QPushButton(""); buttons_Second_keyboard.push_back(prog9); prog9->setFixedSize(60,40);
    QPushButton* prog10 = new QPushButton(""); buttons_Second_keyboard.push_back(prog10); prog10->setFixedSize(60,40);
    QPushButton* prog11 = new QPushButton(""); buttons_Second_keyboard.push_back(prog11); prog11->setFixedSize(60,40);
    QPushButton* prog12 = new QPushButton(""); buttons_Second_keyboard.push_back(prog12); prog12->setFixedSize(60,40);

    QPushButton* open_keyboard_one = new QPushButton("open"); buttons_Second_keyboard.push_back(open_keyboard_one); open_keyboard_one->setFixedSize(60,25);
    QPushButton* close_keyboard_one = new QPushButton("close"); buttons_Second_keyboard.push_back(close_keyboard_one); close_keyboard_one->setFixedSize(60,25);
    QPushButton* open_keyboard_two = new QPushButton("open"); buttons_Second_keyboard.push_back(open_keyboard_two); open_keyboard_two->setFixedSize(60,25);
    QPushButton* close_keyboard_two = new QPushButton("close"); buttons_Second_keyboard.push_back(close_keyboard_two); close_keyboard_two->setFixedSize(60,25);



    //Déclaration des différents onglets
    tab = new QTabWidget(this);
    QWidget* Principal = new QWidget;   secondary_view.push_back(Principal);
    QWidget* Variable = new QWidget;    secondary_view.push_back(Variable);
    QWidget* Programme = new QWidget;   secondary_view.push_back(Programme);
    QWidget* Calculateur = new QWidget; secondary_view.push_back(Calculateur);

    //Création de la couche des chiffres avec plusieurs layouts horizontaux et avec ajout des windgets
    QHBoxLayout* layout123 = new QHBoxLayout; layoutH.push_back(layout123);
    layout123->addWidget(b1); layout123->addWidget(b2); layout123->addWidget(b3);
    QHBoxLayout* layout456 = new QHBoxLayout; layoutH.push_back(layout456);
    layout456->addWidget(b4); layout456->addWidget(b5); layout456->addWidget(b6);
    QHBoxLayout* layout789 = new QHBoxLayout; layoutH.push_back(layout789);
    layout789->addWidget(b7); layout789->addWidget(b8); layout789->addWidget(b9);
    QHBoxLayout* layout0 = new QHBoxLayout; layoutH.push_back(layout0);
    layout0->addWidget(b0);

    //Création de la couche de tous les chiffres
    QVBoxLayout* layout_Number = new QVBoxLayout; layoutV.push_back(layout_Number);
    layout_Number->addLayout(layout123); layout_Number->addLayout(layout456); layout_Number->addLayout(layout789); layout_Number->addLayout(layout0);
    //Création de la couche des opérateurs
    QVBoxLayout* layout_Operator = new QVBoxLayout; layoutV.push_back(layout_Operator);
    layout_Operator->addWidget(bPlus); layout_Operator->addWidget(bMoins); layout_Operator->addWidget(bMult); layout_Operator->addWidget(bDiv); layout_Operator->addWidget(bEqual);
    //Bouton Open et close pour réduire le clavier 1
    QHBoxLayout* layout_OpenClose_One = new QHBoxLayout; layoutH.push_back(layout_OpenClose_One);
    layout_OpenClose_One->addWidget(open_keyboard_one);layout_OpenClose_One->addWidget(close_keyboard_one);


    //Création de la couche pour le clavier N°1 + Open et Close
    QHBoxLayout* layout_Key_One = new QHBoxLayout; layoutH.push_back(layout_Key_One);
    layout_Key_One->addLayout(layout_Number); layout_Key_One->addLayout(layout_Operator);
    QVBoxLayout* layout_Keyboard_One = new QVBoxLayout; layoutV.push_back(layout_Keyboard_One);
    layout_Keyboard_One->addLayout(layout_OpenClose_One);layout_Keyboard_One->addLayout(layout_Key_One);


    //Création des couches pour les programmes et variables
    QHBoxLayout* layout_prog123 = new QHBoxLayout; layoutH.push_back(layout_prog123);
    layout_prog123->addWidget(prog1); layout_prog123->addWidget(prog2); layout_prog123->addWidget(prog3);
    QHBoxLayout* layout_prog456 = new QHBoxLayout; layoutH.push_back(layout_prog456);
    layout_prog456->addWidget(prog4); layout_prog456->addWidget(prog5); layout_prog456->addWidget(prog6);
    QHBoxLayout* layoutp_prog789 = new QHBoxLayout; layoutH.push_back(layoutp_prog789);
    layoutp_prog789->addWidget(prog7); layoutp_prog789->addWidget(prog8); layoutp_prog789->addWidget(prog9);
    QHBoxLayout* layoutp_prog1012 = new QHBoxLayout; layoutH.push_back(layoutp_prog1012);
    layoutp_prog1012->addWidget(prog10); layoutp_prog1012->addWidget(prog11); layoutp_prog1012->addWidget(prog12);
    //Bouton Open et close pour réduire le clavier 2
    QHBoxLayout* layout_OpenClose_Two = new QHBoxLayout; layoutH.push_back(layout_OpenClose_Two);
    layout_OpenClose_Two->addWidget(open_keyboard_two);layout_OpenClose_Two->addWidget(close_keyboard_two);

    //Création de la couche du clavier N°2 + Open et Close
    QVBoxLayout* layout_Key_Two = new QVBoxLayout; layoutV.push_back(layout_Key_Two);
    layout_Key_Two->addLayout(layout_prog123); layout_Key_Two->addLayout(layout_prog456); layout_Key_Two->addLayout(layoutp_prog789);layout_Key_Two->addLayout(layoutp_prog1012);


    QVBoxLayout* layout_Keyboard_Two = new QVBoxLayout; layoutV.push_back(layout_Keyboard_Two);
    layout_Keyboard_Two->addLayout(layout_OpenClose_Two);layout_Keyboard_Two->addLayout(layout_Key_Two);

    //Création de la couche avec le clavier N°1 et N°2
    QHBoxLayout* layout_Keyboard_One_Two = new QHBoxLayout; layoutH.push_back(layout_Keyboard_One_Two);
    layout_Keyboard_One_Two->addLayout(layout_Keyboard_One); layout_Keyboard_One_Two->addLayout(layout_Keyboard_Two);

    //Rendre les bouton Open non visible car les clavier 1 et 2 sont ouvert à défaut
    open_keyboard_one->hide();  open_keyboard_two->hide();


    QPushButton* test = new QPushButton("test"); buttons_First_keyboard.push_back(test); test->setFixedSize(40,40);
    QVBoxLayout* test2 = new QVBoxLayout; layoutV.push_back(test2);
    test2->addWidget(test);


    Principal->setLayout(layout_Keyboard_One_Two); tab->addTab(Principal, "Keyboard");
    /*Variable->setLayout(test2);*/ tab->addTab(Variable, "Variable");
    /*Programme->setLayout(NULL);*/ tab->addTab(Programme, "Program");
    /*Calculateur->setLayout(NULL);*/ tab->addTab(Calculateur, "Settings");



    //Création de la couche de l'affichage avec la couche du clavier N°1
    QHBoxLayout* layout_Display_And_Keyboard_One = new QHBoxLayout; layoutH.push_back(layout_Display_And_Keyboard_One);
    layout_Display_And_Keyboard_One->addLayout(layout_Stack); layout_Display_And_Keyboard_One->addWidget(tab);


    //Création de la couche générale qui englobe le tout
    QVBoxLayout* layout_general = new QVBoxLayout; layoutV.push_back(layout_general);
    layout_general->addLayout(layout_Display_And_Keyboard_One); layout_general->addLayout(layout_Keyboard_Two);



    setLayout(layout_general);
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


    connect(b1,SIGNAL(clicked()),this,SLOT(slot1()));
    connect(b2,SIGNAL(clicked()),this,SLOT(slot2()));
    connect(b3,SIGNAL(clicked()),this,SLOT(slot3()));
    connect(b4,SIGNAL(clicked()),this,SLOT(slot4()));
    connect(b5,SIGNAL(clicked()),this,SLOT(slot5()));
    connect(b6,SIGNAL(clicked()),this,SLOT(slot6()));
    connect(b7,SIGNAL(clicked()),this,SLOT(slot7()));
    connect(b8,SIGNAL(clicked()),this,SLOT(slot8()));
    connect(b9,SIGNAL(clicked()),this,SLOT(slot9()));
    connect(b0,SIGNAL(clicked()),this,SLOT(slot0()));

    connect(bPlus,SIGNAL(clicked()),this,SLOT(slotPlus()));
    connect(bMoins,SIGNAL(clicked()),this,SLOT(slotMoins()));
    connect(bMult,SIGNAL(clicked()),this,SLOT(slotMult()));
    connect(bDiv,SIGNAL(clicked()),this,SLOT(slotDiv()));
    connect(bEqual,SIGNAL(clicked()),this,SLOT(slotEqual()));

    connect(open_keyboard_one,SIGNAL(clicked()),this,SLOT(slotOpen1()));
    connect(close_keyboard_one,SIGNAL(clicked()),this,SLOT(slotClose1()));
    connect(open_keyboard_two,SIGNAL(clicked()),this,SLOT(slotOpen2()));
    connect(close_keyboard_two,SIGNAL(clicked()),this,SLOT(slotClose2()));







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


void QCompUT::slotClose1(){ }
void QCompUT::slotOpen1(){ }
void QCompUT::slotOpen2(){ }
void QCompUT::slotClose2(){ }

