#include "redefine.h"

CRedefine& CRedefine::operator=(const CRedefine& obj)
{
    if(this != &obj) {

        this->x = obj.x;
        this->y = obj.y;
    }

    return *this;
}

bool CRedefine::operator==(const CRedefine& obj)
{
    if(this != &obj) {
        if(this->x == obj.x || this->y == obj.y) {
            return true;
        }
    }

    return false;
}

bool CRedefine::operator!=(const CRedefine& obj)
{
    if(this != &obj) {
        if(this->x != obj.x || this->y != obj.y) {
            return true;
        }
    }

    return false;
}