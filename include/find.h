/**
 * @brief Search sub string in string
 * @param in
 * @param sub
 * @time 1.000.000 = 532-549 ms | 962 ms
 * @return
 */
bool SubSearchMass(const char in[], const char sub[]);

/**
 * @brief Search sub string in string
 * @param in
 * @param sub
 * @time 1.000.000 = 515-528 ms | 915 ms
 * @return
 */
bool SubSearchPoint(const char* in, const char* sub);

int SearchLinear(const int in[], const int size, const int target);

/**
 * @brief Search string in thread
 * @param dataThread
 * @param sizeThread
 * @param dataTarget
 * @param sizeTarget
 * @time 1.000.000 = | 916 ms
 * @return next position after search -> !!! check size data thread after search!!!
 */
int searchThread(const char* dataThread, const int& sizeThread, const char* dataTarget, const int& sizeTarget);