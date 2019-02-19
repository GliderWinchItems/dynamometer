/******************************************************************************
* File Name          : adcTask.h
* Date First Issued  : 02/01/2019
* Description        : Handle ADC w DMA using FreeRTOS/ST HAL within a task
*******************************************************************************/

#ifndef __ADCTASKLC
#define __ADCTASKLC

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "stm32f4xx_hal.h"

/* Augment 'MX adc control block for dma buffering and summing */
struct ADCDMATSKBLK
{
	struct ADCDMATSKBLK* pnext;
	ADC_HandleTypeDef* phadc; // Pointer to 'MX adc control block
	uint32_t  notebit1; // Notification bit for dma half complete interrupt
	uint32_t  notebit2; // Notification bit for dma complete interrupt
	uint32_t* pnoteval; // Pointer to notification word
	uint16_t* pdma1;    // Pointer to first half of dma buffer
	uint16_t* pdma2;    // Pointer to second half of dma buffer
	osThreadId adctaskHandle;
	uint64_t* psum;     // Pointer summed 1/2 dma buffer
	uint16_t  dmact;    // Number of sequences in 1/2 dma buffer
};

/* *************************************************************************/
struct ADCDMATSKBLK* adctask_init(ADC_HandleTypeDef* phadc,\
	uint32_t  notebit1,\
	uint32_t  notebit2,\
	uint32_t* pnoteval,\
	uint16_t  dmact);
/*	@brief	: Setup circular line buffers this uart
 * @param	: phadc = pointer to ADC control block
 * @param	: notebit1 = unique bit for notification @ 1/2 dma buffer
 * @param	: notebit2 = unique bit for notification @ end dma buffer
 * @param	: pnoteval = pointer to word receiving notification word from OS
 * @param	: dmact = number of sequences in 1/2 of circular DMA buffer
 * @return	: 
 * *************************************************************************/
uint64_t* adctask_sum(struct ADCDMATSKBLK* pblk);
/*	@brief	: sum 1/2 of the dma buffer for each ADC in the sequence
 * @param	: pblk = pointer to our control block with all the info
 * *************************************************************************/

#endif

