#include "../include/qCompUT.h"

QCompUT::QCompUT(QWidget* father) : QWidget(father){
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*--Création du Spinbox pour le vue secondaire Setting----------------------------------------------------------------------------------------*/
/**/    Nbr_Line_Stack = new QSpinBox;
/**/    Nbr_Line_Stack->setRange(0,1000); Nbr_Line_Stack->setSingleStep(1); Nbr_Line_Stack->setValue(Nbr_Line); Nbr_Line_Stack->setFixedSize(160,20);
/**/    QTableWidget* viewStack = new QTableWidget(Nbr_Line,1); table["viewStack"] = viewStack;
/**/    viewStack->setMaximumSize(300,250);
/**/    QLineEdit* message   = new QLineEdit; Line_Edit["message"] = message;
/**/    QLineEdit* commande  = new QLineEdit; Line_Edit["commande"] = commande;
/*      Nous avons choisis de commencer cette partie du programme par la création et l'initialisation d'un QSpinBox avec la valeur par défaut Nbr_Line
 *          dans le .h. Cette initialisation est necessaire car nous réutilisons les données du QSpinBox afin de modifier le nombre de visualisation
 *          de ligne dans le stack */

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

    connect(commande,SIGNAL(returnPressed()),this,SLOT(getNextCommande()));

    connect(buttons_secondary_view["new_var"],SIGNAL(clicked()),this,SLOT(slotNewVariable()));
    connect(buttons_secondary_view["modif_var"],SIGNAL(clicked()),this,SLOT(slotModifVariable()));
    connect(buttons_secondary_view["delete_var"],SIGNAL(clicked()),this,SLOT(slotDeleteVariable()));

    connect(buttons_secondary_view["new_prog"],SIGNAL(clicked()),this,SLOT(slotNewProg()));
    connect(buttons_secondary_view["modif_prog"],SIGNAL(clicked()),this,SLOT(slotModifProg()));
    connect(buttons_secondary_view["delete_prog"],SIGNAL(clicked()),this,SLOT(slotDeleteProg()));

    connect(Nbr_Line_Stack,SIGNAL(valueChanged(int)),this,SLOT(slot_Nbr_Line_view_Stack()));

    connect(buttons_settings["save"],SIGNAL(clicked()),this,SLOT(slotSave()));
    connect(buttons_settings["load"],SIGNAL(clicked()),this,SLOT(slotLoad()));
}


void QCompUT::Initialisation_Stack(){
    //viewStack->setStyleSheet("color: white");
    table["viewStack"]->horizontalHeader()->setVisible(false);
    //Ajuster la taille des colone
    table["viewStack"]->horizontalHeader()->setStretchLastSection(true);
    //viewStack->setFixedHeight(Nbr_Line*viewStack->rowHeight(0)+2);
    //Vérouiller l'écriture au clavier dans le tableau
    table["viewStack"]->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //Affichage inverse indice tableau
    QStringList labels;

    for(size_t i=Nbr_Line; i>0; i--){
        QString str = QString::number(i);
        str+=" :";
        labels << str;
        table["viewStack"]->setItem(i-1,0,new QTableWidgetItem(""));
    }
    table["viewStack"]->setVerticalHeaderLabels(labels);
}

