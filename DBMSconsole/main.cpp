//包含文件
#include <QCoreApplication>
#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <vector>
#include <set>
#include <QDebug>
//宏定义
#define UNLEN 5//用户名最大长度
#define PWDLEN 10//密码最大长度
//命名空间
using namespace  std;
//结构体
typedef struct
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
}Date;
typedef struct
{
    string name;//字段名
    string type;//类型
    int length;//长度
    int constraint[7];
    /*七种约束条件，值为0代表无，其余代表有
     * 0代表主键，1代表外键，2代表unique，
     * 3代表check（1代表检查值是否存在于set中，2代表检查值是否在最大和最小值之间，3代表是否在两日期范围中），
     * 4代表default（1代表整型，2代表字符串，3代表日期），
     * 5代表非空，
     * 6代表自增*/

    set<string> scope;//取值的集合
    Date mindate;//最早日期
    Date maxdate;//最晚日期
    int minvalue;//最小值
    int maxvalue;//最大值

    int defaultint;//默认整型
    string defaultchar;//默认字符串
    Date defaultdate;//默认日期
}Field;
//全局变量
int a[] = {4, 5, 3, 2, 4, 5, 1};//加密用整型数组
//功能函数
/*用户管理模块*/
string EnterPassword();//输入密码，返回值为输入的密码
bool JudgeUser(string username,string password);//判断用户名和密码是否存在、是否匹配
void encryption(string& c, int a[]);//对写入文件的密码进行加密操作
void decode(string& c,int a[]);//解密
int regUser(string username,string password);//注册用户

int sqlAnalysis(string sql,vector<string> &sqlkey);//解析sql语法并返回各部分内容
/*数据库管理模块*/
int showdatabases();//查看当前用户下所有数据库
int createDBEntity(string DBname);//创建数据库实体
int renameDBEntity(string newName,string oldName);//重命名数据库实体
int dropDBEntity(string DBname);//删除数据库实体
int useDBEntity(string DBname);//打开并使用数据库
int initDBEntity(string DBname);//初始化数据库
int backupDBEntity(string DBname);//备份数据库
/*表管理模块*/
int createTable(string TBname,string DBname,vector<Field> fields);//创建表
int dropTable(string TBname,string DBname);//删除表
int deleteField(string TBname,string DBname,string colname);//删除表中一列
int addField(string TBname,string DBname,Field col);//增加一列
int modifyCol(string TBname,string DBname,string oldname,string newname,string type,int length,bool notnull);//修改一列的名称及类型
int renameTable(string TBname,string DBname,string newname);//重命名表
int removePri(string TBname,string DBname);//删除主键
int addPri(string TBname,string DBname,string priname,vector<string> colnames);//为一到多列添加主键
/*记录管理模块*/
int insertRecord(string TBname,string DBname,vector<string> colnames);//插入记录TODO:
int updateRecord(string TBname,string DBname,string colname);//更新记录TODO:
int selectRecord(string TBname,string DBname,vector<string> colnames);//查询记录TODO:
int deleteRecord(string TBname,string DBname);//删除记录TODO:
/*索引管理模块*/
int createIndex(string TBname,string DBname,string indexname,vector<string> colnames);//建立索引
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    string username = "";
    string password = "";

    switch(regUser("zzz00","xyzzzzzz"))//TODO:测试用
    {
    case 0:
        cout<<"Registion success!"<<endl;
        break;
    case 1:
        cout<<"Registion failed because this user exists"<<endl;
        break;
    case 2:
        cout<<"Registion failed because account or password is not valid"<<endl;//账号最多5位最少1位，密码最多10位最少1位，只能由字母（区分大小写）和数字组成
        break;
    case 3:
        cout<<"Registion failed because of system error"<<endl;//一般是文件不存在
        break;
    default:
        break;
    }

    while(1)
    {
        cout<<"Please input account";//默认账号是root
        cin>>username;
        getchar();
        cout<<"Please input password";//默认密码是root
        password = EnterPassword();
        if(JudgeUser(username,password))
        {
            cout<<"Logon success"<<endl;
            string curDBname = "";
			while(1)
			{
				int sqlType;//sql命令的类型，包括创建数据库、创建表、添加字段等正确操作，之后可扩展添加语法错误检查
				string sql;//输入的sql命令
				vector<string> sqlkey;
				
				getline(cin,sql);//TODO:暂时没考虑换行的问题，即一句SQL语句是在一行中写完的，以分号结尾
                sqlType = sqlAnalysis(sql,sqlkey);
                switch(sqlType)
				{
                case 0: //创建数据库
                    switch(createDBEntity(sqlkey.at(1)))//TODO:
					{
					case 0:
                        cout<<"Create database success!"<<endl;
						break;
					default:
						break;
					}
					break;
                case 1: //重命名数据库，语法规则：RENAME database olddbname TO newdbname
                    switch(renameDBEntity(sqlkey.at(1), NULL))//TODO:
					{
					case 0:
                        cout<<"Rename database success!"<<endl;
						break;
					default:
						break;
					}
					break;
				case 2:
                    switch(dropDBEntity(sqlkey.at(1)))//TODO:
					{
					case 0:
                        cout<<"Delete database success!"<<endl;
						break;
					default:
						break;
					}
					break;
				case 3:
                    switch(useDBEntity(sqlkey.at(1)))//TODO:
					{
					case 0:
                        curDBname = useDBEntity(sqlkey.at(1));
                        cout<<"Change database success!"<<endl;
						break;
					default:
						break;
					}
					break;
				default:
					break;
				}
			}
        }
        else
        {
            cout<<"Acount or passeord is not valid,please reenter"<<endl;
        }
    }

    return a.exec();
}

