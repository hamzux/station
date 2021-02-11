#include "CUnit.h"
#include "Basic.h"
//#include "CUnit/Automated.h"
//#include "CUnit/Console.h"


#include <stdio.h>  // for printf

/* Test Suite setup and cleanup functions: */

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

/************* Test case functions ****************/

//void test_case_sample(void)
//{
//   CU_ASSERT(CU_TRUE);
//   CU_ASSERT_NOT_EQUAL(2, -1);
//   CU_ASSERT_STRING_EQUAL("string #1", "string #1");
//   CU_ASSERT_STRING_NOT_EQUAL("string #1", "string #2");
//
//   CU_ASSERT(CU_FALSE);
//   CU_ASSERT_EQUAL(2, 3);
//   CU_ASSERT_STRING_NOT_EQUAL("string #1", "string #1");
//   CU_ASSERT_STRING_EQUAL("string #1", "string #2");
//}

void moyenne_test(void) {
  CU_ASSERT_DOUBLE_EQUAL( moyenne(20.0,30.0), 25.0,1.0);
  CU_ASSERT_DOUBLE_EQUAL( moyenne(30.0,20.0), 25.0,1.0);
}

void aberrant_test(void) {
 CU_ASSERT_EQUAL( nb_valeurs_aberrantes(20.0,22.0,24.0), 0);
 CU_ASSERT_EQUAL( nb_valeurs_aberrantes(34.0,20.0,22.0), 1);
 CU_ASSERT_EQUAL( nb_valeurs_aberrantes(20.0,31.0,48.0), 2);
}
void pollution_test(void) {
  CU_ASSERT_EQUAL( detection_pic(20.0,22.0,24.0),0);
  CU_ASSERT_EQUAL( detection_pic(1.0,20.0,40.0), 1);
}

/************* Test Runner Code goes here **************/

int main ( void )
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if ( CUE_SUCCESS != CU_initialize_registry() )
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite( "station_test_suite", init_suite, clean_suite );
   if ( NULL == pSuite ) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if ( (NULL == CU_add_test(pSuite, "moyenne_test", moyenne_test)) ||
        (NULL == CU_add_test(pSuite, "aberrant_test", aberrant_test)) ||
        (NULL == CU_add_test(pSuite, "pollution_test", pollution_test))

      )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // Run all tests using the basic interface
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   printf("\n");
   CU_basic_show_failures(CU_get_failure_list());
   printf("\n\n");
/*
   // Run all tests using the automated interface
   CU_automated_run_tests();
   CU_list_tests_to_file();

   // Run all tests using the console interface
   CU_console_run_tests();
*/
   /* Clean up registry and return */
   CU_cleanup_registry();
   return CU_get_error();
}
