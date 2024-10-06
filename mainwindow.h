#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <memory>
#include "timerstatscollector.h"

/**
 * @brief Основное окно приложения.
 *
 * Этот класс отвечает за отображение главного окна, сбор статистики
 * временных интервалов и взаимодействие с пользователем.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /**
     * @brief Обновляет статистику
     *
     * Этот метод вызывается для обновления отображаемых значений
     * минимального, максимального и среднего временного интервала.
     */
    void updateStats();

    /**
     * @brief Обрабатывает событие нажатия кнопки для показа гистограммы.
     *
     * Этот метод вызывается при нажатии на кнопку "Показать гистограмму"
     * и открывает окно с гистограммой.
     */
    void onShowHistogramClicked();

    /**
     * @brief Показывает информацию о программе.
     *
     * Этот метод открывает диалоговое окно с информацией о программе.
     */
    void showAbout();

private:
    std::unique_ptr<TimerStatsCollector> m_statsCollector;
    std::unique_ptr<QLabel> m_minMaxLabel;
    std::unique_ptr<QLabel> m_avgLabel;
    std::unique_ptr<QPushButton> m_histogramButton;
    std::unique_ptr<QTimer> m_timer;

    /**
     * @brief Настраивает параметры главного окна.
     *
     * Этот метод используется для инициализации параметров главного окна.
     */
    void settingMainWindow();
};

#endif // MAINWINDOW_H
