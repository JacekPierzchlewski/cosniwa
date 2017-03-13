
4. List of functions
===================================


4.1. Python functions
++++++++++++++++++++++++++++++++++++++++++


4.1.1. Python code snippet registration functions
--------------------------------------------------------

**reg_code_with_rego** (string *strLabel*, int *iRego*)

      REGISTER CODE SNIPPET (v1).

      Function registers new code snippet label (*strLabel*) in the snippets
      database.

      Function registers the label with a requested registration number (*iRego*).

      If label already exists with a different registration number, function returns 0.

      Function returns number *iRego* in case of no errors.

          ARGUMENTS:
           *strLabel*:  [string]  Label for the code snippet. |br|
           *iRego*:     [int]     Requested registration number of the code snippet.

          RETURN:
           [int]  Registration number of the code snippet.It is equal to argument *iRego* if there are no errors.


**reg_code** (string *strLabel*)

      REGISTER CODE SNIPPET (v2).

      Function registers new code snippet label (*strLabel*) in the snippets
      database.
      Function returns registration number *iRego* given to the code snippet label.

          ARGUMENTS:
           *strLabel*:  [string]  Label for the code snippet.

          RETURN:
           [int]  Registration number of the code snippet.



**xreg_code_with_rego** (cosniwahandle *hCosniwa*, string *strLabel*, int *iRego*)

      REGISTER CODE SNIPPET (v1) IN EXTERNAL COSNIWA.

      Function registers new code snippet label (*strLabel*) in the snippets
      database in an external Cosniwa.

      Function registers the label with a requested registration number (*iRego*).

      If label already exists with a different registration number, function
      returns 0.

          ARGUMENTS:
           *hCosniwa*:  [cosniwahandle]   Handle to an external Cosniwa. |br|
           *strLabel*:  [string]  Label for the code snippet. |br|
           *iRego*:     [int]     Requested registration number of the code snippet.

          RETURN:
           [int]  Registration number of the code snippet.
           It is equal to argument *iRego* if there are no errors.


**xreg_code** (cosniwahandle *hCosniwa*, string *strLabel*)

      REGISTER CODE SNIPPET (v2) IN EXTERNAL COSNIWA.

      Function registers new code snippet label (*strLabel*) in the snippets database in an external Cosniwa.

      Function returns registration number *iRego* given to the code snippet label.

          ARGUMENTS:
           *hCosniwa*:  [cosniwahandle]   Handle to an external Cosniwa. |br|
           *strLabel*:  [string]  Label for the code snippet. |br|

          RETURN:
           [int]  Registration number of the code snippet.


4.1.2. Python stoper start/stop functions
--------------------------------------------------------

**reset** ()

      RESET COSNIWA MODULE.

      Function resets *Cosniwa* module.


**start** ()

      START THE MAIN TIME.


**stop** ()

      STOP THE MAIN TIME.


**call_start** (int *iRego*)

      START A CODE SNIPPET CALL.

          ARGUMENTS:
           *iRego*:  [int]  Registration number of a code snippet.


**call_stop** (int *iRego*)

      STOP A CODE SNIPPET CALL.

          ARGUMENTS:
           *iRego*:  [int]  Registration number of a code snippet.


**xreset** (cosniwahandle *hCosniwa*)

      RESET EXTERNAL COSNIWA MODULE.

          ARGUMENTS:
           *hCosniwa*:  [cosniwahandle]   Handle to an external Cosniwa.


**xstart** (cosniwahandle *hCosniwa*)

      START THE MAIN TIME IN EXTERNAL COSNIWA.

          ARGUMENTS:
           *hCosniwa*:  [cosniwahandle]   Handle to an external Cosniwa.


**xstop** (cosniwahandle *hCosniwa*)

      STOP THE MAIN TIME IN EXTERNAL COSNIWA.

          ARGUMENTS:
           *hCosniwa*:  [cosniwahandle]   Handle to an external Cosniwa.


**xcall_start** (cosniwahandle *hCosniwa*, int *iRego*)

     START A CODE SNIPPET CALL IN EXTERNAL COSNIWA.

          ARGUMENTS:
           *hCosniwa*:  [cosniwahandle]   Handle to an external Cosniwa. |br|
           *iRego*:  [int]  Registration number of a code snippet.


**xcall_stop** (cosniwahandle *hCosniwa*, int *iRego*)

      STOP A CODE SNIPPET CALL IN EXTERNAL COSNIWA.

          ARGUMENTS:
           *hCosniwa*:  [cosniwahandle]   Handle to an external Cosniwa. |br|
           *iRego*:  [int]  Registration number of a code snippet.


4.1.3. Python timing results functions
--------------------------------------------------------

**result** ()

      GET TIMING RESULTS.

          RETURN:
           [string]  String with timing results.


**resultc** ()

      PRINT TIMING RESULTS TO THE CONSOLE OUTPUT.


**result_short** ()

      GET TIMING RESULTS (SHORT VERSION).

          RETURN:
           [string]  String with timing results (short version).


**resultc_short** ()

      PRINT TIMING RESULTS (SHORT VERSION) TO THE CONSOLE OUTPUT.


**xresult** (cosniwahandle *hCosniwa*)

      GET TIMING RESULTS FROM EXTERNAL COSNIWA.

          ARGUMENTS:
           *hCosniwa*:  [cosniwahandle]   Handle to an external Cosniwa.

          RETURN:
           [string]  String with timing results (short version).


**xresultc** (cosniwahandle *hCosniwa*)

      PRINT TIMING RESULTS FROM EXTERNAL COSNIWA TO THE CONSOLE OUTPUT.

          ARGUMENTS:
           *hCosniwa*:  [cosniwahandle]   Handle to an external Cosniwa.


