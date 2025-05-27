#pragma once

#ifndef SIMPLE_BUTTON
#define SIMPLE_BUTTON

#ifdef __cplusplus
extern "C"
{
#endif

#include <zephyr/drivers/gpio.h>

    struct button_api
    {
        int (*get)(const struct deivce *dev, uint8_t *state);
    };

    struct button_config
    {
        struct gpio_dt_spec btn;
        uint32_t id;
    };

#ifdef __cplusplus
}
#endif

#endif // SIMPLE_BUTTON
