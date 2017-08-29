/*
 * cosniwa4Octave.cpp [version 1.0]
 * CoSniWa:  COde SNIppet stopWAtch
 *
 * Cosniwa  [Octave port - C++ implementation ] v1.0, 31 May 2017.
 *
 * version 1.0 ready on 31 May 2017
 *
 * This is definiton of Code Snippet Stopwatch (CoSniWa) object.
 * CoSniWa is dedicated to profile code using time stamps.
 *
 * read more on: www.speedupcode.com
 *
 * (c) Jacek Pierzchlewski, 2017  jacek@pierzchlewski.com
 * license: BSD-2-Clause.
 */
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <sstream>
#include <sys/time.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include "cosniwa.h"


/* **************************************************** */
/* CONSTRUCTORS / DECONSTRUCTOR:                        */
/* **************************************************** */

Cosniwa::Cosniwa()
{
/*
 *  CONSTRUCTOR (v1). Use default maximum number of intervals.
 *
 */
    // Initialise the object with the default maximum number of intervals
    _init(nTotalCallsMaxDef);
}


Cosniwa::Cosniwa(unsigned int iMaxNCalls_)
{
/*
 *  CONSTRUCTOR (v2). Set maximum number of intervals.
 *
 *  Parameters:
 *   iMaxNCalls_:  [unsigned int]  The maximum number of intervals
 *
 */
    // Initialise the object
    _init(iMaxNCalls_);
}


void Cosniwa::_init(unsigned int iMaxNCalls_)
{
/*
 *  _init:  INITIALISE THE OBJECT
 *
 *  Parameters:
 *   iMaxNCalls_:  [unsigned int]  The maximum number of intervals
 *
 */

    // Store the maximum number of intervals
    nTotalCallsMax = iMaxNCalls_;

    // Reset time stamp counter
    iTSCtr = 0;

    // Allocate space for timevals, registrations and markers
    stsTS = new timeval[nTotalCallsMax * 2];
    isTSRego = new unsigned int[nTotalCallsMax * 2];
    isTSMark = new unsigned int[nTotalCallsMax * 2];

    // Reset the number of registered code snippet labels
    nCSLabels = 0;

    // Allocate space fot code snippet labels
    strssCSLabels = new std::string* [nRegoMax];  // Labels
    for(unsigned int inxLabel=0; inxLabel < nRegoMax; inxLabel++)
    {
        strssCSLabels[inxLabel] = new std::string;
    }

    // Allocate space for code snippet registration numbers
    isCSRego = new unsigned int[nRegoMax];
}


Cosniwa::~Cosniwa()
{
/*
 *  DECONSTRUCTOR.
 */
    delete stsTS;
    delete isTSRego;
    delete isTSMark;

    for(unsigned int inxLabel=0; inxLabel<nRegoMax; inxLabel++)
    {
        delete strssCSLabels[inxLabel];
    }
    delete strssCSLabels;
    delete isCSRego;
}


/* **************************************************** */
/* CODE SNIPPET REGISTRATION FUNCTIONS:                 */
/* **************************************************** */

unsigned int Cosniwa::reg_code(std::string strLabel, unsigned int iRego)
{
/*
 *  reg_code:  REGISTER CODE SNIPPET (v1A).
 *
 *  Function registers new code snippet label (strLabel) in the snippets
 *  database with a given registration number (iRego).
 *  If label already exists with a different registration, function
 *  returns NULL.
 *
 *  Function returns iRego in case of no errors.
 *
 *
 *  Parameters:
 *   strLabel:  [std::string]   Label for the code snippet
 *   iRego:     [unsigned int]  Registration number of a code snippet.
 *
 *  Return:
 *   iRego:     [unsigned int]  Registration number of a code snippet.
 *                              It is equal to parameter 'iRego' if there are
 *                              no errors.
 */

    // Check if there is a place for code snippet labels
    if (nCSLabels == nRegoMax)
    {
        return (unsigned int)NULL;
    }

    // Negative Regos and rego 0 is restricted for the main part of the stoper
    if (iRego <= 0)
    {
        return (unsigned int)NULL;
    }

    // Check if label was not already registered
    unsigned int iLabelRego = _reg_is_label_in_labels(strLabel);
    if (iLabelRego != (unsigned int)NOT_FOUND)
    {
        // Label was found, check if it has the given rego
        if (iLabelRego != iRego)
        {
            // Label was registered with the other rego, it is an error
            return (unsigned int)NULL;
        }
    }

    // Check if a given rego is already registered
    if (_reg_is_rego_in_labels(iRego) == FOUND)
    {
        // Check if label is registered with the given rego
        int bErr = 0;  // Let's preassume it is not an error

        // Look for label in the database
        int iLabel = _reg_is_label_in_labels(strLabel);
        if (iLabel == NOT_FOUND)
        {   // If label is not found, it is an error
            bErr = 1;
        }
        else
        {   // If label is found with another rego, it is also an error
            if ((unsigned int)iLabel != iRego)
                bErr = 1;
        }

        // If an error was not found, return the found iRego
        if (bErr == 0)
        {
            return iRego;
        }
        else
        {
            // Label was registered with the other rego, it is an error
            return (unsigned int)NULL;
        }
    }

    // Add current label, registration number,
    // and increase the number of labels
    strssCSLabels[nCSLabels][0] = strLabel;
    isCSRego[nCSLabels] = (unsigned int)iRego;
    nCSLabels++;

    return iRego;
}


unsigned int Cosniwa::reg_code(const char* csLabel, unsigned int iRego)
{
/*
 *  reg_code:  REGISTER CODE SNIPPET (v1B).
 *
 *  Function registers new code snippet label (csLabel) in the snippets
 *  database with a given registration number (iRego).
 *  If label already exists with a different registration, function
 *  returns NULL.
 *
 *  Function returns iRego in case of no errors.
 *
 *
 *  Parameters:
 *   csLabel:  [const char*]   Label for the code snippet
 *   iRego:    [unsigned int]  Registration number of a code snippet.
 *
 *  Return:
 *   iRego:     [unsigned int]  Registration number of a code snippet.
 *                              It is equal to parameter 'iRego' if there are
 *                              no errors.
 */

    std::string strLabel = csLabel;
    return reg_code(strLabel, iRego);
}


unsigned int Cosniwa::reg_code(char* csLabel, unsigned int iRego)
{
/*
 *  reg_code:  REGISTER CODE SNIPPET (v1C).
 *
 *  Function registers new code snippet label (csLabel) in the snippets
 *  database with a given registration number (iRego).
 *  If label already exists with a different registration, function
 *  returns NULL.
 *
 *  Function returns iRego in case of no errors.
 *
 *
 *  Parameters:
 *   csLabel:  [char*]          Label for the code snippet
 *   iRego:    [unsigned int]   Registration number of a code snippet.
 *
 *  Return:
 *   iRego:     [unsigned int]  Registration number of a code snippet.
 *                              It is equal to parameter 'iRego' if there are
 *                              no errors.
 */

    std::string strLabel = csLabel;
    return reg_code(strLabel, iRego);
}


unsigned int Cosniwa::reg_code(std::string strLabel)
{
/*
 *  reg_code:  REGISTER CODE SNIPPET (v2A).
 *
 *  Function registers new code snippet label (strLabel) in the snippets
 *  database.
 *  Function returns registration number 'iRego' given to the code snippet
 *  label.
 *
 *
 *  Parameters:
 *   strLabel:  [std::string]  Label for the code snippet
 *
 *  Return:
 *   iRego:     [unsigned int]  Registration number of a code snippet
 *
 */

    // Find if a given label exists already in the code snippet labels database
    int iRego = _reg_is_label_in_labels(strLabel);
    if (iRego == NOT_FOUND)
    {
        // Label was not yet registered

        // Find the next available registration number
        iRego = _reg_next_free_rego();

        // Register the label with a given rego
        reg_code(strLabel, iRego);

        return (unsigned int)iRego;
    }
    else
    {
        // Label was already registered
        return (unsigned int)iRego;
    }
}


unsigned int Cosniwa::reg_code(const char* csLabel)
{
/*
 *  reg_code:  REGISTER CODE SNIPPET (v2B).
 *
 *  Function registers new code snippet label (csLabel) in the snippets
 *  database.
 *  Function returns registration number 'iRego' given to the code snippet
 *  label.
 *
 *
 *  Parameters:
 *   csLabel:  [const char*]  Label for the code snippet
 *
 *  Return:
 *   iRego:     [unsigned int]  Registration number of a code snippet
 *
 */
    std::string strLabel = csLabel;
    return reg_code(strLabel);
}


unsigned int Cosniwa::reg_code(char* csLabel)
{
/*
 *  reg_code:  REGISTER CODE SNIPPET (v2C).
 *
 *  Function registers new code snippet label (csLabel) in the snippets
 *  database.
 *  Function returns registration number 'iRego' given to the code snippet
 *  label.
 *
 *
 *  Parameters:
 *   csLabel:  [char*]  Label for the code snippet
 *
 *  Return:
 *   iRego:     [unsigned int]  Registration number of a code snippet
 *
 */
    std::string strLabel = csLabel;
    return reg_code(strLabel);
}


/* **************************************************** */
/* STOPER START/STOP FUNCTIONS:                         */
/* **************************************************** */

void Cosniwa::reset()
{
/*
 *  reset:  RESET THE STOPWATCH
 */

    // Reset time stamp counter
    iTSCtr = 0;

    // Reset the number of registered code snippet labels
    nCSLabels = 0;
}


void Cosniwa::start()
{
/*
 *  start:  START THE MAIN TIME OF STOPWATCH
 */

    isTSRego[iTSCtr] = 0;        // Store main rego
    isTSMark[iTSCtr] = START;    // Store Start marker
    gettimeofday(&stsTS[iTSCtr], NULL);  // Get the timestamp
    iTSCtr++;                    // Increase the counter of time stamps
}


void Cosniwa::stop()
{
/*
 *  start:  STOP THE MAIN TIME OF STOPWATCH
 */

    gettimeofday(&stsTS[iTSCtr], NULL);  // Get the timestamp
    isTSRego[iTSCtr] = 0;        // Store main rego
    isTSMark[iTSCtr] = STOP;     // Store Stop marker
    iTSCtr++;                    // Increase the counter of time stamps
}


void Cosniwa::call_start(unsigned int iRego)
{
/*
 *  call_start:  START A CODE SNIPPET CALL
 *
 *  Parameters:
 *   iRego:  [unsigned int]  Registration number of a code snippet
 *
 */

    isTSRego[iTSCtr] = iRego;    // Store rego
    isTSMark[iTSCtr] = START;    // Store Start marker
    gettimeofday(&stsTS[iTSCtr], NULL);
    iTSCtr++;    // Increase the counter of time stamps
}


