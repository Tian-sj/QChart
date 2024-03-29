#pragma once
#include <QMainWindow>
#include <QtCharts>
#include <vector>
#include <app/dialog.h>

namespace Ui {
class widget;
}

class widget : public QMainWindow
{
    Q_OBJECT

private:
    Dialog *dialog = nullptr;

    QChart *chart = nullptr;
    QLineSeries *series_1 = nullptr;
    QLineSeries *series_2 = nullptr;
    QLineSeries *series_3 = nullptr;
    QLineSeries *series_4 = nullptr;
    QLineSeries *series_5 = nullptr;
    QScatterSeries *scatterSeries_1 = nullptr;
    QScatterSeries *scatterSeries_2 = nullptr;
    QScatterSeries *scatterSeries_3 = nullptr;
    QScatterSeries *scatterSeries_4 = nullptr;
    QScatterSeries *scatterSeries_5 = nullptr;

    QValueAxis *axisX = nullptr;
    QValueAxis *axisY = nullptr;

private:
    std::vector<QGroupBox *> group_box;
    std::vector<QLineSeries *> series;
    std::vector<QPointF> vtPointF;
    std::vector<QPointF> vtSSPointF;
    std::vector<QScatterSeries *> scatterSeries;
    std::vector<int> vf;
    int maxX = 0;
    int maxY = 0;

public:
    widget(QWidget *parent = nullptr);
    ~widget();

private slots:
    void on_pushButton_clicked();

    void on_btnOK_clicked();

    void on_radioButton_clicked(bool checked);

    void on_radioButton_2_clicked(bool checked);

private:
    Ui::widget *ui;

    void createCharts();
    void iniSeries();
    void btn_first();
    void btn_second();
    void btn_third();
    void btn_fourth();
    void btn_fifth();
};
