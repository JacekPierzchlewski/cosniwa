%
% cosniwa_result.m [version 1.0]
% CoSniWa:  COde SNIppet stopWAtch [Octave port] - Results postprocessing
%                                                  module.
%
% CoSniWa is dedicated to profile code using time stamps.
% Cosniwa  [Octave port - native .m implementation ] v1.0, 30 May 2017.
%
% read more on: www.speedupcode.com
%
% (c) Jacek Pierzchlewski, 2017  jacek@pierzchlewski.com
% license: BSD-2-Clause.
%


function strRes = cosniwa_result(csw, bShort=0)
%
%  cosniwa_result:
%
%  (POSTPROCESSING)  MAIN RESULTS POSTPROCESSING FUNCTION.
%
%  Process timestamps and create a string with timing results.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%    csw     [structure]  Cosniwa structure
%
%    bShort  [bool]       Flag: short / full results message
%                         Default: 0
%
%  Return:
%
%    strRes  [std::string]  String with timing results.
%
% -----------------------------------------------------------------------------
%  The following data is added to csw structure.
%
%  1. csw.stTRParam:  structure with general parameters of timing results
%
%      1.1 csw.stTRParam.bMainTimeMeasured:  flag that the main time
%                                            was measured
%
%      1.2 csw.stTRParam.iLongestLabelSiz:   length of the longest code snippet
%                                            label
%
%      1.3 csw.stTRParam.iHighRego:          the highest code snippet
%                                            registraion number
%
%      1.4 csw.stTRParam.tTotalMax:          the maximum total time
%
%      1.5 csw.stTRParam.nCallsMax:          the maximum number of calls for
%                                            a code snippet
%
%      1.6 csw.stTRParam.tAvgMax:            the maximum average time of a
%                                            code snippet call
%
%      1.7 csw.stTRParam.tVarMax:            the maximum variance of code
%                                            snippet calls
%
%      1.8 csw.stTRParam.dPartMax:           the maximum fraction of
%                                            the main time
%
%      1.9 csw.stTRParam.dMaxSpeedUpMax:     the maximum max possible speed up
%                                            corresponding to a single code
%                                            snippet
%
%      1.10 csw.stTRParam.tMinMax:        the maximum min time of a single call
%
%
%      1.11 csw.stTRParam.tMaxMax:        the maximum max time of a single call
%
%
%  2. csw.nURego:  the number of unique code snippet registrations
%
%  3. csw.vRego:   vector with unique code snippet registrations
%
%  4. csw.cstResults:  cell vector with a result structures for every
%                      code snippet registration
%
%          The cell vector cstResults has a shape (csw.nURego x 1).
%          Every element of the cell is a structure with timing results
%          for a single code registration.
%          Structure in csw.cstResults{1} corresponds to code registraion
%          csw.vRego(1), csw.cstResults{2} => csw.vRego(2), and so on.
%
%          Every element of the cell is a structure with the following fields:
%
%              4.1  csw.cstResults{:}.nCalls - the number of calls of
%                                             corresponding code registration.
%
%              4.2  csw.cstResults{:}.vCallT - vector with times of calls
%
%              4.3  csw.cstResults{:}.iRego - registration from vRego
%
%              4.4  csw.cstResults{:}.tTotalTime - the total time
%                                                  of all the calls
%
%              4.5  csw.cstResults{:}.tMin - minimum time of a call
%
%              4.6  csw.cstResults{:}.tMax - maximum time of a call
%
%              4.7  csw.cstResults{:}.nShortCalls - the number of short calls
%                                                   (calls lower than 1 us)
%
%              4.8  csw.cstResults{:}.tAvg - the average time of a single call
%
%              4.9  csw.cstResults{:}.dPart - which part of the main time
%                                             is taken by all the calls from
%                                             the current snippet
%
%              4.10 csw.cstResults{:}.iVar - the variance of calls
%
%              4.11 csw.cstResults{:}.dMaxSpeedUp - max speed up according
%                                                   to Amdahl's law
%
%
%  5. csw.tTotalTime:  time between cosniwa_start() and cosniwa_stop(),
%                      (if measured)
%
%  It is preassumed that the following data is present in csw structure in
%  the moment of call to `cosniwa_postprocessing`.
%
%  1. csw.iTSCtr:    counter of time stamps (equal to the number of timestamps)
%
%  2. csw.vTS:       timestamp
%  3. csw.vTSRego:   registrations of timestamps
%  4. csw.vTSMark:   marker corresponding to a timestamp (csw.START or CSW.STOP)
%
%  5. csw.nCSLabels:   the number of labels
%  6. csw.cLabels:     cell vector with labels
%  7. csw.vLabelsReg:  registrations corresponding to labels
% -----------------------------------------------------------------------------
%
    % Initialise structure with general parameters of timing results
    % (One structure for all the code snippets registrations)
    csw.stTRParam = struct();

    % Count the unique code snippet registrations
    csw = post_count_rego(csw);

    % Start a cell vector of the timing results structures
    % for all the unique code snippet registrations
    csw = post_start_result_structures(csw);

    % Check consistency of the time stamps
    [bCheckRes, csw]= post_check(csw);
    if (bCheckRes == csw.FAIL)
        printf('CoSniWa Error: ');
        printf('Timestamps are inconsistent! ABORT!\n');
        return;
    end

    % Count the number of calls for every code snippet registration
    csw = post_count_calls(csw);

    % Allocate a vector for call times for all the unique code registratons
    csw = post_allocate_call_times(csw);

    % Measure the call times for all the registrations,
    % and fill up the vectors with call times
    csw = post_measure_call_times(csw);

    % Process the table with call times for all the registrations
    csw = post_process_call_times(csw);

    % Sort the code snippets by the total execution time
    csw = post_sort(csw);

    % Fill up the structure with general timing results parameters
    csw = post_find_general_param(csw);

    % Print the timing results
    strRes = post_print_timing(csw, bShort);
end


function csw = post_count_rego(csw)
%
%  post_count_rego:
%
%  (POSTPROCESSING)  COUNT THE UNIQUE CODE SNIPPET REGISTRATIONS.
%
%  Function counts the number of unique code snippet registrations in the
%  timestamps database (stored in csw.nURego).
%  Additionally the function fills up a vector (csw.vRego) with unique code
%  snippet registrations.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:     [structure]  Cosniwa structure
%
%  Return:
%      csw:     [structure]  Cosniwa structure
%          added:   csw.nURego
%                   csw.vRego
%
% -----------------------------------------------------------------
%
%  Example (1):
%
% 1:     stoper.start();   // START
% 2:
% 3:     stoper.lapstart(1);
% 4:     stoper.lapstop(1);
% 5:
% 6:     stoper.lapstart(2);
% 7:     stoper.lapstop(2);
% 8:
% 9:     stoper.stop();
%
% vRego: [ 0, 1, 2 ], nURego: 3
%
%
% -----------------------------------------------------------------
%
% Example (2):
%
% 1:     stoper.start();   // START
% 2:
% 3:     stoper.lapstart(1);
% 4:     stoper.lapstop(1);
% 5:
% 6:     stoper.lapstart(2);
% 7:     stoper.lapstop(2);
% 8:
% 9:     stoper.lapstart(13);
% 10:    stoper.lapstop(13);
% 11:
% 12:    stoper.lapstart(13);
% 13:    stoper.lapstop(13);
% 14:
% 15:    stoper.lapstart(14);
% 16:    stoper.lapstop(14);
% 17:
% 18:    stoper.stop();
%
% vRego: [ 0, 1, 2, 13, 14 ], nURego: 5
%
%
    % Remove -1 (empty space)
    vRegoClean = csw.vTSRego(csw.vTSRego~= -1);

    % Create the internal vector with unique registrations
    csw.vRego = unique(vRegoClean);

    % Count unique registrations
    csw.nURego = size(csw.vRego, 1);