void Cosniwa::call_stop(unsigned int iRego)
{
/*
 *  call_stop:  STOP A CODE SNIPPET CALL
 *
 *  Parameters:
 *   iRego:  [unsigned int]  Registration number of a code snippet
 *
 */

    gettimeofday(&stsTS[iTSCtr], NULL);
    isTSRego[iTSCtr] = iRego;    // Store rego
    isTSMark[iTSCtr] = STOP;     // Store Stop marker
    iTSCtr++;    // Increase the counter of time stamps
}


/* **************************************************** */
/* RESULTS FUNCTIONS:                                   */
/* **************************************************** */

std::string Cosniwa::result()
{
/*
 *  result:  GET TIMING RESULTS.
 *
 *  Return:
 *    [std::string]  String with timing results
 *
 */

    return _postprocessing(0);
}


void Cosniwa::resultc()
{
/*
 *  resultc:  PRINT TIMING RESULTS TO THE CONSOLE OUTPUT.
 *
 */

    std::cout << _postprocessing(0);
}


std::string Cosniwa::result_short()
{
/*
 *  result_short:  GET TIMING RESULTS (SHORT VERSION).
 *
 *  Return:
 *    [std::string]  String with timing results (short version)
 *
 */

   return _postprocessing(1);
}


void Cosniwa::resultc_short()
{
/*
 *  resultc_short:  PRINT TIMING RESULTS (SHORT VERSION) TO THE CONSOLE OUTPUT.
 *
 */

    std::cout << _postprocessing(1);
}


/* **************************************************** */
/* INTERNAL POSTPROCESSING FUNCTIONS:                   */
/* **************************************************** */

std::string Cosniwa::_postprocessing(int bShort)
{
/*
 *  _postprocessing:  PROCESS TIMESTAMPS AND CREATE A STRING WITH TIMING RESULTS
 *
 *
 *  Parameters:
 *    bShort  [int (bool)]   Flag: short / full results message
 *
 *  Return:
 *    strRes  [std::string]  String with timing results.
 *
 */

    unsigned int nURego;    // The number of unique code snippet registrations
                            // present in the timestamp database

    unsigned int* isRego;   // Table with unique code snippet registrations
                            // present in the timestamp database

    unsigned int* isTSInx;  // Table with sorted indices of unique code snippet
                            // registrations - sorted by the total execution
                            // time

    TRPar stTRParam;  // Structure with general parameters of timing results

    TR* stsResults; // Timing results for all the code snippet registrations

    std::string strRes;  // String with all the results

    // Count the unique code snippet registrations
    nURego = _post_count_rego(&isRego);

    // Allocate the timing results structures for all the unique code snippet
    // registrations
    stsResults = new TR[nURego];

    // Check consistency of the time stamps
    if(_post_check(nURego, isRego, &stTRParam) == FAIL)
    {
        printf("TIME STAMPS ARE INCONSISTENT! ABORT!\n");
        return strRes;
    }

    // Count the number of calls for every code snippet registration
    _post_count_calls(nURego, isRego, stsResults);

    // Allocate unequal table for call times for all the registrations
    //_allocate_lap_times_table(&uissPostLapsTimes, nURego);
    _post_allocate_call_times(nURego, stsResults);

    // Measure the call times for all the registrations,
    // and fill up the table with call times
    _post_measure_call_times(nURego, isRego, stsResults);

    // Process the table with call times for all the registrations
    _post_process_call_times(nURego, isRego, stsResults, stTRParam);

    // Sort the code snippets by the total execution time
    _post_sort(nURego, &isTSInx, stsResults);

    // Fill up the structure with with general timing results parameters
    _post_find_general_param(nURego, isTSInx, stsResults, &stTRParam);

    // DEBUG FUNCTIONS CAN BE CALLED FROM HERE

    // Print the timing results
    strRes = _post_print_timing(nURego, isTSInx, stsResults, stTRParam, bShort);

    // Deallocate
    _post_deallocate(nURego, isRego, isTSInx, stsResults);

    return strRes;
}


unsigned int Cosniwa::_post_count_rego(unsigned int** issRego)
{
/*
 *
 *  _post_count_rego:  (POSTPROCESSING) COUNT THE UNIQUE CODE SNIPPET
 *                      REGISTRATIONS
 *
 *  Function counts the number of unique code snippet registrations in the
 *  timestamps database.
 *  Additionally the function fills up table (**issRego) with unique code
 *  snippet registrations.
 *
 *
 * Parameters:
 *   issRego:  [unsigned int**]  Pointer to the beginning of table with
 *                               unique code snippet registrations
 *
 * Return:
 *   nURego:  [unsigned int]  The number of unique code snippet registraions
 *
 * -----------------------------------------------------------------
 *
 *  Example (1):
 *
 * 1:     stoper.start();   // START
 * 2:
 * 3:     stoper.lapstart(1);
 * 4:     stoper.lapstop(1);
 * 5:
 * 6:     stoper.lapstart(2);
 * 7:     stoper.lapstop(2);
 * 8:
 * 9:     stoper.stop();
 *
 * issRego: [ 0, 1, 2 ], nURego: 3
 *
 *
 * -----------------------------------------------------------------
 *
 * Example (2):
 *
 * 1:     stoper.start();   // START
 * 2:
 * 3:     stoper.lapstart(1);
 * 4:     stoper.lapstop(1);
 * 5:
 * 6:     stoper.lapstart(2);
 * 7:     stoper.lapstop(2);
 * 8:
 * 9:     stoper.lapstart(13);
 * 10:    stoper.lapstop(13);
 * 11:
 * 12:    stoper.lapstart(13);
 * 13:    stoper.lapstop(13);
 * 14:
 * 15:    stoper.lapstart(14);
 * 16:    stoper.lapstop(14);
 * 17:
 * 18:    stoper.stop();
 *
 * issRego: [ 0, 1, 2, 13, 14 ], nURego: 5
 *
 */
    // Reset the number of unique code snippet registrations
    unsigned int nURego = 0;

    // Allocate the internal table with unique registrations
    unsigned int* isRegoInt;
    isRegoInt = new unsigned int[nTotalCallsMax];

    // Loop over all timestamps
    nURego = 0;
    for(unsigned int inxTS = 0; inxTS < iTSCtr; inxTS++)
    {
        // Get the current code snippet registration from the timestamp database
        unsigned int iRego = isTSRego[inxTS];

        // Check if it was counted already.
        // If not, then increase the number of found registrations and
        // store the registration
        if (_post_count_rego_is_rego_counted(isRegoInt, nURego, iRego)
             == NOT_FOUND)
        {
            isRegoInt[nURego] = iRego;
            nURego++;
        }
    }

    // Copy the internal table with unique registrations onto
    // the external table
    issRego[0] = new unsigned int[nURego];
    unsigned int iCopyPtr = 0;
    for(; iCopyPtr<nURego;iCopyPtr++)
    {
        issRego[0][iCopyPtr] = isRegoInt[iCopyPtr];
    }

    // Delete the internal table with unique registrations
    delete isRegoInt;

    // Return the number of found unique registrations
    return nURego;
}


int Cosniwa::_post_count_rego_is_rego_counted(unsigned int* isUniqRego,
                                              unsigned int iNRego,
                                              unsigned int iRego)
{
/*
 *  _post_count_rego_is_rego_counted:  (POSTPROCESSING)  WAS REGO COUNTED?
 *
 *
 *  Helper function for counting the unique code snippet registrations.
 *  This function checks if a given rego (code snippet registration number)
 *  was already counted.
 *
 * Parameters:
 *   isUniqRego:  [unsigned int*]  Table with unique code snippet registrations
 *   iNRego:      [unsigned int]   The number of unique code snippet
 *                                 registrations in 'isUniqRego'
 *   iRego:       [unsigned int]   Checked rego (was it counted?)
 *
 *
 * Return:
 *   [int (bool)]  FOUND => Rego was found,
 *                 NOT_FOUND => Rego was not found,
 *
 */

    // Loop over all time stamp registrations
    for(unsigned int inxRego = 0; inxRego < iNRego; inxRego++)
    {
        if (isUniqRego[inxRego] == iRego)
            return FOUND;
    }
    return NOT_FOUND;
}


bool Cosniwa::_post_check(unsigned int nURego, unsigned int* isRego,
                          TRPar* stsTRParam)
{
/*
 *  _post_check:  (POSTPROCESSING)  CHECK IF THE MEASUREMENTS ARE CONSISTENT
 *
 * Parameters:
 *   nURego:  [unsigned int]    The number of unique code snippet registrations
 *   isRego:  [unsigned int*]   Pointer to table with unique code snippet
 *                              registrations
 *
 *   stsTRParam:  [TRPar structure*]  Pointer to the structure with general
 *                                    timing results parameters
 *
 * Return:
 *   [bool]  OK =>  check result: failed / pass check flag
 *           FAIL =>  check result: failed / pass check flag
 *
 */

    // Check if stoper was correctly started and stoped
    if (_post_check_start_stop(stsTRParam) == FAIL)
    {
        return FAIL;
    }

    // Check if the timestamps are correctly interleaved
    // (start-stop-start-stop- ... -start-stop)
    if (_post_check_interleave(nURego, isRego) == FAIL)
    {
        return FAIL;
    }

    return OK;
}


bool Cosniwa::_post_check_start_stop(TRPar* stsTRParam)
{
/*
 *  _post_check_start_stop:  (POSTPROCESSING)  CHECK IF STOPER WAS CORRECTLY
 *                                             STARTED AND STOPPED
 *
 * Parameters:
 *   stsTRParam:  [TRPar structure*]  Pointer to the structure with general
 *                                    timing results parameters
 *
 * Return:
 *   [bool]  OK =>  check result: failed / pass check flag
 *           FAIL =>  check result: failed / pass check flag
 *
 */

    // If no measurements were added, everything is ok
    if (iTSCtr == 0)
    {
        // main time was not measured
        stsTRParam->bMainTimeMeasured = MAIN_TIME_OFF;

        // everything is ok
        return OK;
    }

    // Check if the first timestamp comes from the main code.
    // If yes, then check if the stoper was correctly started and stoped.
    // If not, then check if timestamps from the main code are not present
    // anywhere in the timestamp database
    if ((isTSRego[0] == MAIN_REGO) && (isTSMark[0] == START))
    {
        stsTRParam->bMainTimeMeasured = MAIN_TIME_ON;
        return _post_check_start_stop_with_main();
    }
    else
    {
        stsTRParam->bMainTimeMeasured = MAIN_TIME_OFF;
        return _post_check_start_stop_without_main();
    }
}


