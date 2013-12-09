EDtree
======

an R package for decision tree based on E distance

##结构##
1. 核心数据结构： edtree类， 目前包括两个数据成员 tree和split， 两者均为列表。前者保存从样本构建的树的结构，后者保存对应的分裂点和分裂变量。
2. 主要函数
   EDtree(R)[这是一个R函数] : 从样本数据中生成树，先调用C++函数EDtree，得到一棵完全生长的树，然后，调用R函数pruneTree进行剪枝；
   EDtree(cpp)[这是一个C++函数] : 首先调用C++函数EDnode生成根节点，然后判断是否达到终止条件，如果没有达到终止条件，根据根节点的分裂变量和分裂点，调用getSubData,分开样本数据，然后调用SplitNode得到左节点和右节点（递归过程）；
   EDnode(cpp) ： 初始化一个节点的函数，会在这个函数中计算每个节点的统计量，还会计算节点是否达到终止条件，若未达到终止条件，则计算分裂变量和分裂点（这个函数还没有写哦！）