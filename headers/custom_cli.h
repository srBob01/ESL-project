#include "app_usbd.h"
#include "app_usbd_serial_num.h"
#include "app_usbd_cdc_acm.h"
#include "states.h"
#include "custom_save_color.h"

#define READ_SIZE 1
#define MAX_COMMAND_LENGTH 20

static char m_rx_buffer[READ_SIZE];

static char commandBuffer[MAX_COMMAND_LENGTH];
static size_t commandLength = 0;

#define CDC_ACM_COMM_INTERFACE  2
#define CDC_ACM_COMM_EPIN       NRF_DRV_USBD_EPIN3

#define CDC_ACM_DATA_INTERFACE  3
#define CDC_ACM_DATA_EPIN       NRF_DRV_USBD_EPIN4
#define CDC_ACM_DATA_EPOUT      NRF_DRV_USBD_EPOUT4

static void usb_ev_handler(app_usbd_class_inst_t const * p_inst,
                           app_usbd_cdc_acm_user_event_t event);


APP_USBD_CDC_ACM_GLOBAL_DEF(usb_cdc_acm,
                            usb_ev_handler,
                            CDC_ACM_COMM_INTERFACE,
                            CDC_ACM_DATA_INTERFACE,
                            CDC_ACM_COMM_EPIN,
                            CDC_ACM_DATA_EPIN,
                            CDC_ACM_DATA_EPOUT,
                            APP_USBD_CDC_COMM_PROTOCOL_NONE);


static const char *comandHelp = "help";
static const char *comandRGB = "RGB";
static const char *comandHSV = "HSV";
static uint8_t length_command_help;
static uint8_t length_command_color;

static const char *messageHelp = "RGB <red> <green> <blue> - the device sets current color to specified one.\r\n"
                          "HSV <hue> <saturation> <value> - the same with RGB, but color is specified in HSV.\r\n"
                          "help - print information about supported commands\r\n";
static uint16_t length_message_help;

static const char* messageNone = "You have entered the invalid command. Please, choose the valid command. You can see all command, if enter 'help'.\r\n";
static uint16_t length_message_none;

static const char *messageInvalidRGB = "RGB values should be in the range [0...255]\r\n";
static uint16_t length_message_invalid_rgb;

static const char *messageInvalidHSV = "HSV values should be within these limits: hue [0...360], staturation and value [0...100]\r\n";
static uint16_t length_message_invalid_hsv;

void init_length(){
    length_command_help = strlen(comandHelp);
    length_command_color = strlen(comandRGB);
    length_message_help = strlen(messageHelp);
    length_message_none = strlen(messageNone);
    length_message_invalid_rgb = strlen(messageInvalidRGB);
    length_message_invalid_hsv = strlen(messageInvalidHSV);
}

static enum command what_command_now(const char *commandBuffer, size_t length, int *color_var_1, int *color_var_2, int *color_var_3){
    if(length == length_command_help + 1){
        if(strncmp(commandBuffer, comandHelp, length_command_help) == 0)
        {
            return COMMAND_HELP;
        }
    }
    else
        if(length > length_command_color){
            if (strncmp(commandBuffer, comandRGB, length_command_color) == 0 &&
                    sscanf(commandBuffer, "RGB %d %d %d", color_var_1, color_var_2, color_var_3) == 3)
            {
                return COMMAND_RGB;
            }
            else
                if(strncmp(commandBuffer, comandHSV, length_command_color) == 0 &&
                        sscanf(commandBuffer, "HSV %d %d %d", color_var_1, color_var_2, color_var_3) == 3)
                {
                    return COMMAND_HSV;
                }
    }
    return COMMAND_NONE;
}

static bool is_valid_rgb(int r, int g, int b){
    if(r >= MIN_RGB && g >= MIN_RGB && b >= MIN_RGB &&
        r <= MAX_RGB && g <= MAX_RGB && b <= MAX_RGB)
    {
        return true;
    }
    return false;
}

static bool is_valid_hsv(int hue, int sat, int val){
    if(hue >= MIN_HUE && sat >= MIN_SAT && val >= MIN_VAL &&
        hue <= MAX_HUE && sat <= MAX_SAT && val <= MAX_VAL)
    {
        return true;
    }
    return false;
}

