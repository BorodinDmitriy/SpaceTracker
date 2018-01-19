#include <string>
#include <cstdio>

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

        if (rStrLine.length() != 69) return false;

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

        if (rStrLine.length() != 69) return false;

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
        if (rStrLine[1] != ' ') return false;
        if (rStrLine[8] != ' ') return false;
        if (rStrLine[17] != ' ') return false;
        if (rStrLine[32] != ' ') return false;
        if (rStrLine[43] != ' ') return false;
        if (rStrLine[52] != ' ') return false;
        if (rStrLine[61] != ' ') return false;
        if (rStrLine[63] != ' ') return false;

        return true;
    }

    static bool IsWhitespacesValidLine2(std::string &rStrLine)
    {
        if (rStrLine[1] != ' ') return false;
        if (rStrLine[7] != ' ') return false;
        if (rStrLine[16] != ' ') return false;
        if (rStrLine[25] != ' ') return false;
        if (rStrLine[33] != ' ') return false;
        if (rStrLine[42] != ' ') return false;
        if (rStrLine[51] != ' ') return false;

        return true;
    }

    static bool IsNoradNumValid(std::string &rStrLine)
    {
        if (!_IsDigitField(rStrLine, 2, 6)) return false;
        return true;
    }

    static bool IsClassValid(std::string &rStrLine)
    {
        return true;
    }

    static bool IsLaunchYearValid(std::string &rStrLine)
    {
        if (!_IsDigitField(rStrLine, 9, 10)) return false;
        return true;
    }

    static bool IsLaunchNumValid(std::string &rStrLine)
    {
        if (!_IsDigitField(rStrLine, 11, 13)) return false;
        return true;
    }

    static bool IsLaunchPartValid(std::string &rStrLine)
    {
        if (!_IsRightWhitespacedField(rStrLine, 14, 16)) return false;
        return true;
    }

    static bool IsEpochYearValid(std::string &rStrLine)
    {
        if (!_IsDigitField(rStrLine, 18, 19)) return false;
        return true;
    }

    static bool IsEpochTimeValid(std::string &rStrLine)
    {
        if (!_IsRealField(rStrLine, 20, 31, 3)) return false;
        return true;
    }

    static bool IsAccelerationValid(std::string &rStrLine)
    {
        if (!_IsPosNegChar(rStrLine, 33)) return false;
        if (!_IsRealField(rStrLine, 34, 42, 0)) return false;
        return true;
    }

    static bool IsVelocitySecondDiffValid(std::string &rStrLine)
    {
        if (!_IsPosNegChar(rStrLine, 44)) return false;
        if (!_IsRealExpField(rStrLine, 45, 51, 5)) return false;
        return true;
    }

    static bool IsBrakeKoefValid(std::string &rStrLine)
    {
        if (!_IsPosNegChar(rStrLine, 53)) return false;
        if (!_IsRealExpField(rStrLine, 54, 60, 5)) return false;
        return true;
    }

    static bool IsEpherimidTypeValid(std::string &rStrLine)
    {
        if (rStrLine[62] != '0') return false;
        return true;
    }

    static bool IsVersionValid(std::string &rStrLine)
    {
        if (!_IsLeftWhitespacedDigitField(rStrLine, 64, 67)) return false;
        return true;
    }

    static bool IsInclinationValid(std::string &rStrLine)
    {
        if (!_IsLeftWhitespacedDigitField(rStrLine, 8, 10)) return false;
        if (!_IsRealField(rStrLine, 11, 15, 0)) return false;
        return true;
    }

    static bool IsAscDegreeValid(std::string &rStrLine)
    {
        if (!_IsLeftWhitespacedDigitField(rStrLine, 17, 19)) return false;
        if (!_IsRealField(rStrLine, 20, 24, 0)) return false;
        return true;
    }

    static bool IsEccentricityValid(std::string &rStrLine)
    {
        if (!_IsDigitField(rStrLine, 26, 32)) return false;
        return true;
    }

    static bool IsPercentArgValid(std::string &rStrLine)
    {
        if (!_IsLeftWhitespacedDigitField(rStrLine, 34, 36)) return false;
        if (!_IsRealField(rStrLine, 37, 41, 0)) return false;
        return true;
    }

    static bool IsMidAnomalityValid(std::string &rStrLine)
    {
        if (!_IsLeftWhitespacedDigitField(rStrLine, 43, 45)) return false;
        if (!_IsRealField(rStrLine, 46, 50, 0)) return false;
        return true;
    }

    static bool IsPeriodFreqValid(std::string &rStrLine)
    {
        if (!_IsLeftWhitespacedDigitField(rStrLine, 52, 53)) return false;
        if (!_IsRealField(rStrLine, 54, 62, 0)) return false;
        return true;
    }

    static bool IsPeriodAmntValid(std::string &rStrLine)
    {
        if (!_IsLeftWhitespacedDigitField(rStrLine, 63, 68)) return false;
        if (!_IsRealField(rStrLine, 54, 62, 0)) return false;
        return true;
    }

    static bool IsControllSumValid(std::string &rStrLine)
    {
        if (!_IsDigitField(rStrLine, 68, 68)) return false;
        if (rStrLine[68] != cCheckSum(rStrLine)) return false;
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
