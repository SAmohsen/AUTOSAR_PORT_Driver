 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for Port Module.
 *
 * Author:  sayed mohsen
 ******************************************************************************/

#include "Port.h"
#include "Dio_Regs.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Dio Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED ;
STATIC Port_ConfigChannel *port_PortChannels = NULL_PTR;

STATIC Port_PortType get_portID(Port_PinType pin){
	Port_PortType port_id ;
	if ((pin >= PORT_A_START) && (pin <= PORT_A_FINISH))
	{
		port_id = PORTA_ID;
	}
	else if ((pin >= PORT_B_START) && (pin <= PORT_B_FINISH))
	{
		port_id = PORTB_ID;
	}
	else if ((pin >= PORT_C_START) && (pin <= PORT_C_FINISH))
	{
		port_id = PORTC_ID;
	}
	else if ((pin >= PORT_D_START) && (pin <= PORT_D_FINISH))
	{
		port_id = PORTD_ID;

	}
	else
	{

	}

	return port_id;
}


STATIC Port_PinType get_pinID(Port_PinType pin){
	Port_PinType pin_id ;
	pin_id = (Port_PortType) pin% PINS_PER_PORT ;
	return pin_id;
}
/************************************************************************************
* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Port module.
************************************************************************************/
void Port_Init(const Port_ConfigType* ConfigPtr)
{
	Port_PortType *DDR_ptr;
	Port_PortType *port_ptr;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == ConfigPtr)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
		     PORT_E_PARAM_CONFIG);
	}
	else
#endif
	{
		port_PortChannels = ConfigPtr->port_channels;
		for (int itr = 0; itr < PORT_CONFIGURED_CHANNLES; itr++) {
			/*get port */
			switch (port_PortChannels[itr].port) {
			case PORTA_ID: DDR_ptr  = &DDRA_REG;
						   port_ptr = &PORTA_REG;
			break;
			case PORTB_ID: DDR_ptr  = &DDRB_REG;
						   port_ptr = &PORTB_REG;
			break;
			case PORTC_ID: DDR_ptr  = &DDRC_REG;
						   port_ptr = &PORTC_REG;
			break;
			case PORTD_ID: DDR_ptr  = &DDRD_REG;
						   port_ptr = &PORTD_REG;
			break;
			}
			if(PORT_PIN_IN==port_PortChannels[itr].direction)
			{
				CLEAR_BIT(*DDR_ptr,port_PortChannels[itr].pin_num);
				if (Disable_Pull_up == port_PortChannels[itr].pin_in_mode)
				{
					CLEAR_BIT(*port_ptr, port_PortChannels[itr].pin_num);

				}
				else if(Enable_Pull_up== port_PortChannels[itr].pin_in_mode)
				{
					SET_BIT(*port_ptr, port_PortChannels[itr].pin_num);
				}
				else
				{

				}

			}
			else if(PORT_PIN_OUT==port_PortChannels[itr].direction)
			{
				SET_BIT(*DDR_ptr,port_PortChannels[itr].pin_num);
				if (initial_Low==port_PortChannels[itr].pin_out_mode)
				{
					CLEAR_BIT(*port_ptr,port_PortChannels[itr].pin_num);

				}
				else if (initial_High==port_PortChannels[itr].pin_out_mode)
				{
					SET_BIT(*port_ptr,port_PortChannels[itr].pin_num);
				}
				else
				{

				}

			}
			else
			{

			}

		}//end For Loop
		Port_Status = PORT_INITIALIZED;
	}
}

void Port_RefreshPortDirection(void)
{

}

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction) {
	Port_PortType *DDR_ptr;
	Port_PortType local_port;
	Port_PinType local_pin;

#if (PORT_DEV_ERROR_DETECT == STD_ON)
	if (Port_Status == PORT_NOT_INITIALIZED)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,PORT_E_UNINIT);
	}
	else
#endif
	{
		local_port = get_portID(Pin);
		local_pin = get_pinID(Pin);
		switch (local_port) {
		case PORTA_ID:DDR_ptr = &DDRA_REG;
		break;
		case PORTB_ID:DDR_ptr = &DDRB_REG;
		break;
		case PORTC_ID:DDR_ptr = &DDRC_REG;
		break;
		case PORTD_ID:DDR_ptr = &DDRD_REG;
		break;
		}

		if (PORT_PIN_OUT == Direction)
		{
			SET_BIT(*DDR_ptr, local_pin);

		}
		else if (PORT_PIN_IN == Direction)
		{
			CLEAR_BIT(*DDR_ptr, local_pin);

		}
		else
		{

		}
	}

}
#endif

#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if(NULL_PTR == versioninfo)
	{
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
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

/*Sets the port pin mode*/
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{

}

