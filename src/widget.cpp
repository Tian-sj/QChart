#include "widget.h"

#include <algorithm>
#include <cmath>

widget::widget(QWidget *parent)
    : QMainWindow(parent), ui(new Ui_widget)
{
    ui->setupUi(this);

    ui->btnOK->setVisible(false);
    group_box.push_back(ui->groupBox_1);
    group_box.push_back(ui->groupBox_2);
    group_box.push_back(ui->groupBox_3);
    group_box.push_back(ui->groupBox_4);
    group_box.push_back(ui->groupBox_5);
    for (auto it = group_box.begin(); it != group_box.end(); ++it)
        (*it)->setVisible(false);

    createCharts();
}

widget::~widget()
{
    delete ui;
}

void widget::on_pushButton_clicked()
{
    ui->label_41->setVisible(false);
    ui->text->setVisible(false);
    ui->pushButton->setVisible(false);
    ui->btnOK->setVisible(true);

    for (auto it = group_box.begin(); it != group_box.begin() + ui->text->value(); ++it)
        (*it)->setVisible(true);
}

void widget::iniSeries()
{
    series_1 = new QLineSeries();
    series_1->setUseOpenGL(true);
    series_1->setName("范围一");

    series_2 = new QLineSeries();
    series_2->setUseOpenGL(true);
    series_2->setName("范围二");

    series_3 = new QLineSeries();
    series_3->setUseOpenGL(true);
    series_3->setName("范围三");

    series_4 = new QLineSeries();
    series_4->setUseOpenGL(true);
    series_4->setName("范围四");

    series_5 = new QLineSeries();
    series_5->setUseOpenGL(true);
    series_5->setName("范围五");

    axisX = new QValueAxis();
    axisY = new QValueAxis();
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
}

void widget::createCharts()
{
    chart = new QChart();
    chart->setTitle("直流电源输出特性");
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);

    iniSeries();
}

void widget::btn_first()
{
    qreal ua = round(ui->text_1_p->value() * 1000 / ui->text_1_Imax->value() * 10) / 10;

    maxX = std::max(maxX, ((int)ui->text_1_u2->value() / 100 + 1) * 100);
    maxY = std::max(maxY, ((int)ui->text_1_Imax->value() / 100 + 1) * 100);
    if (maxX <= 3000)
        maxX = std::max(maxX, ((int)ui->text_1_u2->value() / 100 + 1) * 100);
    else
        maxX = std::max(maxX, ((int)ui->text_1_u2->value() / 200 + 1) * 200);
    if (maxY <= 400)
        maxY = std::max(maxY, ((int)ui->text_1_Imax->value() / 100 + 1) * 100);
    else if (maxY <= 2000)
        maxY = std::max(maxY, ((int)ui->text_1_Imax->value() / 200 + 1) * 200);
    else
        maxY = std::max(maxY, ((int)ui->text_1_Imax->value() / 400 + 1) * 400);

    series_1->append(ui->text_1_u1->value(), -ui->text_1_Imax->value());
    series_1->append(ui->text_1_u1->value(), ui->text_1_Imax->value());
    series_1->append(ua, ui->text_1_Imax->value());
    for (int i = ua; i <= ui->text_1_u2->value(); i += 2)
    {
        series_1->append(i, round(ui->text_1_p->value() * 1000 / i * 10) / 10);
    }
    series_1->append(ui->text_1_u2->value(), -round(ui->text_1_p->value() * 1000 / ui->text_1_u2->value() * 10) / 10);
    for (int i = ui->text_1_u2->value(); i >= ua; i -= 2)
    {
        series_1->append(i, -round(ui->text_1_p->value() * 1000 / i * 10) / 10);
    }
    series_1->append(ui->text_1_u1->value(), -ui->text_1_Imax->value());

    scatterSeries_1 = new QScatterSeries();

    scatterSeries_1->setPointLabelsFormat("(@xPoint,@yPoint)");
    scatterSeries_1->setMarkerSize(1);
    scatterSeries_1->setPointLabelsVisible();

    scatterSeries_1->append(ui->text_1_u1->value(), -ui->text_1_Imax->value());
    scatterSeries_1->append(ui->text_1_u1->value(), ui->text_1_Imax->value());
    scatterSeries_1->append(ua, ui->text_1_Imax->value());
    scatterSeries_1->append(ui->text_1_u2->value(), round(ui->text_1_p->value() * 1000 / ui->text_1_u2->value() * 10) / 10);
    scatterSeries_1->append(ui->text_1_u2->value(), -round(ui->text_1_p->value() * 1000 / ui->text_1_u2->value() * 10) / 10);
    scatterSeries_1->append(ua, -ui->text_1_Imax->value());

    series.push_back(series_1);
    scatterSeries.push_back(scatterSeries_1);
}

