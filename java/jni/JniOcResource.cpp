/*
* //******************************************************************
* //
* // Copyright 2015 Intel Corporation.
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

#include "JniOcResource.h"
#include "JniOcRepresentation.h"
#include "JniUtils.h"

using namespace OC;

JniOcResource::JniOcResource(std::shared_ptr<OCResource> resource)
    : m_sharedResource(resource)
{
}

JniOcResource::~JniOcResource()
{
    LOGD("~JniOcResource()");

    m_sharedResource = nullptr;

    jint envRet = JNI_ERR;
    JNIEnv *env = GetJNIEnv(envRet);
    if (nullptr == env)
    {
        return;
    }

    m_onGetManager.removeAllListeners(env);
    m_onPutManager.removeAllListeners(env);
    m_onPostManager.removeAllListeners(env);
    m_onDeleteManager.removeAllListeners(env);
    m_onObserveManager.removeAllListeners(env);
#ifdef WITH_MQ
    m_onFoundTopicResourceManager.removeAllListeners(env);
    m_onSubcribeTopicManager.removeAllListeners(env);
#endif

    if (JNI_EDETACHED == envRet)
    {
        g_jvm->DetachCurrentThread();
    }
}

OCStackResult JniOcResource::get(JNIEnv* env, const QueryParamsMap &queryParametersMap, jobject jListener)
{
    JniOnGetListener *onGetListener = addOnGetListener(env, jListener);

    GetCallback getCallback = [onGetListener](
        const HeaderOptions& opts,
        const OCRepresentation& rep,
        const int eCode)
    {
        onGetListener->onGetCallback(opts, rep, eCode);
    };

    OCStackResult ret = OC_STACK_ERROR;
    if (m_sharedResource)
    {
        ret = m_sharedResource->get(queryParametersMap, getCallback);
    }
    return ret;
}

OCStackResult JniOcResource::get(JNIEnv* env, const QueryParamsMap &queryParametersMap, jobject jListener,
    QualityOfService QoS)
{
    JniOnGetListener *onGetListener = addOnGetListener(env, jListener);

    GetCallback getCallback = [onGetListener](const HeaderOptions& opts, const OCRepresentation& rep,
        const int eCode)
    {
        onGetListener->onGetCallback(opts, rep, eCode);
    };

    OCStackResult ret = OC_STACK_ERROR;
    if (m_sharedResource)
    {
        ret = m_sharedResource->get(queryParametersMap, getCallback, QoS);
    }
    return ret;
}

OCStackResult JniOcResource::get(
    JNIEnv* env,
    const std::string &resourceType,
    const std::string &resourceInterface,
    const QueryParamsMap &queryParametersMap,
    jobject jListener)
{
    JniOnGetListener *onGetListener = addOnGetListener(env, jListener);

    GetCallback getCallback = [onGetListener](const HeaderOptions& opts,
        const OCRepresentation& rep, const int eCode)
    {
        onGetListener->onGetCallback(opts, rep, eCode);
    };

    OCStackResult ret = OC_STACK_ERROR;
    if (m_sharedResource)
    {
        ret = m_sharedResource->get(resourceType, resourceInterface, queryParametersMap,
        getCallback);
    }
    return ret;
}

OCStackResult JniOcResource::get(JNIEnv* env, const std::string &resourceType,
    const std::string &resourceInterface, const QueryParamsMap &queryParametersMap,
    jobject jListener, QualityOfService QoS)
{
    JniOnGetListener *onGetListener = addOnGetListener(env, jListener);

    GetCallback getCallback = [onGetListener](const HeaderOptions& opts,
        const OCRepresentation& rep, const int eCode)
    {
        onGetListener->onGetCallback(opts, rep, eCode);
    };

    OCStackResult ret = OC_STACK_ERROR;
    if (m_sharedResource)
    {
        ret = m_sharedResource->get(resourceType, resourceInterface, queryParametersMap,
        getCallback, QoS);
    }
    return ret;
}

OCStackResult JniOcResource::put(JNIEnv* env, const OCRepresentation &representation,
    const QueryParamsMap &queryParametersMap, jobject jListener)
{
    JniOnPutListener *onPutListener = addOnPutListener(env, jListener);

    PutCallback putCallback = [onPutListener](const HeaderOptions& opts,
        const OCRepresentation& rep, const int eCode)
    {
        onPutListener->onPutCallback(opts, rep, eCode);
    };

    OCStackResult ret = OC_STACK_ERROR;
    if (m_sharedResource)
    {
        ret = m_sharedResource->put(representation, queryParametersMap, putCallback);
    }
    return ret;
}

OCStackResult JniOcResource::put(JNIEnv* env, const OCRepresentation &representation,
    const QueryParamsMap &queryParametersMap, jobject jListener, QualityOfService QoS)
{
    JniOnPutListener *onPutListener = addOnPutListener(env, jListener);

    PutCallback putCallback = [onPutListener](const HeaderOptions& opts,
        const OCRepresentation& rep, const int eCode)
    {
        onPutListener->onPutCallback(opts, rep, eCode);
    };

    OCStackResult ret = OC_STACK_ERROR;
    if (m_sharedResource)
    {
        ret = m_sharedResource->put(representation, queryParametersMap, putCallback, QoS);
    }
    return ret;
}

OCStackResult JniOcResource::put(JNIEnv* env, const std::string &resourceType,
    const std::string &resourceInterface, const OCRepresentation &representation,
    const QueryParamsMap &queryParametersMap, jobject jListener)
{
    JniOnPutListener *onPutListener = addOnPutListener(env, jListener);

    PutCallback putCallback = [onPutListener](const HeaderOptions& opts,
        const OCRepresentation& rep, const int eCode)
    {
        onPutListener->onPutCallback(opts, rep, eCode);
    };

    OCStackResult ret = OC_STACK_ERROR;
    if (m_sharedResource)
    {
        ret = m_sharedResource->put(resourceType, resourceInterface, representation,
        queryParametersMap, putCallback);
    }
    return ret;
}

OCStackResult JniOcResource::put(JNIEnv* env, const std::string &resourceType,
    const std::string &resourceInterface, const OCRepresentation &representation,
    const QueryParamsMap &queryParametersMap, jobject jListener, QualityOfService QoS)
{
    JniOnPutListener *onPutListener = addOnPutListener(env, jListener);

    PutCallback putCallback = [onPutListener](const HeaderOptions& opts,
        const OCRepresentation& rep, const int eCode)
    {
        onPutListener->onPutCallback(opts, rep, eCode);
    };

    OCStackResult ret = OC_STACK_ERROR;
    if (m_sharedResource)
    {
        ret = m_sharedResource->put(resourceType, resourceInterface, representation,
        queryParametersMap, putCallback, QoS);
    }
    return ret;
}

OCStackResult JniOcResource::post(JNIEnv* env, const OCRepresentation &representation,
    const QueryParamsMap &queryParametersMap, jobject jListener)
{
    JniOnPostListener *onPostListener = addOnPostListener(env, jListener);

    PostCallback postCallback = [onPostListener](const HeaderOptions& opts,
        const OCRepresentation& rep, const int eCode)
    {
        onPostListener->onPostCallback(opts, rep, eCode);
    };

    OCStackResult ret = OC_STACK_ERROR;
    if (m_sharedResource)
    {
        ret = m_sharedResource->post(representation, queryParametersMap, postCallback);
    }
    return ret;
}

OCStackResult JniOcResource::post(JNIEnv* env, const OCRepresentation &representation,
    const QueryParamsMap &queryParametersMap, jobject jListener, QualityOfService QoS)
{
    JniOnPostListener *onPostListener = addOnPostListener(env, jListener);

    PostCallback postCallback = [onPostListener](const HeaderOptions& opts,
        const OCRepresentation& rep, const int eCode)
    {
        onPostListener->onPostCallback(opts, rep, eCode);
    };

    OCStackResult ret = OC_STACK_ERROR;
    if (m_sharedResource)
    {
        ret = m_sharedResource->post(representation, queryParametersMap, postCallback, QoS);
    }
    return ret;
}

OCStackResult JniOcResource::post(JNIEnv* env, const std::string &resourceType,
    const std::string &resourceInterface, const OCRepresentation &representation,
    const QueryParamsMap &queryParametersMap, jobject jListener)
{
    JniOnPostListener *onPostListener = addOnPostListener(env, jListener);

    PostCallback postCallback = [onPostListener](const HeaderOptions& opts,
        const OCRepresentation& rep, const int eCode)
    {
        onPostListener->onPostCallback(opts, rep, eCode);
    };

    OCStackResult ret = OC_STACK_ERROR;
    if (m_sharedResource)
    {
        ret = m_sharedResource->post(resourceType, resourceInterface, representation,
        queryParametersMap, postCallback);
    }
    return ret;
}

OCStackResult JniOcResource::post(JNIEnv* env, const std::string &resourceType,
    const std::string &resourceInterface, const OCRepresentation &representation,
    const QueryParamsMap &queryParametersMap, jobject jListener, QualityOfService QoS)
{
    JniOnPostListener *onPostListener = addOnPostListener(env, jListener);

    PostCallback postCallback = [onPostListener](const HeaderOptions& opts,
        const OCRepresentation& rep, const int eCode)
    {
        onPostListener->onPostCallback(opts, rep, eCode);
    };

    OCStackResult ret = OC_STACK_ERROR;
    if (m_sharedResource)
    {
        ret = m_sharedResource->post(resourceType, resourceInterface, representation,
        queryParametersMap, postCallback, QoS);
    }
    return ret;
}

OCStackResult JniOcResource::deleteResource(JNIEnv* env, jobject jListener)
{
    JniOnDeleteListener *onDeleteListener = addOnDeleteListener(env, jListener);

    DeleteCallback deleteCallback = [onDeleteListener](const HeaderOptions& opts,
        const int eCode)
    {
        onDeleteListener->onDeleteCallback(opts, eCode);
    };

    OCStackResult ret = OC_STACK_ERROR;
    if (m_sharedResource)
    {
        ret = m_sharedResource->deleteResource(deleteCallback);
    }
    return ret;
}

OCStackResult JniOcResource::deleteResource(JNIEnv* env, jobject jListener, QualityOfService QoS)
{
    JniOnDeleteListener *onDeleteListener = addOnDeleteListener(env, jListener);

    DeleteCallback deleteCallback = [onDeleteListener](const HeaderOptions& opts, const int eCode)
    {
        onDeleteListener->onDeleteCallback(opts, eCode);
    };

    OCStackResult ret = OC_STACK_ERROR;
    if (m_sharedResource)
    {
        ret = m_sharedResource->deleteResource(deleteCallback, QoS);
    }
    return ret;
}

OCStackResult JniOcResource::observe(JNIEnv* env, ObserveType observeType,
    const QueryParamsMap &queryParametersMap, jobject jListener)
{
    JniOnObserveListener *onObserveListener = addOnObserveListener(env, jListener);

    ObserveCallback observeCallback = [onObserveListener](const HeaderOptions& opts,
        const OCRepresentation& rep, const int& eCode, const int& sequenceNumber)
    {
        onObserveListener->onObserveCallback(opts, rep, eCode, sequenceNumber);
    };

    OCStackResult ret = OC_STACK_ERROR;
    if (m_sharedResource)
    {
        ret = m_sharedResource->observe(observeType, queryParametersMap, observeCallback);
    }
    return ret;
}

OCStackResult JniOcResource::observe(JNIEnv* env, ObserveType observeType,
    const QueryParamsMap &queryParametersMap, jobject jListener, QualityOfService QoS)
{
    JniOnObserveListener *onObserveListener = addOnObserveListener(env, jListener);

    ObserveCallback observeCallback = [onObserveListener](const HeaderOptions& opts,
        const OCRepresentation& rep, const int& eCode, const int& sequenceNumber)
    {
        onObserveListener->onObserveCallback(opts, rep, eCode, sequenceNumber);
    };

    OCStackResult ret = OC_STACK_ERROR;
    if (m_sharedResource)
    {
        ret = m_sharedResource->observe(observeType, queryParametersMap, observeCallback, QoS);
    }
    return ret;
}

OCStackResult JniOcResource::cancelObserve(JNIEnv* env, QualityOfService qos)
{
    // In Low case, after delete the callback and send empty message when client receive the notify.
    // But TCP does not support EMPTY message.
    if ((CT_ADAPTER_IP & connectivityType()) && QualityOfService::HighQos != qos)
    {
        this->m_onObserveManager.removeAllListeners(env);
    }
    OCStackResult ret = OC_STACK_ERROR;
    if (m_sharedResource)
    {
        ret = m_sharedResource->cancelObserve(qos);
    }
    return ret;
}

void JniOcResource::setHeaderOptions(const HeaderOptions &headerOptions)
{
    m_sharedResource->setHeaderOptions(headerOptions);
}

void JniOcResource::unsetHeaderOptions()
{
    m_sharedResource->unsetHeaderOptions();
}

std::string JniOcResource::host()
{
    return m_sharedResource->host();
}

std::vector< std::string > JniOcResource::getAllHosts() const
{
    return m_sharedResource->getAllHosts();
}

std::string JniOcResource::setHost(const std::string& host)
{
    return m_sharedResource->setHost(host);
}
std::string JniOcResource::uri()
{
    return m_sharedResource->uri();
}

OCConnectivityType JniOcResource::connectivityType() const
{
    return m_sharedResource->connectivityType();
}


bool JniOcResource::isObservable()
{
    return m_sharedResource->isObservable();
}

std::vector< std::string > JniOcResource::getResourceTypes() const
{
    return m_sharedResource->getResourceTypes();
}

std::vector< std::string > JniOcResource::getResourceInterfaces(void) const
{
    return m_sharedResource->getResourceInterfaces();
}

OCResourceIdentifier JniOcResource::uniqueIdentifier() const
{
    return m_sharedResource->uniqueIdentifier();
}

std::string JniOcResource::sid() const
{
    return m_sharedResource->sid();
}

JniOnGetListener* JniOcResource::addOnGetListener(JNIEnv* env, jobject jListener)
{
    return this->m_onGetManager.addListener(env, jListener, this);
}

JniOnPutListener* JniOcResource::addOnPutListener(JNIEnv* env, jobject jListener)
{
    return this->m_onPutManager.addListener(env, jListener, this);
}

JniOnPostListener* JniOcResource::addOnPostListener(JNIEnv* env, jobject jListener)
{
    return this->m_onPostManager.addListener(env, jListener, this);
}

JniOnDeleteListener* JniOcResource::addOnDeleteListener(JNIEnv* env, jobject jListener)
{
    return this->m_onDeleteManager.addListener(env, jListener, this);
}

JniOnObserveListener* JniOcResource::addOnObserveListener(JNIEnv* env, jobject jListener)
{
    return this->m_onObserveManager.addListener(env, jListener, this);
}

void JniOcResource::removeOnGetListener(JNIEnv* env, jobject jListener)
{
    this->m_onGetManager.removeListener(env, jListener);
}

void JniOcResource::removeOnPutListener(JNIEnv* env, jobject jListener)
{
    this->m_onPutManager.removeListener(env, jListener);
}

void JniOcResource::removeOnPostListener(JNIEnv* env, jobject jListener)
{
    this->m_onPostManager.removeListener(env, jListener);
}

void JniOcResource::removeOnDeleteListener(JNIEnv* env, jobject jListener)
{
    this->m_onDeleteManager.removeListener(env, jListener);
}

void JniOcResource::removeOnObserveListener(JNIEnv* env, jobject jListener)
{
    this->m_onObserveManager.removeListener(env, jListener);
}

#ifdef WITH_MQ
JniOnMQTopicFoundListener* JniOcResource::addOnTopicFoundListener(JNIEnv* env, jobject jListener)
{
    return this->m_onFoundTopicResourceManager.addListener(env, jListener, this);
}

void JniOcResource::removeOnTopicFoundListener(JNIEnv* env, jobject jListener)
{
    this->m_onFoundTopicResourceManager.removeListener(env, jListener);
}

JniOnMQSubscribeListener* JniOcResource::addOnMQTopicSubscribeListener(JNIEnv* env, jobject jListener)
{
    return this->m_onSubcribeTopicManager.addListener(env, jListener, this);
}

void JniOcResource::removeOnMQTopicSubscribeListener(JNIEnv* env, jobject jListener)
{
    this->m_onSubcribeTopicManager.removeListener(env, jListener);
}
#endif

std::shared_ptr<OCResource> JniOcResource::getOCResource()
{
    return this->m_sharedResource;
}

JniOcResource* JniOcResource::getJniOcResourcePtr(JNIEnv *env, jobject thiz)
{
    JniOcResource *resource = GetHandle<JniOcResource>(env, thiz);
    if (env->ExceptionCheck())
    {
        LOGE("Failed to get native handle from OcResource");
    }
    if (!resource)
    {
        ThrowOcException(JNI_NO_NATIVE_POINTER, "");
    }
    return resource;
}

#ifdef WITH_MQ
OCStackResult JniOcResource::discoveryMQTopics(JNIEnv* env,
    const QueryParamsMap &queryParametersMap, jobject jListener, QualityOfService QoS)
{
    JniOnMQTopicFoundListener *onTopicFoundListener = addOnTopicFoundListener(env, jListener);

    MQTopicCallback findCallback = [onTopicFoundListener](const int& eCode,
            const std::string& uri, std::shared_ptr<OCResource> resource)
    {
        onTopicFoundListener->foundTopicCallback(eCode, uri, resource);
    };

    OCStackResult ret = OC_STACK_ERROR;
    if (m_sharedResource)
    {
        ret = m_sharedResource->discoveryMQTopics(queryParametersMap, findCallback, QoS);
    }
    return ret;
}

OCStackResult JniOcResource::createMQTopic(JNIEnv* env,
    const OCRepresentation &representation, const std::string &targetUri,
    const QueryParamsMap &queryParametersMap, jobject jListener, QualityOfService QoS)
{
    JniOnMQTopicFoundListener *onTopicCreatedListener = addOnTopicFoundListener(env, jListener);

    MQTopicCallback createCallback = [onTopicCreatedListener](const int& eCode,
            const std::string& uri, std::shared_ptr<OCResource> resource)
    {
        onTopicCreatedListener->createdTopicCallback(eCode, uri, resource);
    };

    OCStackResult ret = OC_STACK_ERROR;
    if (m_sharedResource)
    {
        ret = m_sharedResource->createMQTopic(representation, targetUri,
                                           queryParametersMap,
                                           createCallback, QoS);
    }
    return ret;
}
#endif
#ifdef MQ_SUBSCRIBER
OCStackResult JniOcResource::subscribeMQTopic(JNIEnv* env,
    const QueryParamsMap &queryParametersMap, jobject jListener, QualityOfService QoS)
{
    JniOnMQSubscribeListener *onSubscribeListener = addOnMQTopicSubscribeListener(env, jListener);

    ObserveCallback subscribeCallback = [onSubscribeListener](const HeaderOptions& opts,
        const OCRepresentation& rep, const int& eCode, const int& sequenceNumber)
    {
        onSubscribeListener->onSubscribeCallback(opts, rep, eCode, sequenceNumber);
    };

    OCStackResult ret = OC_STACK_ERROR;
    if (m_sharedResource)
    {
        ret = m_sharedResource->subscribeMQTopic(ObserveType::Observe, queryParametersMap,
                                              subscribeCallback, QoS);
    }
    return ret;
}

OCStackResult JniOcResource::unsubscribeMQTopic(QualityOfService QoS)
{
    OCStackResult ret = OC_STACK_ERROR;
    if (m_sharedResource)
    {
        ret = m_sharedResource->unsubscribeMQTopic(QoS);
    }
    return ret;
}

OCStackResult JniOcResource::requestMQPublish(JNIEnv* env,
    const QueryParamsMap &queryParametersMap, jobject jListener, QualityOfService QoS)
{
    JniOnPostListener *onPostListener = addOnPostListener(env, jListener);

    PostCallback postCallback = [onPostListener](const HeaderOptions& opts,
        const OCRepresentation& rep, const int eCode)
    {
        onPostListener->onPostCallback(opts, rep, eCode);
    };

    OCStackResult ret = OC_STACK_ERROR;
    if (m_sharedResource)
    {
        ret = m_sharedResource->requestMQPublish(queryParametersMap, postCallback, QoS);
    }
    return ret;
}
#endif
#ifdef MQ_PUBLISHER
OCStackResult JniOcResource::publishMQTopic(JNIEnv* env, const OCRepresentation &representation,
    const QueryParamsMap &queryParametersMap, jobject jListener, QualityOfService QoS)
{
    JniOnPostListener *onPostListener = addOnPostListener(env, jListener);

    PostCallback postCallback = [onPostListener](const HeaderOptions& opts,
        const OCRepresentation& rep, const int eCode)
    {
        onPostListener->onPostCallback(opts, rep, eCode);
    };

    OCStackResult ret = OC_STACK_ERROR;
    if (m_sharedResource)
    {
        ret = m_sharedResource->publishMQTopic(representation, queryParametersMap,
                                            postCallback, QoS);
    }
    return ret;
}
#endif

/*
* Class:     org_iotivity_base_OcResource
* Method:    get
* Signature: (Ljava/util/Map;Lorg/iotivity/base/OcResource/OnGetListener;)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_base_OcResource_get
(JNIEnv *env, jobject thiz, jobject jQueryParamsMap, jobject jListener)
{
    LOGD("OcResource_get");
    if (!jQueryParamsMap)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "queryParamsMap cannot be null");
        return;
    }
    if (!jListener)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "onGetListener cannot be null");
        return;
    }
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return;
    }

    QueryParamsMap qpm;
    JniUtils::convertJavaMapToQueryParamsMap(env, jQueryParamsMap, qpm);

    try
    {
        OCStackResult result = resource->get(
            env,
            qpm,
            jListener);

        if (OC_STACK_OK != result)
        {
            ThrowOcException(result, "OcResource_get");
        }
    }
    catch (OCException& e)
    {
        LOGE("%s", e.reason().c_str());
        ThrowOcException(e.code(), e.reason().c_str());
    }
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    get1
* Signature: (Ljava/util/Map;Lorg/iotivity/base/OcResource/OnGetListener;I)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_base_OcResource_get1
(JNIEnv *env, jobject thiz, jobject jQueryParamsMap, jobject jListener, jint jQoS)
{
    LOGD("OcResource_get");
    if (!jQueryParamsMap)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "queryParamsMap cannot be null");
        return;
    }
    if (!jListener)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "onGetListener cannot be null");
        return;
    }
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return;
    }

    QueryParamsMap qpm;
    JniUtils::convertJavaMapToQueryParamsMap(env, jQueryParamsMap, qpm);

    try
    {
        OCStackResult result = resource->get(
            env,
            qpm,
            jListener,
            JniUtils::getQOS(env, static_cast<int>(jQoS)));

        if (OC_STACK_OK != result)
        {
            ThrowOcException(result, "OcResource_get");
        }
    }
    catch (OCException& e)
    {
        LOGE("%s", e.reason().c_str());
        ThrowOcException(e.code(), e.reason().c_str());
    }
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    get2
* Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/util/Map;
Lorg/iotivity/base/OcResource/OnGetListener;)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_base_OcResource_get2
(JNIEnv *env, jobject thiz, jstring jResourceType, jstring jResourceInterface,
jobject jQueryParamsMap, jobject jListener)
{
    LOGD("OcResource_get");
    std::string resourceType;
    if (jResourceType)
    {
        resourceType = env->GetStringUTFChars(jResourceType, nullptr);
    }
    std::string resourceInterface;
    if (jResourceInterface)
    {
        resourceInterface = env->GetStringUTFChars(jResourceInterface, nullptr);
    }
    if (!jQueryParamsMap)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "queryParamsMap cannot be null");
        return;
    }
    if (!jListener)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "onGetListener cannot be null");
        return;
    }
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return;
    }

    QueryParamsMap qpm;
    JniUtils::convertJavaMapToQueryParamsMap(env, jQueryParamsMap, qpm);
    try
    {
        OCStackResult result = resource->get(
            env,
            resourceType,
            resourceInterface,
            qpm,
            jListener);

        if (OC_STACK_OK != result)
        {
            ThrowOcException(result, "OcResource_get");
        }
    }
    catch (OCException& e)
    {
        LOGE("%s", e.reason().c_str());
        ThrowOcException(e.code(), e.reason().c_str());
    }
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    get3
* Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/util/Map;
Lorg/iotivity/base/OcResource/OnGetListener;I)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_base_OcResource_get3
(JNIEnv *env, jobject thiz, jstring jResourceType, jstring jResourceInterface,
jobject jQueryParamsMap, jobject jListener, jint jQoS)
{
    LOGD("OcResource_get");
    if (!jQueryParamsMap)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "queryParamsMap cannot be null");
        return;
    }
    if (!jListener)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "onGetListener cannot be null");
        return;
    }
    std::string resourceType;
    if (jResourceType)
    {
        resourceType = env->GetStringUTFChars(jResourceType, nullptr);
    }
    std::string resourceInterface;
    if (jResourceInterface)
    {
        resourceInterface = env->GetStringUTFChars(jResourceInterface, nullptr);
    }
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return;
    }

    QueryParamsMap qpm;
    JniUtils::convertJavaMapToQueryParamsMap(env, jQueryParamsMap, qpm);

    try
    {
        OCStackResult result = resource->get(
            env,
            resourceType,
            resourceInterface,
            qpm,
            jListener,
            JniUtils::getQOS(env, static_cast<int>(jQoS)));

        if (OC_STACK_OK != result)
        {
            ThrowOcException(result, "OcResource_get");
        }
    }
    catch (OCException& e)
    {
        LOGE("%s", e.reason().c_str());
        ThrowOcException(e.code(), e.reason().c_str());
    }
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    put
* Signature: (Lorg/iotivity/base/OcRepresentation;Ljava/util/Map;
Lorg/iotivity/base/OcResource/OnPutListener;)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_base_OcResource_put
(JNIEnv *env, jobject thiz, jobject jRepresentation, jobject jQueryParamsMap, jobject jListener)
{
    LOGD("OcResource_put");
    if (!jRepresentation)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "queryParamsMap cannot be null");
        return;
    }
    if (!jQueryParamsMap)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "queryParamsMap cannot be null");
        return;
    }
    if (!jListener)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "onPutListener cannot be null");
        return;
    }
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return;
    }

    OCRepresentation *representation = JniOcRepresentation::getOCRepresentationPtr(env, jRepresentation);
    if (!representation)
    {
        return;
    }

    QueryParamsMap qpm;
    JniUtils::convertJavaMapToQueryParamsMap(env, jQueryParamsMap, qpm);

    try
    {
        OCStackResult result = resource->put(
            env,
            *representation,
            qpm,
            jListener);

        if (OC_STACK_OK != result)
        {
            ThrowOcException(result, "OcResource_put");
        }
    }
    catch (OCException& e)
    {
        LOGE("%s", e.reason().c_str());
        ThrowOcException(e.code(), e.reason().c_str());
    }
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    put1
* Signature: (Lorg/iotivity/base/OcRepresentation;Ljava/util/Map;
Lorg/iotivity/base/OcResource/OnPutListener;I)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_base_OcResource_put1
(JNIEnv *env, jobject thiz, jobject jRepresentation, jobject jQueryParamsMap,
jobject jListener, jint jQoS)
{
    LOGD("OcResource_put");
    if (!jRepresentation)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "queryParamsMap cannot be null");
        return;
    }
    if (!jQueryParamsMap)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "queryParamsMap cannot be null");
        return;
    }
    if (!jListener)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "onPutListener cannot be null");
        return;
    }
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return;
    }

    OCRepresentation *representation = JniOcRepresentation::getOCRepresentationPtr(env, jRepresentation);
    if (!representation)
    {
        return;
    }

    QueryParamsMap qpm;
    JniUtils::convertJavaMapToQueryParamsMap(env, jQueryParamsMap, qpm);

    try
    {
        OCStackResult result = resource->put(
            env,
            *representation,
            qpm,
            jListener,
            JniUtils::getQOS(env, static_cast<int>(jQoS)));

        if (OC_STACK_OK != result)
        {
            ThrowOcException(result, "OcResource_put");
        }
    }
    catch (OCException& e)
    {
        LOGE("%s", e.reason().c_str());
        ThrowOcException(e.code(), e.reason().c_str());
    }
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    put2
* Signature: (Ljava/lang/String;Ljava/lang/String;Lorg/iotivity/base/OcRepresentation;
Ljava/util/Map;Lorg/iotivity/base/OcResource/OnPutListener;)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_base_OcResource_put2
(JNIEnv *env, jobject thiz, jstring jResourceType, jstring jResourceInterface,
jobject jRepresentation, jobject jQueryParamsMap, jobject jListener)
{
    LOGD("OcResource_put");
    std::string resourceType;
    if (jResourceType)
    {
        resourceType = env->GetStringUTFChars(jResourceType, nullptr);
    }
    std::string resourceInterface;
    if (jResourceInterface)
    {
        resourceInterface = env->GetStringUTFChars(jResourceInterface, nullptr);
    }
    if (!jRepresentation)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "queryParamsMap cannot be null");
        return;
    }
    if (!jQueryParamsMap)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "queryParamsMap cannot be null");
        return;
    }
    if (!jListener)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "onPutListener cannot be null");
        return;
    }
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return;
    }

    OCRepresentation *representation = JniOcRepresentation::getOCRepresentationPtr(env, jRepresentation);
    if (!representation)
    {
        return;
    }

    QueryParamsMap qpm;
    JniUtils::convertJavaMapToQueryParamsMap(env, jQueryParamsMap, qpm);

    try
    {
        OCStackResult result = resource->put(
            env,
            resourceType,
            resourceInterface,
            *representation,
            qpm,
            jListener);

        if (OC_STACK_OK != result)
        {
            ThrowOcException(result, "OcResource_put");
        }
    }
    catch (OCException& e)
    {
        LOGE("%s", e.reason().c_str());
        ThrowOcException(e.code(), e.reason().c_str());
    }
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    put3
* Signature: (Ljava/lang/String;Ljava/lang/String;Lorg/iotivity/base/OcRepresentation;
Ljava/util/Map;Lorg/iotivity/base/OcResource/OnPutListener;I)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_base_OcResource_put3
(JNIEnv *env, jobject thiz, jstring jResourceType, jstring jResourceInterface, jobject jRepresentation,
jobject jQueryParamsMap, jobject jListener, jint jQoS)
{
    LOGD("OcResource_put");
    if (!jRepresentation)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "representation cannot be null");
        return;
    }
    if (!jQueryParamsMap)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "queryParamsMap cannot be null");
        return;
    }
    if (!jListener)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "onPutListener cannot be null");
        return;
    }
    std::string resourceType;
    if (jResourceType)
    {
        resourceType = env->GetStringUTFChars(jResourceType, nullptr);
    }
    std::string resourceInterface;
    if (jResourceInterface)
    {
        resourceInterface = env->GetStringUTFChars(jResourceInterface, nullptr);
    }

    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return;
    }

    OCRepresentation *representation = JniOcRepresentation::getOCRepresentationPtr(env, jRepresentation);
    if (!representation)
    {
        return;
    }

    QueryParamsMap qpm;
    JniUtils::convertJavaMapToQueryParamsMap(env, jQueryParamsMap, qpm);

    try
    {
        OCStackResult result = resource->put(
            env,
            resourceType,
            resourceInterface,
            *representation,
            qpm,
            jListener,
            JniUtils::getQOS(env, static_cast<int>(jQoS)));

        if (OC_STACK_OK != result)
        {
            ThrowOcException(result, "OcResource_put");
        }
    }
    catch (OCException& e)
    {
        LOGE("%s", e.reason().c_str());
        ThrowOcException(e.code(), e.reason().c_str());
    }
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    post
* Signature: (Lorg/iotivity/base/OcRepresentation;Ljava/util/Map;Lorg/iotivity/base/OcResource/OnPostListener;)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_base_OcResource_post
(JNIEnv *env, jobject thiz, jobject jRepresentation, jobject jQueryParamsMap, jobject jListener)
{
    LOGD("OcResource_post");
    if (!jRepresentation)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "representation cannot be null");
        return;
    }
    if (!jQueryParamsMap)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "queryParamsMap cannot be null");
        return;
    }
    if (!jListener)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "onPostListener cannot be null");
        return;
    }
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return;
    }

    OCRepresentation *representation = JniOcRepresentation::getOCRepresentationPtr(env, jRepresentation);
    if (!representation)
    {
        return;
    }

    QueryParamsMap qpm;
    JniUtils::convertJavaMapToQueryParamsMap(env, jQueryParamsMap, qpm);

    try
    {
        OCStackResult result = resource->post(
            env,
            *representation,
            qpm,
            jListener);

        if (OC_STACK_OK != result)
        {
            ThrowOcException(result, "OcResource_post");
        }
    }
    catch (OCException& e)
    {
        LOGE("%s", e.reason().c_str());
        ThrowOcException(e.code(), e.reason().c_str());
    }
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    post1
* Signature: (Lorg/iotivity/base/OcRepresentation;Ljava/util/Map;Lorg/iotivity/base/OcResource/OnPostListener;I)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_base_OcResource_post1
(JNIEnv *env, jobject thiz, jobject jRepresentation, jobject jQueryParamsMap, jobject jListener, jint jQoS)
{
    LOGD("OcResource_post");
    if (!jRepresentation)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "representation cannot be null");
        return;
    }
    if (!jQueryParamsMap)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "queryParamsMap cannot be null");
        return;
    }
    if (!jListener)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "onPostListener cannot be null");
        return;
    }
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return;
    }

    OCRepresentation *representation = JniOcRepresentation::getOCRepresentationPtr(env, jRepresentation);
    if (!representation)
    {
        return;
    }

    QueryParamsMap qpm;
    JniUtils::convertJavaMapToQueryParamsMap(env, jQueryParamsMap, qpm);

    try
    {
        OCStackResult result = resource->post(
            env,
            *representation,
            qpm,
            jListener,
            JniUtils::getQOS(env, static_cast<int>(jQoS)));

        if (OC_STACK_OK != result)
        {
            ThrowOcException(result, "OcResource_post");
        }
    }
    catch (OCException& e)
    {
        LOGE("%s", e.reason().c_str());
        ThrowOcException(e.code(), e.reason().c_str());
    }
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    post2
* Signature: (Ljava/lang/String;Ljava/lang/String;Lorg/iotivity/base/OcRepresentation;
Ljava/util/Map;Lorg/iotivity/base/OcResource/OnPostListener;)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_base_OcResource_post2
(JNIEnv *env, jobject thiz, jstring jResourceType, jstring jResourceInterface,
jobject jRepresentation, jobject jQueryParamsMap, jobject jListener)
{
    LOGD("OcResource_post");
    if (!jRepresentation)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "representation cannot be null");
        return;
    }
    if (!jQueryParamsMap)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "queryParamsMap cannot be null");
        return;
    }
    if (!jListener)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "onPostListener cannot be null");
        return;
    }
    std::string resourceType;
    if (jResourceType)
    {
        resourceType = env->GetStringUTFChars(jResourceType, nullptr);
    }
    std::string resourceInterface;
    if (jResourceInterface)
    {
        resourceInterface = env->GetStringUTFChars(jResourceInterface, nullptr);
    }

    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return;
    }

    OCRepresentation *representation = JniOcRepresentation::getOCRepresentationPtr(env, jRepresentation);
    if (!representation)
    {
        return;
    }

    QueryParamsMap qpm;
    JniUtils::convertJavaMapToQueryParamsMap(env, jQueryParamsMap, qpm);

    try
    {
        OCStackResult result = resource->post(
            env,
            resourceType,
            resourceInterface,
            *representation,
            qpm,
            jListener);

        if (OC_STACK_OK != result)
        {
            ThrowOcException(result, "OcResource_post");
        }
    }
    catch (OCException& e)
    {
        LOGE("%s", e.reason().c_str());
        ThrowOcException(e.code(), e.reason().c_str());
    }
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    post3
* Signature: (Ljava/lang/String;Ljava/lang/String;Lorg/iotivity/base/OcRepresentation;
Ljava/util/Map;Lorg/iotivity/base/OcResource/OnPostListener;I)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_base_OcResource_post3
(JNIEnv *env, jobject thiz, jstring jResourceType, jstring jResourceInterface,
jobject jRepresentation, jobject jQueryParamsMap, jobject jListener, jint jQoS)
{
    LOGD("OcResource_post");
    if (!jRepresentation)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "representation cannot be null");
        return;
    }
    if (!jQueryParamsMap)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "queryParamsMap cannot be null");
        return;
    }
    if (!jListener)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "onPostListener cannot be null");
        return;
    }
    std::string resourceType;
    if (jResourceType)
    {
        resourceType = env->GetStringUTFChars(jResourceType, nullptr);
    }
    std::string resourceInterface;
    if (jResourceInterface)
    {
        resourceInterface = env->GetStringUTFChars(jResourceInterface, nullptr);
    }

    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return;
    }

    OCRepresentation *representation = JniOcRepresentation::getOCRepresentationPtr(env, jRepresentation);
    if (!representation)
    {
        return;
    }

    QueryParamsMap qpm;
    JniUtils::convertJavaMapToQueryParamsMap(env, jQueryParamsMap, qpm);

    try
    {
        OCStackResult result = resource->post(
            env,
            resourceType,
            resourceInterface,
            *representation,
            qpm,
            jListener,
            JniUtils::getQOS(env, static_cast<int>(jQoS)));

        if (OC_STACK_OK != result)
        {
            ThrowOcException(result, "OcResource_post");
        }
    }
    catch (OCException& e)
    {
        LOGE("%s", e.reason().c_str());
        ThrowOcException(e.code(), e.reason().c_str());
    }
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    deleteResource
* Signature: (Lorg/iotivity/base/OcResource/OnDeleteListener;)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_base_OcResource_deleteResource
(JNIEnv *env, jobject thiz, jobject jListener)
{
    LOGD("OcResource_deleteResource");
    if (!jListener)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "onDeleteListener cannot be null");
        return;
    }
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return;
    }

    try
    {
        OCStackResult result = resource->deleteResource(
            env,
            jListener);

        if (OC_STACK_OK != result)
        {
            ThrowOcException(result, "OcResource_deleteResource");
        }
    }
    catch (OCException& e)
    {
        LOGE("%s", e.reason().c_str());
        ThrowOcException(e.code(), e.reason().c_str());
    }
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    deleteResource1
* Signature: (Lorg/iotivity/base/OcResource/OnDeleteListener;I)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_base_OcResource_deleteResource1
(JNIEnv *env, jobject thiz, jobject jListener, jint jQoS)
{
    LOGD("OcResource_deleteResource");
    if (!jListener)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "onDeleteListener cannot be null");
        return;
    }
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return;
    }

    try
    {
        OCStackResult result = resource->deleteResource(
            env,
            jListener,
            JniUtils::getQOS(env, static_cast<int>(jQoS)));

        if (OC_STACK_OK != result)
        {
            ThrowOcException(result, "OcResource_deleteResource");
        }
    }
    catch (OCException& e)
    {
        LOGE("%s", e.reason().c_str());
        ThrowOcException(e.code(), e.reason().c_str());
    }
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    observe
* Signature: (Lorg/iotivity/base/ObserveType;Ljava/util/Map;
Lorg/iotivity/base/OcResource/OnObserveListener;)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_base_OcResource_observe
(JNIEnv *env, jobject thiz, jint observeType, jobject jQueryParamsMap, jobject jListener)
{
    LOGD("OcResource_observe");
    if (!jQueryParamsMap)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "queryParamsMap cannot be null");
        return;
    }
    if (!jListener)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "onObserveListener cannot be null");
        return;
    }
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return;
    }

    QueryParamsMap qpm;
    JniUtils::convertJavaMapToQueryParamsMap(env, jQueryParamsMap, qpm);

    try
    {
        OCStackResult result = resource->observe(
            env,
            JniUtils::getObserveType(env, static_cast<int>(observeType)),
            qpm,
            jListener);

        if (OC_STACK_OK != result)
        {
            ThrowOcException(result, "OcResource_observe");
        }
    }
    catch (OCException& e)
    {
        LOGE("%s", e.reason().c_str());
        ThrowOcException(e.code(), e.reason().c_str());
    }
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    observe1
* Signature: (Lorg/iotivity/base/ObserveType;Ljava/util/Map;
Lorg/iotivity/base/OcResource/OnObserveListener;I)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_base_OcResource_observe1
(JNIEnv *env, jobject thiz, jint observeType, jobject jQueryParamsMap,
jobject jListener, jint jQoS)
{
    LOGD("OcResource_observe");
    if (!jQueryParamsMap)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "queryParamsMap cannot be null");
        return;
    }
    if (!jListener)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "onObserveListener cannot be null");
        return;
    }
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return;
    }

    QueryParamsMap qpm;
    JniUtils::convertJavaMapToQueryParamsMap(env, jQueryParamsMap, qpm);

    try
    {
        OCStackResult result = resource->observe(
            env,
            JniUtils::getObserveType(env, static_cast<int>(observeType)),
            qpm,
            jListener,
            JniUtils::getQOS(env, static_cast<int>(jQoS)));

        if (OC_STACK_OK != result)
        {
            ThrowOcException(result, "OcResource_observe");
        }
    }
    catch (OCException& e)
    {
        LOGE("%s", e.reason().c_str());
        ThrowOcException(e.code(), e.reason().c_str());
    }
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    cancelObserve1
* Signature: I)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_base_OcResource_cancelObserve1
(JNIEnv *env, jobject thiz, jint jQoS)
{
    LOGD("OcResource_cancelObserve1");
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return;
    }

    try
    {
        OCStackResult result = resource->cancelObserve(
            env,
            JniUtils::getQOS(env, static_cast<int>(jQoS)));

        if (OC_STACK_OK != result)
        {
            ThrowOcException(result, "OcResource_cancelObserve");
        }
    }
    catch (OCException& e)
    {
        LOGE("%s", e.reason().c_str());
        ThrowOcException(e.code(), e.reason().c_str());
    }
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    setHeaderOptions
* Signature: ([Lorg/iotivity/OcHeaderOption;)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_base_OcResource_setHeaderOptions
(JNIEnv *env, jobject thiz, jobjectArray jheaderOptionArr)
{
    LOGD("OcResource_setHeaderOptions");
    if (!jheaderOptionArr)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "headerOptionList cannot be null");
        return;
    }
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return;
    }

    HeaderOptions headerOptions;
    JniUtils::convertJavaHeaderOptionsArrToVector(env, jheaderOptionArr, headerOptions);

    resource->setHeaderOptions(headerOptions);
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    unsetHeaderOptions
* Signature: ()V
*/
JNIEXPORT void JNICALL Java_org_iotivity_base_OcResource_unsetHeaderOptions
(JNIEnv *env, jobject thiz)
{
    LOGD("OcResource_unsetHeaderOptions");
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return;
    }

    resource->unsetHeaderOptions();
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    getHost
* Signature: ()Ljava/lang/String;
*/
JNIEXPORT jstring JNICALL Java_org_iotivity_base_OcResource_getHost
(JNIEnv *env, jobject thiz)
{
    LOGD("OcResource_getHost");
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return nullptr;
    }

    return env->NewStringUTF(resource->host().c_str());
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    getAllHosts
* Signature: ()Ljava/util/List;
*/
JNIEXPORT jobject JNICALL Java_org_iotivity_base_OcResource_getAllHosts
    (JNIEnv *env, jobject thiz)
{
    LOGD("OcResource_getAllHosts");
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return nullptr;
    }

    std::vector<std::string> allHosts = resource->getAllHosts();

    return JniUtils::convertStrVectorToJavaStrList(env, allHosts);
}

