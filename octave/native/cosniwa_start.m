%
% cosniwa_start.m [version 1.0]
% CoSniWa:  COde SNIppet stopWAtch [Octave port] - Module which starts
%                                                  the main stopwatch.
%
% CoSniWa is dedicated to profile code using time stamps.
% Cosniwa  [Octave port - native .m implementation ] v1.0, 30 May 2017.
%
% read more on: www.speedupcode.com
%
% (c) Jacek Pierzchlewski, 2017  jacek@pierzchlewski.com
% license: BSD-2-Clause.
%


function csw = cosniwa_start(csw)
%
%  cosniwa_start:
%
%  START THE MAIN TIME OF A STOPWATCH.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%    csw:     [structure]  Cosniwa structure
%
%  Return:
%    csw:     [structure]  Cosniwa structure
%        updated:   csw.iTSCtr
%                   csw.vTSRego
%                   csw.vTSMark
%                   csw.vTS
%
    csw.iTSCtr++;
    csw.vTSRego(csw.iTSCtr) = csw.MAIN_REGO;
    csw.vTSMark(csw.iTSCtr) = csw.START;
    csw.vTS(csw.iTSCtr) = time();
end
