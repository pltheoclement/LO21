#include "operator.h"
#include "ui_operator.h"

Operator::Operator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Operator)
{
    ui->setupUi(this);
}

Operator::~Operator()
{
    delete ui;
}