bool Cosniwa::_post_check_start_stop_with_main()
{
/*
 *  _post_check_start_stop_with_main:  (POSTPROCESSING)
 *                                      CHECK IF STOPER WAS CORRECTLY STARTED
 *                                      AND STOPPED (MAIN TIME WAS MEASURED)
 *
 * Return:
 *   [bool]  OK =>  check result: failed / pass check flag
 *           FAIL =>  check result: failed / pass check flag
 *
 */

    // Check if stoper was correctly started and stoped
    if (!((isTSRego[0] == MAIN_REGO) && (isTSRego[iTSCtr - 1] == MAIN_REGO) &&
         (isTSMark[0] == START) && (isTSMark[iTSCtr - 1] == STOP)))
    {
        printf("Stoper was started, but not correctly stopped!\n");
        return FAIL;
    }

    // Check if stoper was not started/stopped in the middle of time stamps
    for(unsigned int inxTS=1;inxTS<(iTSCtr-1);inxTS++)
    {
        // Rego '0' can be only at the beggining and at the end
        if (isTSRego[inxTS] == MAIN_REGO)
        {
            printf("Stoper was started, but not correctly stopped!\n");
            return FAIL;
        }
    }
    return OK;
}


bool Cosniwa::_post_check_start_stop_without_main()
{
/*
 *  _post_check_start_stop_without_main:  (POSTPROCESSING)
 *                                         CHECK IF STOPER WAS CORRECTLY
 *                                         STARTED AND STOPPED (MAIN TIME WAS
 *                                         NOT MEASURED)
 *
 * Return:
 *   [bool]  OK =>  check result: failed / pass check flag
 *           FAIL =>  check result: failed / pass check flag
 *
 */

    // Check if stoper was not started/stopped anywhere in the time stamps
    for(unsigned int inxTS=0; inxTS<iTSCtr; inxTS++)
    {
        // Rego '0' can be only at the beggining and at the end
        if (isTSRego[inxTS] == MAIN_REGO)
        {
            if (isTSRego[inxTS] == START)
            {
                printf("Incorrect stoper start (timestamp #%d)!\n", inxTS);
            }
            else
            {
               printf("Incorrect stoper stop (timestamp #%d)!\n", inxTS);
            }
            return FAIL;
        }
    }

    return OK;
}


bool Cosniwa::_post_check_interleave(unsigned int nURego, unsigned int* isRego)
{
/*
 *  _post_check_interleave:  (POSTPROCESSING)  CHECK IF THE TIMESTAMPS ARE
 *                                             CORRECTLY INTERLEAVED
 *
 *  Function checks if timestamps are correctly interleaved
 *  (start-stop-start-stop- ... -start-stop).
 *
 * Parameters:
 *   nURego:  [unsigned int]   The number of unique code snippet registrations
 *   isRego:  [unsigned int*]   Pointer to table with unique code snippet
 *                              registrations
 *
 * Return:
 *   [bool]  OK =>  check result: failed / pass check flag
 *           FAIL =>  check result: failed / pass check flag
 *
 */

    // Loop over all unique code snippet registrations
    for(unsigned int inxRego = 0; inxRego < nURego; inxRego++)
    {
        // Get the current checked rego
        unsigned int iRego = isRego[inxRego];

        // Reset the counter of calls
        unsigned int nCalls = 0;

        // Loop over all time stamps
        unsigned int iExpMarker = START;   // Expected marker
        for(unsigned int inxTS = 0; inxTS<iTSCtr; inxTS++)
        {
            // Check if the time stamp is about the currently tested rego
            if(isTSRego[inxTS] == iRego)
            {
                // Increase the number of calls
                nCalls++;

                // Check if the time stamp has correct start/stop marker
                if (isTSMark[inxTS] == iExpMarker)
                {
                    // marker is ok, change the expected marker value
                    if (iExpMarker == START)
                        iExpMarker = STOP;
                    else
                        iExpMarker = START;
                }
                else
                {
                    // marker is incorrect, change the expected marker value
                    printf("Start/stop interleave error ");
                    printf("for rego #%d ", iRego);
                    if (iExpMarker == START)
                    {
                        printf("call: #%d !  Stop timestamp ", nCalls);
                        printf("found without previous start!\n");
                    }
                    else
                    {
                        printf("call: #%d !  Start timestamp", (nCalls + 1));
                        printf(" found without previous stop!\n");
                    }
                    return FAIL;
                }
            }
        }

        // The last expected marker should be START
        if (iExpMarker == STOP)
        {
            printf("Start/stop interleave error for rego #%d ", iRego);
            printf("call: #%d !  ", (nCalls + 1));
            printf("Start timestamp found without a following stop!\n");
            return FAIL;
        }
    }
    return OK;
}


void Cosniwa::_post_count_calls(unsigned int nURego, unsigned int* isRego,
                                TR* stsResults)
{
/*
 * _post_count_calls:  (POSTPROCESSING)  COUNT THE NUMBER OF CALLS
 *
 *
 * Function counts the number of calls for every code snippet and stores this
 * number in a structure with timing results for every code snippet
 * registration  ('stsResults').
 *
 *
 * Parameters:
 *   nURego:  [unsigned int]   The number of unique code snippet registrations
 *
 *   isRego:  [unsigned int*]   Pointer to table with unique code snippet
 *                              registrations
 *
 *   stsResults:  [TR structure*]   Pointer to structures with timing results
 *                                  for every code snippet registration
 *
 */

    // Loop over all the unique code snippet registrations
    for(unsigned int inxRego = 0; inxRego < nURego; inxRego++)
    {
        // Get the current checked registration
        unsigned int iRego = isRego[inxRego];

        // Reset counter of calls
        unsigned int nCalls = 0;

        // Loop over all time stamps
        for(unsigned int inxTS = 0; inxTS<iTSCtr;inxTS++)
        {
            // Check if the time stamp is about the currently tested rego
            // and if it is a starting time stamp
            if((isTSRego[inxTS] == iRego) && (isTSMark[inxTS] == START))
            {
                nCalls++;
            }
        }

        // Store the found number of calls
        stsResults[inxRego].nCalls = nCalls;
    }
}


void Cosniwa::_post_allocate_call_times(unsigned int nURego, TR* stsResults)
{
/*
 * _post_allocate_call_times:  (POSTPROCESSING)
 *                              ALLOCATE TABLE FOR CALL TIME FOR ALL THE UNIQUE
 *                              CODE SNIPPET REGISTRATIONS.
 *
 *
 *  Every structure with timing results for code snippet registration ('TR')
 *  contains a table of integers ('isCallT') dedicated for times of calls.
 *  This Function allocates theis table for all the unique code snippet
 *  registrations.
 *
 *
 * Parameters:
 *   nURego:  [unsigned int]   The number of unique code snippet registrations
 *
 *   stsResults:  [TR structure*]   Pointer to structures with timing results
 *                                  for every code snippet registration
 *
 */

    // Loop over all the uniqe code snippet registrations
    for(unsigned int inxRego = 0; inxRego < nURego; inxRego++)
    {
        // Get the number of calls
        unsigned int nCalls = stsResults[inxRego].nCalls;

        // Allocate vector for all the laps
        stsResults[inxRego].isCallT = new unsigned int[nCalls];
    }
    return;
}


void Cosniwa::_post_measure_call_times(unsigned int nURego,
                                       unsigned int* isRego,
                                       TR* stsResults)

{
/*
 * _post_measure_call_times:  (POSTPROCESSING)
 *                             MEASURE TIME OF ALL THE CALLS AND STORE THESE
 *                             TIMES IN TIMING RESULTS STRUCTURES.
 *
 *
 *  Every structure with timing results for code snippet registration ('TR')
 *  contains a table of integers ('isCallT') dedicated for times of calls.
 *  This Function measures the time of calls and fills up these tables.
 *
 *
 * Parameters:
 *   nURego:  [unsigned int]   The number of unique code snippet registrations
 *
 *   isRego:  [unsigned int*]   Pointer to table with unique code snippet
 *                              registrations
 *
 *   stsResults:  [TR structure*]   Pointer to structures with timing results
 *                                  for every code snippet registration
 *
 */

    long unsigned int iTSstart;    // Time stamp of start
    long unsigned int iTSstop;     // Time stamp of stop

    const uint64_t iSecus = 1000000;  // The number of us in second

    // Loop over all the unique registrations
    for(unsigned int inxRego = 0; inxRego < nURego; inxRego++)
    {
        // Get the current checked rego
        unsigned int iRego = isRego[inxRego];

        // Reset the number of calls
        unsigned int nCalls = 0;

        // Loop over all time stamps
        for(unsigned int inxTS = 0; inxTS<iTSCtr;inxTS++)
        {
            // Check if the time stamp is about the currently tested rego
            // and if it is a starting time stamp
            if((isTSRego[inxTS] == iRego) && (isTSMark[inxTS] == START))
            {
                // Get the seconds and microseconds from the start timestamp
                unsigned int iTSsec = (unsigned int)stsTS[inxTS].tv_sec;
                unsigned int iTSus = (unsigned int)stsTS[inxTS].tv_usec;

                // Compute the start timestamp
                iTSstart = (long unsigned int)(iTSsec*iSecus+iTSus);
            }

            // Check if the time stamp is about the currently tested rego
            // and if it is a stoping time stamp
            if((isTSRego[inxTS] == iRego) && (isTSMark[inxTS] == STOP))
            {
                // Get the seconds and microseconds from the stop timestamp
                unsigned int iTSsec = (unsigned int)stsTS[inxTS].tv_sec;
                unsigned int iTSus = (unsigned int)stsTS[inxTS].tv_usec;

                // Compute the stop timestamp
                iTSstop = (long unsigned int)(iTSsec*iSecus+iTSus);

                // Compute the call time between start and stop
                long unsigned int iCall = iTSstop - iTSstart;

                // Store the call time
                stsResults[inxRego].isCallT[nCalls] = iCall;

                // Increase the number of calls
                nCalls++;
            }
        }
    }
}


