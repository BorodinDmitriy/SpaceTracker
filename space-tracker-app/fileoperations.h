#include <string>
#include <cstdio>
#include "config.h"

// Формат TLE
// 1 00150U 61015AL  18020.36587778 -.00000036  00000-0  39783-4 0  9995
// 2 00150  66.2469 252.6634 0070217 239.6419 119.7695 13.80980942684785
// Размеры строк фиксированы, константы определяются исходя из этого формата

class FileOperations
{
public:
    FileOperations() {}
    ~FileOperations() {}

    static bool IsZeroLineValid(std::string &rStrLine)
    {
        if (rStrLine.length() >= 1 && rStrLine.length() <= 24) return true;
        else return false;
    }

    static bool IsFirstLineValid(std::string &rStrLine)
    {
        if (rStrLine[0] != '1') return false;

        if (rStrLine.length() != TLE_CHECK_SUM_START_AND_FINISH_POSITION + 1) return false;

        if (!IsWhitespacesValidLine1(rStrLine)) return false;

        if (!IsNoradNumValid(rStrLine)) return false;

        if (!IsClassValid(rStrLine)) return false;

        if (!IsLaunchYearValid(rStrLine)) return false;

        if (!IsLaunchNumValid(rStrLine)) return false;

        if (!IsLaunchPartValid(rStrLine)) return false;

        if (!IsEpochYearValid(rStrLine)) return false;

        if (!IsEpochTimeValid(rStrLine)) return false;

        if (!IsAccelerationValid(rStrLine)) return false;

        if (!IsVelocitySecondDiffValid(rStrLine)) return false;

        if (!IsBrakeKoefValid(rStrLine)) return false;

        if (!IsEpherimidTypeValid(rStrLine)) return false;

        if (!IsVersionValid(rStrLine)) return false;

        if (!IsControllSumValid(rStrLine)) return false;

        return true;
    }

    static bool IsSecondLineValid(std::string &rStrLine)
    {
        if (rStrLine[0] != '2') return false;

        if (rStrLine.length() != TLE_CHECK_SUM_START_AND_FINISH_POSITION + 1) return false;

        if (!IsWhitespacesValidLine2(rStrLine)) return false;

        if (!IsInclinationValid(rStrLine)) return false;

        if (!IsAscDegreeValid(rStrLine)) return false;

        if (!IsEccentricityValid(rStrLine)) return false;

        if (!IsPercentArgValid(rStrLine)) return false;

        if (!IsMidAnomalityValid(rStrLine)) return false;

        if (!IsPeriodFreqValid(rStrLine)) return false;

        if (!IsPeriodAmntValid(rStrLine)) return false;

        if (!IsControllSumValid(rStrLine)) return false;

        return true;
    }

    static bool IsWhitespacesValidLine1(std::string &rStrLine)
    {
        if (rStrLine[TLE_ID_START_POSITION - 1] != ' ') return false;
        if (rStrLine[TLE_LAUNCH_YEAR_START_POSITION - 1] != ' ') return false;
        if (rStrLine[TLE_ERA_START_POSITION - 1] != ' ') return false;
        if (rStrLine[TLE_FIRST_DERIVATIVE_START_POSITION - 1] != ' ') return false;
        if (rStrLine[TLE_SECOND_DERIVATIVE_START_POSITION - 1] != ' ') return false;
        if (rStrLine[TLE_FLOW_TYPE_START_POSITION - 1] != ' ') return false;
        if (rStrLine[TLE_FLOW_TYPE_FINISH_POSITION] != ' ') return false;
        if (rStrLine[TLE_NUM_TYPE_START_POSITION - 1] != ' ') return false;

        return true;
    }

    static bool IsWhitespacesValidLine2(std::string &rStrLine)
    {
        if (rStrLine[TLE_ID_START_POSITION - 1] != ' ') return false;
        if (rStrLine[TLE_INCLINATION_START_POSITION - 1] != ' ') return false;
        if (rStrLine[TLE_INCLINATION_TO_THE_RIGHT_START_POSITION - 1] != ' ') return false;
        if (rStrLine[TLE_EXCENTRICITY_START_POSITION - 1] != ' ') return false;
        if (rStrLine[TLE_PERIGEE_START_POSITION - 1] != ' ') return false;
        if (rStrLine[TLE_MEAN_ANOMALY_START_POSITION - 1] != ' ') return false;
        if (rStrLine[TLE_FREQUENCY_START_POSITION - 1] != ' ') return false;

        return true;
    }

    static bool IsNoradNumValid(std::string &rStrLine)
    {
        if (!_IsDigitField(rStrLine, TLE_ID_START_POSITION, TLE_ID_FINISH_POSITION - 1)) return false;
        return true;
    }

