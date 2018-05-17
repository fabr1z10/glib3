#include <ostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <limits>
#include <algorithm>

class TimeFormatter {
public:
    /**
    Set the reference day respect to which all output times are computed.
    */
    static void setReferenceDay(const int secSinceStartDateMidnight);

    /**
    Writes a formatted representation of the input absolute time to an output stream.
    @param streamOut the output stream to which the formatted string is appended.
    @param secSinceStartDateMidnight the absolute time to format.
    */
    static void appendHourMinSec(std::ostream& streamOut, const int secSinceStartDateMidnight);

    /**
    Writes a formatted representation of the input absolute time to an output stream.
    @param streamOut the output stream to which the formatted string is appended.
    @param secSinceStartDateMidnight the absolute time to format.
    @param noDay overloads the parameter passed in the TimeFormatter constructor.
    */
    static void appendHourMinSecRelativeDay(std::ostream& streamOut, const int secSinceStartDateMidnight,
                                            const bool noDay);

    /**
    TimeFormatter constructor.
    @param secSinceStartDateMidnight the absolute time to format.
    @param noDay overloads the parameter passed in the TimeFormatter constructor.
    */
    TimeFormatter(const int secSinceStartDateMidnight, const bool noDay = false)
            : secSinceStartDateMidnight(secSinceStartDateMidnight), noDay(noDay){}

    /**
    Extracts a formatted time to the output stream.
    Usage: ostream << TimeFormatter(secSinceStartDateMidnight);
    */
    friend std::ostream& operator<< (std::ostream& streamOut, const TimeFormatter& timeFormatter)
    {
        TimeFormatter::appendHourMinSecRelativeDay(streamOut,
                                                   timeFormatter.secSinceStartDateMidnight, timeFormatter.noDay);
        return streamOut;
    }

    std::string toString() const;

    const int secSinceStartDateMidnight;
    const bool noDay;

private:
    static const int secADay = 60 * 60 * 24;
    static int referenceDay;
    static bool isReferenceDaySet(const bool isSet = false);
};

/**
    Utility library class containing miscellaneous functions.
    All functions are static.
*/
class Util {
public:
    /**
        Converts a parametric type T to a string.
        Type T must have extractor operator << to output stream.
        @param t the value to convert
    */
    template <typename T>
    static std::string toString(const T& t);

    /**
        Converts a parametric type T to a string.
        Type T must have extractor operator << to output stream.
        @param t the value to convert
        @param outString the string which is assigned the converted value
    */
    template <typename T>
    static void toString(const T& t, std::string& outString);

    /**
        Converts a string to a parametric numeric type T, checking the input string.
        If inString is empty or doesn't start with a possible input format for the type T, the supplied defaultValue is returned.
        Type T must have insert operator >> from input stream and std:numeric_limits<T>::is_specialized must be true.
        @param inString the string containing the numeric value to convert
        @param defaultValue the value that is returned if is the string is empty or doesn't start with a possible input format for the type T
    */
    template <typename T>
    static T stringToNumeric(const std::string& inString, T defaultValue);

    /**
        Converts a string to a parametric numeric type T, checking the input string.
        If inString is empty or doesn't start with a possible input format for the type T, a std::invalid_argument exception is thrown.
        Type T must have insert operator >> from input stream and std:numeric_limits<T>::is_specialized must be true.
        @param inString the string containing the numeric value to convert
        @throws std::invalid_argument if is the string is empty or doesn't start with a possible input format for the type T
    */
    template <typename T>
    static T stringToNumeric(const std::string& inString);

    /**
        Checks if the beginning of a string is a valid representation of a numeric value.
        The string may begin with blanks and contain sign and decimal separator.
        @param inStr the string to check
        @return true if the check is passed.
    */
    static bool startsWithNumeric(const std::string& inStr);

