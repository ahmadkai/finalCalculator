#include "../inc/SimpleCalculator.h"
#include "../inc/Constants.h"  // For constants like PI and EULER
#include "../inc/Utils.h"
#include "../inc/Trig.h"
#include <regex>
#include <chrono>
#include <thread>
#include <fstream>
#include <cstdlib>

using namespace MathOperations;
using namespace TrigRatio;

// Constructor: initializes predefined constants
SimpleCalculator::SimpleCalculator() {
    variables["pi"] = PI;
    variables["e"] = EULER;
}


// Executes operations from a specified file
bool SimpleCalculator::fileExecution(string fileName) {

    // Path to the Output folder in the parent directory
    //std::string folderName = "../Outputs";
    std::string folderName = "Outputs";

    // Create the Output directory in the parent directory
    #ifdef _WIN32
        int res = system(("mkdir \"" + folderName + "\"").c_str());
    #else
        int res = system(("mkdir -p " + folderName).c_str());
    #endif

    if (res == 0) {
        std::cout << "Folder created successfully at: " << folderName << std::endl;
    } else {
        // std::cerr << "Failed to create folder at: " << folderName << std::endl;
    }

    // Full path to the output file
    string outputFileName = Utils::getFileNameWithoutExtension(fileName);
    string outputFilePath = folderName + "/" + outputFileName;

    // if (outFile.is_open()) 
    // {
    //     outFile << "This is a test output.\n";
    //     cout << endl <<"Output file created successfully at: " << outputFilePath << endl;
    // } else {
    //     cerr << "Error: Could not create the output file at: " << outputFilePath << endl;
    //     return false;
    // }

    // Open the input file
    ifstream inputFile(fileName);
    // if (!inputFile.is_open()) {
    //     cerr << "Error opening the input file: " << fileName << endl;
    //     return false;
    // }

    // (Optional) Process the input file and write results to the output file
    // string line;
    // while (getline(inputFile, line)) {
    //     outFile << line << endl; // Copy input content to output
    // }

    // inputFile.close();
    // outFile.close();

    if (!inputFile.is_open()) {
        cerr << "Error opening the file." << endl;
        return false;
    }

    // Create and open the output file
    ofstream outFile(outputFilePath);
    // if (!outFile.is_open()) {
    //     cerr << "Error: Could not create the output file at: " << outputFilePath << endl;
    //     return false;
    // }
    
    // cout << endl <<"Output file was created successfully at: " << outputFilePath << endl;

    string line;
    double result;

    while (getline(inputFile, line)) {
        Utils::remove_Spaces(line);
        try {
            if (line == "----") {
                cout << "----" << endl;
                outFile << "----\n";
            } else if (line == "exit") {
                break;
            } else if (variableDef(line)) {
                continue;
            } else if (mathFunc(line, result)) {
                cout << result << endl;
                outFile << result << "\n";
            }
        } catch (string e) {
            cerr << e << endl;
            return false;
        }
    }

    inputFile.close();
    outFile.close();
    return true;
}

// Defines variables from an input line
bool SimpleCalculator::variableDef(string line) {
    regex mathRegex("[\\w]+[ ]?=[ ]?[^\\s]+");
    smatch match;

    if (regex_search(line, match, mathRegex)) {
        line = match[0];
        int equalsIndex = line.find("=");
        string myVar = line.substr(0, equalsIndex);
        string math = line.substr(equalsIndex + 1);
        Utils::remove_Spaces(myVar);
        double result;

        if (mathFunc(math, result)) {
            variables[myVar] = result;
            return true;
        }
    }
    return false;
}


