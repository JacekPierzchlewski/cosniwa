%
% example1.m [version 1.0]
% CoSniWa:  COde SNIppet stopWAtch [Octave port] - Example 1.
%
%
% CoSniWa is dedicated to profile code using time stamps.
% Cosniwa  [Octave port - native .m implementation ] v1.0, 30 May 2017.
%
% read more on: www.speedupcode.com
%
% (c) Jacek Pierzchlewski, 2017  jacek@pierzchlewski.com
% license: BSD-2-Clause.
%

function example1()

    % Initalise cosniwa
    csw = cosniwa_init();

    csw = cosniwa_call_start(csw, 1);  % Start code snippet
    add(1, 1000000);
    csw = cosniwa_call_stop(csw, 1);   % Stop code snippet

    % Print the results
    cosniwa_resultc(csw);
end


function add(iA, iB)
% Add iA + iB in a slow way.

    for i = 1:iB
        iA = iA + 1;
    endfor
end

