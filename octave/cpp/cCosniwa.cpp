/*
 * cCosniwa.cpp [version 1.0]
 * CoSniWa:  COde SNIppet stopWAtch [Octave port] - interface to Cosniwa.
 *
 *
 * CoSniWa is dedicated to profile code using time stamps.
 * Cosniwa  [Octave port - C++ implementation ] v1.0, 31 May 2017.
 *
 * read more on: www.speedupcode.com
 *
 * (c) Jacek Pierzchlewski, 2017  jacek@pierzchlewski.com
 * license: BSD-2-Clause.
 *
 */
#include <octave/oct.h>
#include "cosniwa.h"

Cosniwa* hCsw;   // Pointer to the main cosniwa object


DEFUN_DLD (cCosniwa, args, nargout, "")
{
/*
 *  cCosniwa:  INTERFACE TO COSNIWA FOR OCTAVE.
 *
 *  Parameters:
 *   strFunction:  [string]   Octave function.
 *
 *    Available functions:
 *
 *       1. 'init':  Initialise Cosniwa.
 *            arguments: none
 *            return: none
 *
 *       2. 'start':  Start the main Cosniwa stopwatch
 *            arguments: none
 *            return: none
 *
 *       3. 'stop':   Stop the main Cosniwa stopwatch
 *            arguments: none
 *            return: none
 *
 *       4. 'call_start': Start a code snippet call
 *            arguments: [integer] code snippet registration
 *            return: none
 ^
 *       5. 'call_stop': Stop a code snippet call
 *            arguments: [integer] code snippet registration
 *            return: none
 *
 *       6. 'result':  Process timing results
 *            arguments: none
 *            return:  [string]  String with timing results
 *
 *       7. 'resultc':  Print timing results to Octave console
 *            arguments:  [string]  code snippet label
 *                        [integer] requested code snippet registration
 *                                  (optional])
 *
 *            return: [integer] code snippet registration
 *
 *
 *       8. 'reg_code': Register code snippet
 *
 *     Take a look at examples in the current directory.
 */

    // Variables
    charMatrix chMat;          // Octave char matrix used to get string from the
                               // arguments
    std::string strFunction;   // cCosniwa function
    int iRego;                 // Function registration
    std::string strLabel;      // Label used in code snippet registration
    octave_value nothing;      // Empty octave value
    octave_value_list retval;  // Used to return a value


    // There must be at least one argument
    int nargin = args.length();
    if (nargin < 1)
    {
        octave_stdout << "cCosniwa ERROR!: ";
        octave_stdout << "you must specify internal cCosniwa function!\n";
        return nothing;
    }

    // Get the function type
    chMat = args(0).char_matrix_value();
    strFunction = chMat.row_as_string(0);

    // Switch to a correct function
    if(strFunction == "start")
    {
        // START THE MAIN TIME OF A STOPWATCH
        hCsw->start();
    }
    else if(strFunction == "stop")
    {
        // STOP THE MAIN TIME OF A STOPWATCH
        hCsw->stop();
    }
    else if(strFunction == "call_start")
    {
        // START A CODE SNIPPET CALL
        iRego = args(1).int_value();
        hCsw->call_start(iRego);
    }
    else if(strFunction == "call_stop")
    {
        // STOP A CODE SNIPPET CALL
        iRego = args(1).int_value();
        hCsw->call_stop(iRego);
    }
    else if (strFunction == "init")
    {
        // INITIALISE NEW COSNIWA
        hCsw = new Cosniwa();
    }
    else if (strFunction == "result")
    {
        // PROCESS TIMING RESULTS

        // Get the Cosniwa results as string
        std::string strResuls = hCsw->result();

        // Return string with values
        chMat = strResuls.c_str();
        retval(0) = octave_value(chMat, '"');
        return retval;
    }
    else if(strFunction == "resultc")
    {
        // PRINT TIMING RESULTS TO OCTAVE CONSOLE

        // Print the results to the console
        std::string strResuls = hCsw->result();
        octave_stdout << strResuls.c_str();
    }
    else if(strFunction == "reg_code")
    {
        // REGISTER CODE SNIPPET

        // Get arguments and run the correct function
        if (nargin == 2)
        {
            // Get the label from the arguments
            chMat = args(1).char_matrix_value();
            strLabel = chMat.row_as_string(0);

            // Register the code snippet
            iRego = hCsw->reg_code(strLabel);
        }
        else if (nargin == 3)
        {
            // Get the label from the arguments
            chMat = args(1).char_matrix_value();
            strLabel = chMat.row_as_string(0);

            // Get the requested rego from the arguments
            iRego = args(2).int_value();

            // Register the code snippet
            iRego = hCsw->reg_code(strLabel, iRego);
        }
        else
        {
            // ERROR: Incorrect use of `reg_code`
            octave_stdout << "cCosniwa ERROR!: ";
            octave_stdout << "\"reg_code\" requires 1 or 2 arguments!\n";
        }

        // Return rego
        retval(0) = iRego;
        return retval;
    }
    else
    {
        // ERROR: Unknown function
        octave_stdout << "cCosniwa ERROR!: \"" << strFunction.c_str() << "\"";
        octave_stdout << " is an unknown cCosniwa function!\n";
    }

    // Return nothing
    return octave_value_list();
}
