/*
 * cCosniwa_py.cpp [version 1.0]
 * CoSniWa:  COde SNIppet stopWAtch module for Python
 *
 * version 1.0 ready on 9 Mar 2017
 *
 * This is CoSniWa module for Python3.
 * CoSniWa is dedicated to profile code using time stamps.
 *
 * read more on: www.speedupcode.com
 *
 * (c) Jacek Pierzchlewski, 2017  jacek@pierzchlewski.com
 * license: BSD-2-Clause.
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <iomanip>
#include <Python.h>
#include "cosniwa.h"

// Pointer to Cosniwa object
static Cosniwa* csw;


static PyObject* reg_code_with_rego_py(PyObject *self, PyObject *args)
{
/*
 *  reg_code_with_rego_py:  PYTHON INTERFACE TO REGISTER CODE SNIPPET
 *                          FUNCTION v1C (WITH GIVEN REGISTRATION NUMBER).
 *
 *  This function is a Python interface to function:
 *
 *    unsigned int Cosniwa::reg_code(char* csLabel, int iRego)
 *
 *  from cosniwa.cpp.
 *
 *  Function registers new code snippet label (csLabel) in the snippets
 *  database with a given registration number (iRego).
 *  If label already exists with a different registration, function returns 0.
 *
 *  Function returns the same number iRego in case of no errors.
 *
 *
 *  Parameters (taken from Python Parse Tuple):
 *   csLabel:  [char*]         Label for the code snippet
 *   iRego:    [unsigned int]  Requested registration number of a code snippet
 *
 *  Return (returned in Python Value):
 *   iRegoReturn:  [unsigned int]  Registration number of a code snippet.
 *                                 It is equal to parameter 'iRego' if there
 *                                 are no errors
 *
 */
    // Parameter variables
    char* csLabel;              // Label of the code snippet
    unsigned int iRego;         // Requested registration number of
                                // a code snippet

    // Returned variable
	unsigned int iRegoReturn;   // Registration number of a code snippet.

    // Get the parameters
    PyArg_ParseTuple(args, "si",&csLabel, &iRego);

    // Register the snippet
	iRegoReturn = csw->reg_code(csLabel, iRego);
    if (iRegoReturn == (unsigned int)NULL)
        iRegoReturn = 0;

    // Return
	return Py_BuildValue("I", iRegoReturn);
}


static PyObject* reg_code_py(PyObject *self, PyObject *args)
{
/*
 *  reg_code_py:  PYTHON INTERFACE TO REGISTER CODE SNIPPET FUNCTION v2C.
 *
 *
 *  This function is a Python interface to function:
 *
 *    unsigned int Cosniwa::reg_code(char* csLabel)
 *
 *  from cosniwa.cpp.
 *
 *  Function registers new code snippet label (csLabel) in the snippets
 *  database.
 *  Function returns registration number 'iRego' given to the code snippet
 *  label.
 *
 *
 *  Parameters (taken from Python Parse Tuple):
 *   csLabel:  [char*]         Label for the code snippet
 *
 *  Return (returned in Python Value):
 *   iRegoReturn:  [unsigned int]  Registration number of a code snippet.
 */
    // Parameter variable
    char* csLabel;                // Label of the code snippet

    // Returned variable
	unsigned int iRegoReturn;     // Registration number of a code snippet.

    // Get the parameter
    PyArg_ParseTuple(args, "s", &csLabel);

    // Register the snippet
	iRegoReturn = csw->reg_code(csLabel);

    // Return
	return Py_BuildValue("I", iRegoReturn);
}


static PyObject* reset_py(PyObject *self, PyObject *args)
{
/*
 *  reset_py:  PYTHON INTERFACE TO RESET THE STOPWATCH FUNCTION.
 */
    // Reset the Cosniwa stopwatch
	csw->reset();

    // Return
	return Py_BuildValue("");
}