/*----------------------------------------------------------------------------------------------------------------------------*/
/*--Création des différents objet QT------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------------*/
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
    QHBoxLayout* Layout_SaveLoad = new QHBoxLayout; layout_Horizontal["Layout_SaveLoad"] = Layout_SaveLoad;

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

    QVBoxLayout* Layout_Save = new QVBoxLayout; layout_Vertical["Layout_Save"] = Layout_Save;
    QVBoxLayout* Layout_Load = new QVBoxLayout; layout_Vertical["Layout_Load"] = Layout_Load;
    QVBoxLayout* Layout_Setting = new QVBoxLayout; layout_Vertical["Layout_Setting"] = Layout_Setting;

    /*-------------------------------------------------------------------------------------------------------------------------------------------*/
    /*--Création des Widget pour la vue secondaire Variable--------------------------------------------------------------------------------------*/
    //Pour créer une nouvelle variable
    QLineEdit* add_name_var = new QLineEdit; Line_Edit["add_name_var"] = add_name_var; Line_Edit["add_name_var"]->setFixedSize(200,20);
    QLineEdit* add_edit_var = new QLineEdit; Line_Edit["add_edit_var"] = add_edit_var; Line_Edit["add_edit_var"]->setFixedSize(200,20);
    QLabel* name_var_add = new QLabel("Entrer name of variable"); label["name_var_add"] = name_var_add;
    QLabel* value_var_add = new QLabel("Entrer value of variable"); label["value_var_add"] = value_var_add;
    QComboBox* list_add_var = new QComboBox; list["list_add_var"] = list_add_var; list["list_add_var"]->setFixedSize(130,35);
    //Pour modifier une variable
    QLineEdit* modif_name_var = new QLineEdit; Line_Edit["modif_name_var"] = modif_name_var; Line_Edit["modif_name_var"]->setFixedSize(200,20);
    QLineEdit* modif_edit_var = new QLineEdit; Line_Edit["modif_edit_var"] = modif_edit_var; Line_Edit["modif_edit_var"]->setFixedSize(200,20);
    QLabel* name_var_modif = new QLabel("Entrer name of variable"); label["name_var_modif"] = name_var_modif;
    QLabel* value_var_modif= new QLabel("Entrer value of variable"); label["value_var_modif"] = value_var_modif;
    QComboBox* list_modif_var = new QComboBox; list["list_modif_var"] = list_modif_var; list["list_modif_var"]->setFixedSize(130,35);
    //Pour supprimer une variable
    QComboBox* list_delete_var = new QComboBox; list["list_delete_var"] = list_delete_var; list["list_delete_var"]->setFixedSize(130,35);

    /*-------------------------------------------------------------------------------------------------------------------------------------------*/
    /*--Création des Widget pour la vue secondaire program---------------------------------------------------------------------------------------*/
    //Pour créer un nouveau programme
    QLineEdit* add_name_prog = new QLineEdit; Line_Edit["add_name_prog"] = add_name_prog; Line_Edit["add_name_prog"]->setFixedSize(200,20);
    QLineEdit* add_edit_prog = new QLineEdit; Line_Edit["add_edit_prog"] = add_edit_prog; Line_Edit["add_edit_prog"]->setFixedSize(200,20);
    QLabel* name_prog_add = new QLabel("Entrer name of program"); label["name_prog_add"] = name_prog_add; label["name_prog_add"]->setFixedSize(200,20);
    QLabel* value_prog_add = new QLabel("Entrer value of program"); label["value_prog_add"] = value_prog_add; label["value_prog_add"]->setFixedSize(200,20);
    QComboBox* list_add_prog = new QComboBox; list["list_add_prog"] = list_add_prog; list["list_add_prog"]->setFixedSize(130,35);
    //Pour modifier un programme
    QLineEdit* modif_name_prog = new QLineEdit; Line_Edit["modif_name_prog"] = modif_name_prog; Line_Edit["modif_name_prog"]->setFixedSize(200,20);
    QLineEdit* modif_edit_prog = new QLineEdit; Line_Edit["modif_edit_prog"] = modif_edit_prog; Line_Edit["modif_edit_prog"]->setFixedSize(200,20);
    QLabel* name_prog_modif = new QLabel("Entrer name of program"); label["name_prog_modif"] = name_prog_modif;
    QLabel* value_prog_modif= new QLabel("Entrer value of program"); label["value_prog_modif"] = value_prog_modif;
    QComboBox* list_modif_prog = new QComboBox; list["list_modif_prog"] = list_modif_prog; list["list_modif_prog"]->setFixedSize(130,35);
    //Pour supprimer un programme
    QComboBox* list_delete_prog = new QComboBox; list["list_delete_prog"] = list_delete_prog; list["list_delete_prog"]->setFixedSize(130,35);

    /*--------------------------------------------------------------------------------------------------------------------------------------------*/
    /*--Création des 2 tables pour voir les nouvelles variable et programmes----------------------------------------------------------------------*/
    QTableWidget* table_var = new QTableWidget(0, 1, this); table["table_var"] = table_var;
    table["table_var"]->setMaximumSize(150,250);
    table["table_var"]->setColumnWidth(0,118);
    table["table_var"]->horizontalHeader()->hide();
    table["table_var"]->verticalHeader()->hide();

    QTableWidget* table_prog = new QTableWidget(0, 1, this); table["table_prog"] = table_prog;
    table["table_prog"]->setMaximumSize(150,250);
    table["table_prog"]->setColumnWidth(0,118);
    table["table_prog"]->horizontalHeader()->hide();
    table["table_prog"]->verticalHeader()->hide();

    /*--------------------------------------------------------------------------------------------------------------------------------------------*/
    /*--Création des labels et boutons pour le vue secondaire Setting----------------------------------------------------------------------------------------*/
    QLabel* label_settings = new QLabel("Number of line in the stack"); label["label_settings"] = label_settings; label["label_settings"]->setFixedSize(160,20);
    QLabel* label_save = new QLabel("Backup a current status"); label["label_save"] = label_save; label["label_save"]->setFixedSize(160,20);
    QLabel* label_load = new QLabel("Recovering a saved state"); label["label_load"] = label_load; label["label_load"]->setFixedSize(160,20);

    QPushButton* save = new QPushButton("Save"); buttons_settings["save"] = save; buttons_settings["save"]->setFixedSize(130,30);
    QPushButton* load = new QPushButton("Load"); buttons_settings["load"] = load; buttons_settings["load"]->setFixedSize(130,30);

    /*--------------------------------------------------------------------------------------------------------------------------------------------*/
    /*--Création des 4 onglets au niveau des claviers---------------------------------------------------------------------------------------------*/
    tab = new QTabWidget(this); tab->setFixedSize(550,300);
    QWidget* Principal = new QWidget;secondary_view["Principal"] = Principal;
    QWidget* Variable = new QWidget; secondary_view["Variable"] = Variable;
    QWidget* Program = new QWidget;  secondary_view["Program"] = Program;
    QWidget* Settings = new QWidget; secondary_view["Settings"] = Settings;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
