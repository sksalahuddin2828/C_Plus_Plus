

#include "stream.h"

#define BOOST_TEST_MODULE stream
#include <boost/test/included/unit_test.hpp>

using namespace streamulus;

BOOST_AUTO_TEST_CASE(int_stream_append_one_value) {
    Stream<int> stream;

    // stream has no data before Append
    BOOST_CHECK(!stream.HasMore());
    BOOST_CHECK(!stream.IsValid());
    BOOST_CHECK_THROW(stream.Current(), std::invalid_argument);

    // stream has data and is valid after Append. Current sees the new data.
    stream.Append(1);
    BOOST_CHECK(stream.HasMore());
    BOOST_CHECK(stream.IsValid());
    BOOST_CHECK_EQUAL(1, stream.Current());

    // Current() consumed the 1, so no more data. But stream is valid and Current() still returns 1.
    BOOST_CHECK(!stream.HasMore());
    BOOST_CHECK(stream.IsValid());
    BOOST_CHECK_EQUAL(1, stream.Current());
}

BOOST_AUTO_TEST_CASE(int_stream_append_multiple_values) {
    Stream<int> stream;

    // Append multiple inputs
    stream.Append(2);
    stream.Append(3);
    BOOST_CHECK(stream.HasMore());
    BOOST_CHECK(stream.IsValid());
    BOOST_CHECK_EQUAL(2, stream.Current());

    // Current() consumed the 2, but we still have the 3 in the future.
    BOOST_CHECK(stream.HasMore());
    BOOST_CHECK(stream.IsValid());
    BOOST_CHECK_EQUAL(3, stream.Current());

    // Current() consumed the 3, so no more data.
    BOOST_CHECK(!stream.HasMore());
    BOOST_CHECK(stream.IsValid());
    BOOST_CHECK_EQUAL(3, stream.Current());
}


// repeats the tests above for integer, but on strings.
BOOST_AUTO_TEST_CASE(string_stream_test) {
    Stream<std::string> stream;
    // stream has no data before Append
    BOOST_CHECK(!stream.HasMore());
    BOOST_CHECK(!stream.IsValid());
    BOOST_CHECK_THROW(stream.Current(), std::invalid_argument);

    // stream has data and is valid after Append. Current sees the new data.
    stream.Append("1");
    BOOST_CHECK(stream.HasMore());
    BOOST_CHECK(stream.IsValid());
    BOOST_CHECK_EQUAL("1", stream.Current());

    // Current() consumed the 1, so no more data. But stream is valid and Current() still returns 1.
    BOOST_CHECK(!stream.HasMore());
    BOOST_CHECK(stream.IsValid());
    BOOST_CHECK_EQUAL("1", stream.Current());

    // Append multiple inputs
    stream.Append("2");
    stream.Append("3");
    BOOST_CHECK(stream.HasMore());
    BOOST_CHECK(stream.IsValid());
    BOOST_CHECK_EQUAL("2", stream.Current());

    // Current() consumed the 2, but we still have the 3 in the future.
    BOOST_CHECK(stream.HasMore());
    BOOST_CHECK(stream.IsValid());
    BOOST_CHECK_EQUAL("3", stream.Current());

    // Current() consumed the 3, so no more data.
    BOOST_CHECK(!stream.HasMore());
    BOOST_CHECK(stream.IsValid());
    BOOST_CHECK_EQUAL("3", stream.Current());
}
