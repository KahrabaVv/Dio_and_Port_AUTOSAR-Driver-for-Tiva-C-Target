/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Kerolos Sameh
 ******************************************************************************/

#include "port.h"
#include "port_Regs.h"
#include "Std_Types.h"

#include "Det.h"
/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
        || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
        || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif



STATIC const Port_ConfigChannel * Port_PortChannels = NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;



/************************************************************************************
 * Service Name: Port_Init
 * Service ID[hex]: 0x00
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): confifPtr - Pointer to post-build configuration data
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initializes the Port Driver module.
 ************************************************************************************/
void Port_Init(
        const Port_ConfigType* ConfigPtr
)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* check if the input configuration pointer is not a NULL_PTR */
    if (NULL_PTR == ConfigPtr)
    {
        Det_ReportError(PORT_MODULE_ID,
                        PORT_INSTANCE_ID,
                        PORT_INIT_SID,
                        PORT_E_PARAM_CONFIG);
    }
    else
    {
#endif

        Port_Status = PORT_INITIALIZED;
        Port_PortChannels = ConfigPtr->Channels;
        uint8 channel_index;
        for(channel_index= ZERO; channel_index<PORT_CONFIGURED_CHANNLES; ++channel_index)
        {
            volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */

            switch(Port_PortChannels[channel_index].port_num)
            {
            case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
            break;
            case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
            break;
            case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
            break;
            case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
            break;
            case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
            break;
            case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
            break;
            }

            SYSCTL_REGCGC2_REG |= (1<<Port_PortChannels[channel_index].port_num);


            if( ((Port_PortChannels[channel_index].port_num == PORTD_ID) && (Port_PortChannels[channel_index].pin_num == PORTD_PIN7_ID)) || ((Port_PortChannels[channel_index].port_num == PORTF_ID) && (Port_PortChannels[channel_index].pin_num == PORTF_PIN0_ID)) ) /* PD7 or PF0 */
            {
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = GPIO_COMMIT_UNLOCK_NUMBER;                     /* Unlock the GPIOCR register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
            }
            else if( (Port_PortChannels[channel_index].port_num == PORTC_ID) && (Port_PortChannels[channel_index].port_num <= PORTC_PIN3_ID) ) /* PC0 to PC3 */
            {
                /* Do Nothing ...  this is the JTAG pins */
            }
            else
            {
                /* Do Nothing ... No need to unlock the commit register for this pin */
            }

            /*********************************************Check Mode**************************************************/
            if(Port_PortChannels[channel_index].mode == PORT_PIN_MODE_DIO)
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(PMCx_BITS_MASK << (Port_PortChannels[channel_index].pin_num * 4));     /* Clear the PMCx bits for this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */

            }

            /***********************************************************************************************/
            else if(Port_PortChannels[channel_index].mode == PORT_PIN_MODE_ADC)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);      /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(PMCx_BITS_MASK << (Port_PortChannels[channel_index].pin_num * 4));     /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_ADC << (Port_PortChannels[channel_index].pin_num * 4));             /* Set the PMCx bits for this pin depending on the mode */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);         /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
            }
            /***********************************************************************************************/
            else if(Port_PortChannels[channel_index].mode == PORT_PIN_MODE_UART)
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);             /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(PMCx_BITS_MASK << (Port_PortChannels[channel_index].pin_num * 4));     /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_UART << (Port_PortChannels[channel_index].pin_num * 4));             /* Set the PMCx bits for this pin depending on the mode */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */

            }
            /*********************************************Check Mode**************************************************/
            else if(Port_PortChannels[channel_index].mode == PORT_PIN_MODE_SSI)
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);             /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(PMCx_BITS_MASK << (Port_PortChannels[channel_index].pin_num * 4));     /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_SSI << (Port_PortChannels[channel_index].pin_num * 4));             /* Set the PMCx bits for this pin depending on the mode */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            }
            /*********************************************Check Mode**************************************************/
            else if(Port_PortChannels[channel_index].mode == PORT_PIN_MODE_I2C)
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);             /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(PMCx_BITS_MASK << (Port_PortChannels[channel_index].pin_num * 4));     /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_I2C << (Port_PortChannels[channel_index].pin_num * 4));             /* Set the PMCx bits for this pin depending on the mode */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */

            }
            /*********************************************Check Mode**************************************************/
            else if(Port_PortChannels[channel_index].mode == PORT_PIN_MODE_CAN)
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);             /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(PMCx_BITS_MASK << (Port_PortChannels[channel_index].pin_num * 4));     /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_CAN << (Port_PortChannels[channel_index].pin_num * 4));             /* Set the PMCx bits for this pin depending on the mode */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            }
            /*********************************************Check Mode**************************************************/
            else if(Port_PortChannels[channel_index].mode == PORT_PIN_MODE_PWM0)
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);             /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(PMCx_BITS_MASK << (Port_PortChannels[channel_index].pin_num * 4));     /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_PWM0 << (Port_PortChannels[channel_index].pin_num * 4));             /* Set the PMCx bits for this pin depending on the mode */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            }
            /*********************************************Check Mode**************************************************/
            else if(Port_PortChannels[channel_index].mode == PORT_PIN_MODE_PWM1)
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);             /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(PMCx_BITS_MASK << (Port_PortChannels[channel_index].pin_num * 4));     /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_PWM1 << (Port_PortChannels[channel_index].pin_num * 4));             /* Set the PMCx bits for this pin depending on the mode */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            }
            /**********************************************************************************************/
            else
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(PMCx_BITS_MASK << (Port_PortChannels[channel_index].pin_num * 4));     /* Clear the PMCx bits for this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            }

            /********************************************Direction,initial_value,resistor**************************************************/

            if(Port_PortChannels[channel_index].direction == PORT_PIN_OUT)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

                if(Port_PortChannels[channel_index].initial_value == PORT_PIN_LEVEL_HIGH)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                }
                else
                {

                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                }
            }
            else if(Port_PortChannels[channel_index].direction == PORT_PIN_IN)
            {

                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

                if(Port_PortChannels[channel_index].resistor == PULL_UP_RES)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                }
                else if(Port_PortChannels[channel_index].resistor == PULL_DOWN_RES)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                }
                else
                {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) ,Port_PortChannels[channel_index].pin_num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                }
            }
            else
            {
                /* Do Nothing */
            }
        }
    }
}


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
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(
        Port_PinType Pin,
        Port_PinDirectionType Direction
)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    if(Pin > MAX_PIN_NO_PORT)
    {
        Det_ReportError(PORT_MODULE_ID,
                        PORT_INSTANCE_ID,
                        PORT_INIT_SID,
                        PORT_E_PARAM_PIN);
    }
    else if(Port_Status == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID,
                        PORT_INSTANCE_ID,
                        PORT_INIT_SID,
                        PORT_E_UNINIT);
    }
    else if(Port_PortChannels[Pin].direction_changble == PORT_PIN_DIR_UNCHANG)
    {
        Det_ReportError(PORT_MODULE_ID,
                        PORT_INSTANCE_ID,
                        PORT_INIT_SID,
                        PORT_E_DIRECTION_UNCHANG);
    }
    else
    {
#endif

        volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
        /*
         * Switch case to determine the Base address of the Port from the attribute port_num in the struct ConfigPtr
         */
        switch(Port_PortChannels[Pin].port_num)
        {
        case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
        break;
        case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
        break;
        case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
        break;
        case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
        break;
        case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
        break;
        case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
        break;
        }

        if( ((Port_PortChannels[Pin].port_num == PORTD_ID) && (Port_PortChannels[Pin].pin_num == PORTD_PIN7_ID)) || ((Port_PortChannels[Pin].port_num == PORTF_ID) && (Port_PortChannels[Pin].pin_num == PORTF_PIN0_ID)) ) /* PD7 or PF0 */
        {
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = GPIO_COMMIT_UNLOCK_NUMBER;                     /* Unlock the GPIOCR register */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , Port_PortChannels[Pin].pin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
        }
        else if( (Port_PortChannels[Pin].port_num == PORTC_ID) && (Port_PortChannels[Pin].pin_num <= PORTC_PIN3_ID) ) /* PC0 to PC3 */
        {
            return;
            /* Do Nothing ...  this is the JTAG pins */
        }
        else
        {

        }

        if(PORT_PIN_IN == Direction)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_PortChannels[Pin].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

        }
        else if(PORT_PIN_OUT == Direction)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_PortChannels[Pin].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
        }
        else
        {

        }
    }
}
#endif

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
)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Port module isn’t initialized */
    if(Port_Status == PORT_NOT_INITIALIZED){
        Det_ReportError(PORT_MODULE_ID,
                        PORT_INSTANCE_ID,
                        PORT_REFRESH_PORT_DIRECTION_SID,
                        PORT_E_UNINIT);
    }
