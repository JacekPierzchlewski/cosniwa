#
# example1.py [version 1.0]
# CoSniWa:  COde SNIppet stopWAtch [Python port] - example 1
#
# Example1: The simplest example
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

    csw.call_start(1)  # Start code snippet
    add(1, 100000)
    csw.call_stop(1)   # Stop code snippet

    # Print the results
    csw.resultc()


if __name__ == '__main__':
    main()
