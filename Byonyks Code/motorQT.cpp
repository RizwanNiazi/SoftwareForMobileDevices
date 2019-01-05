#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h> 
#include <sys/ipc.h>
#include <iostream>
#include <sys/msg.h>

using namespace std;

struct msg_buffer 
{ 
    long msg_type; 
    int msg; 
} sendQueue; 
struct msg_buffer receiveQueue; 

class Ipc
{
private:
/*
    This msendKey is for the process using this class
    mRecieveKey will be of the process this process 
    will be communicating with
*/
    key_t mSendKey;
    key_t mReceiveKey;
public:
    Ipc(int sendKey, int receiveKey)
    {
        // ftok to generate unique key 
        mReceiveKey=ftok("Byonyks", receiveKey);
        mSendKey=ftok("Byonyks",sendKey);
    }
    ~Ipc()
    {
        int msgid; 
        msgid = msgget(mReceiveKey, 0666 | IPC_CREAT); 
        msgctl(msgid, IPC_RMID, NULL); 
        msgid = msgget(mSendKey, 0666 | IPC_CREAT); 
        msgctl(msgid, IPC_RMID, NULL); 
    }

/*
    This function basically sends a message taken as a string
    to the recipient that was set during initialization of the class
    i.e mRecieveKey.
*/

    void sendMessage(int message)
    {
        int msgid; 
    
        // msgget creates a message queue 
        // and returns identifier 
        msgid = msgget(mSendKey, 0666 | IPC_CREAT); 
        sendQueue.msg_type = 1; 
    
        //strcpy(sendQueue.msg_text,message);
        sendQueue.msg = message;

        // msgsnd to send message 
        msgsnd(msgid, &sendQueue, sizeof(sendQueue), 0); 

        // display the message 
        cout<<"Data send is : "<<sendQueue.msg; 
    }
/*
    This function basically recieves a message from the sender
    that was set during initialization of the class i.e mRecieveKey
     as a string. 
     If there are no messages in the queue, an empty string is returned
*/
    int receiveMessage()
    {
        int msgid; 

        // msgget creates a message queue 
        // and returns identifier 
        msgid = msgget(mReceiveKey, 0666 | IPC_CREAT); 
    
        // msgrcv to receive message 
        if (msgrcv(msgid, &receiveQueue, sizeof(receiveQueue), 1, IPC_NOWAIT)>=$
        {
            if(receiveQueue.msg>0 && receiveQueue.msg<4)
             {
               cout<<"Data Received is :"<<receiveQueue.msg<<endl;
            } 
            return receiveQueue.msg;
        } 
    
        // returns an empty string if there is no message
        return 0;
    }
    int getmsg()
    {
        return receiveQueue.msg;
    }
    bool checkstatus(int num1,int num2,int num3, bool &returnValue)
    {
        if((receiveMessage()==num1 || getmsg()==num1) || (receiveMessage()==num$
        {
           returnValue = true;
        }
        else
        {
            returnValue = false;
        }
    }
};

void gpioExport(int gpio)
{
    int fd;
    char buf[255];
    fd = open("/sys/class/gpio/export", O_WRONLY);
    sprintf(buf, "%d", gpio);
    write(fd, buf, strlen(buf));
        close(fd);
}
    
void gpioDirection(int gpio, int direction) // 1 for output, 0 for input
{
        int fd;
        char buf[255];
        sprintf(buf, "/sys/class/gpio/gpio%d/direction", gpio);
        fd = open(buf, O_WRONLY);
    
        if (direction)
        {
            write(fd, "out", 3);
             }
        else
        {
            write(fd, "in", 2);
        }
           close(fd);
}

void gpioSet(int gpio, int value)
{
           int fd;
           char buf[255];
           sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio);
           fd = open(buf, O_WRONLY);
           sprintf(buf, "%d", value);
           write(fd, buf, 1);
           close(fd);
}
void gpiounExport(int gpio)
{
    int fd;
    char buf[255];
    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    sprintf(buf, "%d", gpio);
    write(fd, buf, strlen(buf));
        close(fd);
}

void RUN_Forward(int gpion)
{
    gpioSet(gpion, 0);
    usleep(40);
    gpioSet(gpion,1);
    usleep(40);
}

void RUN_Backward(int gpion)
{
    gpioSet(gpion, 1);
    usleep(40);
    gpioSet(gpion,0);
    usleep(40);
}

Void UNExportGPIOs()
{
     gpiounExport(8);
     gpiounExport(9);
     gpiounExport(60);
     gpiounExport(61);
}

int main (int argc, char** argv)
{
           //string inputstate;
           gpioExport(8);   //create new GPIO object to be attached to  GPIO8
           gpioExport(60);  //create new GPIO object to be attached to  GPIO9
           gpioExport(9);   //create new GPIO object to be attached to  GPIO8
           gpioExport(61);
               //GPIOClass* gpio61 = new GPIOClass("61"); //create new GPIO obj$

           gpioDirection(8,1);  //export GPIO8
           gpioDirection(9,1);  //export GPIO9
           gpioDirection(60,1); //export GPIO60
           gpioDirection(61,1);
           //gpio61->export_gpio(); //export GPIO61
           gpioSet(60,1);
           gpioSet(61,1);
           gpioSet(8,1);
 //gpioSet(9,1);
           Ipc a(65,65);
    while(1)
    {
        //msgrcv(msgid, &receiveQueue, sizeof(receiveQueue), 1, 0);
        if(a.receiveMessage()==1 || a.getmsg()==1)
        {
            while(1)
            {
                RUN_Forward(9);
                cout<<"Data forward is : "<<receiveQueue.msg<<endl;
                    if(a.checkstatus(2,3,4)==true)
                    {
                           break;
                    }
            }//while(1)
        }// if 
        else if(a.receiveMessage()==2 || a.getmsg()==2)
        {
            while(1)
            {
                RUN_Backward(9);
                cout<<"Data Backward is : "<<receiveQueue.msg<<endl;
                if(a.checkstatus(1,3,4)==true)
                {
                    break;
                }
            }// while
        }// elseif
        else if((a.receiveMessage()==3 || a.getmsg()==3))
        {
               break;
        }
        else if((a.receiveMessage()==4 || a.getmsg()==4))
        {

        }
       }
 // to destroy the message queue 
    //msgctl(msgid, IPC_RMID, NULL);
              return 0;
}