end


function csw = post_start_result_structures(csw)
%
%  post_start_result_structures:
%
%  (POSTPROCESSING)  START A CELL VECTOR WITH TIMING RESULTS STRUCTURES
%                    FOR ALL THE UNIQUE CODE SNIPPET REGISTRATIONS.
%
%  Function starts a new cell vector `cstResults` with structures `stResults`
%  for every unique code snippet registration.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%    csw:     [structure]  Cosniwa structure
%
%  Return:
%    csw:     [structure]  Cosniwa structure
%        added:   csw.cstResults
%
    csw.cstResults = cell(csw.nURego, 1);   % Allocate cell vector

    % Start a results structure for all the unique code registrations
    for inxRego=1:csw.nURego
        csw.cstResults{inxRego} = struct();
    endfor
end


function [bRes, csw] = post_check(csw)
%
%  post_check:
%
%  (POSTPROCESSING)  CHECK IF THE MEASUREMENTS ARE CONSISTENT.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:     [structure]  Cosniwa structure
%
%  Return:
%       bRes:  [bool]  csw.OK =>  check result: pass check flag
%                      csw.FAIL =>  check result: failed check flag
%
%       csw:  [structure]  Cosniwa structure
%           added:   csw.stTRParam.bMainTimeMeasured - flag informing if the
%                                                      main time was measured

    % Check if stoper was correctly started and stoped
    [bRes, csw] = post_check_start_stop(csw);
    if (bRes == csw.FAIL)
        return;
    end

    % Check if the timestamps are correctly interleaved
    % (start-stop-start-stop- ... -start-stop)
    bRes = post_check_interleave(csw);
    if (bRes == csw.FAIL)
        return;
    end

    % it looks like everything is ok, return
    bRes = csw.OK;
    return;
end


function [bRes, csw] = post_check_start_stop(csw)
%
%  post_check_start_stop:
%
%  (POSTPROCESSING)  CHECK IF STOPER WAS CORRECTLY STARTED AND STOPPED.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:     [structure]  Cosniwa structure
%
%  Return:
%       bRes: [bool]  csw.OK =>  check result: pass check flag
%                     csw.FAIL =>  check result: failed check flag
%
%       csw: [structure]  Cosniwa structure
%           added:   csw.stTRParam.bMainTimeMeasured - flag informing if the
%                                                      main time was measured
%

    % If no measurements were added, everything is ok
    if (csw.iTSCtr == 0)

        % Note that the main time was not measured
        csw.stTRParam.bMainTimeMeasured = csw.MAIN_TIME_OFF;

        % everything is ok and return
        bRes = csw.OK;
        return;
    end

    % Check if the first timestamp comes from the main code.
    % If yes, then check if the stoper was correctly started and stoped.
    % If not, then check if timestamps from the main code are not present
    % anywhere in the timestamp database
    if (csw.vTSRego(1) == csw.MAIN_REGO) && (csw.vTSMark(1) == csw.START)

        % Note that the main time was measured
        csw.stTRParam.bMainTimeMeasured = csw.MAIN_TIME_ON;

        % Check timestamps consistency with main time measured
        bRes = post_check_start_stop_with_main(csw);

    else

        % Note that the main time was not measured
        csw.stTRParam.bMainTimeMeasured = csw.MAIN_TIME_OFF;

        % Check timestamps consistency without main time measured
        bRes = post_check_start_stop_without_main(csw);
    end
    return;
end


function bRes = post_check_start_stop_with_main(csw)
%
%  post_check_start_stop_with_main:
%
%  (POSTPROCESSING)  CHECK IF STOPER WAS CORRECTLY STARTED AND STOPPED
%                    (FUNCTION USED IF THE MAIN TIME WAS MEASURED).
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:     [structure]  Cosniwa structure
%
%  Return:
%      bRes: [bool]  csw.OK =>  check result: pass check flag
%                    csw.FAIL =>  check result: failed check flag
%
    % Check if stoper was correctly started and stoped
    if (post_check_first_timestamp_is_main(csw) == 0)
        printf('CoSniWa Error: ');
        printf('If used, the Main Stopwatch must be started first!\n');
        bRes = csw.FAIL;
        return;
    end
    if (post_check_last_timestamp_is_main(csw) == 0)
        printf('CoSniWa Error: ');
        printf('If used, the Main Stopwatch must be stopped last!\n');
        bRes = csw.FAIL;
        return;
    end

    % Check if stoper was not started/stopped in the middle of time stamps
    for inxTS = 2:(csw.iTSCtr - 1)

        % Rego '0' can be only at the beggining and at the end
        if (csw.vTSRego(inxTS) == csw.MAIN_REGO)
            printf('CoSniWa Error: ');
            printf('If used, the Main Stopwatch must be started first ');
            printf('and stopped last!\n');
            bRes = csw.FAIL;
            return;
        end
    endfor

    % Everything is ok
    bRes = csw.OK;
    return;
end


function bRes = post_check_first_timestamp_is_main(csw)
%
%  post_check_first_timestamp_is_main:
%
%  (POSTPROCESSING)  CHECK IF THE FIRST TIMESTAMP IS THE START TIMESTAMP Of THE
%                    MAIN STOPWATCH.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:     [structure]  Cosniwa structure
%
%  Return:
%      bRes: [bool]  1 => check result: it is the start timestamp of
%                                       the main stopwatch
%
%                    0 => check result: it is NOT the start timestamp of
%                                       the main stopwatch
%
    bRes = ((csw.vTSRego(1) == csw.MAIN_REGO) && (csw.vTSMark(1) == csw.START));
end


function bRes = post_check_last_timestamp_is_main(csw)
%
%  post_check_last_timestamp_is_main:
%
%  (POSTPROCESSING)  CHECK IF THE LAST TIMESTAMP IS THE STOP TIMESTAMP Of THE
%                    MAIN STOPWATCH.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:     [structure]  Cosniwa structure
%
%  Return:
%       bRes: [bool]  1 => check result: it is the stop timestamp of
%                                        the main stopwatch
%
%                     0 => check result: it is NOT the stop timestamp of
%                                        the main stopwatch
%

    inxTSLast = csw.iTSCtr;  % Index of the last stopwatch
    bRes = ((csw.vTSRego(inxTSLast) == csw.MAIN_REGO) &&
            (csw.vTSMark(inxTSLast) == csw.STOP));
end


function bRes = post_check_start_stop_without_main(csw)
%
%  post_check_start_stop_without_main:
%
%  (POSTPROCESSING)  CHECK IF STOPER WAS CORRECTLY STARTED AND STOPPED
%                    (FUNCTION USED IF THE MAIN TIME WAS MEASURED).
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:     [structure]  Cosniwa structure
%
%  Return:
%      bRes: [bool]  csw.OK =>  check result: pass check flag
%                    csw.FAIL =>  check result: failed check flag
%

    % Check if stoper was not started/stopped anywhere in the time stamps
    for inxTS = 1:csw.iTSCtr

        % Rego MAIN_REGO can be only at the beggining and at the end
        if (csw.vTSRego(inxTS) == csw.MAIN_REGO)
            printf('CoSniWa Error: Illegal Main Stopwatch ');
            if (csw.vTSRego(inxTS) == csw.START)
                printf('start (timestamp #%d)!\n', inxTS);
            else
                printf('stop (timestamp #%d)!\n', inxTS);
            end
            bRes = csw.FAIL;
            return;
        end
    endfor

    % Everything is ok
    bRes = csw.OK;
    return;
