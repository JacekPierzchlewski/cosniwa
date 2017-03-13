#
# example3A.py [version 1.0]
# CoSniWa:  COde SNIppet stopWAtch [Python port] - example 3A
#
# Example3A:  Code registration (version A)
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

    # Register the code snippets
    iRego1 = csw.reg_code("add")
    iRego2 = csw.reg_code("100 x add")

    csw.call_start(iRego2)    # Start code snippet (loop)
    for inxAdd in range(100):
        csw.call_start(iRego1)    # Start code snippet (add)
        add(1, 100000)
        csw.call_stop(iRego1)     # Stop code snippet (add)
    csw.call_stop(iRego2)    # Stop code snippet (loop)

    # Print the results
    csw.resultc()


if __name__ == '__main__':
    main()