/*
 * Class:     org_iotivity_base_OcResource
 * Method:    setHost
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_iotivity_base_OcResource_setHost
(JNIEnv *env, jobject thiz, jstring jHost)
{
    LOGD("OcResource_setHost");
    std::string host;
    if (jHost)
    {
        host = env->GetStringUTFChars(jHost, nullptr);
    }

    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return nullptr;
    }

    return env->NewStringUTF(resource->setHost(host).c_str());
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    getUri
* Signature: ()Ljava/lang/String;
*/
JNIEXPORT jstring JNICALL Java_org_iotivity_base_OcResource_getUri
(JNIEnv *env, jobject thiz)
{
    LOGD("OcResource_getUri");
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return nullptr;
    }

    return env->NewStringUTF(resource->uri().c_str());
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    getConnectivityTypeN
* Signature: ()I
*/
JNIEXPORT jint JNICALL Java_org_iotivity_base_OcResource_getConnectivityTypeN
(JNIEnv *env, jobject thiz)
{
    LOGD("OcResource_getConnectivityType");
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return -1;
    }

    OCConnectivityType connectivityType = resource->connectivityType();
    return static_cast<jint>(connectivityType);
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    isObservable
* Signature: ()Z
*/
JNIEXPORT jboolean JNICALL Java_org_iotivity_base_OcResource_isObservable
(JNIEnv *env, jobject thiz)
{
    LOGD("OcResource_isObservable");
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return false;
    }

    return (jboolean)resource->isObservable();
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    getResourceTypes
* Signature: ()Ljava/util/List;
*/
JNIEXPORT jobject JNICALL Java_org_iotivity_base_OcResource_getResourceTypes
(JNIEnv *env, jobject thiz)
{
    LOGD("OcResource_getResourceTypes");
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return nullptr;
    }

    std::vector<std::string> resourceTypes = resource->getResourceTypes();

    return JniUtils::convertStrVectorToJavaStrList(env, resourceTypes);
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    getResourceInterfaces
* Signature: ()Ljava/util/List;
*/
JNIEXPORT jobject JNICALL Java_org_iotivity_base_OcResource_getResourceInterfaces
(JNIEnv *env, jobject thiz)
{
    LOGD("OcResource_getResourceInterfaces");
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return nullptr;
    }

    std::vector<std::string> resourceInterfaces = resource->getResourceInterfaces();

    return JniUtils::convertStrVectorToJavaStrList(env, resourceInterfaces);
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    getUniqueIdentifier
* Signature: ()Lorg/iotivity/base/OcResourceIdentifier;
*/
JNIEXPORT jobject JNICALL Java_org_iotivity_base_OcResource_getUniqueIdentifier
(JNIEnv *env, jobject thiz)
{
    LOGD("OcResource_getUniqueIdentifier");
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return nullptr;
    }

    JniOcResourceIdentifier *jniResourceIdentifier =
        new JniOcResourceIdentifier(resource->uniqueIdentifier());
    if (!jniResourceIdentifier)
    {
        return nullptr;
    }

    jlong handle = reinterpret_cast<jlong>(jniResourceIdentifier);
    jobject jResourceIdentifier = env->NewObject(g_cls_OcResourceIdentifier,
        g_mid_OcResourceIdentifier_N_ctor, handle);
    if (!jResourceIdentifier)
    {
        delete jniResourceIdentifier;
    }
    return jResourceIdentifier;
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    getServerId
* Signature: ()Ljava/lang/String;
*/
JNIEXPORT jstring JNICALL Java_org_iotivity_base_OcResource_getServerId
(JNIEnv *env, jobject thiz)
{
    LOGD("OcResource_getServerId");
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return nullptr;
    }

    return env->NewStringUTF(resource->sid().c_str());
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    dispose
* Signature: ()V
*/
JNIEXPORT void JNICALL Java_org_iotivity_base_OcResource_dispose
(JNIEnv *env, jobject thiz)
{
    LOGD("OcResource_dispose");
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    delete resource;
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    discoveryMQTopicsImpl
* Signature: (Ljava/util/Map;Lorg/iotivity/base/OcPlatform/OnResourceFoundListener;I)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_base_OcResource_discoveryMQTopicsImpl
(JNIEnv *env, jobject thiz, jobject jQueryParamsMap, jobject jListener, jint jQoS)
{
    LOGD("OcResource_discoveryMQTopicsImpl");
#ifdef WITH_MQ
    if (!jQueryParamsMap)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "queryParamsMap cannot be null");
        return;
    }

    if (!jListener)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "listener cannot be null");
        return;
    }

    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return;
    }

    QueryParamsMap qpm;
    JniUtils::convertJavaMapToQueryParamsMap(env, jQueryParamsMap, qpm);

    try
    {
        OCStackResult result = resource->discoveryMQTopics(
            env,
            qpm,
            jListener,
            JniUtils::getQOS(env, static_cast<int>(jQoS)));

        if (OC_STACK_OK != result)
        {
            ThrowOcException(result, "OcResource_discoveryMQTopicsImpl");
        }
    }
    catch (OCException& e)
    {
        LOGE("%s", e.reason().c_str());
        ThrowOcException(e.code(), e.reason().c_str());
    }
