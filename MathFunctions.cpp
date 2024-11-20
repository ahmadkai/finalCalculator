#include "../inc/MathFunctions.h"
#include "../inc/constants.h"
#include "../inc/Utils.h"
#include <cmath>
#include <iostream>
#include <regex> 
#include <string> 
#include <cstring>

std::unordered_map<std::string, double> variables;  // Definition of 'variables' map

using namespace std;

double add(double val1, double val2) { return val1 + val2; }
double subtract(double val1, double val2) { return val1 - val2; }
double multiply(double val1, double val2) { return val1 * val2; }
double divide(double val1, double val2) {
    if (val2 == 0) {
        std::cerr << "Error: Division by zero. Returning NaN." << std::endl;
        return std::numeric_limits<double>::quiet_NaN();
    }
    return val1 / val2;
}
double exponent(double val1, double val2) { 
    
    return pow(val1, val2); 
    }

// Additional math operations and functions...

double getVarMath(std::string my_Var) {
    if (variables.find(my_Var) != variables.end()) {
        return variables[my_Var];
    }
    else {
        throw string("ERROR: Invalid Input or Function/Variable not found."+my_Var);
        // return std::numeric_limits<double>::quiet_NaN();
    }
}


// Function to validate Hexadecimal input data
bool validateHex_Input(string hex_Value)
{
    string chars = "0x";
    for (char c : chars)
    {
        hex_Value.erase(remove(hex_Value.begin(), hex_Value.end(), c), hex_Value.end());
    }

    bool result = false;
    int len = hex_Value.size();
    if (len < 1)
    {
        cout << "Empty input?\n";
        result = false;
    }
    else
    {
        result = true;
    }

    // now validate every symbol of the line
    for (int i = 0; i < len; i++)
    {
        // convert to uppercase for further operation with uppercase
        hex_Value[i] = toupper(hex_Value[i]);

        if (!(((floor(hex_Value[i]) == ceil(hex_Value[i]))      // check if is integer
               && (hex_Value[i] >= '0' && hex_Value[i] <= '9')) // if is integer, check value
              || ((isalpha(hex_Value[i]))                      // if is a latin letter
                  && (hex_Value[i] >= 'A' && hex_Value[i] <= 'F'))))
        {
            // check that it is A-F

            result = false;
            break;
        }
    }

    return result;
}


// A function to remove "b" and '0x' from input string
void string_Filter(char *str)
{
    int n = strlen(str);

    int i = -1; // previous character
    int j = 0;  // current character

    while (j < n)
    {
        // check if current and next character forms ac
        if (j < n - 1 && str[j] == '0' && str[j + 1] == 'x')
            j += 2;

        // if current character is b
        else if (str[j] == 'b')
            j++;

        // if current char is 'c && last char in output is 'a' so delete both
        else if (i >= 0 && str[j] == 'x' && str[i] == '0')
            i--, j++;

        // else copy curr char to output string
        else
            str[++i] = str[j++];
    }
    str[++i] = '\0';
}

double sinDegSolv(double f)
{
    return sin((f * PI) / 180.0);
}

double sinRadSolv(double f)
{
    return sin(f);
}

double asinDegSolv(double f)
{
    return (asin(f) * 180.0) / PI;
}

double asinRadSolv(double f)
{
    return asin(f);
}

// Functions for solving cosine
double cosFunc(double f)
{
    return cos((f * PI) / 180.0);
}

double cosRadSolv(double f)
{
    return cos(f);
}

double acosDegSolv(double f)
{
    return (acos(f) * 180.0) / PI;
}

double acosRadSolv(double f)
{
    return acos(f);
}