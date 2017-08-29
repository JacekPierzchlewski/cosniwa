%
% cosniwa_call_stop.m [version 1.0]
% CoSniWa:  COde SNIppet stopWAtch [Octave port] - Module which stops
%                                                  a code snippet call.
%
% CoSniWa is dedicated to profile code using time stamps.
% Cosniwa  [Octave port - native .m implementation ] v1.0, 30 May 2017.
%
% read more on: www.speedupcode.com
%
% (c) Jacek Pierzchlewski, 2017  jacek@pierzchlewski.com
% license: BSD-2-Clause.
%


function csw = cosniwa_call_stop(csw, iRego)
%
%  cosniwa_call_stop:
%
%  STOP A CODE SNIPPET CALL.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%    csw:     [structure]       Cosniwa structure
%    iRego:   [integer number]  Registration number of a code snippet
%
%  Return:
%    csw:     [structure]  Cosniwa structure
%        updated:   csw.iTSCtr
%                   csw.vTSRego
%                   csw.vTSMark
%                   csw.vTS
%
    stopstamp = time();
    csw.iTSCtr++;
    csw.vTS(csw.iTSCtr) = stopstamp;
    csw.vTSRego(csw.iTSCtr) = iRego;
    csw.vTSMark(csw.iTSCtr) = csw.STOP;
end