static void checkCommand(const char *commandBuffer, size_t length) {
    char message[50];
    int color_var_1 = 0, color_var_2 = 0, color_var_3 = 0;
    enum command current_command = what_command_now(commandBuffer, length, &color_var_1, &color_var_2, &color_var_3);
    union RGB_OR_WORD tmp_rgb_or_word;
    switch(current_command){
        case COMMAND_NONE:
            NRF_LOG_INFO("None command");
            app_usbd_cdc_acm_write(&usb_cdc_acm, messageNone, length_message_none);
            break;
        case COMMAND_HELP:
            NRF_LOG_INFO("Help command");
            app_usbd_cdc_acm_write(&usb_cdc_acm, messageHelp, length_message_help);
            break;
        case COMMAND_RGB:
            if(is_valid_rgb(color_var_1, color_var_2, color_var_3)){
                NRF_LOG_INFO("Valid RGB command");
                sprintf(message, "Color set to R=%d G=%d B=%d\r\n", color_var_1, color_var_2, color_var_3);
                app_usbd_cdc_acm_write(&usb_cdc_acm, message, strlen(message));
                tmp_rgb_or_word = save_rgb(color_var_1, color_var_2, color_var_3);
                change_ledRGB(tmp_rgb_or_word);
            }
            else{
                NRF_LOG_INFO("Invalid RGB command");
                app_usbd_cdc_acm_write(&usb_cdc_acm, messageInvalidRGB, length_message_invalid_rgb);
            }
            break;
        case COMMAND_HSV:
            if(is_valid_hsv(color_var_1, color_var_2, color_var_3)){
                NRF_LOG_INFO("Valid HSV command");
                sprintf(message, "Color set to H=%d S=%d V=%d\r\n", color_var_1, color_var_2, color_var_3);
                app_usbd_cdc_acm_write(&usb_cdc_acm, message, strlen(message));
                tmp_rgb_or_word = save_hsv(color_var_1, color_var_2, color_var_3);
                change_ledRGB(tmp_rgb_or_word);
            }
            else{
                NRF_LOG_INFO("Invalid HSV command");
                app_usbd_cdc_acm_write(&usb_cdc_acm, messageInvalidHSV, length_message_invalid_hsv);
            }
            break;
    }
}

void usb_ev_handler(app_usbd_class_inst_t const * p_inst,
                           app_usbd_cdc_acm_user_event_t event)
{
    switch (event) {
    case APP_USBD_CDC_ACM_USER_EVT_PORT_OPEN: {
        ret_code_t ret;
        ret = app_usbd_cdc_acm_read(&usb_cdc_acm, m_rx_buffer, READ_SIZE);
        UNUSED_VARIABLE(ret);
        break;
    }
    case APP_USBD_CDC_ACM_USER_EVT_PORT_CLOSE: {
        break;
    }
    case APP_USBD_CDC_ACM_USER_EVT_TX_DONE: {
        NRF_LOG_INFO("tx done");
        break;
    }
    case APP_USBD_CDC_ACM_USER_EVT_RX_DONE: {
        ret_code_t ret;
        do {
            /*Get amount of data transfered*/
            size_t size = app_usbd_cdc_acm_rx_size(&usb_cdc_acm);
            NRF_LOG_INFO("rx size: %d", size);

            /* It's the simple version of an echo. Note that writing doesn't
             * block execution, and if we have a lot of characters to read and
             * write, some characters can be missed.
             */
            if (commandLength < MAX_COMMAND_LENGTH - 1) {
                commandBuffer[commandLength] = m_rx_buffer[0];            
                commandLength++;
                commandBuffer[commandLength] = '\0'; 
            }

            if (m_rx_buffer[0] == '\r' || m_rx_buffer[0] == '\n') {
                ret = app_usbd_cdc_acm_write(&usb_cdc_acm, "\r\n", 2);

                checkCommand(commandBuffer, commandLength);

                memset(commandBuffer, 0, sizeof(commandBuffer));
                commandLength = 0;
            }
            else {
                ret = app_usbd_cdc_acm_write(&usb_cdc_acm,
                                             m_rx_buffer,
                                             READ_SIZE);
            }

            /* Fetch data until internal buffer is empty */
            ret = app_usbd_cdc_acm_read(&usb_cdc_acm,
                                        m_rx_buffer,
                                        READ_SIZE);
        } while (ret == NRF_SUCCESS);

        break;
    }
    default:
        break;
    }
}