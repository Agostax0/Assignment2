#include "Util.h"
#include "MsgService.h"
/* Dictates at which distance which state the system is on */
int getState(double distance)
{
    if (distance >= WL1)
    {
        return NORMAL;
    }
    if (distance >= WL2 && distance < WL1)
    {
        return PRE_ALARM;
    }
    if (((distance < WL2) && (distance >= WL_MAX)) || distance < WL_MAX)
    {
        return ALARM;
    }
}
/* This function returns true when value is withing the expected +- (expected  *  percentage / 100) */
bool range(int value, int expected, int percentage)
{
    double percentage_value = expected * (percentage / 100.0);

    int lower_bound = expected - percentage_value;

    int upper_bound = expected + percentage_value;

    return (value > lower_bound && value < upper_bound) ? true : false;
}
bool serial;
int serial_read;
/* This function updates a global bool value to dictate serial input in an ALARM state */
void updateSerial()
{
    if (MsgService.isMsgAvailable())
    {
        Msg *msg = MsgService.receiveMsg();
        String content = msg->getContent();
        if (content.equals("MANUAL"))
        {
            serial = true;
        }
        else if (content.equals("NOMANUAL"))
        {
            serial = false;
        }
        else{
            serial_read=content.toInt();
        }
        delete msg;
    }
}