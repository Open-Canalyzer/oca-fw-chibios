/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/*
 * This file has been automatically generated using ChibiStudio board
 * generator plugin. Do not edit manually.
 */

#ifndef BOARD_H
#define BOARD_H

/*
 * Setup for STMicroelectronics STM32 Nucleo64-F302R8 board.
 */

/*
 * Board identifier.
 */
#define BOARD_OCA_V1
#define BOARD_NAME                  "Open-Canalyzer V1"

/*
 * Board oscillators-related settings.
 * NOTE: LSE not fitted.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                0U
#endif

#define STM32_LSEDRV                (3U << 3U)

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                8000000U
#endif

/*
 * MCU type as defined in the ST header.
 */
#define STM32F302xC

/*
 * IO pins assignments.
 */
#define GPIOA_PIN0_NC               0U
#define GPIOA_PIN1_NC               1U
#define GPIOA_PIN2_NC               2U
#define GPIOA_PIN3_NC               3U
#define GPIOA_PIN4_NC               4U
#define GPIOA_PIN5_NC               5U
#define GPIOA_PIN6_NC               7U
#define GPIOA_PIN7_NC               8U
#define GPIOA_PIN8_NC               9U
#define GPIOA_PIN9_NC               10U
#define GPIOA_USB_DM                11U
#define GPIOA_USB_DP                12U
#define GPIOA_SWDIO                 13U
#define GPIOA_SWCLK                 14U
#define GPIOA_PIN15_NC              15U

#define GPIOB_LED_ERR               0U
#define GPIOB_LED_STAT              1U
#define GPIOB_LED_ACT               2U
#define GPIOB_SWO                   3U
#define GPIOB_PIN4_NC               3U
#define GPIOB_PIN5_NC               4U
#define GPIOB_PIN6_NC               6U
#define GPIOB_PIN7_NC               7U
#define GPIOB_CAN_RX                8U
#define GPIOB_CAN_TX                9U
#define GPIOB_PIN10_NC              10U
#define GPIOB_PIN11_NC              11U
#define GPIOB_PIN12_NC              12U
#define GPIOB_PIN13_NC              13U
#define GPIOB_PIN14_NC              14U
#define GPIOB_PIN15_NC              15U

#define GPIOC_PIN0_NC               0U
#define GPIOC_PIN1_NC               1U
#define GPIOC_PIN2_NC               2U
#define GPIOC_PIN3_NC               3U
#define GPIOC_PIN4_NC               4U
#define GPIOC_PIN5_NC               5U
#define GPIOC_PIN6_NC               6U
#define GPIOC_PIN7_NC               7U
#define GPIOC_PIN8_NC               8U
#define GPIOC_PIN9_NC               9U
#define GPIOC_UART_TX               10U
#define GPIOC_UART_RX               11U
#define GPIOC_PIN12_NC              12U
#define GPIOC_PIN13_NC              13U
#define GPIOC_PIN14_NC              14U
#define GPIOC_PIN15_NC              15U

#define GPIOF_OSC_IN                0U
#define GPIOF_OSC_OUT               1U
#define GPIOF_PIN4_NC               4U

/*
 * IO lines assignments.
 */
#define LINE_USB_DM                 PAL_LINE(GPIOA, 11U)
#define LINE_USB_DP                 PAL_LINE(GPIOA, 12U)
#define LINE_SWDIO                  PAL_LINE(GPIOA, 13U)
#define LINE_SWCLK                  PAL_LINE(GPIOA, 14U)

#define LINE_CAN_RX                 PAL_LINE(GPIOB, 8U)
#define LINE_CAN_TX                 PAL_LINE(GPIOB, 9U)

#define LINE_OSC_IN                 PAL_LINE(GPIOF, 0U)
#define LINE_OSC_OUT                PAL_LINE(GPIOF, 1U)

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_VERYLOW(n)       (0U << ((n) * 2U))
#define PIN_OSPEED_LOW(n)           (1U << ((n) * 2U))
#define PIN_OSPEED_MEDIUM(n)        (2U << ((n) * 2U))
#define PIN_OSPEED_HIGH(n)          (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v) << (((n) % 8U) * 4U))

/*
 * GPIOA setup:
 *
 * PA0  - NC
 * PA1  - NC
 * PA2  - NC
 * PA3  - NC
 * PA4  - NC
 * PA5  - NC
 * PA6  - NC
 * PA7  - NC
 * PA8  - NC
 * PA9  - NC
 * PA10 - NC
 * PA11 - USB_DM                    (alternate 14).
 * PA12 - USB_DP                    (alternate 14).
 * PA13 - SWDIO                     (alternate 0).
 * PA14 - SWCLK                     (alternate 0).
 * PA15 - NC
 */
