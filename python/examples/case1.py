#
# case1.py [version 1.0]
# CoSniWa:  COde SNIppet stopWAtch [Python port] - case 1
#
# case1:  Test time.sleep() function using Cosniwa
#
# read more on: www.speedupcode.com
#
# (c) Jacek Pierzchlewski, 2017  jacek@pierzchlewski.com
# license: BSD-2-Clause.
#
try:
    import cCosniwa as csw
except ImportError:
    print("\nERROR: cCosniwa was not found! \n")
import time


def test_usleep(tSleep, iRego):

    """
    test_usleep:  TEST 'sleep()' by calling it 1000 times

    Parameters:
     ius:    [int]       Argument for sleep() function
     iRego:  [int]       Cosniwa registration for the current test
     csw:    [Cosniwa*]  Pointer to Cosniwa class
    """

    # Call sleep() function 1000 times
    for inxCall in range(1000):
        csw.call_start(iRego)
        time.sleep(tSleep)
        csw.call_stop(iRego)


def main():

    ius = 1e-6   # Definition of microsecond
    ims = 1e-6   # Definition of milisecons

    # Test usleep with arguments 1 [us] - 9 [us]
    test_usleep(1 * ius, csw.reg_code("Test on sleep(1us) "))
    test_usleep(2 * ius, csw.reg_code("Test on sleep(2us) "))
    test_usleep(3 * ius, csw.reg_code("Test on sleep(3us) "))
    test_usleep(4 * ius, csw.reg_code("Test on sleep(4us) "))
    test_usleep(5 * ius, csw.reg_code("Test on sleep(5us) "))
    test_usleep(6 * ius, csw.reg_code("Test on sleep(6us) "))
    test_usleep(7 * ius, csw.reg_code("Test on sleep(7us) "))
    test_usleep(8 * ius, csw.reg_code("Test on sleep(8us) "))
    test_usleep(9 * ius, csw.reg_code("Test on sleep(9us) "))

    # Test usleep with arguments  10 [us] - 90 [us]
    test_usleep(10 * ius, csw.reg_code("Test on sleep(10us) "))
    test_usleep(20 * ius, csw.reg_code("Test on sleep(20us) "))
    test_usleep(30 * ius, csw.reg_code("Test on sleep(30us) "))
    test_usleep(40 * ius, csw.reg_code("Test on sleep(40us) "))
    test_usleep(50 * ius, csw.reg_code("Test on sleep(50us) "))
    test_usleep(60 * ius, csw.reg_code("Test on sleep(60us) "))
    test_usleep(70 * ius, csw.reg_code("Test on sleep(70us) "))
    test_usleep(80 * ius, csw.reg_code("Test on sleep(80us) "))
    test_usleep(90 * ius, csw.reg_code("Test on sleep(90us) "))

    # Test usleep with arguments  100 [us] - 900 [us]
    test_usleep(100 * ius, csw.reg_code("Test on sleep(100us) "))
    test_usleep(200 * ius, csw.reg_code("Test on sleep(200us) "))
    test_usleep(300 * ius, csw.reg_code("Test on sleep(300us) "))
    test_usleep(400 * ius, csw.reg_code("Test on sleep(400us) "))
    test_usleep(500 * ius, csw.reg_code("Test on sleep(500us) "))
    test_usleep(600 * ius, csw.reg_code("Test on sleep(600us) "))
    test_usleep(700 * ius, csw.reg_code("Test on sleep(700us) "))
    test_usleep(800 * ius, csw.reg_code("Test on sleep(800us) "))
    test_usleep(900 * ius, csw.reg_code("Test on sleep(900us) "))

    # Test usleep with arguments  1 [ms] - 9 [ms]
    test_usleep(1 * ims, csw.reg_code("Test on sleep(1ms) "))
    test_usleep(2 * ims, csw.reg_code("Test on sleep(2ms) "))
    test_usleep(3 * ims, csw.reg_code("Test on sleep(3ms) "))
    test_usleep(4 * ims, csw.reg_code("Test on sleep(4ms) "))
    test_usleep(5 * ims, csw.reg_code("Test on sleep(5ms) "))
    test_usleep(6 * ims, csw.reg_code("Test on sleep(6ms) "))
    test_usleep(7 * ims, csw.reg_code("Test on sleep(7ms) "))
    test_usleep(8 * ims, csw.reg_code("Test on sleep(8ms) "))
    test_usleep(9 * ims, csw.reg_code("Test on sleep(9ms) "))

    # Print out the timing results
    csw.resultc()

if __name__ == '__main__':
    main()
