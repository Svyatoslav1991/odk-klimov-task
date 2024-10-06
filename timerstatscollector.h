#ifndef TIMERSTATSCOLLECTOR_H
#define TIMERSTATSCOLLECTOR_H

#include <QObject>
#include <vector>
#include <windows.h>
#include <utility>

class TimerStatsCollector : public QObject {
    Q_OBJECT
public:
    TimerStatsCollector(QObject* parent = nullptr);
    void startTracking();
    std::pair<double, double> getMinMaxIntervals() const;
    double getAverageInterval() const;
    bool hasMissedTimeslot() const;
    std::vector<double> getIntervals() const;

signals:
    void statsUpdated();

private:
    std::vector<double> m_intervals;
    LARGE_INTEGER m_frequency;
    LARGE_INTEGER m_lastTime;
};

#endif // TIMERSTATSCOLLECTOR_H
