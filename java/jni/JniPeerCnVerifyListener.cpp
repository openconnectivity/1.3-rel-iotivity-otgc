/*
 * *****************************************************************
 *
 *  Copyright 2018 DEKRA Testing and Certification, S.A.U. All Rights Reserved.
 *
 * *****************************************************************
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 * *****************************************************************
 */
#include "JniPeerCnVerifyListener.h"
#include "oic_malloc.h"
#include "oic_string.h"

JniPeerCnVerifyListener::JniPeerCnVerifyListener(JNIEnv *env, jobject jListener)
{
    m_jgListener = env->NewGlobalRef(jListener);
}

JniPeerCnVerifyListener::~JniPeerCnVerifyListener()
{
    LOGI("~JniPeerCnVerifyListener()");
    if (m_jgListener)
    {
        jint ret = JNI_ERR;
        JNIEnv *env = GetJNIEnv(ret);
        if (NULL == env) return;
        env->DeleteGlobalRef(m_jgListener);
        if (JNI_EDETACHED == ret) g_jvm->DetachCurrentThread();
    }
}

CAResult_t JniPeerCnVerifyListener::peerCnVerifyCallback(const unsigned char *cn, size_t cnLen)
{
    jint ret = JNI_ERR;
    JNIEnv *env = GetJNIEnv(ret);

    if (NULL == env)
    {
        return CA_STATUS_FAILED;
    }

    jclass clsL = env->GetObjectClass(m_jgListener);

    if (!clsL)
    {
        if (JNI_EDETACHED == ret) g_jvm->DetachCurrentThread();
        return CA_STATUS_FAILED;
    }

    jmethodID midL = env->GetMethodID(clsL, "peerCnVerifyListener", "(Ljava/lang/String;)I");
    if (!midL)
    {
        if (JNI_EDETACHED == ret) g_jvm->DetachCurrentThread();
        return CA_STATUS_FAILED;
    }

    char *cnStr = (char*)OICMalloc(cnLen + 1);
    if (!cnStr)
    {
        LOGE("malloc failed");
        if (JNI_EDETACHED == ret) g_jvm->DetachCurrentThread();
        return CA_STATUS_FAILED;
    }
    OICStrcpy(cnStr, (cnLen+1), reinterpret_cast<const char*>(cn));

    CAResult_t result = (CAResult_t)env->CallIntMethod(m_jgListener, midL, env->NewStringUTF(cnStr));
    OICFree(cnStr);

    if (env->ExceptionCheck())
    {
        LOGE("Java exception is thrown");
        env->ExceptionClear();
    }

    if (JNI_EDETACHED == ret) g_jvm->DetachCurrentThread();
    return result;
}
