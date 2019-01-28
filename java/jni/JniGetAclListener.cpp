/*
* //******************************************************************
* //
* // Copyright 2015 Samsung Electronics All Rights Reserved.
* //
* //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
* //
* // Licensed under the Apache License, Version 2.0 (the "License");
* // you may not use this file except in compliance with the License.
* // You may obtain a copy of the License at
* //
* //      http://www.apache.org/licenses/LICENSE-2.0
* //
* // Unless required by applicable law or agreed to in writing, software
* // distributed under the License is distributed on an "AS IS" BASIS,
* // WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* // See the License for the specific language governing permissions and
* // limitations under the License.
* //
* //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/
#include "JniGetAclListener.h"
#include "JniOcSecureResource.h"
#include "JniSecureUtils.h"

using namespace OC;

JniGetAclListener::JniGetAclListener(JNIEnv *env, jobject jListener,
    RemoveGetAclCallback removeGetAclListener)
{
    m_jwListener = env->NewWeakGlobalRef(jListener);
    m_removeGetAclListener = removeGetAclListener;
}

JniGetAclListener::~JniGetAclListener()
{
    LOGI("~JniGetAclListener()");
    if (m_jwListener)
    {
        jint ret = JNI_ERR;
        JNIEnv *env = GetJNIEnv(ret);
        if (nullptr == env)
        {
            return;
        }
        env->DeleteWeakGlobalRef(m_jwListener);
        if (JNI_EDETACHED == ret)
        {
            g_jvm->DetachCurrentThread();
        }
    }
}

void JniGetAclListener::GetAclResultListener(PMGetAclResult_t *result, int hasError)
{
    jint ret = JNI_ERR;
    JNIEnv *env = GetJNIEnv(ret);
    if (nullptr == env)
    {
        return;
    }

    jobject jListener = env->NewLocalRef(m_jwListener);
    if (!jListener)
    {
        checkExAndRemoveListener(env);
        if (JNI_EDETACHED == ret)
        {
            g_jvm->DetachCurrentThread();
        }
        return;
    }

    jclass clsL = env->GetObjectClass(jListener);

    if (!clsL)
    {
        checkExAndRemoveListener(env);
        if (JNI_EDETACHED == ret)
        {
            g_jvm->DetachCurrentThread();
        }
        return;
    }


    jobject jResult = JniSecureUtils::convertOCAclToJavaACL(env, result);
    if (!jResult)
    {
        checkExAndRemoveListener(env);
        if (JNI_EDETACHED == ret)
        {
            g_jvm->DetachCurrentThread();
        }
        return;
    }

    jmethodID midL = env->GetMethodID(clsL, "getAclListener", "(Lorg/iotivity/base/OicSecAcl;I)V");
    if (!midL)
    {
        checkExAndRemoveListener(env);
        if (JNI_EDETACHED == ret)
        {
            g_jvm->DetachCurrentThread();
        }
        return;
    }
    env->CallVoidMethod(jListener, midL, jResult, (jint)hasError);
    if (env->ExceptionCheck())
    {
        LOGE("Java exception is thrown");
    }

    checkExAndRemoveListener(env);
    if (JNI_EDETACHED == ret)
    {
        g_jvm->DetachCurrentThread();
    }
}

void JniGetAclListener::checkExAndRemoveListener(JNIEnv* env)
{
    if (env->ExceptionCheck())
    {
        jthrowable ex = env->ExceptionOccurred();
        env->ExceptionClear();
        m_removeGetAclListener(env, m_jwListener);
        env->Throw((jthrowable)ex);
    }
    else
    {
        m_removeGetAclListener(env, m_jwListener);
    }
}