end


function bRes = post_check_interleave(csw)
%
%  post_check_interleave:
%
%  (POSTPROCESSING)  CHECK IF THE TIMESTAMPS ARE CORRECTLY INTERLEAVED.
%
%  Function checks if timestamps are correctly interleaved
%  (start-stop-start-stop- ... -start-stop).
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%    csw:  [structure]  Cosniwa structure
%
%  Return:
%    bRes: [bool]  csw.OK =>  check result: pass check flag
%                  csw.FAIL =>  check result: failed check flag
%
%

    % Loop over all unique code snippet registrations
    for inxRego = 1:csw.nURego

        % Main rego was already checked
        if inxRego == csw.MAIN_REGO
            continue;
        end

        % Get the current checked rego
        iRego = csw.vRego(inxRego);

        % Reset the counter of calls
        nCalls = 0;

        % Loop over all time stamps
        iExpMarker = csw.START;   % Current expected marker

        % Loop over all time stamps
        for inxTS = 1:csw.iTSCtr
            % If the time stamp is not about the currently tested rego, go
            % further
            if csw.vTSRego(inxTS) ~= iRego
                continue;
            end

            % Increase the number of calls of the current code snippet
            % registration
            nCalls++;

            % Check if the time stamp has correct start/stop marker
            if (csw.vTSMark(inxTS) == iExpMarker)

                % marker is ok, change the expected marker value
                if (iExpMarker == csw.START)
                    iExpMarker = csw.STOP;
                else
                    iExpMarker = csw.START;
                end
            else
                % marker is incorrect, change the expected marker value
                printf('CoSniWa Error: Start/stop interleave error ');
                printf('for rego #%d ', iRego);
                if iExpMarker == csw.START
                    printf('call: #%d!\n', nCalls);
                    printf('CoSniWa Error: ');
                    printf('Stop timestamp found without previous start!\n');
                else
                    printf('call: #%d!\n', (nCalls + 1));
                    printf('CoSniWa Error: ');
                    printf('Start timestamp found without stop!\n');
                end

                % There was an error
                bRes = csw.FAIL;
                return;
            end
        endfor

        % The last expected marker should be START
        if iExpMarker == csw.STOP
            printf('CoSniWa Error: ');
            printf('Start/stop interleave error for rego #%d ', iRego);
            printf('call: #%d !\n', (nCalls + 1));
            printf('CoSniWa Error: ');
            printf('Start timestamp found without a following stop!\n');

            % There was an error
            bRes = csw.FAIL;
            return;
        end
    endfor

    % Everything is ok
    bRes = csw.OK;
    return;
end


function csw = post_count_calls(csw)
%
%  post_count_calls:
%
%  (POSTPROCESSING)  COUNT THE NUMBER OF CALLS.
%
%  Function counts the number of calls for every code snippet and stores this
%  number in a structure with timing results for every code snippet
%  registration  (Structures 'stResults' stored in cell vector `cstResults`).
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:     [structure]  Cosniwa structure
%
%  Return:
%      csw:     [structure]  Cosniwa structure
%          added:   csw.cstResults{:}.nCalls
%

    % Loop over all the unique code snippet registrations
    for inxRego=1:csw.nURego

        % Get the current checked registration
        iRego = csw.vRego(inxRego);

        % Reset counter of calls
        nCalls = 0;

        % Loop over all time stamps
        for inxTS = 1:csw.iTSCtr

            % Check if the time stamp is about the currently tested rego
            % and if it is a starting time stamp.
            % If it is, calls counter goes up.
            if((csw.vTSRego(inxTS) == iRego) &&
               (csw.vTSMark(inxTS) == csw.START))
                nCalls++;
            end
        endfor

        % Store the found number of calls
        csw.cstResults{inxRego}.nCalls = nCalls;
    endfor
end


function csw = post_allocate_call_times(csw)
%
%  post_allocate_call_times:
%
%  (POSTPROCESSING)  ALLOCATE VECTORS FOR CALL TIMES FOR ALL THE UNIQUE CODE
%                    SNIPPET REGISTRATIONS.
%
%
%  Every structure with timing results for code snippets `csw.cstResults{:}`
%  contains a vector ('vCallT') dedicated for times of calls.
%
%  This function allocates these vectors for all the unique code snippet
%  registrations.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:     [structure]  Cosniwa structure
%
%  Return:
%      csw:    [structure]  Cosniwa structure
%          added:   csw.cstResults{:}.vCallT
%

    % Loop over all the uniqe code snippet registrations
    for inxRego = 1:csw.nURego

        % Get the number of calls
        nCalls = csw.cstResults{inxRego}.nCalls;

        % Allocate vector for all the calls
        csw.cstResults{inxRego}.vCallT = -1 * ones(nCalls, 1);
    endfor
end


function csw = post_measure_call_times(csw)
%
%  post_measure_call_times:
%
%  (POSTPROCESSING)  MEASURE CALL TIMES FOR ALL THE UNIQUE CODE
%                    SNIPPET REGISTRATIONS.
%
%
%  Every structure with timing results for code snippets `csw.cstResults{:}`
%  contains a vector ('vCallT') dedicated for times of calls.
%
%  This function measures the call times and put these times into proper
%  `vCallT` vectors.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:    [structure]  Cosniwa structure
%
%  Return:
%      csw:    [structure]  Cosniwa structure
%          modified:   csw.cstResults{:}.vCallT
%

    % Loop over all the uniqe code snippet registrations
    for inxRego = 1:csw.nURego

        % Get the current checked rego
        iRego = csw.vRego(inxRego);

        % Reset the index of calls
        inxCalls = 1;

        % Loop over all time stamps
        for inxTS = 1:csw.iTSCtr

            % Check if the timestamp is about the currently tested rego
            % and if it is a starting timestamp
            if((csw.vTSRego(inxTS) == iRego) &&
               (csw.vTSMark(inxTS) == csw.START))

                % Get start timestamp
                startstamp = csw.vTS(inxTS);
            end

            % Check if the time stamp is about the currently tested rego
            % and if it is a stoping time stamp
            if((csw.vTSRego(inxTS) == iRego) &&
               (csw.vTSMark(inxTS) == csw.STOP))

                % Get stop timestamp
                stopstamp = csw.vTS(inxTS);

                % Compute time difference [microseconds]
                tCall = post_measure_time_difference(stopstamp, startstamp);

                % Store the time snipper call time
                csw.cstResults{inxRego}.vCallT(inxCalls) = tCall;

                % Increase the index of calls
                inxCalls++;

                % It it was a main stoper time, store is as tTotalTime
                if iRego == csw.MAIN_REGO
                    csw.tTotalTime = tCall;
                end
            end
        endfor
    endfor
end


