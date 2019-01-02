#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct mesg_buffer 
{
    long mesg_type;
    int mesg;
} message;

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()  //backward
{
        key_t key;
        int msgid;

        // ftok to generate unique key
        key = ftok("Byonyks", 65);

        // msgget creates a message queue
        // and returns identifier
        msgid = msgget(key, 0666 | IPC_CREAT);
        message.mesg_type = 1;
        //strcpy(message.mesg_text,"Backward");
        message.mesg=2;
        // msgsnd to send message
        msgsnd(msgid, &message, sizeof(message), 0);
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_4_clicked()   //forward
{
    key_t key;
    int msgid;

    // ftok to generate unique key
    key = ftok("Byonyks", 65);

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.mesg_type = 1;
    //strcpy(message.mesg_text,"Forward");
    message.mesg=1;
    // msgsnd to send message
    msgsnd(msgid, &message, sizeof(message), 0);
}

void MainWindow::on_pushButton_1_clicked()
{
   ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_2_clicked()
{
    key_t key;
    int msgid;

    // ftok to generate unique key
    key = ftok("Byonyks", 65);

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);

    message.mesg_type = 1;

    //strcpy(message.mesg_text,"Stop");
    message.mesg=3;

    // msgsnd to send message
    msgsnd(msgid, &message, sizeof(message), 0);
}

void MainWindow::on_pushButton_clicked()
{
    key_t key;
    int msgid;

    // ftok to generate unique key
    key = ftok("Byonyks", 65);

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);

    message.mesg_type = 1;

    //strcpy(message.mesg_text,"Stop");
    message.mesg=4;

    // msgsnd to send message
    msgsnd(msgid, &message, sizeof(message), 0);
}

