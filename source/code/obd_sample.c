#include "main.h"

#define RET_CHECK(code)   \
    if (code != HAL_OK)   \
    {                     \
        return HAL_ERROR; \
    }

/* define diagnosis service number */
#define SVC_01 (0x01) // Current Powertrain Diagnostic

/* define diagnosis service id */
#define DIAGNOSIS_STD_ID (0x7DF)
#define DIAGNOSIS_ID     (DIAGNOSIS_STD_ID)

/* define pid */
#define PID_Engine_Coolant_Temperature (0x05)
#define PID_Intake_Manifold_Pressure   (0x0B)
#define PID_Engine_RPM                 (0x0C)
#define PID_Vehicle_Speed              (0x0D)
#define PID_Intake_Air_Temperature     (0x0F)
#define PID_Mass_Air_Flow_Rate         (0x10)
#define PID_Throttle_Position          (0x11)
#define PID_Fuel_Level                 (0x2F)

/**
 * @brief  init can bus
 * @return uint32_t
 */
static uint32_t obd_init(void)
{
    RET_CHECK(_can_init(&can1_handle));
    RET_CHECK(_can_start(&can1_handle));
    return HAL_OK;
}

/**
 * @brief  deinit can bus
 * @return uint32_t
 */
static uint32_t obd_deinit(void)
{
    RET_CHECK(_can_stop(&can1_handle));
    RET_CHECK(_can_deinit(&can1_handle));
    return HAL_OK;
}

/**
 * @brief print diagnosis information
 * @param[in] pid diagnosis pid
 * @param[in] data diagnosis data
 * @return uint32_t
 */
static uint32_t obd_diagnosis_item_info(uint8_t pid, uint8_t *data)
{
    uint32_t info   = 0;
    uint8_t  data_A = data[3];
    uint8_t  data_B = data[4];
    uint8_t  data_C = data[5];
    uint8_t  data_D = data[6];
    UNUSED(data_C);
    UNUSED(data_D);
    switch (pid)
    {
        case PID_Engine_Coolant_Temperature:
            info = data_A - 40;
            printf("Engine_Coolant    %4d C\r\n", info);
            break;
        case PID_Intake_Manifold_Pressure:
            info = data_A;
            printf("Intake_Manifold   %4d Kpa\r\n", info);
            break;
        case PID_Engine_RPM:
            info = (data_A * 256 + data_B) / 4;
            printf("Engine_RPM        %4d Rpm\r\n", info);
            break;
        case PID_Vehicle_Speed:
            info = data_A;
            printf("Vehicle_Speed     %4d Km/h\r\n", info);
            break;
        case PID_Intake_Air_Temperature:
            info = data_A - 40;
            printf("Air_Temperature   %4d C\r\n", info);
            break;
        case PID_Mass_Air_Flow_Rate:
            info = (data_A * 256 + data_B) / 100;
            printf("Air_Flow_Rate     %4d g/s\r\n", info);
            break;
        case PID_Throttle_Position:
            info = (100 * data_A) / 255;
            printf("Throttle_Position %4d %%\r\n", info);
            break;
        case PID_Fuel_Level:
            info = (100 * data_A) / 255;
            printf("Fuel_Level        %4d %%\r\n", info);
            break;
        default:
            break;
    }

    return info;
}

/**
 * @brief a diagnosis item
 * @param[in] service diagnosis service
 * @param[in] pid diagnosis pid
 * @param[out] info diagnosis info
 * @return uint32_t
 */
static uint32_t obd_diagnosis_item(uint8_t service, uint8_t pid, uint32_t *info)
{
    uint8_t obd_cmd[8] = {0x2, service, pid};
    uint8_t obd_dat[8] = {0};

    CAN_RxHeader_T rx_head = {0};
    CAN_TxHeader_T tx_head = {
        .id  = DIAGNOSIS_ID,
        .ide = CAN_ID_STD,
        .rtr = CAN_RTR_DATA,
        .dlc = 8,
    };

    RET_CHECK(_can_tx_one_msg(&can1_handle, &tx_head, obd_cmd, CAN_MAILBOX_STB, 1));

    RET_CHECK(_can_rx_one_msg(&can1_handle, &rx_head, obd_dat, 1));
    *info = obd_diagnosis_item_info(pid, obd_dat);

    return HAL_OK;
}

uint32_t obd_test(void)
{
    uint32_t info      = 0;
    uint8_t  exit_flag = 1;

    /* obd init */
    RET_CHECK(obd_init());

    /* obd show item */
    while (exit_flag)
    {
        printf("\r\n\r\n");
        obd_diagnosis_item(SVC_01, PID_Engine_Coolant_Temperature, &info);
        obd_diagnosis_item(SVC_01, PID_Intake_Manifold_Pressure, &info);
        obd_diagnosis_item(SVC_01, PID_Engine_RPM, &info);
        obd_diagnosis_item(SVC_01, PID_Vehicle_Speed, &info);
        obd_diagnosis_item(SVC_01, PID_Intake_Air_Temperature, &info);
        obd_diagnosis_item(SVC_01, PID_Mass_Air_Flow_Rate, &info);
        obd_diagnosis_item(SVC_01, PID_Throttle_Position, &info);
        obd_diagnosis_item(SVC_01, PID_Fuel_Level, &info);
        HAL_Delay(1000);
    }

    /* obd deinit */
    RET_CHECK(obd_deinit());

    return HAL_OK;
}
