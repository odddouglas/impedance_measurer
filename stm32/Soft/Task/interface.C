#include "interface.H"

void FormatRsDisStr(float Rs, char str[])
{
    if (Rs > 1000000)
    {
        sprintf(str, "%03.03fM次  ", Rs / 1000000);
    }
    else if (Rs > 1000)
    {
        sprintf(str, "%03.03fK次  ", Rs / 1000);
    }
    else if (Rs < 1000)
    {
        sprintf(str, "%03.03f次  ", Rs);
    }
    ////	sprintf(str,"%08.0f次  ",Rs);
}
