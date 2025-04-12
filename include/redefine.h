#pragma once

class CRedefine
{
private:
    double x;
    double y;

public:
    CRedefine() = default;
    ~CRedefine() = default;

    CRedefine& operator=(const CRedefine& obj);

    bool operator==(const CRedefine& obj);

    bool operator!=(const CRedefine& obj);
};