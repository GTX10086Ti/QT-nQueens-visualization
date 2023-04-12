#ifndef STACKTYPE_H
#define STACKTYPE_H
#include "iostream"
#include <stdlib.h>
#include <QDebug>
#include <QObject>
using namespace std;
#define MaxSize 100
class StackType: public QObject
{
    Q_OBJECT

public:
    explicit StackType();
    int col[MaxSize];
    int rsp;
    int		peekTopData(void);
    int		pop();
    void	ShowStack(void);
    bool	push(int a);
    bool	isStackEmpty(void);
    bool place(StackType *St,int x,int y);
    bool isFound;

signals:
    void sgn_push();
    void sgn_pop();
};

#endif // STACKTYPE_H
