#include <QWidget>
#include <QHBoxLayout>

class Galaxy : public QWidget
{
    Q_OBJECT
public:
    Galaxy();

private:
    QStringList getModulesNames();
    bool loadModule(QString name);

    const QString moduleDirName = "build/modules/"; // TODO : maybe rename 'build' directory 

    QHBoxLayout *lay = nullptr;
};