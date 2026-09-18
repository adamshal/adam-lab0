/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "bme280_direct.h"

LOG_MODULE_REGISTER(lab0_bme280, CONFIG_LOG_DEFAULT_LEVEL);

#define BME280_NODE DT_NODELABEL(bme280)

#if !DT_NODE_EXISTS(BME280_NODE)
#error "BME280 devicetree node is missing"
#endif

static const struct i2c_dt_spec bme280 = I2C_DT_SPEC_GET(BME280_NODE);

int main(void)
{
	struct bme280_calib calib;
	int ret;

	if (!device_is_ready(bme280.bus)) {
		LOG_ERR("BME280 I2C bus is not ready");
		return 0;
	}

	ret = bme280_init(&bme280, &calib);
	if (ret < 0) {
		LOG_ERR("BME280 init failed: %d", ret);
		return 0;
	}

	while (1) {
		int32_t temp_centi;
		int32_t whole;
		int32_t frac;

		ret = bme280_read_temperature_centi(&bme280, &calib, &temp_centi);
		if (ret < 0) {
			LOG_ERR("BME280 temperature read failed: %d", ret);
		} else {
			whole = temp_centi / 100;
			frac = temp_centi % 100;
			if (frac < 0) {
				frac = -frac;
			}

			LOG_INF("BME280 temperature: %d.%02d C", whole, frac);
		}

		k_sleep(K_SECONDS(1));
	}
}
