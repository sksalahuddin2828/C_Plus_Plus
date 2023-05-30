#pragma once

#include "streamulus.h"

using namespace streamulus;

struct assert_eq {
    template<typename T1, typename T2>
    bool operator()(const T1 &v1, const T2 &v2) const {
        BOOST_CHECK_EQUAL(v1, v2);
        return (v1 == v2);
    }
};

struct ValuesFixture {
protected:
    int v1_ = 7;
    int v2_ = 2;
    int v1 = v1_;
    int v2 = v2_;
    bp::terminal<int>::type t1 = {v1};
    bp::terminal<int>::type t2 = {v2};
    bp::terminal<int *>::type p1 = {&v1};
    bp::terminal<int *>::type p2 = {&v2};

    template<typename Expr, typename ExpectedValueType>
    void RunTest(Expr &expr, ExpectedValueType expected) {
        Streamulus engine;
        engine.Subscribe(Streamify<assert_eq>(expr, expected));
        Reset();
    }

private:
    void Reset() {
        v1 = v1_;
        v2 = v2_;
    }
};
