#ifndef RMR_EVENT_H_
#define RMR_EVENT_H_

#include <ti/sysbios/knl/Event.h>

extern Event_Handle event_init_system;

#define Event_Init_Cla 		Event_Id_00
#define Event_Init_Control 	Event_Id_01
#define Event_Init_Imu Event_Id_02
#define Event_Init_Motor Event_Id_03
#define Event_Init_Remote Event_Id_04
#define Event_Init_Message Event_Id_05
#define Event_Init_Ultrasonic Event_Id_06

UInt events_and_init_system = Event_Init_Cla +Event_Init_Control + Event_Init_Imu + Event_Init_Motor + Event_Init_Remote + Event_Init_Message + Event_Init_Ultrasonic;
#endif
