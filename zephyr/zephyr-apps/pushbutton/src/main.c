#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#if !DT_NODE_EXISTS(DT_NODELABEL(switch1))
#   error "switch1 component not properly defined."
#endif

#define SLEEP_TIME_MS   1

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(void)
{
    struct gpio_dt_spec switch_1 = GPIO_DT_SPEC_GET(DT_NODELABEL(switch1), gpios);

    if (!gpio_is_ready_dt(&led))
        return 0;

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0)
        return 0;

    for (;;) {
        if (gpio_pin_get_dt(&switch_1)) {
            while(gpio_pin_get_dt(&switch_1))
                k_msleep(SLEEP_TIME_MS);

            if (gpio_pin_toggle_dt(&led) < 0)
	        return 0;
        }
    }
    return 0;
}