#define VAL_GPIOA_MODER             (PIN_MODE_ALTERNATE(GPIOA_USB_DM) |     \
                                     PIN_MODE_ALTERNATE(GPIOA_USB_DP) |     \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_SWDIO) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWCLK))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_HIGH(GPIOA_USB_DM) |        \
                                     PIN_OSPEED_VERYLOW(GPIOA_USB_DP) |     \
                                     PIN_OSPEED_HIGH(GPIOA_SWDIO) |         \
                                     PIN_OSPEED_HIGH(GPIOA_SWCLK))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_FLOATING(GPIOA_USB_DM) |     \
                                     PIN_PUPDR_FLOATING(GPIOA_USB_DP) |     \
                                     PIN_PUPDR_PULLUP(GPIOA_SWDIO) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOA_SWCLK))
#define VAL_GPIOA_ODR               (PIN_ODR_HIGH(GPIOA_USB_DM) |           \
                                     PIN_ODR_HIGH(GPIOA_USB_DP) |           \
                                     PIN_ODR_HIGH(GPIOA_SWDIO) |            \
                                     PIN_ODR_HIGH(GPIOA_SWCLK))
#define VAL_GPIOA_AFRL              (0)
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_USB_DM, 14U) |       \
                                     PIN_AFIO_AF(GPIOA_USB_DP, 14U) |       \
                                     PIN_AFIO_AF(GPIOA_SWDIO, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0U))

/*
 * GPIOB setup:
 *
 * PB0  - LED_ERR (RED)             (output).
 * PB1  - LED_STAT (BLUE)           (output).
 * PB2  - LED_ACT (GREEN)           (output).
 * PB3  - SWO
 * PB4  - NC
 * PB5  - NC
 * PB6  - NC
 * PB7  - NC
 * PB8  - CAN_RX
 * PB9  - CAN_TX
 * PB10 - NC
 * PB11 - NC
 * PB12 - NC
 * PB13 - NC
 * PB14 - NC
 * PB15 - NC
 */
#define VAL_GPIOB_MODER             (PIN_MODE_OUTPUT(GPIOB_LED_ERR) |       \
                                     PIN_MODE_OUTPUT(GPIOB_LED_STAT) |      \
                                     PIN_MODE_OUTPUT(GPIOB_LED_ACT) |       \
                                     PIN_MODE_ALTERNATE(GPIOB_SWO) |        \
                                     PIN_MODE_ALTERNATE(GPIOB_CAN_RX) |     \
                                     PIN_MODE_ALTERNATE(GPIOB_CAN_TX))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_LED_ERR) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_LED_STAT) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_LED_ACT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_SWO) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOB_CAN_RX) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_CAN_TX))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_HIGH(GPIOB_LED_ERR) |       \
                                     PIN_OSPEED_HIGH(GPIOB_LED_STAT) |      \
                                     PIN_OSPEED_HIGH(GPIOB_LED_ACT) |       \
                                     PIN_OSPEED_HIGH(GPIOB_SWO) |           \
                                     PIN_OSPEED_HIGH(GPIOB_CAN_RX) |       \
                                     PIN_OSPEED_HIGH(GPIOB_CAN_TX))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_PULLUP(GPIOB_LED_ERR) |      \
                                     PIN_PUPDR_PULLUP(GPIOB_LED_STAT) |     \
                                     PIN_PUPDR_PULLUP(GPIOB_LED_ACT) |      \
                                     PIN_PUPDR_PULLUP(GPIOB_SWO) |          \
                                     PIN_PUPDR_FLOATING(GPIOB_CAN_RX) |      \
                                     PIN_PUPDR_FLOATING(GPIOB_CAN_TX))
#define VAL_GPIOB_ODR               (PIN_ODR_LOW(GPIOB_LED_ERR) |           \
                                     PIN_ODR_LOW(GPIOB_LED_STAT) |          \
                                     PIN_ODR_LOW(GPIOB_LED_ACT) |           \
                                     PIN_ODR_HIGH(GPIOB_SWO) |              \
                                     PIN_ODR_HIGH(GPIOB_CAN_RX) |          \
                                     PIN_ODR_HIGH(GPIOB_CAN_TX))
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_LED_ERR, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_LED_STAT, 0U) |      \
                                     PIN_AFIO_AF(GPIOB_LED_ACT, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_SWO, 0U))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_CAN_RX, 9U) |       \
                                     PIN_AFIO_AF(GPIOB_CAN_TX, 9U))

