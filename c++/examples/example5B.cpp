/*
 * example5B.cpp [version 1.0]
 * CoSniWa:  COde SNIppet stopWAtch - example 5B
 *
 * Example5B:  Using Cosniwa with classes (versionB)
 *
 * read more on: www.speedupcode.com
 *
 * (c) Jacek Pierzchlewski, 2017  jacek@pierzchlewski.com
 * license: BSD-2-Clause.
 */
#include <unistd.h>
#include <sstream>
#include "cosniwa.h"


class Fibonacci
{
/*
 * 'Fibonacci': class which computes n-th element
 *              of the Fibonacci sequence.
 */
    private:
        unsigned int iIndex;  // Index which distinguish the class
        std::string strName;  // Name of the class

        Cosniwa* csw;           // Pointer to Cosniwa
        unsigned int iCSWRego;  // Registration number in Cosniwa

    public:
        Fibonacci(int, Cosniwa* );
        long unsigned int run(unsigned int);
};


Fibonacci::Fibonacci(int iIndex_, Cosniwa* csw_)
{
/*
 *  CONSTRUCTOR.
 *
 *  Parameters:
 *   iIndex_:  [int]       Index of a class
 *   csw_:     [Cosniwa*]  Pointer to Cosniwa object
 *
 */

    // Store the index of the class and the pointer to Cosniwa
    iIndex = iIndex_;
    csw = csw_;

    // Create a class name
    strName = "Fibonacci";

    // Regsiter the class in Cosniwa
    iCSWRego = csw->reg_code(strName);
}


long unsigned int Fibonacci::run(unsigned int iNLen)
{
/*
 *  run:  COMPUTE THE n-TH ELEMENT OF THE FIBONACCI SEQUENCE.
 *
 *  Function computes the n-th element of the Fibonacci sequence by
 *  iterating through all the sequence until n-th elements.
 *  It is preassumed that the 1st (index 0) and the 2nd (index 1) elements of
 *  the sequence equal 1.
 *
 *  Parameters:
 *   iNLen:  [unsigned int]  Index of the element to be computed
 *
 *  Returns:
 *   iFibo:  [long unsigned int]  n-th element of the Fibonacci sequence
 *
 */

    long unsigned int iFibo = 1;
    long unsigned int iFiboPrev = 1;
    long unsigned int iFiboPrevPrev = 1;

    // Start the Cosniwa stopwatch
    csw->call_start(iCSWRego);

    // 1st and 2nd element equals 1
    if (iNLen < 2)
    {
        return 1;
    }

    // Loop unitl n-th elements
    for (int inxFib=0 ; inxFib < (iNLen - 2) ; inxFib++)
    {
        iFiboPrevPrev = iFiboPrev;
        iFiboPrev = iFibo;

        iFibo = iFiboPrev + iFiboPrevPrev;
    }

    // Stop the Cosniwa stopwatch
    csw->call_stop(iCSWRego);

    return iFibo;
}


int main()
{
    // Create Cosniwa object
    Cosniwa csw = Cosniwa();

    // Start the main CoSniWa time
    csw.start();

    // Define 10 Fibonacci classes with indices from 0 to 9
    Fibonacci f0(0, &csw);
    Fibonacci f1(1, &csw);
    Fibonacci f2(2, &csw);
    Fibonacci f3(3, &csw);
    Fibonacci f4(4, &csw);
    Fibonacci f5(5, &csw);
    Fibonacci f6(6, &csw);
    Fibonacci f7(7, &csw);
    Fibonacci f8(8, &csw);
    Fibonacci f9(9, &csw);

    // Compute Fibonacci sequences with different number of elements
    f0.run(100000);
    f1.run(90000);
    f2.run(80000);
    f3.run(70000);
    f4.run(60000);
    f5.run(50000);
    f6.run(40000);
    f7.run(30000);
    f8.run(20000);
    f9.run(1000);

    // Stop the main CoSniWa time
    csw.stop();

    // Print out the timing results
    csw.resultc();
}