/*--Initialisation des différents objet QT------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------------*/
void QCompUT::Initialisation(){
    //Titre de l'application
    setWindowTitle("Comp'UT");

    //Instance pour la création des opérateurs
    creationOperators();

/*------Initialisation de la couche stack et EditLine----------------------------------------------------------------------------------------*/
/**/    layout_Vertical["layout_stack"]->addWidget(Line_Edit["message"]);
/**/    layout_Vertical["layout_stack"]->addWidget(table["viewStack"]);
/**/    layout_Vertical["layout_stack"]->addWidget(Line_Edit["commande"]);
/**/    Line_Edit["message"]->setReadOnly(true);
/**/    //Line_Edit["message"]->setText("Bonjour et bienvenu dans CompUT");
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
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*------Initialisation du second clavier------------------------------------------------------------------------------------------------------*/
/**/    layout_Horizontal["layout_var_prog"]->addWidget(table["table_var"]); layout_Horizontal["layout_var_prog"]->addWidget(table["table_prog"]);
/**/
/**/    layout_Vertical["layout_keyboard_two"]->addWidget(buttons_Second_keyboard["reduce_keyboard_two"]); layout_Vertical["layout_keyboard_two"]->addWidget(buttons_Second_keyboard["open_keyboard_two"]);
/**/    layout_Vertical["layout_keyboard_two"]->addLayout(layout_Horizontal["layout_var_prog"]);
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/**/    //Layout de la vue secondaire Variable
/**/    layout_Vertical["layoutV_add_var"]->addWidget(label["name_var_add"]);layout_Vertical["layoutV_add_var"]->addWidget(Line_Edit["add_name_var"]);
/**/    layout_Vertical["layoutV_add_var"]->addWidget(label["value_var_add"]);layout_Vertical["layoutV_add_var"]->addWidget(Line_Edit["add_edit_var"]);
/**/
/**/    layout_Horizontal["layoutH_add_var"]->addLayout(layout_Vertical["layoutV_add_var"]);
/**/    layout_Horizontal["layoutH_add_var"]->addWidget(buttons_secondary_view["new_var"]);
/**/    layout_Horizontal["layoutH_add_var"]->setAlignment(Qt::AlignLeft);
/**/
/**/    layout_Vertical["layoutV_modif_var"]->addWidget(label["name_var_modif"]);layout_Vertical["layoutV_modif_var"]->addWidget(Line_Edit["modif_name_var"]);
/**/    layout_Vertical["layoutV_modif_var"]->addWidget(label["value_var_modif"]);layout_Vertical["layoutV_modif_var"]->addWidget(Line_Edit["modif_edit_var"]);
/**/
/**/    layout_Horizontal["layoutH_modif_var"]->addLayout(layout_Vertical["layoutV_modif_var"]);
/**/    layout_Horizontal["layoutH_modif_var"]->addWidget(list["list_modif_var"]);
/**/    layout_Horizontal["layoutH_modif_var"]->addWidget(buttons_secondary_view["modif_var"]);
/**/    layout_Horizontal["layoutH_modif_var"]->setAlignment(Qt::AlignLeft);
/**/
/**/    layout_Horizontal["layoutH_del_var"]->addWidget(list["list_delete_var"]);
/**/    layout_Horizontal["layoutH_del_var"]->addWidget(buttons_secondary_view["delete_var"]);
/**/    layout_Horizontal["layoutH_del_var"]->setAlignment(Qt::AlignLeft);
/**/
/**/    layout_Vertical["layout_var"]->addLayout(layout_Horizontal["layoutH_add_var"]);
/**/    layout_Vertical["layout_var"]->addLayout(layout_Horizontal["layoutH_modif_var"]);
/**/    layout_Vertical["layout_var"]->addLayout(layout_Horizontal["layoutH_del_var"]);
/**/
/**/    //Layout de la vue secondaire Program
/**/    layout_Vertical["layoutV_add_prog"]->addWidget(label["name_prog_add"]);layout_Vertical["layoutV_add_prog"]->addWidget(Line_Edit["add_name_prog"]);
/**/    layout_Vertical["layoutV_add_prog"]->addWidget(label["value_prog_add"]);layout_Vertical["layoutV_add_prog"]->addWidget(Line_Edit["add_edit_prog"]);
/**/
/**/    layout_Horizontal["layoutH_add_prog"]->addLayout(layout_Vertical["layoutV_add_prog"]);
/**/    layout_Horizontal["layoutH_add_prog"]->addWidget(buttons_secondary_view["new_prog"]);
/**/    layout_Horizontal["layoutH_add_prog"]->setAlignment(Qt::AlignLeft);
/**/
/**/    layout_Vertical["layoutV_modif_prog"]->addWidget(label["name_prog_modif"]);layout_Vertical["layoutV_modif_prog"]->addWidget(Line_Edit["modif_name_prog"]);
/**/    layout_Vertical["layoutV_modif_prog"]->addWidget(label["value_prog_modif"]);layout_Vertical["layoutV_modif_prog"]->addWidget(Line_Edit["modif_edit_prog"]);
/**/
/**/    layout_Horizontal["layoutH_modif_prog"]->addLayout(layout_Vertical["layoutV_modif_prog"]);
/**/    layout_Horizontal["layoutH_modif_prog"]->addWidget(list["list_modif_prog"]);
/**/    layout_Horizontal["layoutH_modif_prog"]->addWidget(buttons_secondary_view["modif_prog"]);
/**/    layout_Horizontal["layoutH_modif_prog"]->setAlignment(Qt::AlignLeft);
/**/
/**/    layout_Horizontal["layoutH_del_prog"]->addWidget(list["list_delete_prog"]);
/**/    layout_Horizontal["layoutH_del_prog"]->addWidget(buttons_secondary_view["delete_prog"]);
/**/    layout_Horizontal["layoutH_del_prog"]->setAlignment(Qt::AlignLeft);
/**/
/**/    layout_Vertical["layout_prog"]->addLayout(layout_Horizontal["layoutH_add_prog"]);
/**/    layout_Vertical["layout_prog"]->addLayout(layout_Horizontal["layoutH_modif_prog"]);
/**/    layout_Vertical["layout_prog"]->addLayout(layout_Horizontal["layoutH_del_prog"]);
/**/
/**/    //Layout de la vue secondaire Settings
/**/    layout_Vertical["Layout_Save"]->addWidget(label["label_save"]); layout_Vertical["Layout_Save"]->addWidget(buttons_settings["save"]);
/**/    layout_Vertical["Layout_Load"]->addWidget(label["label_load"]); layout_Vertical["Layout_Load"]->addWidget(buttons_settings["load"]);
/**/    layout_Horizontal["Layout_SaveLoad"]->addLayout(layout_Vertical["Layout_Save"]); layout_Horizontal["Layout_SaveLoad"]->addLayout(layout_Vertical["Layout_Load"]);
/**/    layout_Vertical["Layout_Setting"]->addWidget(label["label_settings"]);
/**/    layout_Vertical["Layout_Setting"]->addWidget(Nbr_Line_Stack);
/**/    layout_Vertical["Layout_Setting"]->addLayout(layout_Horizontal["Layout_SaveLoad"]);
/**/    layout_Vertical["Layout_Setting"]->setAlignment(Qt::AlignTop);       
/**/
/**/    //Initialisation de la couche avec les 2 claviers
/**/    layout_Horizontal["layout_keyboard_one_two"]->addLayout(layout_Vertical["layout_keyboard_one"]); layout_Horizontal["layout_keyboard_one_two"]->addLayout(layout_Vertical["layout_keyboard_two"]);
/**/
/**/    //Initialisation des 4 onglets, dont 3 sont secondaires
/**/    secondary_view["Principal"]->setLayout(layout_Horizontal["layout_keyboard_one_two"]); tab->addTab(secondary_view["Principal"], "Keyboard");
/**/    secondary_view["Variable"]->setLayout(layout_Vertical["layout_var"]); tab->addTab(secondary_view["Variable"], "Variable");
/**/    secondary_view["Program"]->setLayout(layout_Vertical["layout_prog"]); tab->addTab(secondary_view["Program"], "Program");
/**/    secondary_view["Settings"]->setLayout(layout_Vertical["Layout_Setting"]); tab->addTab(secondary_view["Settings"], "Settings");
/**/
/**/    //Initialisation de l'affichage totale de l'application
/**/    layout_Horizontal["layout_display_and_keyboard"]->addLayout(layout_Vertical["layout_stack"]); layout_Horizontal["layout_display_and_keyboard"]->addWidget(tab);
/**/    setLayout(layout_Horizontal["layout_display_and_keyboard"]);
/**/
/**/    //Boutons non visible à l'initialisation, boutons qui vont servire à déplier les claviers 1 et 2 s'il sont cachés
/**/    buttons_First_keyboard["open_keyboard_one"]->setVisible(false);
/**/    buttons_Second_keyboard["open_keyboard_two"]->setVisible(false);
/**/
/**/    //Permet aux objets de ces layouts de se placer le plus en haut, utile pour ne pas changer l'affichage de l'application quand on reduit/réouvre les claviers
/**/    layout_Vertical["layout_keyboard_one"]->setAlignment(Qt::AlignTop);
/**/    layout_Vertical["layout_keyboard_two"]->setAlignment(Qt::AlignTop);
/**/    layout_Horizontal["layout_keyboard_one_two"]->setAlignment(Qt::AlignLeft);
/**/
/**/    //Taille fixé, non modifiable
/**/    setFixedSize(900,350);
/**/
/**/    //Focus a un composant
/**/    Line_Edit["commande"]->setFocus(Qt::OtherFocusReason);
}