void widget::btn_second()
{
    qreal ua = round(ui->text_2_p->value() * 1000 / ui->text_2_Imax->value() * 10) / 10;

    maxX = std::max(maxX, ((int)ui->text_2_u2->value() / 100 + 1) * 100);
    maxY = std::max(maxY, ((int)ui->text_2_Imax->value() / 100 + 1) * 100);
    if (maxX <= 3000)
        maxX = std::max(maxX, ((int)ui->text_2_u2->value() / 100 + 1) * 100);
    else
        maxX = std::max(maxX, ((int)ui->text_2_u2->value() / 200 + 1) * 200);
    if (maxY <= 400)
        maxY = std::max(maxY, ((int)ui->text_2_Imax->value() / 100 + 1) * 100);
    else if (maxY <= 2000)
        maxY = std::max(maxY, ((int)ui->text_2_Imax->value() / 200 + 1) * 200);
    else
        maxY = std::max(maxY, ((int)ui->text_2_Imax->value() / 400 + 1) * 400);

    series_2->append(ui->text_2_u1->value(), -ui->text_2_Imax->value());
    series_2->append(ui->text_2_u1->value(), ui->text_2_Imax->value());
    series_2->append(ua, ui->text_2_Imax->value());
    for (int i = ua; i <= ui->text_2_u2->value(); i += 2)
    {
        series_2->append(i, round(ui->text_2_p->value() * 1000 / i * 10) / 10);
    }
    series_2->append(ui->text_2_u2->value(), -round(ui->text_2_p->value() * 1000 / ui->text_2_u2->value() * 10) / 10);
    for (int i = ui->text_2_u2->value(); i >= ua; i -= 2)
    {
        series_2->append(i, -round(ui->text_2_p->value() * 1000 / i * 10) / 10);
    }
    series_2->append(ui->text_2_u1->value(), -ui->text_2_Imax->value());

    scatterSeries_2 = new QScatterSeries();

    scatterSeries_2->setPointLabelsFormat("(@xPoint,@yPoint)");
    scatterSeries_2->setMarkerSize(1);
    scatterSeries_2->setPointLabelsVisible();

    scatterSeries_2->append(ui->text_2_u1->value(), -ui->text_2_Imax->value());
    scatterSeries_2->append(ui->text_2_u1->value(), ui->text_2_Imax->value());
    scatterSeries_2->append(ua, ui->text_2_Imax->value());
    scatterSeries_2->append(ui->text_2_u2->value(), round(ui->text_2_p->value() * 1000 / ui->text_2_u2->value() * 10) / 10);
    scatterSeries_2->append(ui->text_2_u2->value(), -round(ui->text_2_p->value() * 1000 / ui->text_2_u2->value() * 10) / 10);
    scatterSeries_2->append(ua, -ui->text_2_Imax->value());

    series.push_back(series_2);
    scatterSeries.push_back(scatterSeries_2);
}

