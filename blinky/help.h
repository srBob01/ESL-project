// typedef enum
// {
//     NRF_GPIO_PIN_NOPULL   = GPIO_PIN_CNF_PULL_Disabled, ///<  Pin pull-up resistor disabled.
//     NRF_GPIO_PIN_PULLDOWN = GPIO_PIN_CNF_PULL_Pulldown, ///<  Pin pull-down resistor enabled.
//     NRF_GPIO_PIN_PULLUP   = GPIO_PIN_CNF_PULL_Pullup,   ///<  Pin pull-up resistor enabled.
// } nrf_gpio_pin_pull_t;

// /** @brief Macro for mapping port and pin numbers to values understandable for nrf_gpio functions. */
// #define NRF_GPIO_PIN_MAP(port, pin) (((port) << 5) | ((pin) & 0x1F))

// /**
//  * @brief Function for configuring the given GPIO pin number as input, hiding inner details.
//  *        This function can be used to configure a pin as simple input.
//  *
//  * @note  Sense capability on the pin is disabled and input is connected to buffer so that the GPIO->IN register is readable.
//  *
//  * @param pin_number  Specifies the pin number.
//  * @param pull_config State of the pin range pull resistor (no pull, pulled down, or pulled high).
//  */
// __STATIC_INLINE void nrf_gpio_cfg_input(uint32_t pin_number, nrf_gpio_pin_pull_t pull_config);

// /**
//  * @brief Function for configuring the given GPIO pin number as output, hiding inner details.
//  *        This function can be used to configure a pin as simple output with gate driving GPIO_PIN_CNF_DRIVE_S0S1 (normal cases).
//  *
//  * @note  Sense capability on the pin is disabled and input is disconnected from the buffer as the pins are configured as output.
//  *
//  * @param pin_number Specifies the pin number.
//  */
// __STATIC_INLINE void nrf_gpio_cfg_output(uint32_t pin_number);

// /**
//  * @brief Function for reading the input level of a GPIO pin.
//  *
//  * If the value returned by this function is to be valid, the pin's input buffer must be connected.
//  *
//  * @param pin_number Specifies the pin number to read.
//  *
//  * @return 0 if the pin input level is low. Positive value if the pin is high.
//  */
// __STATIC_INLINE uint32_t nrf_gpio_pin_read(uint32_t pin_number);

// /**
//  * @brief Function for writing a value to a GPIO pin.
//  *
//  * For this function to have any effect, the pin must be configured as an output.
//  *
//  * @param pin_number Specifies the pin number to write.
//  * @param value      Specifies the value to be written to the pin.
//  * @arg 0 Clears the pin.
//  * @arg >=1 Sets the pin.
//  */
// __STATIC_INLINE void nrf_gpio_pin_write(uint32_t pin_number, uint32_t value);