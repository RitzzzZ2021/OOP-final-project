#include "include/querymanager.h"
#include <QtTest>

class QueryManagerTest : public QObject {
    Q_OBJECT
public:
    QueryManagerTest() {}
private Q_SLOTS:
    void testCase1();
};

void QueryManagerTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(QueryManagerTest)

#include "QueryManager_Test.moc"
