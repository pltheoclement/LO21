#include <qCompUT.h>

QCompUT::QCompUT(QWidget* father) : QWidget(father){

    Initialisation_Stack(); //Initilisation de la pile
    creation(); //Création des différents composant utiliser pour l'interface de l'application
    Initialisation(); //Initialisation des différents composants

    //Utilisation des signaux poiur les composant composants
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

    connect(buttons_First_keyboard["reduce_keyboard_one"],SIGNAL(clicked()),this,SLOT(slotReduce1()));
    connect(buttons_First_keyboard["open_keyboard_one"],SIGNAL(clicked()),this,SLOT(slotOpen1()));
    connect(buttons_Second_keyboard["reduce_keyboard_two"],SIGNAL(clicked()),this,SLOT(slotReduce2()));
    connect(buttons_Second_keyboard["open_keyboard_two"],SIGNAL(clicked()),this,SLOT(slotOpen2()));

    connect(stack,SIGNAL(modificationEtat()),this,SLOT(refresh()));
    connect(commande,SIGNAL(returnPressed()),this,SLOT(getNextCommande()));

    connect(buttons_secondary_view["new_var"],SIGNAL(clicked()),this,SLOT(slotNewVariable()));
    connect(buttons_secondary_view["modif_var"],SIGNAL(clicked()),this,SLOT(slotModifVariable()));
    connect(buttons_secondary_view["delete_var"],SIGNAL(clicked()),this,SLOT(slotDeleteVariable()));

    connect(buttons_secondary_view["new_prog"],SIGNAL(clicked()),this,SLOT(slotNewProg()));
    connect(buttons_secondary_view["modif_prog"],SIGNAL(clicked()),this,SLOT(slotModifProg()));
    connect(buttons_secondary_view["delete_prog"],SIGNAL(clicked()),this,SLOT(slotDeleteProg()));
}


void QCompUT::Initialisation_Stack(){
    stack = new Stack;
    controleur = new Controleur(ExpressionManager::getInstance(), *stack);

    message   = new QLineEdit;
    viewStack = new QTableWidget(stack->getNbItemsToAffiche(),1);
    commande  = new QLineEdit;

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
}