void Cosniwa::_post_process_call_times(unsigned int nURego,
                                       unsigned int* isRego,
                                       TR* stsResults, TRPar stTRParam)
{
/*
 * _post_process_call_times:  (POSTPROCESSING)  PROCESS ALL THE CALL TIMES
 *
 *
 *  Function process all the call times for all the registered code snippets.
 *  The function computes the total time of calls, the average single call time,
 *  minimum time of a single call, maximim time of a single call, etc.
 *
 *
 * Parameters:
 *   nURego:  [unsigned int]   The number of unique code snippet registrations
 *
 *   isRego:  [unsigned int*]   Pointer to table with unique code snippet
 *                              registrations
 *
 *   stsResults:  [TR structure*]   Pointer to structures with timing results
 *                                  for every code snippet registration
 *
 *   stsTRParam:  [TRPar structure*]  Pointer to the structure with general
 *                                    timing results parameters
 *
 */

    // Loop over all the unique registrations
    for(unsigned int inxRego = 0; inxRego < nURego; inxRego++)
    {
        // Get the current checked rego
        unsigned int iRego = isRego[inxRego];

        // Get the number of calls
        unsigned int nCalls = stsResults[inxRego].nCalls;

        // ** Compute the total time of a code snippet and min/max times of
        // ** a single call

        // Reset...:
        long unsigned int tTotalTime = 0;     // ...the total time of a snippet
        long unsigned int iTmin = ULONG_MAX;  // ... minimum time of a call
        long unsigned int iTmax = 0;          // ... maximim time of a call
        unsigned int nShortCalls = 0;

        // Loop over all the calls
        for(unsigned int inxCall=0;inxCall<nCalls;inxCall++)
        {
            // Get the length og the time call
            unsigned int iCallTime = stsResults[inxRego].isCallT[inxCall];

            // Add time of the current time to the total time
            tTotalTime+=iCallTime;

            // Update the minimim and maximim time of a single call
            // (if needed)
            if (nCalls > 1)
            {
                if (iTmin > iCallTime)
                {
                    iTmin = iCallTime;
                }
                if (iTmax < iCallTime)
                {
                    iTmax = iCallTime;
                }
            }

            // Update the number of short calls, if it is a short call
            if (iCallTime == 0)
            {
                nShortCalls++;
            }
        }

        // ** Compute the average time of a single call
        double tAvgTime;

        // Compute the avg. time if the code snippet was called more than once
        if (nCalls > 1)
        {
            tAvgTime = (double)tTotalTime / nCalls;
        }
        else
        {
            tAvgTime = -1;
        }

        // ** Compute what part of the main time is the current snippet **
        double dPart;
        if (stTRParam.bMainTimeMeasured == MAIN_TIME_ON)
        {
            if (inxRego == 0)
                dPart = 1;
            else
            {
                // Get the time of the first registration - time between
                // stoper.start() and stoper.stop()
                long unsigned int iStoperTotalTime = stsResults[0].tTotalTime;
                dPart = (double)tTotalTime / iStoperTotalTime;
            }
        }
        else
        {
            dPart = -1;
        }

        // Store the code snippet registration
        stsResults[inxRego].iRego = iRego;

        // Store the minimum time of a single call;
        stsResults[inxRego].tMin = iTmin;

        // Store the maximum time of a single call;
        stsResults[inxRego].tMax = iTmax;

        // Store the number of short calls
        stsResults[inxRego].nShortCalls = nShortCalls;

        // Store the total time of all calls
        stsResults[inxRego].tTotalTime = tTotalTime;

        // Store the average time of a single call
        stsResults[inxRego].tAvgTime = tAvgTime;

        // Store how big part of the whole time measured by the stoper was
        // taken by the current code snippet registration
        stsResults[inxRego].dPart = dPart;

        // ** Compute the variance **
        double tVar = 0;

        // Compute the variance if the code snippet was called more than once
        if (nCalls > 1)
        {
            // Loop over all the calls
            for(unsigned int inxCall=0; inxCall<nCalls; inxCall++)
            {
                tVar+= pow((stsResults[inxRego].isCallT[inxCall] - tAvgTime),
                            2);
            }
            tVar = tVar / nCalls;
        }

        // Store the variance
        stsResults[inxRego].tVar = tVar;

        // Compute the max speed up according to Amdahl's law
        double dMaxSpeedUp;
        if (inxRego == 0)
        {
            dMaxSpeedUp = -1;
        }
        else
        {
            dMaxSpeedUp = 1/(1 - dPart);
        }

        // Store the max speed-up
        stsResults[inxRego].dMaxSpeedUp = dMaxSpeedUp;
    }
}


void Cosniwa::_post_sort(unsigned int nURego, unsigned int** issTSInx,
                         TR* stsResults)
{
/*
 * _post_sort:  (POSTPROCESSING)  SORT THE CODE SNIPPETS BY THE TOTAL CALL TIME
 *
 *
 * Parameters:
 *   nURego:  [unsigned int]   The number of unique code snippet registrations
 *
 *   issTSInx:  [unsigned int**]  Pointer to a table with sorted indices of
 *                                unique code snippet registrations - sorted
 *                                by the total call time
 *                                (should not point to any allocated memory -
 *                                 - it is allocated in this function)
 *
 *   stsResults:  [TR structure*]   Pointer to structures with timing results
 *                                  for every code snippet registration
 *
 */

    // Allocate a table with sorted indices of code snippets timing results
    issTSInx[0] = new unsigned int[nURego];
    for(unsigned int inxRego = 0; inxRego < nURego; inxRego++)
    {
        issTSInx[0][inxRego] = inxRego;
    }

    // There is a simple bubble sort here.
    // Its performance is ok for the sorting needed by stoper,
    // while its very generic implementation ensures seemless integration
    // with f.ex. CPython.
    bool bNotSorted = 1;
    if (nURego == 0)
    {
        bNotSorted = 0;
    }
    while (bNotSorted)
    {
        bNotSorted = 0;  // Preassume that structures are sorted
        for(unsigned int i = 0; i < (nURego - 1); i++)
        {
            // Get currently compared indices of the code snippets
            unsigned int iInx1 = issTSInx[0][i];
            unsigned int iInx2 = issTSInx[0][i+1];

            // Compare
            if ((stsResults[iInx1].tTotalTime) < (stsResults[iInx2].tTotalTime))
            {
                // Create a 'bubble', if needed
                unsigned int iTempInx = issTSInx[0][i];
                issTSInx[0][i] = issTSInx[0][i+1];
                issTSInx[0][i+1] = iTempInx;

                // Note that the table is not yet sorted
                bNotSorted = 1;
            }
        }
    }
}


void Cosniwa::_post_find_general_param(unsigned int nURego,
                                       unsigned int* isTSInx,
                                       TR* stsResults, TRPar* stsTRParam)
{
/*
 * _post_find_general_param:  (POSTPROCESSING)
 *                             FIND THE GENERAL TIMING RESULTS PARAMETERS
 *
 *
 * The function computes the general timing results parameters and store these
 * parameters in 'stsTRParam' structure.
 *
 *
 * Parameters:
 *   nURego:  [unsigned int]   The number of unique code snippet registrations
 *
 *   isTSInx:  [unsigned int*]   Pointer to a table with sorted indices of
 *                               unique code snippet registrations - sorted
 *                               by the total call time
 *
 *   stsResults:  [TR structure*]     Pointer to structures with timing results
 *                                    for every code snippet registration
 *
 *   stsTRParam:  [TRPar structure*]  Pointer to the structure with general
 *                                    timing results parameters
 *
 */

    // Store the number of unique code snippet registrations
    stsTRParam->nURego = nURego;

    // Find size of the longest code snippet label
    stsTRParam->iLongestLabelSiz = 0;
    for(unsigned int inxLabel = 0; inxLabel < nCSLabels; inxLabel++)
    {
        // Get the size of a code snippet label
        unsigned int iLabelSiz = strssCSLabels[inxLabel][0].length();

        // Update the longest size, if needed
        if (stsTRParam->iLongestLabelSiz < iLabelSiz)
        {
            stsTRParam->iLongestLabelSiz = iLabelSiz;
        }
    }

    // Create an empty label
    stsTRParam->strEmptyLabel = "";
    for(unsigned int inxChr = 0; inxChr < stsTRParam->iLongestLabelSiz; inxChr++)
    {
        stsTRParam->strEmptyLabel+= " ";
    }

    // Reset...:
    stsTRParam->iHighRego = 0;       // highest code snippet registraion number
    stsTRParam->tTotalMax = 0;       // the total time spend in a code snippet
    stsTRParam->nCallsMax = 0;       // the number of calls
    stsTRParam->tAvgMax = 0;         // the maximum average time
    stsTRParam->tVarMax = 0;         // the maximum variance
    stsTRParam->dPartMax = 0;        // the maximum fraction of the main time
    stsTRParam->dMaxSpeedUpMax = 0;  // the maximum max possible speed up
    stsTRParam->tMinMax = 0;         // the maximum min time of a single call
    stsTRParam->tMaxMax = 0;         // the maximim max time of a single call

    // Find the maximum values in the Timing Results structures:
    for(unsigned int inxRego = 0; inxRego < nURego; inxRego++)
    {
        // Code snippet with registration 0 means all the measured code
        // - not interesting
        if (stsResults[inxRego].iRego == 0)
            continue;

        // Update the highest code snippet registraion number
        if (stsTRParam->iHighRego < stsResults[inxRego].iRego)
        {
            stsTRParam->iHighRego = stsResults[inxRego].iRego;
        }

        // Update the maximum total time
        if (stsTRParam->tTotalMax < stsResults[inxRego].tTotalTime)
        {
            stsTRParam->tTotalMax = stsResults[inxRego].tTotalTime;
        }

        // Update the maximum number of calls for a code snippet
        if (stsTRParam->nCallsMax < stsResults[inxRego].nCalls)
        {
            stsTRParam->nCallsMax = stsResults[inxRego].nCalls;
        }

        // Update the maximum average time
        if (stsTRParam->tAvgMax < stsResults[inxRego].tAvgTime)
        {
            if (stsResults[inxRego].nCalls > 1)
            {
                stsTRParam->tAvgMax = stsResults[inxRego].tAvgTime;
            }
        }

        // Update the maximum variance
        if (stsTRParam->tVarMax < stsResults[inxRego].tVar)
        {
            if (stsResults[inxRego].nCalls > 1)
            {
                stsTRParam->tVarMax = stsResults[inxRego].tVar;
            }
        }

        // Update the maximum fraction of the main time
        if (stsTRParam->dPartMax < stsResults[inxRego].dPart)
        {
            stsTRParam->dPartMax = stsResults[inxRego].dPart;
        }

        // Update the maximum max possible speed up
        if (stsTRParam->dMaxSpeedUpMax < stsResults[inxRego].dMaxSpeedUp)
        {
            stsTRParam->dMaxSpeedUpMax = stsResults[inxRego].dMaxSpeedUp;
        }

        // Update the maximum min time of a single call
        if (stsTRParam->tMinMax < stsResults[inxRego].tMin)
        {
            if (stsResults[inxRego].nCalls > 1)
            {
                stsTRParam->tMinMax = stsResults[inxRego].tMin;
            }
        }

        // Update the maximim max time of a single call
        if (stsTRParam->tMaxMax < stsResults[inxRego].tMax)
        {
            if (stsResults[inxRego].nCalls > 1)
            {
                stsTRParam->tMaxMax = stsResults[inxRego].tMax;
            }
        }
    }
}


std::string Cosniwa::_post_print_timing(unsigned int nURego,
                                        unsigned int* isTSInx,
                                        TR* stsResults, TRPar stTRParam,
                                        int bShort)
{
/*
 * _post_print_timing:  (POSTPROCESSING  RESULTS PRINTING)
 *                       THE MAIN RESULTS PRINTING FUNCTION
 *
 *
 *
 * Parameters:
 *   nURego:  [unsigned int]   The number of unique code snippet registrations
 *
 *   isTSInx:  [unsigned int*]   Pointer to a table with sorted indices of
 *                               unique code snippet registrations - sorted
 *                               by the total call time
 *
 *   stsResults:  [TR structure*]     Pointer to structures with timing results
 *                                    for every code snippet registration
 *
 *   stsTRParam:  [TRPar structure*]  Pointer to the structure with general
 *                                    timing results parameters
 *
 *   bShort:  [int (bool)]   Flag: short / full results message
 *
 *
 * Returns:
 *   strRes:  [str::string]   String with the timing results
 *
 */

    // String with the results
    std::string strRes = "";

    // Print header
    strRes += _post_print_header();

    // Print the  main time
    strRes += _post_print_main_time(stsResults, stTRParam);

    // Print measured code snippet timing
    strRes += _post_print_snippets_times(nURego, isTSInx,
                                         stsResults, stTRParam, bShort);
    // Print footer
    strRes += _post_print_footer();

    // Return the string with results
    return strRes;
}


