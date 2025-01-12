#include "Steps.h"

Steps::Steps()
{
    for (int i = 0; i < stepperNb; i++)
        steps[i] = 0;
}