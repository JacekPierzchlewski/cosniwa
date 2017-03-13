#
# example4.py [version 1.0]
# CoSniWa:  COde SNIppet stopWAtch [Python port] - example 4
#
# Example4:  Add main time
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


def add(iA, iB):
    """
    Add iA + iB in a slow way.
    """
    for i in range(iB):
        iA = iA + 1


def main():

    # Register the code snippets
    iRego1 = csw.reg_code("add(1, 100000)")
    iRego2 = csw.reg_code("100 x add(1, 100000)")
    iRego3 = csw.reg_code("add(1, 10000)")
    iRego4 = csw.reg_code("100 x add(1, 10000)")

    # Start the main CoSniWa time
    csw.start()

    csw.call_start(iRego2)   # Start loop 100 x add(1, 100000)
    for inxAdd in range(100):
        csw.call_start(iRego1)   # Start code snippet (add(1, 100000))
        add(1, 100000)
        csw.call_stop(iRego1)    # Stop code snippet (add(1, 100000))
    csw.call_stop(iRego2)  # Stop loop 100 x add(1, 100000)

    csw.call_start(iRego4)   # Start loop 100 x add(1, 10000)
    for inxAdd in range(100):
        csw.call_start(iRego3)   # Start code snippet (add(1, 10000))
        add(1, 10000)
        csw.call_stop(iRego3)    # Stop code snippet (add(1, 10000))
    csw.call_stop(iRego4)  # Stop loop 100 x add(1, 10000)

    # Stop the main CoSniWa time
    csw.stop()

    # Print the results
    csw.resultc()


if __name__ == '__main__':
    main()