    /**
        Checks if the beginning of a string is a valid representation of a numeric value and begins with a 0.
        The string may begin with blanks and contain sign and decimal separator.
        @param inStr the string to check
        @return true if the check is passed.
    */
    static bool startsWithNumericZero(const std::string& inStr);

    /**
        Returns a string obtained replacing all occurances of a charachter with another charachter in an input string.
        @param inStr the original string
        @param chToSearch the charachter to be replaced
        @param chToPut the replacing charachter
        @return the new string
    */
    static std::string replaceChars(const std::string& inStr, const char chToSearch, const char chToPut);

    /**
        Returns a string obtained trimming all beginning blanks or another specific charachter from an input string.
        @param inStr the original string
        @param chToTrim the charachter to be trimmed, if not specified the blank charachter is trimmed
        @return the new string
    */
    static std::string trimLeft(const std::string &inStr, const char chToTrim = ' ');

    /**
        Returns a string obtained trimming all ending blanks or another specific charachter from an input string.
        @param inStr the original string
        @param chToTrim the charachter to be trimmed, if not specified the blank charachter is trimmed
        @return the new string
    */
    static std::string trimRight(const std::string &inStr, const char chToTrim = ' ');

    /**
        Returns a string obtained trimming all beginning and ending blanks or another specific charachter from an input string.
        @param inStr the original string
        @param chToTrim the charachter to be trimmed, if not specified the blank charachter is trimmed
        @return the new string
    */
    static std::string trim(const std::string& inStr, const char chToTrim = ' ');

    /**
        Returns a string obtained converting to uppercase all charachters from an input string.
        @param inStr the original string
        @return the new string
    */
    static std::string toUpperCase(const std::string& inStr);

    /**
        Returns a string obtained converting to lowercase all charachters from an input string.
        @param inStr the original string
        @return the new string
    */
    static std::string toLowerCase(const std::string& inStr);

    /**
        Splits an input string into tokens using a specified separator.
        @param inStr the original string
        @param sep the separator used to split the string
        @param tokens the vector where the tokens are inserted (pushed back)
        @param addAlsoEmptyTokens indicates if empty strings should be added to the tokens
    */
    static void split(const std::string& inStr, const std::string& sep,
                      std::vector<std::string>& tokens, const bool addAlsoEmptyTokens = true);

    /**
        Returns the n-th integer value contained in a string.
        @param strIn the string containing the integer value to parse
        @param integerOrdinalPos the ordinal number of the integer value to return, starting from 0
        @param skipMinus if true the '-' character is not meant as the sign of the integer value and the returned value is always positive
        @return the n-th integer if present
        @throws a std::invalid_argument exception if the supplied string doesn't contain enough integers.
    */
    static int parseInteger(const std::string strIn, const unsigned integerOrdinalPos,
                            const bool skipMinus = false);

    /**
        Parses a time value in the format hh:mm:ss contained in a string.
        @param inStr the string containing the time value to parse
        @param hours the output integer parameter where the hours are parsed into
        @param minutes the output integer parameter where the minutes are parsed into
        @param seconds the output integer parameter where the hours are seconds into
        @throws a std::invalid_argument exception if the supplied string doesn't contain a well formatted time.
    */
    static void hmsStrParse(const std::string& inStr, unsigned& hours, unsigned& minutes, unsigned& seconds);

    /**
        Returns the number of seconds since midnight parsing a time value in the format hh:mm:ss contained in a string.
        @param inStr the string containing the time value to parse
        @return the number of seconds since midnight
        @throws a std::invalid_argument exception if the supplied string doesn't contain a well formatted time.
    */
    static unsigned hmsStrToSec(const std::string&  inStr);

    /**
        Returns the name of the current executable file without the path.
        In Windows O.S. the extension (the ending ".exe") is removed.
    */
    //static std::string getExeName();


