#include <stdint.h>
#ifndef __REGISTERS_H
#define __REGISTERS_H

//SETUP BUSES
#define BUS_PERIPH_BASE             (0x40000000UL) //Peripheral base starting register

#define BUS_AHB1_OFFSET             (0x00020000UL) //AHB1 Offset
#define BUS_AHB1_BASE               (BUS_PERIPH_BASE+BUS_AHB1_OFFSET)

#define BUS_APB1_OFFSET             (0x00000000UL) //APB1 Offset
#define BUS_APB1_BASE               (BUS_PERIPH_BASE+BUS_APB1_OFFSET)

// Generate a struct for RCC Registers to make things preeeeeetty
typedef struct {
    volatile uint32_t CR;           //0x00
    volatile uint32_t PLLCFGR;      //0x04
    volatile uint32_t CFGR;         //0x08
    volatile uint32_t CIR;          //0x0C
    volatile uint32_t AHB1RSTR;     //0x10
    volatile uint32_t AHB2RSTR;     //0x14
    volatile uint32_t AHB3RSTR;     //0x18
    volatile uint32_t reserved0;    //0x1C
    volatile uint32_t APB1RSTR;     //0X20
    volatile uint32_t APB2RSTR;     //0x24
    volatile uint32_t reserved1;    //0x28
    volatile uint32_t reserved2;    //0x2C
    volatile uint32_t AHB1ENR;      //0x30
    volatile uint32_t AHB2ENR;      //0x34
    volatile uint32_t AHB3ENR;      //0x38
    volatile uint32_t reserved3;    //0x3C
    volatile uint32_t APB1ENR;      //0x40
    volatile uint32_t APB2ENR;      //0x44
    volatile uint32_t reserved4;    //0x48
    volatile uint32_t reserved5;    //0x4C
    volatile uint32_t AHB1LPENR;    //0x50
    volatile uint32_t AHB2LPENR;    //0x54
    volatile uint32_t AHB3LPENR;    //0x58
    volatile uint32_t reserved6;    //0x5C
    volatile uint32_t APB1LPENR;    //0x60
    volatile uint32_t APB2LPENR;    //0x64
    volatile uint32_t reserved7;    //0x68
    volatile uint32_t reserved8;    //0x6C
    volatile uint32_t BDCR;         //0x70
    volatile uint32_t CSR;          //0x74
    volatile uint32_t reserved9;    //0x78
    volatile uint32_t reserved10;   //0x7C
    volatile uint32_t SSCGR;        //0x80
    volatile uint32_t PLLI2SCFGR;   //0x84
    volatile uint32_t PLLSAICFGR;   //0x88
    volatile uint32_t DCKCFGR;      //0x8C
    volatile uint32_t CKGATENR;     //0x90
    volatile uint32_t DCKCFGR2;     //0x94
}RCC_DataType;

// CLOCK ACCESS AHB1
#define PERIPH_RCC_OFFSET           (0x00003800UL) //RCC offset
#define AHB1_RCC_BASE               (BUS_AHB1_BASE+PERIPH_RCC_OFFSET)
#define RCC ((RCC_DataType*) AHB1_RCC_BASE)

// Generate a struct for GPIO Registers to make things preeeeeetty
typedef struct {
    volatile uint32_t MODER;    //0x00
    volatile uint32_t OTYPER;   //0x04
    volatile uint32_t OSPEEDR;  //0x08
    volatile uint32_t PUPDR;    //0x0C
    volatile uint32_t IDR;      //0x10
    volatile uint32_t ODR;      //0x14
    volatile uint32_t BSRR;     //0x18
    volatile uint32_t LCKR;     //0x1C
    volatile uint32_t AFRL;     //0x20
    volatile uint32_t AFRH;     //0x24
}GPIO_DataType;

//CONFIGURE GPIOA
#define PERIPH_GPIOA_OFFSET         (0x00000000UL) //GPIOA offset
#define AHB1_GPIOA_BASE             (BUS_AHB1_BASE+PERIPH_GPIOA_OFFSET)
#define GPIOA ((GPIO_DataType*) AHB1_GPIOA_BASE)

// Generate a struct for TIM2-5 Registers to make things preeeeeetty
typedef struct {
    volatile uint32_t CR1;          //0x00
    volatile uint32_t CR2;          //0x04
    volatile uint32_t SMCR;         //0x08
    volatile uint32_t DIER;         //0x0C
    volatile uint32_t SR;           //0x10
    volatile uint32_t EGR;          //0x14
    volatile uint32_t CCMR1;        //0x18
    volatile uint32_t CCMR2;        //0x1C
    volatile uint32_t CCER;         //0X20
    volatile uint32_t CNT;          //0x24
    volatile uint32_t PSC;          //0x28
    volatile uint32_t ARR;          //0x2C
    volatile uint32_t reserved0;    //0x30
    volatile uint32_t CCR1;         //0x34
    volatile uint32_t CCR2;         //0x38
    volatile uint32_t CCR3;         //0x3C
    volatile uint32_t CCR4;         //0x40
    volatile uint32_t reserved1;    //0x44
    volatile uint32_t DCR;          //0x48
    volatile uint32_t DMAR;         //0x4C
    volatile uint32_t OR;           //0x50
}TIM2_5_DataType;

// CONFIGURE TIM_2
#define PERIPH_TIM2_OFFSET          (0x00000000UL) //TIM2 offset
#define APB1_TIM2_BASE              (BUS_APB1_BASE+PERIPH_TIM2_OFFSET)
#define TIM2 ((TIM2_5_DataType*) APB1_TIM2_BASE)

#endif