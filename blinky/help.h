// /**
//  * @brief Function for initializing the GPIOTE module.
//  *
//  * @details Only static configuration is supported to prevent the shared
//  * resource being customized by the initiator.
//  *
//  * @retval NRFX_SUCCESS             Initialization was successful.
//  * @retval NRFX_ERROR_INVALID_STATE The driver was already initialized.
//  */
// nrfx_err_t nrfx_gpiote_init(void);


// /**
//  * @brief Function for initializing a GPIOTE input pin.
//  * @details The input pin can act in two ways:
//  * - lower accuracy but low power (high frequency clock not needed)
//  * - higher accuracy (high frequency clock required)
//  *
//  * The initial configuration specifies which mode is used.
//  * If high-accuracy mode is used, the driver attempts to allocate one
//  * of the available GPIOTE channels. If no channel is
//  * available, an error is returned.
//  * In low accuracy mode SENSE feature is used. In this case, only one active pin
//  * can be detected at a time. It can be worked around by setting all of the used
//  * low accuracy pins to toggle mode.
//  * For more information about SENSE functionality, refer to Product Specification.
//  *
//  * @param[in] pin         Pin.
//  * @param[in] p_config    Initial configuration.
//  * @param[in] evt_handler User function to be called when the configured transition occurs.
//  *
//  * @retval NRFX_SUCCESS             Initialization was successful.
//  * @retval NRFX_ERROR_INVALID_STATE The driver is not initialized or the pin is already used.
//  * @retval NRFX_ERROR_NO_MEM        No GPIOTE channel is available.
//  */
// nrfx_err_t nrfx_gpiote_in_init(nrfx_gpiote_pin_t               pin,
//                                nrfx_gpiote_in_config_t const * p_config,
//                                nrfx_gpiote_evt_handler_t       evt_handler);


// /** @brief Input pin configuration. */
// typedef struct
// {
//     nrf_gpiote_polarity_t sense;               /**< Transition that triggers the interrupt. */
//     nrf_gpio_pin_pull_t   pull;                /**< Pulling mode. */
//     bool                  is_watcher      : 1; /**< True when the input pin is tracking an output pin. */
//     bool                  hi_accuracy     : 1; /**< True when high accuracy (IN_EVENT) is used. */
//     bool                  skip_gpio_setup : 1; /**< Do not change GPIO configuration */
// } nrfx_gpiote_in_config_t;


// /**
//  * @brief Macro for configuring a pin to use a GPIO IN or PORT EVENT to detect any change on the pin.
//  * @details Set hi_accu to true to use IN_EVENT.
//  */
// #define NRFX_GPIOTE_CONFIG_IN_SENSE_TOGGLE(hi_accu) \
// {                                                   \
//     .sense = NRF_GPIOTE_POLARITY_TOGGLE,            \
//     .pull = NRF_GPIO_PIN_NOPULL,                    \
//     .is_watcher = false,                            \
//     .hi_accuracy = hi_accu,                         \
//     .skip_gpio_setup = false,                       \
// }


// /**
//  * @brief Function for enabling sensing of a GPIOTE input pin.
//  *
//  * @details If the input pin is configured as high-accuracy pin, the function
//  * enables an IN_EVENT. Otherwise, the function enables the GPIO sense mechanism.
//  * The PORT event is shared between multiple pins, therefore the interrupt is always enabled.
//  *
//  * @param[in] pin        Pin.
//  * @param[in] int_enable True to enable the interrupt. Always valid for a high-accuracy pin.
//  */
// void nrfx_gpiote_in_event_enable(nrfx_gpiote_pin_t pin, bool int_enable);

//  /** @brief Polarity for the GPIOTE channel. */
// typedef enum
// {
//   NRF_GPIOTE_POLARITY_LOTOHI = GPIOTE_CONFIG_POLARITY_LoToHi,       ///<  Low to high.
//   NRF_GPIOTE_POLARITY_HITOLO = GPIOTE_CONFIG_POLARITY_HiToLo,       ///<  High to low.
//   NRF_GPIOTE_POLARITY_TOGGLE = GPIOTE_CONFIG_POLARITY_Toggle        ///<  Toggle.
// } nrf_gpiote_polarity_t;

// /**
//  * @brief Pin event handler prototype.
//  *
//  * @param[in] pin    Pin that triggered this event.
//  * @param[in] action Action that led to triggering this event.
//  */
// typedef void (*nrfx_gpiote_evt_handler_t)(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action);


// /**
//  * @brief Function for configuring and starting the timer.
//  *
//  * Function configures SysTick as a free-running timer without interrupt.
//  */
// void nrfx_systick_init(void);

// /**
//  * @brief Function for getting the current SysTick state.
//  *
//  * Function gets the current state of the SysTick timer.
//  * It can be used to check time-out by @ref nrfx_systick_test.
//  *
//  * @param[out] p_state The pointer to the state variable to be filled.
//  */
// void nrfx_systick_get(nrfx_systick_state_t * p_state);

// /**
//  * @brief Function for testing if the current time is higher in relation to the remembered state.
//  *
//  * @param[in] p_state Remembered state set by @ref nrfx_systick_get
//  * @param[in] us      Required time-out.
//  *
//  * @retval true  The current time is higher than the specified state plus the given time-out.
//  * @retval false The current time is lower than the specified state plus the given time-out.
//  */
// bool nrfx_systick_test(nrfx_systick_state_t const * p_state, uint32_t us);