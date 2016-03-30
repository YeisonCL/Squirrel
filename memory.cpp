#include "memory.h"
#include "ui_memory.h"
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <iostream>
#include <QObject>

using namespace std;

extern "C" {
    #include "Facade.h"
}

Memory::Memory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Memory)
{
    ui->setupUi(this);
    _lastStart = 1024;
    _lastFinnish = 2048;
    ui->finnishEdit->setValidator( new QIntValidator(0, 2044, this) );
    ui->startEdit->setValidator( new QIntValidator(0, 2040, this) );
    loadMemory(1024, 2048);
}

Memory::~Memory()
{
    delete ui;
}

void Memory::loadMemory(int pStart, int pFinnish){
    QLayoutItem *item;
    while((item = ui->tableScrollArea->layout()->takeAt(0))) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }

    int *mem = getMemory();
    int iInstruction = pStart/4;
    while(iInstruction<(pFinnish+4)/4){
       addMemSpace(iInstruction*4, *(mem+iInstruction));
        iInstruction++;
    }
}

void Memory::setMemory(int pAddress, int pData){
    int *mem = getMemory();
    *(mem+pAddress/4) = pData;
}

void Memory::addMemSpace(int pDirection, int pValue){
    QString dir = QString::number(pDirection, 16);
    dir = QString::fromStdString("0x") + (QString::fromStdString("00000")).fill('0', 5-dir.length()) + dir;

    QString val = QString::fromStdString("0x") + QString::number((unsigned int)pValue, 16).toUpper();

    QLineEdit *valSpace = new QLineEdit();
    valSpace->setText(val);
    valSpace->setAlignment(Qt::AlignCenter);

    QRegExp re("[+|-]?0[x|X][a-fA-F0-9]+");
    QRegExpValidator *validator = new QRegExpValidator(re, this);
    valSpace->setValidator(validator);


    QLabel *dirLabel = new QLabel();
    dirLabel->setObjectName("dir");
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
    QObject::connect(valSpace, SIGNAL(textEdited(QString)), this, SLOT(slotMemChange(QString)));
    ui->tableScrollArea->layout()->addWidget(wid);
}

void Memory::on_startEdit_returnPressed()
{
    int fpos = ui->finnishEdit->text().toInt();
    int spos = ui->startEdit->text().toInt();
    if (fpos <= spos){
        ui->startEdit->setText(QString::number(_lastStart));
        ui->finnishEdit->setText(QString::number(_lastFinnish));
    } else {
        _lastFinnish = fpos;
        _lastStart = spos;
        loadMemory(spos, fpos);
    }
}

void Memory::slotMemChange(QString pText){
    QLineEdit *lineEdit = (QLineEdit *)QObject::sender();
    QString sdir = lineEdit->parent()->findChild<QLabel *>("dir")->text();
    int dir = sdir.toInt(0, 16);
    int val = pText.toInt(0, 16);
    setMemory(dir, val);
}

void Memory::on_finnishEdit_returnPressed()
{
    int fpos = ui->finnishEdit->text().toInt();
    int spos = ui->startEdit->text().toInt();
    if (fpos <= spos){
        ui->startEdit->setText(QString::number(_lastStart));
        ui->finnishEdit->setText(QString::number(_lastFinnish));
    } else {
        _lastFinnish = fpos;
        _lastStart = spos;
        loadMemory(spos, fpos);
    }
}

void Memory::on_startEdit_selectionChanged()
{

}

void Memory::on_finnishEdit_selectionChanged()
{

}
