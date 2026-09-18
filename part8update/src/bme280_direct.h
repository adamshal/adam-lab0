/*
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef BME280_DIRECT_H
#define BME280_DIRECT_H

#include <stdint.h>
#include <zephyr/drivers/i2c.h>

struct bme280_calib {
	uint16_t dig_t1;
	int16_t dig_t2;
	int16_t dig_t3;
};

int bme280_init(const struct i2c_dt_spec *dev, struct bme280_calib *calib);
int bme280_read_temperature_centi(const struct i2c_dt_spec *dev,
				  const struct bme280_calib *calib,
				  int32_t *temp_centi);
int32_t bme280_compensate_temperature_centi(int32_t adc_temp,
					    const struct bme280_calib *calib);

#endif
