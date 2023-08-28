#include <stdint.h>
#include <stdio.h>
#include <SN34F280.h>
#include <core_cm4.h>

/* Private typedef -----------------------------------------------------------*/
enum
{
    r0,
    r1,
    r2,
    r3,
    r12,
    lr,
    pc,
    psr
};
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Hard_Fault_Handler(uint32_t stack[]);
/* Private functions ---------------------------------------------------------*/
static void printErrorMsg(const char *errMsg)
{
//    while (*errMsg != '\0')
//    {
//        ITM_SendChar(*errMsg);
//        ++errMsg;
//    }
    printf("%s", errMsg);
}

static void printUsageErrorMsg(uint32_t CFSRValue)
{
    printErrorMsg("Usage fault: \r\n");
    CFSRValue >>= 16; // right shift to lsb

    if ((CFSRValue & (1 << 9)) != 0)
    {
        printErrorMsg("Divide by zero\r\n");
    }
    if ((CFSRValue & (1 << 8)) != 0)
    {
        printErrorMsg("Unaligned access\r\n");
    }
}

static void printBusFaultErrorMsg(uint32_t CFSRValue)
{
    printErrorMsg("Bus fault: \r\n");
    CFSRValue = ((CFSRValue & 0x0000FF00) >> 8); // mask and right shift to lsb
}

static void printMemoryManagementErrorMsg(uint32_t CFSRValue)
{
    printErrorMsg("Memory Management fault: \r\n");
    CFSRValue &= 0x000000FF; // mask just mem faults
}

static void stackDump(uint32_t stack[])
{
    static char msg[80];
    sprintf(msg, "R0  = 0x%08x\r\n", stack[r0]);
    printErrorMsg(msg);
    sprintf(msg, "R1  = 0x%08x\r\n", stack[r1]);
    printErrorMsg(msg);
    sprintf(msg, "R2  = 0x%08x\r\n", stack[r2]);
    printErrorMsg(msg);
    sprintf(msg, "R3  = 0x%08x\r\n", stack[r3]);
    printErrorMsg(msg);
    sprintf(msg, "R12 = 0x%08x\r\n", stack[r12]);
    printErrorMsg(msg);
    sprintf(msg, "LR  = 0x%08x\r\n", stack[lr]);
    printErrorMsg(msg);
    sprintf(msg, "PC  = 0x%08x\r\n", stack[pc]);
    printErrorMsg(msg);
    sprintf(msg, "PSR = 0x%08x\r\n", stack[psr]);
    printErrorMsg(msg);
}

void Hard_Fault_Handler(uint32_t stack[])
{
    static char msg[80];
    // if((CoreDebug->DHCSR & 0x01) != 0) {
    printErrorMsg("\r\nIn Hard Fault Handler\r\n");
    sprintf(msg, "SCB->HFSR = 0x%08x\r\n", SCB->HFSR);
    printErrorMsg(msg);
    if ((SCB->HFSR & (1 << 30)) != 0)
    {
        printErrorMsg("Forced Hard Fault\r\n");
        sprintf(msg, "SCB->CFSR = 0x%08x\r\n", SCB->CFSR);
        printErrorMsg(msg);
        if ((SCB->CFSR & 0xFFFF0000) != 0)
        {
            printUsageErrorMsg(SCB->CFSR);
        }
        if ((SCB->CFSR & 0xFF00) != 0)
        {
            printBusFaultErrorMsg(SCB->CFSR);
        }
        if ((SCB->CFSR & 0xFF) != 0)
        {
            printMemoryManagementErrorMsg(SCB->CFSR);
        }
    }
    stackDump(stack);
    __ASM volatile("BKPT #01");
    //}
    while (1)
        ;
}
/******************************************************************************/
/*    Cortex-M7 Processor Exceptions Handlers                                 */
/******************************************************************************/

/**
 * @brief This function handles NMI exception.
 * @param None
 * @retval None
 */
void NMI_Handler(void)
{
}

/**
 * @brief This function handles Hard Fault exception.
 * @param None
 * @retval None
 */
// void HardFault_Handler(void)
// {
//     __asm("TST lr, #4");
//     __asm("ITE EQ");
//     __asm("MRSEQ r0, MSP");
//     __asm("MRSNE r0, PSP");
//     __asm("B __cpp(Hard_Fault_Handler)");
// }
__asm void HardFault_Handler(void)
{
  TST lr, #4     // Test for MSP or PSP
  ITE EQ
  MRSEQ r0, MSP
  MRSNE r0, PSP
  B __cpp(Hard_Fault_Handler)
}
