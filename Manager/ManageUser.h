#ifndef GLOBALUSER_H
#define GLOBALUSER_H

#include <QObject>
#include <QMap>
#include <QSharedPointer>
#include "UserInfo/UserInfo.h"
#include "UserInfo/COperateRoster.h"
#include "Client/Client.h"
#include "UserInfo/User.h"

class CManageUser : public QObject
{
    Q_OBJECT
public:
    explicit CManageUser(QObject *parent = 0);
    virtual ~CManageUser();

    /**
     * @brief 用户登录成功后调用,用于初始化工作  
     *
     * @param szId:登录用户名  
     * @return int
     */
    virtual int Init(QString szId);
    /**
     * @brief 用户登出时调用,用于清理工作   
     *
     * @return int
     */
    virtual int Clean();
    /**
     * @brief 设置内容修改标志  
     *
     * @param bModify
     * @return int
     */
    virtual int SetModify(bool bModify = true);

    /**
     * @brief 得到登录用户对象  
     *
     * @return QSharedPointer<CUserInfo>:登录用户对象  
     */
    virtual QSharedPointer<CUser> GetUserInfoLocale();
    /**
     * @brief 得到好友对象  
     *
     * @param szId:好友ID  
     * @return QSharedPointer<CUserInfo>:成功,返回好友对象.失败,返回空  
     */
    virtual QSharedPointer<CUser> GetUserInfoRoster(const QString &szId);

    /**
     * @brief 新增加一个空的好友对象，并把此好友对象插入到好友列表中  
     *
     * @param szId：新增加好的ID  
     * @return QSharedPointer<CUserInfo>:成功,返回好友对象.失败,返回空  
     */
    virtual QSharedPointer<CUser> AddUserInfoRoster(const QString &szId);

    /**
     * @brief 处理好友列表操作  
     *
     * @param pOperateRoster:操作类.派生于COperateRoster  
     * @param para:传递给COperateRoster::ProcessRoster  
     * @return int  
     */
    virtual int ProcessRoster(COperateRoster* pOperateRoster, void *para = NULL);
    /**
     * @brief 从好友列表中删除好友  
     *
     * @param szId  
     * @return int  
     */
    virtual int RemoveUserInfoRoster(const QString &szId);

    /**
     * @brief 新建立一个空的用户信息对象.由实现类实现.  
     *
     * @return QSharedPointer<CUserInfo>:用户信息对象  
     */
    virtual QSharedPointer<CUser> NewUser();
private:
    /**
     * @brief 从存储中加载信息  
     *
     * @param szLocaleJid  
     * @return int  
     */
    int LoadFromFile(QString szId);
    /**
     * @brief 保存信息到存储  
     *
     * @return int  
     */
    int SaveToStorage();
    virtual int LoadLocaleFromStorage(const QString &szId);
    virtual int SaveLocaleToStorage();
    virtual int LoadRosterFromStorage(QString szId);
    virtual int SaveRosterToStorage();

    /**
     * @brief 得到登录用户信息保存的文件,不同协议用不同的文件.需要实现类实现.  
     *
     * @param szId:登录用户id  
     * @return QString:保存信息的文件名  
     */
    virtual QString GetLocaleFile(const QString &szId);
    /**
     * @brief 得到保存好友信息的文件,不同协议用不同的文件.需要实现类实现.    
     *
     * @param szId:登录用户id  
     * @return QString:保存信息的文件名  
     */
    virtual QString GetRosterFile(const QString &szId);

protected:
    //本地用户信息  
    QSharedPointer<CUser> m_UserLocale;
    //好友信息列表  
    QMap<QString, QSharedPointer<CUser> > m_UseRoster;

protected:
    bool m_bModify; //标志内容是否修改  

signals:

public slots:

};

#endif // GLOBALUSER_H
