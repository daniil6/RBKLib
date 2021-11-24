bool SubSearchMass(const char in[], const char sub[])
{
    int i(0), j(0);
    while(in[i] != '\0') {
        if(in[i++] == sub[j++]) {
            if(sub[j] == '\0')
                return true;
        } else
            j = 0;
    }
    return false;
}

bool SubSearchPoint(const char* in, const char* sub)
{
    char* t_sub = const_cast<char*>(sub);
    while(*in != '\0') {
        if(*in++ == *t_sub++) {
            if(*t_sub == '\0')
                return true;
        } else
            t_sub = const_cast<char*>(sub);
    }
    return false;
}

int SearchLinear(const int in[], const int size, const int target)
{
    for(int i = 0; i < size; i++) {
        if(in[i] == target)
            return i;

        // Проверка, пройдена возможная позиция целевого элемента (Для сортированного массива)
        if(in[i] > target)
            return -1;
    }
    // В массиве нет необходимого элемента
    return -1;
}

int searchThread(const char* dataThread, const int& sizeThread, const char* dataTarget, const int& sizeTarget)
{
    int offset(0), i(0), j(0);
    int searchEnd = sizeThread - sizeTarget;

    if(searchEnd < 0)
        return -1;

    while(offset <= searchEnd) {

        while(dataThread[i++] == dataTarget[j++])
            if(j == sizeTarget)
                return i;

        i = ++offset;
        j = 0;
    }

    return -1;
}