#include "simple_button.h"

#include <stdint.h>
#include <stdio.h>
#include <zephyr/kernel.h>

static const struct device *btn_dev = DEVICE_DT_GET(DT_ALIAS(button_0));
static const struct device *btn_dev2 = DEVICE_DT_GET(DT_ALIAS(button_1));

int main(void)
{
    if (!device_is_ready(btn_dev))
    {
        printf("Button device not ready\n");
        return -1;
    }

    if (!device_is_ready(btn_dev2))
    {
        printf("Button device 2 not ready\n");
        return -1;
    }

    const struct button_api *btn_api = (const struct button_api *)btn_dev->api;

    uint8_t val = 0;
    uint8_t val2 = 0;

    for (;;)
    {
        int ret = btn_api->get(btn_dev, &val);
        if (ret < 0)
            printf("not able to do a get val\n");

        ret = btn_api->get(btn_dev2, &val2);
        if (ret < 0)
            printf("not able to do a get val\n");

        printf("%u, %u", val, val2);

        k_msleep(100);
    }

    return 0;
}