#else
    OC_UNUSED(env);
    OC_UNUSED(thiz);
    OC_UNUSED(jQueryParamsMap);
    OC_UNUSED(jListener);
    OC_UNUSED(jQoS);
    ThrowOcException(JNI_NO_SUPPORT, "not support");
#endif
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    createMQTopicImpl
* Signature: (Lorg/iotivity/base/OcRepresentation;Ljava/util/String;Ljava/util/Map
*             ;Lorg/iotivity/base/OcPlatform/OnMQTopicCreatedListener;I)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_base_OcResource_createMQTopicImpl
(JNIEnv *env, jobject thiz, jobject jRepresentation, jstring jUri,
 jobject jQueryParamsMap, jobject jListener, jint jQoS)
{
    LOGD("OcResource_createMQTopicImpl");
#ifdef WITH_MQ
    if (!jQueryParamsMap)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "queryParamsMap cannot be null");
        return;
    }

    if (!jListener)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "listener cannot be null");
        return;
    }

    if (!jRepresentation)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "representation null");
        return;
    }

    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return;
    }

    std::string targetUri;
    if (jUri)
    {
        targetUri = env->GetStringUTFChars(jUri, nullptr);
    }

    OCRepresentation *representation = JniOcRepresentation::getOCRepresentationPtr(env,
                                                                                   jRepresentation);
    if (!representation)
    {
        return;
    }

    QueryParamsMap qpm;
    JniUtils::convertJavaMapToQueryParamsMap(env, jQueryParamsMap, qpm);

    try
    {
        OCStackResult result = resource->createMQTopic(
            env,
            *representation,
            targetUri,
            qpm,
            jListener,
            JniUtils::getQOS(env, static_cast<int>(jQoS)));

        if (OC_STACK_OK != result)
        {
            ThrowOcException(result, "OcResource_createMQTopicImpl");
        }
    }
    catch (OCException& e)
    {
        LOGE("%s", e.reason().c_str());
        ThrowOcException(e.code(), e.reason().c_str());
    }
