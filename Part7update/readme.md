# ESE 5180 Lab 0 Zephyr App

This application contains the Lab 0 Zephyr exercises for the nRF7002 DK.

The application builds one of two sum implementations selected with Kconfig:

- `CONFIG_SUM_PRINT` uses `printk()`.
- `CONFIG_SUM_LOG` uses the Zephyr logger and prints a hexdump of the inputs.

The nRF7002 DK overlay defines the aliases used in the LED and button sections:

- `led5180` points to LED2.
- `button5180` points to Button 1.

Part 7 adds a Ztest unit test for `sum_log()` in `tests/SUM_UNIT_TEST`. The test covers basic addition, negative inputs, and zero inputs.
