#include "../inc/Utils.h"
#include <cmath>
#include <iostream>
#include <regex>

using namespace std;

bool Utils::check_StrIsNum(string s)
{
    for (long unsigned int i = 0; i < s.size(); i++)
    {
        if (isdigit(s.at(i)) == false && s.at(i) != '.')
        {
            return false;
        }
    }

    return true;
}

void Utils::remove_Spaces(std::string &s) {
    regex r("[ ]+");

    s = regex_replace(s, r, "");
    // cout<< "removed spaces: "+s<<endl;
}

std::string Utils::getFileNameWithoutExtension(const std::string filePath) {
    // Find the last path separator (handles both Linux and Windows paths)
    size_t lastSlashPos = filePath.find_last_of("/\\");
    
    // Extract the file name with extension
    std::string fileName = (lastSlashPos == std::string::npos) ? filePath : filePath.substr(lastSlashPos + 1);
    
    // Find the last dot (.)
    size_t lastDotPos = fileName.find_last_of('.');
    
    // Remove the extension if a dot is found
    if (lastDotPos != std::string::npos) {
        fileName = fileName.substr(0, lastDotPos);
    }
    
    return fileName;
}





bool Utils::stringBinary(string str) {


    if (!str.empty() && str.back() == 'b') {
        str.pop_back();
    }



    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] != '1' && str[i] != '0')
            return false;
    }
    return true;
}

int Utils::BinToDec(int BinaryBits)
{
    int dec = 0, i = 0, rem;
    while (BinaryBits != 0)
    {
        rem = BinaryBits % 10;
        dec = dec + rem * pow(2, i);
        i++;
        BinaryBits = BinaryBits / 10;
    }
    cout << dec;
    return dec;
}

bool Utils::validateHexInput(string hexValue) {
    return hexValue.find_first_not_of("0123456789ABCDEFabcdef") == std::string::npos;
}

int Utils::hexToDec(string hexValue) {
    int dec = 0, base = 1;
    for (auto it = hexValue.rbegin(); it != hexValue.rend(); ++it) {
        if (*it >= '0' && *it <= '9')
            dec += (*it - '0') * base;
        else if (*it >= 'A' && *it <= 'F')
            dec += (*it - 'A' + 10) * base;
        base *= 16;
    }
    return dec;
}

bool Utils::check_Substring(string s2, string s1)
{
    int counter = 0; // pointing s2
    int i = 0;
    for (; i < s1.length(); i++)
    {
        if (counter == s2.length())
            break;
        if (s2[counter] == s1[i])
        {
            counter++;
        }
        else
        {
            // Special case where character preceding the i'th character is duplicate
            if (counter > 0)
            {
                i -= counter;
            }
            counter = 0;
        }
    }
    return counter < s2.length() ? 0 : 1;
}

