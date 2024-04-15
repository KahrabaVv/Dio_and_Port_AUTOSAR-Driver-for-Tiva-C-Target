/******************************************************************************
 *
 * Module: Port
 *
 * File Name: port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Kerolos Sameh
 ******************************************************************************/

#ifndef PORT_CFG_H_
#define PORT_CFG_H_

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION (1U)
#define PORT_CFG_SW_MINOR_VERSION (0U)
#define PORT_CFG_SW_PATCH_VERSION (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT (STD_ON)


/* Number of the configured Port Channels */
#define PORT_CONFIGURED_CHANNLES              (43U)

#define ZERO 0

/* Precompile option for setting Pin direction API */
#define PORT_SET_PIN_DIRECTION_API            (STD_ON)

/* Precompile option to set pin mode API */
#define PORT_SET_PIN_MODE_API                 (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API (STD_ON)

#define PMCx_BITS_MASK                        0x0000000F

#define NUMBER_OF_CONFIGURED_MODES            (11u)

#define MAX_PIN_NO_PORT                    (7u)
/* Ports Number */
#define PORTA_ID (0u)
#define PORTB_ID (1u)
#define PORTC_ID (2u)
#define PORTD_ID (3u)
#define PORTE_ID (4u)
#define PORTF_ID (5u)

/* Pins Number */
#define PORTA_PIN0_ID  (0u)
#define PORTA_PIN1_ID  (1u)
#define PORTA_PIN2_ID  (2u)
#define PORTA_PIN3_ID  (3u)
#define PORTA_PIN4_ID  (4u)
#define PORTA_PIN5_ID  (5u)
#define PORTA_PIN6_ID  (6u)
#define PORTA_PIN7_ID  (7u)

#define PORTB_PIN0_ID  (0u)
#define PORTB_PIN1_ID  (1u)
#define PORTB_PIN2_ID  (2u)
#define PORTB_PIN3_ID  (3u)
#define PORTB_PIN4_ID  (4u)
#define PORTB_PIN5_ID  (5u)
#define PORTB_PIN6_ID  (6u)
#define PORTB_PIN7_ID  (7u)

#define PORTC_PIN0_ID  (0u)
#define PORTC_PIN1_ID  (1u)
#define PORTC_PIN2_ID  (2u)
#define PORTC_PIN3_ID  (3u)
#define PORTC_PIN4_ID  (4u)
#define PORTC_PIN5_ID  (5u)
#define PORTC_PIN6_ID  (6u)
#define PORTC_PIN7_ID  (7u)

#define PORTD_PIN0_ID  (0u)
#define PORTD_PIN1_ID  (1u)
#define PORTD_PIN2_ID  (2u)
#define PORTD_PIN3_ID  (3u)
#define PORTD_PIN4_ID  (4u)
#define PORTD_PIN5_ID  (5u)
#define PORTD_PIN6_ID  (6u)
#define PORTD_PIN7_ID  (7u)

#define PORTE_PIN0_ID  (0u)
#define PORTE_PIN1_ID  (1u)
#define PORTE_PIN2_ID  (2u)
#define PORTE_PIN3_ID  (3u)
#define PORTE_PIN4_ID  (4u)
#define PORTE_PIN5_ID  (5u)

#define PORTF_PIN0_ID  (0u)
#define PORTF_PIN1_ID  (1u)
#define PORTF_PIN2_ID  (2u)
#define PORTF_PIN3_ID  (3u)
#define PORTF_PIN4_ID  (4u)



#define  PORT_PIN_MODE_ADC   (0U)
#define  PORT_PIN_MODE_UART  (1U)
#define  PORT_PIN_MODE_SSI   (2U)
#define  PORT_PIN_MODE_UART1 (2U)
#define  PORT_PIN_MODE_I2C   (3U)
#define  PORT_PIN_MODE_CAN0  (3U)
#define  PORT_PIN_MODE_PWM0  (4U)
#define  PORT_PIN_MODE_PWM1  (5U)
#define  PORT_PIN_MODE_QEI   (6U)
#define  PORT_PIN_MODE_GPT   (7U)
#define  PORT_PIN_MODE_CAN   (8U)
#define  PORT_PIN_MODE_USB   (8U)
#define  PORT_PIN_NOT_ACTIVE (9U)
#define  PORT_PIN_MODE_DIO   (10U)



#endif /* PORT_CFG_H_ */
