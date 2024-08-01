/*
 * Copyright (c) 2024 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <zephyr/drivers/dac.h>

#define DAC_NODE DT_ALIAS(dac1)

extern volatile uint32_t m_init_done;
extern volatile uint32_t m_underflow_happened;

const struct device *const dac_dev = DEVICE_DT_GET(DT_NODELABEL(dac1));

static const struct dac_channel_cfg dac_ch_cfg = {
	.channel_id  = 1,
	.resolution  = 16,
	.buffered = true
};

int main(void) 
{
	printf("Hello World! %s\n", CONFIG_BOARD_TARGET);
	printf("Getting DAC device\n");
	printf("DAC device status : %s\n", DT_PROP(DAC_NODE, status));
	if (!device_is_ready(dac_dev)) {
		printf("DAC device %s is not ready\n", dac_dev->name);
		return 0;
	} else {
		printf("DAC device %s is ready\n", dac_dev->name);
	}
	while (m_init_done == 0) {}
	printf("Mocking channel setup\n");
	dac_channel_setup(dac_dev, &dac_ch_cfg);
	printf("Mocking writing value\n");
	dac_write_value(dac_dev, 1, 100);
	while (m_underflow_happened == 0) {}
	printf("Test successful, exit\n");
	return 0;
}
