%
% example2.m [version 1.0]
% CoSniWa:  COde SNIppet stopWAtch [Octave port] - Example 2.
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

function example2()

    % Initalise cosniwa
    cCosniwa('init');

    cCosniwa('call_start', 2);  % Start code snippet (loop)
    for inxAdd=1:100
        cCosniwa('call_start', 1);  % Start code snippet (add)
        add(1, 10000);
        cCosniwa('call_stop', 1);   % Stop code snippet (add)
    endfor
    cCosniwa('call_stop', 2);   % Stop code snippet (loop)

   % Print the results
    cCosniwa('resultc');
end


function add(iA, iB)
% Add iA + iB in a slow way.

    for i = 1:iB
        iA = iA + 1;
    endfor
end