#else
    OC_UNUSED(env);
    OC_UNUSED(thiz);
    OC_UNUSED(jRepresentation);
    OC_UNUSED(jUri);
    OC_UNUSED(jQueryParamsMap);
    OC_UNUSED(jListener);
    OC_UNUSED(jQoS);
    ThrowOcException(JNI_NO_SUPPORT, "not support");
#endif
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    subscribeMQTopic
* Signature: (Ljava/util/Map;Lorg/iotivity/base/OcResource/OnObserveListener;I)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_base_OcResource_subscribeMQTopicImpl
(JNIEnv *env, jobject thiz, jobject jQueryParamsMap, jobject jListener, jint jQoS)
{
    LOGD("OcResource_subscribeMQTopicImpl");
#ifdef MQ_SUBSCRIBER
    if (!jQueryParamsMap)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "queryParamsMap cannot be null");
        return;
    }
    if (!jListener)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "onObserveListener cannot be null");
        return;
    }
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return;
    }

    QueryParamsMap qpm;
    JniUtils::convertJavaMapToQueryParamsMap(env, jQueryParamsMap, qpm);

    try
    {
        OCStackResult result = resource->subscribeMQTopic(
            env,
            qpm,
            jListener,
            JniUtils::getQOS(env, static_cast<int>(jQoS)));

        if (OC_STACK_OK != result)
        {
            ThrowOcException(result, "OcResource_subscribeMQTopicImpl");
        }
    }
    catch (OCException& e)
    {
        LOGE("%s", e.reason().c_str());
        ThrowOcException(e.code(), e.reason().c_str());
    }