string EnterPassword()
{
    char password[100];
    int index=0;
    while(1)
    {
        char ch;
        ch=getch();
        if(ch==8) //退格键
        {
            if(index!=0)
            {
                cout<<char(8)<<" "<<char(8);
                index--;
            }
        }
        else if(ch=='\r') //回车键
        {
            password[index]='\0';
            cout<<endl;
            break;
        }
        else if((ch<='Z'&&ch>='A')||(ch<='z'&&ch>='a')||(ch<='9'&&ch>='0'))//密码只支持英文字母（大小写均可）和数字
        {
            cout<<"*";
            password[index++]=ch;
        }
    }
    string p(password);
    return p;
}

bool JudgeUser(string username,string password)
{
    int usernum = 0;
    QString u,p;
    // 指定文件：
    QFile inputFile("./usernum.txt");
    // 只读打开：
    if(!inputFile.open(QIODevice::ReadOnly))
    {
        cout<<"Failed to open usernum.txt"<<endl;
        return false;
    }
    // 文本流：
    QTextStream in(&inputFile);
    // 将文本流读取到字符串中：
    QString line = in.readAll();
    // 关闭文本流：
    inputFile.close();
    usernum = line.toInt();
    QFile inputFile1("./user.txt");
    if(!inputFile1.open(QIODevice::ReadOnly))
    {
        cout<<"Failed to open user.txt"<<endl;
        return false;
    }
    QTextStream in1(&inputFile1);
    for(int i=0;i<usernum;i++)
    {
        u = in1.readLine();
        p = in1.readLine();
        string u1,p1;
        u1 = u.toStdString();
        p1 = p.toStdString();
        decode(p1,a);
        if(u1==username&&p1==password)
            return true;
    }
    inputFile1.close();
    return false;
}

void encryption(string& c, int a[]){

    for(int i = 0, j = 0; c[j];j++, i = (i + 1) % 7){

        c[j]+=a[i];

        c[j] %= 90;
    }
}

void decode(string& c,int a[]){

    for(int i = 0, j = 0; c[j];j++, i = (i + 1) % 7){

        c[j]-=a[i];

        if(c[j]<48)
        {
            c[j]+=90;
        }
    }
}

