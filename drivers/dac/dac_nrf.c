#define DT_DRV_COMPAT nordic_nrf_dac

#include <stdbool.h>
#include <zephyr/drivers/dac.h>
#include <zephyr/drivers/pinctrl.h>
#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <soc.h>
#include <hal/nrf_dac.h>
#include <zephyr/sys/printk.h>

volatile uint32_t m_init_done;
volatile uint32_t m_underflow_happened;

void DAC00_IRQHandler(void){
	printf("Interrupt : Entered DAC00_IRQHandler!\n");
	printf("Interrupt : Disabling DAC00 IRQ\n");
	NVIC_DisableIRQ(DAC00_IRQn);
	if (nrf_dac_event_check(NRF_DAC00, NRF_DAC_EVENT_STOPPED)) {
		printf("Interrupt : Clearing event STOPPED\n");
		nrf_dac_event_clear(NRF_DAC00, NRF_DAC_EVENT_STOPPED);
		printf("Interrupt : Stopping converting\n");
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

static const nrf_dac_config_t dac_nrf_config = NRF_DAC_DEFAULT_CONFIG(0, 0, 0, 1);

static int dac_nrf_init(const struct device *dev)
{
    const nrf_dac_config_t * config = dev->config;
    NRF_DAC_Type * base = config->base;
    m_init_done = 0;
    m_underflow_happened = 0;
    printf("Connecting DAC IRQ\n");
	IRQ_CONNECT(DAC00_IRQn, 5, DAC00_IRQHandler, 0, 0);
    printf("Enabling DAC00 IRQ: %d\n", DAC00_IRQn);
	NVIC_EnableIRQ(DAC00_IRQn);
	printf("Reading INTEN: %#010X\n", base->INTEN);
	printf("Enabling DAC00\n");
	nrf_dac_enable(base);
	printf("Enabling interrupts for STOPPED, INITDONE and UNDERFLOW\n");
	nrf_dac_int_enable(base, NRF_DAC_INT_STOPPED_MASK | NRF_DAC_INT_INITDONE_MASK | NRF_DAC_INT_UNDERFLOW_MASK);
    printk("Initializing device : %s\n", dev->name);
    printf("Enabling DAC00\n");
	nrf_dac_enable(base);
    nrf_dac_init(base, dac_nrf_config);
    return 0;
}

static int dac_nrf_channel_setup(const struct device *dev,
				   const struct dac_channel_cfg *channel_cfg)
{
	printk("Setting up device : %s\n- channel : %d\n- resolution : %d\n- buffered : %s\n",
            dev->name, channel_cfg->channel_id, channel_cfg->resolution, channel_cfg->buffered ? "TRUE" : "FALSE");
	return 0;
}

static int dac_nrf_write_value(const struct device *dev,
					uint8_t channel, uint32_t value)
{
    const nrf_dac_config_t * config = dev->config;
    NRF_DAC_Type * base = config->base;
	printk("Writing value for device : %s\n- channel : %d\n- value : %d\n",
            dev->name, channel, value);
    printf("Starting converting samples\n");
	nrf_dac_task_trigger(base, NRF_DAC_TASK_START);
	return 0;
}

static const struct dac_driver_api dac_nrf_api = {
	.channel_setup = dac_nrf_channel_setup,
	.write_value = dac_nrf_write_value
};


DEVICE_DT_INST_DEFINE(0, &dac_nrf_init, NULL, NULL, &dac_nrf_config, POST_KERNEL, CONFIG_DAC_INIT_PRIORITY, &dac_nrf_api)