static PyObject* start_py(PyObject *self, PyObject *args)
{
/*
 *  start_py:  PYTHON INTERFACE TO START THE MAIN TIME OF THE STOPWATCH.
 */
    // Start the main time of Cosniwa stopwatch
	csw->start();

    // Return
	return Py_BuildValue("");
}


static PyObject* stop_py(PyObject *self, PyObject *args)
{
/*
 *  stop_py:  PYTHON INTERFACE TO STOP THE MAIN TIME OF THE STOPWATCH.
 */
    // Stop the main time of Cosniwa stopwatch
	csw->stop();

    // Return
	return Py_BuildValue("");
}


static PyObject* call_start_py(PyObject *self, PyObject *args)
{
/*
 *  call_start_py:  PYTHON INTERFACE TO START A CODE SNIPPET CALL.
 *
 *  Parameters (taken from Python Parse Tuple):
 *   iRego:  [unsigned int]  Registration number of a code snippet
 *
 */
    // Parameter variable
	unsigned int iRego;    // Registration number of a code snippet

    // Get the code snippet registration
    PyArg_ParseTuple(args, "i", &iRego);

    // Start the call snippet call
	csw->call_start(iRego);

    // Return
	return Py_BuildValue("");
}


static PyObject* call_stop_py(PyObject *self, PyObject *args)
{
/*
 *  call_stop_py:  PYTHON INTERFACE TO STOP A CODE SNIPPET CALL.
 *
 *  Parameters (taken from Python Parse Tuple):
 *   iRego:  [unsigned int]  Registration number of a code snippet
 *
 */
    // Parameter variable
    unsigned int iRego;    // Registration number of a code snippet

    // Get the code snippet registration
    PyArg_ParseTuple(args, "i", &iRego);

    // Stop the call snippet call
	csw->call_stop(iRego);

    // Return
	return Py_BuildValue("");
}


static PyObject* result_py(PyObject *self, PyObject *args)
{
/*
 *  result_py:  PYTHON INTERFACE TO OBTAINING TIMING RESULTS.
 *
 *  Return (returned in Python Value):
 *    [string]  String with timing results
 */

    // Returned variable
	std::string strTimingResult;  // String with timing results

    // Get the results
	strTimingResult = csw->result();

    // Return
	return Py_BuildValue("s", strTimingResult.c_str());
}


static PyObject* resultc_py(PyObject *self, PyObject *args)
{
/*
 *  resultc_py:  PYTHON INTERFACE TO PRINTING TIMING RESULTS TO THE
 *               CONSOLE OUTPUT.
 */
    // Print timing results to the console
	csw->resultc();

    // Return
	return Py_BuildValue("");
}


static PyObject* result_short_py(PyObject *self, PyObject *args)
{
/*
 *  result_short_py:  PYTHON INTERFACE TO OBTAINING TIMING RESULTS
 *                    (SHORT VERSION).
 *
 *  Return (returned in Python Value):
 *    [string]  String with timing results
 */
    // Returned variable
	std::string strTimingResult;

    // Get timing results (short)
	strTimingResult = csw->result_short();

    // Return
	return Py_BuildValue("s", strTimingResult.c_str());
}


static PyObject* resultc_short_py(PyObject *self, PyObject *args)
{
/*
 *  resultc_short_py:  PYTHON INTERFACE TO PRINTING TIMING RESULTS
 *                     (SHORT VERSION) TO THE CONSOLE OUTPUT).
 */
    // Print timing results (short) to the console
	csw->resultc_short();

    // Return
	return Py_BuildValue("");
}


static PyObject* get_handle_py(PyObject *self, PyObject *args)
{
/*
 *  get_handle_py:  GET HANDLE TO COSNIWA CLASS FROM THE MODULE
 *
 *  Return (returned in Python Value):
 *    [PyObject]  Python capsule with a handle (C++ pointer) to Cosniwa class
 */

    // Returned variable
    PyObject* CosniwaCapsule;  // Capsule with a handle to Cosniwa

    // Create a Python capsule with a handle to Cosniwa
    CosniwaCapsule = PyCapsule_New((void *)csw, "CosniwaH", NULL);
    PyCapsule_SetPointer(CosniwaCapsule, (void *)csw);

    // Return
    return Py_BuildValue("O", CosniwaCapsule);
}


