#ifndef TIMERSTATSCOLLECTOR_H
#define TIMERSTATSCOLLECTOR_H

#include <QObject>
#include <vector>
#include <windows.h>
#include <utility>

/**
 * @brief Класс для сбора статистики временных интервалов.
 *
 * Этот класс отслеживает временные интервалы, собирает их и предоставляет методы
 * для получения статистики (минимум, максимум, среднее значение).
 */
class TimerStatsCollector : public QObject {
    Q_OBJECT
public:
    TimerStatsCollector(QObject* parent = nullptr);

    /**
    * @brief Запускает отслеживание временных интервалов.
    *
    * Метод записывает текущий временной интервал и уведомляет
    * об обновлении статистики, если это не первое отслеживание.
    */
    void startTracking();

    /**
    * @brief Получить минимальное и максимальное значения интервалов.
    * @return Пара значений (мин, макс) интервалов.
    */
    std::pair<double, double> getMinMaxIntervals() const;

    /**
    * @brief Получить средний временной интервал.
    * @return Средний интервал времени в секундах.
    */
    double getAverageInterval() const;

    /**
    * @brief Проверяет, были ли пропущены временные слоты.
    * @return true, если были пропущены слоты; иначе false.
    */
    bool hasMissedTimeslot() const;

    /**
    * @brief Получить вектор временных интервалов.
    * @return Вектор, содержащий все отслеживаемые интервалы.
    */
    std::vector<double> getIntervals() const;

signals:
    /**
    * @brief Сигнал, генерируемый при обновлении статистики.
    */
    void statsUpdated();

private:
    std::vector<double> m_intervals;///< Вектор для хранения временных интервалов.
    LARGE_INTEGER m_frequency;      ///< Частота таймера.
    LARGE_INTEGER m_lastTime;       ///< Время последнего отслеживания.
};

#endif // TIMERSTATSCOLLECTOR_H
