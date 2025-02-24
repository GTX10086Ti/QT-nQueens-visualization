#include "stacktype.h"
StackType::StackType()
{
    this->rsp = 0;
    isFound = false;
}

bool	StackType::push(int a)
{
    if (rsp != MaxSize - 1)
    {
        this->rsp++;
        this->col[this->rsp] = a;
        emit sgn_push();
        return true;
    }
    else return false;
}

int		StackType::peekTopData(void)
{
    return this->col[this->rsp];
}

bool	StackType::isStackEmpty(void)
{
    return this->rsp == 0;
}

int		StackType::pop()
{
    if (this->rsp != 0)
    {
        if (this->rsp == 0) return -1;
        int b = this->col[this->rsp];
        this->col[this->rsp] = -1;
        this->rsp--;
        emit sgn_pop();
        return b;
    }
}

void	StackType::ShowStack(void)
{
    for (int i = 1; i <= this->rsp; i++)
        qDebug() << '<' << i << ',' << this->col[i] << ">  ";
//    qDebug() << '\n';
}

bool StackType::place(StackType *St,int x,int y)
{
    int i=1;
    while (i<x)					//遍历至上一行
    {
        //	 列冲突				是否和前面元素斜线冲突
        if ((St->col[i]==y) || (abs(y-St->col[i])==abs(i-x)))  //检查与前面的元素是否冲突
            return false;	//↑遍历元素斜线		↑要放置的坐标
        i++;
    }
    return true;
}
