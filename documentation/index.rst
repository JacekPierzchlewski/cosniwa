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
*Cosniwa* [(Co)de (sni)ppet stop(wa)tch] is a tool for profiling Python (3)
and C++ code using timestamps.
It is reasonably easy to use, it can profile multi-class,
mixed C++ / Python code.
*Cosniwa* uses timestamps, so you CAN NOT expect nanosecond precision,
but it is precise enough for most of the applications.
It is written entirely in C++ with a port to Python.

Read more on `www.speedupcode.com  <http://www.speedupcode.com>`_.


1.1 Platforms
+++++++++++++++++++++++++++++++++++
1. *Cosniwa* is officially supported on LINUX and MAC.
2. It is planned to add support for WINDOWS in the near future.


1.2 Languages
+++++++++++++++++++++++++++++++++++
*Cosniwa* can be used with C++ and with Python 3.
There is a plan to add support for C. |br|

*Cosniwa* is written in C++.

1.3 License
+++++++++++++++++++++++++++++++++++
*Cosniwa* is (very) free software, it is licensed under BSD 2-clause license.


1.4 Author
+++++++++++++++++++++++++++++++++++
*Cosniwa* v1.0 is written by Jacek Pierzchlewski
(`http://pierzchlewski.com <http://www.pierzchlewski.com/>`_) |br|
email: jacek@pierzchlewski.com

1.5 Download and install
+++++++++++++++++++++++++++++++++++
*Cosniwa* repository is hosted on `github.com  <https://github.com/jacekpierzchlewski/cosniwa/>`_.

Download *Cosniwa* `zipped <http://www.speedupcode.com/cosniwa/download/cosniwa-1.0.zip>`_ or `as tar ball <http://www.speedupcode.com/cosniwa/download/cosniwa-1.0.tar.bz2>`_.


You can also download the zipped package
`from Github <https://github.com/jacekpierzchlewski/cosniwa/archive/master.zip>`_.

After downloading run 'make install' as superuser:

:code:`# make install`  |br|





.. include:: ./tutorial.rst
.. include:: ./cases.rst
.. include:: ./functions.rst



Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`


.. |br| raw:: html

   <br />