/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*------IMPLEMENTATION DES DIFFERENTS SLOT----------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*------Rafraichissement de la vue du stack---------------------------------------------------------------------------------------------------*/
void QCompUT::refresh_stack(){
    Line_Edit["message"]->setText(QString::fromStdString(Computer::getInstance().getMessage()));
    for(size_t i=0; i<Nbr_Line; i++)
        table["viewStack"]->item(i,0)->setText("");

   size_t nb=0;
    for(auto it=Stack::getInstance().iterator(); it!=Stack::getInstance().end() && nb<Nbr_Line; ++it){
        table["viewStack"]->item(Nbr_Line-nb-1,0)->setText(QString::fromStdString((*it)->toString()));
        nb++;
    }
}

/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*------Permet de passer une information dans le stack----------------------------------------------------------------------------------------*/
void QCompUT::getNextCommande(){
    QString c=Line_Edit["commande"]->text();
    Computer::getInstance().evalLine(c.toStdString());
    refresh_stack();
    Update_Var_Prog();
    Line_Edit["commande"]->clear();
    text ="";
}

/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*------Slot pour les boutons du premier------------------------------------------------------------------------------------------------------*/
/**/    void QCompUT::slot1(){ text +="1"; Line_Edit["commande"]->setText(text); Line_Edit["commande"]->setFocus(Qt::OtherFocusReason);}
/**/    void QCompUT::slot2(){ text +="2"; Line_Edit["commande"]->setText(text); Line_Edit["commande"]->setFocus(Qt::OtherFocusReason);}
/**/    void QCompUT::slot3(){ text +="3"; Line_Edit["commande"]->setText(text); Line_Edit["commande"]->setFocus(Qt::OtherFocusReason);}
/**/    void QCompUT::slot4(){ text +="4"; Line_Edit["commande"]->setText(text); Line_Edit["commande"]->setFocus(Qt::OtherFocusReason);}
/**/    void QCompUT::slot5(){ text +="5"; Line_Edit["commande"]->setText(text); Line_Edit["commande"]->setFocus(Qt::OtherFocusReason);}
/**/    void QCompUT::slot6(){ text +="6"; Line_Edit["commande"]->setText(text); Line_Edit["commande"]->setFocus(Qt::OtherFocusReason);}
/**/    void QCompUT::slot7(){ text +="7"; Line_Edit["commande"]->setText(text); Line_Edit["commande"]->setFocus(Qt::OtherFocusReason);}
/**/    void QCompUT::slot8(){ text +="8"; Line_Edit["commande"]->setText(text); Line_Edit["commande"]->setFocus(Qt::OtherFocusReason);}
/**/    void QCompUT::slot9(){ text +="9"; Line_Edit["commande"]->setText(text); Line_Edit["commande"]->setFocus(Qt::OtherFocusReason);}
/**/    void QCompUT::slot0(){ text +="0"; Line_Edit["commande"]->setText(text); Line_Edit["commande"]->setFocus(Qt::OtherFocusReason);}
/**/    void QCompUT::slotPlus() { text +="+"; Line_Edit["commande"]->setText(text); Line_Edit["commande"]->setFocus(Qt::OtherFocusReason);}
/**/    void QCompUT::slotMoins(){ text +="-"; Line_Edit["commande"]->setText(text); Line_Edit["commande"]->setFocus(Qt::OtherFocusReason);}
/**/    void QCompUT::slotMult() { text +="*"; Line_Edit["commande"]->setText(text); Line_Edit["commande"]->setFocus(Qt::OtherFocusReason);}
/**/    void QCompUT::slotDiv()  { text +="/"; Line_Edit["commande"]->setText(text); Line_Edit["commande"]->setFocus(Qt::OtherFocusReason);}
/**/    void QCompUT::slotEqual() { QCompUT::getNextCommande(); }

