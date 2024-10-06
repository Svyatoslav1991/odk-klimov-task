#include "histogramwindow.h"
#include <QVBoxLayout>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QValueAxis>
#include <QDebug>

HistogramWindow::HistogramWindow(QWidget *parent) :
    QDialog(parent),
    m_chart(new QChart()),             // Создаем обычный указатель
    m_chartView(new QChartView(m_chart)) // Создаем обычный указатель
{
    m_chart->setTitle("Гистограмма");
    m_chartView->setRenderHint(QPainter::Antialiasing);

    this->resize(500, 400);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_chartView);
    setLayout(layout);

}

//-------------------------------------------------------------------------------

HistogramWindow::~HistogramWindow() {
    delete m_chart;
    delete m_chartView;
}

//-------------------------------------------------------------------------------

//Устанавливить данные для гистограммы
void HistogramWindow::setHistogramData(const std::vector<double>& data)
{
    QBarSet *set = new QBarSet("Интервалы");

    // Преобразуем данные в набор для гистограммы
    for (double value : data) {
        *set << value;
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    // Добавляем серию к графику
    m_chart->addSeries(series);
    m_chart->createDefaultAxes();

    // Устанавливаем оси
    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Интервалы");
    m_chart->setAxisX(axisX, series);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Количество");
    m_chart->setAxisY(axisY, series);
}
