#ifndef SQUIRRELMAIN_H
#define SQUIRRELMAIN_H

#include <QTextLine>
#include <QMainWindow>
#include "LogicInterface.h"

namespace Ui {
class SquirrelMain;
}

class SquirrelMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit SquirrelMain(QWidget *parent = 0);

    ~SquirrelMain();

signals:
    void executeSimulation(char *pPath);
    void executeCompilation(char *pPath);


public slots:
    void updateTextRegisters(int pRegister0, int pRegister1, int pRegister2, int pRegister3, int pRegister4, int pRegister5, int pRegister6, int pRegister7,
                             int pRegister8, int pRegister9, int pRegister10, int pRegister11, int pRegister12, int pRegister13, int pRegister14, int pRegister15);
    void updateTextConsole(QString *pText);
    void updateTextFlags(int pCarry, int pNegative, int pZero, int pOverflow);


private slots:
    void on_codeEdit_textChanged();

    void on_codeEdit_cursorPositionChanged();

    void on_memButton_clicked();

    void on_aboutButton_clicked();

    void on_newButton_clicked();

    void on_openButton_clicked();

    void on_saveButton_clicked();

    void on_compileButton_clicked();

    void on_simulateButton_clicked();

private:
    QString filePath;
    Ui::SquirrelMain *ui;
    int currentTextLine(const QTextCursor &cursor);    
    LogicInterface* _logicInterface;
};

#endif // SQUIRRELMAIN_H