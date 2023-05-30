#include "streamulus.h"

#define BOOST_TEST_MODULE operator_subscribe
#include <boost/test/included/unit_test.hpp>

#include "op_subscribe_values_fixture.h"

BOOST_FIXTURE_TEST_SUITE(operator_subscribe_test, ValuesFixture)

    BOOST_AUTO_TEST_CASE(if_else_operator_between_terminals) {
        // TODO: make this work
        /*
        RunTest(true ? t1 : 2, true ? v1 : 2);
        RunTest(true ? 2 : t1, true ? 2 : v1);

        RunTest(false ? t1 : 2, false ? v1 : 2);
        RunTest(false ? 2 : t1, false ? 2 : v1);
         */
    }

BOOST_AUTO_TEST_SUITE_END()
