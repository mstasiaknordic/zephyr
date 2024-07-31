#ifndef DAC_H
#define DAC_H

#ifdef __cplusplus
    extern "C" {
#endif

#include <nrfx.h>
#include <stdbool.h>

typedef enum
{
    NRF_DAC_TASK_START = offsetof(NRF_DAC_Type, TASKS_START), /**< DAC start sampling task. */
    NRF_DAC_TASK_STOP  = offsetof(NRF_DAC_Type, TASKS_STOP),  /**< DAC stop sampling task. */
    NRF_DAC_TASK_ABORT = offsetof(NRF_DAC_Type, TASKS_ABORT), /**< DAC abort sampling task. */
} nrf_dac_task_t;

typedef enum
{
    NRF_DAC_INT_STOPPED_MASK   = DAC_INTENSET_STOPPED_Msk,     /**< DAC interrupt on STOPPED event. */
    NRF_DAC_INT_ABORTED_MASK   = DAC_INTENSET_ABORTED_Msk,     /**< DAC interrupt on ABORTED event. */
    NRF_DAC_INT_UNDERFLOW_MASK = DAC_INTENSET_UNDERFLOW_Msk,   /**< DAC interrupt on UNDERFLOW event. */
    NRF_DAC_INT_INITDONE_MASK  = DAC_INTENSET_INITDONE_Msk,    /**< DAC interrupt on INITDONE event. */
} nrf_dac_int_mask_t;

typedef enum
{
    NRF_DAC_SHORTS_INITDONE_START_MASK  = DAC_SHORTS_INITDONE_START_Msk,
    NRF_DAC_SHORTS_UNDERFLOW_ABORT_MASK = DAC_SHORTS_UNDERFLOW_ABORT_Msk,
} nrf_dac_short_mask_t;

typedef enum
{
    NRF_DAC_EVENT_STOPPED   = offsetof(NRF_DAC_Type, EVENTS_STOPPED),   /**< Transfer stopped. */
    NRF_DAC_EVENT_ABORTED   = offsetof(NRF_DAC_Type, EVENTS_ABORTED),   /**< Transfer aborted. */
    NRF_DAC_EVENT_UNDERFLOW = offsetof(NRF_DAC_Type, EVENTS_UNDERFLOW), /**< DMA read from memory failed. */
    NRF_DAC_EVENT_INITDONE  = offsetof(NRF_DAC_Type, EVENTS_INITDONE),  /**< Initialization is complete. */
} nrf_dac_event_t;

typedef enum
{
    NRF_DAC_SAMPLESOURCE_DMA = DAC_CONFIG_SAMPLESOURCE_SAMPLESOURCE_DMA, /**< DMA as DAC samplesource */
    NRF_DAC_SAMPLESOURCE_APB = DAC_CONFIG_SAMPLESOURCE_SAMPLESOURCE_APB, /**< APB as DAC samplesource */
} nrf_dac_config_samplesource_t;

typedef enum
{
    NRF_DAC_MCK_DIV_CKDIV2   = DAC_MCK_DIV_DIV_CKDIV2,   /**< CK divided by 2 */
    NRF_DAC_MCK_DIV_CKDIV3   = DAC_MCK_DIV_DIV_CKDIV3,   /**< CK divided by 3 */
    NRF_DAC_MCK_DIV_CKDIV4   = DAC_MCK_DIV_DIV_CKDIV4,   /**< CK divided by 4 */
    NRF_DAC_MCK_DIV_CKDIV5   = DAC_MCK_DIV_DIV_CKDIV5,   /**< CK divided by 5 */
    NRF_DAC_MCK_DIV_CKDIV6   = DAC_MCK_DIV_DIV_CKDIV6,   /**< CK divided by 6 */
    NRF_DAC_MCK_DIV_CKDIV8   = DAC_MCK_DIV_DIV_CKDIV8,   /**< CK divided by 8 */
    NRF_DAC_MCK_DIV_CKDIV10  = DAC_MCK_DIV_DIV_CKDIV10,  /**< CK divided by 10 */
    NRF_DAC_MCK_DIV_CKDIV11  = DAC_MCK_DIV_DIV_CKDIV11,  /**< CK divided by 11 */
    NRF_DAC_MCK_DIV_CKDIV15  = DAC_MCK_DIV_DIV_CKDIV15,  /**< CK divided by 15 */
    NRF_DAC_MCK_DIV_CKDIV16  = DAC_MCK_DIV_DIV_CKDIV16,  /**< CK divided by 16 */
    NRF_DAC_MCK_DIV_CKDIV21  = DAC_MCK_DIV_DIV_CKDIV21,  /**< CK divided by 21 */
    NRF_DAC_MCK_DIV_CKDIV23  = DAC_MCK_DIV_DIV_CKDIV23,  /**< CK divided by 23 */
    NRF_DAC_MCK_DIV_CKDIV30  = DAC_MCK_DIV_DIV_CKDIV30,  /**< CK divided by 30 */
    NRF_DAC_MCK_DIV_CKDIV31  = DAC_MCK_DIV_DIV_CKDIV31,  /**< CK divided by 31 */
    NRF_DAC_MCK_DIV_CKDIV32  = DAC_MCK_DIV_DIV_CKDIV32,  /**< CK divided by 32 */
    NRF_DAC_MCK_DIV_CKDIV42  = DAC_MCK_DIV_DIV_CKDIV42,  /**< CK divided by 42 */
    NRF_DAC_MCK_DIV_CKDIV63  = DAC_MCK_DIV_DIV_CKDIV63,  /**< CK divided by 63 */
    NRF_DAC_MCK_DIV_CKDIV125 = DAC_MCK_DIV_DIV_CKDIV125, /**< CK divided by 125 */
} nrf_dac_mck_div_t;

typedef enum
{
    NRF_DAC_SRC_CLKSRC_PCLK32M = DAC_MCK_SRC_CLKSRC_PCLK32M,
    NRF_DAC_SRC_CLKSRC_ACLK    = DAC_MCK_SRC_CLKSRC_ACLK,
} nrf_dac_src_clksrc_t;

typedef enum
{
    NRF_DAC_SRC_BYPASS_DISABLE = DAC_MCK_SRC_BYPASS_Disable,
    NRF_DAC_SRC_BYPASS_ENABLE  = DAC_MCK_SRC_BYPASS_Enable,
} nrf_dac_src_bypass_t;

typedef enum
{
    NRF_DAC_SRC_JITTER_DISABLE = DAC_MCK_SRC_JITTER_Disable,
    NRF_DAC_SRC_JITTER_ENABLE  = DAC_MCK_SRC_JITTER_Enable,
} nrf_dac_src_jitter_t;

typedef struct
{
    nrf_dac_src_clksrc_t clksrc;
    nrf_dac_src_bypass_t bypass;
    nrf_dac_src_jitter_t jitter;
} nrf_dac_mck_src_t;

typedef struct
{
    nrf_dac_mck_div_t div; /**< MCK divider */
    nrf_dac_mck_src_t src; /**< MCK source selection */
} nrf_dac_config_mck_t;

typedef enum
{
    NRF_DAC_PSEL_LEFT_CONNECT_DISCONNECTED  = DAC_PSEL_LEFT_CONNECT_Disconnected,
    NRF_DAC_PSEL_LEFT_CONNECT_CONNECTED     = DAC_PSEL_LEFT_CONNECT_Connected,
    NRF_DAC_PSEL_RIGHT_CONNECT_DISCONNECTED = DAC_PSEL_LEFT_CONNECT_Disconnected,
    NRF_DAC_PSEL_RIGHT_CONNECT_CONNECTED    = DAC_PSEL_LEFT_CONNECT_Connected,
} nrf_dac_psel_connect_t;

typedef struct
{
    nrf_dac_psel_connect_t connect;
    uint32_t               port;
    uint32_t               pin;
} nrf_dac_psel_t;


typedef struct
{
    nrf_dac_psel_t left;  /**< Pin select for left signal */
    nrf_dac_psel_t right; /**< Pin select for right signal */
} nrf_dac_config_psel_t;

typedef struct
{
    nrf_dac_config_samplesource_t samplesource; /**< DAC samplesource */
    nrf_dac_config_mck_t          mck;          /**< DAC master clock */
    nrf_dac_config_psel_t         psel;         /**< DAC pin select */
} nrf_dac_config_t;

#define NRF_DAC_DEFAULT_CONFIG(_l_port, _l_pin, _r_port, _r_pin)           \
{                                                                          \
    .samplesource = NRF_DAC_SAMPLESOURCE_DMA,                              \
    .mck          = {.div   = NRF_DAC_MCK_DIV_CKDIV2,                      \
                     .src   = {.clksrc  = NRF_DAC_SRC_CLKSRC_PCLK32M,      \
                               .bypass  = NRF_DAC_SRC_BYPASS_DISABLE,      \
                               .jitter  = NRF_DAC_SRC_JITTER_DISABLE}},    \
    .psel         = {.left  = {.connect = DAC_PSEL_LEFT_CONNECT_Connected, \
                               .port    = _l_port,                         \
                               .pin     = _l_pin},                         \
                     .right = {.connect = DAC_PSEL_RIGHT_CONNECT_Connected, \
                               .port    = _l_port,                         \
                               .pin     = _l_pin}},                        \
}

NRF_STATIC_INLINE void nrf_dac_enable(NRF_DAC_Type * p_reg)
{
    p_reg->ENABLE = 0x1;
}

NRF_STATIC_INLINE void nrf_dac_disable(NRF_DAC_Type * p_reg)
{
    p_reg->ENABLE = 0x0;
}

NRF_STATIC_INLINE uint32_t nrf_dac_enable_check(NRF_DAC_Type const * p_reg)
{
    return p_reg->ENABLE;
}

NRF_STATIC_INLINE void nrf_dac_int_enable(NRF_DAC_Type * p_reg, nrf_dac_int_mask_t mask)
{
    p_reg->INTENSET = mask;
}

NRF_STATIC_INLINE void nrf_dac_int_disable(NRF_DAC_Type * p_reg, nrf_dac_int_mask_t mask)
{
    p_reg->INTENCLR = mask;
}

NRF_STATIC_INLINE uint32_t nrf_dac_int_enable_check(NRF_DAC_Type const * p_reg, nrf_dac_int_mask_t mask)
{
    return p_reg->INTEN & mask;
}

// SHORTS not yet modelled
// NRF_STATIC_INLINE void nrf_dac_shorts_enable(NRF_DAC_Type * p_reg, nrf_dac_short_mask_t mask)
// {
//     p_reg->SHORTS |= mask;
// }

// NRF_STATIC_INLINE void nrf_dac_shorts_disable(NRF_DAC_Type * p_reg, nrf_dac_short_mask_t mask)
// {
//     p_reg->SHORTS &= ~(mask);
// }

NRF_STATIC_INLINE void nrf_dac_task_trigger(NRF_DAC_Type * p_reg, nrf_dac_task_t task)
{
    *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)task)) = 0x1UL;
}

