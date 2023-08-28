#include "main.h"

#define RECO_STEP_CNT (32)
#define BUFF_STEP_CNT (64)
#if (RECO_STEP_CNT > BUFF_STEP_CNT)
#error "The buffer is shortage."
#elif (RECO_STEP_CNT == BUFF_STEP_CNT)
#error "The buffer usage does not apply it currently."
#elif (RECO_STEP_CNT < BUFF_STEP_CNT)
#endif

#define AUDIO_SAMPLE_RATE (8 * 1000) // multiples of 1000
#define AUDIO_SAMPLE_BIT (2 * 8)     // multiples of 8
#define AUDIO_SAMPLE_CH (1)          // 1: mono, 2:stero
#define AUDIO_STEP_TIM_ms (16)       // choose what you want

#define AUDIO_RECO_TIM_ms (AUDIO_STEP_TIM_ms * RECO_STEP_CNT) // 16*32= 512 ms
#define AUDIO_BUFF_TIM_ms (AUDIO_STEP_TIM_ms * BUFF_STEP_CNT) // 16*64=1024 ms

#define AUDIO_BUFF_BYTE(ms, rate, ch, bit) (ms * (rate / 1000) * (bit / 8) * ch)
#define AUDIO_STEP_SIZ AUDIO_BUFF_BYTE(AUDIO_STEP_TIM_ms, AUDIO_SAMPLE_RATE, AUDIO_SAMPLE_CH, AUDIO_SAMPLE_BIT) // size of recording data
#define AUDIO_RECO_SIZ AUDIO_BUFF_BYTE(AUDIO_RECO_TIM_ms, AUDIO_SAMPLE_RATE, AUDIO_SAMPLE_CH, AUDIO_SAMPLE_BIT) // size of recognize need
#define AUDIO_BUFF_SIZ AUDIO_BUFF_BYTE(AUDIO_BUFF_TIM_ms, AUDIO_SAMPLE_RATE, AUDIO_SAMPLE_CH, AUDIO_SAMPLE_BIT) // size of totally buffer

Audio_Handle_T audio_handle = {
    .init = {
        .xfer_instance = SN_SPI0,
        .cmd_instance = SN_I2C1,
    },
};
uint8_t *audio_buff = NULL;

static uint32_t exist_task = 1;
void exit_recording_task(void)
{
    exist_task = 0;
}

void recording_task(void *pvParameters)
{
    uint32_t state = HAL_ERROR;

    audio_buff = pvPortMalloc(AUDIO_BUFF_SIZ);
    RET_ERROR_IF(audio_buff == NULL, "err recording_task");

    state = record_buff_start(AUDIO_SAMPLE_RATE, AUDIO_SAMPLE_CH, AUDIO_SAMPLE_BIT, AUDIO_STEP_SIZ);
    RET_ERROR_IF(state != HAL_OK, "err recording_task");

    // for give recognize_task a continuous buffer, there is two eg.
    //--------------------------------------------------------------
    // eg1.
    // BUFF_STEP_CNT=8, RECO_STEP_CNT=4
    // data map:index scope
    // sync->[0-4]
    //            step->[3-7]
    //                      copy->[5-7]
    // *00* 00 00 *00* | 01 *02* 03 04 |
    // *02* 03 04 *05* | 06 *07* 08 09 |
    // *07* 08 09 *10* | 11 *12* 13 14 |
    //--------------------------------------------------------------
    // eg2.
    // BUFF_STEP_CNT=12, RECO_STEP_CNT=4
    // data map:index scope
    // sync->[0-8]
    //            step->[3-11]
    //                                    copy->[9-11]
    // *00* 00 00 *00* | 01 02 03 04 | 05 *06* 07 08 |
    // *06* 07 08 *09* | 10 11 12 13 | 14 *15* 16 17 |
    // *15* 16 17 *18* | 19 20 21 22 | 23 *24* 25 26 |
    //--------------------------------------------------------------
    uint32_t sync_idx = 0; // index for sync to recognize_task
    uint32_t step_idx = 0; // index for save current audio data
    uint32_t copy_idx = 0; // index for copy current audio data
    while (exist_task)
    {
        // recircle
        step_idx = step_idx % BUFF_STEP_CNT;
        if (step_idx < RECO_STEP_CNT)
        {
            step_idx = RECO_STEP_CNT - 1;
        }

        // read audio data from codec
        state = record_buff_data(audio_buff + step_idx * AUDIO_STEP_SIZ, AUDIO_STEP_SIZ);
        RET_ERROR_IF(state != HAL_OK, "err recording_task");

        // copy current audio data for compose the continuous buffer
        // copy tail data to head position
        if (step_idx > (BUFF_STEP_CNT - RECO_STEP_CNT))
        {
            copy_idx = (step_idx - (BUFF_STEP_CNT - RECO_STEP_CNT + 1));
            uint8_t *src_addr = audio_buff + step_idx * AUDIO_STEP_SIZ;
            uint8_t *dst_addr = audio_buff + copy_idx * AUDIO_STEP_SIZ;
            memcpy(src_addr, dst_addr, AUDIO_STEP_SIZ);
        }
        else
        {
            copy_idx = 0;
        }

        // sync to recognize_task
        sync_idx = step_idx - (RECO_STEP_CNT - 1);
        uint8_t *sync_addr = audio_buff + sync_idx * AUDIO_STEP_SIZ;
        uint32_t sync_size = AUDIO_RECO_SIZ;
        UNUSED(sync_addr);
        UNUSED(sync_size);

        KWS_LOG("step_idx=%d, sync_idx=%d, copy_idx=%d", step_idx, sync_idx, copy_idx);
        // recircle
        step_idx++;
    }

    state = record_buff_ended();
    RET_ERROR_IF(state != HAL_OK, "err recording_task");

    vPortFree(audio_buff);
    vTaskDelete(NULL);
}
