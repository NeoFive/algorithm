#include<stdio.h>
#include<string.h>
#include<stack>
#include<queue>
#include<vector>
//二叉树节点
struct binary_tree_node
{
    int m_nvalue;
    binary_tree_node * m_pleft;
    binary_tree_node * m_pright;
};

//根据二叉树先序遍历和中序遍历重构二叉树递归调用函数
binary_tree_node * construct_binary_tree_core(int * start_pre_order, int * end_pre_order,
		int * start_in_order, int * end_in_order)
{
    //生成根节点
    int root_value = start_pre_order[0];
    binary_tree_node * root = new binary_tree_node();
    root->m_nvalue = root_value;
    root->m_pleft = root->m_pright = NULL;
    #ifdef EXTRA_DEBUG
    printf("start_pre_order point to %d\n", *start_pre_order);
    printf("end_pre_order point to %d\n", *end_pre_order);
    printf("start_in_order point to %d\n", *start_in_order);
    printf("end_in_order point to %d\n\n", *end_in_order);
    
    #endif 
    //如果只有根节点一个节点，则返回
    if (start_pre_order == end_pre_order)
    {
        if (start_in_order == end_in_order && *start_pre_order == *start_in_order)
	    return root;//两个序列的状态必须吻合
	else
	{
	    printf("invalid input\n");
	    return NULL;
	}
    }

    //在中序遍历序列中查找根节点
    int* root_in_order = start_in_order;
    while (root_in_order <= end_in_order)
    {
        if (*root_in_order != root_value)
            root_in_order++;
	else
	    break;
    }

    //根节点在中序遍历序列中没哟找到，属于错误输入
    if (root_in_order > end_in_order)
    {
        printf("invalid input : root_in_order > end_in_order\n");
        printf("root_value = %d\n", root_value);
       	return NULL;
    }
    //构建左子树
    int left_length = root_in_order - start_in_order;
    if (left_length > 0)
        root->m_pleft = construct_binary_tree_core(start_pre_order + 1, start_pre_order + left_length,
			start_in_order, root_in_order -1);

    //构建右子树
    int right_length = end_in_order - root_in_order;
    if (right_length > 0)
        root->m_pright = construct_binary_tree_core(start_pre_order + left_length +1, end_pre_order,
			root_in_order + 1, end_in_order);
    return root;

}
//根据中序遍历和先序遍历构建二叉树
binary_tree_node * construct_binary_tree(int * pre_order, int * in_order, int length)
{
    if (pre_order == NULL || in_order == NULL || length <= 0)
        return NULL;
    return construct_binary_tree_core(pre_order,  pre_order + length -1, in_order, in_order + length - 1);
}
//递归中序遍历二叉树
void in_order_scan(binary_tree_node* root)
{
    if (root == NULL)
         return;
    if (root->m_pleft != NULL)
         in_order_scan(root->m_pleft);
    printf("%d ", root->m_nvalue);
    if (root->m_pright != NULL)
         in_order_scan(root->m_pright);
    
    return;
}
//非递归中序遍历二叉树
void inorder_scan_with_norecursive(binary_tree_node * root)
{
    if (root == NULL)
        return;
    binary_tree_node * p = root;
    std:: stack<binary_tree_node*> s;
   
    while (p != NULL || !s.empty())
    {
        while (p != NULL)
	{
	    s.push(p);
	    p = p->m_pleft;
	}
	p = s.top();
	s.pop();
        printf("%d ", p->m_nvalue);
        p = p->m_pright;	
    }
}