std::string Cosniwa::_post_print_header()
{
/*
 * _post_print_header:  (POSTPROCESSING  RESULTS PRINTING)
 *                       PRINT HEADER
 *
 * Returns:
 *   strOut:  [str::string]   String with the header
 *
 */

    std::string strOut="";  // Out string

    // Print out header of timing results
    strOut += ">>> ===================";
    strOut += " CoSniWa [Octave port] ";
    strOut += "=================== >>>\n";

    return strOut;
}


std::string Cosniwa::_post_print_footer()
{
/*
 * _post_print_footer:  (POSTPROCESSING  RESULTS PRINTING)
 *                       PRINT FOOTER
 *
 * Returns:
 *   strOut:  [str::string]   String with the footer
 *
 */

    std::string strOut="";  // Out string

    // Print out footer
    strOut += "<<< ===================";
    strOut += " CoSniWa [Octave port] ";
    strOut += "=================== <<<\n";

    return strOut;
}


std::string Cosniwa::_post_print_main_time(TR* stsResults, TRPar stTRParam)
{
/*
 * _post_print_main_time:  (POSTPROCESSING  RESULTS PRINTING)
 *                          PRINT THE MAIN TIME OF THE STOPWATCH
 *
 *
 * Function prints the main time of the stopwatch, if it was measured
 *
 *
 * Parameters:
 *   stsResults:  [TR structure*]   Pointer to structures with timing results
 *                                  for every code snippet registration
 *
 *   stTRParam:  [TRPar structure]   Structure with general timing results
 *                                   parameters
 *
 * Returns:
 *   strOut:  [str::string]   String with the main time of the stopwatch
 *
 */

    std::string strOut="";  // Out string
    // If there are no code snippets in the database, do not print anythong
    if (iTSCtr == 0)
        return strOut;

    // If he main time was not measured, do not print anything
    if (stTRParam.bMainTimeMeasured == MAIN_TIME_OFF)
        return strOut;

    // Buffer for the printed output
    char csBuf[iTempBufSiz];

    // convert the total time to ms
    double iMainTimems = (double)stsResults[0].tTotalTime / 1000;

    // Print out timing for the main stoper time
    int iDAC = 3;   // The number of digits after comma
    const char csPrefix[] = "Total measured time: ";
    const char csSuffix[] = " [ms]";
    _post_print_record_float(csBuf, iMainTimems, iMainTimems,
                             csPrefix, csSuffix, iDAC);
    strOut += csBuf;
    strOut += "\n";

    return strOut;
}


std::string Cosniwa::_post_print_snippets_times(unsigned int nURego,
                                                unsigned int* isTSInx,
                                                TR* stsResults, TRPar stTRParam,
                                                int bShort)
{
/*
 * _post_print_snippets_times:  (POSTPROCESSING  RESULTS PRINTING)
 *                               PRINT THE TIMING RESULTS FOR CODE SNIPPETS
 *
 *
 * Function prints timing results for all the ordinary (not-main) code snippets.
 *
 *
 * Parameters:
 *   nURego:  [unsigned int]   The number of unique code snippet registrations
 *
 *   isTSInx:  [unsigned int*]   Pointer to a table with sorted indices of
 *                               unique code snippet registrations - sorted
 *                               by the total call time
 *
 *   stsResults:  [TR structure*]     Pointer to structures with timing results
 *                                    for every code snippet registration
 *
 *   stTRParam:  [TRPar structure]  Structure with general timing results
 *                                  parameters
 *
 *   bShort:  [int (bool)]   Flag: short / full results message
 *
 *
 * Returns:
 *   strOut:  [str::string]   String with the timing results for code snippets
 *
 */

    std::string strOut = "";  // Start out string

    // Print code snippets only if there are code snippets
    if ((nURego == 1) && (stTRParam.bMainTimeMeasured == MAIN_TIME_ON))
    {
        return strOut;
    }
    else if ((nURego == 0) && (stTRParam.bMainTimeMeasured == MAIN_TIME_OFF))
    {
        return strOut;
    }

    // Print code snippet header
    if (stTRParam.bMainTimeMeasured == MAIN_TIME_ON)
    {
        strOut += "\n";
    }
    strOut += "Code snippets: \n";

    // **  Print data for all Loop the code snippets **
    unsigned int inxRego = 0;   // Reset index of the current code snippet
    unsigned int inxCS = 1;     // Reset order number of the code snippet

    // If the main time was measured, start with code snippet indexed as 1.
    // Index 0 is the main time
    if (stTRParam.bMainTimeMeasured == MAIN_TIME_ON)
    {
        inxRego = 1;
    }

    // Loop over all code snippets
    for(; inxRego < nURego; inxRego++)
    {

        // Print the data for a single snippet
        strOut += _post_print_single_snippet_data(inxCS, isTSInx[inxRego],
                                                  isTSInx, stsResults,
                                                  stTRParam, bShort);

        // Increase index if the code snippet
        inxCS += 1;
    }

    return strOut;
}


std::string Cosniwa::_post_print_single_snippet_data(unsigned int iInx,
                                                     unsigned int iCS,
                                                     unsigned int *isTSInx,
                                                     TR* stsResults,
                                                     TRPar stTRParam,
                                                     int bShort)
{
/*
 * _post_print_single_snippet_data:  (POSTPROCESSING  RESULTS PRINTING)
 *                                    PRINT THE TIMING RESULTS FOR SINGLE
 *                                    CODE SNIPPET
 *
 *
 * Parameters:
 *   iInx:  [unsigned int]  Index of the code snippet
 *
 *   iCS:  [unsigned int]   Index of the timing results structure
 *                          for the code snippet in the 'stsResults'
 *
 *   isTSInx:  [unsigned int*]   Pointer to a table with sorted indices of
 *                               unique code snippet registrations - sorted
 *                               by the total call time
 *
 *   stsResults:  [TR structure*]     Pointer to structures with timing results
 *                                    for every code snippet registration
 *
 *   stTRParam:  [TRPar structure]  Structure with general timing results
 *                                  parameters
 *
 *   bShort:  [int (bool)]   Flag: short / full results message
 *
 *
 * Returns:
 *   strOut:  [str::string]   String with the timing results for single code
 *                            snippet
 *
 */

    std::string strOut="";  // Start out string

    // Print the index of the current code snippet
    strOut += _post_print_single_snippet_data_inx(iInx, stTRParam);

    // Get the structure for the code snippet the function is talking about
    TR stTR = stsResults[iCS];

    // Print rego
    strOut += _post_print_single_snippet_data_rego(stTR, stTRParam);

    // Print label
    strOut += _post_print_single_snippet_data_label(stTR, stTRParam);

    // Print the number of calls
    strOut += _post_print_single_snippet_data_calls(stTR, stTRParam);

    // Print the total time spend in the code snippet
    strOut += _post_print_single_snippet_data_totaltime(stTR, stTRParam);

    // Print fraction of the main time, if the main time was measured
    strOut += _post_print_single_snippet_data_fraction(stTR, stTRParam);

    // Print the maximum speed up
    strOut += _post_print_single_snippet_data_max_s_up(stTR, stTRParam);

    // If the detailed (non short) data was requested, add the average time,
    // the variance the minimum time and the maximum time
    if (bShort == 0)
    {
        // Print the average time
        strOut += _post_print_single_snippet_data_avg_time(stTR, stTRParam);

        // Print the variance
        strOut += _post_print_single_snippet_data_var(stTR, stTRParam);

        // Print the minimum time
        strOut += _post_print_single_snippet_data_min_time(stTR, stTRParam);

        // Print the maximum time
        strOut += _post_print_single_snippet_data_max_time(stTR, stTRParam);
    }

    // Line finished here
    strOut += "\n";

    // Report too short calls
    strOut += _post_print_single_snippet_data_short_call(stTR, stTRParam);

    return strOut;
}


std::string Cosniwa::_post_print_single_snippet_data_inx(unsigned int iInx,
                                                         TRPar stTRParam)
{
/*
 * _post_print_single_snippet_data_inx:  (POSTPROCESSING  RESULTS PRINTING)
 *                                        PRINT THE INDEX OF THE CURRENT CODE
 *                                        SNIPPET
 *
 *
 * Parameters:
 *   iInx:  [unsigned int]  Index of the code snippet
 *
 *   stTRParam:  [TRPar structure]  Structure with general timing results
 *                                  parameters
 *
 * Returns:
 *   strOut:  [str::string]   String with formatted index of the code snippet
 *
 */

    std::string strOut="";  // Start out string
    char csBuf[iTempBufSiz];

    const char csPrefixIndex[] = "";     // Prefix
    const char csSuffixIndex[] = ".  ";  // Suffix
    const char csInvoIndex[] = "#";      // Number invocation
    _post_print_record_int(csBuf, stTRParam.nURego, iInx,
                           csPrefixIndex, csInvoIndex, csSuffixIndex);
    strOut += csBuf;

    return strOut;
}


std::string Cosniwa::_post_print_single_snippet_data_rego(TR stTR,
                                                          TRPar stTRParam)
{
/*
 * _post_print_single_snippet_data_rego:  (POSTPROCESSING  RESULTS PRINTING)
 *                                         PRINT REGISTRATION NUMBER OF
 *                                         A CODE SNIPPET
 *
 *
 * Parameters:
 *   stTR:  [TR structure]   Structure with timing results for the code snippet
 *
 *   stTRParam:  [TRPar structure]   Structure with general timing results
 *                                   parameters
 *
 * Returns:
 *   strOut:  [str::string]   String with formatted registratioin number
 *                            of the code snippet
 */

    std::string strOut="";  // Start out string

    char csBuf[iTempBufSiz];

    const char csPrefixRego[] = "rego: ";
    const char csSuffixRego[] = "  ";
    const char csInvoRego[] = "";
    _post_print_record_int(csBuf, stTRParam.iHighRego, stTR.iRego,
                           csPrefixRego, csInvoRego, csSuffixRego);
    strOut += csBuf;

    return strOut;
}