void widget::btn_third()
{
    qreal ua = round(ui->text_3_p->value() * 1000 / ui->text_3_Imax->value() * 10) / 10;

    maxX = std::max(maxX, ((int)ui->text_3_u2->value() / 100 + 1) * 100);
    maxY = std::max(maxY, ((int)ui->text_3_Imax->value() / 100 + 1) * 100);
    if (maxX <= 3000)
        maxX = std::max(maxX, ((int)ui->text_3_u2->value() / 100 + 1) * 100);
    else
        maxX = std::max(maxX, ((int)ui->text_3_u2->value() / 200 + 1) * 200);
    if (maxY <= 400)
        maxY = std::max(maxY, ((int)ui->text_3_Imax->value() / 100 + 1) * 100);
    else if (maxY <= 2000)
        maxY = std::max(maxY, ((int)ui->text_3_Imax->value() / 200 + 1) * 200);
    else
        maxY = std::max(maxY, ((int)ui->text_3_Imax->value() / 400 + 1) * 400);

    series_3->append(ui->text_3_u1->value(), -ui->text_3_Imax->value());
    series_3->append(ui->text_3_u1->value(), ui->text_3_Imax->value());
    series_3->append(ua, ui->text_3_Imax->value());
    for (int i = ua; i <= ui->text_3_u2->value(); i += 2)
    {
        series_3->append(i, round(ui->text_3_p->value() * 1000 / i * 10) / 10);
    }
    series_3->append(ui->text_3_u2->value(), -round(ui->text_3_p->value() * 1000 / ui->text_3_u2->value() * 10) / 10);
    for (int i = ui->text_3_u2->value(); i >= ua; i -= 2)
    {
        series_3->append(i, -round(ui->text_3_p->value() * 1000 / i * 10) / 10);
    }
    series_3->append(ui->text_3_u1->value(), -ui->text_3_Imax->value());

    scatterSeries_3 = new QScatterSeries();

    scatterSeries_3->setPointLabelsFormat("(@xPoint,@yPoint)");
    scatterSeries_3->setMarkerSize(1);
    scatterSeries_3->setPointLabelsVisible();

    scatterSeries_3->append(ui->text_3_u1->value(), -ui->text_3_Imax->value());
    scatterSeries_3->append(ui->text_3_u1->value(), ui->text_3_Imax->value());
    scatterSeries_3->append(ua, ui->text_3_Imax->value());
    scatterSeries_3->append(ui->text_3_u2->value(), round(ui->text_3_p->value() * 1000 / ui->text_3_u2->value() * 10) / 10);
    scatterSeries_3->append(ui->text_3_u2->value(), -round(ui->text_3_p->value() * 1000 / ui->text_3_u2->value() * 10) / 10);
    scatterSeries_3->append(ua, -ui->text_3_Imax->value());

    series.push_back(series_3);
    scatterSeries.push_back(scatterSeries_3);
}

