/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>
#include <stdint.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/kernel.h>

#include "bme280_direct.h"

#define BME280_REG_CHIP_ID 0xD0
#define BME280_REG_CTRL_MEAS 0xF4
#define BME280_REG_TEMP_MSB 0xFA
#define BME280_REG_CALIB_T1 0x88

#define BME280_CHIP_ID 0x60
#define BME280_CTRL_MEAS_TEMP_X1_NORMAL 0x23

static uint16_t u16_le(const uint8_t *buf)
{
	return (uint16_t)buf[0] | ((uint16_t)buf[1] << 8);
}

static int16_t s16_le(const uint8_t *buf)
{
	return (int16_t)u16_le(buf);
}

static int bme280_read_calibration(const struct i2c_dt_spec *dev,
				   struct bme280_calib *calib)
{
	uint8_t buf[6];
	int ret;

	ret = i2c_burst_read_dt(dev, BME280_REG_CALIB_T1, buf, sizeof(buf));
	if (ret < 0) {
		return ret;
	}

	calib->dig_t1 = u16_le(&buf[0]);
	calib->dig_t2 = s16_le(&buf[2]);
	calib->dig_t3 = s16_le(&buf[4]);

	return 0;
}

int bme280_init(const struct i2c_dt_spec *dev, struct bme280_calib *calib)
{
	uint8_t chip_id;
	int ret;

	ret = i2c_reg_read_byte_dt(dev, BME280_REG_CHIP_ID, &chip_id);
	if (ret < 0) {
		return ret;
	}

	if (chip_id != BME280_CHIP_ID) {
		return -ENODEV;
	}

	ret = bme280_read_calibration(dev, calib);
	if (ret < 0) {
		return ret;
	}

	ret = i2c_reg_write_byte_dt(dev, BME280_REG_CTRL_MEAS,
				    BME280_CTRL_MEAS_TEMP_X1_NORMAL);
	if (ret < 0) {
		return ret;
	}

	k_msleep(10);

	return 0;
}

int32_t bme280_compensate_temperature_centi(int32_t adc_temp,
					    const struct bme280_calib *calib)
{
	int32_t var1;
	int32_t var2;
	int32_t t_fine;

	var1 = ((((adc_temp >> 3) - ((int32_t)calib->dig_t1 << 1))) *
		((int32_t)calib->dig_t2)) >> 11;
	var2 = (((((adc_temp >> 4) - ((int32_t)calib->dig_t1)) *
		  ((adc_temp >> 4) - ((int32_t)calib->dig_t1))) >> 12) *
		((int32_t)calib->dig_t3)) >> 14;
	t_fine = var1 + var2;

	return (t_fine * 5 + 128) >> 8;
}

int bme280_read_temperature_centi(const struct i2c_dt_spec *dev,
				  const struct bme280_calib *calib,
				  int32_t *temp_centi)
{
	uint8_t buf[3];
	int32_t adc_temp;
	int ret;

	ret = i2c_burst_read_dt(dev, BME280_REG_TEMP_MSB, buf, sizeof(buf));
	if (ret < 0) {
		return ret;
	}

	adc_temp = ((int32_t)buf[0] << 12) | ((int32_t)buf[1] << 4) |
		   ((int32_t)buf[2] >> 4);
	*temp_centi = bme280_compensate_temperature_centi(adc_temp, calib);

	return 0;
}