std::string Cosniwa::_post_print_single_snippet_data_label(TR stTR,
                                                           TRPar stTRParam)
{
/*
 * _post_print_single_snippet_data_label:  (POSTPROCESSING  RESULTS PRINTING)
 *                                          PRINT REGISTRATION LABEL OF
 *                                          A CODE SNIPPET (IF AVAILABLE)
 *
 *
 * Parameters:
 *   stTR:  [TR structure]   Structure with timing results for the code snippet
 *
 *   stTRParam:  [TRPar structure]   Structure with general timing results
 *                                   parameters
 *
 * Returns:
 *   strOut:  [str::string]   String with formatted label of the code snippet
 *
 */

    std::string strOut="";  // Start out string

    std::string strPrefix = "\"";
    std::string strSuffix = "\"  ";

    // Get index of a label
    int iInxLabel = _reg_is_rego_in_labels(stTR.iRego);

    // Buffer for an empty string
    char csEmpty[iTempBufSiz];

    // Print the label, if it exists for a given code snippet
    if (iInxLabel == NOT_FOUND)
    {
        // Print an empty label
        _post_print_space_padding(csEmpty, strPrefix.length());
        strOut += csEmpty;
        strOut += stTRParam.strEmptyLabel;
        _post_print_space_padding(csEmpty, strSuffix.length());
        strOut += csEmpty;
    }
    else
    {
        // Print the label
        std::string strLabel = strssCSLabels[iInxLabel][0];
        strOut += strPrefix;
        strOut += strLabel;
        strOut += strSuffix;

        // Adjust the label length
        int iChrMissing = stTRParam.iLongestLabelSiz - strLabel.length();
        _post_print_space_padding(csEmpty, iChrMissing);
        strOut += csEmpty;
    }

    return strOut;
}


std::string Cosniwa::_post_print_single_snippet_data_calls(TR stTR,
                                                           TRPar stTRParam)
{
/*
 * _post_print_single_snippet_data_calls:  (POSTPROCESSING  RESULTS PRINTING)
 *                                          PRINT THE NUMBER OF CALLS FOR
 *                                          A CODE SNIPPET
 *
 *
 * Parameters:
 *   stTR:  [TR structure]   Structure with timing results for the code snippet
 *
 *   stTRParam:  [TRPar structure]   Structure with general timing results
 *                                   parameters
 *
 * Returns:
 *   strOut:  [str::string]   String with formatted number of calls
 *
 */

    std::string strOut="";    // Start out string
    char csBuf[iTempBufSiz];

    const char csPrefixCalls[] = "[calls:  ";
    const char csSuffixCalls[] = "]  ";
    const char csInvoCalls[] = "";
    _post_print_record_int(csBuf, stTRParam.nCallsMax, stTR.nCalls,
                           csPrefixCalls, csInvoCalls, csSuffixCalls);
    strOut += csBuf;

    return strOut;
}


std::string Cosniwa::_post_print_single_snippet_data_totaltime(TR stTR,
                                                               TRPar stTRParam)
{
/*
 * _post_print_single_snippet_data_totaltime: (POSTPROCESSING  RESULTS PRINTING)
 *                                             PRINT THE TOTAL TIME CALL FOR
 *                                             A CODE SNIPPET
 *
 * Parameters:
 *   stTR:  [TR structure]   Structure with timing results for the code snippet
 *
 *   stTRParam:  [TRPar structure]   Structure with general timing results
 *                                   parameters
 *
 * Returns:
 *   strOut:  [str::string]   String with formatted total call time ofor the
 *                            code snippet
 *
 */

    std::string strOut="";    // Start out string
    char csBuf[iTempBufSiz];

    double iMaxTotalTimems = (double)stTRParam.tTotalMax / 1000;
    double tTotalTimems = (double)stTR.tTotalTime / 1000;

    const char csPrefixTotal[] = "";
    const char csSuffixTotal[] = " [ms]  ";
    const char csDefault[] = "<0.001";    // Default value
    int iDAC = 3;      // The number of digits after comma

    // If the average time is lower then 0.001 ms, print a default value
    bool bPrintDefault = 0;
    if (tTotalTimems < 0.001)
        bPrintDefault = 1;

    _post_print_record_float(csBuf, iMaxTotalTimems, tTotalTimems,
                             csPrefixTotal, csSuffixTotal, csDefault,
                             iDAC, bPrintDefault);
    strOut += csBuf;

    return strOut;
}


std::string Cosniwa::_post_print_single_snippet_data_fraction(TR stTR,
                                                              TRPar stTRParam)
{
/*
 * _post_print_single_snippet_data_fraction: (POSTPROCESSING  RESULTS PRINTING)
 *                                            PRINT WHAT FRACTION OF THE MAIN
 *                                            STOPWATCH TIME IS TAKEN BY
 *                                            A CODE SNIPPET
 *
 * Parameters:
 *   stTR:  [TR structure]   Structure with timing results for the code snippet
 *
 *   stTRParam:  [TRPar structure]   Structure with general timing results
 *                                   parameters
 *
 * Returns:
 *   strOut:  [str::string]   String with formatted fraction of the main
 *                            stopwatch time
 *
 */

    std::string strOut="";    // Start out string
    char csBuf[iTempBufSiz];

    if (stTRParam.bMainTimeMeasured == MAIN_TIME_ON)
    {
        int iDAC = 2;   // The number of digits after comma
        const char csPrefix[] = "";
        const char csSuffix[] = "%  ";
        const char csDefault[] = "<0.01";    // Default value

        // If the fraction is lower then 0.01%, print a default value
        bool bPrintDefault = 0;
        if ((stTR.dPart * 100) < 0.01)
            bPrintDefault = 1;

        // Print the record
        _post_print_record_float(csBuf, 100.0, stTR.dPart * 100,
                                 csPrefix, csSuffix, csDefault, iDAC,
                                 bPrintDefault);
        strOut += csBuf;
    }
    return strOut;
}


std::string Cosniwa::_post_print_single_snippet_data_max_s_up(TR stTR,
                                                              TRPar stTRPar)
{
/*
 * _post_print_single_snippet_data_max_s_up: (POSTPROCESSING  RESULTS PRINTING)
 *                                            PRINT MAXIMUM POSSIBLE SPEED UP
 *                                            FOR A CODE SNIPPET
 *
 * Parameters:
 *   stTR:  [TR structure]   Structure with timing results for the code snippet
 *
 *   stTRParam:  [TRPar structure]   Structure with general timing results
 *                                   parameters
 *
 * Returns:
 *   strOut:  [str::string]   String with formatted maximum possible speed up
 *                            for the code snippet
 *
 */

    std::string strOut="";    // Start out string
    char csBuf[iTempBufSiz];

    if (stTRPar.bMainTimeMeasured == MAIN_TIME_ON)
    {
        int iDAC = 2;   // The number of digits after comma
        const char csPrefix[] = "MPA: ";
        const char csSuffix[] = "  ";
        const char csDefault[] = "<1.01";   // Default value

        // If the fraction is lower then 0.01, print a default value
        bool bPrintDefault = 0;
        if (stTR.dMaxSpeedUp < 1.01)
            bPrintDefault = 1;

        // Print the record
        _post_print_record_float(csBuf, stTRPar.dMaxSpeedUpMax,
                                 stTR.dMaxSpeedUp,
                                 csPrefix, csSuffix, csDefault,
                                 iDAC, bPrintDefault);
        strOut += csBuf;
    }

    return strOut;
}


std::string Cosniwa::_post_print_single_snippet_data_avg_time(TR stTR,
                                                              TRPar stTRPar)
{
/*
 * _post_print_single_snippet_data_avg_time: (POSTPROCESSING  RESULTS PRINTING)
 *                                            PRINT AVERAGE CALL TIME
 *                                            FOR A CODE SNIPPET
 *
 * Parameters:
 *   stTR:  [TR structure]   Structure with timing results for the code snippet
 *
 *   stTRParam:  [TRPar structure]   Structure with general timing results
 *                                   parameters
 *
 * Returns:
 *   strOut:  [str::string]   String with formatted average call time for the
 *                            code snippet
 *
 */

    std::string strOut="";    // Start out string
    char csBuf[iTempBufSiz];

    // Print the average time only if the code snippet was called more than once
    if (stTR.nCalls > 1)
    {
        double iMaxAvgTimems = stTRPar.tAvgMax / 1000;
        double iAvgTimems = stTR.tAvgTime / 1000;

        int iDAC = 3;   // The number of digits after comma
        const char csPrefix[] = "avg: ";
        const char csSuffix[] = " [ms]  ";
        const char csDefault[] = "<0.001";   // Default value

        // If the average time is lower then 0.001 ms, print default value
        bool bPrintDefault = 0;
        if (iAvgTimems < 0.001)
            bPrintDefault = 1;

        // Print the record
        _post_print_record_float(csBuf, iMaxAvgTimems,
                                 iAvgTimems,
                                 csPrefix, csSuffix, csDefault,
                                 iDAC, bPrintDefault);
        strOut += csBuf;
    }

    return strOut;
}


std::string Cosniwa::_post_print_single_snippet_data_var(TR stTR, TRPar stTRPar)
{
/*
 * _post_print_single_snippet_data_var: (POSTPROCESSING  RESULTS PRINTING)
 *                                       PRINT VARIANCE OF CALLING TIMES
 *                                       FOR A CODE SNIPPET
 *
 * Parameters:
 *   stTR:  [TR structure]   Structure with timing results for the code snippet
 *
 *   stTRParam:  [TRPar structure]   Structure with general timing results
 *                                   parameters
 *
 * Returns:
 *   strOut:  [str::string]   String with formatted variance of calling times
 *                            for a code snippet
 *
 */

    std::string strOut="";    // Start out string
    char csBuf[iTempBufSiz];

    // Print the variance only if the code snippet was called more than once
    if (stTR.nCalls > 1)
    {
        double iMaxVarms = stTRPar.tVarMax / 1000;
        double iVarms = stTR.tVar / 1000;

        int iDAC = 3;   // The number of digits after comma
        const char csPrefix[] = "var: ";
        const char csSuffix[] = " [ms]  ";
        const char csDefault[] = "<0.001";   // Default value

        // If the average variance is lower then 0.001 ms, print default value
        bool bPrintDefault = 0;
        if (iVarms < 0.001)
            bPrintDefault = 1;

        // Print the record
        _post_print_record_float(csBuf, iMaxVarms,
                                 iVarms,
                                 csPrefix, csSuffix, csDefault,
                                 iDAC, bPrintDefault);
        strOut += csBuf;
    }

    return strOut;
}


std::string Cosniwa::_post_print_single_snippet_data_min_time(TR stTR,
                                                              TRPar stTRPar)
{
/*
 * _post_print_single_snippet_data_min_time: (POSTPROCESSING  RESULTS PRINTING)
 *                                            PRINT MINIMUM CALL TIME FOR
 *                                            A CODE SNIPPET
 *
 * Parameters:
 *   stTR:  [TR structure]   Structure with timing results for the code snippet
 *
 *   stTRParam:  [TRPar structure]   Structure with general timing results
 *                                   parameters
 *
 * Returns:
 *   strOut:  [str::string]   String with formatted minimum (shortest) call
 *                            time for a code snippet
 *
 */

    std::string strOut="";    // Start out string
    char csBuf[iTempBufSiz];

    // Print the minimum call time only if the code snippet was called more
    // than once
    if (stTR.nCalls > 1)
    {
        double iMaxTMinms = (double)stTRPar.tMinMax / 1000;
        double iTMinms = (double)stTR.tMin / 1000;

        int iDAC = 3;   // The number of digits after comma
        const char csPrefix[] = "min/max call: ";
        const char csSuffix[] = "/";
        const char csDefault[] = "<0.001";   // Default value

        // If the minimum time is lower than 0.001 ms, print default value
        bool bPrintDefault = 0;
        if (iTMinms < 0.001)
            bPrintDefault = 1;

        // Print the record
        _post_print_record_float(csBuf, iMaxTMinms, iTMinms,
                                 csPrefix, csSuffix, csDefault,
                                 iDAC, bPrintDefault);
        strOut += csBuf;
    }

    return strOut;
}


