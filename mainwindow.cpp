#include "mainwindow.h"
#include <QVBoxLayout>
#include <QTimer>
#include "histogramwindow.h"
#include <QDebug>
#include <QMenuBar>
#include <QMessageBox>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_statsCollector(std::make_unique<TimerStatsCollector>(this)),
      m_minMaxLabel(std::make_unique<QLabel>("Min/Max интервал: 0/0", this)),
      m_avgLabel(std::make_unique<QLabel>("Средний интервал: 0", this)),
      m_histogramButton(std::make_unique<QPushButton>("Показать гистограмму", this)),
      m_timer(std::make_unique<QTimer>(this))
{
    this->settingMainWindow();
}

//------------------------------------------------------------------------------------------------------------

MainWindow::~MainWindow()
{
}

//------------------------------------------------------------------------------------------------------------

//Обновляет статистику
void MainWindow::updateStats()
{
    auto[min, max] = m_statsCollector->getMinMaxIntervals();
    double avg = m_statsCollector->getAverageInterval();

    m_minMaxLabel->setText(QString("Min/Max интервал: %1/%2").arg(min).arg(max));
    m_avgLabel->setText(QString("Средний интервал: %1").arg(avg));
}

//------------------------------------------------------------------------------------------------------------

//Обрабатывает событие нажатия кнопки для показа гистограммы
void MainWindow::onShowHistogramClicked()
{
    auto intervals = m_statsCollector->getIntervals();

    if (intervals.empty()) {
        qWarning("Вектор интервалов пуст!");
        return;
    }

    try {
        auto histogramWindow = std::make_unique<HistogramWindow>(nullptr);
        histogramWindow->setHistogramData(intervals);
        histogramWindow->exec();
    } catch (const std::exception &e) {
        qCritical() << "Exception occurred:" << e.what();
    }
}

//------------------------------------------------------------------------------------------------------------

//Показывает информацию о программе
void MainWindow::showAbout()
{
    QMessageBox::information(this, "О программе", "Тестовое задание\nИзвестно, что ни Windows, ни Линукс не являются системами реального времени — каждому процессу/потоку таймслот для работы выделяется с определенной периодичностью диспетчером на конкурентной основе с многочисленными работающими службам и другими приложениями. Тем не менее для простоты нередко приложения, работающие с «железом», разрабатывают под этими ОС. Требуется разработать приложение, которое накапливало бы статистику промежутков времени между моментами предоставления ему процессорного времени, с периодом в 10с отображало бы текущие данные о Min и Max полигона рассеяния величин таких интервалов, оценку величины периода таймслотов и наличия пропусков таймслотов, если они имели место. Приложение должно также по нажатию определенной кнопки показать в отдельном окне графическое представление накопленной статистики в виде гистограммы. Желательно (факультативно) сделать приложение кроссплатформенным, но для начала можно обойтись и одной ОС (на Ваш выбор).");
}

//------------------------------------------------------------------------------------------------------------

//Этот метод используется для инициализации параметров главного окна
void MainWindow::settingMainWindow()
{
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    layout->addWidget(m_minMaxLabel.get());
    layout->addWidget(m_avgLabel.get());
    layout->addWidget(m_histogramButton.get());
    setCentralWidget(centralWidget);

    connect(m_timer.get(), &QTimer::timeout, this, [&]() {
        m_statsCollector->startTracking(); // Начинаем отслеживание интервалов
    });

    m_timer->start(10000);

    connect(m_histogramButton.get(), &QPushButton::clicked, this, &MainWindow::onShowHistogramClicked);
    connect(m_statsCollector.get(), &TimerStatsCollector::statsUpdated, this, &MainWindow::updateStats);

    m_statsCollector->startTracking();

    resize(350, 250);

    this->setWindowTitle("Задание от ОДК Климов");

    setWindowIcon(QIcon(":/icons/icons/klimov.jpg"));

    QMenuBar* menuBar = this->menuBar();
    QMenu* fileMenu = menuBar->addMenu("Файл");

    QAction* aboutAction = new QAction(QIcon(":/icons/icons/questionmark.ico"), "О программе", this);
    QAction* exitAction = new QAction(QIcon(":/icons/icons/cross.ico"), "Выход", this);

    aboutAction->setShortcut(QKeySequence("Ctrl+O"));
    exitAction->setShortcut(QKeySequence("Ctrl+Q"));

    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAbout);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    fileMenu->addAction(aboutAction);
    fileMenu->addAction(exitAction);
}

