/*
 * example3A.cpp [version 1.0]
 * CoSniWa:  COde SNIppet stopWAtch - example 3A
 *
 * Example3A:  Code registration (version A)
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

    // Register code snippets
    unsigned int iRego1 = csw.reg_code("add");
    unsigned int iRego2 = csw.reg_code("100 x add");

    csw.call_start(iRego2);   // Start code snippet (loop)
    for (int inxAdd = 0 ; inxAdd < 100 ; inxAdd++)
    {
        csw.call_start(iRego1);   // Start code snippet (add)
        add(1, 100000);
        csw.call_stop(iRego1);    // Stop code snippet (add)
    }
    csw.call_stop(iRego2);  // Stop code snippet (loop)

    // Print the results
    csw.resultc();
}
