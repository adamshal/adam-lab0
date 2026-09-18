/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/ztest.h>

#include "bme280_direct.h"

#define BME280_NODE DT_NODELABEL(bme280)
#define BME280_BUS DT_BUS(BME280_NODE)

ZTEST(bme280_dt_test_suite, test_bme280_devicetree_node)
{
	zassert_true(DT_NODE_EXISTS(BME280_NODE), "bme280 node should exist");
	zassert_true(DT_NODE_HAS_STATUS(BME280_NODE, okay), "bme280 node should be okay");
	zassert_true(DT_NODE_HAS_STATUS(BME280_BUS, okay), "BME280 I2C bus should be okay");
	zassert_equal(DT_REG_ADDR(BME280_NODE), 0x77, "BME280 I2C address should be 0x77");
	zassert_equal(DT_PROP(BME280_BUS, clock_frequency), 100000,
		      "BME280 I2C bus should use standard-mode speed");
}

ZTEST(bme280_dt_test_suite, test_bme280_temperature_compensation)
{
	const struct bme280_calib calib = {
		.dig_t1 = 27504,
		.dig_t2 = 26435,
		.dig_t3 = -1000,
	};

	zassert_equal(bme280_compensate_temperature_centi(519888, &calib), 2508,
		      "Datasheet example should convert to 25.08 C");
}

ZTEST_SUITE(bme280_dt_test_suite, NULL, NULL, NULL, NULL, NULL);
