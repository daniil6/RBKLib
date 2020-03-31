#include <stdint.h>

enum CheckError : uint8_t {
    SUCCESS = 0,        /*!< Успех*/
    ERRORS,             /*!< Ошибка*/
    SIGN_BRACKET_CLOSE, /*!< После знака идет закрывающаяся скобка*/
    SIGN_END,           /*!< Знак стоит в конце формулы*/
    SIGN_SIGN,          /*!< После знака идет знак*/
    BRACKET_OPEN_BRACKET_CLOSE, /*!< После открывающейся скобки идет закрывающаяся скобка*/
    BRACKET_OPEN_SIGN, /*!< После открывающейся скобки идет неправильный знак*/
    EMPTY_BRACKET_CLOSE, /*!< Вначале не может идти закрывающаяся скобка*/
    EMPTY_SIGN,          /*!< Вначеле не может идти неправильный знак*/
    POINT_BRACKET_OPEN,  /*!< После точки идет открывающаяся скобка*/
    POINT_BRACKET_CLOSE, /*!< После точки идет закрывающаяся скобка*/
    POINT_END,           /*!< точка стоит в конце формулы*/
    POINT_SIGN           /*!< После точки идет знак*/
};

enum CheckStatus : uint8_t { EMPTY = 0, SIGN, SYMBOL, BRACKET_OPEN, POINT };

CheckError SignFullError(const char* inStr);
CheckError SignCompactError(const char* inStr);