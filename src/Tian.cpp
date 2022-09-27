#include "Tian.h"

Tian::Tian(QWidget *parent)
    : QMainWindow(parent), ui(new Ui_Tian)
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
    m_series_name.push_back("范围一");
    m_series_name.push_back("范围二");
    m_series_name.push_back("范围三");
    m_series_name.push_back("范围四");
    m_series_name.push_back("范围五");
}

Tian::~Tian()
{
    if (m_chart != nullptr)
    {
        delete m_chart;
        m_chart = nullptr;
        delete m_chartView;
        m_chartView = nullptr;
        delete m_mainLayout;
        m_mainLayout = nullptr;
        delete m_mainWidget;
        m_mainWidget = nullptr;
    }
    delete ui;
}

void Tian::iniChart()
{
    m_chart = new QChart();
    m_chartView = new QChartView(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);
}

void Tian::addSeries()
{
    for (int i = 0; i < ui->text->value(); ++i)
    {
        QLineSeries *series = new QLineSeries();
        m_series.append(series);

        series->setUseOpenGL(true);
        series->setName(m_series_name[i]);

        QList<QPointF> data;

        qreal ua = round(value[i][2] * 1000 / value[i][3] * 10) / 10;

        maxX = std::max(maxX, ((int)value[i][1] / 100 + 1) * 100);
        maxY = std::max(maxY, ((int)value[i][3] / 100 + 1) * 100);
        if (maxX <= 3000)
            maxX = std::max(maxX, ((int)value[i][1] / 100 + 1) * 100);
        else
            maxX = std::max(maxX, ((int)value[i][1] / 200 + 1) * 200);
        if (maxY <= 400)
            maxY = std::max(maxY, ((int)value[i][3] / 100 + 1) * 100);
        else if (maxY <= 2000)
            maxY = std::max(maxY, ((int)value[i][3] / 200 + 1) * 200);
        else
            maxY = std::max(maxY, ((int)value[i][3] / 400 + 1) * 400);

        data.append(QPointF(value[i][0], -value[i][3]));
        data.append(QPointF(value[i][0], value[i][3]));
        data.append(QPointF(ua, value[i][3]));
        for (int j = ua; j <= value[i][1]; j += 2)
        {
            data.append(QPointF(j, round(value[i][2] * 1000 / j * 10) / 10));
        }
        for (int j = value[i][1]; j >= ua; j -= 2)
        {
            data.append(QPointF(j, -round(value[i][2] * 1000 / j * 10) / 10));
        }
        data.append(QPointF(value[i][0], -value[i][3]));

        series->append(data);
        m_chart->addSeries(series);
    }
}

void Tian::addScaSeries()
{
    for (int i = 0; i < ui->text->value(); ++i)
    {
        QScatterSeries *series = new QScatterSeries();
        series->setPointLabelsFormat("(@xPoint, @yPoint)");
        series->setMarkerSize(6);
        series->setPointLabelsVisible();
        series->setPointLabelsClipping(false);
        m_point.append(series);

        QList<QPointF> data;

        qreal ua = round(value[i][2] * 1000 / value[i][3] * 10) / 10;

        if (ui->radioButton->isChecked())
        {
            data.append(QPointF(value[i][0], -value[i][3]));
            data.append(QPointF(value[i][1], -round(value[i][2] * 1000 / value[i][1] * 10) / 10));
            data.append(QPointF(ua, -value[i][3]));
        }
        data.append(QPointF(value[i][0], value[i][3]));
        data.append(QPointF(ua, value[i][3]));
        data.append(QPointF(value[i][1], round(value[i][2] * 1000 / value[i][1] * 10) / 10));

        series->append(data);
        m_chart->addSeries(series);
    }
}