void widget::btn_fourth()
{
    qreal ua = round(ui->text_4_p->value() * 1000 / ui->text_4_Imax->value() * 10) / 10;

    maxX = std::max(maxX, ((int)ui->text_4_u2->value() / 100 + 1) * 100);
    maxY = std::max(maxY, ((int)ui->text_4_Imax->value() / 100 + 1) * 100);
    if (maxX <= 3000)
        maxX = std::max(maxX, ((int)ui->text_4_u2->value() / 100 + 1) * 100);
    else
        maxX = std::max(maxX, ((int)ui->text_4_u2->value() / 200 + 1) * 200);
    if (maxY <= 400)
        maxY = std::max(maxY, ((int)ui->text_4_Imax->value() / 100 + 1) * 100);
    else if (maxY <= 2000)
        maxY = std::max(maxY, ((int)ui->text_4_Imax->value() / 200 + 1) * 200);
    else
        maxY = std::max(maxY, ((int)ui->text_4_Imax->value() / 400 + 1) * 400);

    series_4->append(ui->text_4_u1->value(), -ui->text_4_Imax->value());
    series_4->append(ui->text_4_u1->value(), ui->text_4_Imax->value());
    series_4->append(ua, ui->text_4_Imax->value());
    for (int i = ua; i <= ui->text_4_u2->value(); i += 2)
    {
        series_4->append(i, round(ui->text_4_p->value() * 1000 / i * 10) / 10);
    }
    series_4->append(ui->text_4_u2->value(), -round(ui->text_4_p->value() * 1000 / ui->text_4_u2->value() * 10) / 10);
    for (int i = ui->text_4_u2->value(); i >= ua; i -= 2)
    {
        series_4->append(i, -round(ui->text_4_p->value() * 1000 / i * 10) / 10);
    }
    series_4->append(ui->text_4_u1->value(), -ui->text_4_Imax->value());

    scatterSeries_4 = new QScatterSeries();

    scatterSeries_4->setPointLabelsFormat("(@xPoint,@yPoint)");
    scatterSeries_4->setMarkerSize(1);
    scatterSeries_4->setPointLabelsVisible();

    scatterSeries_4->append(ui->text_4_u1->value(), -ui->text_4_Imax->value());
    scatterSeries_4->append(ui->text_4_u1->value(), ui->text_4_Imax->value());
    scatterSeries_4->append(ua, ui->text_4_Imax->value());
    scatterSeries_4->append(ui->text_4_u2->value(), round(ui->text_4_p->value() * 1000 / ui->text_4_u2->value() * 10) / 10);
    scatterSeries_4->append(ui->text_4_u2->value(), -round(ui->text_4_p->value() * 1000 / ui->text_4_u2->value() * 10) / 10);
    scatterSeries_4->append(ua, -ui->text_4_Imax->value());

    series.push_back(series_4);
    scatterSeries.push_back(scatterSeries_4);
}

void widget::btn_fifth()
{
    qreal ua = round(ui->text_5_p->value() * 1000 / ui->text_5_Imax->value() * 10) / 10;

    maxX = std::max(maxX, ((int)ui->text_5_u2->value() / 100 + 1) * 100);
    maxY = std::max(maxY, ((int)ui->text_5_Imax->value() / 100 + 1) * 100);
    if (maxX <= 3000)
        maxX = std::max(maxX, ((int)ui->text_5_u2->value() / 100 + 1) * 100);
    else
        maxX = std::max(maxX, ((int)ui->text_5_u2->value() / 200 + 1) * 200);
    if (maxY <= 400)
        maxY = std::max(maxY, ((int)ui->text_5_Imax->value() / 100 + 1) * 100);
    else if (maxY <= 2000)
        maxY = std::max(maxY, ((int)ui->text_5_Imax->value() / 200 + 1) * 200);
    else
        maxY = std::max(maxY, ((int)ui->text_5_Imax->value() / 400 + 1) * 400);

    series_5->append(ui->text_5_u1->value(), -ui->text_5_Imax->value());
    series_5->append(ui->text_5_u1->value(), ui->text_5_Imax->value());
    series_5->append(ua, ui->text_5_Imax->value());
    for (int i = ua; i <= ui->text_5_u2->value(); i += 2)
    {
        series_5->append(i, round(ui->text_5_p->value() * 1000 / i * 10) / 10);
    }
    series_5->append(ui->text_5_u2->value(), -round(ui->text_5_p->value() * 1000 / ui->text_5_u2->value() * 10) / 10);
    for (int i = ui->text_5_u2->value(); i >= ua; i -= 2)
    {
        series_5->append(i, -round(ui->text_5_p->value() * 1000 / i * 10) / 10);
    }
    series_5->append(ui->text_5_u1->value(), -ui->text_5_Imax->value());

    scatterSeries_5 = new QScatterSeries();

    scatterSeries_5->setPointLabelsFormat("(@xPoint,@yPoint)");
    scatterSeries_5->setMarkerSize(1);
    scatterSeries_5->setPointLabelsVisible();

    scatterSeries_5->append(ui->text_5_u1->value(), -ui->text_5_Imax->value());
    scatterSeries_5->append(ui->text_5_u1->value(), ui->text_5_Imax->value());
    scatterSeries_5->append(ua, ui->text_5_Imax->value());
    scatterSeries_5->append(ui->text_5_u2->value(), round(ui->text_5_p->value() * 1000 / ui->text_5_u2->value() * 10) / 10);
    scatterSeries_5->append(ui->text_5_u2->value(), -round(ui->text_5_p->value() * 1000 / ui->text_5_u2->value() * 10) / 10);
    scatterSeries_5->append(ua, -ui->text_5_Imax->value());

    series.push_back(series_5);
    scatterSeries.push_back(scatterSeries_5);
}
void widget::on_pushButton_2_clicked()
{
    ui->btnOK->setVisible(false);
    ui->label_41->setVisible(true);
    ui->text->setVisible(true);
    ui->pushButton->setVisible(true);

    for (auto it = group_box.begin(); it != group_box.begin() + ui->text->value(); ++it)
        (*it)->setVisible(false);

    for (int i = 0; i < ui->text->value(); ++i)
    {
        delete series[i];
        series[i] = nullptr;
        delete scatterSeries[i];
        scatterSeries[i] = nullptr;
    }

    series.clear();
    scatterSeries.clear();

    delete axisX;
    axisX = nullptr;
    delete axisY;
    axisY = nullptr;

    iniSeries();
}

