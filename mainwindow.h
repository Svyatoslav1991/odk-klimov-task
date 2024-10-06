#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <memory>
#include "timerstatscollector.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateStats();
    void onShowHistogramClicked();
    void showAbout();

private:
    std::unique_ptr<TimerStatsCollector> m_statsCollector;
    std::unique_ptr<QLabel> m_minMaxLabel;
    std::unique_ptr<QLabel> m_avgLabel;
    std::unique_ptr<QPushButton> m_histogramButton;
    std::unique_ptr<QTimer> m_timer;

    void settingMainWindow();
};

#endif // MAINWINDOW_H