void Tian::addAxis()
{
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

        ui->btnOK->setEnabled(false);
        for (auto it = group_box.begin(); it != group_box.begin() + ui->text->value(); ++it)
            (*it)->setEnabled(false);

        addScaSeries();

        for (int i = ui->text->value(); i < 2 * ui->text->value(); ++i)
        {
            m_chart->legend()->markers().at(i)->setVisible(false);
        }

        m_mainLayout = new QGridLayout();
        m_mainLayout->addWidget(m_chartView, 0, 1, 3, 1);
        m_mainWidget = new QWidget();
        m_mainWidget->setLayout(m_mainLayout);
        QString label;
        if (ui->radioButton->isChecked())
            label = ui->radioButton->text();
        else
            label = ui->radioButton_2->text();
        ui->tabWidget->addTab(m_mainWidget, label);
        ui->tabWidget->setCurrentIndex(1);

        ui->radioButton->setEnabled(false);
        ui->radioButton_2->setEnabled(false);
    }
    else
    {
        delete dialog;
        dialog = nullptr;

        while (m_series.count() > 0)
        {
            QLineSeries *series = m_series.last();
            m_chart->removeSeries(series);
            m_series.removeLast();
            delete series;
        }

        delete m_chart;
        m_chart = nullptr;

        delete m_chartView;
        m_chartView = nullptr;

        value.clear();
        return;
    }
    delete dialog;
    dialog = nullptr;

    axisX = new QValueAxis();
    axisY = new QValueAxis();
    m_chart->addAxis(axisX, Qt::AlignBottom);
    m_chart->addAxis(axisY, Qt::AlignLeft);

    axisX->setLabelFormat("%d");
    axisX->setMax(maxX);
    axisX->setMin(start);
    if (maxX <= 3000)
        axisX->setTickCount(maxX / 100 + 1);
    else
        axisX->setTickCount(maxX / 200 + 1);
    axisY->setLabelFormat("%d");
    axisY->setMax(maxY);
    if (maxY <= 400)
        axisY->setTickCount(maxY / 100 * 2 + 1);
    else if (maxY <= 2000)
        axisY->setTickCount(maxY / 200 * 2 + 1);
    else
        axisY->setTickCount(maxY / 400 * 2 + 1);

    if (ui->radioButton->isChecked())
    {
        axisX->setTitleText("直流输出电压（V）");
        axisY->setTitleText("直流输出电流（A）");
        axisY->setMin(-maxY);
    }
    else
    {
        axisX->setTitleText("交流输出电压（V）");
        axisY->setTitleText("交流输出电流（A）");
        axisY->setMin(0);
    }

    for (int i = 0; i < ui->text->value(); ++i)
    {
        m_series.at(i)->attachAxis(axisX);
        m_series.at(i)->attachAxis(axisY);
        m_point.at(i)->attachAxis(axisX);
        m_point.at(i)->attachAxis(axisY);
    }
}

void Tian::on_pushButton_clicked()
{
    ui->label_41->setVisible(false);
    ui->text->setVisible(false);
    ui->pushButton->setVisible(false);
    ui->btnOK->setVisible(true);
    ui->btnOK->setEnabled(true);

    for (auto it = group_box.begin(); it != group_box.begin() + ui->text->value(); ++it)
        (*it)->setVisible(true);
}

void Tian::on_btnOK_clicked()
{
    std::vector<qreal> v;
    v.push_back(ui->text_1_u1->value());
    v.push_back(ui->text_1_u2->value());
    v.push_back(ui->text_1_p->value());
    v.push_back(ui->text_1_Imax->value());
    value.push_back(v);
    v.clear();
    v.push_back(ui->text_2_u1->value());
    v.push_back(ui->text_2_u2->value());
    v.push_back(ui->text_2_p->value());
    v.push_back(ui->text_2_Imax->value());
    value.push_back(v);
    v.clear();
    v.push_back(ui->text_3_u1->value());
    v.push_back(ui->text_3_u2->value());
    v.push_back(ui->text_3_p->value());
    v.push_back(ui->text_3_Imax->value());
    value.push_back(v);
    v.clear();
    v.push_back(ui->text_4_u1->value());
    v.push_back(ui->text_4_u2->value());
    v.push_back(ui->text_4_p->value());
    v.push_back(ui->text_4_Imax->value());
    value.push_back(v);
    v.clear();
    v.push_back(ui->text_5_u1->value());
    v.push_back(ui->text_5_u2->value());
    v.push_back(ui->text_5_p->value());
    v.push_back(ui->text_5_Imax->value());
    value.push_back(v);

    iniChart();
    addSeries();
    addAxis();
}

