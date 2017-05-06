#ifndef TABLE_H
#define TABLE_H
#include <vector>
#include <set>
#include <QCoreApplication>
using namespace std;
typedef struct
{
    QString name;//�ֶ���
    QString type;//�ֶ�����
}Field;
typedef struct
{
    QString name;//Լ��������
    int type;//Լ���������ͣ�0����������1���������2����unique��3����not null��4����check��5����default
    vector<QString> colnos;//ʩ��Լ�����У�����������ڶ���

    //�����Ҫ
    QString outertable;//�ο��ı���
    QString outerprino;//�ο�������

    //check��Ҫ
    int checktype;//0�����������ͷ�Χ������������Сֵ��1��������ɢ�ͷ�Χ���ü��ϱ�ʾ��ֵ�Ӽ��ϵ�Ԫ����ѡ��
    QString max;//���ֵ
    QString min;//��Сֵ
    set<QString> valueset;//ȡֵ�ļ���

    //defalut��Ҫ
    QString defaultvalue;//Ĭ��ֵ
}Constraint;
/*�����ģ��*/
void showtables(QString user,QString DBname);//����Ļ�ϴ�ӡ��ǰ�û���ǰ���ݿ��µ����б���
int createTable(QString user,QString DBname,QString TBname,vector<Field> fields,vector<Constraint> constraints);//������
int dropTable(QString user,QString DBname,QString TBname);//ɾ����
int deleteField(QString user,QString DBname,QString TBname,QString col);//ɾ������һ��
int addField(QString user,QString DBname,QString TBname,Field col,bool notnull);//����һ�У�ֻ������ӷǿ�Լ��������true������ӣ�false�������
int modifyCol(QString user,QString DBname,QString oldname,QString newname,QString type,bool notnull);//�޸�һ�е����Ƽ����ͣ�ֻ������ӷǿ�Լ��������true������ӣ�false�������
int renameTable(QString user,QString DBname,QString oldname,QString newname);//��������
int removePri(QString user,QString DBname,QString TBname);//ɾ������
int addPri(QString user,QString DBname,QString TBname,Constraint primarykey);//Ϊһ�������������
#endif // TABLE_H