function tDiff = post_measure_time_difference(stopstamp, startstamp)
%
%  post_measure_time_difference:
%
%  (POSTPROCESSING)  MEASURE THE TIME DIFFERENCE BETWEEN TWO TIMESTAMPS.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      stopstamp:     [float number]  Stop timestamp
%      startstamp:    [float number]  Start timestamp
%
%  Return:
%      tDiff:    [integer nubmer]  Time between start and stop timestamps [us]
%

    tUsInSec = 1000000;   % The number of microseconds in a second

    % Change timestamps to time structures
    stStart = gmtime(startstamp);
    stStop = gmtime(stopstamp);

    % Start with difference in useconds
    tDiffUS_us = stStop.usec - stStart.usec;

    % Difference in seconds
    tDiffS_s = stStop.sec - stStart.sec;
    tDiffS_us = tDiffS_s * tUsInSec;

    % Difference in minutes
    tDiffM_min = stStop.min - stStart.min;
    tDiffM_us = tDiffM_min * 60 * tUsInSec;

    % Difference in hours
    tDiffH_h = stStop.hour - stStart.hour;
    tDiffH_us = tDiffH_h * 3600 * tUsInSec;

    % Difference in days
    tDiffD_d = stStop.yday - stStart.yday;
    tDiffD_us = tDiffH_h * 24 * 3600 * tUsInSec;

    % Add all the dfferences
    tDiff = tDiffUS_us + tDiffS_us + tDiffM_us + tDiffH_us + tDiffD_us;
end


function csw = post_process_call_times(csw)
%
%  post_process_call_times:
%
%  (POSTPROCESSING)  PROCESS  ALL THE CALL TIMES.
%
%  Function process all the call times for all the registered code snippets.
%  The function computes the total time of calls, the average single call time,
%  minimum time of a single call, maximim time of a single call, etc.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:    [structure]  Cosniwa structure
%
%  Return:
%      csw     [structure]  Cosniwa structure
%           added: to structures with processed data from code snippets:
%
%               csw.cstResults{:}.iRego - registration of code snippet
%
%               csw.cstResults{:}.tTotalTime - the total time of all the calls
%                                              from a snippet
%
%               csw.cstResults{:}.tMin - minimum time of a call
%
%               csw.cstResults{:}.tMax - maximum time of a call
%
%               csw.cstResults{:}.nShortCalls - the number of short calls
%                                               (calls lower than 1 us)
%
%               csw.cstResults{:}.tAvg - the average time of a single call
%
%               csw.cstResults{:}.dPart - which part of the main time
%                                         is taken by all the calls from
%                                         the current snippet
%
%               csw.cstResults{:}.iVar - the variance of calls
%
%               csw.cstResults{:}.dMaxSpeedUp - max speed up according
%                                               to Amdahl's law
%

    % Loop over all the uniqe code snippet registrations
    for inxRego = 1:csw.nURego

        % Store the registration of the code snippet
        iRego = csw.vRego(inxRego);
        csw.cstResults{inxRego}.iRego = iRego;

        % Get the vector with time calls for the current code snippet
        % regsitrations
        vCallT = csw.cstResults{inxRego}.vCallT;

        % Compute the total time of all the calls
        tTotalTime = sum(vCallT);
        csw.cstResults{inxRego}.tTotalTime = tTotalTime;

        % Compute the minimum and maximum time of a call
        csw.cstResults{inxRego}.tMin = min(vCallT);
        csw.cstResults{inxRego}.tMax = max(vCallT);

        % Compute the number of short calls (calls lower than 1 us)
        csw.cstResults{inxRego}.nShortCalls = size((vCallT(vCallT < 1)), 1);

        % Compute the average time of a single call
        csw.cstResults{inxRego}.tAvg = mean(vCallT);

        % Compute what part of the main time is the current snippet
        if csw.stTRParam.bMainTimeMeasured
            dPart = tTotalTime / csw.tTotalTime;
        else
            dPart = -1;
        end
        csw.cstResults{inxRego}.dPart = dPart;

        % Compute the variance if the code snippet was called more than once
        if csw.cstResults{inxRego}.nCalls > 1
            iVar = var(vCallT);
        else
            iVar = -1;
        end
        csw.cstResults{inxRego}.iVar = iVar;

        % Compute the max speed up according to Amdahl's law
        if (iRego == csw.MAIN_REGO)
            dMaxSpeedUp = -1;
        else
            dMaxSpeedUp = 1 / (1 - dPart);
        end
        csw.cstResults{inxRego}.dMaxSpeedUp = dMaxSpeedUp;
    endfor
end


function csw = post_sort(csw)
%
%  post_sort:
%
%  (POSTPROCESSING)  SORT THE CODE SNIPPETS STRUCTURES BY THE TOTAL CALL TIME.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:     [structure]  Cosniwa structure
%
%  Return:
%      csw:     [structure]  Cosniwa structure
%          modified:   csw.cstResults{:}
%

    % Generate a vector with all the total call times for every code snippet
    vTotalT = zeros(csw.nURego, 1);
    for inxRego = 1 : csw.nURego
        vTotalT(inxRego) = csw.cstResults{inxRego}.tTotalTime;
    endfor

    % Sort the above vector, and sort the cell vector with structures with
    % timing results for code snippets
    [~, vInx] = sort(vTotalT, 'descend');
    csw.cstResults = csw.cstResults(vInx);
end


