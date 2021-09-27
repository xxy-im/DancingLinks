/*
 * @Author: xxy
 * @Date: 2021-09-27 22:57:52
 * @Description: DancingLinks.cpp
 */
#include <iostream>

#include "DancingLinks.h"

void DLNode::Add2Row(DLNode *node)
{
	node->Left = this->Left;
	node->Right = this;

	this->Left->Right = node;
	this->Left = node;
}

void DLNode::Add2Colume(DLNode *node)
{
	node->Up = this->Up;
	node->Down = this;

	this->Up->Down = node;
	this->Up = node;

	this->nums++;
}

void DLNode::RemoveCol()
{
	this->Right->Left = this->Left;
	this->Left->Right = this->Right;

	for (auto i = this->Down; i != this; i = i->Down)
	{
		for (auto j = i->Right; j != i; j = j->Right)
		{
			j->Up->Down = j->Down;
			j->Down->Up = j->Up;

			j->Col->nums--;
		}
	}
}

void DLNode::RecoverCol()
{
	for (auto i = this->Up; i != this; i = i->Up)
	{
		for (auto j = i->Left; j != i; j = j->Left)
		{
			j->Up->Down = j;
			j->Down->Up = j;

			j->Col->nums++;
		}

	}

	this->Right->Left = this;
	this->Left->Right = this;
}

void DLNode::Remove()
{
	auto node = this;

	do
	{
		node->Col->RemoveCol();
		node = node->Right;

	} while (node != this);

}

DancingLinks::DancingLinks(int s[M][N])
{
    Head = new DLNode(nullptr, 0);

    // N列，创建N个列结点
    for (int i = 0; i < N; i++)
    {
      auto t = new DLNode(nullptr, 0, 0);
      Head->Add2Row(t);
      Cols.push_back(t);
    }

    for (int r = 0; r < M; r++)
    {
        bool flag = false;
        DLNode *node = nullptr;
        for (int c = 0; c < N; c++)
        {
            // 创建结点
            if (s[r][c])
            {
                // 该行的第一个结点
                if (!flag)
                {
                    node = new DLNode(Cols[c], r+1);
                    flag = true;
                }

                node->Add2Row(new DLNode(Cols[c], r+1));
            }
        }
    }

    // 移除初始为空的列
    for (auto col = Head->Right; col != Head; col = col->Right)
	{
		if (!col->nums) col->RemoveCol();
	}
}

bool DancingLinks::DLX()
{
    if (Head->Right == Head)
	{
		ShowResult();
		return true;
	}

    DLNode *col = nullptr;
	int min = INT_MIN;

    // 找到列元素最少的列
	for (auto c = Head->Right; c != Head; c = c->Right)
	{
		if (min > c->nums)
		{
			col = c;
			min = c->nums;
		}
	}

    col->RemoveCol();

	for (auto node = col->Down; node != col; node = node->Down)
	{
		Ans.push_back(node);

		for (auto rnode = node->Right; rnode != node; rnode = rnode->Right)
		{
			rnode->Col->RemoveCol();
		}

		if (DLX())
            return true;

		for (auto lnode = node->Left; lnode != node; lnode = lnode->Left)
		{
			lnode->Col->RecoverCol();
		}

		Ans.pop_back();
	}

	col->RecoverCol();
}

void DancingLinks::ShowResult()
{
    std::cout << "精确覆盖集合为：";
    
    for (auto it = Ans.begin(); it != Ans.end(); it++)
    {
        std::cout << "S" << (*it)->row << " ";
    }

    std::cout << std::endl;    
}