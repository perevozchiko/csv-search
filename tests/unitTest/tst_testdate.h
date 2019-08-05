#ifndef TST_TESTDATE_H
#define TST_TESTDATE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../../parser.h"
#include "../../constants.h"
#include "../../cmdparams.h"

using namespace testing;

TEST(testDate, testFunc)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

#endif // TST_TESTDATE_H
