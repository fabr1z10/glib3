#include <test/timeformatter.h>
#include <sstream>



//--------------------TimeFormatter-----------------------
int TimeFormatter::referenceDay;

bool TimeFormatter::isReferenceDaySet(const bool isSet) {
    static bool isFirstCall = true;
    if (isSet) {
        isFirstCall = false;
    }
    return !isFirstCall;
}

void TimeFormatter::setReferenceDay(const int secSinceStartDateMidnight) {
    referenceDay = secSinceStartDateMidnight / secADay;
    isReferenceDaySet(true);
}

void TimeFormatter::appendHourMinSec(std::ostream& streamOut, const int secSinceStartDateMidnight) {
    if (secSinceStartDateMidnight < 0) {
        throw std::invalid_argument("TimeFormatter::append_HourMinSec  secSinceStartDateMidnight < 0. secSinceStartDateMidnight = "
                                    + Util::toString(secSinceStartDateMidnight));
    }

    int sec24h = secSinceStartDateMidnight % secADay;
    int hours = sec24h / 3600;
    int minutes = (sec24h - hours * 3600) / 60;
    int seconds = sec24h % 60;

    std::stringstream tempStream;
    tempStream << hours << ":";

    tempStream.fill('0');
    tempStream.width(2);
    tempStream << std::right << minutes << ":";

    tempStream.fill('0');
    tempStream.width(2);
    tempStream << std::right << seconds;

    streamOut << tempStream.str();
}

void TimeFormatter::appendHourMinSecRelativeDay(std::ostream& streamOut, const int secSinceStartDateMidnight,
                                                const bool noDay) {
    if (secSinceStartDateMidnight < 0) {
        throw std::invalid_argument(
                "TimeFormatter::append_HourMinSec_RelativeDay secSinceStartDateMidnight < 0. secSinceStartDateMidnight = "
                + Util::toString(secSinceStartDateMidnight));
    }
    appendHourMinSec(streamOut, secSinceStartDateMidnight);

    if (!noDay) {
        if (!isReferenceDaySet()) {
            streamOut << " (WARNING: Reference day not set)";
        } else {
            int relDays = (secSinceStartDateMidnight / secADay) - referenceDay;
            if (relDays != 0) {
                streamOut << " (day " << relDays << ")";
            }
        }
    }
}

std::string TimeFormatter::toString() const
{
    std::ostringstream stream;
    stream << *this;
    return stream.str();
}