static PyObject* xreg_code_with_rego_py(PyObject *self, PyObject *args)
{
/*
 *  xreg_code_with_rego_py:  PYTHON INTERFACE TO REGISTER CODE SNIPPET
 *                           FUNCTION v1C (WITH GIVEN REGISTRATION NUMBER).
 *                           X-VERSION:  WITH A HANDLE TO AN EXTERNAL COSNIWA
 *
 *  This function is a Python interface to function:
 *
 *    unsigned int Cosniwa::reg_code(char* csLabel, int iRego)
 *
 *  from cosniwa.cpp.
 *
 *  Function registers new code snippet label (csLabel) in the snippets
 *  database with a given registration number (iRego).
 *  If label already exists with a different registration, it is an error.
 *
 *  Function returns the same number iRego in case of no errors.
 *
 *
 *  Parameters (taken from Python Parse Tuple):
 *   CosniwaCapsule:  [PyObject]  Python capsule with a handle (C++ pointer)
 *                                to Cosniwa class
 *   csLabel:  [char*]         Label for the code snippet
 *   iRego:    [unsigned int]  Registration number of a code snippet
 *
 *  Return (returned in Python Value):
 *   iRegoReturn:  [unsigned int]  Registration number of a code snippet.
 *                                 It is equal to parameter 'iRego' if there
 *                                 are no errors
 *
 */
    // Capsule with a pointer to external Cosniwa
    PyObject* CosniwaCapsule;

    // Pointer to external Cosniwa
    Cosniwa* cswExt;

    // Parameter variable
    char* strLabel;         // Label of the code snippet
    unsigned int iRego;     // Requested registration number of a code snippet

    // Returned variable
    unsigned int iRegoReturn;   // Returned code snippet registration

    // Get parameters and the pointer to external Cosniwa
    PyArg_ParseTuple(args, "OsI", &CosniwaCapsule, &strLabel, &iRego);
    cswExt = (Cosniwa*)PyCapsule_GetPointer(CosniwaCapsule, "CosniwaH");

    // Register the code in external Cosniwa
    iRegoReturn = cswExt->reg_code(strLabel, iRego);

    // Return
    return Py_BuildValue("I", iRegoReturn);
}


static PyObject* xreg_code_py(PyObject *self, PyObject *args)
{
/*
 *  xreg_code_py:  PYTHON INTERFACE TO REGISTER CODE SNIPPET FUNCTION v2C.
 *                 X-VERSION:  WITH A HANDLE TO AN EXTERNAL COSNIWA
 *
 *  This function is a Python interface to function:
 *
 *    unsigned int Cosniwa::reg_code(char* csLabel)
 *
 *  from cosniwa.cpp.
 *
 *  Function registers new code snippet label (csLabel) in the snippets
 *  database.
 *  Function returns registration number 'iRego' given to the code snippet
 *  label.
 *
 *
 *  Parameters (taken from Python Parse Tuple):
 *   CosniwaCapsule:  [PyObject]  Python capsule with a handle (C++ pointer)
 *                                to Cosniwa class
 *   csLabel:  [char*]         Label for the code snippet
 *
 *  Return (returned in Python Value):
 *   iRegoReturn:  [unsigned int]  Registration number of a code snippet.
 */
    // Capsule with a pointer to external Cosniwa
    PyObject* CosniwaCapsule;

    // Pointer to external Cosniwa
    Cosniwa* cswExt;

    // Parameter variable
    char* strLabel;            // Label of the code snippet

    // Returned variable
    unsigned int iRegoReturn;  // Returned code snippet registration

    // Get parameters and the pointer to external Cosniwa
    PyArg_ParseTuple(args, "Os", &CosniwaCapsule, &strLabel);
    cswExt = (Cosniwa*)PyCapsule_GetPointer(CosniwaCapsule, "CosniwaH");

    // Register the code in external Cosniwa
    iRegoReturn = cswExt->reg_code(strLabel);

    // Return
    return Py_BuildValue("I", iRegoReturn);
}


