#ifndef SQLITEHELPER_H
#define SQLITEHELPER_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QHash>
#include <QString>
#include <QVariant>

class SqliteHelper
{
public:
    SqliteHelper();
    ///
    /// \brief OpenSqlite 打开数据库
    /// \param dbName 数据库名
    /// \param connectName 连接名
    /// \return
    ///
    bool OpenSqlite(const QString &dbName,const QString &connectName);
    ///
    /// \brief CloseSqlite 关闭数据库
    /// \return
    ///
    void CloseSqlite();

    /**
     * @brief getConnectName 获取连接名
     * @return
     */
    QString getConnectName() const;

    /**
     * @brief isExistTable 判断数据表是否存在
     * @param tableName 数据表名
     * @return
     */
    bool isExistTable(const QString &tableName);

    /**
     * @brief createTable 创建数据表
     * @param tableName 数据表名
     * @param fields 字段(字段名和类型，如{"name", "varchar(5)"})
     * @param pks 主键
     * @return
     */
    bool createTable(const QString &tableName, const QHash<QString, QString> &fields, const QList<QString> &pks);

    /**
     * @brief selectData 选择数据(适用于单表选择)
     * @param tableName 数据表名
     * @param fields 选择字段
     * @param data [OUT]数据(按fields的顺序)
     * @return
     */
    bool selectData(const QString &tableName, const QList<QString> &fields, QList<QVariantList> &data);

    /**
     * @brief selectData 选择数据(适用于单表选择)
     * @param tableName 数据表名
     * @param fields 选择字段
     * @param whereConditions where条件
     * @param data [OUT]数据(按fields的顺序)
     * @return
     */
    bool selectData(const QString &tableName, const QList<QString> &fields, const QHash<QString, QVariant> &whereConditions,
                    QList<QVariantList> &data);

    /**
     * @brief selectDataBySql 选择数据(通过sql查询, 多表联合查询)
     * @param sql select语句
     * @param fields 选择字段
     * @param data [OUT]数据(按fields的顺序)
     * @return
     */
    bool selectDataBySql(const QString &sql, const QList<QString> &fields, QList<QVariantList> &data);

    /**
     * @brief insertRowData 插入行数据
     * @param tableName 数据表名
     * @param fields 插入字段
     * @param data 插入数据(数据与字段的顺序需一致)
     * @return
     */
    bool insertRowData(const QString &tableName, const QList<QString> &fields, const QVariantList &data);

    /**
     * @brief insertRowsData 插入多行数据
     * @param tableName 数据表名
     * @param fields 字段
     * @param data 插入数据(数据与字段的顺序需一致)
     * @return
     */
    bool insertRowsData(const QString &tableName, const QList<QString> &fields, const QList<QVariantList> &data);

    /**
     * @brief updateData 更新数据
     * @param tableName 数据表名
     * @param data 更新的字段数据(字段名和值，如{"age", 27})
     * @param whereConditions where条件(字段名和值，如{"age", 27})
     * @return
     */
    bool updateData(const QString &tableName, const QHash<QString, QVariant> &data,
                    const QHash<QString, QVariant> &whereConditions);

    /**
     * @brief deleteData 删除数据
     * @param tableName 数据表名
     * @param whereConditions where条件(字段名和值，如{"age", 27})
     * @return
     */
    bool deleteData(const QString &tableName, const QHash<QString, QVariant> &whereConditions);

    /**
     * @brief exec 执行sql语句
     * @param sql sql语句
     * @return 执行结果
     */
    bool exec(const QString &sql);

    /**
     * @brief hasTransactions 是否支持事务
     * @return
     */
    bool hasTransactions();

    /**
     * @brief transaction 开启事务
     * @return
     */
    bool transaction();

    /**
     * @brief commit 事务提交
     * @return
     */
    bool commit();

    /**
     * @brief rollback 事务回滚
     * @return
     */
    bool rollback();

    /**
     * @brief size 记录数量(在执行select语句后，可用该函数获取select的大小)
     * @return
     */
    int size();

    /**
     * @brief getTableFieldsInfo 获取数据表字段
     * @param tableName 数据表名
     * @param fieldsName [OUT]字段
     * @return
     */
    bool getTableFieldsInfo(const QString &tableName, QList<QString> &fieldsName);

    /**
     * @brief lastQuerySql 获取最新一次执行的sql语句
     * @return
     */
    QString lastQuerySql();

    /**
     * @brief lastError 获取最新的错误信息
     * @return 错误信息
     */
    QString lastError() const;

private:
    /**
     * @brief checkTableInfo 校验数据表信息(数据表和字段是否存在)
     * @param tableName 数据表名
     * @param fields 字段
     * @return
     */
    bool checkTableInfo(const QString &tableName, const QList<QString> &fields);


protected:
    QSqlDatabase sqlDb;
    QString m_connectName;
    QSqlQuery m_query;
    QString m_lastError;
};

#endif // SQLITEHELPER_H