**xresult_short** (cosniwahandle *hCosniwa*)

      GET TIMING RESULTS (SHORT VERSION) FROM EXTERNAL COSNIWA.

          ARGUMENTS:
           *hCosniwa*:  [cosniwahandle]   Handle to an external Cosniwa.

          RETURN:
           [string]  String with timing results (short version).


**xresultc_short** (cosniwahandle *hCosniwa*)

      PRINT TIMING RESULTS (SHORT VERSION) FROM EXTERNAL COSNIWA TO THE CONSOLE OUTPUT.

          ARGUMENTS:
           *hCosniwa*:  [cosniwahandle]   Handle to an external Cosniwa.


4.1.4. Pyton external Cosniwa handle function
--------------------------------------------------------

**get_handle** ()

      GET HANDLE TO A COSNIWA MODULE.

          RETURN:
           [cosniwahandle]  Handle to Cosniwa module.


4.2. C++ functions
++++++++++++++++++++++++++++++++++++++++++


4.2.1. C++ *Cosniwa* constructors
--------------------------------------------------------

**Cosniwa** ()

    CONSTRUCTOR (v1). Use default maximum number of intervals.


**Cosniwa** (unsigned int *iMaxNCalls*)

    CONSTRUCTOR (v2). Set maximum number of intervals.

          PARAMETERS:
           *iMaxNCalls*:  [unsigned int]  The maximum number of intervals.


4.2.2. C++ code snippet registration functions
--------------------------------------------------------

unsigned int **reg_code** (std::string *strLabel*, unsigned int *iRego*)

      REGISTER CODE SNIPPET (v1A).

      Function registers new code snippet label (*strLabel*) in the snippets
      database.

      Function registers the label with a requested registration number (*iRego*).

      If label already exists with a different registration number, function
      returns NULL.

      Function returns *iRego* in case of no errors.


          PARAMETERS:
           *strLabel*:  [std::string]   Label for the code snippet. |br|
           *iRego*:     [unsigned int]  Requested registration number of the code snippet.

          RETURN:
           [unsigned int]  Registration number of the code snippet. It is equal to parameter *iRego* if there are no errors.


unsigned int **reg_code** (const char*  *csLabel*, unsigned int *iRego*)


      REGISTER CODE SNIPPET (v1B).

      Function registers new code snippet label (*csLabel*) in the snippets
      database.

      Function registers the label with a requested registration number (*iRego*).

      If label already exists with a different registration, function
      returns NULL.

      Function returns *iRego* in case of no errors.


          PARAMETERS:
           *csLabel*:   [const char*]   Label for the code snippet. |br|
           *iRego*:     [unsigned int]  Requested registration number of the code snippet.

          RETURN:
           [unsigned int]  Registration number of the code snippet. It is equal to parameter *iRego* if there are no errors.


unsigned int **reg_code** (char* *csLabel*, unsigned int *iRego*)

      REGISTER CODE SNIPPET (v1C).

      Function registers new code snippet label (*csLabel*) in the snippets
      database.

      Function registers the label with a requested registration number (*iRego*).

      If label already exists with a different registration, function
      returns NULL.

      Function returns *iRego* in case of no errors.


          PARAMETERS:
           *csLabel*:   [char*]         Label for the code snippet. |br|
           *iRego*:     [unsigned int]  Requested registration number of the code snippet.

          RETURN:
           [unsigned int]  Registration number of the code snippet. It is equal to parameter *iRego* if there are no errors.


unsigned int **reg_code** (std::string *strLabel*)


      REGISTER CODE SNIPPET (v2A).

      Function registers new code snippet label (*strLabel*) in the snippets database.

      Function returns registration number *iRego* given to the code snippet label.


          PARAMETERS:
           *strLabel*:  [std::string]  Label for the code snippet. |br|

          RETURN:
           [unsigned int]  Registration number of the code snippet. |br|


unsigned int **reg_code** (const char* *csLabel*)


      REGISTER CODE SNIPPET (v2B).

      Function registers new code snippet label (*csLabel*) in the snippets database.

      Function returns registration number *iRego* given to the code snippet label.


          PARAMETERS:
           *csLabel*:  [const char]  Label for the code snippet. |br|

          RETURN:
           [unsigned int]  Registration number of the code snippet. |br|



unsigned int **reg_code** (char* *csLabel*)


      REGISTER CODE SNIPPET (v2C).

      Function registers new code snippet label (*csLabel*) in the snippets database.

      Function returns registration number *iRego* given to the code snippet label.


          PARAMETERS:
           *csLabel*:  [char*]  Label for the code snippet.

          RETURN:
           [unsigned int]  Registration number of the code snippet.


4.2.3. C++ stoper start/stop functions
--------------------------------------------------------

void **reset** ()

      RESET COSNIWA OBJECT.


void **start** ()

      START THE MAIN TIME.


void **stop** ()

      STOP THE MAIN TIME.


void **call_start** (unsigned int *iRego*)

      START A CODE SNIPPET CALL.


          PARAMETERS:
           *iRego*:  [unsigned int]  Registration number of a code snippet.


void **call_stop** (unsigned int *iRego*)

      STOP A CODE SNIPPET CALL.

          PARAMETERS:
           *iRego*:  [unsigned int]  Registration number of a code snippet.



4.2.4. C++ timing results functions
--------------------------------------------------------

std::string **result** ()

      GET TIMING RESULTS.


          RETURN:
           [std::string]  String with timing results.


void **resultc** ()

      PRINT TIMING RESULTS TO THE CONSOLE OUTPUT.


std::string **result** ()

      GET TIMING RESULTS (SHORT VERSION).


          RETURN:
           [std::string]  String with timing results (short version).



void **resultc_short** ()

      PRINT TIMING RESULTS (SHORT VERSION) TO THE CONSOLE OUTPUT.
