static PyObject* xreset_py(PyObject *self, PyObject *args)
{
/*
 *  xreset_py:  PYTHON INTERFACE TO RESET THE STOPWATCH FUNCTION.
 *              X-VERSION:  WITH A HANDLE TO AN EXTERNAL COSNIWA
 *
 */
    // Capsule with a pointer to external Cosniwa
    PyObject* CosniwaCapsule;

    // Pointer to external Cosniwa
    Cosniwa* cswExt;

    // Get the pointer to external Cosniwa
    PyArg_ParseTuple(args, "O", &CosniwaCapsule);
    cswExt = (Cosniwa*)PyCapsule_GetPointer(CosniwaCapsule, "CosniwaH");

    // Reset the external Cosniwa
    cswExt->reset();

    // Return
    return Py_BuildValue("");
}


static PyObject* xstart_py(PyObject *self, PyObject *args)
{
/*
 *  xstart_py:  PYTHON INTERFACE TO START THE MAIN TIME OF THE STOPWATCH.
 *              X-VERSION:  WITH A HANDLE TO AN EXTERNAL COSNIWA
 *
 */
    // Capsule with a pointer to external Cosniwa
    PyObject* CosniwaCapsule;

    // Pointer to external Cosniwa
    Cosniwa* cswExt;

    // Get the pointer to external Cosniwa
    PyArg_ParseTuple(args, "O", &CosniwaCapsule);
    cswExt = (Cosniwa*)PyCapsule_GetPointer(CosniwaCapsule, "CosniwaH");

    // Start the main time in the external Cosniwa
    cswExt->start();

    // Return
    return Py_BuildValue("");
}


static PyObject* xstop_py(PyObject *self, PyObject *args)
{
/*
 *  xstop_py:  PYTHON INTERFACE TO STOP THE MAIN TIME OF THE STOPWATCH.
 *             X-VERSION:  WITH A HANDLE TO AN EXTERNAL COSNIWA
 *
 */
    // Capsule with a pointer to external Cosniwa
    PyObject* CosniwaCapsule;

    // Pointer to external Cosniwa
    Cosniwa* cswExt;

    // Get the pointer to external Cosniwa
    PyArg_ParseTuple(args, "O", &CosniwaCapsule);
    cswExt = (Cosniwa*)PyCapsule_GetPointer(CosniwaCapsule, "CosniwaH");

    // Stop the main time in the external Cosniwa
    cswExt->stop();

    // Return
    return Py_BuildValue("");
}


static PyObject* xcall_start_py(PyObject *self, PyObject *args)
{
/*
 *  xcall_start_py:  PYTHON INTERFACE TO START A CODE SNIPPET CALL.
 *                   X-VERSION:  WITH A HANDLE TO AN EXTERNAL COSNIWA
 *
 *
 *  Parameters (taken from Python Parse Tuple):
 *   iRego:  [unsigned int]  Registration number of a code snippet
 *
 */
    // Capsule with a pointer to external Cosniwa
    PyObject* CosniwaCapsule;

    // Pointer to external Cosniwa
    Cosniwa* cswExt;

    // Parameter variable
    unsigned int iRego;        // Registration number of a code snippet

    // Get the pointer to external Cosniwa and
    // the registration number of a code snippet
    PyArg_ParseTuple(args, "Oi", &CosniwaCapsule, &iRego);
    cswExt = (Cosniwa*)PyCapsule_GetPointer(CosniwaCapsule, "CosniwaH");

    // Start a code snippet call in the external Cosniwa
    cswExt->call_start(iRego);

    // Return
    return Py_BuildValue("");
}


