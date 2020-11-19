
/**
 * @brief Check brackets with use stack
 * @param inStr - input string
 * @param count - count error
 * @return result
 * @time 1820 ms per 100000
 */
bool BracketsStack(const char* inStr, uint8_t& count);

/**
 * @brief Check brackets with use shift
 * @param in - input string
 * @param count - count error
 * @return result
 * @time 100 ms per 100000
 */
bool BracketsBool(const char* in, int& count);

/**
 * @brief Check brackets with use counter
 * @param in - input string
 * @param countError - count error
 * @return result
 * @time 90 ms per 100000
 */
bool BracketsCount(const char* in, int& countError);