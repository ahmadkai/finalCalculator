#include <cmath>
#include "../inc/Constants.h"
#include "../inc/Trig.h"

using namespace TrigRatio;

double Trig::sinDegSolv(double f)
{
    return sin((f * PI) / 180.0);
}

double Trig::sinRadSolv(double f)
{
    return sin(f);
}

double Trig::asinDegSolv(double f)
{
    return (asin(f) * 180.0) / PI;
}

double Trig::asinRadSolv(double f)
{
    return asin(f);
}

// Functions for solving cosine
double Trig::cosFunc(double f)
{
    return cos((f * PI) / 180.0);
}

double Trig::cosRadSolv(double f)
{
    return cos(f);
}

double Trig::acosDegSolv(double f)
{
    return (acos(f) * 180.0) / PI;
}

double Trig::acosRadSolv(double f)
{
    return acos(f);
}