    static bool IsClassValid(std::string &rStrLine)
    {
        return true;
    }

    static bool IsLaunchYearValid(std::string &rStrLine)
    {
        if (!_IsDigitField(rStrLine, TLE_LAUNCH_YEAR_START_POSITION, TLE_LAUNCH_YEAR_FINISH_POSITION - 1)) return false;
        return true;
    }

    static bool IsLaunchNumValid(std::string &rStrLine)
    {
        if (!_IsDigitField(rStrLine, TLE_LAUNCH_DATA_START_POSITION, TLE_LAUNCH_DATA_FINISH_POSITION - 1)) return false;
        return true;
    }

    static bool IsLaunchPartValid(std::string &rStrLine)
    {
        if (!_IsRightWhitespacedField(rStrLine, TLE_LAUNCH_TYPE_START_POSITION, TLE_LAUNCH_TYPE_FINISH_POSITION - 1)) return false;
        return true;
    }

    static bool IsEpochYearValid(std::string &rStrLine)
    {
        if (!_IsDigitField(rStrLine, TLE_ERA_START_POSITION, TLE_ERA_FINISH_POSITION - 1)) return false;
        return true;
    }

    static bool IsEpochTimeValid(std::string &rStrLine)
    {
        if (!_IsRealField(rStrLine, TLE_ERA_TYPE_START_POSITION, TLE_ERA_TYPE_FINISH_POSITION - 1, 3)) return false;
        return true;
    }

    static bool IsAccelerationValid(std::string &rStrLine)
    {
        if (!_IsPosNegChar(rStrLine, TLE_FIRST_DERIVATIVE_START_POSITION)) return false;
        if (!_IsRealField(rStrLine, TLE_FIRST_DERIVATIVE_START_POSITION + 1, TLE_FIRST_DERIVATIVE_FINISH_POSITION - 1, 0)) return false;
        return true;
    }

    static bool IsVelocitySecondDiffValid(std::string &rStrLine)
    {
        if (!_IsPosNegChar(rStrLine, TLE_SECOND_DERIVATIVE_START_POSITION)) return false;
        if (!_IsRealExpField(rStrLine, TLE_SECOND_DERIVATIVE_START_POSITION + 1, TLE_SECOND_DERIVATIVE_FINISH_POSITION - 1, 5)) return false;
        return true;
    }

    static bool IsBrakeKoefValid(std::string &rStrLine)
    {
        if (!_IsPosNegChar(rStrLine, TLE_FLOW_TYPE_START_POSITION)) return false;
        if (!_IsRealExpField(rStrLine, TLE_FLOW_TYPE_START_POSITION + 1, TLE_FLOW_TYPE_FINISH_POSITION - 1, 5)) return false;
        return true;
    }

    static bool IsEpherimidTypeValid(std::string &rStrLine)
    {
        if (rStrLine[TLE_FLOW_TYPE_FINISH_POSITION + 1] != '0') return false;
        return true;
    }

    static bool IsVersionValid(std::string &rStrLine)
    {
        if (!_IsLeftWhitespacedDigitField(rStrLine, TLE_NUM_TYPE_START_POSITION, TLE_NUM_TYPE_FINISH_POSITION - 1)) return false;
        return true;
    }

    static bool IsInclinationValid(std::string &rStrLine)
    {
        if (!_IsLeftWhitespacedDigitField(rStrLine, TLE_INCLINATION_START_POSITION, TLE_INCLINATION_START_POSITION + 2)) return false;
        if (!_IsRealField(rStrLine, TLE_INCLINATION_START_POSITION + 3, TLE_INCLINATION_FINISH_POSITION - 1, 0)) return false;
        return true;
    }

    static bool IsAscDegreeValid(std::string &rStrLine)
    {
        if (!_IsLeftWhitespacedDigitField(rStrLine, TLE_INCLINATION_TO_THE_RIGHT_START_POSITION, TLE_INCLINATION_TO_THE_RIGHT_START_POSITION + 2)) return false;
        if (!_IsRealField(rStrLine, TLE_INCLINATION_TO_THE_RIGHT_START_POSITION + 3, TLE_INCLINATION_TO_THE_RIGHT_FINISH_POSITION - 1, 0)) return false;
        return true;
    }

    static bool IsEccentricityValid(std::string &rStrLine)
    {
        if (!_IsDigitField(rStrLine, TLE_EXCENTRICITY_START_POSITION, TLE_EXCENTRICITY_FINISH_POSITION - 1)) return false;
        return true;
    }

    static bool IsPercentArgValid(std::string &rStrLine)
    {
        if (!_IsLeftWhitespacedDigitField(rStrLine, TLE_PERIGEE_START_POSITION, TLE_PERIGEE_START_POSITION + 2)) return false;
        if (!_IsRealField(rStrLine, TLE_PERIGEE_START_POSITION + 3, TLE_PERIGEE_FINISH_POSITION - 1, 0)) return false;
        return true;
    }