int regUser(string username,string password)
{
    if(username.size()>(unsigned)UNLEN||password.size()>(unsigned)PWDLEN) return 2;
    for(int i=0;(unsigned)i<username.size();i++)
    {
        if(!((username[i]<='z'&&username[i]>='a')||(username[i]<='Z'&&username[i]>='A')||(username[i]<='9'&&username[i]>='0'))) return 2;
    }
    for(int i=0;(unsigned)i<password.size();i++)
    {
        if(!((password[i]<='z'&&password[i]>='a')||(password[i]<='Z'&&password[i]>='A')||(password[i]<='9'&&password[i]>='0'))) return 2;
    }
    int usernum = 0;
    // 指定文件：
    QFile inputFile("./usernum.txt");
    // 只读打开：
    qDebug()<<QDir::currentPath();
    if(!inputFile.open(QIODevice::ReadOnly))
    {
        cout<<"Failed to open usernum.txt"<<endl;
        return 3;
    }
    // 文本流：
    QTextStream in(&inputFile);
    // 将文本流读取到字符串中：
    QString line = in.readAll();
    // 关闭文本流：
    inputFile.close();
    usernum = line.toInt();
    QFile inputFile1("./user.txt");
    if(!inputFile1.open(QIODevice::ReadOnly))
    {
        cout<<"Failed to open user.txt！"<<endl;
        return 3;
    }
    QTextStream in1(&inputFile1);
    for(int i=0;i<usernum;i++)
    {
        QString u,p;
        u = in1.readLine();
        p = in1.readLine();
        string u1;
        u1 = u.toStdString();
        if(u1==username)
            return 1;
    }
    inputFile1.close();


    QFile f("./usernum.txt");
    QFile f1("./user.txt");

    f1.open(QIODevice::Append|QIODevice::Text);
    f.open(QIODevice::WriteOnly);
    QTextStream qts3(&f);
    usernum++;
    QString qusernum = QString::number(usernum,10);
    qts3<<qusernum;
    f.flush();
    f.close();
    QTextStream qts2(&f1);
    QString u = QString::fromStdString(username);
    encryption(password,a);
    QString p = QString::fromStdString(password);
    qts2<<u<<endl;
    qts2<<p<<endl;
    f1.flush();
    f1.close();

    QDir *temp = new QDir;
    QString folder = "./";
    folder += QString::fromStdString(username);
    bool exist = temp->exists(folder);
    if(!exist)
    {
        bool ok = temp->mkdir(folder);
        if(ok) return 0;
        else return 3;
    }
}

int sqlAnalysis(string sql,vector<string> &sqlkey)
{
    return 0;
}

int createDBEntity(string DBname)
{
    return 0;
}

int renameDBEntity(string newName,string oldName)
{
    return 0;
}

int dropDBEntity(string DBname)
{
    return 0;
}

int useDBEntity(string DBname)
{
    return 0;
}

int initDBEntity(string DBname)//1代表初始化失败，0代表成功
{
	if(dropDBEntity(DBname)!=0) return 1;
	if(createDBEntity(DBname)!=0) return 1;
	return 0;
}

int backupDBEntity(string DBname)//备份数据库
{
    return 0;
}

int createTable(string TBname,string DBname,vector<Field> fields)//创建表
{
    return 0;
}

int dropTable(string TBname,string DBname)//删除表
{
     return 0;
}

int deleteField(string TBname,string DBname,string colname)//删除表中一列
{
    return 0;
}

int addField(string TBname,string DBname,Field col)//增加一列
{
    return 0;
}

int modifyCol(string TBname,string DBname,string oldname,string newname,string type,int length,bool notnull)//修改一列的名称及类型
{

}

int renameTable(string TBname,string DBname,string newname)//重命名表
{

}

int removePri(string TBname,string DBname)//删除主键
{

}

int addPri(string TBname,string DBname,string priname,vector<string> colnames)//为一到多列添加主键
{

}