/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*------Slot pour réduire/ouvrir les 2 claviers-----------------------------------------------------------------------------------------------*/
/***/   void QCompUT::slotReduce1(){
/* */       buttons_First_keyboard["reduce_keyboard_one"]->hide();
/* */       buttons_First_keyboard["open_keyboard_one"]->show();
/* */       buttons_First_keyboard["b1"]->hide();
/* */       buttons_First_keyboard["b2"]->hide();
/* */       buttons_First_keyboard["b3"]->hide();
/* */       buttons_First_keyboard["b4"]->hide();
/* */       buttons_First_keyboard["b5"]->hide();
/* */       buttons_First_keyboard["b6"]->hide();
/* */       buttons_First_keyboard["b7"]->hide();
/* */       buttons_First_keyboard["b8"]->hide();
/* */       buttons_First_keyboard["b9"]->hide();
/* */       buttons_First_keyboard["b0"]->hide();
/* */       buttons_First_keyboard["plus"]->hide();
/* */       buttons_First_keyboard["moins"]->hide();
/* */       buttons_First_keyboard["mult"]->hide();
/* */       buttons_First_keyboard["div"]->hide();
/* */       buttons_First_keyboard["equal"]->hide();
/***/    }
/*-------------------------------------------------------------*/
/***/   void QCompUT::slotOpen1(){
/* */     buttons_First_keyboard["reduce_keyboard_one"]->show();
/* */     buttons_First_keyboard["open_keyboard_one"]->hide();
/* */     buttons_First_keyboard["b1"]->show();
/* */     buttons_First_keyboard["b2"]->show();
/* */     buttons_First_keyboard["b3"]->show();
/* */     buttons_First_keyboard["b4"]->show();
/* */     buttons_First_keyboard["b5"]->show();
/* */     buttons_First_keyboard["b6"]->show();
/* */     buttons_First_keyboard["b7"]->show();
/* */     buttons_First_keyboard["b8"]->show();
/* */     buttons_First_keyboard["b9"]->show();
/* */     buttons_First_keyboard["b0"]->show();
/* */     buttons_First_keyboard["plus"]->show();
/* */     buttons_First_keyboard["moins"]->show();
/* */     buttons_First_keyboard["mult"]->show();
/* */     buttons_First_keyboard["div"]->show();
/* */     buttons_First_keyboard["equal"]->show();
/***/   }
/*-------------------------------------------------------------*/
/***/   void QCompUT::slotReduce2(){
/* */     buttons_Second_keyboard["reduce_keyboard_two"]->hide();
/* */     buttons_Second_keyboard["open_keyboard_two"]->show();
/* */     table["table_var"]->hide();
/* */     table["table_prog"]->hide();
/***/   }
/*-------------------------------------------------------------*/
/***/   void QCompUT::slotOpen2(){
/* */     buttons_Second_keyboard["reduce_keyboard_two"]->show();
/* */     buttons_Second_keyboard["open_keyboard_two"]->hide();
/* */     table["table_var"]->show();
/* */     table["table_prog"]->show();
/***/   }