#endif

    uint8 channel_index;
    for(channel_index= ZERO; channel_index<PORT_CONFIGURED_CHANNLES; channel_index++)
    {
        volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */

        switch(Port_PortChannels[channel_index].port_num)

        {
        case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
        break;
        case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
        break;
        case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
        break;
        case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
        break;
        case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
        break;
        case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
        break;
        }
        if(Port_PortChannels[channel_index].direction == PORT_PIN_OUT)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

        }
        else if(Port_PortChannels[channel_index].direction == PORT_PIN_IN)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_PortChannels[channel_index].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
        }
    }
}

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
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(
        Std_VersionInfoType* versioninfo
)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if input pointer is not Null pointer */
    if(NULL_PTR == versioninfo)
    {
        /* Report to DET  */
        Det_ReportError(PORT_MODULE_ID,
                        PORT_INSTANCE_ID,
                        PORT_GET_VERSION_INFO_SID,
                        PORT_E_PARAM_POINTER);
    }
    else
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Copy the vendor Id */
        versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
        /* Copy the module Id */
        versioninfo->moduleID = (uint16)PORT_MODULE_ID;
        /* Copy Software Major Version */
        versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
        /* Copy Software Minor Version */
        versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
        /* Copy Software Patch Version */
        versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;

    }
}
#endif


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
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(
        Port_PinType Pin,
        Port_PinModeType Mode )
{

#if (PORT_DEV_ERROR_DETECT == STD_ON)
    if(Pin > MAX_PIN_NO_PORT)
    {
        Det_ReportError(PORT_MODULE_ID,
                        PORT_INSTANCE_ID,
                        PORT_INIT_SID,
                        PORT_E_PARAM_PIN);
    }
    else if(Port_Status == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID,
                        PORT_INSTANCE_ID,
                        PORT_INIT_SID,
                        PORT_E_UNINIT);
    }
    else if(Port_PortChannels[Pin].mode_changble == PORT_PIN_MODE_UNCHANG)
    {
        Det_ReportError(PORT_MODULE_ID,
                        PORT_INSTANCE_ID,
                        PORT_INIT_SID,
                        PORT_E_MODE_UNCHANG);
    }
    else
    {
#endif

        volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */

        switch(Port_PortChannels[Pin].port_num)
        {
        case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
        break;
        case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
        break;
        case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
        break;
        case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
        break;
        case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
        break;
        case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
        break;
        }

        if( ((Port_PortChannels[Pin].port_num == PORTD_ID) && (Port_PortChannels[Pin].pin_num == PORTD_PIN7_ID)) || ((Port_PortChannels[Pin].port_num == PORTF_ID) && (Port_PortChannels[Pin].pin_num == PORTF_PIN0_ID)) ) /* PD7 or PF0 */
        {
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = GPIO_COMMIT_UNLOCK_NUMBER;                     /* Unlock the GPIOCR register */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , Port_PortChannels[Pin].pin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
        }
        else if( (Port_PortChannels[Pin].port_num == PORTC_ID) && (Port_PortChannels[Pin].port_num <= PORTC_PIN3_ID) ) /* PC0 to PC3 */
        {
            /* Do Nothing ...  this is the JTAG pins */
        }
        else
        {
            /* Do Nothing ... No need to unlock the commit register for this pin */
        }

        if(Port_PortChannels[Pin].mode == PORT_PIN_MODE_DIO)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[Pin].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(PMCx_BITS_MASK << (Port_PortChannels[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[Pin].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */

        }


        else if(Port_PortChannels[Pin].mode == PORT_PIN_MODE_ADC)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[Pin].pin_num);      /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[Pin].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(PMCx_BITS_MASK << (Port_PortChannels[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (Mode << (Port_PortChannels[Pin].pin_num * 4));             /* Set the PMCx bits for this pin depending on the mode */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[Pin].pin_num);         /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
        }
        else if(Port_PortChannels[Pin].mode == PORT_PIN_MODE_UART)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[Pin].pin_num);             /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(PMCx_BITS_MASK << (Port_PortChannels[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (Mode << (Port_PortChannels[Pin].pin_num * 4));             /* Set the PMCx bits for this pin depending on the mode */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[Pin].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */

        }
        else if(Port_PortChannels[Pin].mode == PORT_PIN_MODE_SSI)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[Pin].pin_num);             /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(PMCx_BITS_MASK << (Port_PortChannels[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (Mode << (Port_PortChannels[Pin].pin_num * 4));             /* Set the PMCx bits for this pin depending on the mode */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[Pin].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
        }
        else if(Port_PortChannels[Pin].mode == PORT_PIN_MODE_I2C)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[Pin].pin_num);             /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(PMCx_BITS_MASK << (Port_PortChannels[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (Mode << (Port_PortChannels[Pin].pin_num * 4));             /* Set the PMCx bits for this pin depending on the mode */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[Pin].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */

        }
        else if(Port_PortChannels[Pin].mode == PORT_PIN_MODE_CAN)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[Pin].pin_num);             /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(PMCx_BITS_MASK << (Port_PortChannels[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (Mode << (Port_PortChannels[Pin].pin_num * 4));             /* Set the PMCx bits for this pin depending on the mode */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[Pin].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
        }
        else if(Port_PortChannels[Pin].mode == PORT_PIN_MODE_PWM0)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[Pin].pin_num);             /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(PMCx_BITS_MASK << (Port_PortChannels[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (Mode << (Port_PortChannels[Pin].pin_num * 4));             /* Set the PMCx bits for this pin depending on the mode */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[Pin].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
        }
        else if(Port_PortChannels[Pin].mode == PORT_PIN_MODE_PWM1)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[Pin].pin_num);             /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(PMCx_BITS_MASK << (Port_PortChannels[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (Mode << (Port_PortChannels[Pin].pin_num * 4));             /* Set the PMCx bits for this pin depending on the mode */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[Pin].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
        }
        else
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[Pin].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(PMCx_BITS_MASK << (Port_PortChannels[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[Pin].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
        }

    }
}
#endif
