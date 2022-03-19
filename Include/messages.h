#ifndef MESSAGES_H
#define MESSAGES_H

#include <process.h>

struct message {
    struct process *from, *to;
    void *bytes;
};

struct messageListNode {
    struct messageListNode *next;
    struct message *leaf;
};

struct messageQueue {
    struct messageListNode *head, *tail;
};

#endif