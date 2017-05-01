//�����ļ�
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
//�궨��
#define UNLEN 5//�û�����󳤶�
#define PWDLEN 10//������󳤶�
#define CT //������ĺ�
#define DT //ɾ����
//�����ռ�
using namespace  std;
//�ṹ��
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
    string name;//�ֶ���
    string type;//����
    int length;//����
    int constraint[7];
    /*����Լ��������ֵΪ0�����ޣ����������
     * 0����������1���������2����unique��
     * 3����check��1������ֵ�Ƿ������set�У�2������ֵ�Ƿ���������Сֵ֮�䣬3�����Ƿ��������ڷ�Χ�У���
     * 4����default��1�������ͣ�2�����ַ�����3�������ڣ���
     * 5����ǿգ�
     * 6��������*/

    set<string> scope;//ȡֵ�ļ���
    Date mindate;//��������
    Date maxdate;//��������
    int minvalue;//��Сֵ
    int maxvalue;//���ֵ

    int defaultint;//Ĭ������
    string defaultchar;//Ĭ���ַ���
    Date defaultdate;//Ĭ������
}Field;
//ȫ�ֱ���
int a[] = {4, 5, 3, 2, 4, 5, 1};//��������������
//���ܺ���
string EnterPassword();//�������룬����ֵΪ���������
bool JudgeUser(string username,string password);//�ж��û����������Ƿ���ڡ��Ƿ�ƥ��
void encryption(string& c, int a[]);//��д���ļ���������м��ܲ���
void decode(string& c,int a[]);//����
int regUser(string username,string password);//ע���û�
int sqlAnalysis(string sql,vector<string> &sqlkey);//����sql�﷨�����ظ���������
int createDBEntity(string DBname);//�������ݿ�ʵ��
int renameDBEntity(string newName,string oldName);//���������ݿ�ʵ��
int dropDBEntity(string DBname);//ɾ�����ݿ�ʵ��
int useDBEntity(string DBname);//�򿪲�ʹ�����ݿ�
int initDBEntity(string DBname);//��ʼ�����ݿ�
int backupDBEntity(string DBname);//�������ݿ�
int createTable(string TBname,string DBname,vector<Field> fields);//������
int dropTable(string TBname,string DBname);//ɾ����
int deleteField(string TBname,string DBname,string colname);//ɾ������һ��
int addField(string TBname,string DBname,Field col);//����һ��
int modifyCol(string TBname,string DBname,string oldname,string newname,string type,int length);//�޸�һ�е����Ƽ�����
int renameTable(string TBname,string DBname,string newname);//��������
int removePri(string TBname,string DBname);//ɾ������
int addPri(string TBname,string DBname,string priname,vector<string> colnames);//Ϊһ�������������
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    string username = "";
    string password = "";

    switch(regUser("zzz00","xyzzzzzz"))//TODO:������
    {
    case 0:
        cout<<"ע��ɹ���"<<endl;
        break;
    case 1:
        cout<<"���û����Ѿ�����,ע��ʧ�ܣ�"<<endl;
        break;
    case 2:
        cout<<"�û����������벻����Ҫ��ע��ʧ�ܣ�"<<endl;//�˺����5λ����1λ���������10λ����1λ��ֻ������ĸ�����ִ�Сд�����������
        break;
    case 3:
        cout<<"ϵͳ������ע��ʧ�ܣ�"<<endl;//һ�����ļ�������
        break;
    default:
        break;
    }

    while(1)
    {
        cout<<"�������˺ţ�";//Ĭ���˺���root
        cin>>username;
        getchar();
        cout<<"���������룺";//Ĭ��������root
        password = EnterPassword();
        if(JudgeUser(username,password))
        {
            cout<<"��¼�ɹ���"<<endl;
            string curDBname = "";
			while(1)
			{
				int sqlType;//sql��������ͣ������������ݿ⡢����������ֶε���ȷ������֮�����չ����﷨������
				string sql;//�����sql����
				vector<string> sqlkey;
				
				getline(cin,sql);//TODO:��ʱû���ǻ��е����⣬��һ��SQL�������һ����д��ģ��ԷֺŽ�β
                sqlType = sqlAnalysis(sql,sqlkey);
				switch()
				{
				case 0://�������ݿ�
                    switch(createDBEntity(sqlkey.at((1))))//TODO:
					{
					case 0:
						cout<<"�������ݿ�ɹ���"<<endl;
						break;
					default:
						break;
					}
					break;
				case 1://���������ݿ⣬�﷨����RENAME database olddbname TO newdbname
                    switch(renameDBEntity())//TODO:
					{
					case 0:
						cout<<"���������ݿ�ɹ���"<<endl;
						break;
					default:
						break;
					}
					break;
				case 2:
                    switch(dropDBEntity(sqlkey.at((1))))//TODO:
					{
					case 0:
						cout<<"ɾ�����ݿ�ɹ���"<<endl;
						break;
					default:
						break;
					}
					break;
				case 3:
                    switch(useDBEntity(sqlkey.at((1))))//TODO:
					{
					case 0:
                        curDBname = useDBEntity(sqlkey.at((1)));
						cout<<"�������ݿ�ɹ���"<<endl;
						break;
					default:
						break;
					}
					break;
				case CT:
					
					break;
				case DT:
					
					break;
				default:
					break;
				}
			}
        }
        else
        {
            cout<<"�˺Ż������������������������..."<<endl;
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
        if(ch==8) //�˸��
        {
            if(index!=0)
            {
                cout<<char(8)<<" "<<char(8);
                index--;
            }
        }
        else if(ch=='\r') //�س���
        {
            password[index]='\0';
            cout<<endl;
            break;
        }
        else if((ch<='Z'&&ch>='A')||(ch<='z'&&ch>='a')||(ch<='9'&&ch>='0'))//����ֻ֧��Ӣ����ĸ����Сд���ɣ�������
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
    // ָ���ļ���
    QFile inputFile("D:/2qt projects/DBMSconsole/usernum.txt");
    // ֻ���򿪣�
    if(!inputFile.open(QIODevice::ReadOnly))
    {
        cout<<"��usernum.txt�ļ�ʧ�ܣ�"<<endl;
        return false;
    }
    // �ı�����
    QTextStream in(&inputFile);
    // ���ı�����ȡ���ַ����У�
    QString line = in.readAll();
    // �ر��ı�����
    inputFile.close();
    usernum = line.toInt();
    QFile inputFile1("D:/2qt projects/DBMSconsole/user.txt");
    if(!inputFile1.open(QIODevice::ReadOnly))
    {
        cout<<"��user.txt�ļ�ʧ�ܣ�"<<endl;
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
    // ָ���ļ���
    QFile inputFile("D:/2qt projects/DBMSconsole/usernum.txt");
    // ֻ���򿪣�
    if(!inputFile.open(QIODevice::ReadOnly))
    {
        cout<<"��usernum.txt�ļ�ʧ�ܣ�"<<endl;
        return 3;
    }
    // �ı�����
    QTextStream in(&inputFile);
    // ���ı�����ȡ���ַ����У�
    QString line = in.readAll();
    // �ر��ı�����
    inputFile.close();
    usernum = line.toInt();
    QFile inputFile1("D:/2qt projects/DBMSconsole/user.txt");
    if(!inputFile1.open(QIODevice::ReadOnly))
    {
        cout<<"��user.txt�ļ�ʧ�ܣ�"<<endl;
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


    QFile f("D:/2qt projects/DBMSconsole/usernum.txt");
    QFile f1("D:/2qt projects/DBMSconsole/user.txt");

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
    QString folder = "D:/2qt projects/DBMSconsole/";
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
	
}

int createDBEntity(string DBname)
{
	
}

int renameDBEntity(string newName,string oldName)
{
	
}

int dropDBEntity(string DBname)
{
	
}

int useDBEntity(string DBname)
{
	
}

int initDBEntity(string DBname)//1�����ʼ��ʧ�ܣ�0����ɹ�
{
	if(dropDBEntity(DBname)!=0) return 1;
	if(createDBEntity(DBname)!=0) return 1;
	return 0;
}

int backupDBEntity(string DBname)//�������ݿ�
{

}

int createTable(string TBname,string DBname,vector<Field> fields)//������
{

}

int dropTable(string TBname,string DBname)//ɾ����
{

}

int deleteField(string TBname,string DBname,string colname)//ɾ������һ��
{

}

int addField(string TBname,string DBname,Field col)//����һ��
{

}

int modifyCol(string TBname,string DBname,string oldname,string newname,string type,int length)//�޸�һ�е����Ƽ�����
{

}

int renameTable(string TBname,string DBname,string newname)//��������
{

}

int removePri(string TBname,string DBname)//ɾ������
{

}

int addPri(string TBname,string DBname,string priname,vector<string> colnames)//Ϊһ�������������
{

}