void QCompUT::creation(){
    //Création des différents boutons pour le claiver 1
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
    QPushButton* bMult  = new QPushButton("*"); buttons_First_keyboard["mult"] = bMult; buttons_First_keyboard["mult"]->setFixedSize(40,40);
    QPushButton* bDiv   = new QPushButton("/"); buttons_First_keyboard["div"]  = bDiv; buttons_First_keyboard["div"]->setFixedSize(40,40);
    QPushButton* bEqual = new QPushButton("="); buttons_First_keyboard["equal"]= bEqual; buttons_First_keyboard["equal"]->setFixedSize(40,40);
    QPushButton* reduce_keyboard_one = new QPushButton("reduce"); buttons_First_keyboard["reduce_keyboard_one"] = reduce_keyboard_one; buttons_First_keyboard["reduce_keyboard_one"]->setFixedSize(200,30);
    QPushButton* reduce_keyboard_two = new QPushButton("reduce"); buttons_Second_keyboard["reduce_keyboard_two"] = reduce_keyboard_two; buttons_Second_keyboard["reduce_keyboard_two"]->setFixedSize(200,30);

    //Création des différents boutons pour le claiver 2
    QPushButton* var1 = new QPushButton; buttons_Second_keyboard["var1"] = var1; buttons_Second_keyboard["var1"]->setFixedSize(88,35);
    QPushButton* var2 = new QPushButton; buttons_Second_keyboard["var2"] = var2; buttons_Second_keyboard["var2"]->setFixedSize(88,35);
    QPushButton* var3 = new QPushButton; buttons_Second_keyboard["var3"] = var3; buttons_Second_keyboard["var3"]->setFixedSize(88,35);
    QPushButton* var4 = new QPushButton; buttons_Second_keyboard["var4"] = var4; buttons_Second_keyboard["var4"]->setFixedSize(88,35);
    QPushButton* var5 = new QPushButton; buttons_Second_keyboard["var5"] = var5; buttons_Second_keyboard["var5"]->setFixedSize(88,35);
    QPushButton* var6 = new QPushButton; buttons_Second_keyboard["var6"] = var6; buttons_Second_keyboard["var6"]->setFixedSize(88,35);
    QPushButton* prog1 = new QPushButton; buttons_Second_keyboard["prog1"] = prog1; buttons_Second_keyboard["prog1"]->setFixedSize(88,35);
    QPushButton* prog2 = new QPushButton; buttons_Second_keyboard["prog2"] = prog2; buttons_Second_keyboard["prog2"]->setFixedSize(88,35);
    QPushButton* prog3 = new QPushButton; buttons_Second_keyboard["prog3"] = prog3; buttons_Second_keyboard["prog3"]->setFixedSize(88,35);
    QPushButton* prog4 = new QPushButton; buttons_Second_keyboard["prog4"] = prog4; buttons_Second_keyboard["prog4"]->setFixedSize(88,35);
    QPushButton* prog5 = new QPushButton; buttons_Second_keyboard["prog5"] = prog5; buttons_Second_keyboard["prog5"]->setFixedSize(88,35);
    QPushButton* prog6 = new QPushButton; buttons_Second_keyboard["prog6"] = prog6; buttons_Second_keyboard["prog6"]->setFixedSize(88,35);
    QPushButton* open_keyboard_one = new QPushButton("open"); buttons_First_keyboard["open_keyboard_one"] = open_keyboard_one; buttons_First_keyboard["open_keyboard_one"]->setFixedSize(200,30);
    QPushButton* open_keyboard_two = new QPushButton("open"); buttons_Second_keyboard["open_keyboard_two"] = open_keyboard_two; buttons_Second_keyboard["open_keyboard_two"]->setFixedSize(200,30);

    //Création des boutons pour la vue secondaire "Variable"
    QPushButton* new_var = new QPushButton("New variable"); buttons_secondary_view["new_var"] = new_var; buttons_secondary_view["new_var"]->setFixedSize(130,30);
    QPushButton* modif_var = new QPushButton("Modif variable"); buttons_secondary_view["modif_var"] = modif_var; buttons_secondary_view["modif_var"]->setFixedSize(130,30);
    QPushButton* delete_var = new QPushButton("Delete variable"); buttons_secondary_view["delete_var"] = delete_var; buttons_secondary_view["delete_var"]->setFixedSize(130,30);

    //Création des boutons pour la vue secondaire "Program"
    QPushButton* new_prog = new QPushButton("New program"); buttons_secondary_view["new_prog"] = new_prog; buttons_secondary_view["new_prog"]->setFixedSize(130,30);
    QPushButton* modif_prog = new QPushButton("Modif program"); buttons_secondary_view["modif_prog"] = modif_prog; buttons_secondary_view["modif_prog"]->setFixedSize(130,30);
    QPushButton* delete_prog = new QPushButton("Delete program"); buttons_secondary_view["delete_prog"] = delete_prog; buttons_secondary_view["delete_prog"]->setFixedSize(130,30);


    /*-------------------------------------------------------------------------------------------------------------------------------------------*/
    /*---------Création de layout HORIZONTAUX sous forme de Map----------------------------------------------------------------------------------*/
    //Création de la couche avec les chiffres avec les couches 123, 456, ...
    QHBoxLayout* layout123 = new QHBoxLayout; layout_Horizontal["layout123"] = layout123;
    QHBoxLayout* layout456 = new QHBoxLayout; layout_Horizontal["layout456"] = layout456;
    QHBoxLayout* layout789 = new QHBoxLayout; layout_Horizontal["layout789"] = layout789;
    QHBoxLayout* layout0 = new QHBoxLayout; layout_Horizontal["layout0"] = layout0;

    QHBoxLayout* layout_key_one = new QHBoxLayout; layout_Horizontal["layout_key_one"] = layout_key_one;

    //Création de la couche pour les programmes et variables
    QHBoxLayout* layout_var_prog = new QHBoxLayout; layout_Horizontal["layout_var_prog"] = layout_var_prog;

    //Création de la couche avec le clavier N°1 et N°2
    QHBoxLayout* layout_keyboard_one_two = new QHBoxLayout; layout_Horizontal["layout_keyboard_one_two"] = layout_keyboard_one_two;

    //Création de la couche de l'affichage avec la couche du clavier N°1
    QHBoxLayout* layout_display_and_keyboard = new QHBoxLayout; layout_Horizontal["layout_display_and_keyboard"] = layout_display_and_keyboard;

    //création des couches horizontales pour la vue secondaire variable
    QHBoxLayout* layoutH_add_var = new QHBoxLayout; layout_Horizontal["layoutH_add_var"] = layoutH_add_var;
    QHBoxLayout* layoutH_modif_var = new QHBoxLayout; layout_Horizontal["layoutH_modif_var"] = layoutH_modif_var;
    QHBoxLayout* layoutH_del_var = new QHBoxLayout; layout_Horizontal["layoutH_del_var"] = layoutH_del_var;

    //création des couches horizontales pour la vue secondaire program
    QHBoxLayout* layoutH_add_prog = new QHBoxLayout; layout_Horizontal["layoutH_add_prog"] = layoutH_add_prog;
    QHBoxLayout* layoutH_modif_prog = new QHBoxLayout; layout_Horizontal["layoutH_modif_prog"] = layoutH_modif_prog;
    QHBoxLayout* layoutH_del_prog = new QHBoxLayout; layout_Horizontal["layoutH_del_prog"] = layoutH_del_prog;

    /*-------------------------------------------------------------------------------------------------------------------------------------------*/
    /*--Création de layout VERTICAUX sous forme de Map-------------------------------------------------------------------------------------------*/
    //Déclaration de la couche Stack, viewStack et message avec ajout des widgets
    QVBoxLayout* layout_stack = new QVBoxLayout; layout_Vertical["layout_stack"] = layout_stack;

    //Création de la couche de tous les chiffres
    QVBoxLayout* layout_number = new QVBoxLayout; layout_Vertical["layout_number"] = layout_number;
    //Création de la couche de tous les opérateurs
    QVBoxLayout* layout_operator = new QVBoxLayout; layout_Vertical["layout_operator"] = layout_operator;

    //Création de la couche pour le clavier N°1 + Open et Close
    QVBoxLayout* layout_keyboard_one = new QVBoxLayout; layout_Vertical["layout_keyboard_one"] = layout_keyboard_one;

    //Création de la couche du clavier N°2 + Open et Close
    QVBoxLayout* layout_keyboard_var = new QVBoxLayout; layout_Vertical["layout_keyboard_var"] = layout_keyboard_var;
    QVBoxLayout* layout_keyboard_prog = new QVBoxLayout; layout_Vertical["layout_keyboard_prog"] = layout_keyboard_prog;

    //QVBoxLayout* layout_key_two = new QVBoxLayout; layout_Vertical["layout_key_two"] = layout_key_two;
    QVBoxLayout* layout_keyboard_two = new QVBoxLayout; layout_Vertical["layout_keyboard_two"] = layout_keyboard_two;

    QVBoxLayout* layout_general = new QVBoxLayout; layout_Vertical["layout_general"] = layout_general;


    //création des couches verticales pour la vue secondaire variable
    QVBoxLayout* layoutV_add_var = new QVBoxLayout; layout_Vertical["layoutV_add_var"] = layoutV_add_var;
    QVBoxLayout* layoutV_modif_var = new QVBoxLayout; layout_Vertical["layoutV_modif_var"] = layoutV_modif_var;
    QVBoxLayout* layout_var = new QVBoxLayout; layout_Vertical["layout_var"] = layout_var;
    QVBoxLayout* layout_Variable = new QVBoxLayout; layout_Vertical["layout_Variable"] = layout_Variable;

    //création des couches verticales pour la vue secondaire program
    QVBoxLayout* layoutV_add_prog = new QVBoxLayout; layout_Vertical["layoutV_add_prog"] = layoutV_add_prog;
    QVBoxLayout* layoutV_modif_prog = new QVBoxLayout; layout_Vertical["layoutV_modif_prog"] = layoutV_modif_prog;
    QVBoxLayout* layout_prog = new QVBoxLayout; layout_Vertical["layout_prog"] = layout_prog;
    QVBoxLayout* layout_Program = new QVBoxLayout; layout_Vertical["layout_Program"] = layout_Program;

    /*-------------------------------------------------------------------------------------------------------------------------------------------*/
    /*--Création des Widget pour la vue secondaire Variable--------------------------------------------------------------------------------------*/
    QLineEdit* add_name_var = new QLineEdit; Line_Edit["add_name_var"] = add_name_var; Line_Edit["add_name_var"]->setFixedSize(200,20);
    QLineEdit* add_edit_var = new QLineEdit; Line_Edit["add_edit_var"] = add_edit_var; Line_Edit["add_edit_var"]->setFixedSize(200,20);
    QLabel* name_var_add = new QLabel("Entrer name of variable"); label["name_var_add"] = name_var_add;
    QLabel* value_var_add = new QLabel("Entrer value of variable"); label["value_var_add"] = value_var_add;
    QComboBox* list_add_var = new QComboBox; list["list_add_var"] = list_add_var; list["list_add_var"]->setFixedSize(130,35);
    list["list_add_var"]->addItem("Position N°1"); list["list_add_var"]->addItem("Position N°3"); list["list_add_var"]->addItem("Position N°3");
    list["list_add_var"]->addItem("Position N°4"); list["list_add_var"]->addItem("Position N°5"); list["list_add_var"]->addItem("Position N°6");

    QLineEdit* modif_name_var = new QLineEdit; Line_Edit["modif_name_var"] = modif_name_var; Line_Edit["modif_name_var"]->setFixedSize(200,20);
    QLineEdit* modif_edit_var = new QLineEdit; Line_Edit["modif_edit_var"] = modif_edit_var; Line_Edit["modif_edit_var"]->setFixedSize(200,20);
    QLabel* name_var_modif = new QLabel("Entrer name of variable"); label["name_var_modif"] = name_var_modif;
    QLabel* value_var_modif= new QLabel("Entrer value of variable"); label["value_var_modif"] = value_var_modif;
    QComboBox* list_modif_var = new QComboBox; list["list_modif_var"] = list_modif_var; list["list_modif_var"]->setFixedSize(130,35);

    QComboBox* list_delete_var = new QComboBox; list["list_delete_var"] = list_delete_var; list["list_delete_var"]->setFixedSize(130,35);


    /*-------------------------------------------------------------------------------------------------------------------------------------------*/
    /*--Création des Widget pour la vue secondaire program---------------------------------------------------------------------------------------*/
    QLineEdit* add_name_prog = new QLineEdit; Line_Edit["add_name_prog"] = add_name_prog; Line_Edit["add_name_prog"]->setFixedSize(200,20);
    QLineEdit* add_edit_prog = new QLineEdit; Line_Edit["add_edit_prog"] = add_edit_prog; Line_Edit["add_edit_prog"]->setFixedSize(200,20);
    QLabel* name_prog_add = new QLabel("Entrer name of program"); label["name_prog_add"] = name_prog_add; label["name_prog_add"]->setFixedSize(200,20);
    QLabel* value_prog_add = new QLabel("Entrer value of program"); label["value_prog_add"] = value_prog_add; label["value_prog_add"]->setFixedSize(200,20);
    QComboBox* list_add_prog = new QComboBox; list["list_add_prog"] = list_add_prog; list["list_add_prog"]->setFixedSize(130,35);
    list["list_add_prog"]->addItem("Position N°1"); list["list_add_prog"]->addItem("Position N°3"); list["list_add_prog"]->addItem("Position N°3");
    list["list_add_prog"]->addItem("Position N°4"); list["list_add_prog"]->addItem("Position N°5"); list["list_add_prog"]->addItem("Position N°6");

    QLineEdit* modif_name_prog = new QLineEdit; Line_Edit["modif_name_prog"] = modif_name_prog; Line_Edit["modif_name_prog"]->setFixedSize(200,20);
    QLineEdit* modif_edit_prog = new QLineEdit; Line_Edit["modif_edit_prog"] = modif_edit_prog; Line_Edit["modif_edit_prog"]->setFixedSize(200,20);
    QLabel* name_prog_modif = new QLabel("Entrer name of program"); label["name_prog_modif"] = name_prog_modif;
    QLabel* value_prog_modif= new QLabel("Entrer value of program"); label["value_prog_modif"] = value_prog_modif;
    QComboBox* list_modif_prog = new QComboBox; list["list_modif_prog"] = list_modif_prog; list["list_modif_prog"]->setFixedSize(130,35);

    QComboBox* list_delete_prog = new QComboBox; list["list_delete_prog"] = list_delete_prog; list["list_delete_prog"]->setFixedSize(130,35);



    /*-------------------------------------------------------------------------------------------------------------------------------------------*/
    /*--Création des 4 onglets au niveau des claviers--------------------------------------------------------------------------------------------*/
    tab = new QTabWidget(this);
    QWidget* Principal = new QWidget;secondary_view["Principal"] = Principal;
    QWidget* Variable = new QWidget; secondary_view["Variable"] = Variable;
    QWidget* Program = new QWidget;  secondary_view["Program"] = Program;
    QWidget* Settings = new QWidget; secondary_view["Settings"] = Settings;
}


