/******************************************************************************
 *
 * Module: Port
 *
 * File Name: port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Kerolos Sameh
 ******************************************************************************/

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION (1U)
#define PORT_PBCFG_SW_MINOR_VERSION (0U)
#define PORT_PBCFG_SW_PATCH_VERSION (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION (3U)

#include "Port.h"

/* Check compatibility of Port.h AUTOSAR version with
* Port_PBcfg.c AUTOSAR version.
*/
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
        || (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
        || (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Port.h does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
        || (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
        || (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error "The SW version of PBcfg.c does not match the expected version"
#endif


/* PB structure used with Port_Init API */
const Port_ConfigType port_configuration = {
                                            PORTA_ID , PORTA_PIN0_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTA_ID , PORTA_PIN1_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTA_ID , PORTA_PIN2_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTA_ID , PORTA_PIN3_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTA_ID , PORTA_PIN4_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTA_ID , PORTA_PIN5_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTA_ID , PORTA_PIN6_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTA_ID , PORTA_PIN7_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,

                                            PORTB_ID , PORTB_PIN0_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTB_ID , PORTB_PIN1_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTB_ID , PORTB_PIN2_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTB_ID , PORTB_PIN3_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTB_ID , PORTB_PIN4_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTB_ID , PORTB_PIN5_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTB_ID , PORTB_PIN6_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTB_ID , PORTB_PIN7_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,

                                            PORTC_ID , PORTC_PIN0_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTC_ID , PORTC_PIN1_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTC_ID , PORTC_PIN2_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTC_ID , PORTC_PIN3_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTC_ID , PORTC_PIN4_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTC_ID , PORTC_PIN5_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTC_ID , PORTC_PIN6_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTC_ID , PORTC_PIN7_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,

                                            PORTD_ID , PORTD_PIN0_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTD_ID , PORTD_PIN1_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTD_ID , PORTD_PIN2_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTD_ID , PORTD_PIN3_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTD_ID , PORTD_PIN4_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTD_ID , PORTD_PIN5_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTD_ID , PORTD_PIN6_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTD_ID , PORTD_PIN7_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,

                                            PORTE_ID , PORTE_PIN0_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTE_ID , PORTE_PIN1_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTE_ID , PORTE_PIN2_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTE_ID , PORTE_PIN3_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTE_ID , PORTE_PIN4_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTE_ID , PORTE_PIN5_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,

                                            PORTF_ID , PORTF_PIN0_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTF_ID , PORTF_PIN1_ID , PORT_PIN_OUT, RES_OFF, PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTF_ID , PORTF_PIN2_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTF_ID , PORTF_PIN3_ID , PORT_PIN_IN , RES_OFF , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG ,
                                            PORTF_ID , PORTF_PIN4_ID , PORT_PIN_IN , PULL_UP_RES , PORT_PIN_LEVEL_LOW , PORT_PIN_MODE_DIO , PORT_PIN_DIR_UNCHANG , PORT_PIN_MODE_UNCHANG
};




