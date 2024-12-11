#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXNUM 100000

typedef struct Mdata {
    int i, j;
    int num;
} Mdata;

typedef union Udata {
    Mdata elem;
    struct Term *next;
} Udata;

typedef struct Term {
    Udata data;
    struct Term *right;
    struct Term *down;
} Term, *head, *pTerm;

int my_getchar();
void get_elem(head A);
void matrix_add(head A, head B, head C);
head matrix_get_up(head A, int i);
void matrix_insert(head C, head p_C, head p);
head init_matrix(int row, int col);
void matrix_free(head A);

int main()
{
    int row, col;
    int i, j, elem_num = 0;

    scanf("%d", &row);
    scanf("%d", &col);
    while (getchar() != '\n')
        ;
    head A = init_matrix(row, col);
    head B = init_matrix(row, col);
    head C = init_matrix(row, col);

    get_elem(A);
    while (getchar() != '\n')
        ;
    get_elem(B);
    matrix_add(A, B, C);

    head p_row = C->down, p;

    // 为了不多打一个空格 麻烦一点
    int first_print = 1;
    while (p_row != C) {
        p = p_row->right;
        while (p != p_row) {
            if (first_print) {
                printf("%d", p->data.elem.num);
                first_print = 0;
            } else
                printf(" %d", p->data.elem.num);
            p = p->right;
        }
        p_row = p_row->data.next;
    }

    p = C->down->right;
    p_row = C->down;
    for (i = 0; i < row; i++) {
        putchar('\n');
        for (j = 0; j < col - 1; j++) {
            if (p != p_row && i == p->data.elem.i && j == p->data.elem.j) {
                printf("1 ");
                p = p->right;

            } else
                printf("0 ");
        }

        if (p != p_row && i == p->data.elem.i && j == p->data.elem.j) {
            printf("1");
            p = p->right;
        } else
            printf("0");

        p_row = p_row->data.next;
        p = p_row->right;
    }

    matrix_free(A);
    matrix_free(B);
    matrix_free(C);

    return 0;
}

head init_matrix(int row, int col)
{
    head A = (Term *)malloc(sizeof(Term));
    head p, q = A;
    int max = (col > row) ? col : row;

    A->data.elem.i = row;
    A->data.elem.j = col;
    A->data.elem.num = 0;

    p = (Term *)malloc(sizeof(Term));
    p->down = p->right = p;
    q->down = q->right = p;
    q = p;

    for (int i = 1; i < max; i++) {
        p = (Term *)malloc(sizeof(Term));
        p->down = p->right = p;
        q->data.next = p;
        q = p;
    }
    p->data.next = A;
    return A;
}

int buf = 0;
int my_getchar()
{
    int c;
    if (buf) {
        c = buf;
        buf = 0;
        return c;
    } else
        return getchar();
}
void get_elem(head A)
{
    int V[MAXNUM];
    int i, j, num, sign;
    int c, elem_num = 0;
    if ((c = getchar()) != '\n')
        buf = c;
    while (c != '\n') {
        num = 0;
        if ((c = my_getchar()) == '-')
            sign = -1;
        else {
            sign = 1;
            buf = c;
        }
        while (isdigit((c = my_getchar())))
            num = num * 10 + c - '0';
        V[elem_num++] = sign * num;
    }
    A->data.elem.num = elem_num;

    elem_num = 0;
    pTerm p, p_left = A->down;
    for (i = 0; i < A->data.elem.i; i++) {
        for (j = 0; j < A->data.elem.j; j++) {
            scanf("%d", &num);
            if (num) {
                p = (pTerm)malloc(sizeof(Term));
                p->data.elem.i = i;
                p->data.elem.j = j;
                p->data.elem.num = V[elem_num++];
                matrix_insert(A, p_left, p);
                p_left = p;
            }
        }
        p_left = p_left->right->data.next;
    }
}

void matrix_add(head A, head B, head C)
{
    int i, j, index_A, index_B, num, elem_num = 0;
    int col = A->data.elem.j;
    head p_row_A = A->down; // A的行指针 方便判断有没有到尾
    head p_row_B = B->down; // B的行指针 方便判断有没有到尾
    head p_C = C->down;     // 始终指向当前插入元素
    head p_A, p_B, p, p_up; // p_A, p_B遍历AB，p_up用来寻找插入位置头上的元素

    while (p_row_A != A) {
        for (p_A = p_row_A->right, p_B = p_row_B->right; p_A != p_row_A && p_B != p_row_B;) {
            index_A = p_A->data.elem.i * col + p_A->data.elem.j;
            index_B = p_B->data.elem.i * col + p_B->data.elem.j;

            if (index_A == index_B) {
                if ((num = p_A->data.elem.num + p_B->data.elem.num)) {
                    p = (pTerm)malloc(sizeof(Term));
                    p->data.elem = p_A->data.elem;
                    p->data.elem.num = num;
                    matrix_insert(C, p_C, p);
                    elem_num++;
                    p_C = p;
                }
                p_A = p_A->right;
                p_B = p_B->right;
            } else {
                elem_num++;
                p = (pTerm)malloc(sizeof(Term));
                if (index_A < index_B) {
                    p->data.elem = p_A->data.elem;
                    p_A = p_A->right;
                } else {
                    p->data.elem = p_B->data.elem;
                    p_B = p_B->right;
                }
                matrix_insert(C, p_C, p);
                p_C = p;
            }
        }
        for (; p_A != p_row_A; p_A = p_A->right) {
            elem_num++;
            p = (pTerm)malloc(sizeof(Term));
            p->data.elem = p_A->data.elem;
            matrix_insert(C, p_C, p);
            p_C = p_C->right;
        }
        for (; p_B != p_row_B; p_B = p_B->right) {
            elem_num++;
            p = (pTerm)malloc(sizeof(Term));
            p->data.elem = p_B->data.elem;
            matrix_insert(C, p_C, p);
            p_C = p_C->right;
        }
        p_A = p_row_A = p_A->data.next;
        p_B = p_row_B = p_B->data.next;
        p_C = p_C->right->data.next;
    }
    C->data.elem.num = elem_num;
}

// 找到第i列最下边的元素
head matrix_get_up(head A, int i)
{
    int index;
    head p, h;
    for (p = A->right, index = 0; index < i; index++, p = p->data.next)
        ;
    h = p;
    for (; p->down != h; p = p->down)
        ;
    return p;
}

void matrix_insert(head C, head p_C, head p)
{
    p->right = p_C->right;
    p_C->right = p;
    p_C = matrix_get_up(C, p->data.elem.j);
    p->down = p_C->down;
    p_C->down = p;
}

void matrix_free(head A)
{
    head row = A->down, p, q;
    while (row != A) {
        p = row->right;
        while (p != row) {
            q = p->right;
            free(p);
            p = q;
        }
        p = row;
        row = row->data.next;
        free(p);
    }
    free(A);
}
