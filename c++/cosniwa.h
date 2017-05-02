/*
 * cosniwa.h [version 1.0r1]
 * CoSniWa:  COde SNIppet stopWAtch
 *
 * version 1.0r1 ready on 2 May 2017
 *
 * This is header for Code Snippet Stopwatch (CoSniWa) object.
 * CoSniWa is dedicated to profile code using time stamps.
 *
 * read more on: www.speedupcode.com
 *
 * (c) Jacek Pierzchlewski, 2017  jacek@pierzchlewski.com
 * license: BSD-2-Clause.
 */
#include <iostream>

#ifndef COSNIWA_IS_DEFINED
#define COSNIWA_IS_DEFINED 1

class Cosniwa
{

    private:

        // BOOL aliases:
        static const int MAIN_REGO = 0;

        static const int STOPPED = 0;
        static const int STARTED = 1;

        static const int START = 0;
        static const int STOP = 1;

        static const int OK = 1;
        static const int FAIL = 0;

        static const int FOUND = 0;
        static const int NOT_FOUND = -1;

        static const int MAIN_TIME_ON = 1;
        static const int MAIN_TIME_OFF = 0;

        // Structure with timing results for every code snippet registration
        // (one p. registered code snippet)
        struct TR
        {

            unsigned int iRego;         // Snippet registration number
            unsigned int nCalls;        // The number of calls
            unsigned int nShortCalls;   // The number of calls to short to
                                        // measure

            unsigned int nTS;   // The number of time stamps with this (iRego)
                                // code  snippet registration number

            unsigned int* isCallT;  // Table with times of all the calls
                                    // of code snippet with this rego

            long unsigned int tTotalTime;  // Total time of all the calls

            double tAvgTime;      // Average time
            double tVar;          // Variance

            double dPart;         // Fraction of the whole time measured
            double dMaxSpeedUp;   // Max speed-up according to Amdahl's law

            long unsigned int tMin;    // Min time of a single call
            long unsigned int tMax;    // Max time of a single call
        };

        // Structure with general timing results parameters:
        // (for all code snippets)
        struct TRPar
        {

            unsigned int nURego;   // the number of unique code snippet
                                   // registrations present int the timestamp
                                   // database

            int bMainTimeMeasured;  // Was the main time measured?

            unsigned int iLongestLabelSiz;   // Size (in characters) of the
                                             // longest code snippet label

            std::string strEmptyLabel;  // Create an empty label

            unsigned int iHighRego;     // Highest code snippet registration
                                        // number

            // Maximum values (for all the registered code snippets except
            //                 the main code snippet):
            long unsigned int tTotalMax;   // The maximum total time

            unsigned int nCallsMax;        // The maximum number of calls
                                           // for one code snippet

            double tAvgMax;          // Maximum average time
            double tVarMax;          // Maximum variance

            double dPartMax;         // Maximum fraction of the main time
            double dMaxSpeedUpMax;   // Maximum max possible speed up

            long unsigned int tMinMax;  // Maximum min time of a single call
            long unsigned int tMaxMax;  // Maximum max time of a single call

        };

        /* The maximum total number of calls:*/
        unsigned int nTotalCallsMax;    // All the calls for all code snippets
        static const unsigned int nTotalCallsMaxDef = 1000000;  // default

        /* The maximum number of code snippet registrations */
        static const unsigned int nRegoMax = 1000;

        /* Code snippet labels database: */
        std::string** strssCSLabels;    // Code snippet labels
        unsigned int* isCSRego;         // Code snippet registrations numbers

        unsigned int nCSLabels;      // The number of registered code snippet
                                     // labels

        /* Timestamps database: */
        timeval* stsTS;             // Timestamps [table with structures]
        unsigned int* isTSRego;     // Code snippet registrations corresponding
                                    // to timestamps
        unsigned int* isTSMark;     // Start/Stop markers corresponding
                                    // to timestamps
        long unsigned int iTSCtr;   // Time stamps counter


        /* **************************************************** */
        /* OBJECT INITIALISE FUNCTION: */
        /* **************************************************** */
        void _init(unsigned int);

        /* **************************************************** */
        /* INTERNAL POSTPROCESSING FUNCTIONS: */
        /* **************************************************** */

        std::string _postprocessing(int);

        // POSTPROCESSING:  Count the unique code snippet registrations
        unsigned int _post_count_rego(unsigned int**);
        int _post_count_rego_is_rego_counted(unsigned int*, unsigned int,
                                             unsigned int);

