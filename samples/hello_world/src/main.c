/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <stdlib.h>
#include "dac.h"
#include <zephyr/kernel.h>

volatile uint32_t m_init_done;
volatile uint32_t m_underflow_happened;

void DAC00_IRQHandler(void){
	printf("Interrupt : Entered DAC00_IRQHandler!\n");
	printf("Interrupt : Disabling DAC00 IRQ\n");
	NVIC_DisableIRQ(DAC00_IRQn);
	if (nrf_dac_event_check(NRF_DAC00, NRF_DAC_EVENT_STOPPED)) {
		printf("Interrupt : Clearing event STOPPED\n");
		nrf_dac_event_clear(NRF_DAC00, NRF_DAC_EVENT_STOPPED);
		printf("Interrupt : Resuming converting\n");
		nrf_dac_task_trigger(NRF_DAC00, NRF_DAC_TASK_START);
	} else if (nrf_dac_event_check(NRF_DAC00, NRF_DAC_EVENT_INITDONE)) {
		printf("Interrupt : Clearing event INITDONE\n");
		nrf_dac_event_clear(NRF_DAC00, NRF_DAC_EVENT_INITDONE);
		printf("Interrupt : DAC Init done\n");
		m_init_done = 0x1;
	} else if (nrf_dac_event_check(NRF_DAC00, NRF_DAC_EVENT_UNDERFLOW)) {
		printf("Interrupt : Clearing event UNDERFLOW\n");
		nrf_dac_event_clear(NRF_DAC00, NRF_DAC_EVENT_UNDERFLOW);
		printf("Interrupt : No more data. Stopping DAC00\n");
		nrf_dac_task_trigger(NRF_DAC00, NRF_DAC_TASK_STOP);
		m_underflow_happened = 0x1;
	} else {
		printf("Interrupt : Unknown event\n");
	}
	printf("Interrupt : Enabling DAC00 IRQ\n");
	NVIC_EnableIRQ(DAC00_IRQn);
}

int main(void) {

	nrf_dac_config_t dac_config = NRF_DAC_DEFAULT_CONFIG(0, 0, 0, 1);

	printf("Connecting DAC IRQ\n");
	IRQ_CONNECT(DAC00_IRQn, 5, DAC00_IRQHandler, 0, 0);
	m_init_done = 0x0;
	m_underflow_happened = 0x0;
	printf("Enabling DAC00 IRQ: %d\n", DAC00_IRQn);
	NVIC_EnableIRQ(DAC00_IRQn);
	printf("Reading INTEN: %#010X\n", NRF_DAC00->INTEN);
	printf("Enabling DAC00\n");
	nrf_dac_enable(NRF_DAC00);
	printf("Enabling interrupts for STOPPED, INITDONE and UNDERFLOW\n");
	nrf_dac_int_enable(NRF_DAC00, NRF_DAC_INT_STOPPED_MASK | NRF_DAC_INT_INITDONE_MASK | NRF_DAC_INT_UNDERFLOW_MASK);
	printf("Trying to configure and initialize DAC00\n");
	nrf_dac_init(NRF_DAC00, dac_config);
	while (m_init_done == 0) {}
	printf("Starting converting samples\n");
	nrf_dac_task_trigger(NRF_DAC00, NRF_DAC_TASK_START);
	for(int i = 0; i < 1000; i++) {i++; i--;} // to be replaced with k_msleep
	printf("Stopping converting samples\n");
	nrf_dac_task_trigger(NRF_DAC00, NRF_DAC_TASK_STOP);
	printf("Resuming converting samples\n");
	while (m_underflow_happened == 0) {}
	printf("Test successful, exit\n");
	return 0;
}
