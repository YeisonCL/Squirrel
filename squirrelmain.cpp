#include "squirrelmain.h"
#include "ui_squirrelmain.h"
#include "memory.h"
#include "about.h"
#include <string>
#include <iostream>
#include <QTextBlock>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QThread>

using namespace std;

extern "C"{
    #include "Facade.h"
}

using namespace std;

int _lines = 1;

SquirrelMain::SquirrelMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SquirrelMain)
{
    ui->setupUi(this);
    _logicInterface = new LogicInterface();

    QThread *thread = new QThread;
    _logicInterface->moveToThread(thread);

    QObject::connect(this, SIGNAL(executeCompilation(char*, char*)), _logicInterface, SLOT(compile(char*, char*)));
    QObject::connect(this, SIGNAL(executeSimulation(char*)), _logicInterface, SLOT(simulate(char*)));

    QObject::connect(_logicInterface, SIGNAL(signalPrint(QString*)), this, SLOT(updateTextConsole(QString*)));
    QObject::connect(_logicInterface, SIGNAL(signalRefreshRegs(int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int)),
                     this, SLOT(updateTextRegisters(int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int)));
    QObject::connect(_logicInterface, SIGNAL(signalRefreshFlags(int,int,int,int)), this, SLOT(updateTextFlags(int,int,int,int)));
    ui->consoleEdit->setReadOnly(true);
    thread->start();
}

SquirrelMain::~SquirrelMain()
{
    delete ui;
}

void SquirrelMain::on_codeEdit_textChanged()
{

}

void SquirrelMain::on_codeEdit_cursorPositionChanged()
{
    int y = currentTextLine(ui->codeEdit->textCursor());
    ui->lineLabel->setText(QString::fromStdString(std::to_string(y)));
}


int SquirrelMain::currentTextLine(const QTextCursor &cursor)
{
   QTextBlock block = cursor.block();
   int count = 1;
   while(block.position() != 0){
       count++;
       block = block.previous();
   }
   return count;
}

void SquirrelMain::on_memButton_clicked()
{
    Memory m;
    m.setModal(true);
    m.exec();
}

void SquirrelMain::on_aboutButton_clicked()
{
    About a;
    a.setModal(true);
    a.exec();
}

void SquirrelMain::updateTextConsole(QString *pText)
{
    ui->consoleEdit->append(*pText);
    free(pText);
}

void SquirrelMain::updateTextRegisters(int pRegister0, int pRegister1, int pRegister2, int pRegister3, int pRegister4, int pRegister5, int pRegister6, int pRegister7,
                                       int pRegister8, int pRegister9, int pRegister10, int pRegister11, int pRegister12, int pRegister13, int pRegister14, int pRegister15)
{   
    ui->reg0->setText(QString::number(pRegister0));
    ui->reg1->setText(QString::number(pRegister1));
    ui->reg2->setText(QString::number(pRegister2));
    ui->reg3->setText(QString::number(pRegister3));
    ui->reg4->setText(QString::number(pRegister4));
    ui->reg5->setText(QString::number(pRegister5));
    ui->reg6->setText(QString::number(pRegister6));
    ui->reg7->setText(QString::number(pRegister7));
    ui->reg8->setText(QString::number(pRegister8));
    ui->reg9->setText(QString::number(pRegister9));
    ui->reg10->setText(QString::number(pRegister10));
    ui->reg11->setText(QString::number(pRegister11));
    ui->reg12->setText(QString::number(pRegister12));
    ui->reg13->setText(QString::number(pRegister13));
    ui->reg14->setText(QString::number(pRegister14));
    ui->reg15->setText(QString::number(pRegister15));
}

void SquirrelMain::updateTextFlags(int pCarry, int pNegative, int pZero, int pOverflow)
{
    ui->cFlag->setText(QString::number(pCarry));
    ui->nFlag->setText(QString::number(pNegative));
    ui->zFlag->setText(QString::number(pZero));
    ui->vFlag->setText(QString::number(pOverflow));
}

void SquirrelMain::restartCodeSection()
{
    ui->codeEdit->setText("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"><html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">p, li { white-space: pre-wrap; }</style></head><body style=\" font-family:'Cantarell'; font-size:9pt; font-weight:400; font-style:normal;\" bgcolor=\"#000000\"><p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; line-height:17px;\"><br /></p></body></html>");
}

void SquirrelMain::on_newButton_clicked()
{
    restartCodeSection();
    ui->label_10->setText("new_file.armv4");
    filePath = "";
}

