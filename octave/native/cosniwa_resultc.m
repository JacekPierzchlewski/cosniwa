%
% cosniwa_resultc.m [version 1.0]
% CoSniWa:  COde SNIppet stopWAtch [Octave port] - Module which prints
%                                                  the processed results.
%
% CoSniWa is dedicated to profile code using time stamps.
% Cosniwa  [Octave port - native .m implementation ] v1.0, 30 May 2017.
%
% read more on: www.speedupcode.com
%
% (c) Jacek Pierzchlewski, 2017  jacek@pierzchlewski.com
% license: BSD-2-Clause.
%


function cosniwa_resultc(csw, bShort=0)
%
%  cosniwa_resultc:
%
%  (POSTPROCESSING)  PRINT PROCESSED RESULTS TO COSNIWA CONSOLE
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
%    nothing
%

    strRes = cosniwa_result(csw, bShort);
    printf(strRes);
end
