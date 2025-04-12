int array(const char* data, const int& size, const char& ch)
{
    int count = 0;
    for(; count < size; count++) {
        if(data[count] == ch) {
            return count;
        }
    }

    return -1;
}

int main()
{
	const char ch = 'o';
	const int size = 5;
	const char* data = "hello";
	
	array(data, size, ch);
	return 0;
}