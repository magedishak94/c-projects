#include <stdio.h>
#include <stdlib.h>
#define EMPTY_ERROR -1
typedef struct node* node_ptr;
typedef int node_data;
struct node{
node_data data;
node_ptr next;
node_ptr prev;
};
node_ptr head=NULL,tail=NULL;
int empty(void)
{
    if(head==NULL)return 0;
    else return 1;
}
void push(node_data data)
{
node_ptr new=(node_ptr)malloc(sizeof(struct node));
new->data=data;
if(head==NULL)
{
    head=new;
    tail=new;
    new->next=NULL;
    new->prev=NULL;

}
else{
    head->prev=new;
    new->next=head;
    head=new;
}
}
node_data top(void)
{
    if(head==NULL)
    {
        return EMPTY_ERROR;
    }
    else return head->data;

}
node_data pop(void)
{
    node_data data=top();

    if(head!=NULL)
    {
        node_ptr old=head;

        head=head->next;
        if(head!=NULL)
        head->prev=NULL;

        free(old);
    }
    return data;
}
void enqueue(node_data data)
{
    node_ptr new=(node_ptr)malloc(sizeof(struct node));
    new->data=data;
    new->next=NULL;
    if(tail==NULL)
    {
        tail=new;
        head=new;
        new->prev=NULL;
    }
    else{
        new->prev=tail;
        tail->next=new;
        tail=new;
    }
}
node_data dequeue(void)
{
    if(head==NULL)
    {
        return EMPTY_ERROR;
    }
    else{
        node_data data=head->data;
        node_ptr old=head;
        head=head->next;
        if(head!=NULL)
            head->prev=NULL;
        free(old);
        return data;
    }

}
int main(void)
{
int x;
enqueue(122);
enqueue(133);
while(empty())
{
    x=dequeue();
    printf("%d ",x);
}
    return 0;
}
