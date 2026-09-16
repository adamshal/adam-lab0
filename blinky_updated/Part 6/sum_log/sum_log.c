/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/logging/log.h>

#include "sum_log.h"

LOG_MODULE_REGISTER(sum_log, CONFIG_LOG_DEFAULT_LEVEL);

int sum_log(int a, int b)
{
	int result = a + b;
	int values[] = { a, b };

	LOG_INF("SUM_LOG using Zephyr logger");
	LOG_DBG("Inputs are a=%d and b=%d", a, b);
	LOG_HEXDUMP_INF(values, sizeof(values), "Input values");
	LOG_WRN("Warning-level demo message");
	LOG_INF("%d + %d = %d", a, b, result);

	return result;
}
