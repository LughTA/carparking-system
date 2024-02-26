   #include "main.h"
#include "defines.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_fatfs.h"

#define MAX_LEN 16
#define MAX_CARDS 5

uchar status;
uchar str[MAX_LEN]; // Max_LEN = 16
uchar serNum[5];
char myString[100];
uchar check,check2;
uchar Key_Cards[MAX_CARDS][5]; 
uchar test [5] ={0xf3, 0xfa, 0x9c, 0xf7, 0x62};
FATFS FatFs;
FIL fil;
FRESULT fr;

// comfare 2 array 
int compareArrays(const uchar *arr1, const uchar *arr2, int size) {
    for (int i = 0; i < size; ++i) {
        if (arr1[i] != arr2[i]) {
            return 0; // if 2 array not equal
        }
    }
    return 1; // if 2 array equal
}

// display data
void showFileContent() {
    f_rewind(&fil); 
    char ch;
    UINT bytesRead;
    while (f_read(&fil, &ch, 1, &bytesRead) == FR_OK && bytesRead > 0) { // read single character and display
        USART_SendChar(ch); // send character to UART
    }
}

int main() {
    // initialization 
    SPIRC552_Config(); // configure RFID
    TIMDelay_Config(); // configure delay funtion
    UART1_Config(); //  configure UART
    MFRC522_Init(); // initialization RFID

    // Mount file system
    fr = f_mount(&FatFs, "", 1);
    if (fr != FR_OK) {
        return 0;
    }

    // open "cards.txt"
    fr = f_open(&fil, "cards.txt", FA_READ);
    if (fr != FR_OK) {
        return 0;
    }

    // display "cards.txt" data
    showFileContent();

    // read card data from file
    for (int i = 0; i < MAX_CARDS; ++i) {
        UINT bytesRead; 
        fr = f_read(&fil, Key_Cards[i], sizeof(serNum), &bytesRead);
        if (fr != FR_OK || bytesRead != sizeof(serNum)) {
            break; // stop if error
        }
    }

    // close
    f_close(&fil);

    while (1) {
       
        Delay_ms(1000); // delay 1s
        status = MFRC522_Request(PICC_REQIDL, str);    
        if (status == MI_OK) {	
            sprintf(myString,"Your card's number are: %x, %x, %x, %x, %x \r\n",serNum[0], serNum[1], serNum[2], serNum[3],serNum[4]);
						USART_SendString(myString);
            status = MFRC522_Anticoll(str);
            memcpy(serNum, str, sizeof(serNum));
						check = 1;
						check2 = 1;
            // Reset cardMatched variable
            int cardMatched = 0;

            USART_SendString("The ID: ");
            for (int k = 0; k < sizeof(serNum); ++k) {
                sprintf(myString, "%02X ", serNum[k]); // decimal to hex
                USART_SendString(myString);
            }
            USART_SendString("\n");
 
            // compare id card with id in Sd memory
             for (int j = 0; j < MAX_CARDS; ++j) {
                if (compareArrays(serNum, Key_Cards[j], sizeof(serNum))) {
                    
                    sprintf(myString, "ID the khop tai vi tri %d\n", j);
                    USART_SendString(myString);
                    cardMatched = 1;  
                    break; 
                }
								if (!cardMatched) {
                USART_SendString("ID the khong khop voi du lieu SD\n");
								}
            }

            
        }
		if(check == 1||check2 ==1)
				{
				
					check = 0;
					check2 = 0;
					Delay_ms(1000);
					set_pwm(1500);
					Delay_ms(2000);
					set_pwm(500);
					Delay_ms(1000);
				}
    }

    return 0;
}