    /**
        It returns true  if two intervals intersect and are not adjacent
        @param start1 first interval start
        @param end1 first interval end
        @param start2 second interval start
        @param end2 second interval end
    */
    static bool hasIntersection(const int start1, const int end1, const int start2, const int end2) {

        if(intersectionValue(start1,end1,start2,end2)>0 )
            return true;
        else if(intersectionValue(start1,end1,start2,end2)<0 )
            return false;
        else if (end2 == start1)
            return false;
        else if (end1 == start2)
            return false;
        else if(start1== end1  && start2 <= start1 && start1 <= end2)
            return true;
        else  if ( start2==end2 && start1 <= start2 && start2<=end1)
            return true;
        else
            return false;
    }

    /**
        It returns true if two intervals strictly intersect and are not adjacent
        @param start1 first interval start
        @param end1 first interval end
        @param start2 second interval start
        @param end2 second interval end
    */
    static bool hasStrictIntersection(const int start1, const int end1, const int start2, const int end2) {

        if(intersectionValue(start1,end1,start2,end2)>0 )
            return true;
        else if(intersectionValue(start1,end1,start2,end2)<0 )
            return false;
        else if (end2 == start1)
            return false;
        else if (end1 == start2)
            return false;
        else if(start1== end1  && start2 < start1 && start1 < end2)
            return true;
        else  if ( start2==end2 && start1 < start2 && start2<end1)
            return true;
        else
            return false;
    }


    /**
        It returns true if two intervals are equal and pointed
        @param start1 first interval start
        @param end1 first interval end
        @param start2 second interval start
        @param end2 second interval end
    */
    static  bool isEqual(const int start1, const int end1, const int start2, const int end2) {
        if(start1==end1 && start2 == end2 && start1 == start2)
            return true;
        else
            return false;
    }


    /**
        it retruns back a measure related to the intersection between two intervals
        @return if they intersect is the intersection with, otherwise the absolute value gives the distance between tow intervals
    */
    static  int intersectionValue(const int start1, const int end1, const int start2, const int end2) {
        return std::min(end1,end2) - std::max(start1,start2);
    }



    /**
        Returns a double precision floating point value obtained from the input value rounded to the nearest integer value.
        @param r the double precision floating point value to round
        @return the double precision floating point value rounded to the nearest integer value
    */
    static inline double roundToDouble(const double r) {
        return (r > 0.0) ? std::floor(r + 0.5) : std::ceil(r - 0.5);
    }

    /**
        Returns an integer value obtained from the input value rounded to the nearest integer value.
        @param x the double precision floating point value to round
        @return the integer value rounded to the nearest integer value
    */
    static inline int roundToInt(const double x){
        return int(x > 0.0 ? x + 0.5 : x - 0.5);
    }

    /**
        Checks if a double precision floating point value is not a valid number.
        @param x the double precision floating point value to check
        @return true if input value is not a number
    */
    static inline bool isNaN(double x) {
        volatile double d = x;//without this line there is a chance the compiler will optimize the comparison out, always returning true. e.g. if -ffast-math is set, isnan() will fail to return the correct result for gcc. Of course, this optimization is documented as breaking IEEE semantics.
        return d != d;
    }

    /**
        Checks if the input value is zero (0).
        @param v the generic value to check
        @return true if input value is 0
    */
    template <typename T>
    static bool isNotZero(const T& v) { return v != T(0); }


    /**
        Returns the coordinates of the intersection point of two segments.
        @param x1 x coordinate of an extreme point of the first segment
        @param y1 y coordinate of an extreme point of the first segment
        @param x2 x coordinate of the other extreme point of the first segment
        @param y2 y coordinate of the other extreme point of the first segment
        @param x3 x coordinate of an extreme point of the second segment
        @param y3 y coordinate of an extreme point of the second segment
        @param x4 x coordinate of the other extreme point of the second segment
        @param y4 y coordinate of the other extreme point of the second segment
        @param x x coordinate of the intersection point
        @param y y coordinate of the intersection point
        @return true if the two segments intersect
    */
    static bool findIntersectionTwoSegments(double x1, double y1, double x2, double y2, double x3,
                                            double y3, double x4, double y4, double& x, double& y);

private:
    static const std::string allDecimalDigits;
};

