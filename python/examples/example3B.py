#
# example3B.py [version 1.0]
# CoSniWa:  COde SNIppet stopWAtch [Python port] - example 3B
#
# Example3B:  Code registration (version B)
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


def add(iA, iB):
    """
    Add iA + iB in a slow way.
    """
    for i in range(iB):
        iA = iA + 1


def main():

    csw.call_start(csw.reg_code("100 x add"))  # Start code snippet (loop)
    for inxAdd in range(100):
        csw.call_start(csw.reg_code("add"))    # Start code snippet (add)
        add(1, 100000)
        csw.call_stop(csw.reg_code("add"))     # Stop code snippet (add)
    csw.call_stop(csw.reg_code("100 x add"))   # Stop code snippet (loop)

    # Print the results
    csw.resultc()


if __name__ == '__main__':
    main()
