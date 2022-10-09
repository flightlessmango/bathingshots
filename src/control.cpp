#include <sys/ipc.h>
#include <sys/msg.h>
#include "control.h"
#include <iostream>

int main(){
    int key = ftok("bathingshots", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    struct bathingshots_v1 msg = {0};
    msg.msg_type = 2;
    msg.screenshot = true;
    msgsnd(msgid, &msg, sizeof(bathingshots_v1), IPC_NOWAIT);
    printf("sent message\n");

    static uint8_t raw_msg[1024] = {0};
    struct bathingshots_v1 *ctrl_msg = (struct bathingshots_v1*) raw_msg;
    size_t msg_size = msgrcv(msgid, (void *) raw_msg, sizeof(raw_msg), 1, 0) + sizeof(long);
    ctrl_msg = (struct bathingshots_v1*) raw_msg;
    printf("%i\n", ctrl_msg->screenshot);
}
