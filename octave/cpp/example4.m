%
% example4.m [version 1.0]
% CoSniWa:  COde SNIppet stopWAtch [Octave port] - Example 4.
%
%
% CoSniWa is dedicated to profile code using time stamps.
% Cosniwa  [Octave port - C++ implementation ] v1.0, 31 May 2017.
%
% read more on: www.speedupcode.com
%
% (c) Jacek Pierzchlewski, 2017  jacek@pierzchlewski.com
% license: BSD-2-Clause.
%

function example4()

    % Initalise cosniwa
    cCosniwa('init');

    % Register the code snippets
    iRego1 = cCosniwa('reg_code', 'add(1, 100000)');
    iRego2 = cCosniwa('reg_code', '100 x add(1, 100000)');
    iRego3 = cCosniwa('reg_code', 'add(1, 10000)');
    iRego4 = cCosniwa('reg_code', '100 x add(1, 10000)');

    % Start the main CoSniWa time
    cCosniwa('start');

    cCosniwa('call_start', iRego2);  % Start code snippet (loop)
    for inxAdd=1:100
        cCosniwa('call_start', iRego1);  % Start code snippet (add)
        add(1, 100000);
        cCosniwa('call_stop', iRego1);   % Stop code snippet (add)
    endfor
    cCosniwa('call_stop', iRego2);   % Stop code snippet (loop)

    cCosniwa('call_start', iRego4);  % Start code snippet (loop)
    for inxAdd=1:100
        cCosniwa('call_start', iRego3);  % Start code snippet (add)
        add(1, 10000);
        cCosniwa('call_stop', iRego3);  % Stop code snippet (add)
    endfor
    cCosniwa('call_stop', iRego4);   % Stop code snippet (loop)

    % Stop the main CoSniWa time
    cCosniwa('stop');

    % Print the results
    cCosniwa('resultc');

end


function add(iA, iB)
% Add iA + iB in a slow way.

    for i = 1:iB
        iA = iA + 1;
    endfor
end