        // POSTPROCESSING:  Check the measurements:
        bool _post_check(unsigned int, unsigned int*, TRPar*);
        bool _post_check_start_stop(TRPar*);
        bool _post_check_start_stop_with_main();
        bool _post_check_start_stop_without_main();
        bool _post_check_interleave(unsigned int, unsigned int*);

        // POSTPROCESSING:  Count calls for every code snippet registration
        void _post_count_calls(unsigned int, unsigned int*, TR*);

        // POSTPROCESSING:  Allocate space for call times and
        //                  measure the times
        void _post_allocate_call_times(unsigned int, TR*);
        void _post_measure_call_times(unsigned int, unsigned int*, TR*);

        // POSTPROCESSING:  Process call times
        void _post_process_call_times(unsigned int, unsigned int*, TR*, TRPar);

        // POSTPROCESSING:  Sort the call time
        void _post_sort(unsigned int, unsigned int**, TR*);

        // POSTPROCESSING:  Find general postprocessin parameters
        void _post_find_general_param(unsigned int, unsigned int*, TR*, TRPar*);

        // POSTPROCESSING:  Print timing results
        static const unsigned int iTempBufSiz = 1024;
        std::string _post_print_timing(unsigned int, unsigned int*, TR*,
                                       TRPar, int);

        std::string _post_print_header();
        std::string _post_print_footer();
        std::string _post_print_main_time(TR*, TRPar);
        std::string _post_print_snippets_times(unsigned int, unsigned int*,
                                               TR*, TRPar, int);

        std::string _post_print_single_snippet_data(unsigned int, unsigned int,
                                                    unsigned int*,
                                                    TR*, TRPar, int);
        std::string _post_print_single_snippet_data_inx(unsigned int, TRPar);
        std::string _post_print_single_snippet_data_rego(TR, TRPar);
        std::string _post_print_single_snippet_data_label(TR, TRPar);
        std::string _post_print_single_snippet_data_calls(TR, TRPar);
        std::string _post_print_single_snippet_data_totaltime(TR, TRPar);
        std::string _post_print_single_snippet_data_fraction(TR, TRPar);
        std::string _post_print_single_snippet_data_max_s_up(TR, TRPar);
        std::string _post_print_single_snippet_data_avg_time(TR, TRPar);
        std::string _post_print_single_snippet_data_var(TR, TRPar);
        std::string _post_print_single_snippet_data_min_time(TR, TRPar);
        std::string _post_print_single_snippet_data_max_time(TR, TRPar);
        std::string _post_print_single_snippet_data_short_call(TR, TRPar);

        // Single record printing fuinctions:
        int _post_print_record_int(char*, int, int, const char*, const char*);
        int _post_print_record_int(char*, int, int,
                                   const char*, const char*, const char*);

        int _post_print_record_float(char*, double, double,
                                     const char*, const char*, int);
        int _post_print_record_float(char*, double, double,
                                     const char*, const char*, const char*,
                                     int, bool);

        void _post_print_space_padding(char*, unsigned int);

        // POSTPROCESSING:  Memory deallocation
        void _post_deallocate(unsigned int, unsigned int*, unsigned int*, TR*);

        /* **************************************************** */
        /* INTERNAL CODE SNIPPET REGISTRATION FUNCTIONS: */
        /* **************************************************** */

        // find label for a given rego
        std::string _reg_label_for_rego(unsigned int);

        // find if label is registered in code snippet labels
        int _reg_is_label_in_labels(std::string);

        // find next free rego of a code snippet
        unsigned int _reg_next_free_rego();

        // find if a given rego is registered in code snippet labels
        int _reg_is_rego_in_labels(unsigned int);

        // find if a given rego is registered
        int _reg_is_rego_in_TS(unsigned int);




    public:
        Cosniwa();
        Cosniwa(unsigned int);
        ~Cosniwa();

        // Code snippet registration
        unsigned int reg_code(std::string, unsigned int);
        unsigned int reg_code(const char*, unsigned int);
        unsigned int reg_code(char*, unsigned int);

        unsigned int reg_code(std::string);
        unsigned int reg_code(const char*);
        unsigned int reg_code(char*);

        // Stoper start / stop functions:
        void reset();

        void start();
        void stop();
        void call_start(unsigned int);
        void call_stop(unsigned int);

        // Print out the results
        std::string result();
        void resultc();
        std::string result_short();
        void resultc_short();
};
#endif