/*
 * GPIOC setup:
 *
 * PC0   - NC
 * PC1   - NC
 * PC2   - NC
 * PC3   - NC
 * PC4   - NC
 * PC5   - NC
 * PC6   - NC
 * PC7   - NC
 * PC8   - NC
 * PC9   - NC
 * PC10  - NC
 * PC11  - NC
 * PC12  - NC
 * PC13  - NC
 * PC14  - NC
 * PC15  - NC
 */
#define VAL_GPIOC_MODER             (0)
#define VAL_GPIOC_OTYPER            (0)
#define VAL_GPIOC_OSPEEDR           (0)
#define VAL_GPIOC_PUPDR             (0)
#define VAL_GPIOC_ODR               (0)
#define VAL_GPIOC_AFRL              (0)
#define VAL_GPIOC_AFRH              (0)

/*
 * GPIOD setup:
 *
 * PD2   - NC
 */
#define VAL_GPIOD_MODER             (0)
#define VAL_GPIOD_OTYPER            (0)
#define VAL_GPIOD_OSPEEDR           (0)
#define VAL_GPIOD_PUPDR             (0)
#define VAL_GPIOD_ODR               (0)
#define VAL_GPIOD_AFRL              (0)
#define VAL_GPIOD_AFRH              (0)

/*
 * GPIOE setup:
 */
#define VAL_GPIOE_MODER             (0)
#define VAL_GPIOE_OTYPER            (0)
#define VAL_GPIOE_OSPEEDR           (0)
#define VAL_GPIOE_PUPDR             (0)
#define VAL_GPIOE_ODR               (0)
#define VAL_GPIOE_AFRL              (0)
#define VAL_GPIOE_AFRH              (0)

/*
 * GPIOF setup:
 *
 * PF0  - OSC_IN                    (input floating).
 * PF1  - OSC_OUT                   (input floating).
 * PF4  - NC
 */
#define VAL_GPIOF_MODER             (PIN_MODE_INPUT(GPIOF_OSC_IN) |         \
                                     PIN_MODE_INPUT(GPIOF_OSC_OUT) |        \
                                     PIN_MODE_INPUT(GPIOF_PIN4_NC))
#define VAL_GPIOF_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOF_OSC_IN) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_OSC_OUT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN4_NC))
#define VAL_GPIOF_OSPEEDR           (PIN_OSPEED_HIGH(GPIOF_OSC_IN) |        \
                                     PIN_OSPEED_HIGH(GPIOF_OSC_OUT) |       \
                                     PIN_OSPEED_HIGH(GPIOF_PIN4_NC))
#define VAL_GPIOF_PUPDR             (PIN_PUPDR_FLOATING(GPIOF_OSC_IN) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_OSC_OUT) |    \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN4_NC))
#define VAL_GPIOF_ODR               (PIN_ODR_HIGH(GPIOF_OSC_IN) |           \
                                     PIN_ODR_HIGH(GPIOF_OSC_OUT) |          \
                                     PIN_ODR_HIGH(GPIOF_PIN4_NC))
#define VAL_GPIOF_AFRL              (PIN_AFIO_AF(GPIOF_OSC_IN, 0U) |        \
                                     PIN_AFIO_AF(GPIOF_OSC_OUT, 0U))
#define VAL_GPIOF_AFRH              (0)

/*
 * GPIOG setup:
 */
#define VAL_GPIOG_MODER             (0)
#define VAL_GPIOG_OTYPER            (0)
#define VAL_GPIOG_OSPEEDR           (0)
#define VAL_GPIOG_PUPDR             (0)
#define VAL_GPIOG_ODR               (0)
#define VAL_GPIOG_AFRL              (0)
#define VAL_GPIOG_AFRH              (0)

/*
 * GPIOH setup:
 */
#define VAL_GPIOH_MODER             (0)
#define VAL_GPIOH_OTYPER            (0)
#define VAL_GPIOH_OSPEEDR           (0)
#define VAL_GPIOH_PUPDR             (0)
#define VAL_GPIOH_ODR               (0)
#define VAL_GPIOH_AFRL              (0)
#define VAL_GPIOH_AFRH              (0)

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* BOARD_H */
