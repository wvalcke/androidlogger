#include "LockHelper.h"

#include "LockHelper.h"
#include <QAndroidJniObject>
#include <QDebug>
#include "jni.h"

KeepAwakeHelper::KeepAwakeHelper()
{
    QAndroidJniObject::callStaticMethod<void>("org/bep/jni/ScreenLockInterface",
                                       "LockJni",
                                       "()V"
                                       );

}

KeepAwakeHelper::~KeepAwakeHelper()
{
    QAndroidJniObject::callStaticMethod<void>("org/bep/jni/ScreenLockInterface",
                                       "UnlockJni",
                                       "()V"
                                       );
}
