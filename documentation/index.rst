.. Cosniwa documentation master file, created by
   sphinx-quickstart on Thu Mar  2 21:33:52 2017.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

===================================
Welcome to Cosniwa's documentation!
===================================

.. contents:: :local:

1. About *Cosniwa*
===================================
*Cosniwa* [(Co)de (sni)ppet stop(wa)tch] is a tool for profiling code using timestamps.
*Cosniwa* uses timestamps, so you CAN NOT expect nanosecond precision,
but it is precise enough for most of the applications.

Read more on `www.speedupcode.com  <http://www.speedupcode.com>`_.


1.1 Platforms
+++++++++++++++++++++++++++++++++++
1. *Cosniwa* is officially supported on LINUX and MAC.
2. It is planned to add support for WINDOWS in the near future.


1.2 Languages
+++++++++++++++++++++++++++++++++++
Currently (mid 2017) *Cosniwa* can be used with the following languages:

    **1. C++**.  The first version of *Cosniwa* was written in C++.
    *Cosniwa* can be used with both GCC and Clang compilers. Timing precision
    below 10 us can be expected. |br|

    **2. Python 3.** *Cosniwa* can be used with CPython interpreter
    for Python 3. *Cosniwa* Python3 port uses *Cosniwa* C++ modules
    via the Python-to-C++ interface provided by CPython. Timing
    precision below 10 us can be expected.  |br|

    **3. Octave.** *Cosniwa* can be used with GNU Octave. There are two
    versions of *Cosniwa* prepared for Octave: |br|

            - **C++ based**.  This version uses *Cosniwa* C++ modules via GNU Octave interface for modules written in C++. It is a recommended version which ensures highest possible timing precision (below 10 us). |br| |br|

            - **Native**. This version uses GNU Octave functions to obtain timestamps. It should be used if modules written in C++ can not be used. Worse timing precision than for C++ modules can be expected, below 100 us.  |br|





1.3 License
+++++++++++++++++++++++++++++++++++
*Cosniwa* is (very) free software, it is licensed under BSD 2-clause license.


1.4 Author
+++++++++++++++++++++++++++++++++++
*Cosniwa* v1.0 is written by Jacek Pierzchlewski
(`http://pierzchlewski.com <http://www.pierzchlewski.com/>`_) |br|
email: jacek@pierzchlewski.com

1.5 Download
+++++++++++++++++++++++++++++++++++
*Cosniwa* repository is hosted on `github.com  <https://github.com/jacekpierzchlewski/cosniwa/>`_.

Download *Cosniwa* `zipped <http://www.speedupcode.com/cosniwa/download/cosniwa-1.0.zip>`_ or `as tar ball <http://www.speedupcode.com/cosniwa/download/cosniwa-1.0.tar.bz2>`_.


You can also download the zipped package
`from Github <https://github.com/jacekpierzchlewski/cosniwa/archive/master.zip>`_.



.. include:: ./cpp.rst
.. include:: ./python.rst
.. include:: ./octave.rst



Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`


.. |br| raw:: html

   <br />

.. |space| raw:: html

   &nbsp