std::string Cosniwa::_post_print_single_snippet_data_max_time(TR stTR,
                                                              TRPar stTRPar)
{
/*
 * _post_print_single_snippet_data_max_time: (POSTPROCESSING  RESULTS PRINTING)
 *                                            PRINT MAXIMUM CALL TIME FOR
 *                                            A CODE SNIPPET
 *
 * Parameters:
 *   stTR:  [TR structure]   Structure with timing results for the code snippet
 *
 *   stTRParam:  [TRPar structure]   Structure with general timing results
 *                                   parameters
 *
 * Returns:
 *   strOut:  [str::string]   String with formatted maximum (longest) call time
 *                            for a code snippet
 *
 */

    std::string strOut="";    // Start out string
    char csBuf[iTempBufSiz];

    // Print the maximum call time only if the code snippet was called more
    // than once
    if (stTR.nCalls > 1)
    {
        double iMaxTMaxms = (double)stTRPar.tMaxMax / 1000;
        double iTMaxms = (double)stTR.tMax / 1000;

        int iDAC = 3;   // The number of digits after comma
        const char csPrefix[] = "";
        const char csSuffix[] = " [ms]";
        const char csDefault[] = "<0.001";   // Default value

        // If the minimum time is lower than 0.001 ms, print default value
        bool bPrintDefault = 0;
        if (iTMaxms < 0.001)
            bPrintDefault = 1;

        // Print the record
        _post_print_record_float(csBuf, iMaxTMaxms, iTMaxms,
                                 csPrefix, csSuffix, csDefault,
                                 iDAC, bPrintDefault);
        strOut += csBuf;
    }

    return strOut;
}


std::string Cosniwa::_post_print_single_snippet_data_short_call(TR stTR,
                                                                TRPar stTRPar)
{
/*
 * _post_print_single_snippet_data_short_call: (POSTPROCESSING  RESULTS PRINT.)
 *                                              PRINT WARNING THAT THERE WAS
 *                                              A CALL WHICH WAS TOO SHORT TO
 *                                              MEASURE
 *
 * Parameters:
 *   stTR:  [TR structure]   Structure with timing results for the code snippet
 *
 *   stTRParam:  [TRPar structure]   Structure with general timing results
 *                                   parameters
 *
 * Returns:
 *   strOut:  [str::string]   String with a warning about too short call
 *
 */

    std::string strOut="";    // Start out string
    char csBuf[iTempBufSiz];

    unsigned int nShortCalls = stTR.nShortCalls;
    if (nShortCalls > 0)
    {
        sprintf(csBuf, "      WARNING!     ");
        if (nShortCalls == 1)
        {
            sprintf(csBuf, "%s There was %d call ", csBuf, nShortCalls);
        }
        else
        {
            sprintf(csBuf, "%s There were %d calls ", csBuf, nShortCalls);
        }
        sprintf(csBuf, "%stoo short to measure (< 1us)", csBuf);
        sprintf(csBuf, "%s for code snippet #%d !\n", csBuf, stTR.iRego);
        strOut += csBuf;
    }

    return strOut;
}


int Cosniwa::_post_print_record_int(char* csBuffer, int iMaxNum, int iValue,
                                   const char* csPrefix, const char* csSuffix)
{
/*
 * _post_print_record_int: (POSTPROCESSING  RESULTS PRINTING)
 *                          FORMAT AN INTEGER RECORD ENTRY (v1)
 *
 *
 *   Add an integer record entry (v1):
 *
 *   Record = prefix + [Padded augmented number] + suffix
 *   Padded  number = {space padding} + number
 *
 *
 * Parameters:
 *   csBuffer:  [char*]         Buffer where the record will be printed
 *   iMaxNum:   [int]           Maximum possible number
 *   iValue:    [int]           VALUE of the number to be printed
 *   csPrefix:  [const char*]   Prefix before the record
 *   csSuffix:  [const char*]   Suffix after the record
 *
 * Returns:
 *   iNChar:  [int]   The number of characters written to the record
 *
 */

    // Auxiliary buffers:...
    char csAuxBufNum[iTempBufSiz];     // ... for the number
    char csAuxBufNumPad[iTempBufSiz];  // ... for the number padded with spaces
    char csAuxBufPad[iTempBufSiz];     // ... for the spaces padding

    // Max number of characters in the number:
    unsigned int iMaxCharInNum;

    // The number of characters in the number (in the current case):
    unsigned int iCharInNum;

    // The number of missing characters in the number
    int iNumCharMissing;

    // Returned variable
    int iNChar;   // The number of characters written to the record

    // Compute the max number of characters in the number
    sprintf(csAuxBufNum, "%d", iMaxNum);
    iMaxCharInNum = strlen(csAuxBufNum);

    // *** Print the record ***

    // Create space padding
    iCharInNum = sprintf(csAuxBufNum,"%d", iValue);
    iNumCharMissing = iMaxCharInNum - iCharInNum;
    if (iNumCharMissing < 0)
        iNumCharMissing = 0;
    _post_print_space_padding(csAuxBufPad, iNumCharMissing);

    // Add space padding to the number
    sprintf(csAuxBufNumPad, "%s%d", csAuxBufPad, iValue);

    // Create the final record
    iNChar = sprintf(csBuffer, "%s%s%s", csPrefix, csAuxBufNumPad, csSuffix);

    return iNChar;
}


int Cosniwa::_post_print_record_int(char* csBuffer, int iMaxNum, int iValue,
                                   const char* csPrefix, const char* csInvo,
                                   const char* csSuffix)

{
/*
 * _post_print_record_int: (POSTPROCESSING  RESULTS PRINTING)
 *                          FORMAT AN INTEGER RECORD ENTRY (v2)
 *
 *
 *   Add an integer record entry (v2):
 *
 *   Record = prefix + [Padded augmented number] + suffix
 *   Padded augmented number = invocation + {space padding} + number
 *   Augmented number = invocation + number
 *
 *
 * Parameters:
 *   csBuffer:  [char*]         Buffer where the record will be printed
 *   iMaxNum:   [int]           Maximum possible number
 *   iValue:    [int]           VALUE of the number to be printed
 *   csPrefix:  [const char*]   Prefix before the record
 *   csInvo:    [const char*]   Invocation before a number (e.g. #)
 *   csSuffix:  [const char*]   Suffix after the record
 *
 * Returns:
 *   iNChar:  [int]   The number of characters written to the record
 *
 */

    // Auxiliary buffers:...
    char csAuxBufNum[iTempBufSiz];         // ... for the number
    char csAuxBufAugNum[iTempBufSiz];      // ... for the augmented number
    char csAuxBufAugNumPad[iTempBufSiz];   // ... for the augmented number
                                           //     padded with spaces
    char csAuxBufPad[iTempBufSiz];         // ... for the spaces padding

    // Max number of characters in (in the current case):
    unsigned int iMaxCharInNum;   // the number
    unsigned int iMaxCharInInv;   // the invocation
    unsigned int iMaxCharAugNum;  // the augmented number

    // The number of characters in:
    unsigned int iCharInAugNum;  // augmented number

    // The number of missing characters:
    int iAugNumCharMissing;  // the augmented number

    // Returned variable
    int iNChar;   // The number of characters written to the record

    // Compute the max number of characters in the number
    sprintf(csAuxBufNum, "%d", iMaxNum);
    iMaxCharInNum = strlen(csAuxBufNum);

    // Compute the max number of characters in the invocation
    iMaxCharInInv = strlen(csInvo);

    // Compute the max number of character in the augmented number
    // [invocation + minus + number ]
    iMaxCharAugNum = iMaxCharInInv + iMaxCharInNum;

    // *** Print the record ***

    // Create an augmented number
    iCharInAugNum = sprintf(csAuxBufAugNum,"%s%d", csInvo, iValue);
    iAugNumCharMissing = iMaxCharAugNum - iCharInAugNum;
    if (iAugNumCharMissing < 0)
        iAugNumCharMissing = 0;

    // Create space padding
    _post_print_space_padding(csAuxBufPad, iAugNumCharMissing);

    // Add space padding to the augmented number
    sprintf(csAuxBufAugNumPad, "%s%s%d", csInvo, csAuxBufPad, iValue);

    // Create the final record
    iNChar = sprintf(csBuffer, "%s%s%s", csPrefix, csAuxBufAugNumPad, csSuffix);

    return iNChar;
}


int Cosniwa::_post_print_record_float(char* csBuffer, double iMaxNum,
                                      double iValue,
                                      const char* csPrefix,
                                      const char* csSuffix,
                                      int iDAC)
{
/*
 * _post_print_record_float: (POSTPROCESSING  RESULTS PRINTING)
 *                            FORMAT A FLOAT RECORD ENTRY (v1)
 *
 *
 *   Add a float record entry:
 *
 *   Record = prefix + [Padded augmented number] + suffix
 *   Padded number = {space padding} + number
 *
 *
 * Parameters:
 *   csBuffer:  [char*]         Buffer where the record will be printed
 *   iMaxNum:   [double]        Maximum possible number
 *   iValue:    [double]        VALUE of the number to be printed
 *   csPrefix:  [const char*]   Prefix before the record
 *   csSuffix:  [const char*]   Suffix after the record
 *   iDAC:      [int]           The number of Digits After Comma
 *
 * Returns:
 *   iNChar:  [int]   The number of characters written to the record
 *
 */

    // Auxiliary buffers:...
    char csAuxBufNum[iTempBufSiz];      // ... for the number
    char csAuxBufNumPad[iTempBufSiz];   // ... for the augmented number
                                        //     padded with spaces
    char csAuxBufPad[iTempBufSiz];      // ... for the spaces padding

    // Max number of characters in (in the current case):
    unsigned int iMaxCharInNum;   // the number

    // The number of characters in number
    unsigned int iCharInNum;

    // The number of missing characters in :
    int iNumCharMissing;              // the number

    // Returned variable
    int iNChar;   // The number of characters written to the record

    // Compute the max number of characters in the max number
    int iMaxNumRounded = floor(iMaxNum);
    sprintf(csAuxBufNum, "%d", iMaxNumRounded);
    iMaxCharInNum = strlen(csAuxBufNum);

    // Compensate for comma and digits after the comma
    iMaxCharInNum = iMaxCharInNum + iDAC + 1;

    // Print the record:
    char csFormatString[iTempBufSiz];
    sprintf(csFormatString,"%%.%df", iDAC);
    iCharInNum = sprintf(csAuxBufNum, csFormatString, iValue);

    // Create space padding
    iNumCharMissing = iMaxCharInNum - iCharInNum;
    if (iNumCharMissing < 0)
        iNumCharMissing = 0;
    _post_print_space_padding(csAuxBufPad, iNumCharMissing);

    // Add space padding to the augmented number
    sprintf(csFormatString,"%%s%%.%df", iDAC);
    sprintf(csAuxBufNumPad, csFormatString, csAuxBufPad, iValue);

    // Create the final record
    iNChar = sprintf(csBuffer, "%s%s%s", csPrefix, csAuxBufNumPad, csSuffix);
    return iNChar;
}


