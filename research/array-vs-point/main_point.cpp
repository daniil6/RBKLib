int point(const char* data, const int& size, const char& ch)
{
    int count = size;

    do {
        if(*data++ == ch)
            return size - count;
    } while(count--);

    return -1;
}

int main()
{
	const char ch = 'o';
	const int size = 5;
	const char* data = "hello";
	
	point(data, size, ch);
	return 0;
}