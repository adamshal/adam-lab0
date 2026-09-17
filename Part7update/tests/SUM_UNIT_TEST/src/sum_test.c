/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/ztest.h>

#include "sum_log.h"

ZTEST(sum_log_test_suite, test_sum_log_basic)
{
	zassert_equal(sum_log(18, 42), 60, "18 + 42 should equal 60");
}

ZTEST(sum_log_test_suite, test_sum_log_negative)
{
	zassert_equal(sum_log(-10, -5), -15, "-10 + -5 should equal -15");
	zassert_equal(sum_log(-10, 5), -5, "-10 + 5 should equal -5");
}

ZTEST(sum_log_test_suite, test_sum_log_zero)
{
	zassert_equal(sum_log(0, 0), 0, "0 + 0 should equal 0");
	zassert_equal(sum_log(42, 0), 42, "42 + 0 should equal 42");
}

ZTEST_SUITE(sum_log_test_suite, NULL, NULL, NULL, NULL, NULL);
