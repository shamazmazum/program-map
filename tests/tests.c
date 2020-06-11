#include <stdlib.h>
#include <string.h>

#include <CUnit/CUError.h>
#include <CUnit/TestDB.h>
#include <CUnit/TestRun.h>
#include <CUnit/Basic.h>

#include <program-map.h>

static void test_existing () {
    struct pm_program_handler handler;
    int res;

    res = pm_map_program (&handler, "success");
    CU_ASSERT (res);

    if (res) {
        CU_ASSERT (strcmp (handler.ph_space, "Test...\n") == 0);
        CU_ASSERT (strlen (handler.ph_space) == handler.ph_size); /* Minus '\0', plus '\n' */
        pm_unmap_program (&handler);
    }
}

static void test_nonexisting () {
    struct pm_program_handler handler;

    CU_ASSERT (!pm_map_program (&handler, "failure"));
}

static CU_TestInfo tests[] = {
    { "Existing file",     test_existing,    },
    { "Non-existing file", test_nonexisting, },
    CU_TEST_INFO_NULL
};

static CU_SuiteInfo suites[] = {
    { "program-map", NULL, NULL, NULL, NULL, tests },
    CU_SUITE_INFO_NULL
};

int main () {
    int code;

    if (CU_initialize_registry() != CUE_SUCCESS) {
        fprintf (stderr, "Failed to initialize registry: %s\n",
                 CU_get_error_msg ());
        return EXIT_FAILURE;
    }

    if (CU_register_suites (suites) != CUE_SUCCESS) {
        fprintf (stderr, "Failed to add suites: %s\n",
                 CU_get_error_msg ());
        CU_cleanup_registry ();
        return EXIT_FAILURE;
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    code = (CU_get_number_of_tests_failed() == 0)? 0: EXIT_FAILURE;
    CU_cleanup_registry();

    return code;
}