//--------Template implementation------------------
template <typename T>
std::string Util::toString(const T& t){
    std::string outString;
    toString(t, outString);
    return outString;
}

template <typename T>
void Util::toString(const T& t, std::string& outString){
    std::stringstream ss;
    if(std::numeric_limits<T>::is_specialized && std::numeric_limits<T>::is_iec559){
        ss.precision(std::numeric_limits<T>::digits10 + 2);
    }
    ss << t;
    outString = ss.str();
}

template <typename T>
T Util::stringToNumeric(const std::string& inString, T defaultValue) {
    //TODO? usare static_assert
    if(!std::numeric_limits<T>::is_specialized)
        throw std::invalid_argument("Util::StringToNumeric: implemented only for types that have a specialized numeric_limit implementation.");
    if(!startsWithNumeric(inString)) return defaultValue;
    bool isZero(startsWithNumericZero(inString));
    if(isZero) return T(0);
    std::istringstream stream(inString);
    T retVal(defaultValue);
    stream >> retVal;
    if(defaultValue != 0 && retVal == 0 && !isZero) return defaultValue;
    return retVal;
}

template <typename T>
T Util::stringToNumeric(const std::string& inString) {
    //TODO? usare static_assert
    if(!std::numeric_limits<T>::is_specialized)
        throw std::invalid_argument("Util::StringToNumeric: implemented only for types that have a specialized numeric_limit implementation.");
    if(!startsWithNumeric(inString))
        throw std::invalid_argument("Util::StringToNumeric: !StartsWithNumeric(inString)");
    bool isZero(startsWithNumericZero(inString));
    if(isZero) return T(0);
    T defaultValue(std::numeric_limits<T>::min());
    T retVal(defaultValue);
    std::istringstream stream(inString);
    stream >> retVal;
    if(defaultValue != 0 && retVal == 0 && !isZero)
        throw std::invalid_argument("Util::StringToNumeric: invalid format, inString=\"" + inString + "\"");
    if(retVal == defaultValue){//check if default value was used, starting from a different default value
        T defaultValueBis(std::numeric_limits<T>::max());
        //TODO? usare static_assert
        if(defaultValue == defaultValueBis)
            throw std::invalid_argument("Util::StringToNumeric: T.min() == T.max()");
        T retValBis(defaultValueBis);
        std::istringstream streamBis(inString);
        streamBis >> retValBis;
        if(retVal != retValBis)
            throw std::invalid_argument("Util::StringToNumeric: invalid format, inString=\"" + inString + "\"");
    }
    return retVal;
}

//---------TemplateFullSpecialization-------------------

template <> //Template specialization for bool, converts a string to a bool (see base template).
inline bool Util::stringToNumeric(const std::string& inString, bool defaultValue){
    std::string locString(inString);
    std::transform(locString.begin(), locString.end(), locString.begin(), ::tolower);
    locString = Util::trim(locString);
    if(locString.size() > 5) locString = locString.substr(0, 5);
    if(locString == "false") return false;
    if(locString.size() > 4) locString = locString.substr(0, 4);
    if(locString == "true") return true;

    int inAsInt(stringToNumeric<int>(inString, defaultValue ? 1 : 0));
    return inAsInt != 0;
}

template <> //Template specialization for bool, converts a string to a bool, throws std::invalid_argument exception if format is invalid (see base template).
inline bool Util::stringToNumeric(const std::string& inString){
    std::string locString(inString);
    std::transform(locString.begin(), locString.end(), locString.begin(), ::tolower);
    locString = Util::trim(locString);
    if(locString.size() > 5) locString = locString.substr(0, 5);
    if(locString == "false") return false;
    if(locString.size() > 4) locString = locString.substr(0, 4);
    if(locString == "true") return true;

    int inAsInt(stringToNumeric<int>(inString));
    return inAsInt != 0;
}