/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*------IMPLEMENTATION DES DIFFERENTS SLOT----------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*------Slot pour créer une nouvelle variable-------------------------------------------------------------------------------------------------*/
/****/  void QCompUT::slotNewVariable(){
/*  */      //Permet de vérifier que les champs necessaires soient bien incrémentés pour réaliser la création d'une nouvelle variable
/*  */      if (Line_Edit["add_name_var"]->text().isEmpty()) return;
/*  */      if (Line_Edit["add_edit_var"]->text().isEmpty()) return;
/*  */
/*  */      //Variable pour récupérer le nom et valeur pour la création
/*  */      QString name_var = Line_Edit["add_name_var"]->text();
/*  */      QString value_var = Line_Edit["add_edit_var"]->text();
/*  */
/*  */      if (Literal::isLiteral(name_var.toStdString()) == latom){
/*  */         LiteralType lt = Literal::isLiteral(value_var.toStdString());
/*  */          if (lt != lprogram && lt != latom && lt != lerror) {
/*  */              Computer::getInstance().storeVariable(name_var.toStdString(),*Literal::makeLiteral(value_var.toStdString(), lt));
/*  */              Line_Edit["add_name_var"]->setText(""); Line_Edit["add_edit_var"]->setText("");
/*  */          }
/*  */          else Line_Edit["message"]->setText("Invalid variable");
/*  */       }
/*  */       else Line_Edit["message"]->setText("Invalid variable name");
/*  */
/*  */      //Remet le focus sur le nom d'une prochaine variable à créer
/*  */      Line_Edit["add_name_var"]->setFocus(Qt::OtherFocusReason);
/*  */      Update_Var_Prog();
/****/  }

/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*------Slot pour modifier le nom et la valeur d'une variable---------------------------------------------------------------------------------*/
/****/  void QCompUT::slotModifVariable(){
/*  */      //Permet de vérifier que les champs necessaires soient bien incrémentés pour réaliser la modification par la suite
/*  */      if (Line_Edit["modif_name_var"]->text().isEmpty()) return;
/*  */      if (Line_Edit["modif_edit_var"]->text().isEmpty()) return;
/*  */      if (list["list_modif_var"]->currentText().isEmpty()) return;
/*  */
/*  */      //Variables pour récupérer le nom existant, le nouveau nom et la nouvelle valeur
/*  */      QString new_name_var = Line_Edit["modif_name_var"]->text();
/*  */      QString new_value_var = Line_Edit["modif_edit_var"]->text();
/*  */      QString current_name_var = list["list_modif_var"]->currentText();
/*  */
/*  */      if (Literal::isLiteral(new_name_var.toStdString()) == latom){
/*  */         LiteralType lt = Literal::isLiteral(new_value_var.toStdString());
/*  */          if (lt != lprogram && lt != latom && lt != lerror) {
/*  */             Computer::getInstance().forgetVariable(current_name_var.toStdString());
/*  */             Computer::getInstance().storeVariable(new_name_var.toStdString(),*Literal::makeLiteral(new_value_var.toStdString(), lt));
/*  */             Line_Edit["modif_name_var"]->setText(""); Line_Edit["modif_edit_var"]->setText("");
/*  */          }
/*  */          else Line_Edit["message"]->setText("Invalid Variable");
/*  */       }
/*  */       else Line_Edit["message"]->setText("Invalid Variable name");
/*  */
/*  */      //Remet le focus sur le nom à modifier d'une prochaine variable
/*  */      Line_Edit["modif_name_var"]->setFocus(Qt::OtherFocusReason);
/*  */
/*  */      Update_Var_Prog();
/****/  }

