#include "streamulus.h"

#define BOOST_TEST_MODULE operator_subscribe
#include <boost/test/included/unit_test.hpp>

#include "op_subscribe_values_fixture.h"

BOOST_FIXTURE_TEST_SUITE(operator_subscribe_test, ValuesFixture)

    BOOST_AUTO_TEST_CASE(unary_operators_between_terminals) {
        RunTest(-t1, -v1);
        RunTest(*p1, v1);
        RunTest(~t1, ~v1);
        RunTest(!t1, !v1);
        RunTest(++t1, ++v1);
        RunTest(--t1, --v1);
        RunTest(t1++, v1++);
        RunTest(t1--, v1--);
    }

BOOST_AUTO_TEST_SUITE_END()