void Tian::on_radioButton_clicked(bool checked)
{
    if (checked)
    {
        ui->label->clear();
        ui->label->setText("直流最低电压U1：");
        ui->label_2->clear();
        ui->label_2->setText("直流最高电压U2：");
        ui->label_6->clear();
        ui->label_6->setText("直流功率P：");
        ui->label_8->clear();
        ui->label_8->setText("直流电流Imax：");

        ui->label_9->clear();
        ui->label_9->setText("直流最低电压U1：");
        ui->label_11->clear();
        ui->label_11->setText("直流最高电压U2：");
        ui->label_13->clear();
        ui->label_13->setText("直流功率P：");
        ui->label_15->clear();
        ui->label_15->setText("直流电流Imax：");

        ui->label_17->clear();
        ui->label_17->setText("直流最低电压U1：");
        ui->label_19->clear();
        ui->label_19->setText("直流最高电压U2：");
        ui->label_21->clear();
        ui->label_21->setText("直流功率P：");
        ui->label_23->clear();
        ui->label_23->setText("直流电流Imax：");

        ui->label_25->clear();
        ui->label_25->setText("直流最低电压U1：");
        ui->label_27->clear();
        ui->label_27->setText("直流最高电压U2：");
        ui->label_29->clear();
        ui->label_29->setText("直流功率P：");
        ui->label_31->clear();
        ui->label_31->setText("直流电流Imax：");

        ui->label_33->clear();
        ui->label_33->setText("直流最低电压U1：");
        ui->label_35->clear();
        ui->label_35->setText("直流最高电压U2：");
        ui->label_37->clear();
        ui->label_37->setText("直流功率P：");
        ui->label_39->clear();
        ui->label_39->setText("直流电流Imax：");
    }
}

void Tian::on_radioButton_2_clicked(bool checked)
{
    if (checked)
    {
        ui->label->clear();
        ui->label->setText("交流最低电压U1：");
        ui->label_2->clear();
        ui->label_2->setText("交流最高电压U2：");
        ui->label_6->clear();
        ui->label_6->setText("交流功率P：");
        ui->label_8->clear();
        ui->label_8->setText("交流电流Imax：");

        ui->label_9->clear();
        ui->label_9->setText("交流最低电压U1：");
        ui->label_11->clear();
        ui->label_11->setText("交流最高电压U2：");
        ui->label_13->clear();
        ui->label_13->setText("交流功率P：");
        ui->label_15->clear();
        ui->label_15->setText("交流电流Imax：");

        ui->label_17->clear();
        ui->label_17->setText("交流最低电压U1：");
        ui->label_19->clear();
        ui->label_19->setText("交流最高电压U2：");
        ui->label_21->clear();
        ui->label_21->setText("交流功率P：");
        ui->label_23->clear();
        ui->label_23->setText("交流电流Imax：");

        ui->label_25->clear();
        ui->label_25->setText("交流最低电压U1：");
        ui->label_27->clear();
        ui->label_27->setText("交流最高电压U2：");
        ui->label_29->clear();
        ui->label_29->setText("交流功率P：");
        ui->label_31->clear();
        ui->label_31->setText("交流电流Imax：");

        ui->label_33->clear();
        ui->label_33->setText("交流最低电压U1：");
        ui->label_35->clear();
        ui->label_35->setText("交流最高电压U2：");
        ui->label_37->clear();
        ui->label_37->setText("交流功率P：");
        ui->label_39->clear();
        ui->label_39->setText("交流电流Imax：");
    }
}

void Tian::on_btnReset_clicked()
{
    ui->tabWidget->removeTab(1);
    for (auto it = group_box.begin(); it != group_box.begin() + ui->text->value(); ++it)
    {
        (*it)->setEnabled(true);
        (*it)->setVisible(false);
    }
    ui->text->setVisible(true);
    ui->pushButton->setVisible(true);
    ui->btnOK->setVisible(false);
    ui->radioButton->setEnabled(true);
    ui->radioButton_2->setEnabled(true);

    if (m_chart != nullptr)
    {
        while (m_series.count() > 0)
        {
            QLineSeries *series = m_series.last();
            m_chart->removeSeries(series);
            m_series.removeLast();
            delete series;
        }
        while (m_point.count() > 0)
        {
            QScatterSeries *series = m_point.last();
            m_chart->removeSeries(series);
            m_point.removeLast();
            delete series;
        }

        m_chart->removeAxis(axisX);
        m_chart->removeAxis(axisY);
        delete axisX;
        axisX = nullptr;
        delete axisY;
        axisY = nullptr;

        delete m_chart;
        m_chart = nullptr;

        delete m_chartView;
        m_chartView = nullptr;

        delete m_mainLayout;
        m_mainLayout = nullptr;

        delete m_mainWidget;
        m_mainWidget = nullptr;
    }

    value.clear();
}
