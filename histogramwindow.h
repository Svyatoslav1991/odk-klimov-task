#ifndef HISTOGRAMWINDOW_H
#define HISTOGRAMWINDOW_H

#include <QDialog>
#include <QtCharts/QChartView>

QT_CHARTS_USE_NAMESPACE

/**
 * @brief Класс для отображения гистограммы.
 *
 * Этот класс создает диалоговое окно, в котором отображается
 * гистограмма на основе заданных данных.
 */
class HistogramWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HistogramWindow(QWidget *parent = nullptr);
    ~HistogramWindow();

    /**
     * @brief Установить данные для гистограммы.
     * @param data Вектор значений, который будет отображаться в гистограмме.
     */
    void setHistogramData(const std::vector<double>& data);

private:
    QChart* m_chart;        ///< Указатель на объект графика
    QChartView* m_chartView;///< Указатель на объект представления графика
};

#endif // HISTOGRAMWINDOW_H
