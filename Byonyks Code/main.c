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
#include <sys/msg.h> 

//using namespace std;

struct mesg_buffer { 
    long mesg_type; 
    char mesg_text[100]; 
} message; 

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
int main (int argc, char** argv)
{

    //string inputstate;
    gpioExport(8); //create new GPIO object to be attached to  GPIO8
    gpioExport(60);  //create new GPIO object to be attached to  GPIO9
    gpioExport(9);//create new GPIO object to be attached to  GPIO8
    gpioExport(61);
        //GPIOClass* gpio61 = new GPIOClass("61"); //create new GPIO object to $

    gpioDirection(8,1);//export GPIO8
    gpioDirection(9,1);//export GPIO9
    gpioDirection(60,1);//export GPIO60
    gpioDirection(61,1);
    //gpio61->export_gpio(); //export GPIO61
    gpioSet(60,1);
    gpioSet(61,1);
    gpioSet(8,1);
    //gpioSet(9,1);
          key_t key; 
  int msgid; 
  
    // ftok to generate unique key 
    key = ftok("Byonyks", 65); 
  
    // msgget creates a message queue 
    // and returns identifier 
    msgid = msgget(key, 0666 | IPC_CREAT); 
  
    // msgrcv to receive message 
    msgrcv(msgid, &message, sizeof(message), 1, 0);        
       while(message.mesg_text!="Stop")
       {
//msgrcv(msgid, &message, sizeof(message), 1, 0);
           while(message.mesg_text=="Forward")
           {
               gpioSet(9, 1);
                usleep(40);
                gpioSet(9,0);
                usleep(40);
           }
msgrcv(msgid, &message, sizeof(message), 1, 0);
           while(message.mesg_text=="Backward")
           {
               gpioSet(9, 0);
                usleep(40);
                gpioSet(9,1);
                usleep(40);
           }
       }
       // to destroy the message queue
          msgctl(msgid, IPC_RMID, NULL);
              return 0;
}



//The End
 