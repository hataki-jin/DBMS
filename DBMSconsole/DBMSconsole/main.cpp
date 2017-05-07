//�����ļ�
#include <QCoreApplication>
#include <iostream>
#include <vector>
#include "convert.h"
#include "database.h"
#include "index.h"
#include "record.h"
#include "table.h"
#include "user.h"
#include "sqlanalysis.h"
//�����ռ�
using namespace  std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    User user;
    User reg;
    reg.username="root";//ע���õ��û���
    reg.password="root";//ע���õ�����

    switch(regUser(reg))//TODO:������
    {
    case 0:
        cout<<"Registion success!"<<endl;
        break;
    case 1:
        cout<<"Registion failed because this user exists!"<<endl;
        break;
    case 2:
        cout<<"Registion failed because account or password is not valid!"<<endl;//�˺����5λ����1λ���������10λ����1λ��ֻ������ĸ�����ִ�Сд�����������
        break;
    case 3:
        cout<<"Registion failed because of system error!"<<endl;//һ�����ļ�������
        break;
    default:
        break;
    }

    while(1)
    {
        cout<<"Please input account:";//Ĭ���˺���root
        string u;
        cin>>u;
        user.username = QString::fromStdString(u);
        getchar();
        cout<<"Please input password:";//Ĭ��������root
        user.password = EnterPassword();
        if(JudgeUser(user))
        {
            cout<<"Login success!"<<endl;

            QString curuser = user.username;
            QString curDBname = "";
			while(1)
			{
                cout<<"sql>>";
				int sqlType;//sql��������ͣ������������ݿ⡢����������ֶε���ȷ������֮�����չ����﷨������
                string sql;//�����sql����
                vector<QString> sqlkey;
				
                getline(cin,sql);//TODO:��ʱû���ǻ��е����⣬��һ��SQL�������һ����д��ģ��ԷֺŽ�β
                QString qsql = stringtoqstring(sql);
                sqlType = sqlAnalysis(qsql,sqlkey);
                switch(sqlType)
				{
                case 0://�������ݿ�
                    if(createDBEntity(curuser,sqlkey.at(0))==1)
                        cout<<"Create database successfully!"<<endl;
                    else
                    {

                    }
                    break;
                case 1://���������ݿ�
                    if(renameDBEntity(curuser,sqlkey.at(0),sqlkey.at(1))==1)
                        cout<<"Rename database successfully!"<<endl;
                    else
                    {

                    }
                    break;
                case 2://ɾ�����ݿ�
                    if(dropDBEntity(curuser,sqlkey.at(0))==1)
                        cout<<"Drop database successfully!"<<endl;
                    else
                    {

                    }
                    break;
                case 3://ʹ�����ݿ�
                    if(useDBEntity(curuser,sqlkey.at(0),curDBname)==1)
                    {
                        cout<<"Database changed."<<endl;
                    }
                    else
                    {

                    }
                    break;
                case -1:
                    cout<<"syntax error!"<<endl;
                    break;
				default:
					break;
				}
			}
        }
        else
        {
            cout<<"Acount or passeord is not valid,please reenter..."<<endl;
        }
    }

    return a.exec();
}
