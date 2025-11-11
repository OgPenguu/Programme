#include "globals.h"

ImVec2 globals::GetCursorPosition()
{
    ImVec2 out{};

    POINT p;
    GetCursorPos(&p);
    out.x = (float)p.x;
    out.y = (float)p.y;

    return out;
}
