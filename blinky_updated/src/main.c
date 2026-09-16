/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   2000
/* Poll the button every 20 ms */
#define SLEEP_TIME_MS   20


#define BUTTON_NODE DT_ALIAS(sw0)

/*
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED5180_NODE, gpios);
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(BUTTON_NODE, gpios);

	int ret;
	bool led_state = true;
	bool led_state = false;
	bool last_button_state = false;

	if (!gpio_is_ready_dt(&led) || !gpio_is_ready_dt(&button)) {
		return 0;
	}

	if (!gpio_is_ready_dt(&led)) {
	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return 0;

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
	if (ret < 0) {
	while (1) {
		ret = gpio_pin_toggle_dt(&led);
		bool button_state;

		ret = gpio_pin_get_dt(&button);
		if (ret < 0) {

		led_state = !led_state;
		printf("LED state: %s\n", led_state ? "ON" : "OFF");
		button_state = ret > 0;

		if (button_state && !last_button_state) {
			led_state = !led_state;
			ret = gpio_pin_set_dt(&led, led_state);
			if (ret < 0) {
				return 0;
			}

			printf("Button pressed; LED state: %s\n", led_state ? "ON" : "OFF");
		}

		last_button_state = button_state;
		k_msleep(SLEEP_TIME_MS);
