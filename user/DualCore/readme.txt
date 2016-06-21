/**
  @page USBH_DualCore  USB Host Dual Core example
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    readme.txt 
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    09-November-2015
  * @brief   Description of the USB Host Dual Core example
  ******************************************************************************
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License
  *   
  ******************************************************************************
   @endverbatim
   

@par Example Description 

The USB Device Dual Core example uses the STM32F207xx, STM32F429xx and STM32F407xx multi core support
feature and integrates the Mass Storage and HID examples in the same project. 
The Mass storage device should be connected to the USB HS port while the HID device 
should be connected to the FS port. 

The user has to select the USB operation (MSC or HID) using the embedded joystick
following the menu displayed in the Bottom of the LCD display.

 @note Only the BMP files with the following format are supported : 
         - width  : 320
         - Height : 240
         - BPP    :  16
         - Compression : RGB bitmap with RGB masks  
       To use the Image browser, copy the BMP files from "\Utilities\Binary\Media"
       to the root of the USB flash disk to be used.     


@par Hardware and Software environment 

   - This example has been tested with STM322xG-EVAL RevB (STM32F207xx), STM324xG-EVAL RevB (STM32F407xx) 
     and STM324x9I-EVAL RevB (STM32F429xx)    
        
  - STM322xG-EVAL Set-up
    - Use both CN8 and CN9 connectors to connect the USB devices
		@note Make sure that :
		 - Please ensure that jumper JP31 is fitted when using USB OTG HS 
		 
  - STM324xG-EVAL Set-up
    - Use both CN8 and CN9 connectors to connect the USB devices
		@note Make sure that :
		 - Please ensure that jumper JP31 is fitted when using USB OTG HS 
		 
  - STM324x9I-EVAL Set-up
    - Use CN14 connector to connect the board to host when using USB OTG FS peripheral
    - Use CN9  connector to connect the board to host when using USB OTG HS peripheral
    - Use CN15  connector to connect the board to host when using USB OTG HS-IN-FS peripheral
      Note that some FS signals are shared with the HS ULPI bus, so some PCB rework is needed.
              For more details, refer to section "USB OTG2 HS & FS" in STM324x9I-EVAL Evaluation Board 
              User Manual.
        @note Make sure that :
         - Please ensure that jumper JP16 is not fitted when using USB OTG FS

@par How to use it ?

In order to make the program work, you must do the following:
  - Open your preferred toolchain
  - In the workspace toolbar select the project config:
   
    - STM322xG-EVAL_USBD-HS: to configure the project for STM32F207xx devices
    - STM324xG-EVAL_USBD-HS: to configure the project for STM32F407xx devices
    - STM324x9i-EVAL_USBD-HS:to configure the project for STM32F429xx devices
    
  - Rebuild all files and load your image into target memory
  - Run the application

@note Known Limitations
      This example retarget the C library printf() function to the EVAL board�s LCD
      screen (C library I/O redirected to LCD) to display some Library and user debug
      messages. TrueSTUDIO Lite version does not support I/O redirection, and instead
      have do-nothing stubs compiled into the C runtime library. 
      As consequence, when using this toolchain no debug messages will be displayed
      on the LCD (only some control messages in green will be displayed in bottom of
      the LCD). To use printf() with TrueSTUDIO Professional version, just include the
      TrueSTUDIO Minimal System calls file "syscalls.c" provided within the toolchain.
      It contains additional code to support printf() redirection.
      
	  - Display BMP image is not managed within STM324x9I-EVAL eval board.
	  
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