NRF_STATIC_INLINE bool nrf_dac_event_check(NRF_DAC_Type const * p_reg, nrf_dac_event_t event)
{
    return nrf_event_check(p_reg, event);
}

NRF_STATIC_INLINE void nrf_dac_event_clear(NRF_DAC_Type * p_reg, nrf_dac_event_t event)
{
    *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)event)) = 0x0UL;
}

NRF_STATIC_INLINE void nrf_dac_init(NRF_DAC_Type * p_reg, nrf_dac_config_t config)
{
    // NOTE: This is a mock configuration, abstracted for the sake of simplicity
    p_reg->MCK.DIV             = config.mck.div             << DAC_MCK_DIV_DIV_Pos;
    p_reg->MCK.SRC             = (config.mck.src.clksrc     << DAC_MCK_SRC_CLKSRC_Pos)  |
                                 (config.mck.src.bypass     << DAC_MCK_SRC_BYPASS_Pos)  |
                                 (config.mck.src.jitter     << DAC_MCK_SRC_JITTER_Pos);
    p_reg->PSEL.LEFT           = (config.psel.left.pin      << DAC_PSEL_LEFT_PIN_Pos)   |
                                 (config.psel.left.port     << DAC_PSEL_LEFT_PORT_Pos)  |
                                 (config.psel.left.connect  << DAC_PSEL_LEFT_CONNECT_Pos);
    p_reg->PSEL.RIGHT          = (config.psel.right.pin     << DAC_PSEL_RIGHT_PIN_Pos)  |
                                 (config.psel.right.port    << DAC_PSEL_RIGHT_PORT_Pos) |
                                 (config.psel.right.connect << DAC_PSEL_RIGHT_CONNECT_Pos);
    // NOTE: Doesn't match DMA but changed for it to work with a bug in the model
    p_reg->CONFIG.SAMPLESOURCE = config.samplesource        << DAC_CONFIG_SAMPLESOURCE_SAMPLESOURCE_Pos;
}


#ifdef __cplusplus
}
#endif
#endif
