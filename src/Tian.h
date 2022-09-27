#pragma once
#include "ui_Tian.h"
#include "dialog.h"

#include <QMainWindow>
#include <QtCharts>
QT_CHARTS_USE_NAMESPACE
#include <vector>
#include <QGroupBox>
#include <QList>
#include <algorithm>

class Tian : public QMainWindow
{
    Q_OBJECT

private:
    QGridLayout *m_mainLayout = nullptr;
    QWidget *m_mainWidget = nullptr;
    QChartView *m_chartView = nullptr;
    QChart *m_chart = nullptr;
    QValueAxis *axisX = nullptr;
    QValueAxis *axisY = nullptr;

    Dialog *dialog = nullptr;

private:
    std::vector<QGroupBox *> group_box;
    QList<QLineSeries *> m_series;
    QList<QScatterSeries *> m_point;
    std::vector<QString> m_series_name;
    std::vector<std::vector<qreal>> value;

    int maxX = 0;
    int maxY = 0;

private:
    void iniChart();
    void addSeries();
    void addScaSeries();
    void addAxis();

public:
    Tian(QWidget *parent = nullptr);
    ~Tian();

private slots:
    void on_pushButton_clicked();

    void on_btnOK_clicked();

    void on_radioButton_clicked(bool checked);

    void on_radioButton_2_clicked(bool checked);

    void on_btnReset_clicked();

private:
    Ui_Tian *ui;
};
