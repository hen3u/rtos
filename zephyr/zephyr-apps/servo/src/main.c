#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>

#if !DT_NODE_EXISTS(DT_NODELABEL(switch1))
#   error "switch1 component not properly defined."
#endif

#define SLEEP_TIME_MS   1

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec switch_1 = GPIO_DT_SPEC_GET(DT_NODELABEL(switch1), gpios);

static const struct pwm_dt_spec servo = PWM_DT_SPEC_GET(DT_NODELABEL(servo));
static const uint32_t min_pulse = DT_PROP(DT_NODELABEL(servo), min_pulse);
static const uint32_t max_pulse = DT_PROP(DT_NODELABEL(servo), max_pulse);

#define STEP PWM_USEC(100)

enum direction {
	DOWN,
	UP,
};

int main(void)
{
    printf("Hello World! %s\n", CONFIG_BOARD_TARGET);
    printf("min_pulse %d\n", min_pulse);
    printf("max_pulse %d\n", max_pulse);
	uint32_t pulse_width = min_pulse;
	enum direction dir = UP;
	int ret;
    printk("Servomotor control\n");

    if (!gpio_is_ready_dt(&led))
        return 0;

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0)
        return 0;

    if (!pwm_is_ready_dt(&servo)) {
        printk("Error: PWM device %s is not ready\n", servo.dev->name);
        return 0;
    }

    for (;;) {
        /*if (gpio_pin_get_dt(&switch_1)) {
            while(gpio_pin_get_dt(&switch_1))
                k_msleep(SLEEP_TIME_MS);

            printf("GPIO toggle\n");

            if (gpio_pin_toggle_dt(&led) < 0){
	            return 0;
            }
        }*/
		printk("pulse_width %d\n", pulse_width);

		ret = pwm_set_pulse_dt(&servo, pulse_width);
		if (ret < 0) {
			printk("Error %d: failed to set pulse width\n", ret);
			return 0;
		}

		if (dir == DOWN) {
			if (pulse_width <= min_pulse) {
				dir = UP;
				pulse_width = min_pulse;
			} else {
				pulse_width -= STEP;
			}
		} else {
			pulse_width += STEP;

			if (pulse_width >= max_pulse) {
				dir = DOWN;
				pulse_width = max_pulse;
			}
		}

		k_sleep(K_SECONDS(0.1));
    }
    return 0;
}