void SquirrelMain::on_openButton_clicked()
{
    QString oldFilePath = filePath;
    filePath = QFileDialog::getOpenFileName(this, tr("Open ARMv4 File"), "/root", tr("ARMv4 File (*.armv4)"));
    if(filePath != "")
    {
        QFile file(filePath);
        file.open(QIODevice::ReadOnly);
        QTextStream in(&file);
        in.setCodec("UTF-8");

        QString fileRead = in.readAll();
        ui->label_10->setText(file.fileName());
        file.close();
        restartCodeSection();
        ui->codeEdit->append(fileRead);
        originalText = fileRead;
    }
    else
    {
        filePath = oldFilePath;
    }
}

void SquirrelMain::on_saveButton_clicked()
{
    if(filePath == "")
    {
        filePath = QFileDialog::getSaveFileName(this, tr("Save ARMv4 File"), "/root/new_file.armv4", tr("ARMv4 File (*.armv4)"));
        if(filePath != "")
        {
            QFile file(filePath);
            if ( file.open(QIODevice::ReadWrite) )
            {
                originalText = ui->codeEdit->toPlainText();
                QTextStream saveFile(&file);
                saveFile << ui->codeEdit->toPlainText()<< endl;
            }
            file.resize(file.pos());
            file.close();
            QMessageBox::information(this, "GREAT", "File created succesfully.");
            ui->label_10->setText(filePath);
        }
    }
    else
    {
        QFile file(filePath);
        if ( file.open(QIODevice::ReadWrite) )
        {
            originalText = ui->codeEdit->toPlainText();
            QTextStream saveFile(&file);
            saveFile << ui->codeEdit->toPlainText()<< endl;
        }
        file.resize(file.pos());
        file.close();
        QMessageBox::information(this, "GREAT", "Saved succesfully.");
    }
}


void SquirrelMain::on_compileButton_clicked()
{
    if(filePath == "")
    {
        on_saveButton_clicked();
    }
    if(originalText != ui->codeEdit->toPlainText())
    {
        QMessageBox question;
        question.setIconPixmap(QPixmap(":/icons/icons/warning_icon.png"));
        question.setWindowTitle("Save");
        question.setText("There are unsaved changes. ¿Do you want to save them or compile the previous file?");
        QAbstractButton* saveButton = question.addButton(tr("Save"), QMessageBox::ActionRole);
        QAbstractButton* compileButton = question.addButton(tr("Compile"), QMessageBox::AcceptRole);
        QAbstractButton* cancelButton = question.addButton(tr("Cancel"), QMessageBox::NoRole);
        question.exec();
        if (question.clickedButton() == saveButton)
        {
            on_saveButton_clicked();
        }
        else if(question.clickedButton() == cancelButton)
        {
            return;
        }
        else if(question.clickedButton() == compileButton)
        {
            ;
        }
    }
    QString compiledPathQ = QFileDialog::getSaveFileName(this, tr("Save Compiled File"), "/root/out.txt", tr("Txt File (*.txt)"));
    if(compiledPathQ != "")
    {
        char *path= (char*)malloc(512*sizeof(char));
        char *compiledPath = (char*)malloc(1024*sizeof(char));
        strcpy(path, filePath.toStdString().c_str());
        strcpy(compiledPath, compiledPathQ.toStdString().c_str());
        emit executeCompilation(path, compiledPath);
    }
}

void SquirrelMain::on_simulateButton_clicked()
{
    if(filePath == "")
    {
        on_saveButton_clicked();
    }
    if(originalText != ui->codeEdit->toPlainText())
    {
        QMessageBox question;
        question.setIconPixmap(QPixmap(":/icons/icons/warning_icon.png"));
        question.setWindowTitle("Save");
        question.setText("There are unsaved changes. ¿Do you want to save them or run the previous file?");
        QAbstractButton* saveButton = question.addButton(tr("Save"), QMessageBox::ActionRole);
        QAbstractButton* runButton = question.addButton(tr("Run"), QMessageBox::AcceptRole);
        QAbstractButton* cancelButton = question.addButton(tr("Cancel"), QMessageBox::NoRole);
        question.exec();
        if (question.clickedButton() == saveButton)
        {
            on_saveButton_clicked();
        }
        else if(question.clickedButton() == cancelButton)
        {
            return;
        }
        else if(question.clickedButton() == runButton)
        {
            ;
        }
    }
    char *path= (char*)malloc(512*sizeof(char));
    strcpy(path, filePath.toStdString().c_str());
    emit executeSimulation(path);
}
