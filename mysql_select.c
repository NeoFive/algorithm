#include<stdlib.h>
#include<stdio.h>

#include "mysql.h"

MYSQL my_connection, *conn_ret;//连接句柄
MYSQL_RES * res_ptr;//select 查询返回结果句柄
MYSQL_ROW sqlrow;//select 查询返回数据的行数

void display_header();
void display_row();

int main(int arg, char * argv[])
{
    int res;//返回值
    int first_row = 1;//只有第一行使用diaplay_header()函数

    mysql_init(&my_connection);//初始化连接，不采用动态结构，因为后面要使用my_connection进行错误分析

    conn_ret = mysql_real_connect(&my_connection, "localhost", "rick", "123456", "foo", 0, NULL, 0);//建立连接
    if (conn_ret == NULL)
    {
        fprintf(stderr, "connection failed\n");
	if (mysql_errno(&my_connection))//错误检测
	{
	    fprintf(stderr, "connection error %d: %s\n", mysql_errno(&my_connection), mysql_error(&my_connection));
	}
	exit(EXIT_FAILURE);
    }
    printf("connection success\n");

    res = mysql_query(&my_connection, "select childno, fname, age from children where age > 20");//查询
    if (res)
    {
	fprintf(stderr, "select error : %s\n", mysql_error(&my_connection));
        exit(EXIT_FAILURE);
    }

    res_ptr = mysql_use_result(&my_connection);//取得查询结果
    if (res_ptr == NULL)
    {
        if (mysql_errno(&my_connection))
	    fprintf(stderr, "mysql use result error %d : %s\n", mysql_errno(&my_connection), mysql_error(&my_connection));
        exit(EXIT_FAILURE);	
    }
    
    while ((sqlrow = mysql_fetch_row(res_ptr)))//一次取得查询结果的一行
    {
        if (first_row)
	{
            display_header();//显示行信息
	    first_row = 0;
        }
	display_row();//显示数据信息
     }
    //mysql_fetch_row 当数据取完或者发生错误时，返回NULL，因此这里要对错误进行检测
    if (mysql_errno(&my_connection))
        fprintf(stderr, "Retrive error : %s\n", mysql_error(&my_connection));
    mysql_free_result(res_ptr);//清除查询结果
    mysql_close(&my_connection);//关闭连接
    return EXIT_SUCCESS;
}

void display_header()
{
    MYSQL_FIELD * field_ptr;

    printf("column details : \n");
    while ((field_ptr = mysql_fetch_field(res_ptr)) != NULL)//取得字段
    {
        printf("\t Name : %s\n", field_ptr->name);
	printf("\t Type :");
	if (IS_NUM(field_ptr->type))
	    printf("Numeric field\n");
	else
        {
	    switch (field_ptr->type)
	    {
	        case FIELD_TYPE_VAR_STRING:
		    printf("VARCHAR\n");
		    break;
		case FIELD_TYPE_LONG:
		    printf("LONG\n");
		    break;
		default:
		    printf("Type is %d, check in mysql_com.h", field_ptr->type);
	    }
	}
	printf("\t Max width %ld\n", field_ptr->length);
	if (field_ptr->flags & AUTO_INCREMENT_FLAG)
	    printf("\t Auto increment\n");
	printf("\n");
    }
}

void display_row()
{
    unsigned int field_count;
    field_count = 0;
    while (field_count < mysql_field_count(&my_connection))//取得一行有多少字段
    {
        if (sqlrow[field_count])
	    printf("%s ", sqlrow[field_count]);
	else
	    printf("NULL");
	field_count++;
    }
    printf("\n");
}