#else
    OC_UNUSED(env);
    OC_UNUSED(thiz);
    OC_UNUSED(jQueryParamsMap);
    OC_UNUSED(jListener);
    OC_UNUSED(jQoS);
    ThrowOcException(JNI_NO_SUPPORT, "not support");
#endif
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    unsubscribeMQTopicImpl
* Signature: (I)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_base_OcResource_unsubscribeMQTopicImpl
(JNIEnv *env, jobject thiz, jint jQoS)
{
    LOGD("OcResource_unsubscribeMQTopicImpl");
#ifdef MQ_SUBSCRIBER
    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return;
    }

    try
    {
        OCStackResult result = resource->unsubscribeMQTopic(
                JniUtils::getQOS(env, static_cast<int>(jQoS)));
        if (OC_STACK_OK != result)
        {
            ThrowOcException(result, "OcResource_unsubscribeMQTopicImpl");
        }
    }
    catch (OCException& e)
    {
        LOGE("%s", e.reason().c_str());
        ThrowOcException(e.code(), e.reason().c_str());
    }
#else
    OC_UNUSED(env);
    OC_UNUSED(thiz);
    OC_UNUSED(jQoS);
    ThrowOcException(JNI_NO_SUPPORT, "not support");
#endif
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    requestMQPublishImpl
* Signature: (Ljava/util/Map;Lorg/iotivity/base/OcResource/OnPostListener;I)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_base_OcResource_requestMQPublishImpl
(JNIEnv *env, jobject thiz, jobject jQueryParamsMap, jobject jListener, jint jQoS)
{
    OC_UNUSED(thiz);
    LOGD("OcResource_requestMQPublishImpl");
#ifdef MQ_SUBSCRIBER
    if (!jQueryParamsMap)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "queryParamsMap cannot be null");
        return;
    }
    if (!jListener)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "onPostListener cannot be null");
        return;
    }

    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return;
    }

    QueryParamsMap qpm;
    JniUtils::convertJavaMapToQueryParamsMap(env, jQueryParamsMap, qpm);

    try
    {
        OCStackResult result = resource->requestMQPublish(
            env,
            qpm,
            jListener,
            JniUtils::getQOS(env, static_cast<int>(jQoS)));

        if (OC_STACK_OK != result)
        {
            ThrowOcException(result, "OcResource_requestMQPublishImpl");
        }
    }
    catch (OCException& e)
    {
        LOGE("%s", e.reason().c_str());
        ThrowOcException(e.code(), e.reason().c_str());
    }
