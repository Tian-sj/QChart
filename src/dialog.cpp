#include "dialog.h"
#include "ui_dialog.h"
#include "QMessageBox"

Dialog::Dialog(QWidget *parent) : QDialog(parent),
                                  ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setAxisStart_stop(int x_start, int x_stop, int y_stop)
{
    ui->x_start->setValue(x_start);
    ui->x_stop->setValue(x_stop);
    ui->y_stop->setValue(y_stop);
}

std::vector<int> Dialog::getAxisStart_stop()
{
    std::vector<int> v;
    v.push_back(ui->x_start->value());
    v.push_back(ui->x_stop->value());
    v.push_back(ui->y_stop->value());
    return v;
}

void Dialog::on_btnOk_pressed()
{
    if (ui->x_start->value() <= 3000)
    {
        if (ui->x_start->value() % 100 != 0)
        {
            QMessageBox::warning(this, "警告", "x坐标起始位置必须填写100得倍数!");
            return;
        }
        if (ui->x_stop->value() <= 3000)
        {
            if (ui->x_stop->value() % 100 != 0)
            {
                QMessageBox::warning(this, "警告", "x坐标终点位置必须填写100得倍数!");
                return;
            }
        }
        else
        {
            if (ui->x_stop->value() % 200 != 0)
            {
                QMessageBox::warning(this, "警告", "x坐标终点位置大于3000必须填写200得倍数!");
                return;
            }
        }
    }
    else
    {
        if (ui->x_start->value() % 200 != 0)
        {
            QMessageBox::warning(this, "警告", "x坐标起始大于3000位置必须填写200得倍数!");
            return;
        }
        if (ui->x_stop->value() % 200 != 0)
        {
            QMessageBox::warning(this, "警告", "x坐标终点大于3000位置必须填写200得倍数!");
            return;
        }
    }
    if (ui->y_stop->value() <= 500)
    {
        if (ui->y_stop->value() % 100 != 0)
        {
            QMessageBox::warning(this, "警告", "y坐标终点位置必须填写100得倍数!");
            return;
        }
    }
    else if (ui->y_stop->value() <= 2000)
    {
        if (ui->y_stop->value() % 200 != 0)
        {
            QMessageBox::warning(this, "警告", "y坐标终点大于500小于2000位置必须填写200得倍数!");
            return;
        }
    }
    else
    {
        if (ui->y_stop->value() % 400 != 0)
        {
            QMessageBox::warning(this, "警告", "y坐标终点大于2000位置必须填写400得倍数!");
            return;
        }
    }
}
