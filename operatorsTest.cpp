#include "operators.h"

#define BOOST_TEST_MODULE functor_of
#include <boost/test/included/unit_test.hpp>

namespace bp = boost::proto;
using namespace streamulus;

struct ValuesFixture {
protected:
    int i0 = 7;
    int j0 = 2;

    ValuesFixture() {
        i = iexp = i0;
        j = jexp = j0;
        pi = &i;
    }

    int i, j, iexp, jexp;
    int *pi;
};

BOOST_FIXTURE_TEST_SUITE(functor_of_test, ValuesFixture)

// Note: operators don't actually modify the stream, just generate a modified output.
// So we compare the vale of the "stream" with unmodified input values

    BOOST_AUTO_TEST_CASE(unary_operators) {
        BOOST_CHECK_EQUAL(functor_of<bp::tag::negate>()(i), -iexp);
        BOOST_CHECK_EQUAL(i, i0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::negate>()(-i), iexp);
        BOOST_CHECK_EQUAL(i, i0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::dereference>()(pi), iexp);
        BOOST_CHECK_EQUAL(i, i0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::complement>()(i), ~iexp);
        BOOST_CHECK_EQUAL(i, i0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::logical_not>()(i), !iexp);
        BOOST_CHECK_EQUAL(i, i0);
    }


    BOOST_AUTO_TEST_CASE(increment_decrement_operators) {
        BOOST_CHECK_EQUAL(functor_of<bp::tag::pre_inc>()(i), ++iexp);
        BOOST_CHECK_EQUAL(i, i0); iexp = i0;
        BOOST_CHECK_EQUAL(functor_of<bp::tag::pre_dec>()(i), --iexp);
        BOOST_CHECK_EQUAL(i, i0); iexp = i0;
        BOOST_CHECK_EQUAL(functor_of<bp::tag::post_inc>()(i), iexp++);
        BOOST_CHECK_EQUAL(i, i0); iexp = i0;
        BOOST_CHECK_EQUAL(functor_of<bp::tag::post_dec>()(i), iexp--);
        BOOST_CHECK_EQUAL(i, i0); iexp = i0;
    }

    BOOST_AUTO_TEST_CASE(binary_operators) {
        BOOST_CHECK_EQUAL(functor_of<bp::tag::shift_left>()(i, j), (iexp << jexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::shift_left>()(j, i), (jexp << iexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::shift_right>()(i, j), (iexp >> jexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::shift_right>()(j, i), (jexp >> iexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::multiplies>()(i, j), (iexp * jexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::multiplies>()(j, i), (jexp * iexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::divides>()(i, j), (iexp / jexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::divides>()(j, i), (jexp / iexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::modulus>()(i, j), (iexp % jexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::modulus>()(j, i), (jexp % iexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::plus>()(i, j), (iexp + jexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::plus>()(j, i), (jexp + iexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::minus>()(i, j), (iexp - jexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::minus>()(j, i), (jexp - iexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::less>()(i, j), (iexp < jexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::less>()(j, i), (jexp < iexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::greater>()(i, j), (iexp > jexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::greater>()(j, i), (jexp > iexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::less_equal>()(i, j), (iexp <= jexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::less_equal>()(j, i), (jexp <= iexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::greater_equal>()(i, j), (iexp >= jexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::greater_equal>()(j, i), (jexp >= iexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::equal_to>()(i, j), (iexp == jexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::equal_to>()(j, i), (jexp == iexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::not_equal_to>()(i, j), (iexp != jexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::not_equal_to>()(j, i), (jexp != iexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::logical_or>()(i, j), (iexp || jexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::logical_or>()(j, i), (jexp || iexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::logical_and>()(i, j), (iexp && jexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::logical_and>()(j, i), (jexp && iexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::bitwise_or>()(i, j), (iexp | jexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::bitwise_or>()(j, i), (jexp | iexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::bitwise_and>()(i, j), (iexp & jexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::bitwise_and>()(j, i), (jexp & iexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::bitwise_xor>()(i, j), (iexp ^ jexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::bitwise_xor>()(j, i), (jexp ^ iexp));
        BOOST_CHECK(i == i0 && j == j0);
    }

    BOOST_AUTO_TEST_CASE(assignment_operators) {
        BOOST_CHECK_EQUAL(functor_of<bp::tag::assign>()(i, j), (iexp = jexp));
        BOOST_CHECK(i == i0 && j == j0); iexp = i0; jexp = j0;
        BOOST_CHECK_EQUAL(functor_of<bp::tag::assign>()(j, i), (jexp = iexp));
        BOOST_CHECK(i == i0 && j == j0); iexp = i0; jexp = j0;
        BOOST_CHECK_EQUAL(functor_of<bp::tag::shift_left_assign>()(i, j), (iexp <<= jexp));
        BOOST_CHECK(i == i0 && j == j0); iexp = i0; jexp = j0;
        BOOST_CHECK_EQUAL(functor_of<bp::tag::shift_left_assign>()(j, i), (jexp <<= iexp));
        BOOST_CHECK(i == i0 && j == j0); iexp = i0; jexp = j0;
        BOOST_CHECK_EQUAL(functor_of<bp::tag::shift_right_assign>()(i, j), (iexp >>= jexp));
        BOOST_CHECK(i == i0 && j == j0); iexp = i0; jexp = j0;
        BOOST_CHECK_EQUAL(functor_of<bp::tag::shift_right_assign>()(j, i), (jexp >>= iexp));
        BOOST_CHECK(i == i0 && j == j0); iexp = i0; jexp = j0;
        BOOST_CHECK_EQUAL(functor_of<bp::tag::multiplies_assign>()(i, j), (iexp *= jexp));
        BOOST_CHECK(i == i0 && j == j0); iexp = i0; jexp = j0;
        BOOST_CHECK_EQUAL(functor_of<bp::tag::multiplies_assign>()(j, i), (jexp *= iexp));
        BOOST_CHECK(i == i0 && j == j0); iexp = i0; jexp = j0;
        BOOST_CHECK_EQUAL(functor_of<bp::tag::divides_assign>()(i, j), (iexp /= jexp));
        BOOST_CHECK(i == i0 && j == j0); iexp = i0; jexp = j0;
        BOOST_CHECK_EQUAL(functor_of<bp::tag::divides_assign>()(j, i), (jexp /= iexp));
        BOOST_CHECK(i == i0 && j == j0); iexp = i0; jexp = j0;
        BOOST_CHECK_EQUAL(functor_of<bp::tag::modulus_assign>()(i, j), (iexp %= jexp));
        BOOST_CHECK(i == i0 && j == j0); iexp = i0; jexp = j0;
        BOOST_CHECK_EQUAL(functor_of<bp::tag::modulus_assign>()(j, i), (jexp %= iexp));
        BOOST_CHECK(i == i0 && j == j0); iexp = i0; jexp = j0;
        BOOST_CHECK_EQUAL(functor_of<bp::tag::plus_assign>()(i, j), (iexp += jexp));
        BOOST_CHECK(i == i0 && j == j0); iexp = i0; jexp = j0;
        BOOST_CHECK_EQUAL(functor_of<bp::tag::plus_assign>()(j, i), (jexp += iexp));
        BOOST_CHECK(i == i0 && j == j0); iexp = i0; jexp = j0;
        BOOST_CHECK_EQUAL(functor_of<bp::tag::minus_assign>()(i, j), (iexp -= jexp));
        BOOST_CHECK(i == i0 && j == j0); iexp = i0; jexp = j0;
        BOOST_CHECK_EQUAL(functor_of<bp::tag::minus_assign>()(j, i), (jexp -= iexp));
        BOOST_CHECK(i == i0 && j == j0); iexp = i0; jexp = j0;
        BOOST_CHECK_EQUAL(functor_of<bp::tag::bitwise_and_assign>()(i, j), (iexp &= jexp));
        BOOST_CHECK(i == i0 && j == j0); iexp = i0; jexp = j0;
        BOOST_CHECK_EQUAL(functor_of<bp::tag::bitwise_and_assign>()(j, i), (jexp &= iexp));
        BOOST_CHECK(i == i0 && j == j0); iexp = i0; jexp = j0;
        BOOST_CHECK_EQUAL(functor_of<bp::tag::bitwise_or_assign>()(i, j), (iexp |= jexp));
        BOOST_CHECK(i == i0 && j == j0); iexp = i0; jexp = j0;
        BOOST_CHECK_EQUAL(functor_of<bp::tag::bitwise_or_assign>()(j, i), (jexp |= iexp));
        BOOST_CHECK(i == i0 && j == j0); iexp = i0; jexp = j0;
        BOOST_CHECK_EQUAL(functor_of<bp::tag::bitwise_xor_assign>()(i, j), (iexp ^= jexp));
        BOOST_CHECK(i == i0 && j == j0); iexp = i0; jexp = j0;
        BOOST_CHECK_EQUAL(functor_of<bp::tag::bitwise_xor_assign>()(j, i), (jexp ^= iexp));
        BOOST_CHECK(i == i0 && j == j0); iexp = i0; jexp = j0;
    }

    BOOST_AUTO_TEST_CASE(if_else_) {
        BOOST_CHECK_EQUAL(functor_of<bp::tag::if_else_>()(true, i, j), (true ? iexp : jexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::if_else_>()(true, j, i), (true ? jexp : iexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::if_else_>()(false, i, j), (false ? iexp : jexp));
        BOOST_CHECK(i == i0 && j == j0);
        BOOST_CHECK_EQUAL(functor_of<bp::tag::if_else_>()(false, j, i), (false ? jexp : iexp));
        BOOST_CHECK(i == i0 && j == j0);
    }

BOOST_AUTO_TEST_SUITE_END()
