/**
  ******************************************************************************
  * @file    usbh_fs.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    09-November-2015
  * @brief   This file includes File read management function.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "usbh_fs.h"
#include "usbh_data.h"
#include <string.h>

/** @addtogroup USBH_FS
* @{
*/

/** @addtogroup USBH_CDC_DEMO_USER_CALLBACKS
* @{
*/

/** @defgroup USBH_FS
* @brief This file includes File read management function.
* @{
*/ 


/** @defgroup USBH_CORE_Exported_TypesDefinitions
* @{
*/ 

/**
* @}
*/ 

/** @addtogroup USER
* @{
*/

/** @defgroup USBH_FS 
* @brief    This file includes the user application layer
* @{
*/ 

/** @defgroup USBH_CORE_Exported_Types
* @{
*/ 


/** @defgroup USBH_FS_Private_Defines
* @{
*/ 
/**
* @}
*/ 


/** @defgroup USBH_FS_Private_Macros
* @{
*/ 
/**
* @}
*/ 

/** @defgroup USBH_FS_Private_Variables
* @{
*/


/**
* @}
*/

/** @defgroup USBH_FS_Private_Constants
* @{
*/ 

/**
* @}
*/



/** @defgroup USBH_FS_Private_FunctionPrototypes
* @{
*/ 

/**
* @}
*/ 


/** @defgroup USBH_FS_Private_Functions
* @{
*/ 
/**
* @brief  This function open the file 
* @param  name : name of the file 
* @param  file : this holds the filename and length of the file 
* @retval TRUE : file exist
          FALSE : file not exist  
*/
uint32_t Fs_Open(uint8_t *name, struct fs_file *file)
{
  struct fsdata_file_noconst *f;

  for (f = (struct fsdata_file_noconst *)FS_ROOT; f != NULL; f = (struct fsdata_file_noconst *)f->next)
  {
    if (!strcmp((char *)name, (char *)f->name))
    {
      file->data = f->data;
      file->len = f->len;
      return TRUE;
    }
  }
  return FALSE;
}


/**
* @}h
*/ 

/**
* @}
*/ 

/**
* @}
*/

/**
* @}
*/
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