//判断两颗二叉树是否相同
bool is_equal(binary_tree_node * root1, binary_tree_node * root2)
{
    if (root1 == NULL && root2 == NULL)
        return true;
    if ((root1 == NULL && root2 != NULL) || (root1 != NULL && root2 == NULL))
	return false;
    if (root1->m_nvalue != root2->m_nvalue)
	return false;
    return (is_equal(root1->m_pleft, root2->m_pleft) && is_equal(root1->m_pright, root2->m_pright));
}
//求二叉树的深度
int tree_depth(binary_tree_node * root)
{
    if (root == NULL)
        return 0;
    int left_depth = tree_depth(root->m_pleft);
    int right_depth = tree_depth(root->m_pright);
    return left_depth > right_depth ? left_depth + 1 : right_depth + 1;

}
//求二叉树中节点的最大距离
typedef struct result
{
    int depth;
    int distance;
}result;
result  max_distance(binary_tree_node * root)
{
    if (root == NULL)
    {
        result result_ret;
	result_ret.depth = -1;//单个节点的深度定义为0，这样求出的深度才是需要的
	result_ret.distance = 0;
	return result_ret;
    }
    result result_left = max_distance(root->m_pleft);
    result result_right = max_distance(root->m_pright);
    result result_ret;
    result_ret.depth = result_left.depth > result_right.depth ? result_left.depth + 1 : 
	    result_right.depth + 1;
    int temp = result_left.depth + result_right.depth + 2;
    int  max = result_left.distance > result_right.distance ? result_left.distance : result_right.distance;
    max = max > temp ? max : temp;
    result_ret.distance = max;
    #ifdef EXTRA_DEBUG
    printf("root point to %d\n", root->m_nvalue);
    printf("depth = %d\n", result_ret.depth);
    printf("distance = %d\n", result_ret.distance);
    printf("result_left.distance = %d\n", result_left.distance);
    printf("result_right.distance = %d\n", result_right.distance);
    printf("temp = %d\n", temp);
    printf("result_left.depth = %d\n", result_left.depth);
    printf("result_right.depth = %d\n", result_right.depth);
    #endif
    return result_ret;
}
//判断一棵树是否二叉排序树
binary_tree_node * pre = NULL;//指向遍历的前一个节点
bool judge_BST(binary_tree_node * root)
{
    if (root == NULL)
        return true;
    bool left = judge_BST(root->m_pleft);
    if (pre != NULL)
        if (pre->m_nvalue > root->m_nvalue)
            return false;
    pre = root;
    bool right = judge_BST(root->m_pright);
    if (left && right)
        return true;
   return false; 
}
//判断一棵树是否二叉平衡树
typedef struct result_avl
{
    bool is_AVL;
    int depth;
}result_avl;
result_avl judge_AVL(binary_tree_node * root)
{
    if (root == NULL)
    {
        result_avl result_ret = {true, 0};
	return result_ret;
    }
    result_avl result_left = judge_AVL(root->m_pleft);
    result_avl result_right = judge_AVL(root->m_pright);
    result_avl result_ret;
    int diff = result_left.depth - result_right.depth;
    if (result_left.is_AVL && result_right.is_AVL && 
	(diff <=1 && diff >= -1))
        result_ret.is_AVL = true;
    else
	result_ret.is_AVL = false;
    result_ret.depth = result_left.depth > result_right.depth ?
	    result_left.depth + 1 : result_right.depth + 1;
    return result_ret;
}
//二叉树的镜像
int minitor_tree(binary_tree_node * root)
{
    if (root == NULL)
        return 0;
    if (root->m_pleft == NULL && root->m_pright == NULL)
	return 0;
    binary_tree_node * temp = root->m_pleft;
    root->m_pleft = root->m_pright;
    root->m_pright = temp;

    minitor_tree(root->m_pleft);
    minitor_tree(root->m_pright);
    return 0;
}
//层次遍历二叉树
void print_binary_tree(binary_tree_node * root)
{
    if (root == NULL)
        return ;
    std::queue<binary_tree_node *> q;
    q.push(root);
    while (!q.empty())
    {
        binary_tree_node * p = q.front();
	printf("%d ", p->m_nvalue);
	q.pop();
	if (p->m_pleft != NULL)
	    q.push(p->m_pleft);
	if (p->m_pright != NULL)
	    q.push(p->m_pright);
    }
}
//判断一个序列是否某颗二叉搜索树的后序遍历序列
bool is_after_scan(int * begin, int * end)
{
    if (begin == end)
        return true;
    int root_value = *end;
    int * cur;
    for (cur = begin; cur < end; cur++)
    {
        if (*cur > root_value)
            break;
    }
    printf("cur point to %d\n", *cur);
    int * p = cur;//如果指针变量的结果后面需要使用，那么就需要替换成新的变量
    for (; p < end; p++)
    {
        if (*p < root_value)
            return false;
    }
    bool left, right;
    if (cur - begin > 0)
        left = is_after_scan(begin, cur - 1);
    if (end - cur + 1 > 0)
	right = is_after_scan(cur, end - 1);
    if (left && right)
        return true;
    return false;
}

//二叉树中和为某一值得路径
std::vector<int> path;
int path_sum = 0;
int sum_path(binary_tree_node * root, int num)
{
    if (root == NULL)
        return 0;
    path_sum += root->m_nvalue;
    path.push_back(root->m_nvalue);
    //printf("path_sum = %d\n", path_sum);
    if (path_sum > num)
    {
        path.pop_back();
	path_sum -= root->m_nvalue;
	return 0;
    } 
    else if (path_sum == num)
    {
	int i;
	for (i = 0; i < path.size(); i++)
            printf("%d ", path[i]);
	printf("\n");
	path.pop_back();
	path_sum -= root->m_nvalue;
	return 0;
    }
    sum_path(root->m_pleft, num);
    sum_path(root->m_pright, num);
    path.pop_back();
    path_sum -= root->m_nvalue;
    return 0;
}
//二叉搜索树与反向链表
binary_tree_node * plast_node = NULL;
int convert_to_list_core(binary_tree_node * root)
{
    if (root == NULL)
        return 0;
    convert_to_list_core(root->m_pleft);
    if (plast_node != NULL)
        plast_node->m_pright = root;
    root->m_pleft = plast_node;
    plast_node = root;
    convert_to_list_core(root->m_pright);
    return 0;
}
binary_tree_node * convert_to_list(binary_tree_node * root)
{
    if (root == NULL)
        return NULL;
    convert_to_list_core(root);
    binary_tree_node * phead = root;
    while (phead->m_pleft != NULL)
        phead = phead->m_pleft;
    return phead;
}
//判断数据是否在二叉树中存在
bool exit_or_not(binary_tree_node * root, int a)
{
    if (root == NULL)
        return false;
    if (root->m_nvalue == a)
	return true;
    bool exit_in_left = exit_or_not(root->m_pleft, a);
    bool exit_in_right = exit_or_not(root->m_pright, a);
    return exit_in_left ? exit_in_left : exit_in_right; 
}

