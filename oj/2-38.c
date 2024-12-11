#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    int freq;
    int class;
    struct Node* prior;
    struct Node* next;
} Node;

typedef struct Node *Linkedlist;

Linkedlist init_Linkedlist(int n);
void LOCATE(Linkedlist* plist, int x);

int main() {
    int num, c;
    Linkedlist head, p;
    head = p = NULL;
    scanf("%d", &num);
    getchar();
    head = init_Linkedlist(num);
    Linkedlist init_head = head;
    getchar();

    if ((c = getchar()) != '\n') {
        LOCATE(&head, c - '0');
        // for (c = 0, p = head; c < num - 1; c++) {
        //     printf("%d ", p->data);
        //     p = p->next;
        // }
        // if (num)
        //     printf("%d\n", p->data);
        while (getchar() != '\n') {
            scanf("%d", &c);
            LOCATE(&head, c);
            // for (c = 0, p = head; c < num - 1; c++) {
            //     printf("%d ", p->data);
            //     p = p->next;
            // }
            // if (num)
            //     printf("%d\n", p->data);
        }
    }
    for (c = 0, p = head; c < num - 1; c++) {
        printf("%d ", p->data);
        p = p->next;
    }
    if (num)
        printf("%d", p->data);
    free(init_head);
    return 0;
}

Linkedlist init_Linkedlist(int n) {
    Linkedlist p = NULL, head = (Node*)malloc(sizeof(Node) * n);

    if (n == 0)
        return NULL;
    else if (n == 1) {
        scanf("%d", &(head->data));
        head->prior = head;
        head->next = head;
        head->freq = 0;
        head->class = 0;
        return head;
    }

    p = head;
    scanf("%d", &(p->data));
    p->freq = 0;
    p->class = 0;
    (p + 1)->prior = p;
	int i;
    for (i = 1; i < n; i++){
        p->next = p + 1;
        (p + 1)->prior = p;
        p++;
        scanf("%d", &(p->data));
        p->freq = 0;
        p->class = 0;
    }
    p->next = head;
    head->prior = p;

    return head;
}

void LOCATE(Linkedlist* plist, int x) {
    Linkedlist p, q;
    static int class = 1;
    p = *plist;
    do {
        if (p->data == x) {
            (p->freq)++;
            break;
        }
        p = p->next;
    } while(p != *plist);
    if (!(p->class))
        p->class = class++;

    if (((p->prior->freq < p->freq) || \
    (p->prior->freq == p->freq && p->prior->class > p->class)) && p != *plist) {
        q = p->prior;
        q->next = p->next;
        p->next->prior = q;

        while((q->freq < p->freq || q->freq == p->freq && p->class < q->class) && q != *plist)
            q = q->prior;

        if (q == *plist && (q->freq < p->freq ||q->freq == p->freq && q->class > p->class )) {
            q = q->prior;
            *plist = p;
        }

        p->next = q->next;
        p->next->prior = p;
        q->next = p;
        p->prior = q;
    }
}
