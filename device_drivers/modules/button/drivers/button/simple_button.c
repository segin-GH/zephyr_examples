#define DT_DRV_COMPAT simple_button

#include "simple_button.h"
#include <errno.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(button);

static int button_init(const struct device *dev)
{
    const struct button_config *cfg = (const struct button_config *)dev->config;
    LOG_DBG("Init button instance ID: %u", cfg->id);

    const struct gpio_dt_spec *btn = &cfg->btn;

    if (!gpio_is_ready_dt(btn))
    {
        LOG_ERR("GPIO is not ready");
        return -ENODEV;
    }

    int err = gpio_pin_configure_dt(btn, GPIO_INPUT);
    if (err != 0)
    {
        LOG_ERR("GPIO is not configured");
        return -ENODEV;
    }

    return 0;
}

static int button_state_get(const struct device *dev, uint8_t *state)
{
    const struct button_config *cfg = (const struct button_config *)dev->config;
    const struct gpio_dt_spec *btn = &cfg->btn;

    int ret = gpio_pin_get_dt(btn);

    if (ret < 0)
    {
        LOG_ERR("Failed to get GPIO state %d", ret);
        return ret;
    }
    else
    {
        *state = ret;
    }

    return 0;
}

/* Device tree Handling */

static const struct button_api button_api_functions = {
    .get = button_state_get,
};

#define BUTTON_DEFINE(inst)                                                                                            \
    static const struct button_config button_config_##inst = {                                                         \
        .btn = GPIO_DT_SPEC_GET(DT_PHANDLE(DT_INST(inst, simple_button), pin), gpios),                                 \
        .id = inst,                                                                                                    \
    };                                                                                                                 \
    DEVICE_DT_INST_DEFINE(inst, button_init, NULL, NULL, &button_config_##inst, POST_KERNEL,                           \
                          CONFIG_GPIO_INIT_PRIORITY, &button_api_functions);

DT_INST_FOREACH_STATUS_OKAY(BUTTON_DEFINE);
