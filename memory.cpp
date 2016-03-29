#include "memory.h"
#include "ui_memory.h"
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>

Memory::Memory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Memory)
{
    ui->setupUi(this);
    addMemSpace(0, 5);
    addMemSpace(10, 16);
}

Memory::~Memory()
{
    delete ui;
}

void Memory::addMemSpace(int pDirection, int pValue){
    QString dir = QString::number(pDirection, 16);
    dir = QString::fromStdString("0x") + (QString::fromStdString("00000")).fill('0', 5-dir.length()) + dir;

    QString val = QString::fromStdString("0x") + QString::number(pValue, 16);

    QLineEdit *valSpace = new QLineEdit();
    valSpace->setText(val);
    valSpace->setAlignment(Qt::AlignCenter);

    QLabel *dirLabel = new QLabel();
    dirLabel->setText(dir);
    dirLabel->setMinimumSize(75, 0);
    dirLabel->setAlignment(Qt::AlignLeft);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(dirLabel);
    layout->addWidget(valSpace);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    QWidget *wid = new QWidget();
    wid->setLayout(layout);

    ui->tableScrollArea->layout()->addWidget(wid);
}

void Memory::on_pushButton_clicked()
{
    this->close();
}