bool SimpleCalculator::mathFunc(string math, double &result)
{
    // Loops over all of the string
    for (long unsigned int i = 0; i < math.size(); i++)
    {
        /* Check for parentheses and if they are found solve the
         math inside them and then replace the parentheses with the result
        */
        if (math.at(i) == '(')
        {
            /*
            This holds the parentheses count. A '(' increaes the cound by one
             while a ')' decreases the cound by one. When pCount equals zero you know that you
             have found the right parentheses that matches your current left parentheses.
             */
            int pCount = 1;

            // Position where the left parenteseis was found.
            int pPos = i;

            // Index to start looking for the right parentheses
            long unsigned int index = i + 1;

            // loop until either the end of the string or the right parentheses was found
            while (index < math.size() && pCount != 0)
            {
                if (math.at(index) == '(')
                {
                    pCount++;
                }
                if (math.at(index) == ')')
                {
                    pCount--;
                }
                index++;
            }

            // If the end of the string is reached and the mathching parentheses was not found then throw and error
            if (index >= math.size() && pCount != 0)
            {
                cout << "ERROR: Parentheses mismatch." << endl;
                // throw string("ERROR: Parentheses mismatch.");
            }
            else
            {
                // Extract the command inside the parentheses
                string pSub = math.substr(pPos + 1, index - pPos - 2);

                // Check if it is not blank
                if (pSub == "")
                {
                    throw string("Error: Empty parentheses.");
                }

                // Solve the math and replace the parentheses with the answer
                mathFunc(pSub, result);
                math.erase(pPos, index - pPos);
                math.insert(pPos, to_string(result));
            }
        }
    }

    // Run the mathematical operation functions
    mathOp(math, "^", BasicOperations::exponent);
    mathOp(math, "*", BasicOperations::multiply);
    mathOp(math, "/", BasicOperations::divide);
    mathOp(math, "+", BasicOperations::add);
    mathOp(math, "-", BasicOperations::subtract);

    // Run the sine Calculation Function functions
    mathFunc(math, "asinr", Trig::asinRadSolv);
    mathFunc(math, "sinr", Trig::sinRadSolv);
    mathFunc(math, "asin", Trig::asinDegSolv);
    mathFunc(math, "sin", Trig::sinDegSolv);

    // Run the cosine Calculation functions
    mathFunc(math, "acosr", Trig::acosRadSolv);
    mathFunc(math, "cosr", Trig::cosRadSolv);
    mathFunc(math, "acos", Trig::acosDegSolv);
    mathFunc(math, "cos", Trig::cosFunc);

    Utils::remove_Spaces(math);
    int binValue, decnumber;

    if (Utils::check_StrIsNum(math))
    {
        result = stof(math);

    }
    else if (Utils::stringBinary(math) && Utils::check_Substring("b", math))
    {

        math.erase(remove(math.begin(), math.end(), 'b'), math.end());

        binValue = stoi(math);
        decnumber = Utils::BinToDec(binValue);
        math = to_string(decnumber);
        result = stof(math);
    }
    else if (Utils::validateHex_Input(math) && Utils::check_Substring("0x", math))
    {

    if (math.substr(0, 2) == "0x") {
            math = math.substr(2);
        }

        decnumber = Utils::hexToDec(math);
        math = to_string(decnumber);
        result = stof(math);
    }
    else
    {
        result = SimpleCalculator::getVarMath(math);
    }

    return true;
}


// Applies a binary operation to expressions matching the given symbol
// void SimpleCalculator::mathOp(string &math, string symbol, const function<double(double, double)> &f) {
//     // Placeholder function for handling binary operations
// }

