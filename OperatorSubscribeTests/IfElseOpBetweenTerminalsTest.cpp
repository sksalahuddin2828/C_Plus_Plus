#include "streamulus.h"

#define BOOST_TEST_MODULE operator_subscribe
#include <boost/test/included/unit_test.hpp>

#include "op_subscribe_values_fixture.h"

BOOST_FIXTURE_TEST_SUITE(operator_subscribe_test, ValuesFixture)

    BOOST_AUTO_TEST_CASE(if_else_operator_between_terminals) {
        // TODO: make this work
        /*
        RunTest(true ? t1 : t2, true ? v1 : v2);
        RunTest(true ? t2 : t1, true ? v2 : v1);

        RunTest(false ? t1 : t2, false ? v1 : v2);
        RunTest(false ? t2 : t1, false ? v2 : v1);
         */
    }

BOOST_AUTO_TEST_SUITE_END()
