#include "timerstatscollector.h"
#include <numeric>
#include <algorithm>

TimerStatsCollector::TimerStatsCollector(QObject *parent) : QObject(parent)
{
    QueryPerformanceFrequency(&m_frequency);
    m_lastTime.QuadPart = 0;
}

//---------------------------------------------------------------------------------------


void TimerStatsCollector::startTracking()
{
    LARGE_INTEGER currentTime;
    QueryPerformanceCounter(&currentTime);

    if (m_lastTime.QuadPart != 0) {
        double interval = static_cast<double>(currentTime.QuadPart - m_lastTime.QuadPart) / m_frequency.QuadPart;
        m_intervals.push_back(interval);
        emit statsUpdated();
    }
    m_lastTime = currentTime;
}

//---------------------------------------------------------------------------------------


std::pair<double, double> TimerStatsCollector::getMinMaxIntervals() const
{
    if (m_intervals.empty()) return {0.0, 0.0};

    auto [minIt, maxIt] = std::minmax_element(m_intervals.begin(), m_intervals.end());
    return {*minIt, *maxIt};
}

//---------------------------------------------------------------------------------------


double TimerStatsCollector::getAverageInterval() const
{
    if (m_intervals.empty()) return 0.0;

    double sum = std::accumulate(m_intervals.begin(), m_intervals.end(), 0.0);
    return sum / m_intervals.size();
}

//---------------------------------------------------------------------------------------


bool TimerStatsCollector::hasMissedTimeslot() const
{
    double avg = getAverageInterval();
    for (const auto& interval : m_intervals) {
        if (interval > 2 * avg) {
            return true;
        }
    }
    return false;
}

//---------------------------------------------------------------------------------------


std::vector<double> TimerStatsCollector::getIntervals() const
{
    return m_intervals;
}