static PyObject* xcall_stop_py(PyObject *self, PyObject *args)
{
/*
 *  xcall_stop_py:  PYTHON INTERFACE TO STOP A CODE SNIPPET CALL.
 *                  X-VERSION:  WITH A HANDLE TO AN EXTERNAL COSNIWA
 *
 *
 *  Parameters (taken from Python Parse Tuple):
 *   iRego:  [unsigned int]  Registration number of a code snippet
 *
 */
    // Capsule with a pointer to external Cosniwa
    PyObject* CosniwaCapsule;

    // Pointer to external Cosniwa
    Cosniwa* cswExt;

    // Parameter variables
    unsigned int iRego;        // Registration number of a code snippet

    // Get the pointer to external Cosniwa and
    // the registration number of a code snippet
    PyArg_ParseTuple(args, "Oi", &CosniwaCapsule, &iRego);
    cswExt = (Cosniwa*)PyCapsule_GetPointer(CosniwaCapsule, "CosniwaH");

    // Stop a code snippet call in the external Cosniwa
    cswExt->call_stop(iRego);

    // Return
    return Py_BuildValue("");
}


static PyObject* xresult_py(PyObject *self, PyObject *args)
{
/*
 *  xresult_py:  PYTHON INTERFACE TO OBTAINING TIMING RESULTS.
 *               X-VERSION:  WITH A HANDLE TO AN EXTERNAL COSNIWA
 *
 *
 *  Return (returned in Python Value):
 *    [string]  String with timing results
 */

    // Capsule with a pointer to external Cosniwa
    PyObject* CosniwaCapsule;

    // Pointer to external Cosniwa
    Cosniwa* cswExt;

    // Returned variable
    std::string strTimingResult;  // String with timing results

    // Get the pointer to external Cosniwa
    PyArg_ParseTuple(args, "O", &CosniwaCapsule);
    cswExt = (Cosniwa*)PyCapsule_GetPointer(CosniwaCapsule, "CosniwaH");

    // Get timing results from external Cosniwa
    strTimingResult = cswExt->result();

    // Return
    return Py_BuildValue("s", strTimingResult.c_str());
}


static PyObject* xresultc_py(PyObject *self, PyObject *args)
{
/*
 *  xresultc_py:  PYTHON INTERFACE TO PRINTING TIMING RESULTS TO THE
 *                CONSOLE OUTPUT.
 *                X-VERSION:  WITH A HANDLE TO AN EXTERNAL COSNIWA
 *
 */
    // Capsule with a pointer to external Cosniwa
    PyObject* CosniwaCapsule;

    // Pointer to external Cosniwa
    Cosniwa* cswExt;

    // Get the pointer to external Cosniwa
    PyArg_ParseTuple(args, "O", &CosniwaCapsule);
    cswExt = (Cosniwa*)PyCapsule_GetPointer(CosniwaCapsule, "CosniwaH");

    // Print timing results from external Cosniwa
    cswExt->resultc();

    // Return
    return Py_BuildValue("");
}


static PyObject* xresult_short_py(PyObject *self, PyObject *args)
{
/*
 *  xresult_short_py:  PYTHON INTERFACE TO OBTAINING TIMING RESULTS
 *                     (SHORT VERSION).
 *                     X-VERSION:  WITH A HANDLE TO AN EXTERNAL COSNIWA
 *
 *
 *  Return (returned in Python Value):
 *    [string]  String with timing results
 */
    // Capsule with a pointer to external Cosniwa
    PyObject* CosniwaCapsule;

    // Pointer to external Cosniwa
    Cosniwa* cswExt;

    // Returned variable
    std::string strTimingResult;  // String with timing results

    // Get the pointer to external Cosniwa
    PyArg_ParseTuple(args, "O", &CosniwaCapsule);
    cswExt = (Cosniwa*)PyCapsule_GetPointer(CosniwaCapsule, "CosniwaH");

    // Get timing results (short) from external Cosniwa
    strTimingResult = cswExt->result_short();

    // Return
    return Py_BuildValue("s", strTimingResult.c_str());
}