/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*------Slot pour supprimer une variable------------------------------------------------------------------------------------------------------*/
/****/  void QCompUT::slotDeleteVariable(){
/*  */      if (list["list_delete_var"]->currentText().isEmpty()) return;
/*  */
/*  */      //Variable pour récupérer le nom existant
/*  */      QString current_name_var = list["list_delete_var"]->currentText();
/*  */
/*  */      //Envoi du nom courrant, pour la suppression au niveau du Computer
/*  */      Computer::getInstance().forgetVariable(current_name_var.toStdString());
/*  */
/*  */      Update_Var_Prog();
/****/  }


/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*------Slot pour créer un nouveau programme--------------------------------------------------------------------------------------------------*/
/****/  void QCompUT::slotNewProg(){
/*  */      //Permet de vérifier que les champs necessaires soient bien incrémentés pour réaliser la création du nouveau programme
/*  */      if (Line_Edit["add_name_prog"]->text().isEmpty()) return;
/*  */      if (Line_Edit["add_edit_prog"]->text().isEmpty()) return;
/*  */
/*  */      //Variable pour récupérer le nom et valeur pour la création
/*  */      QString name_prog = Line_Edit["add_name_prog"]->text();
/*  */      QString value_prog = Line_Edit["add_edit_prog"]->text();
/*  */
/*  */      //Ajout dand la liste de modification, puis suppression, puis remise à vide des champs pour entrer le nouveau nom et la nouvelle valeur à créer
/*  */
/*  */      //Envoi des informations vers le Computer
/*  */      if (Literal::isLiteral(name_prog.toStdString()) == latom){
/*  */         LiteralType lt = Literal::isLiteral(value_prog.toStdString());
/*  */          if (lt == lprogram) {
/*  */              Computer::getInstance().storeVariable(name_prog.toStdString(),*Literal::makeLiteral(value_prog.toStdString(), lt));
/*  */              Line_Edit["add_name_prog"]->setText(""); Line_Edit["add_edit_prog"]->setText("");
/*  */          }
/*  */          else Line_Edit["message"]->setText("Invalid program");
/*  */       }
/*  */       else Line_Edit["message"]->setText("Invalid program name");
/*  */
/*  */      //Remet le focus sur le nom d'un prochaine programme à créer
/*  */      Line_Edit["add_name_prog"]->setFocus(Qt::OtherFocusReason);
/*  */
/*  */      Update_Var_Prog();
/****/  }

/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*------Slot pour modifier le nom et la valeur d'un programme---------------------------------------------------------------------------------*/
/****/  void QCompUT::slotModifProg(){
/*  */      //Permet de vérifier que les champs necessaires soient bien incrémentés pour réaliser la modification par la suite
/*  */      if (Line_Edit["modif_name_prog"]->text().isEmpty()) return;
/*  */      if (Line_Edit["modif_edit_prog"]->text().isEmpty()) return;
/*  */      if (list["list_delete_prog"]->currentText().isEmpty()) return;
/*  */
/*  */      //Variables pour récupérer le nom existant, le nouveau nom et la nouvelle valeur
/*  */      QString new_name_prog = Line_Edit["modif_name_prog"]->text();
/*  */      QString new_value_prog = Line_Edit["modif_edit_prog"]->text();
/*  */      QString current_name_prog = list["list_modif_prog"]->currentText();
/*  */
/*  */      //Envoi du nom courrant, puis du nouveau nom et nouvelle valeur vers le Computer   
/*  */      if (Literal::isLiteral(new_name_prog.toStdString()) == latom){
/*  */         LiteralType lt = Literal::isLiteral(new_value_prog.toStdString());
/*  */          if (lt == lprogram) {
/*  */             Computer::getInstance().forgetVariable(current_name_prog.toStdString());
/*  */             Computer::getInstance().storeVariable(new_name_prog.toStdString(),*Literal::makeLiteral(new_value_prog.toStdString(), lt));
/*  */             Line_Edit["modif_name_prog"]->setText(""); Line_Edit["modif_edit_prog"]->setText("");
/*  */          }
/*  */          else Line_Edit["message"]->setText("Invalid program");
/*  */       }
/*  */       else Line_Edit["message"]->setText("Invalid program name");
/*  */
/*  */      //Remet le focus sur le nom à modifier d'un prochain programme
/*  */      Line_Edit["modif_name_prog"]->setFocus(Qt::OtherFocusReason);
/*  */
/*  */      Update_Var_Prog();
/****/  }