    static bool IsMidAnomalityValid(std::string &rStrLine)
    {
        if (!_IsLeftWhitespacedDigitField(rStrLine, TLE_MEAN_ANOMALY_START_POSITION, TLE_MEAN_ANOMALY_START_POSITION + 2)) return false;
        if (!_IsRealField(rStrLine, TLE_MEAN_ANOMALY_START_POSITION + 3, TLE_MEAN_ANOMALY_FINISH_POSITION - 1, 0)) return false;
        return true;
    }

    static bool IsPeriodFreqValid(std::string &rStrLine)
    {
        if (!_IsLeftWhitespacedDigitField(rStrLine, TLE_FREQUENCY_START_POSITION, TLE_FREQUENCY_START_POSITION + 1)) return false;
        if (!_IsRealField(rStrLine, TLE_FREQUENCY_START_POSITION + 2, TLE_FREQUENCY_FINISH_POSITION - 1, 0)) return false;
        return true;
    }

    static bool IsPeriodAmntValid(std::string &rStrLine)
    {
        if (!_IsLeftWhitespacedDigitField(rStrLine, TLE_ERA_NUM_START_POSITION, TLE_ERA_NUM_FINISH_POSITION)) return false;
        if (!_IsRealField(rStrLine, TLE_FREQUENCY_START_POSITION + 2, TLE_FREQUENCY_FINISH_POSITION - 1, 0)) return false;
        return true;
    }

    static bool IsControllSumValid(std::string &rStrLine)
    {
        if (!_IsDigitField(rStrLine, TLE_CHECK_SUM_START_AND_FINISH_POSITION, TLE_CHECK_SUM_START_AND_FINISH_POSITION)) return false;
        if (rStrLine[TLE_CHECK_SUM_START_AND_FINISH_POSITION] != cCheckSum(rStrLine)) return false;
        return true;
    }

private:
    static bool _IsDigitField(std::string &rStrLine, int nStart, int nEnd)
    {
        for (int i = nStart; i <= nEnd; i++)
        {
            if (!isdigit(rStrLine[i])) return false;
        }

        return true;
    }

    static bool _IsRightWhitespacedField(std::string &rStrLine, int nStart, int nEnd)
    {
        bool whitespace_started = false;

        for (int i = nStart; i <= nEnd; i++)
        {
            if (rStrLine[i] == ' ' && !whitespace_started) whitespace_started = true;
            else if (rStrLine[i] != ' ' && whitespace_started) return false;
        }

        return true;
    }

    static bool _IsLeftWhitespacedDigitField(std::string &rStrLine, int nStart, int nEnd)
    {
        //  т.к. хоть одна цифра быть должна
        if (!isdigit(rStrLine[nEnd])) return false;

        for (int i = nStart; i <= nEnd-1; i++)
        {
            if (rStrLine[i] != ' ') return _IsDigitField(rStrLine, i, nEnd);
        }

        return true;
    }

    static bool _IsRealField(std::string &rStrLine, int nStart, int nEnd, int nBeforePoint)
    {
        if (!_IsDigitField(rStrLine, nStart, nStart + nBeforePoint - 1)) return false;

        if (rStrLine[nStart + nBeforePoint] != '.') return false;

        if (!_IsDigitField(rStrLine, nStart + nBeforePoint + 1, nEnd)) return false;

        return true;
    }

    static bool _IsPosNegChar(std::string &rStrLine, int nPos)
    {
        if (rStrLine[nPos] == '+' || rStrLine[nPos] == ' ' || rStrLine[nPos] == '-') return true;
        else return false;
    }

    static bool _IsRealExpField(std::string &rStrLine, int nStart, int nEnd, int nBeforePosNegChar)
    {
        if (!_IsDigitField(rStrLine, nStart, nStart + nBeforePosNegChar - 1)) return false;

        if (!_IsPosNegChar(rStrLine, nStart + nBeforePosNegChar)) return false;

        if (!_IsDigitField(rStrLine, nStart + nBeforePosNegChar + 1, nEnd)) return false;

        return true;
    }

    static char cCheckSum(const std::string& str)
    {
        // The length is "- 1" because we don't include the current (existing)
        // checksum character in the checksum calculation.
        size_t len = str.size() - 1;
        int xsum = 0;

        for (size_t i = 0; i < len; i++)
        {
            char ch = str[i];

            if (isdigit(ch))
            {
                xsum += (ch - '0');
            }
            else if (ch == '-')
            {
                xsum++;
            }
        }

        return char((xsum % 10) + 48);
    }
};
