#ifndef COMMANDTYPE_H
#define COMMANDTYPE_H
//enum commandType{isCam = 0,isADMIN,isCMD};
enum my_net_cmd{
         Login = 0x1,
         LoginSuccess,
         LoginFailed,

         Register,
         RegisterSuccess,
         RegisterFailed,


         Change_Password,
         Change_Password_Success,
         Change_Password_Failed,


         Dev_list,

         Open_Camera = 0x20,
         Open_Camera_Success,
         Open_Camera_Failed,

         Close_Camera,
         Close_Camera_Success,
         Close_Camera_Failed,

         /*灯 控制命令组 开 关 亮度*/
         Open_Led = 0x30,
         Open_Led_Success,
         Open_Led_Failed,
         Close_Led,
         Close_Led_Success,
         Close_Led_Failed,


         Open_Fan = 0x40,
         Open_Fan_Success,
         Open_Fan_Failed,
         Close_Fan,
         Close_Fan_Success,
         Close_Fan_Failed,

         Open_Beep,
         Open_Beep_Success,
         Open_Beep_Failed,
         Close_Beep,
         Close_Beep_Success,
         Close_Beep_Failed,


         Open_Sensor = 0x60,
         Open_Sensor_Success,
         Open_Seneor_Failed,
         Close_Sensor,
         Close_Sensor_Success,
         Close_Sensor_Faile


};
#endif // COMMANDTYPE_H