void QCompUT::Initialisation(){
    //Titre de l'application
    setWindowTitle("Comp'UT");

/*------Initialisation de la couche stack et EditLine----------------------------------------------------------------------------------------*/
/**/    layout_Vertical["layout_stack"]->addWidget(message);
/**/    layout_Vertical["layout_stack"]->addWidget(viewStack);
/**/    layout_Vertical["layout_stack"]->addWidget(commande);
/**/    message->setReadOnly(true);
/**/    message->setText("Bonjour et bienvenu dans CompUT");
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/*------Initialisation de secon clavier------------------------------------------------------------------------------------------------------*/
/**/    layout_Horizontal["layout123"]->addWidget(buttons_First_keyboard["b1"]); layout_Horizontal["layout123"]->addWidget(buttons_First_keyboard["b2"]); layout_Horizontal["layout123"]->addWidget(buttons_First_keyboard["b3"]);
/**/    layout_Horizontal["layout456"]->addWidget(buttons_First_keyboard["b4"]); layout_Horizontal["layout456"]->addWidget(buttons_First_keyboard["b5"]); layout_Horizontal["layout456"]->addWidget(buttons_First_keyboard["b6"]);
/**/    layout_Horizontal["layout789"]->addWidget(buttons_First_keyboard["b7"]); layout_Horizontal["layout789"]->addWidget(buttons_First_keyboard["b8"]); layout_Horizontal["layout789"]->addWidget(buttons_First_keyboard["b9"]);
/**/    layout_Horizontal["layout0"]->addWidget(buttons_First_keyboard["b0"]);
/**/
/**/    layout_Vertical["layout_number"]->addLayout(layout_Horizontal["layout123"]);
/**/    layout_Vertical["layout_number"]->addLayout(layout_Horizontal["layout456"]);
/**/    layout_Vertical["layout_number"]->addLayout(layout_Horizontal["layout789"]);
/**/    layout_Vertical["layout_number"]->addLayout(layout_Horizontal["layout0"]);
/**/
/**/    layout_Vertical["layout_operator"]->addWidget(buttons_First_keyboard["plus"]);
/**/    layout_Vertical["layout_operator"]->addWidget(buttons_First_keyboard["moins"]);
/**/    layout_Vertical["layout_operator"]->addWidget(buttons_First_keyboard["mult"]);
/**/    layout_Vertical["layout_operator"]->addWidget(buttons_First_keyboard["div"]);
/**/    layout_Vertical["layout_operator"]->addWidget(buttons_First_keyboard["equal"]);
/**/
/**/    layout_Horizontal["layout_key_one"]->addLayout(layout_Vertical["layout_number"]); layout_Horizontal["layout_key_one"]->addLayout(layout_Vertical["layout_operator"]);
/**/
/**/    layout_Vertical["layout_keyboard_one"]->addWidget(buttons_First_keyboard["reduce_keyboard_one"]); layout_Vertical["layout_keyboard_one"]->addWidget(buttons_First_keyboard["open_keyboard_one"]);
/**/    layout_Vertical["layout_keyboard_one"]->addLayout(layout_Horizontal["layout_key_one"]);
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/*------Initialisation du second clavier------------------------------------------------------------------------------------------------------*/
/**/    layout_Vertical["layout_keyboard_var"]->addWidget(buttons_Second_keyboard["var1"]); layout_Vertical["layout_keyboard_var"]->addWidget(buttons_Second_keyboard["var2"]);
    layout_Vertical["layout_keyboard_var"]->addWidget(buttons_Second_keyboard["var3"]); layout_Vertical["layout_keyboard_var"]->addWidget(buttons_Second_keyboard["var4"]);
    layout_Vertical["layout_keyboard_var"]->addWidget(buttons_Second_keyboard["var5"]); layout_Vertical["layout_keyboard_var"]->addWidget(buttons_Second_keyboard["var6"]);

    layout_Vertical["layout_keyboard_prog"]->addWidget(buttons_Second_keyboard["prog1"]); layout_Vertical["layout_keyboard_prog"]->addWidget(buttons_Second_keyboard["prog2"]);
    layout_Vertical["layout_keyboard_prog"]->addWidget(buttons_Second_keyboard["prog3"]); layout_Vertical["layout_keyboard_prog"]->addWidget(buttons_Second_keyboard["prog4"]);
    layout_Vertical["layout_keyboard_prog"]->addWidget(buttons_Second_keyboard["prog5"]); layout_Vertical["layout_keyboard_prog"]->addWidget(buttons_Second_keyboard["prog6"]);

    layout_Horizontal["layout_var_prog"]->addLayout(layout_Vertical["layout_keyboard_var"]); layout_Horizontal["layout_var_prog"]->addLayout(layout_Vertical["layout_keyboard_prog"]);
/**/
/**/    layout_Vertical["layout_keyboard_two"]->addWidget(buttons_Second_keyboard["reduce_keyboard_two"]); layout_Vertical["layout_keyboard_two"]->addWidget(buttons_Second_keyboard["open_keyboard_two"]);
/**/    layout_Vertical["layout_keyboard_two"]->addLayout(layout_Horizontal["layout_var_prog"]);
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
    //Layout de la vu secondaire Variable
    layout_Vertical["layoutV_add_var"]->addWidget(label["name_var_add"]);layout_Vertical["layoutV_add_var"]->addWidget(Line_Edit["add_name_var"]);
    layout_Vertical["layoutV_add_var"]->addWidget(label["value_var_add"]);layout_Vertical["layoutV_add_var"]->addWidget(Line_Edit["add_edit_var"]);

    layout_Horizontal["layoutH_add_var"]->addLayout(layout_Vertical["layoutV_add_var"]);
    layout_Horizontal["layoutH_add_var"]->addWidget(list["list_add_var"]);
    layout_Horizontal["layoutH_add_var"]->addWidget(buttons_secondary_view["new_var"]);

    layout_Vertical["layoutV_modif_var"]->addWidget(label["name_var_modif"]);layout_Vertical["layoutV_modif_var"]->addWidget(Line_Edit["modif_name_var"]);
    layout_Vertical["layoutV_modif_var"]->addWidget(label["value_var_modif"]);layout_Vertical["layoutV_modif_var"]->addWidget(Line_Edit["modif_edit_var"]);

    layout_Horizontal["layoutH_modif_var"]->addLayout(layout_Vertical["layoutV_modif_var"]);
    layout_Horizontal["layoutH_modif_var"]->addWidget(list["list_modif_var"]);
    layout_Horizontal["layoutH_modif_var"]->addWidget(buttons_secondary_view["modif_var"]);

    layout_Horizontal["layoutH_del_var"]->addWidget(list["list_delete_var"]);
    layout_Horizontal["layoutH_del_var"]->addWidget(buttons_secondary_view["delete_var"]);

    layout_Vertical["layout_var"]->addLayout(layout_Horizontal["layoutH_add_var"]);
    layout_Vertical["layout_var"]->addLayout(layout_Horizontal["layoutH_modif_var"]);
    layout_Vertical["layout_var"]->addLayout(layout_Horizontal["layoutH_del_var"]);

    //Layout de la vu secondaire Program
    layout_Vertical["layoutV_add_prog"]->addWidget(label["name_prog_add"]);layout_Vertical["layoutV_add_prog"]->addWidget(Line_Edit["add_name_prog"]);
    layout_Vertical["layoutV_add_prog"]->addWidget(label["value_prog_add"]);layout_Vertical["layoutV_add_prog"]->addWidget(Line_Edit["add_edit_prog"]);

    layout_Horizontal["layoutH_add_prog"]->addLayout(layout_Vertical["layoutV_add_prog"]);
    layout_Horizontal["layoutH_add_prog"]->addWidget(list["list_add_prog"]);
    layout_Horizontal["layoutH_add_prog"]->addWidget(buttons_secondary_view["new_prog"]);

    layout_Vertical["layoutV_modif_prog"]->addWidget(label["name_prog_modif"]);layout_Vertical["layoutV_modif_prog"]->addWidget(Line_Edit["modif_name_prog"]);
    layout_Vertical["layoutV_modif_prog"]->addWidget(label["value_prog_modif"]);layout_Vertical["layoutV_modif_prog"]->addWidget(Line_Edit["modif_edit_prog"]);

    layout_Horizontal["layoutH_modif_prog"]->addLayout(layout_Vertical["layoutV_modif_prog"]);
    layout_Horizontal["layoutH_modif_prog"]->addWidget(list["list_modif_prog"]);
    layout_Horizontal["layoutH_modif_prog"]->addWidget(buttons_secondary_view["modif_prog"]);

    layout_Horizontal["layoutH_del_prog"]->addWidget(list["list_delete_prog"]);
    layout_Horizontal["layoutH_del_prog"]->addWidget(buttons_secondary_view["delete_prog"]);

    layout_Vertical["layout_prog"]->addLayout(layout_Horizontal["layoutH_add_prog"]);
    layout_Vertical["layout_prog"]->addLayout(layout_Horizontal["layoutH_modif_prog"]);
    layout_Vertical["layout_prog"]->addLayout(layout_Horizontal["layoutH_del_prog"]);






    //layout_Vertical["layout_Variable"]->addWidget(buttons_secondary_view["new_var"]); layout_Vertical["layout_Variable"]->addWidget(buttons_secondary_view["delete_var"]);

    //Initialisation de la couche avec les 2 claviers
    layout_Horizontal["layout_keyboard_one_two"]->addLayout(layout_Vertical["layout_keyboard_one"]); layout_Horizontal["layout_keyboard_one_two"]->addLayout(layout_Vertical["layout_keyboard_two"]);

    //Initialisation des 4 onglets, dont 3 sont secondaires
    secondary_view["Principal"]->setLayout(layout_Horizontal["layout_keyboard_one_two"]); tab->addTab(secondary_view["Principal"], "Keyboard");
    secondary_view["Variable"]->setLayout(layout_Vertical["layout_var"]); tab->addTab(secondary_view["Variable"], "Variable");
    secondary_view["Program"]->setLayout(layout_Vertical["layout_prog"]); tab->addTab(secondary_view["Program"], "Program");
    /*Settings->setLayout(NULL);*/ tab->addTab(secondary_view["Settings"], "Settings");

    //Initialisation de l'affichage totale de l'application
    layout_Horizontal["layout_display_and_keyboard"]->addLayout(layout_Vertical["layout_stack"]); layout_Horizontal["layout_display_and_keyboard"]->addWidget(tab);

    setLayout(layout_Horizontal["layout_display_and_keyboard"]);

    //Boutons non visible à l'initialisation, boutons qui vont servire à déplier les claviers 1 et 2 s'il sont cachés
    buttons_First_keyboard["open_keyboard_one"]->setVisible(false);
    buttons_Second_keyboard["open_keyboard_two"]->setVisible(false);

    //Permet aux objets de ces layouts de se placer le plus en haut, utile pour ne pas changer l'affichage de l'application quand on reduit/réouvre les claviers
    layout_Vertical["layout_keyboard_one"]->setAlignment(Qt::AlignTop);
    layout_Vertical["layout_keyboard_two"]->setAlignment(Qt::AlignTop);
    layout_Horizontal["layoutH_add_var"]->setAlignment(Qt::AlignTop);

    //Taille fixé, non modifiable
    setFixedSize(900,350);

    //Focus a un composant
    commande->setFocus(Qt::OtherFocusReason);
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


void QCompUT::slotReduce1(){
    buttons_First_keyboard["reduce_keyboard_one"]->hide();
    buttons_First_keyboard["open_keyboard_one"]->show();
    buttons_First_keyboard["b1"]->hide();
    buttons_First_keyboard["b2"]->hide();
    buttons_First_keyboard["b3"]->hide();
    buttons_First_keyboard["b4"]->hide();
    buttons_First_keyboard["b5"]->hide();
    buttons_First_keyboard["b6"]->hide();
    buttons_First_keyboard["b7"]->hide();
    buttons_First_keyboard["b8"]->hide();
    buttons_First_keyboard["b9"]->hide();
    buttons_First_keyboard["b0"]->hide();
    buttons_First_keyboard["plus"]->hide();
    buttons_First_keyboard["moins"]->hide();
    buttons_First_keyboard["mult"]->hide();
    buttons_First_keyboard["div"]->hide();
    buttons_First_keyboard["equal"]->hide();
}

void QCompUT::slotOpen1(){
    buttons_First_keyboard["reduce_keyboard_one"]->show();
    buttons_First_keyboard["open_keyboard_one"]->hide();
    buttons_First_keyboard["b1"]->show();
    buttons_First_keyboard["b2"]->show();
    buttons_First_keyboard["b3"]->show();
    buttons_First_keyboard["b4"]->show();
    buttons_First_keyboard["b5"]->show();
    buttons_First_keyboard["b6"]->show();
    buttons_First_keyboard["b7"]->show();
    buttons_First_keyboard["b8"]->show();
    buttons_First_keyboard["b9"]->show();
    buttons_First_keyboard["b0"]->show();
    buttons_First_keyboard["plus"]->show();
    buttons_First_keyboard["moins"]->show();
    buttons_First_keyboard["mult"]->show();
    buttons_First_keyboard["div"]->show();
    buttons_First_keyboard["equal"]->show();
}

void QCompUT::slotReduce2(){
    buttons_Second_keyboard["reduce_keyboard_two"]->hide();
    buttons_Second_keyboard["open_keyboard_two"]->show();
    buttons_Second_keyboard["var1"]->hide();
    buttons_Second_keyboard["var2"]->hide();
    buttons_Second_keyboard["var3"]->hide();
    buttons_Second_keyboard["var4"]->hide();
    buttons_Second_keyboard["var5"]->hide();
    buttons_Second_keyboard["var6"]->hide();
    buttons_Second_keyboard["prog1"]->hide();
    buttons_Second_keyboard["prog2"]->hide();
    buttons_Second_keyboard["prog3"]->hide();
    buttons_Second_keyboard["prog4"]->hide();
    buttons_Second_keyboard["prog5"]->hide();
    buttons_Second_keyboard["prog6"]->hide();

}

void QCompUT::slotOpen2(){
    buttons_Second_keyboard["reduce_keyboard_two"]->show();
    buttons_Second_keyboard["open_keyboard_two"]->hide();
    buttons_Second_keyboard["var1"]->show();
    buttons_Second_keyboard["var2"]->show();
    buttons_Second_keyboard["var3"]->show();
    buttons_Second_keyboard["var4"]->show();
    buttons_Second_keyboard["var5"]->show();
    buttons_Second_keyboard["var6"]->show();
    buttons_Second_keyboard["prog1"]->show();
    buttons_Second_keyboard["prog2"]->show();
    buttons_Second_keyboard["prog3"]->show();
    buttons_Second_keyboard["prog4"]->show();
    buttons_Second_keyboard["prog5"]->show();
    buttons_Second_keyboard["prog6"]->show();
}



void QCompUT::slotNewVariable(){
     //Pour eviter d'avoir de créer un objet sans non ni valeur
    if (Line_Edit["add_name_var"]->text().isEmpty()) return;
    if (Line_Edit["add_edit_var"]->text().isEmpty()) return;

    QString name = Line_Edit["add_name_var"]->text();
    QString edit = Line_Edit["add_edit_var"]->text();
    buttons_Second_keyboard["var1"]->setText(name);

    list["list_modif_var"]->addItem(name); list["list_delete_var"]->addItem(name);

    Line_Edit["add_name_var"]->setText(""); Line_Edit["add_edit_var"]->setText("");

}
void QCompUT::slotModifVariable(){
    if (list["list_modif_var"]->currentText() == NULL) return;

}

void QCompUT::slotDeleteVariable(){
    if (list["list_delete_var"]->currentText() == NULL) return;

    list["list_modif_var"]->removeItem(list["list_delete_var"]->currentIndex());
    list["list_delete_var"]->removeItem(list["list_delete_var"]->currentIndex());
}








void QCompUT::slotNewProg(){
    //Pour eviter d'avoir de créer un objet sans non ni valeur
    if (Line_Edit["add_name_prog"]->text().isEmpty()) return;
    if (Line_Edit["add_edit_prog"]->text().isEmpty()) return;

   QString name = Line_Edit["add_name_prog"]->text();
   QString edit = Line_Edit["add_edit_prog"]->text();
   buttons_Second_keyboard["prog1"]->setText(name);

   list["list_modif_prog"]->addItem(name);
   list["list_delete_prog"]->addItem(name);

   Line_Edit["add_name_prog"]->setText(""); Line_Edit["add_edit_prog"]->setText("");
}

void QCompUT::slotModifProg(){
    if (list["list_modif_prog"]->currentText() == NULL) return;
}

void QCompUT::slotDeleteProg(){
    if (list["list_delete_prog"]->currentText() == NULL) return;

    list["list_modif_prog"]->removeItem(list["list_delete_prog"]->currentIndex());
    list["list_delete_prog"]->removeItem(list["list_delete_prog"]->currentIndex());
}