//二叉树的第一个公共节点的核心函数
binary_tree_node * the_first_common_node_core(binary_tree_node * root, int a, int b)
{
    if (root == NULL || root->m_nvalue == a || root->m_nvalue == b)
        return root;
    binary_tree_node * left = the_first_common_node_core(root->m_pleft, a, b);
    binary_tree_node * right = the_first_common_node_core(root->m_pright, a, b);

    if (left && right)
        return root;
    return left == NULL ? right : left;
}
//二叉树的公共祖先节点
binary_tree_node * the_first_common_node(binary_tree_node * root, int a, int b)
{
    if (root == NULL || !exit_or_not(root, a) || !exit_or_not(root, b))
        return NULL;
    return the_first_common_node_core(root, a, b);
}

int main()
{
    #ifdef DEBUG
    //int pre_order[8] = {1, 2, 4, 7, 3, 5, 6, 8};
    //int in_order[8] = {4, 7, 2, 1, 5, 3, 8, 6};
    //int pre_order[7] = {1, 2, 4, 6, 5, 7, 3};
    //int in_order[7] = {6, 4, 2, 5, 7, 1, 3};
    //int pre_order[8] = {5, 3, 2, 1, 4, 7, 6, 8};
    //int in_order[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int pre_order[9] = {1, 2, 4, 8, 5, 3, 6, 9, 7};
    int in_order[9] = {8, 4, 2, 5, 1, 6, 9, 3, 7};
    //int pre_order[5] = {10, 5, 4, 7, 12};
    //int in_order[5] = {4, 5, 7, 10, 12};
    //int in_order[7] = {4, 6, 8, 10, 12, 14, 16};
    //int pre_order[7] = {10, 6, 4, 8, 14, 12, 16};
    binary_tree_node * root = construct_binary_tree(pre_order, in_order, 9);
    if (root != NULL)
    {
        printf("in_order_scan:\n");
        in_order_scan(root);
        printf("\n");
        
	printf("inorder_scan_with_norecursive:\n");
        inorder_scan_with_norecursive(root);
        printf("\n");

	printf("print_binary_tree:\n");
	print_binary_tree(root);
	printf("\n");
/*
	printf("please enter two num:\n");
	int a , b;
	scanf("%d %d", &a, &b);
	binary_tree_node * common_node = the_first_common_node(root, a, b);
	if (common_node)
	    printf("the first common node is %d\n", common_node->m_nvalue);
	else 
            printf("the value doesn't all in binary_tree\n");

        printf("Tree depth is %d\n", tree_depth(root));
        result result_ret = max_distance(root);
	printf("the max distance is %d\n", result_ret.distance);

	if (judge_BST(root))
	    printf("this is a BST\n");
	else
	    printf("this is not a BST\n");

	result_avl result_avl_ret = judge_AVL(root);
	if (result_avl_ret.is_AVL)
	    printf("this is AVL\n");
	else
	    printf("this is not AVL\n");
        sum_path(root, 22);
*/
	binary_tree_node * phead = convert_to_list(root);
	if (phead != NULL)
	{
            printf("list : \n");
	    while (phead)
	    {
		printf("%d ", phead->m_nvalue);
		phead = phead->m_pright;
	    }
	    printf("\n");
	}
/*
	minitor_tree(root);
	in_order_scan(root);
        printf("\n");

        int list[] = {1, 3, 2, 5, 7, 6, 4};
        bool after_list = is_after_scan(list, list + 6);	
        if (after_list)
	    printf("this is an after scan\n");
	else
	    printf("this is not an after scan list\n");
	
        int pre_order[8] = {1, 2, 4, 7, 3, 5, 6, 9};
        int in_order[8] = {4, 7, 2, 1, 5, 3, 8, 9};
	binary_tree_node * root1 = root;
        binary_tree_node * root2 = construct_binary_tree(pre_order, in_order, 8);
	bool equal_test = is_equal(root1, root2);
	if (equal_test)
	    printf("%s\n", "root1 is equal to root2");
	else
  	printf("%s\n", "root1 is not equal to root2");
*/  
}

    #else

    int length;
    while (scanf("%d", &length))
    {
        int * pre_order = new int[length];
	for (int i = 0; i < length; i++)
	{
	    scanf("%d", &pre_order[i]);
	}
	int * in_order = new int [length];
	for (int i = 0; i < length; i++)
	{
	    scanf("%d", &in_order[i]);
	}
	binary_tree_node * root = construct_binary_tree(pre_order, in_order, length);
	in_order_scan(root);
	printf("\n");
    }
    #endif

    return 0;
}
