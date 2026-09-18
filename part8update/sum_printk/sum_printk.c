/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>

#include "sum_printk.h"

int sum_printk(int a, int b)
{
	int result = a + b;

	printk("SUM_PRINT using printk\n");
	printk("%d + %d = %d\n", a, b, result);

	return result;
}
