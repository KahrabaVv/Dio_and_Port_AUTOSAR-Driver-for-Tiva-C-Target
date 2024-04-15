 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Kerolos Sameh
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H
#include "Common_Macros.h"
#include "Std_Types.h"
#include "Port_Cfg.h"
/* Id for the company in the AUTOSAR */
#define PORT_VENDOR_ID    (1000U)

/* Port Module Id */
#define PORT_MODULE_ID    (120U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)


/* AUTOSAR checking between Std Types and PORT Modules */

#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* AUTOSAR Version checking between PORT_Cfg.h and PORT.h files */

#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

   /* Software Version checking between PORT_Cfg.h and PORT.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif





#define GPIO_COMMIT_UNLOCK_NUMBER 0x4C4F434B

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for Port Init */
#define PORT_INIT_SID                      (uint8)0x00

/* Service ID for Port Set Pin Direction */
#define PORT_SET_PIN_DIRECTION_SID         (uint8)0x01

/* Service ID for Refresh Port Direction*/
#define PORT_REFRESH_PORT_DIRECTION_SID    (uint8)0x02

/* Service ID for Port Get Version Info */
#define PORT_GET_VERSION_INFO_SID          (uint8)0x03

/* Service ID for Port Set Pin Mode */
#define PORT_SET_PIN_MODE_SID              (uint8)0x04
/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
#define PORT_E_PARAM_PIN                   (uint8)0x0A

#define PORT_E_DIRECTION_UNCHANG           (uint8)0x0B

#define PORT_E_PARAM_CONFIG                (uint8)0x0C

#define PORT_E_PARAM_INVALID_MODE          (uint8)0x0D

#define PORT_E_MODE_UNCHANG                (uint8)0x0E

#define PORT_E_UNINIT                      (uint8)0x0F

#define PORT_E_PARAM_POINTER               (uint8)0x10
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
typedef uint8 Port_PortType;

typedef uint8 Port_PinType ;

typedef uint8 Port_PinModeType;

/* Description: Enum to hold initialization state for Port */
typedef enum{
    PORT_NOT_INITIALIZED,PORT_INITIALIZED
}Port_Intialization_State;


/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    RES_OFF,PULL_UP_RES,PULL_DOWN_RES
}Port_PinInternalResistor;

/* Description: Enum to hold PIN direction */
typedef enum
{
  PORT_PIN_IN,PORT_PIN_OUT
} Port_PinDirectionType;

/* Description: Enum to hold changeability of mode for PIN */
typedef enum
{
  PORT_PIN_MODE_UNCHANG,PORT_PIN_MODE_CHANG
} Port_PinModeChangeable;

/* Description: Enum to hold changeability of direction for PIN */

typedef enum
{
  PORT_PIN_DIR_UNCHANG,PORT_PIN_DIR_CHANG
} Port_PinDirectionChangeable;

/* Description: Enum to hold initial value for PIN */
typedef enum
{
    PORT_PIN_LEVEL_LOW , PORT_PIN_LEVEL_HIGH
}Port_PinInitialValue;


/* Description: Structure to configure each individual PIN:
 *  1. PORT: The port to which the pin belongs, ranging from 0 to 5.
 *  2. Pin Number: The number of the pin within the PORT.
 *  3. Pin Direction: Specifies whether the pin is set as INPUT or OUTPUT.
 *  4. Internal Resistor: Options include Disable, Pull up, or Pull down.
 *  5. Initial Value: Can be either PORT_PIN_LEVEL_LOW or PORT_PIN_LEVEL_HIGH.
 *  6. Pin Mode: Ranges from PORT_PIN_MODE_ADC to PORT_PIN_MODE_DIO.
 *  7. Direction Changeable: Indicates if the pin direction can be changed, with options PORT_PIN_DIRECTION_UNCHANGEABLE or PORT_PIN_DIRECTION_CHANGEABLE.
 *  8. Mode Changeable: Specifies if the pin mode can be changed, with options PORT_PIN_MODE_UNCHANGEABLE or PORT_PIN_MODE_CHANGEABLE.
 */

typedef struct 
{
    Port_PortType port_num;
    Port_PinType pin_num;
    Port_PinDirectionType direction;
    Port_PinInternalResistor resistor;
    Port_PinInitialValue initial_value;
    Port_PinModeType mode;
    Port_PinDirectionChangeable direction_changble;
    Port_PinModeChangeable mode_changble;
}Port_ConfigChannel;


typedef struct{
    Port_ConfigChannel Channels[PORT_CONFIGURED_CHANNLES];
}Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/************************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: Non-reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: This function initializes the Port Driver module.
*              - Configures the pins as Digital GPIO pins
*              - Sets up the direction of the GPIO pins
*              - Configures the internal resistor for input pins
*              - Sets up the initial value for pins
************************************************************************************/

void Port_Init(
 const Port_ConfigType* ConfigPtr
) ;

/************************************************************************************
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin  - Port Pin ID number.
*                  Direction - Port Pin Direction.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction.
************************************************************************************/
void Port_SetPinDirection(
 Port_PinType Pin,
 Port_PinDirectionType Direction
) ;

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction.
************************************************************************************/
void Port_RefreshPortDirection(
 void
) ;

/************************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo - Pointer to where to store the version information of this module.
* Return value: None
* Description: Returns the version information of this module.
************************************************************************************/
void Port_GetVersionInfo(
 Std_VersionInfoType* versioninfo
) ;

/************************************************************************************
* Service Name: Port_SetPinMode
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin  - Port Pin ID number.
*                  Mode - New Port Pin mode to be set on port pin.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode.
************************************************************************************/
void Port_SetPinMode(
 Port_PinType Pin,
 Port_PinModeType Mode
) ;

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Port and other modules */
extern const Port_ConfigType port_configuration;

#endif /* PORT_H */
