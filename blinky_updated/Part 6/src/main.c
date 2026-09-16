/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>

#if defined(CONFIG_SUM_PRINT)
#include "sum_printk.h"
#elif defined(CONFIG_SUM_LOG)
#include "sum_log.h"
#endif

int main(void)
{
	const int a = 18;
	const int b = 42;

	while (1) {
		int result;

#if defined(CONFIG_SUM_PRINT)
		result = sum_printk(a, b);
#elif defined(CONFIG_SUM_LOG)
		result = sum_log(a, b);
#else
#error "Select CONFIG_SUM_PRINT or CONFIG_SUM_LOG"
#endif

		if (result != (a + b)) {
			return -1;
		}

		k_sleep(K_SECONDS(1));
	}
}