/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*------Slot pour supprimer un programme------------------------------------------------------------------------------------------------------*/
/****/  void QCompUT::slotDeleteProg(){
/*  */      //Permet de vérifier que les champs necessaires soient bien incrémentés pour réaliser la modification par la suite
/*  */      if (list["list_delete_prog"]->currentText().isEmpty()) return;
/*  */
/*  */      //Variable pour récupérer le nom existant
/*  */      QString current_name_prog = list["list_delete_prog"]->currentText();
/*  */
/*  */      //Envoi du nom courrant, pour la suppression au niveau du Computer
/*  */      Computer::getInstance().forgetVariable(current_name_prog.toStdString());
/*  */
/*  */      Update_Var_Prog();
/****/  }


//Slot qui permet de réstituer la valeur d'une variable créée précédemment
void QCompUT::slotVariable(){
    text = qobject_cast<QPushButton*>(sender())->text();
    string nom = Computer::getInstance().getVariable(text.toStdString());
    Line_Edit["commande"]->setText(QString::fromStdString(nom));

    //Remet le focus commande
    Line_Edit["commande"]->setFocus(Qt::OtherFocusReason);
}

//Slot qui permet de réstituer la valeur d'un programme créé précédemment
void QCompUT::slotProgram(){
    text = qobject_cast<QPushButton*>(sender())->text();
    string nom = Computer::getInstance().getVariable(text.toStdString());
    Line_Edit["commande"]->setText(QString::fromStdString(nom));

    //Remet le focus commande
    Line_Edit["commande"]->setFocus(Qt::OtherFocusReason);
}

//Slot permettant de modifier le nombre visuel de ligne dans le stack
void QCompUT::slot_Nbr_Line_view_Stack(){
    //viewStack->setRowCount(0);
    Nbr_Line = Nbr_Line_Stack->text().toInt();
    table["viewStack"]->setRowCount(Nbr_Line);
    table["viewStack"]->clear();
    Initialisation_Stack();
    refresh_stack();
}

//Slot pour sauvegarder l'état actuel
void QCompUT::slotSave(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save file"), "", tr("All Files (*)"));
    Computer::getInstance().saveToFile(fileName.toStdString());
}

//Slot pour restituer un précédent état sauvegardé
void QCompUT::slotLoad(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("All Files (*)"));
    Computer::getInstance().loadFromFile(fileName.toStdString());
    Update_Var_Prog();
    refresh_stack();
}


void QCompUT::Update_Var_Prog() {
    table["table_var"]->setRowCount(0);
    table["table_prog"]->setRowCount(0);
    list["list_modif_prog"]->clear();
    list["list_modif_var"]->clear();
    list["list_delete_prog"]->clear();
    list["list_delete_var"]->clear();

    for (string stdname : Computer::getInstance().getVariableNames()) {
        QString name = QString::fromStdString(stdname);
        //Création du bouton qui va apparaitre dans le second clavier cliquable
        QWidget *pWidget_vp = new QWidget();
        QPushButton *btn_vp = new QPushButton();
        btn_vp->setFixedSize(90, 30);
        //Connexion du nouveau bouton avec le signal

        //Alternative pour faire afficher un bouton dans un tableau
        btn_vp->setText(name);
        QHBoxLayout *pLayout_vp = new QHBoxLayout(pWidget_vp);
        pLayout_vp->addWidget(btn_vp);
        pLayout_vp->setAlignment(Qt::AlignCenter);
        pWidget_vp->setLayout(pLayout_vp);

        // Ajout dans les menus déroulants et connexion des signaux
        QString table_name;
        if (Computer::getInstance().getVariable(stdname)[0] == '[') {
            table_name = "table_prog";
            list["list_modif_prog"]->addItem(name); list["list_delete_prog"]->addItem(name);
            connect(btn_vp, SIGNAL(clicked()), this, SLOT(slotVariable()));
        } else {
            table_name = "table_var";
            list["list_modif_var"]->addItem(name); list["list_delete_var"]->addItem(name);
            connect(btn_vp, SIGNAL(clicked()), this, SLOT(slotProgram()));
        }

        //Alternative pour augmenter la taille de la table qui accueille les boutons
        size_t nbr_row = table[table_name]->rowCount();
        table[table_name]->insertRow(nbr_row);
        table[table_name]->setRowHeight(nbr_row, 45);
        table[table_name]->setCellWidget(nbr_row, 0, pWidget_vp);
        buttons_var[name] = btn_vp;
    }
}
