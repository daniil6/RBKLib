#include "check/sign.h"

int sign(const int& value)
{
    return value > 0 ? 1 : value < 0 ? -1 : 0;
}

CheckError SignShowFullError(const CheckStatus& status, const char& symbol)
{
    if(status == SIGN) {

        if(symbol == ')')
            return SIGN_BRACKET_CLOSE; // После знака идет закрывающаяся скобка //

        if(symbol == '\0')
            return SIGN_END; // Знак стоит в конце формулы //

        if(symbol > 0x28 && symbol < 0x30)
            return SIGN_SIGN; // После знака идет знак //
    }

    if(status == D_POINT) {

        if(symbol == '(')
            return POINT_BRACKET_OPEN; // После точки идет закрывающаяся скобка

        if(symbol == ')')
            return POINT_BRACKET_CLOSE; // После точки идет закрывающаяся скобка

        if(symbol == '\0')
            return POINT_END; // точка стоит в конце формулы

        if(symbol > 0x28 && symbol < 0x30)
            return POINT_SIGN; // После точки идет знак
    }

    if(status == BRACKET_OPEN) {

        if(symbol == ')')
            return BRACKET_OPEN_BRACKET_CLOSE; // После открывающейся скобки идет закрывающаяся скобка //

        if(symbol > 0x29 && symbol < 0x30 && symbol != '-')
            return BRACKET_OPEN_SIGN; // После открывающейся скобки идет неправильный знак //
    }

    if(status == EMPTY) {

        if(symbol == ')')
            return EMPTY_BRACKET_CLOSE; // Вначале не может идти закрывающаяся скобка //

        if(symbol > 0x29 && symbol < 0x30 && symbol != '-')
            return EMPTY_SIGN; // Вначеле не может идти неправильный знак //
    }

    return SUCCESS;
}

CheckError SignFullError(const char* inStr, int& count)
{
    char symbol = ' ';
    CheckStatus status = EMPTY;
    count = 0;

    if(inStr != nullptr) {
        while((symbol = *inStr++) != '\0') {
            count++;

            CheckError error = SignShowFullError(status, symbol);
            if(error != SUCCESS)
                return error;

            if(symbol > 0x29 && symbol < 0x30) {
                if(symbol == '.' || symbol == ',')
                    status = D_POINT;
                else
                    status = SIGN;
            } else {
                if(symbol == '(')
                    status = BRACKET_OPEN;
                else
                    status = SYMBOL;
            }
        }
    }

    if(status == SYMBOL)
        return SUCCESS;
    else
        return SIGN_END;
}

// --------------------------------------------------

CheckError SignCompactError(const char* inStr, int& count)
{
    char symbol = 0;
    CheckStatus status = EMPTY;
    count = 0;

    if(inStr != nullptr) {
        while((symbol = *inStr++) != '\0') {
            count++;

            if(status == SIGN)
                if((symbol > 0x28 && symbol < 0x30) || symbol == '\0')
                    return ERRORS;
            if(status == D_POINT)
                if((symbol > 0x27 && symbol < 0x30) || symbol == '\0')
                    return ERRORS;
            if(status == BRACKET_OPEN || status == EMPTY)
                if(symbol > 0x28 && symbol < 0x30 && symbol != '-')
                    return ERRORS;

            if(symbol > 0x29 && symbol < 0x30) {
                if(symbol == '.' || symbol == ',')
                    status = D_POINT;
                else
                    status = SIGN;
            } else {
                if(symbol == '(')
                    status = BRACKET_OPEN;
                else
                    status = SYMBOL;
            }
        }
    }

    if(status == SYMBOL)
        return SUCCESS;
    else
        return ERRORS;
}

// --------------------------------------------------

bool EndString(const char& symbol)
{
    if(symbol == '\0')
        return true;
    else
        return false;
}

bool BracketOpen(const char& symbol)
{
    if(symbol == '(')
        return true;
    else
        return false;
}

bool BracketClose(const char& symbol)
{
    if(symbol == ')')
        return true;
    else
        return false;
}

bool SignWithoutMinus(const char& symbol)
{
    if(symbol > 0x29 && symbol < 0x30 && symbol != '-')
        return true;
    else
        return false;
}

bool SignAndBracketClose(const char& symbol)
{
    if(symbol > 0x28 && symbol < 0x30)
        return true;
    else
        return false;
}