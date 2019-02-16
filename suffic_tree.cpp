#include<stdio.h>
#include<map>
#include<string>
#include<vector>
#include<iostream>

using namespace std;

class suffix_tree_node//后缀树节点类
{

    public:
        suffix_tree_node() {}//默认构造函数
        //递归插入后缀子串，原理同trie树的插入，s为要插入的字符串，index为s在主串中的位置
	void insert_string(string s, int index);
	//用递归法查询子串s，原理同trie树
	vector<int> get_indexes(string s);
        ~suffix_tree_node();
    private:
        map<char, suffix_tree_node*> children;//节点指针
        char value;//节点的字符值
        vector<int> indexes;//存储子字符串在s中的位置
};

void suffix_tree_node::insert_string(string s, int index)
{
    indexes.push_back(index);
    if (s.length() > 0)
    {
        value = s[0];
	suffix_tree_node * child = NULL;
	if (children.find(value) != children.end())
	{
	    child = children[value];
	}
	else
	{
	    child = new suffix_tree_node();
	    children[value] = child;
	}
	string remainder = s.substr(1);
	child->insert_string(remainder, index);
    }

}

vector<int> suffix_tree_node::get_indexes(string s)
{
    if (s.length() == 0)
        return indexes;
    char first = s[0];
    if (children.find(first) != children.end())
    {
        string remainder = s.substr(1);
	return children[first]->get_indexes(remainder);
    }
    else
    {
        vector<int> empty;
	return empty;
    }
}

suffix_tree_node::~suffix_tree_node()
{
    map<char, suffix_tree_node*>::iterator ite;
    for(ite = children.begin(); ite != children.end(); ite++)
        delete (ite->second);
}

class suffix_tree
{
    public:
        suffix_tree(string s);
	//查询字符串s在原串中的位置
	vector<int> get_indexes(string s);
	~suffix_tree();
    private:
	suffix_tree_node * root;
};

suffix_tree::suffix_tree(string s)
{
    root = new suffix_tree_node();
    for (int i = 0; i < s.length(); i++)
    {
        string suffix = s.substr(i);
	root->insert_string(suffix, i);
    }
}

vector<int> suffix_tree::get_indexes(string s)
{
    return root->get_indexes(s);
}

suffix_tree::~suffix_tree()
{
    if (root != NULL)
        delete root;
}

int main()
{
    string test_string = "mississippi";
    string string_list[] = {"is", "sip", "hi", "sis"};
    suffix_tree tree(test_string);
    for (int i = 0; i < 4; i++)
    {
        vector<int> li = tree.get_indexes(string_list[i]);
	if (li.size() != 0)
	{
	    cout<<string_list[i].c_str()<<" ";
	    for (int j = 0; j < li.size(); j++)
	        cout<<li[j]<<" ";
	    cout<<endl;
	}
    }
    return 0;
}


