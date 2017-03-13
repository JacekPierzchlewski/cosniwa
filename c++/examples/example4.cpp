/*
 * example4.cpp [version 1.0]
 * CoSniWa:  COde SNIppet stopWAtch - example 4
 *
 * Example4:  Add main time
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

    // Register the code snippets
    unsigned int iRego1 = csw.reg_code("add(1, 100000)");
    unsigned int iRego2 = csw.reg_code("100 x add(1, 100000)");
    unsigned int iRego3 = csw.reg_code("add(1, 10000)");
    unsigned int iRego4 = csw.reg_code("100 x add(1, 10000)");

    // Start the main CoSniWa time
    csw.start();

    csw.call_start(iRego2);   // Start loop 100 x add(1, 100000)
    for (int inxAdd = 0 ; inxAdd < 100 ; inxAdd++)
    {
        csw.call_start(iRego1);   // Start code snippet (add(1, 100000))
        add(1, 100000);
        csw.call_stop(iRego1);    // Stop code snippet (add(1, 100000))
    }
    csw.call_stop(iRego2);   // Stop loop 100 x add(1, 100000)

    csw.call_start(iRego4);   // Start loop 100 x add(1, 10000)
    for (int inxAdd = 0 ; inxAdd < 100 ; inxAdd++)
    {
        csw.call_start(iRego3);   // Start code snippet (add(1, 10000))
        add(1, 10000);
        csw.call_stop(iRego3);    // Stop code snippet (add(1, 10000))
    }
    csw.call_stop(iRego4);  // Stop loop 100 x add(1, 10000)

    // Stop the main CoSniWa time
    csw.stop();

    /// Print the results
    csw.resultc();  // Print results
}
