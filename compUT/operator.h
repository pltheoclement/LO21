#ifndef OPERATOR_H
#define OPERATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Operator; }
QT_END_NAMESPACE

class Operator : public QMainWindow
{
    Q_OBJECT

public:
    Operator(QWidget *parent = nullptr);
    ~Operator();

private:
    Ui::Operator *ui;
};
#endif // OPERATOR_H
