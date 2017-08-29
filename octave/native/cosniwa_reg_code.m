%
% cosniwa_reg_code.m [version 1.0]
% CoSniWa:  COde SNIppet stopWAtch [Octave port] - Code registration module.
%
% CoSniWa is dedicated to profile code using time stamps.
% Cosniwa  [Octave port - native .m implementation ] v1.0, 30 May 2017.
%
% read more on: www.speedupcode.com
%
% (c) Jacek Pierzchlewski, 2017  jacek@pierzchlewski.com
% license: BSD-2-Clause.
%


function [csw, iRego] = cosniwa_reg_code(csw, strLabel, iRego = -1000)
%
%  cosniwa_reg_code:
%
%  REGISTER CODE SNIPPET.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%    csw       [structure]   Cosniwa structure
%    strLabel  [string]      Label to be registered
%    iRego     [int number]  Requested registration code
%                            (optional, if it will not be given)
%
%  Return:
%    csw     [structure]    Cosniwa structure
%    iRego   [int number]   Given registration, NaN if registration is empty
%

    % If rego was not given, add a rego automatically
    if iRego == -1000
        [csw, iRego] = cosniwa_reg_code_without_requested_rego(csw, strLabel);
        return;
    end

    % Check if there is place for code snippet labels
    if (csw.nCSLabels == csw.nRegoMax)
        iRego = NaN;
        return;
    end

    % Negative Regos and MAIN_REGO is restricted for the main part of the stoper
    if (iRego < 0) || (iRego == csw.MAIN_REGO)
        iRego = NaN;
        return;
    end

    % Check if the label was not already registered
    iLabelRego = cosniwa_reg_is_label_in_labels(csw, strLabel);
    if iLabelRego ~= csw.NOT_FOUND
        % Label was found, check if it has the requested rego
        if iLabelRego ~= iRego
            % Label was registered with the other rego,
            % it is a registration error
            iRego = NaN;
        end
        return;
    end

    % Label was not found, so check if a given rego is already registered.
    % If it is registered, it is a registration error
    if cosniwa_reg_is_rego_in_labels(csw, iRego) == csw.FOUND
        iRego = NaN;
        return;
    end

    % Increase the number of labels, add current label and registration number
    csw.nCSLabels++;
    csw.cLabels{csw.nCSLabels} = strLabel;
    csw.vLabelsReg(csw.nCSLabels) = iRego;
end


function [csw, iRego] = cosniwa_reg_code_without_requested_rego(csw, strLabel)
%
%  cosniwa_reg_code_without_requested_rego:
%
%  REGISTER A CODE SNIPPET WITHOUT A REQUESTED REGO.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%    csw       [structure]   Cosniwa structure
%    strLabel  [string]      Label to be registered
%
%  Return:
%    csw     [structure]    Cosniwa structure
%    iRego   [int number]   Given registration
%
    % Loop over all the possible registration
    for iRegoTry = 1:csw.nRegoMax

        % Try to register the label with the current code
        [csw, iRego] = cosniwa_reg_code(csw, strLabel, iRegoTry);
        if ~isnan(iRego)
            % Ok, the rego was accepted
            return;
        end
    endfor
end


function iLabelRego = cosniwa_reg_is_label_in_labels(csw, strLabel)
%
%  cosniwa_reg_is_label_in_labels:
%
%  CHECK IF A GIVEN LABEL IS IN THE LABELS DATABASE.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%    csw        [structure]  Cosniwa structure
%    strLabel   [string]     Label to be checked
%
%
%  Return:
%    iLabelRego [int number]  Found registration of the label,
%                             csw.NOT_FOUND if not found
%

    % Check if the label exists
    vLabelFound = strcmp(csw.cLabels, strLabel);
    if sum(vLabelFound) == 0

        % Label was not found
        iLabelRego = csw.NOT_FOUND;
    else

        % Label exists
        vInx = (1:csw.nCSLabels)';
        iLabelRego = csw.vLabelsReg(vInx(vLabelFound));
    end
end


function bFound = cosniwa_reg_is_rego_in_labels(csw, iRego)
%
%  cosniwa_reg_is_rego_in_labels:
%
% CHECK IF A GIVEN REGO IS IN THE LABELS DATABASE.
%
%  -----------------------------------------------------------------------------
%
%  Parameters:
%    csw        [structure]  Cosniwa structure
%    strLabel   [string]     Label to be checked
%
%
%  Return:
%    bFound     [bool]  -> csw.FOUND if rego found
%                       -> csw.NOT_FOUND if rego not found
%

    % Check if the rego exists
    vRegoFound = (csw.vLabelsReg == iRego);
    if sum(vRegoFound) == 0

        % Rego was not found
        bFound = csw.NOT_FOUND;
    else

        % Rego exists
        bFound = csw.FOUND;
    end
    return;
end