function csw = post_find_general_param(csw)
%
%  post_find_general_param:
%
%  (POSTPROCESSING)  FIND THE GENERAL TIMING RESULTS PARAMETERS.
%
%  The function computes the general timing results parameters and store these
%  parameters in 'stTRParam' structure.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw     [structure]  Cosniwa structure
%
%  Return:
%      csw     [structure]  Cosniwa structure
%           added: to structure with general parameters of timing results
%
%               csw.stTRParam.iHighRego - highest code snippet registraion
%
%               csw.stTRParam.tTotalMax - the maximum total time of a code
%                                         snippet
%
%               csw.stTRParam.nCallsMax - the maximum number of calls for
%                                         a code snippet
%
%               csw.stTRParam.tAvgMax - the maximum average time of a
%                                       code snippet
%
%               csw.stTRParam.tVarMax - the maximum variance of
%                                       code snippet calls
%
%               csw.stTRParam.dPartMax - the maximum fraction of the main time
%
%               csw.stTRParam.dMaxSpeedUpMax - the maximum max possible speed up
%                                              corresponding to a single code
%                                              snippet
%
%               csw.stTRParam.tMinMax - the maximum min time of a single call
%
%               csw.stTRParam.tMaxMax - the maximum max time of a single call
%

    % Find size of the longest code snippet label
    csw.stTRParam.iLongestLabelSiz = 0;
    for inxLabel = 1: csw.nCSLabels

        % Get the size of a code snippet label
        iLen = length(csw.cLabels{inxLabel});

        % Update the longest size, if needed
        if iLen > csw.stTRParam.iLongestLabelSiz
            csw.stTRParam.iLongestLabelSiz = iLen;
        end
    endfor

    % Create an empty label
    strEmptyLabel = '';
    for inxChr = 0: csw.stTRParam.iLongestLabelSiz
        strEmptyLabel = cstrcat(strEmptyLabel,' ');
    endfor
    csw.stTRParam.strEmptyLabel = strEmptyLabel;

    % Reset...:
    csw.stTRParam.iHighRego = 0;       % highest code snippet registraion number
    csw.stTRParam.tTotalMax = 0;       % the maximum total time of a snippet
    csw.stTRParam.nCallsMax = 0;       % the number of calls
    csw.stTRParam.tAvgMax = 0;         % the maximum average time
    csw.stTRParam.tVarMax = 0;         % the maximum variance
    csw.stTRParam.dPartMax = 0;        % the maximum fraction of the main time
    csw.stTRParam.dMaxSpeedUpMax = 0;  % the maximum max possible speed up
    csw.stTRParam.tMinMax = 0;         % the maximum min time of a single call
    csw.stTRParam.tMaxMax = 0;         % the maximim max time of a single call

    % Find the maximum values in the Timing Results structures:
    for inxRego = 1: csw.nURego

        % Code snippet with registration 0 means all the measured code
        % - not interesting
        if (csw.cstResults{inxRego}.iRego == 0)
            continue;
        end

        % Update the highest code snippet registraion number
        if csw.stTRParam.iHighRego < csw.cstResults{inxRego}.iRego
            csw.stTRParam.iHighRego = csw.cstResults{inxRego}.iRego;
        end

        % Update the maximum total time of a code snippet
        if csw.stTRParam.tTotalMax < csw.cstResults{inxRego}.tTotalTime
            csw.stTRParam.tTotalMax = csw.cstResults{inxRego}.tTotalTime;
        end

        % Update the maximum number of calls for a code snippet
        if csw.stTRParam.nCallsMax < csw.cstResults{inxRego}.nCalls
            csw.stTRParam.nCallsMax = csw.cstResults{inxRego}.nCalls;
        end

        % Update the maximum average time
        if csw.stTRParam.tAvgMax < csw.cstResults{inxRego}.tAvg
            if csw.cstResults{inxRego}.nCalls > 1
                csw.stTRParam.tAvgMax = csw.cstResults{inxRego}.tAvg;
            end
        end

        % Update the maximum variance
        if csw.stTRParam.tVarMax < csw.cstResults{inxRego}.iVar
            if csw.cstResults{inxRego}.nCalls > 1
                csw.stTRParam.tVarMax = csw.cstResults{inxRego}.iVar;
            end
        end

        % Update the maximum fraction of the main time
        if csw.stTRParam.dPartMax < csw.cstResults{inxRego}.dPart
            csw.stTRParam.dPartMax = csw.cstResults{inxRego}.dPart;
        end

        % Update the maximum max possible speed up
        if csw.stTRParam.dMaxSpeedUpMax < csw.cstResults{inxRego}.dMaxSpeedUp
            csw.stTRParam.dMaxSpeedUpMax = csw.cstResults{inxRego}.dMaxSpeedUp;
        end

        % Update the maximum min time of a single call
        if csw.stTRParam.tMinMax < csw.cstResults{inxRego}.tMin
            if csw.cstResults{inxRego}.nCalls > 1
                csw.stTRParam.tMinMax = csw.cstResults{inxRego}.tMin;
            end
        end

        % Update the maximim max time of a single call
        if csw.stTRParam.tMaxMax < csw.cstResults{inxRego}.tMax
            if csw.cstResults{inxRego}.nCalls > 1
                csw.stTRParam.tMaxMax = csw.cstResults{inxRego}.tMax;
            end
        end
    endfor
end


function strRes = post_print_timing(csw, bShort)
%
%  post_print_timing:
%
%  (POSTPROCESSING RESULTS PRINTING) THE MAIN RESULTS PRINTING FUNCTION.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:     [structure]  Cosniwa structure
%      bShort:  [bool]       Short results flag
%
%  Return:
%      strRes:  [string]  String with all the processed results.
%

    % Reset the string
    strRes = '';

    % Print header
    strHead = post_print_header();
    strRes = cstrcat(strRes, strHead);

    % Print the main time
    strMainTime = post_print_main_time(csw);
    strRes = cstrcat(strRes, strMainTime);

    % Print measured code snippet timing
    strTimings = post_print_snippets_times(csw, bShort);
    strRes = cstrcat(strRes, strTimings);

    % Print footer
    strFoot = post_print_footer();
    strRes = cstrcat(strRes, strFoot);
end


function strHead = post_print_header()
%
%  post_print_header:
%
%  (POSTPROCESSING RESULTS PRINTING) PRINT HEADER.
%
%  -----------------------------------------------------------------------------
%
%  Return:
%      strHead:  [string]  String with header
%

    strHead = '';
    strHead = cstrcat(strHead, '>>> ===================');
    strHead = cstrcat(strHead, ' CoSniWa [Octave port] ');
    strHead = cstrcat(strHead, '=================== >>>\n');
end


function strMainTime = post_print_main_time(csw)
%
%  post_print_main_time:
%
%  (POSTPROCESSING RESULTS PRINTING) PRINT THE MAIN TIME OF THE STOPWATCH.
%
%  Function prints the main time of the stopwatch, if it was measured.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:     [structure]  Cosniwa structure
%
%  Return:
%      strMainTime:  [string]  String with the main time of the stopwatch
%

    % If there are no code snippets in the database, do not print anything
    if csw.iTSCtr == 0
        strMainTime = '';
        return;
    end

    % If the main time was not measured, do not print anything
    if csw.stTRParam.bMainTimeMeasured == csw.MAIN_TIME_OFF
        strMainTime = '';
        return;
    end

    % convert the total time to ms
    iMainTime_ms = csw.cstResults{1}.tTotalTime / 1000;

    % Print out timing for the main stoper time
    strMainTime = sprintf('Total measured time: %.3f [ms]\n', iMainTime_ms);
end


function strTimings = post_print_snippets_times(csw, bShort)
%
%  post_print_snippets_times:
%
%  (POSTPROCESSING RESULTS PRINTING) PRINT THE TIMING RESULTS FOR CODE SNIPPETS.
%
%  Function prints timing results for all the ordinary (not-main) code snippets.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:     [structure]  Cosniwa structure
%      bShort:  [bool]       Short results flag
%
%  Return:
%      strTimings:  [string]  String with the timing results for code snippets
%

    % Reset the string with timings
    strTimings = '';

    % Print code snippets only if there are code snippets
    if (csw.nURego == 0)
        return;
    elseif ((csw.nURego == 1) &&
           (csw.stTRParam.bMainTimeMeasured == csw.MAIN_TIME_ON))
        return;
    end

    % Print code snippet header
    if csw.stTRParam.bMainTimeMeasured == csw.MAIN_TIME_ON
        strTimings = cstrcat(strTimings, '\n');
    end
    strTimings = cstrcat(strTimings, 'Code snippets: \n');

    % If the main time was measured, start with code snippet indexed as 2.
    % Index 1 is the main time
    if (csw.stTRParam.bMainTimeMeasured == csw.MAIN_TIME_ON)
        inxRegoStart = 2;
    else
        inxRegoStart = 1;
    end

    % Reset order number of the code snippet
    inxCS = 1;

    for inxRego = inxRegoStart:csw.nURego

        % Print the data for a single snippet
        strTiming = post_print_single_snippet_data(csw, inxCS, inxRego, bShort);
        strTimings = cstrcat(strTimings, strTiming);

        % Increase index of the code snippet
        inxCS += 1;
    endfor
end


function strSnippet = post_print_single_snippet_data(csw, inxCS, inxRego,
                                                     bShort)
