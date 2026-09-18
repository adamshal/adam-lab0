# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(bme280_dt_test)

target_include_directories(app PRIVATE
	../../src
)

target_sources(app PRIVATE
	src/bme280_dt_test.c
	../../src/bme280_direct.c
)
