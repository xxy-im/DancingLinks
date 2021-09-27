/*
 * @Author: xxy
 * @Date: 2021-09-27 22:56:29
 * @Description: DancingLinks.h
 */
#pragma once

#include <vector> 

#define     M       6
#define     N       7

class DLNode
{
public:
    DLNode * Left;           // 左结点
    DLNode *Right;          // 右结点
    DLNode *Up;             // 上结点
    DLNode *Down;           // 下结点
    DLNode *Col;            // 所属列结点
    
    int row;                // 行号
    int nums;               // 该列存在的结点个数（当结点为列结点时有效，否则为-1）
    
    DLNode(DLNode *Col, int n, int s = -1):   
        Left(this), Right(this), Up(this), Down(this), 
        Col(Col), row(n), nums(s){ if (Col) Col->Add2Colume(this); };
    ~DLNode() {};
    
    void Add2Row(DLNode *node);            // 添加结点到该行末尾
    void Add2Colume(DLNode *node);         // 添加结点到该列尾
    
    void RemoveCol();                      // 移除该结点所在的列
    void RecoverCol();                     // 还原列
    void Remove();                         // 移除该结点关联的行和列
};
  
class DancingLinks
{
public:
    DancingLinks(int s[M][N]);
    ~DancingLinks(){};
    
    DLNode *Head;                   // 头结点
    std::vector<DLNode *> Cols;     // 列向量
    std::vector<DLNode *> Ans;      // 保存结果
    
    bool DLX();                     // DLX算法求解
    void ShowResult();              // 输出结果
};