int Cosniwa::_post_print_record_float(char* csBuffer, double iMaxNum,
                                      double iValue,
                                      const char* csPrefix,
                                      const char* csSuffix,
                                      const char* csEmpty, int iDAC,
                                      bool bEmpty)
{
/*
 * _post_print_record_float: (POSTPROCESSING  RESULTS PRINTING)
 *                            FORMAT A FLOAT RECORD ENTRY (v2)
 *
 *
 * Add a float record entry:
 *
 *  1)  If bEmpty == 0
 *       Record = prefix + [Padded augmented number] + suffix
 *
 *       Padded number = {space padding} + number
 *
 *
 *  2)  If bEmpty == 1
 *       Record = prefix + [Padded empty string] + suffix
 *
 *       [Padded empty string] = {space padding} + csEmpty
 *
 *
 * Parameters:
 *   csBuffer:  [char*]         Buffer where the record will be printed
 *   iMaxNum:   [double]        Maximum possible number
 *   iValue:    [double]        VALUE of the number to be printed
 *   csPrefix:  [const char*]   Prefix before the record
 *   csSuffix:  [const char*]   Suffix after the record
 *   csEmpty:   [const char*]   String used if bEmpty = 1
 *   iDAC:      [int]           The number of Digits After Comma
 *   bEmpty:    [bool]          Flag: Keep the whole record empty
 *
 * Returns:
 *   iNChar:  [int]   The number of characters written to the record
 *
 */

    // Auxiliary buffers:...
    char csAuxBufNum[100];      // ... for the number
    char csAuxBufNumPad[100];   // ... for the augmented number
                                // ... padded with spaces
    char csAuxBufPad[100];      // ... for the spaces padding

    // Max number of characters in (in the current case):
    unsigned int iMaxCharInNum;   // the number
    unsigned int iMaxCharInEmp;   // the empty string

    // The number of characters in number
    unsigned int iCharInNum;

    // The number of missing characters in:
    unsigned int iEmptyCharMissing;   // empty
    int iNumCharMissing;              // the number

    // Returned variable
    int iNChar;   // The number of characters written to the record

    // Compute the max number of characters in the max number
    int iMaxNumRounded = floor(iMaxNum);
    sprintf(csAuxBufNum, "%d", iMaxNumRounded);
    iMaxCharInNum = strlen(csAuxBufNum);

    // Compensate for comma and digits after the comma
    iMaxCharInNum = iMaxCharInNum + iDAC + 1;

    // Max number of characters in 'empty'
    iMaxCharInEmp = strlen(csEmpty);

    //  Correct the maximum number of characters in the number:
    //  it can not be lower then the number of characters in empty
    if (iMaxCharInEmp > iMaxCharInNum)
        iMaxCharInNum = iMaxCharInEmp;

    // Print the record
    if (bEmpty == 0)
    {
        // *** Print the record ***
        char csFormatString[100];
        sprintf(csFormatString,"%%.%df", iDAC);
        iCharInNum = sprintf(csAuxBufNum, csFormatString, iValue);

        iNumCharMissing = iMaxCharInNum - iCharInNum;
        if (iNumCharMissing < 0)
            iNumCharMissing = 0;

        // Create space padding
        _post_print_space_padding(csAuxBufPad, iNumCharMissing);

        // Add space padding to the augmented number
        sprintf(csFormatString,"%%s%%.%df", iDAC);

        sprintf(csAuxBufNumPad, csFormatString, csAuxBufPad, iValue);

        // Create the final record
        iNChar = sprintf(csBuffer, "%s%s%s",
                         csPrefix, csAuxBufNumPad, csSuffix);
    }
    else
    {
        // *** Leave the record empty ***

        // Compute the number of missing characters in empty string
        iEmptyCharMissing = iMaxCharInNum - iMaxCharInEmp;

        // Create zero padding
        _post_print_space_padding(csAuxBufPad, iEmptyCharMissing);

        // Add zero padding to the empty message
        sprintf(csAuxBufNumPad, "%s%s", csAuxBufPad, csEmpty);

        // Create the final record
        iNChar = sprintf(csBuffer, "%s%s%s",
                         csPrefix, csAuxBufNumPad, csSuffix);
    }

    return iNChar;
}


void Cosniwa::_post_print_space_padding(char* csBuffer, unsigned int iNPad)
{
/*
 * _post_print_space_padding: (POSTPROCESSING  RESULTS PRINTING)
 *                             PRINT EMPTY SPACES TO A BUFFER
 *
 *
 * Function prints empty spaces to a buffer.
 *
 *
 * Parameters:
 *   csBuffer:  [char*]    Buffer where the empty space will be printed
 *
 *   iNPad:     [int]      The number of empty spaces to be printed
 *
 */

    for(unsigned int inxChr=0; inxChr < iNPad; inxChr++)
    {
        csBuffer[inxChr] = ' ';
    }
    csBuffer[iNPad] = 0;
}



void Cosniwa::_post_deallocate(unsigned int nURego, unsigned int* isRego,
                               unsigned int* isTSInx, TR* stsResults)
{
/*
 * _post_deallocate: (POSTPROCESSING)  DEALLOCATE MEMORY STRUCTURES
 *
 *
 * Parameters:
 *   nURego:   [unsigned int]   The number of unique code snippet registrations
 *
 *   isRego:   [unsigned int*]   Pointer to table with unique code snippet
 *                               registrations
 *
 *   issTSInx:   [unsigned int**]   Pointer to a table with sorted indices of
 *                                  unique code snippet registrations - sorted
 *                                  by the total call time
 *
 *   stsResults:  [TR structure*]   Pointer to structures with timing results
 *                                  for every code snippet registration
 *
 */

    // Loop over all the unique registrations
    for(unsigned int inxRego = 0; inxRego < nURego; inxRego++)
    {
        delete stsResults[inxRego].isCallT;
    }

    // Delete structures with timing results
    delete stsResults;

    delete isTSInx;

    // Delete a table with unique code snippet registrations
    delete isRego;
}


/* **************************************************** */
/* INTERNAL CODE SNIPPET REGISTRATION FUNCTIONS: */
/* **************************************************** */

std::string Cosniwa::_reg_label_for_rego(unsigned int iRego)
{
/*
 * _reg_label_for_rego:   MATCH A CODE SNIPPET REGO WITH A CODE SNIPPET LABEL
 *
 *
 * Parameters:
 *   iRego:  [unsigned int]   Code snippet registration number
 *
 *
 * Returns:
 *   [str::string]   String with the found label, empty string ("") if rego
 *                   not found in the databse
 *
 */

    // Loop over all the labels
    for(unsigned int inxLabel = 0; inxLabel < nCSLabels; inxLabel++)
    {
        // Check if the rego macthes the searched rego
        // If yes, returned the label
        if (isCSRego[inxLabel] == iRego)
        {
            return strssCSLabels[inxLabel][0];
        }
    }

    // Rego was not found
    std::string strEmpty = "";
    return strEmpty;
}


int Cosniwa::_reg_is_label_in_labels(std::string strLabel)
{
/*
 * _reg_is_label_in_labels:   CHECK IF A LABEL EXISTS IN THE TIMESTAMP DATABASE
 *
 *
 * Parameters:
 *   strLabel:  [std::string]  Code snippet label
 *
 * Returns:
 *   [int]   Code snippet registration matched with the label
 *           (NOT_FOUND if label not found)
 *
 */

    // Loop over all the labels
    for(unsigned int inxLabel = 0; inxLabel < nCSLabels; inxLabel++)
    {
        // Check if the label matches the searched label
        if(strssCSLabels[inxLabel][0] == strLabel)
        {
            return isCSRego[inxLabel];
        }
    }

    // Label was not found
    return NOT_FOUND;
}


unsigned int Cosniwa::_reg_next_free_rego()
{
/*
 * _reg_next_free_rego:   FIND NEXT FREE CODE SNIPPET REGISTRATION NUMBER
 *
 *
 * Returns:
 *   [unsigned int]   Found the next free code snippet registration number
 *                    (0 if no free number found)
 *
 */

    // Loop over all the possible registration numbers
    for(unsigned int inxRego = 1; inxRego < nRegoMax; inxRego++)
    {
        // If this code snippet rego is not yet the database, use it
        if ((_reg_is_rego_in_labels(inxRego) == NOT_FOUND) &&
            (_reg_is_rego_in_TS(inxRego) == NOT_FOUND))
        {
            return inxRego;
        }
    }

    // No free number was found
    return 0;
}


int Cosniwa::_reg_is_rego_in_labels(unsigned int iRego)
{
/*
 * _reg_is_rego_in_labels:   IS REGO IN LABELS?
 *
 *
 * Parameters:
 *   iRego: [unsigned int]   Code snippet registration number
 *
 * Returns:
 *   inxLabel:  [int]   Index of code snippet label in labels databse
 *                      matched with the parameter Code snippet registration
 *                      number 'iRego'  (NOT_FOUND if label was not found)
 *
 */

    // Loop over all the code snippet labels
    for(unsigned int inxLabel = 0; inxLabel < nCSLabels; inxLabel++)
    {
        // If a tested rego is present in the code snippet labels,
        // return that it is found
        if (isCSRego[inxLabel] == iRego)
        {
            return inxLabel;
        }
    }

    // All the code snippet labels were searched and nothing was found
    return NOT_FOUND;
}


int Cosniwa::_reg_is_rego_in_TS(unsigned int iRego)
{
/*
 * _reg_is_rego_in_TS:   IS REGO IN TIMESTAMPS DATABASE?
 *
 *
 * Parameters:
 *   iRego: [unsigned int]   Code snippet registration number
 *
 * Returns:
 *   [int (bool)]   FOUND =>  check result: iRego was found
 *                  NOT_FOUND =>  check result: iRego was not found
 *
 */

    // Loop over all the timestamps database
    for(unsigned int inxTS = 0; inxTS<iTSCtr; inxTS++)
    {
        // If a tested rego is present in the timestamps library,
        // return that it is found
        if (isTSRego[inxTS] == iRego)
        {
            return FOUND;
        }
    }

    // The whole timestamps database was searched and nothing was found
    return NOT_FOUND;
}