static PyObject* xresultc_short_py(PyObject *self, PyObject *args)
{
/*
 *  xresultc_short_py:  PYTHON INTERFACE TO PRINTING TIMING RESULTS
 *                      (SHORT VERSION) TO THE CONSOLE OUTPUT).
 *                      X-VERSION:  WITH A HANDLE TO AN EXTERNAL COSNIWA
 */
    // Capsule with a pointer to external Cosniwa
    PyObject* CosniwaCapsule;

    // Pointer to external Cosniwa
    Cosniwa* cswExt;

    // Get the Python capsule with a handle to Cosniwa and registration
    PyArg_ParseTuple(args, "O", &CosniwaCapsule);
    cswExt = (Cosniwa*)PyCapsule_GetPointer(CosniwaCapsule, "CosniwaH");

    // Print timing results from external Cosniwa
    cswExt->resultc_short();

    // Return
    return Py_BuildValue("");
}


static PyMethodDef cCosniwaMethods[] =
{
/*
 *   Python methods definition
 */
    {"reg_code_with_rego", reg_code_with_rego_py, METH_VARARGS,
     "Register code snippet with a given registration number"},
    {"reg_code", reg_code_py, METH_VARARGS,
     "Register code snippet"},
    {"reset", reset_py, METH_VARARGS, "Reset the stopwatch"},
    {"start", start_py, METH_VARARGS, "Start the main time of stopwatch"},
    {"stop", stop_py, METH_VARARGS, "Stop the main time of stopwatch"},
    {"call_start",  call_start_py, METH_VARARGS, "Start a code snippet call"},
    {"call_stop",  call_stop_py, METH_VARARGS, "Stop a code snippet call"},
    {"result",  result_py, METH_VARARGS, "Get timing results"},
    {"resultc",  resultc_py, METH_VARARGS,
     "Print timing results to the console"},
    {"result_short",  result_short_py, METH_VARARGS,
     "Get timing results (short version)"},
    {"resultc_short",  resultc_short_py, METH_VARARGS,
     "Print timing results to the console (short version)"},
    {"get_handle",  get_handle_py, METH_VARARGS,
     "Get a handle to Cosniwa"},
    {"xreg_code_with_rego", xreg_code_with_rego_py, METH_VARARGS,
     "Register code snippet with a given registration number [through handle]"},
    {"xreg_code", xreg_code_py, METH_VARARGS,
     "Register code snippet [through handle]"},
    {"xreset", xreset_py, METH_VARARGS,
     "Reset the stopwatch [through handle]"},
    {"xstart", xstart_py, METH_VARARGS,
     "Start the main time of stopwatch [through handle]"},
    {"xstop", xstop_py, METH_VARARGS,
     "Stop the main time of stopwatch [through handle]"},
    {"xcall_start",  xcall_start_py, METH_VARARGS,
     "Start a code snippet call [through handle]"},
    {"xcall_stop",  xcall_stop_py, METH_VARARGS,
     "Stop a code snippet call [through handle]"},
    {"xresult",  xresult_py, METH_VARARGS,
     "Get timing results [through handle]"},
    {"xresultc",  xresultc_py, METH_VARARGS,
     "Print timing results to the console [through handle]"},
    {"xresult_short",  xresult_short_py, METH_VARARGS,
     "Get timing results (short version) [through handle]"},
    {"xresultc_short",  xresultc_short_py, METH_VARARGS,
     "Print timing results to the console (short version) [through handle]"},
    {NULL, NULL, 0, NULL}        // Protector
};


static struct PyModuleDef stCcosniwaModule =
{
/*
 *   Python module parameters
 */
   PyModuleDef_HEAD_INIT,
   "usxTest",     // name of module
   NULL,          // module documentation, may be NULL
   -1,            // size of per-interpreter state of the module

   cCosniwaMethods
};


PyMODINIT_FUNC
PyInit_cCosniwa(void)
{
/*
 *   Python module definition
 */
   csw = new Cosniwa();
   return PyModule_Create(&stCcosniwaModule);
}
