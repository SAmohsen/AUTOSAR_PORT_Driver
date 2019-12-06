/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for Port Module.
 *
 * Author:  sayed mohsen
 ******************************************************************************/

#import "Port.h"

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif

/* PB structure used with Port_Init API */
const Port_ConfigType Port_Configuration =
                                   {
		.port_channels[portConf_INT0_CHANNEL_ID_INDX].pin_num =portConf_INT0_CHANNEL_CHANNEL_NUMBER,
		.port_channels[portConf_INT0_CHANNEL_ID_INDX].port =portConf_INT0_CHANNEL_PORT_NUMBER,
		.port_channels[portConf_INT0_CHANNEL_ID_INDX].direction =portConf_INT0_CHANNEL_CHANNEL_DIRECTION,
		.port_channels[portConf_INT0_CHANNEL_ID_INDX].pin_out_mode =portConf_INT0_CHANNEL_INPUT_PIN_MODE,

	/*	  .port_channels[portConf_LED_CHANNEL_ID_INDX].pin_num = portConf_LED_CHANNEL_CHANNEL_NUMBER ,
		  .port_channels[portConf_LED_CHANNEL_ID_INDX].port = portConf_LED_CHANNEL_PORT_NUMBER,
		  .port_channels[portConf_LED_CHANNEL_ID_INDX].direction = portConf_LED_CHANNEL_CHANNEL_DIRECTION,
		  .port_channels[portConf_LED_CHANNEL_ID_INDX].pin_out_mode = portConf_LED_CHANNEL_INPUT_PIN_MODE,
*/
		  .port_channels[portConf_ADC_CHANNEL_ID_INDX].pin_num = portConf_ADC_CHANNEL_CHANNEL_NUMBER ,
		  .port_channels[portConf_ADC_CHANNEL_ID_INDX].port = portConf_ADC_CHANNEL_PORT_NUMBER,
		  .port_channels[portConf_ADC_CHANNEL_ID_INDX].direction = portConf_ADC_CHANNEL_CHANNEL_DIRECTION,
		  .port_channels[portConf_ADC_CHANNEL_ID_INDX].pin_out_mode = portConf_ADC_CHANNEL_INPUT_PIN_MODE,

								   };