#else
    OC_UNUSED(env);
    OC_UNUSED(jQueryParamsMap);
    OC_UNUSED(jListener);
    OC_UNUSED(jQoS);
    ThrowOcException(JNI_NO_SUPPORT, "not support");
#endif
}

/*
* Class:     org_iotivity_base_OcResource
* Method:    publishMQTopicImpl
* Signature: (Lorg/iotivity/base/OcRepresentation;Ljava/util/Map;
*             Lorg/iotivity/base/OcResource/OnPostListener;I)V
*/
JNIEXPORT void JNICALL Java_org_iotivity_base_OcResource_publishMQTopicImpl
(JNIEnv *env, jobject thiz, jobject jRepresentation, jobject jQueryParamsMap,
 jobject jListener, jint jQoS)
{
    OC_UNUSED(thiz);
    LOGD("OcResource_publishMQTopicImpl");
#ifdef MQ_PUBLISHER
    if (!jRepresentation)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "representation cannot be null");
        return;
    }

    if (!jQueryParamsMap)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "queryParamsMap cannot be null");
        return;
    }

    if (!jListener)
    {
        ThrowOcException(OC_STACK_INVALID_PARAM, "onPostListener cannot be null");
        return;
    }

    JniOcResource *resource = JniOcResource::getJniOcResourcePtr(env, thiz);
    if (!resource)
    {
        return;
    }

    OCRepresentation *representation = JniOcRepresentation::getOCRepresentationPtr(env,
                                                                                   jRepresentation);
    if (!representation)
    {
        return;
    }

    QueryParamsMap qpm;
    JniUtils::convertJavaMapToQueryParamsMap(env, jQueryParamsMap, qpm);

    try
    {
        OCStackResult result = resource->publishMQTopic(
            env,
            *representation,
            qpm,
            jListener,
            JniUtils::getQOS(env, static_cast<int>(jQoS)));

        if (OC_STACK_OK != result)
        {
            ThrowOcException(result, "OcResource_publishMQTopicImpl");
        }
    }
    catch (OCException& e)
    {
        LOGE("%s", e.reason().c_str());
        ThrowOcException(e.code(), e.reason().c_str());
    }
#else
    OC_UNUSED(env);
    OC_UNUSED(jRepresentation);
    OC_UNUSED(jQueryParamsMap);
    OC_UNUSED(jListener);
    OC_UNUSED(jQoS);
    ThrowOcException(JNI_NO_SUPPORT, "not support");
#endif
}
