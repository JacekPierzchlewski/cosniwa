#
# example2.py [version 1.0]
# CoSniWa:  COde SNIppet stopWAtch [Python port] - example 2
#
# Example2:  Two code snippets.
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

    csw.call_start(2)   # Start code snippet (loop)
    for inxAdd in range(100):
        csw.call_start(1)    # Start code snippet (add)
        add(1, 100000)
        csw.call_stop(1)     # Stop code snippet (add)
    csw.call_stop(2)   # Stop code snippet (loop)

    # Print the results
    csw.resultc()


if __name__ == '__main__':
    main()
