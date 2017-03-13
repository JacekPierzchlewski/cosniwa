/*
 * example2.cpp [version 1.0]
 * CoSniWa:  COde SNIppet stopWAtch - example 2
 *
 * Example2:  Two code snippets.
 *
 * read more on: www.speedupcode.com
 *
 * (c) Jacek Pierzchlewski, 2017  jacek@pierzchlewski.com
 * license: BSD-2-Clause.
 */
#include "cosniwa.h"


int add(int iA, int iB)
{
/*
 *  Add iA + iB in a slow way.
 */
    for(int i=0; i < iB; i++)
    {
        iA = iA + 1;
    }
    return iA;
}


int main()
{
    // Create Cosniwa object
    Cosniwa csw = Cosniwa();

    csw.call_start(2);   // Start code snippet (loop)
    for (int inxAdd = 0 ; inxAdd < 100 ; inxAdd++)
    {
        csw.call_start(1);   // Start code snippet (add)
        add(1, 100000);
        csw.call_stop(1);    // Stop code snippet (add)
    }
    csw.call_stop(2);  // Stop code snippet (loop)

    // Print the results
    csw.resultc();
}
