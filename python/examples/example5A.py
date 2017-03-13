#
# example5A.py [version 1.0]
# CoSniWa:  COde SNIppet stopWAtch [Python port] - example 5A
#
# Example5A:  Using Cosniwa with classes (versionA)
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


class Fibonacci():
    """
    'Fibonacci': Class which computes n-th element
                 of the Fibonacci sequence.
    """

    def __init__(self, iIndex_, Cosniwa_):
        """
        INITIALISATION METHOD.

        Arguments:
          iIndex_:   [int]             Index of a class
          Cosniwa_:  [Cosniwa handle]  Handle to Cosniwa object

        """

        # Store the index of the class and the handle to Cosniwa
        self.iIndex = iIndex_
        self.hCsw = Cosniwa_

        # Create a class name
        self.strName = 'Fibonacci #%d' % self.iIndex

        # Register the class in Cosniwa
        self.iCswReg = csw.xreg_code(self.hCsw, self.strName)

    def run(self, iNEl):
        """
        run:  COMPUTE THE n-TH ELEMENT OF THE FIBONACCI SEQUENCE.

         Function computes the n-th element of the Fibonacci sequence by
         iterating through all the sequence until n-th elements.
         It is preassumed that the 1st (index 0) and the 2nd (index 1)
         elements of the sequence equal 1.

          Arguments:
            iNLen:  [int]  Index of the element to be computed

          Returns:
            iFibo:  [int]  n-th element of the Fibonacci sequence
        """

        iFibo = 1
        iFiboPrev = 1
        iFiboPrevPrev = 1

        # Start the Cosniwa stopwatch
        csw.xcall_start(self.hCsw, self.iCswReg)

        # 1st and 2nd element equals 1
        if (iNEl < 2):
            return 1

        # Loop unitl n-th element
        for inxFib in range(iNEl - 2):
            iFiboPrevPrev = iFiboPrev
            iFiboPrev = iFibo
            iFibo = iFiboPrev + iFiboPrevPrev

        # Stop the Cosniwa stopwatch
        csw.xcall_stop(self.hCsw, self.iCswReg)

        return iFibo


def main():

    # Get handle to Cosniwa module
    hCsw = csw.get_handle()

    # Start the main CoSniWa time
    csw.start()

    # Generate 10 Fibonacci classes
    f0 = Fibonacci(0, hCsw)
    f1 = Fibonacci(1, hCsw)
    f2 = Fibonacci(2, hCsw)
    f3 = Fibonacci(3, hCsw)
    f4 = Fibonacci(4, hCsw)
    f5 = Fibonacci(5, hCsw)
    f6 = Fibonacci(6, hCsw)
    f7 = Fibonacci(7, hCsw)
    f8 = Fibonacci(8, hCsw)
    f9 = Fibonacci(9, hCsw)

    # Compute Fibonacci sequences with different number of elements
    f0.run(100000)
    f1.run(90000)
    f2.run(80000)
    f3.run(70000)
    f4.run(60000)
    f5.run(50000)
    f6.run(40000)
    f7.run(30000)
    f8.run(20000)
    f9.run(1000)

    # Stop the main CoSniWa time
    csw.stop()

    # Print out the timing results
    csw.resultc()


if __name__ == '__main__':
    main()