void SimpleCalculator::mathOp(string &math, string symbol, const function<double(double, double)> &f)
{
    // Make a regex to find all the instances of the operator
    smatch sm;
    regex reg("[\\w.]+[ ]?\\" + symbol + "[ ]?[\\w.]+");

    // Find and loop through all the instances
    while (regex_search(math, sm, reg))
    {
        string sub = sm[0];

        Utils::remove_Spaces(sub);

        int splitIndex = sub.find(symbol);

        // Get the data on the left and right side of the operator
        string left = sub.substr(0, splitIndex);
        string right = sub.substr(splitIndex + 1);

        double val2, val1;
        int binValue, decnumber;

        // Check if the right side is a variable and if it is access its value from one of the maps.
        if (Utils::check_StrIsNum(right))
        {
            val2 = stof(right);
        }
        else if (Utils::stringBinary(right) && Utils::check_Substring("b", right))
        {

            right.erase(remove(right.begin(), right.end(), 'b'), right.end());

            binValue = stoi(right);
            decnumber = Utils::BinToDec(binValue);
            right = to_string(decnumber);
            val2 = stof(right);
        }
        else if (Utils::validateHex_Input(right) && Utils::check_Substring("0x", right))
        {
            string chars = "0x";
            for (char c : chars)
            {
                right.erase(remove(right.begin(), right.end(), c), right.end());
            }
            decnumber = Utils::hexToDec(right);
            right = to_string(decnumber);
            val2 = stof(right);
        }
        else if (variables.find(right) != variables.end())
        {
            val2 = SimpleCalculator::getVarMath(right);
        }

        // Check if the left side is a variable and if it is access its value from one of the maps.
        if (Utils::check_StrIsNum(left))
        {

            val1 = stof(left);
        }
        else if (Utils::stringBinary(left) && Utils::check_Substring("b", left))
        {

            left.erase(remove(left.begin(), left.end(), 'b'), left.end());

            binValue = stoi(left);
            decnumber = Utils::BinToDec(binValue);
            left = to_string(decnumber);
            val1 = stof(left);
        }
        else if (Utils::validateHex_Input(left) && Utils::check_Substring("0x", left))
        {
            string chars = "0x";
            for (char c : chars)
            {
                left.erase(remove(left.begin(), left.end(), c), left.end());
            }
            decnumber = Utils::hexToDec(left);
            left = to_string(decnumber);
            val2 = stof(left);
        }
        else

        {
            val1 = SimpleCalculator::getVarMath(left);
        }

        // Solve the math for the operator using the given function
        double result = f(val1, val2);

        // Replace the operator and the values to its left and right with the answer
        int startPos = sm.position(0);
        int len = sm[0].str().size();
        math.erase(startPos, len);
        math.insert(startPos, to_string(result));
    }
}


// Applies a unary operation to expressions matching the given symbol
// void SimpleCalculator::mathFunc(string &math, string symbol, const function<double(double)> &f) {
//     // Placeholder function for handling unary operations
// }

void SimpleCalculator::mathFunc(string &math, string symbol, const function<double(double)> &f)
{
    // Create the regex that will actually find the given functio "symbol" such as sin
    smatch sm;
    regex reg(symbol + "([\\w.]+)");

    // Find all the instances of the "symbol" and loop through all of them
    while (regex_search(math, sm, reg))
    {
        string value = sm[0].str().substr(symbol.size());
        Utils::remove_Spaces(value);
        double doubleValue;

        // Check if the right side is a variable and if it is access its value from one of the maps.
        if (Utils::check_StrIsNum(value))
        {
            doubleValue = stof(value);
        }
        else if (variables.find(value) != variables.end())
        {
            doubleValue = SimpleCalculator::getVarMath(value);
        }

        // Solve for the value using the given function pointer
        double result = f(doubleValue);

        // Check and make sure the value return was not a nan.
        if (isnan(result))
        {
            throw string("ERROR: Invalid function operation");
        }

        // Repalce the operator and its value with the answer
        int startPos = sm.position(0);
        int len = sm[0].str().size();
        math.erase(startPos, len);
        math.insert(startPos, to_string(result));
    }
}

// Retrieves the value of a defined variable, returns NaN if not found
double SimpleCalculator::getVarMath(string my_Var)
{
   
    if (variables.find(my_Var) != variables.end())
    {
        return variables[my_Var];
    }
    else
    {
        return numeric_limits<double>::quiet_NaN();
    }
}

// Additional math operations and functions...

// double SimpleCalculator::getVarMath(std::string my_Var) {
//     if (variables.find(my_Var) != variables.end()) {
//         return variables[my_Var];
//     }
//     else {
//         throw string("ERROR: Invalid Input or Function/Variable not found."+my_Var);
//         // return std::numeric_limits<double>::quiet_NaN();
//     }
// }