/*
 * case1.cpp [version 1.0]
 * CoSniWa:  COde SNIppet stopWAtch - case 1
 *
 * case1:  Test usleep() function using Cosniwa
 *
 * read more on: www.speedupcode.com
 *
 * (c) Jacek Pierzchlewski, 2017  jacek@pierzchlewski.com
 * license: BSD-2-Clause.
 */
#include <unistd.h>
#include "cosniwa.h"


void test_usleep(int ius, int iRego, Cosniwa* csw)
{
/*
 *  test_usleep:  TEST 'usleep()' by calling it 1000 times
 *
 *  Parameters:
 *   ius:    [int]       Argument for usleep() function
 *   iRego:  [int]       Cosniwa registration for the current test
 *   csw:    [Cosniwa*]  Pointer to Cosniwa class
 *
 */

    // Call usleep() function 1000 times
    for (int inxCall=0; inxCall < 1000; inxCall++)
    {
        csw->call_start(iRego);
        usleep(ius);
        csw->call_stop(iRego);
    }
}


int main()
{
    // Create Cosniwa object
    Cosniwa csw = Cosniwa();

    // Test usleep with arguments 1 [us] - 9 [us]
    test_usleep(1, csw.reg_code("Test on usleep(1) [1us] "), &csw);
    test_usleep(2, csw.reg_code("Test on usleep(2) [2us] "), &csw);
    test_usleep(3, csw.reg_code("Test on usleep(3) [3us] "), &csw);
    test_usleep(4, csw.reg_code("Test on usleep(4) [4us] "), &csw);
    test_usleep(5, csw.reg_code("Test on usleep(5) [5us] "), &csw);
    test_usleep(6, csw.reg_code("Test on usleep(6) [6us] "), &csw);
    test_usleep(7, csw.reg_code("Test on usleep(7) [7us] "), &csw);
    test_usleep(8, csw.reg_code("Test on usleep(8) [8us] "), &csw);
    test_usleep(9, csw.reg_code("Test on usleep(9) [9us] "), &csw);

    // Test usleep with arguments  10 [us] - 90 [us]
    test_usleep(10, csw.reg_code("Test on usleep(10) [10us] "), &csw);
    test_usleep(20, csw.reg_code("Test on usleep(20) [20us] "), &csw);
    test_usleep(30, csw.reg_code("Test on usleep(30) [30us] "), &csw);
    test_usleep(40, csw.reg_code("Test on usleep(40) [40us] "), &csw);
    test_usleep(50, csw.reg_code("Test on usleep(50) [50us] "), &csw);
    test_usleep(60, csw.reg_code("Test on usleep(60) [60us] "), &csw);
    test_usleep(70, csw.reg_code("Test on usleep(70) [70us] "), &csw);
    test_usleep(80, csw.reg_code("Test on usleep(80) [80us] "), &csw);
    test_usleep(90, csw.reg_code("Test on usleep(90) [90us] "), &csw);

    // Test usleep with arguments  100 [us] - 900 [us]
    test_usleep(100, csw.reg_code("Test on usleep(100) [100us] "), &csw);
    test_usleep(200, csw.reg_code("Test on usleep(200) [200us] "), &csw);
    test_usleep(300, csw.reg_code("Test on usleep(300) [300us] "), &csw);
    test_usleep(400, csw.reg_code("Test on usleep(400) [400us] "), &csw);
    test_usleep(500, csw.reg_code("Test on usleep(500) [500us] "), &csw);
    test_usleep(600, csw.reg_code("Test on usleep(600) [600us] "), &csw);
    test_usleep(700, csw.reg_code("Test on usleep(700) [700us] "), &csw);
    test_usleep(800, csw.reg_code("Test on usleep(800) [800us] "), &csw);
    test_usleep(900, csw.reg_code("Test on usleep(900) [900us] "), &csw);

    // Test usleep with arguments  1 [ms] - 9 [ms]
    test_usleep(1000, csw.reg_code("Test on usleep(1000) [1ms] "), &csw);
    test_usleep(2000, csw.reg_code("Test on usleep(2000) [2ms] "), &csw);
    test_usleep(3000, csw.reg_code("Test on usleep(3000) [3ms] "), &csw);
    test_usleep(4000, csw.reg_code("Test on usleep(4000) [4ms] "), &csw);
    test_usleep(5000, csw.reg_code("Test on usleep(5000) [5ms] "), &csw);
    test_usleep(6000, csw.reg_code("Test on usleep(6000) [6ms] "), &csw);
    test_usleep(7000, csw.reg_code("Test on usleep(7000) [7ms] "), &csw);
    test_usleep(8000, csw.reg_code("Test on usleep(8000) [8ms] "), &csw);
    test_usleep(9000, csw.reg_code("Test on usleep(9000) [9ms] "), &csw);

    // Print out the timing results
    csw.resultc();
}
