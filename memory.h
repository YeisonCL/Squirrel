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
    void on_pushButton_clicked();

private:
    Ui::Memory *ui;
};

#endif // MEMORY_H
