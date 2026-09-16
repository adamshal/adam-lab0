ESE 5180 Lab 0 Zephyr App
#########################

This application contains the Lab 0 Zephyr exercises for the nRF7002 DK.

The current Part 6 application builds one of two sum implementations selected
with Kconfig:

* ``CONFIG_SUM_PRINT`` uses ``printk()``.
* ``CONFIG_SUM_LOG`` uses the Zephyr logger and prints a hexdump of the inputs.

The nRF7002 DK overlay also defines the aliases used in the earlier LED and
button sections:

* ``led5180`` points to LED2.
* ``button5180`` points to Button 1.
