#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <vector>

namespace Ui
{
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    void setAxisStart_stop(int x_start, int x_stop, int y_stop);
    std::vector<int> getAxisStart_stop();

private slots:
    void on_btnOk_pressed();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
