#ifndef DATABASE_H
#define DATABASE_H
#include <QCoreApplication>
/*���ݿ����ģ��*/
void showdatabases(QString user);//����Ļ�ϴ�ӡ��ǰ�û����������ݿ���
int createDBEntity(QString user,QString DBname);//�������ݿ�ʵ��
int renameDBEntity(QString user,QString newName,QString oldName);//���������ݿ�ʵ��
int dropDBEntity(QString user,QString DBname);//ɾ�����ݿ�ʵ��
int useDBEntity(QString user,QString DBname);//�򿪲�ʹ�����ݿ�
int initDBEntity(QString user,QString DBname);//��ʼ�����ݿ�
int backupDBEntity(QString user,QString DBname);//�������ݿ�
#endif // DATABASE_H