%
%  post_print_single_snippet_data:
%
%  (POSTPROCESSING RESULTS PRINTING)  PRINT THE TIMING RESULTS FOR SINGLE CODE
%                                     SNIPPET.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:      [structure]       Cosniwa structure
%      inxCS:    [integer number]  Index of printed code snippet
%      inxRego:  [integer number]  Index of a structure in `csw.cstResults{}`
%                                  corresponding to the current code snippet
%      bShort:   [bool]            Short results flag
%
%  Return:
%      strSnippet:  [string]  String with the timing results for single code
%                             snippet
%

    strSnippet='';  % Start out string

    % Print the index of the current code snippet
    strInx = post_print_single_snippet_data_inx(csw, inxCS);
    strSnippet = cstrcat(strSnippet, strInx);

    % Get the structure for the code snippet the function is talking about
    stTR = csw.cstResults{inxRego};

    % Print rego
    strRego = post_print_single_snippet_data_rego(csw, stTR);
    strSnippet = cstrcat(strSnippet, strRego);

    % Print label
    strLabel = post_print_single_snippet_data_label(csw, stTR);
    strSnippet = cstrcat(strSnippet, strLabel);

    % Print the number of calls
    strNCalls = post_print_single_snippet_data_calls(csw, stTR);
    strSnippet = cstrcat(strSnippet, strNCalls);

    % Print the total time spend in the code snippet
    strTTot = post_print_single_snippet_data_totaltime(csw, stTR);
    strSnippet = cstrcat(strSnippet, strTTot);

    % Print fraction of the main time, if the main time was measured
    strFrac = post_print_single_snippet_data_fraction(csw, stTR);
    strSnippet = cstrcat(strSnippet, strFrac);

    % Print the maximum speed up
    strSpeedUp = post_print_single_snippet_data_max_s_up(csw, stTR);
    strSnippet = cstrcat(strSnippet, strSpeedUp);

    % If the detailed (non short) data was requested, add the average time,
    % the variance the minimum time and the maximum time
    if (bShort == 0)

        % Print the average time
        strAvgT = post_print_single_snippet_data_avg_time(csw, stTR);
        strSnippet = cstrcat(strSnippet, strAvgT);

        % Print the variance
        strVar = post_print_single_snippet_data_var(csw, stTR);
        strSnippet = cstrcat(strSnippet, strVar);

        % Print the minimum time
        strMinT = post_print_single_snippet_data_min_time(csw, stTR);
        strSnippet = cstrcat(strSnippet, strMinT);

        % Print the maximum time
        strMaxT = post_print_single_snippet_data_max_time(csw, stTR);
        strSnippet = cstrcat(strSnippet, strMaxT);

    end

    % Line is finished here
    strSnippet = cstrcat(strSnippet, '\n');

    % Report too short calls
    strTwoShort = post_print_single_sni_data_short_call(csw, stTR);
    strSnippet = cstrcat(strSnippet, strTwoShort);
end


function strInx = post_print_single_snippet_data_inx(csw, inxCS)
%
%  post_print_single_snippet_data_inx:
%
%  (POSTPROCESSING RESULTS PRINTING)  PRINT THE INDEX OF A CODE SNIPPET.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:      [structure]       Cosniwa structure
%      inxCS:    [integer number]  Index of printed code snippet
%
%  Return:
%      strInx:  [string]  String with formatted index of the code snippet
%

    strPrefix = '';     % Prefix
    strSuffix = '.  ';  % Suffix
    strInvo = '#';      % Number invocation

    strInx = post_print_record_int(csw.nURego, inxCS,
                                   strPrefix, strInvo, strSuffix);
end


function strRego = post_print_single_snippet_data_rego(csw, stTR)
%
%  post_print_single_snippet_data_rego:
%
%  (POSTPROCESSING RESULTS PRINTING)  PRINT REGISTRATION NUMBER OF
%                                     A CODE SNIPPET.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:   [structure]   Cosniwa structure
%      stTR:  [structure]   Structure with processed timing results for
%                           a code snippet
%
%  Return:
%      strRego:  [string]   String with formatted registration number
%                           of a code snippet
%

    strPrefix = 'rego: ';  % Prefix
    strSuffix = '  ';      % Suffix
    strInvo = '';          % Number invocation

    strRego = post_print_record_int(csw.stTRParam.iHighRego, stTR.iRego,
                                    strPrefix, strInvo, strSuffix);

end


function strLabel = post_print_single_snippet_data_label(csw, stTR)
%
%  post_print_single_snippet_data_label:
%
%  (POSTPROCESSING RESULTS PRINTING)  PRINT REGISTRATION LABEL OF
%                                     A CODE SNIPPET (IF AVAILABLE).
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:   [structure]   Cosniwa structure
%      stTR:  [structure]   Structure with processed timing results for
%                           a code snippet
%
%  Return:
%      strLabel:  [string]  String with formatted label of the code snippet
%

    strPrefix = '\"';
    strSuffix = '\"  ';

    % Get index of a label
    iInxLabel = post_rego_to_label(csw, stTR.iRego);

    % Get the label, if it exists for a given code snippet
    if iInxLabel == csw.NOT_FOUND

        % Generate an empty label
        strLabel = '';
    else

        % Get the label
        strLabel = csw.cLabels{iInxLabel};
    end

    % The number of missing characters to the longest label from
    % all the code snippets
    iMissingChr = csw.stTRParam.iLongestLabelSiz - length(strLabel);

    % Create space padding
    strSpacePadding = post_print_space_padding(iMissingChr);

    % Create the label record
    strLabel = sprintf('%s%s%s%s',
                       strPrefix, strLabel, strSuffix, strSpacePadding);

end


function strNCalls = post_print_single_snippet_data_calls(csw, stTR);
%
%  post_print_single_snippet_data_calls:
%
%  (POSTPROCESSING RESULTS PRINTING)  PRINT THE NUMBER OF CALLS FOR
%                                     A CODE SNIPPET.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:   [structure]   Cosniwa structure
%      stTR:  [structure]   Structure with processed timing results for
%                           a code snippet
%
%  Return:
%      strNCalls:  [string]  String with formatted number of calls
%

    strPrefix = '[calls:  ';  % Prefix
    strSuffix = ']  ';        % Suffix
    strInvo = '';             % Number invocation

    % Print the record
    strNCalls = post_print_record_int(csw.stTRParam.nCallsMax, stTR.nCalls,
                                      strPrefix, strInvo, strSuffix);
end


function strTotal = post_print_single_snippet_data_totaltime(csw, stTR);
%
%  post_print_single_snippet_data_totaltime:
%
%  (POSTPROCESSING RESULTS PRINTING)  PRINT THE TOTAL TIME CALL FOR
%                                     A CODE SNIPPET.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:   [structure]   Cosniwa structure
%      stTR:  [structure]   Structure with processed timing results for
%                           a code snippet
%
%  Return:
%      strTotal:  [string]  String with formatted total call time ofor the
%                           code snippet
%

    iMaxTotalTime_ms = csw.stTRParam.tTotalMax / 1000;
    tTotalTime_ms = stTR.tTotalTime / 1000;

    strPrefix = '';         % Prefix
    strSuffix = ' [ms]  ';  % Suffix
    strDefault = '<0.001';  % Default value
    iDAC = 3;         % The number of digits after comma

    % If the average time is lower then 0.001 ms, print a default value
    bPrintDefault = 0;
    if tTotalTime_ms < 0.001
        bPrintDefault = 1;
    end

    % Print the record
    strTotal = post_print_record_float(iMaxTotalTime_ms, tTotalTime_ms,
                                       strPrefix, strSuffix, strDefault,
                                       iDAC, bPrintDefault);
end


