#ifndef HISTOGRAMWINDOW_H
#define HISTOGRAMWINDOW_H

#include <QDialog>
#include <QtCharts/QChartView>

QT_CHARTS_USE_NAMESPACE

class HistogramWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HistogramWindow(QWidget *parent = nullptr);
    ~HistogramWindow();
    void setHistogramData(const std::vector<double>& data);

private:
    QChart* m_chart;
    QChartView* m_chartView;
};

#endif // HISTOGRAMWINDOW_H