void widget::on_btnOK_clicked()
{
    ui->btnOK->setEnabled(false);
    if (ui->text->value() == 1)
    {
        btn_first();
    }
    else if (ui->text->value() == 2)
    {
        btn_first();
        btn_second();
    }
    else if (ui->text->value() == 3)
    {
        btn_first();
        btn_second();
        btn_third();
    }
    else if (ui->text->value() == 4)
    {
        btn_first();
        btn_second();
        btn_third();
        btn_fourth();
    }
    else if (ui->text->value() == 5)
    {
        btn_first();
        btn_second();
        btn_third();
        btn_fourth();
        btn_fifth();
    }
    int start = 0;

    dialog = new Dialog(this);
    dialog->setWindowTitle("设置坐标起始终点值");
    dialog->setAxisStart_stop(0, maxX, maxY);
    int r = dialog->exec();
    if (r == QDialog::Accepted)
    {
        start = dialog->getAxisStart_stop()[0];
        maxX = dialog->getAxisStart_stop()[1];
        maxY = dialog->getAxisStart_stop()[2];
    }
    else
    {
        delete dialog;
        dialog = nullptr;
        return;
    }
    delete dialog;
    dialog = nullptr;

    axisX->setLabelFormat("%d");
    axisX->setTitleText("直流输出电压（V）");
    axisX->setMax(maxX);
    axisX->setMin(start);
    if (maxX <= 3000)
        axisX->setTickCount(maxX / 100 + 1);
    else
        axisX->setTickCount(maxX / 200 + 1);
    axisY->setLabelFormat("%d");
    axisY->setTitleText("直流输出电流（A）");
    axisY->setMax(maxY);
    axisY->setMin(-maxY);
    if (maxY <= 400)
        axisY->setTickCount(maxY / 100 * 2 + 1);
    else if (maxY <= 2000)
        axisY->setTickCount(maxY / 200 * 2 + 1);
    else
        axisY->setTickCount(maxY / 400 * 2 + 1);

    for (auto it = scatterSeries.begin(); it != scatterSeries.begin() + ui->text->value(); ++it)
        chart->addSeries(*it);
    foreach (QLegendMarker *marker, chart->legend()->markers())
    {
        if (marker->type() == QLegendMarker::LegendMarkerTypeXY)
        {
            marker->setVisible(false);
        }
    }
    for (auto it = series.begin(); it != series.begin() + ui->text->value(); ++it)
        chart->addSeries(*it);

    for (int i = 0; i < ui->text->value(); ++i)
    {
        series[i]->attachAxis(axisX);
        series[i]->attachAxis(axisY);
        series[i]->setVisible(true);
        scatterSeries[i]->attachAxis(axisX);
        scatterSeries[i]->attachAxis(axisY);
        scatterSeries[i]->setVisible(true);
    }
    ui->tabWidget->setCurrentIndex(1);
}
