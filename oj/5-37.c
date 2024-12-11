#include <stdio.h>
#include <stdlib.h>

typedef enum {ATOM, LIST} ElemTag;

typedef struct GLNode {
    ElemTag tag;
    union{
        char atom;
        struct GLNode *hp;
    }ptr;
    struct GLNode *tp;
}GLNode, *GList;

void DeleteAtom(GList p, char x) {
    if (p == NULL)
        return;
    if (p->tag == ATOM && p->ptr.atom == x) {
        // 如果当前节点是原子节点且值等于x，则删除该节点
        GLNode *temp = *p;
        *p = (*p)->ptr.tp;
        free(temp);
        DeleteAtom(p, x);
    } else if ((*p)->tag == LIST) {
        // 如果当前节点是子表节点，则递归处理其子表
        DeleteAtom(&((*p)->ptr.hp), x);
        DeleteAtom(&((*p)->ptr.tp), x);
    } else {
        // 如果当前节点是原子节点但值不等于x，则继续遍历下一个节点
        DeleteAtom(&((*p)->ptr.tp), x);
    }
}

int main() {
    // 在控制台内输入广义表，例如 (a, (b, c), d, (e, (f, g)))
    GList gl = (GList)malloc(sizeof(GLNode));
    gl->tag = LIST;
    gl->ptr.hp = NULL;
    gl->ptr.tp = NULL;
    GLNode *p = gl->ptr.hp;

    char ch = getchar();
    while (ch != ' ') 
	{
        if (ch == '(') {
            GLNode *node = (GLNode *)malloc(sizeof(GLNode));
            node->tag = LIST;
            node->ptr.hp = NULL;
            node->ptr.tp = NULL;
            *p = node;
            p = &((*p)->ptr.tp);
        } 
		else if (ch == ')') 
		{
            *p = NULL;
            p = &((*p)->ptr.tp);
        } else if (ch == ',') {
            p = &((*p)->ptr.tp);
        } else {
            GLNode *node = (GLNode *)malloc(sizeof(GLNode));
            node->tag = ATOM;
            node->ptr.atom = ch;
            *p = node;
            p = &((*p)->ptr.tp);
        }
        ch = getchar();
    }

    // 删除广义表中所有值等于'a'的原子项
    DeleteAtom(&gl, 'a');

    // 打印删除后的广义表
    printf("After deleting all atoms equal to 'a':\n");
    while (gl != NULL) {
        if (gl->tag == ATOM) {
            printf("%c ", gl->ptr.atom);
            gl = gl->ptr.tp;
        } else {
            printf("(");
            GList sublist = gl->ptr.hp;
            while (sublist != NULL) {
                DeleteAtom(&(sublist->ptr.hp), 'a');
                            printf("\n  ");
            GList sub = sublist;
            while (sub != NULL) {
                if (sub->tag == ATOM) {
                    printf("%c ", sub->ptr.atom);
                    sub = sub->ptr.tp;
                } 
				else 
				{
                    printf("(");
                    DeleteAtom(&(sub->ptr.hp), 'a');
                    sub = sub->ptr.hp;
                }
            }
            printf(") ");
            sublist = sublist->ptr.tp;
        }
        printf(")");
        gl = gl->ptr.tp;
    }
}

return 0;
}
