%
% example3.m [version 1.0]
% CoSniWa:  COde SNIppet stopWAtch [Octave port] - Example 3.
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


function example3()

    % Initalise cosniwa
    csw = cosniwa_init();

    % Register the code snippets
    [csw, iRego1] = cosniwa_reg_code(csw, 'add');
    [csw, iRego2] = cosniwa_reg_code(csw, '100 x add');

    csw = cosniwa_call_start(csw, iRego2);  % Start code snippet (loop)
    for inxAdd=1:100
        csw = cosniwa_call_start(csw, iRego1);  % Start code snippet (add)
        add(1, 10000);
        csw = cosniwa_call_stop(csw, iRego1);   % Stop code snippet (add)
    endfor
    csw = cosniwa_call_stop(csw, iRego2);   % Stop code snippet (loop)

    % Print the results
    cosniwa_resultc(csw);
end


function add(iA, iB)
% Add iA + iB in a slow way.

    for i = 1:iB
        iA = iA + 1;
    endfor
end
