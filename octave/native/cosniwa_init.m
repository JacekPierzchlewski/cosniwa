%
% cosniwa_init.m [version 1.0]
% CoSniWa:  COde SNIppet stopWAtch [Octave port] - CoSniWa initialisation
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


function csw = cosniwa_init(nTotalCallsMax = 10000)
%
%  cosniwa_init:
%
%  INITIALISE COSNIWA STRUCTURE.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%    nTotalCallsMax:  [integer number]  The maximum number of calls
%                                       Default: 10000
%
%  Return:
%    csw:     [structure]  Initialised Cosniwa structure
%

    % Start a structure
    csw = struct();

    % BOOL aliases
    csw.MAIN_REGO = 0;

    csw.STOPPED = 0;
    csw.STARTED = 1;

    csw.START = 0;
    csw.STOP = 1;

    csw.OK = 1;
    csw.FAIL = 0;

    csw.FOUND = 0;
    csw.NOT_FOUND = -1;

    csw.MAIN_TIME_ON = 1;
    csw.MAIN_TIME_OFF = 0;

    % Structure with timing results for every code snippet registration
    % (one p. registered code snippet)
    csw.TR = struct();

    % The maximum total number of calls
    csw.nTotalCallsMax = nTotalCallsMax;

    % Reset time stamp counter
    csw.iTSCtr = 0;

    % Allocate space for time stamps, registrations and start/stop markers
    csw.vTS = -1 * ones(nTotalCallsMax, 1);      % Time stamp markers
    csw.vTSRego = -1 * ones(nTotalCallsMax, 1);  % Code snippets
                                                 % registrations
    csw.vTSMark = -1 * ones(nTotalCallsMax, 1);  % Markers

    % Allocate code snippet labels database
    csw.nRegoMax = 10;  % The maximum number of code snippet registrations
    csw.cLabels = cell(csw.nRegoMax, 1);          % Labels
    csw.vLabelsReg = -1 * ones(csw.nRegoMax, 1);  % Labels registrations
    csw.nCSLabels = 0;                            % The number of registered
                                                  % labels
end


