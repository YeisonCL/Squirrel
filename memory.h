#ifndef MEMORY_H
#define MEMORY_H

#include <QDialog>

namespace Ui {
class Memory;
}

class Memory : public QDialog
{
    Q_OBJECT

public:
    explicit Memory(QWidget *parent = 0);
    void addMemSpace(int pDirection, int pValue);
    ~Memory();

private slots:
    void on_startEdit_returnPressed();

    void on_finnishEdit_returnPressed();

    void on_startEdit_selectionChanged();

    void on_finnishEdit_selectionChanged();

    void slotMemChange(QString pText);

private:
    Ui::Memory *ui;
    void loadMemory(int pStart, int pFinnish);
    void setMemory(int pAddress, int pData);
    int _lastStart;
    int _lastFinnish;
};

#endif // MEMORY_H
