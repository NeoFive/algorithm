#include<stdio.h>
struct node
{
    int m_nvalue;
    node* m_pnext;
};

node* creat_list(int* p, int num)
{
    if (p == NULL && num <= 0)
        return NULL;
    node* head = new node;
    head->m_pnext = NULL;
    node* ptail = head; 
    for (int i = 0; i < num; i++)
    {
        node* pcur = new node;
	pcur->m_nvalue = p[i];
	pcur->m_pnext = NULL;

	ptail->m_pnext = pcur;
	ptail = pcur;
	pcur = NULL;
    }

    return head;
}
int show_list(node* head)
{
    if (head == NULL)
        return -1;
    node* pcur = head->m_pnext;
    while (pcur != NULL)
    {
        printf("%d ", pcur->m_nvalue);
        pcur = pcur->m_pnext;
    }
    printf("\n");
    return 0;
}

int delete_note(node* head, int value)
{
    if (head == NULL || head->m_pnext == NULL) 
        return -1;
    node* p = head;
    node* q = head->m_pnext;
    while (q != NULL)
    {
        if(q->m_nvalue == value)
	{
	    p->m_pnext = q->m_pnext;
	    delete q;
	    break;
	}
        p = q;
	q = q->m_pnext;
    }
    if (q == NULL)
        return -1;

    return 0;
}

int delete_list(node* head)
{
    if (head == NULL)
        return -1;
    node* pcur = head;
    node* pnext;
    while(pcur != NULL)
    {   pnext = pcur->m_pnext;
        delete pcur;
	pcur = pnext;

    }
    return 0;
}
node* reverse_list(node* head)
{
    if (head == NULL || head->m_pnext == NULL ||
        head->m_pnext->m_pnext == NULL)//链表为空或者链表只有一个节点，此时直接返回头指针
        return head;
    node* pcur = head->m_pnext->m_pnext;
    head->m_pnext->m_pnext = NULL;
    node* pnext;
    while (pcur != NULL)
    {
	pnext = pcur->m_pnext;
	pcur->m_pnext = head->m_pnext;
	head->m_pnext = pcur;
	pcur = pnext;
    }
   return head;
}
node* reverse_list_recursive_operator(node* phead)//没有头结点的链表
{
    if (phead == NULL)
        return NULL;
    node* pnext = phead->m_pnext;
    if (pnext == NULL)
	return phead;
    phead->m_pnext = NULL;
    node* phead_new = reverse_list_recursive_operator(pnext);
    pnext->m_pnext = phead; 
    return phead_new;
}
node* reverse_list_recursive(node* head)//拥有头结点的链表
{
    if (head == NULL || head->m_pnext == NULL ||
	head->m_pnext->m_pnext == NULL)
	return head;
    node* pcur = reverse_list_recursive_operator(head->m_pnext);
    head->m_pnext = pcur;
    return head;

}
int main()
{
    int num;
    scanf("%d", &num);
    int* p = new int[num];
    for (int i = 0; i < num; i++)
    {
        scanf("%d", &p[i]);
    }
    node* head = creat_list(p, num);
    show_list(head);

    head = reverse_list(head);
    show_list(head);

    head = reverse_list_recursive(head);
    show_list(head);
/*
    int value;
    scanf("%d", &value);
    delete_note(head, value);
    show_list(head);
*/  
    delete_list(head);
    return 0;
}