function strFrac = post_print_single_snippet_data_fraction(csw, stTR)
%
%  post_print_single_snippet_data_fraction:
%
%  (POSTPROCESSING RESULTS PRINTING)  PRINT FRACTION OF THE MAIN STOPWATCH TIME
%                                     TAKEN BY A CODE SNIPPET.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:   [structure]   Cosniwa structure
%      stTR:  [structure]   Structure with processed timing results for
%                           a code snippet
%
%  Return:
%      strFrac:  [string]  String with formatted fraction of the main
%                          stopwatch time
%

    strFrac = '';
    if csw.stTRParam.bMainTimeMeasured == csw.MAIN_TIME_ON

        strPrefix = '';          % Prefix
        strSuffix = ' pct.  ';   % Suffix
        strDefault = '<0.01';    % Default value
        iDAC = 2;        % The number of digits after comma

        % If the fraction is lower then 0.01%, print a default value
        bPrintDefault = 0;
        if ((stTR.dPart * 100) < 0.01)
            bPrintDefault = 1;
        end
        bPrintDefault = 0;

        % Print the record
        strFrac = post_print_record_float(100.0, stTR.dPart * 100,
                                          strPrefix, strSuffix, strDefault,
                                          iDAC, bPrintDefault);
    end
end


function strSpeedUp = post_print_single_snippet_data_max_s_up(csw, stTR)
%
%  post_print_single_snippet_data_max_s_up:
%
%  (POSTPROCESSING RESULTS PRINTING)  PRINT MAXIMUM POSSIBLE SPEED UP
%                                     CORRESPONDING TO A CODE SNIPPET
%                                     (ACCORDING TO AMDAHL'S LAW).
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:   [structure]   Cosniwa structure
%      stTR:  [structure]   Structure with processed timing results for
%                           a code snippet
%
%  Return:
%      strSpeedUp:  [string]  String with formatted maximum possible speed up
%                             correspodning to a code snippet
%

    strSpeedUp = '';
    if csw.stTRParam.bMainTimeMeasured == csw.MAIN_TIME_ON

        strPrefix = 'MPA: ';   % Prefix
        strSuffix = '  ';      % Suffix
        strDefault = '<1.01';  % Default value
        iDAC = 2;        % The number of digits after comma

        % If the speed up is lower then 1.01, print a default value
        bPrintDefault = 0;
        if (stTR.dMaxSpeedUp < 1.01)
            bPrintDefault = 1;
        end

        % Print the record
        strSpeedUp = post_print_record_float(csw.stTRParam.dMaxSpeedUpMax,
                                             stTR.dMaxSpeedUp,
                                             strPrefix, strSuffix, strDefault,
                                             iDAC, bPrintDefault);
    end
end


function strAvgT = post_print_single_snippet_data_avg_time(csw, stTR)
%
%  post_print_single_snippet_data_avg_time:
%
%  (POSTPROCESSING RESULTS PRINTING)  PRINT AVERAGE CALL TIME FOR
%                                     A CODE SNIPPET.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:   [structure]   Cosniwa structure
%      stTR:  [structure]   Structure with processed timing results for
%                           a code snippet
%
%  Return:
%      strAvgT:  [string]  String with formatted average call time for a code
%                          snippet
%

    strAvgT = '';
    if stTR.nCalls > 1

        iMaxAvgTime_ms = csw.stTRParam.tAvgMax / 1000;
        iAvgTime_ms = stTR.tAvg / 1000;

        strPrefix = 'avg: ';     % Prefix
        strSuffix = ' [ms]  ';   % Suffix
        strDefault = '<0.001';   % Default value
        iDAC = 3;        % The number of digits after comma

        % If the average time is lower then 0.001 ms, print a default value
        bPrintDefault = 0;
        if (iAvgTime_ms < 0.001)
            bPrintDefault = 1;
        end

        % Print the record
        strAvgT = post_print_record_float(iMaxAvgTime_ms, iAvgTime_ms,
                                          strPrefix, strSuffix, strDefault,
                                          iDAC, bPrintDefault);
    end
end


function strVar = post_print_single_snippet_data_var(csw, stTR)
%
%  post_print_single_snippet_data_var:
%
%  (POSTPROCESSING RESULTS PRINTING)  PRINT VARIANCE OF CALLING TIMES
%                                     FOR A CALL SNIPPET.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:   [structure]   Cosniwa structure
%      stTR:  [structure]   Structure with processed timing results for
%                           a code snippet
%
%  Return:
%      strVar:  [string]   String with formatted variance of calling times
%                          for a code snippet
%

    strVar = '';
    if stTR.nCalls > 1

        iMaxVar_ms = csw.stTRParam.tVarMax / 1000;
        iVar_ms = stTR.iVar / 1000;

        strPrefix = 'var: ';     % Prefix
        strSuffix = ' [ms]  ';   % Suffix
        strDefault = '<0.001';   % Default value
        iDAC = 3;        % The number of digits after comma

        % If the average time is lower then 0.001 ms, print a default value
        bPrintDefault = 0;
        if (iVar_ms < 0.001)
            bPrintDefault = 1;
        end

        % Print the record
        strVar = post_print_record_float(iMaxVar_ms, iVar_ms,
                                         strPrefix, strSuffix, strDefault,
                                         iDAC, bPrintDefault);
    end
end


function strMinT = post_print_single_snippet_data_min_time(csw, stTR)
%
%  post_print_single_snippet_data_min_time:
%
%  (POSTPROCESSING RESULTS PRINTING)  PRINT MINIMUM CALL TIME FOR
%                                     A CODE SNIPPET.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:   [structure]   Cosniwa structure
%      stTR:  [structure]   Structure with processed timing results for
%                           a code snippet
%
%  Return:
%      strMinT:  [string]  String with formatted minimum (shortest) call
%                          time for a code snippet
%

    strMinT = '';
    if stTR.nCalls > 1

        iMaxTMin_ms = csw.stTRParam.tMinMax / 1000;
        iTMin_ms = stTR.tMin / 1000;

        strPrefix = 'min/max call: ';  % Prefix
        strSuffix = '/';               % Suffix
        strDefault = '<0.001';         % Default value
        iDAC = 3;        % The number of digits after comma

        % If the minimum time is lower than 0.001 ms, print default value
        bPrintDefault = 0;
        if (iTMin_ms < 0.001)
            bPrintDefault = 1;
        end

        % Print the record
        strMinT = post_print_record_float(iMaxTMin_ms, iTMin_ms,
                                          strPrefix, strSuffix, strDefault,
                                          iDAC, bPrintDefault);
    end
end


function strMaxT = post_print_single_snippet_data_max_time(csw, stTR)
%
%  post_print_single_snippet_data_max_time:
%
%  (POSTPROCESSING RESULTS PRINTING)  PRINT MAXIMUM CALL TIME FOR
%                                     A CODE SNIPPET.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:   [structure]   Cosniwa structure
%      stTR:  [structure]   Structure with processed timing results for
%                           a code snippet
%
%  Return:
%      strMaxT:  [string]  String with formatted maximum (longest) call time
%                          for a code snippet
%

    strMaxT = '';
    if stTR.nCalls > 1

        iMaxTMax_ms = csw.stTRParam.tMaxMax / 1000;
        iTMax_ms = stTR.tMax / 1000;

        strPrefix = '';         % Prefix
        strSuffix = ' [ms]';    % Suffix
        strDefault = '<0.001';  % Default value
        iDAC = 3;        % The number of digits after comma

        % If the maximum time is lower than 0.001 ms, print default value
        bPrintDefault = 0;
        if (iTMax_ms < 0.001)
            bPrintDefault = 1;
        end

        % Print the record
        strMaxT = post_print_record_float(iMaxTMax_ms, iTMax_ms,
                                          strPrefix, strSuffix, strDefault,
                                          iDAC, bPrintDefault);
    end
end


function strTwoShort = post_print_single_sni_data_short_call(csw, stTR)
%
%  post_print_single_sni_data_short_call:
%
%  (POSTPROCESSING RESULTS PRINTING)  PRINT WARNING THAT THERE WAS A CALL WHICH
%                                     WAS TOO SHORT TO MEASURE.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:   [structure]   Cosniwa structure
%      stTR:  [structure]   Structure with processed timing results for
%                           a code snippet
%
%  Return:
%      strTwoShort:  [string]  String with a warning about too short call
%

    strTwoShort = '';
    nShortCalls = stTR.nShortCalls;
    if nShortCalls > 0
        strTwoShort = cstrcat(strTwoShort, '      WARNING!     ');
        if nShortCalls == 1
            strCalls = sprintf('There was %d call ', nShortCalls);
        else
            strCalls = sprintf('There were %d calls ', nShortCalls);
        end
        strTwoShort = cstrcat(strTwoShort, strCalls);
        strTwoShort = cstrcat(strTwoShort, 'too short to measure (< 1us)');
    end
end


function strFoot = post_print_footer()
%
%  post_print_footer:
%
%  (POSTPROCESSING RESULTS PRINTING) PRINT FOOTER.
%
%  -----------------------------------------------------------------------------
%
%  Return:
%      strFoot:  [string]  String with footer
%

    strFoot = '';
    strFoot = cstrcat(strFoot, '<<< ===================');
    strFoot = cstrcat(strFoot, ' CoSniWa [Octave port] ');
    strFoot = cstrcat(strFoot, '=================== <<<\n');
end


function iInxLabel = post_rego_to_label(csw, iRego)
%
%  post_rego_to_label:
%
%  (POSTPROCESSING RESULTS PRINTING)  FIND A LABEL CORRESPONDING TO
%                                     A REGISTRAION.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      csw:    [structure]       Cosniwa structure
%      iRego:  [integer number]  Code registration to be matched with a label
%
%
%  Return:
%      iInxLabel:  [integer number]  Index of a label which corresponds to
%                                    a given rego.
%                                    If rego was not found in the database,
%                                    return csw.NOT_FOUND
%

    % Check if the rego exists
    vRegoFound = (csw.vLabelsReg == iRego);
    if sum(vRegoFound) == 0

        % Rego was not found
        iInxLabel = csw.NOT_FOUND;
        return;

    else
        % Rego exists, find index of the corresponding label
        vInx = 1:length(csw.vLabelsReg);
        iInxLabel = vInx(vRegoFound);
        return;
    end
end


function strRecord = post_print_record_int(iMaxNum, iValue,
                                            strPrefix, strInvo, strSuffix)
%
%  post_print_record_int:
%
%  (POSTPROCESSING RESULTS PRINTING)  FORMAT AN INTEGER RECORD ENTRY.
%
%  Add an integer record entry (v1).
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      iMaxNum:    [integer number]   Maximum possible number
%      iValue:     [integer number]   VALUE of the number to be printed
%      strPrefix:  [string]           Prefix before the record
%      strInvo:    [string]           Invocation before a number (e.g. #)
%      strSuffix:  [string]           Suffix after the record
%
%  Return:
%      strRecord:  [string]  Formated record
%

    % Compute the max number of characters in the max number
    iMaxNumRounded = floor(iMaxNum);
    strMaxNum = sprintf('%d', iMaxNumRounded);
    iMaxCharInNum = length(strMaxNum);

    % Compute the max number of characters in the invocation
    iMaxCharInInv = length(strInvo);

    % Compute the max number of characters in the augmented number
    % [invocation + minus + number ]
    iMaxCharAugNum = iMaxCharInInv + iMaxCharInNum;

    % Create space padding
    strAugNum = sprintf('%s%d', strInvo, iValue);
    iCharInAugNum = length(strAugNum);
    iNumCharMissing = iMaxCharAugNum - iCharInAugNum;
    strSpacePadding = post_print_space_padding(iNumCharMissing);

    % Add space padding to the number
    strNum = sprintf('%s%s%d', strSpacePadding, strInvo, iValue);

    % Create the final record
    strRecord = sprintf('%s%s%s', strPrefix, strNum, strSuffix);

end


function strRecord = post_print_record_float(iMaxNum, iValue,
                                             strPrefix, strSuffix, strEmpty,
                                             iDAC, bEmpty)
%
%  post_print_record_float:
%
%  (POSTPROCESSING RESULTS PRINTING)  FORMAT A FLOAT RECORD ENTRY.
%
%  Add an integer record entry (v1).
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      iMaxNum:    [integer number]   Maximum possible number
%      iValue:     [integer number]   VALUE of the number to be printed
%      strPrefix:  [string]           Prefix before the record
%      strSuffix:  [string]           Suffix after the record
%      strEmpty:   [string]           String used if bEmpty = 1
%      iDAC:       [integer number]   The number of Digits After Comma
%      bEmpty:     [bool]             Flag: Keep the whole record empty
%
%  Return:
%      strRecord:  [string]   Formated record
%

    % Compute the max number of characters in the max number
    iMaxNumRounded = floor(iMaxNum);
    strMaxNum = sprintf('%d', iMaxNumRounded);
    iMaxCharInNum = length(strMaxNum);

    % Compensate for comma and digits after the comma
    iMaxCharInNum = iMaxCharInNum + iDAC + 1;

    % Compute the maximum number of characters in empty
    iMaxCharInEmp = length(strEmpty);

    %  Correct the maximum number of characters in the number:
    %  it can not be lower then the number of characters in empty
    if iMaxCharInEmp > iMaxCharInNum
        iMaxCharInNum = iMaxCharInEmp;
    end

    % Print the record
    if bEmpty == 0

        % *** Print the record ***

        % Print the number:
        strFormatString = sprintf('%%.%df', iDAC);
        strNum = sprintf(strFormatString, iValue);
        iCharInNum = length(strNum);

        % Create space padding
        iNumCharMissing = iMaxCharInNum - iCharInNum;
        strSpacePadding = post_print_space_padding(iNumCharMissing);

        % Add space padding to the augmented number
        strFormatString = sprintf('%%s%%.%df', iDAC);
        printf(strFormatString);
        strNum = sprintf(strFormatString, strSpacePadding, iValue);

        % Create the final record
        strRecord = sprintf('%s%s%s', strPrefix, strNum, strSuffix);

    else
        % *** Leave the record empty ***

        % Compute the number of missing characters in empty string
        iEmptyCharMissing = iMaxCharInNum - iMaxCharInEmp;

        % Create space padding
        strSpacePadding = post_print_space_padding(iEmptyCharMissing);

        % Create the final record
        strRecord = sprintf('%s%s%s%s',strPrefix, strEmpty,
                            strSpacePadding, strSuffix);

    end
end


function strSpacePadding = post_print_space_padding(iNumCharMissing)
%
%  post_print_space_padding:
%
%  (POSTPROCESSING RESULTS PRINTING)  CREATE AN STRINT WITH SPACES.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%      iNumCharMissing:  [integer number]  The number of spaces in a string
%
%  Return:
%      strSpacePadding:  [string]   String with spaces

    strSpacePadding = '';
    if (iNumCharMissing < 0)
        iNumCharMissing = 0;
    end
    for inxChr = 1:iNumCharMissing
        strSpacePadding = cstrcat(strSpacePadding, ' ');
    endfor
end
