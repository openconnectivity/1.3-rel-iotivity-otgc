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

#include "JniSecureUtils.h"
#include "JniOcStack.h"
#include "JniOcSecureResource.h"
#include "oic_malloc.h"
#include "srmutility.h"
#include "base64.h"

using namespace OC;

jobject JniSecureUtils::convertProvisionresultVectorToJavaList(JNIEnv *env, const OC::PMResultList_t *result)
{
    jobject jResultList = env->NewObject(g_cls_LinkedList, g_mid_LinkedList_ctor);
    if (!jResultList)
    {
        return nullptr;
    }

    for (size_t i = 0; i < result->size(); ++i)
    {
        char *Str = NULL;

        if (OC_STACK_OK != ConvertUuidToStr(&(result->at(i).deviceId), &Str))
        {
            return nullptr;
        }
        jstring jStr = env->NewStringUTF(Str);
        OICFree(Str);

        if (!jStr)
        {
            return nullptr;
        }
        jobject jresult = env->NewObject(
                g_cls_OcProvisionResult,
                g_mid_OcProvisionResult_ctor,
                jStr,
                static_cast<jint>(result->at(i).res)
                );
        if (!jresult)
        {
            return nullptr;
        }

        env->CallBooleanMethod(jResultList, g_mid_LinkedList_add_object, jresult);
        if (env->ExceptionCheck())
        {
            return nullptr;
        }
        env->DeleteLocalRef(jresult);
        env->DeleteLocalRef(jStr);
    }
    return jResultList;
}

jobjectArray JniSecureUtils::convertDeviceVectorToJavaArray(JNIEnv *env,
    std::vector<std::shared_ptr<OC::OCSecureResource>> &deviceListVector)
{
    jsize len = static_cast<jsize>(deviceListVector.size());
    jobjectArray devArr = env->NewObjectArray(len, g_cls_OcSecureResource, NULL);

    if (!devArr)
    {
        return nullptr;
    }

    for (jsize i = 0; i < len; ++i)
    {
        JniOcSecureResource *device = new JniOcSecureResource(deviceListVector[i]);
        jobject jDevice = env->NewObject(g_cls_OcSecureResource, g_mid_OcSecureResource_ctor);

        SetHandle<JniOcSecureResource>(env, jDevice, device);
        if (!jDevice)
        {
            return nullptr;
        }

        env->SetObjectArrayElement(devArr, i, jDevice);
        if (env->ExceptionCheck())
        {
            return nullptr;
        }
        env->DeleteLocalRef(jDevice);
    }
    return devArr;
}

jobject JniSecureUtils::convertDeviceToJava(JNIEnv *env,
    std::shared_ptr<OC::OCSecureResource> &device)
{
    JniOcSecureResource *jniDevice = new JniOcSecureResource(device);
    jobject jDevice = env->NewObject(g_cls_OcSecureResource, g_mid_OcSecureResource_ctor);

    SetHandle<JniOcSecureResource>(env, jDevice, jniDevice);
    return jDevice;
}

std::string JniSecureUtils::convertUUIDtoStr(OicUuid_t uuid)
{
    std::ostringstream deviceId("");
    char base64Buff[B64ENCODE_OUT_SAFESIZE(sizeof(((OicUuid_t*)0)->id)) + 1] = {0,};
    size_t outLen = 0;

    b64Encode(uuid.id, sizeof(uuid.id), base64Buff,
              sizeof(base64Buff), &outLen);

    deviceId << base64Buff;
    return deviceId.str();
}

jobject JniSecureUtils::convertUUIDVectorToJavaStrList(JNIEnv *env, UuidList_t &vector)
{
    jobject jList = env->NewObject(g_cls_LinkedList, g_mid_LinkedList_ctor);
    if (!jList)
    {
        return nullptr;
    }
    for (size_t i = 0; i < vector.size(); ++i)
    {
        char *Str = NULL;

        if (OC_STACK_OK != ConvertUuidToStr(&(vector[i]), &Str))
        {
            return nullptr;
        }
        jstring jStr = env->NewStringUTF(Str);
        OICFree(Str);

        if (!jStr)
        {
            return nullptr;
        }
        env->CallBooleanMethod(jList, g_mid_LinkedList_add_object, jStr);
        if (env->ExceptionCheck())
        {
            return nullptr;
        }
        env->DeleteLocalRef(jStr);
    }
    return jList;
}

static OicSecValidity_t* getValiditiesList(JNIEnv *env, jobject validityObject)
{
    jstring jData;
    jobjectArray  valList = (jobjectArray)env->CallObjectMethod(validityObject, g_mid_OcOicSecAcl_ace_get_validities);
    if (!valList || env->ExceptionCheck())
    {
        return nullptr;
    }
    int nr_validities = env->GetArrayLength(valList);

    OicSecValidity_t *valHead = NULL;

    for (int i = 0 ; i < nr_validities; i++)
    {
        OicSecValidity_t *tmp = (OicSecValidity_t*)OICCalloc(1, sizeof(OicSecValidity_t));
        jobject element = env->GetObjectArrayElement(valList, i);
        if (!element || env->ExceptionCheck())
        {
            return nullptr;
        }

        jData = (jstring)env->CallObjectMethod(element, g_mid_OcOicSecAcl_validity_get_getPeriod);
        if (!jData || env->ExceptionCheck())
        {
            return nullptr;
        }
        tmp->period = (char*)env->GetStringUTFChars(jData, 0);

        jint jrecurrenceLen = (jint) env->CallIntMethod(element,
                g_mid_OcOicSecAcl_validity_get_recurrenceLen);
        tmp->recurrenceLen = (int)jrecurrenceLen;

        if (jrecurrenceLen > 0)
        {
            jvalue argv[1];
            tmp->recurrences = (char**)OICCalloc(jrecurrenceLen, sizeof(char*));

            for (int j = 0 ; j < jrecurrenceLen; j++)
            {
                argv[0].i = j;
                jData = (jstring)env->CallObjectMethodA(element, g_mid_OcOicSecAcl_validity_get_recurrences, argv);
                if (!jData || env->ExceptionCheck())
                {
                    return nullptr;
                }
                tmp->recurrences[j] = (char*)env->GetStringUTFChars(jData, 0);
            }
        }
        if (NULL == valHead)
        {
            valHead = tmp;
        }
        else
        {
            OicSecValidity_t *ptr = valHead;
            while(ptr->next != NULL) ptr = ptr->next;
            ptr->next = tmp;
            tmp->next = NULL;
        }
        env->DeleteLocalRef(element);
    }
    return valHead;
}

static OicSecRsrc_t * getResourcesList(JNIEnv *env, jobject resourceObject)
{
    jstring jData;

    jobjectArray rescList = (jobjectArray)env->CallObjectMethod(resourceObject, g_mid_OcOicSecAcl_ace_get_resources);
    if (!rescList || env->ExceptionCheck())
    {
        LOGI("getResourcesList_afterGetResources");
        return nullptr;
    }

    int nr_resc = env->GetArrayLength(rescList);
    OicSecRsrc_t *rescHead = NULL;

    for (int i = 0 ; i < nr_resc; i++)
    {
        OicSecRsrc_t *tmp = (OicSecRsrc_t*)OICCalloc(1, sizeof(OicSecRsrc_t));
        jobject element = env->GetObjectArrayElement(rescList, i);
        if (!element || env->ExceptionCheck())
        {
            LOGI("getResourcesList_afterGetElement");
            return nullptr;
        }
        jData = (jstring)env->CallObjectMethod(element, g_mid_OcOicSecAcl_resr_get_href);
        if (!jData || env->ExceptionCheck())
        {
            return nullptr;
        }
        tmp->href = (char*)env->GetStringUTFChars(jData, 0);

        /*jData = (jstring)env->CallObjectMethod(element, g_mid_OcOicSecAcl_resr_get_rel);
        if (!jData || env->ExceptionCheck())
        {
            LOGI("getResourcesList_afterGetRel");
            return nullptr;
        }
        tmp->rel = (char*)env->GetStringUTFChars(jData, 0);*/

        jint len = (jint) env->CallIntMethod(element, g_mid_OcOicSecAcl_resr_get_typeLen);
        tmp->typeLen = (int)len;
        if (len > 0)
        {
            jvalue argv[1];
            tmp->types = (char**)OICCalloc(len, sizeof(char*));

            for (int j = 0 ; j < len; j++)
            {
                argv[0].i = j;
                jData = (jstring)env->CallObjectMethodA(element, g_mid_OcOicSecAcl_resr_get_types, argv);
                if (!jData || env->ExceptionCheck())
                {
                    return nullptr;
                }
                tmp->types[j] = (char*)env->GetStringUTFChars(jData, 0);
            }
        }

        len = (jint) env->CallIntMethod(element, g_mid_OcOicSecAcl_resr_get_interfaceLen);
        tmp->interfaceLen = len;
        if (len > 0)
        {
            jvalue argv[1];
            tmp->interfaces = (char**)OICCalloc(len, sizeof(char*));

            for (int j = 0 ; j < len; j++)
            {
                argv[0].i = j;
                jData = (jstring)env->CallObjectMethodA(element, g_mid_OcOicSecAcl_resr_get_interfaces, argv);
                if (!jData || env->ExceptionCheck())
                {
                    return nullptr;
                }
                tmp->interfaces[j] = (char*)env->GetStringUTFChars(jData, 0);
            }
        }

        if (NULL == rescHead)
        {
            rescHead = tmp;
        }
        else
        {
            OicSecRsrc_t *ptr = rescHead;
            while(ptr->next != NULL) ptr = ptr->next;
            ptr->next = tmp;
            tmp->next = NULL;
        }
        env->DeleteLocalRef(element);
    }
    return rescHead;
}

OCStackResult JniSecureUtils::convertJavaACLToOCAcl(JNIEnv *env, jobject in, OicSecAcl_t *acl)
{
    jstring jData;

    // rowneruuid
    jData = (jstring) env->CallObjectMethod(in, g_mid_OcOicSecAcl_get_rownerID);
    LOGI("convertJavaACLToOCAcl_get_rownerID");
    /*if (!jData || env->ExceptionCheck())
    {
        return OC_STACK_ERROR;
    }*/
    if (env->ExceptionCheck())
    {
        LOGI("convertJavaACLToOCAcl_afterGetRownerID");
        return OC_STACK_ERROR;
    }    
    
    char *str = NULL;
    
    if (jData)
    {
        str = (char*) env->GetStringUTFChars(jData, 0);
        if (OC_STACK_OK == ConvertStrToUuid(str, &acl->rownerID))
        {
            env->ReleaseStringUTFChars(jData, str);
        }
        else
        {
            LOGI("convertJavaACLToOCAcl_afterConvertRownerID");
            return OC_STACK_ERROR;
        }    
    }    

    // aces
    jobjectArray acesList = (jobjectArray)env->CallObjectMethod(in, g_mid_OcOicSecAcl_get_aces);

    if (!acesList || env->ExceptionCheck())
    {
        LOGI("convertJavaACLToOCAcl_afterGetAces");
        return OC_STACK_ERROR;
    }

    int nr_aces = env->GetArrayLength(acesList);

    OicSecAce_t *acesHead = NULL;

    for (int i = 0 ; i < nr_aces; i++)
    {
        OicSecAce_t *tmp = (OicSecAce_t*)OICCalloc(1, sizeof(OicSecAce_t));

        jobject element = env->GetObjectArrayElement(acesList, i);
        if (!element || env->ExceptionCheck())
        {
            LOGI("convertJavaACLToOCAcl_afterGetAce");
            return OC_STACK_ERROR;
        }
        
        // aceid
        //jint aceId = (jint)env->CallIntMethod(element, g_mid_OcOicSecAcl_ace_get_aceid);
        //tmp->aceid = (uint16_t)aceId;
        
        // subject
        jobject jSubjectObj = env->CallObjectMethod(element, g_mid_OcOicSecAcl_ace_get_subject);
        if (!jSubjectObj || env->ExceptionCheck())
        {
            LOGI("convertJavaACLToOCAcl_afterGetSubject");
            return OC_STACK_ERROR;
        }
        
        // subjecttype        
        jint jSubjectType = (jint)env->CallIntMethod(jSubjectObj, g_mid_OcOicSecAcl_ace_subject_get_type);
        tmp->subjectType = static_cast<OicSecAceSubjectType>(jSubjectType);
        LOGI("subjectType: %d", jSubjectType);
        
        if (tmp->subjectType == OicSecAceUuidSubject)
        {
            LOGI("convertJavaACLToOCAcl_intoOicSecAceUuidSubject");
            // uuid
            jstring jStr = (jstring) env->CallObjectMethod(jSubjectObj, g_mid_OcOicSecAcl_ace_get_subject_uuid);
            if (!jStr || env->ExceptionCheck())
            {
                LOGI("convertJavaACLToOCAcl_afterGetSubjectUuid");
                return OC_STACK_ERROR;
            }

            str = (char*) env->GetStringUTFChars(jStr, 0);
            if (OC_STACK_OK == ConvertStrToUuid(str, &tmp->subjectuuid))
            {
                env->ReleaseStringUTFChars(jStr, str);
            }
            else
            {
                LOGI("convertJavaACLToOCAcl_afterConvertSubjectUuid");
                return OC_STACK_ERROR;
            }
        }
        else if (tmp->subjectType == OicSecAceRoleSubject)
        {
            LOGI("convertJavaACLToOCAcl_intoOicSecAceRoleSubject");
            // role
            jobject jSubjectRoleObj = env->CallObjectMethod(jSubjectObj, g_mid_OcOicSecAcl_ace_subject_get_role);
            if (!jSubjectRoleObj || env->ExceptionCheck())
            {
                LOGI("convertJavaACLToOCAcl_afterGetSubjectRole");
                return OC_STACK_ERROR;
            }
            
            OicSecRole_t *role = (OicSecRole_t*)OICCalloc(1, sizeof(OicSecRole_t));
            
            if (!role)
            {
                LOGI("convertJavaACLToOCAcl_afterAllocateSubjectRole");
                return OC_STACK_ERROR;
            }
            
            jstring jId = (jstring) env->CallObjectMethod(jSubjectRoleObj, g_mid_OcOicSecAcl_ace_subject_role_get_id);
            str = (char*) env->GetStringUTFChars(jId, 0);
            if (strlen(str) < ROLEID_LENGTH)
            {
                strcpy(role->id, str);
                env->ReleaseStringUTFChars(jId, str);
            }
            else
            {
                LOGI("convertJavaACLToOCAcl_afterGetSubjectRoleId");
                return OC_STACK_ERROR;
            }
            
            jstring jAuthority = (jstring) env->CallObjectMethod(jSubjectRoleObj, g_mid_OcOicSecAcl_ace_subject_role_get_authority);
            str = (char*) env->GetStringUTFChars(jAuthority, 0);
            if (strlen(str) < ROLEAUTHORITY_LENGTH)
            {
                strcpy(role->authority, str);
                env->ReleaseStringUTFChars(jAuthority, str);
            }
            else
            {
                LOGI("convertJavaACLToOCAcl_afterGetSubjectRoleAuthority");
                return OC_STACK_ERROR;
            }
            
            tmp->subjectRole = *role;
        }
        else if (tmp->subjectType == OicSecAceConntypeSubject)
        {
            LOGI("convertJavaACLToOCAcl_intoOicSecAceConnTypeSubject");
            // conn-type
            jstring jStr = (jstring) env->CallObjectMethod(jSubjectObj, g_mid_OcOicSecAcl_ace_subject_get_connType);
            if (!jStr || env->ExceptionCheck())
            {
                LOGI("convertJavaACLToOCAcl_afterGetSubjectConnType");
                return OC_STACK_ERROR;
            }
            
            str = (char*) env->GetStringUTFChars(jStr, 0);
            if (0 == strcmp(str, "auth-crypt"))
            {
                tmp->subjectConn = AUTH_CRYPT;
            }
            else
            {
                tmp->subjectConn = ANON_CLEAR;
            }
            
            env->ReleaseStringUTFChars(jStr, str);
        }
        else
        {
            LOGI("convertJavaACLToOCAcl_intoElseOicSecAceSubject");
            return OC_STACK_ERROR;
        }

        jint perm = (jint)env->CallIntMethod(element, g_mid_OcOicSecAcl_ace_get_permissions);
        tmp->permission = (uint16_t)perm;
        if (nullptr == (tmp->resources = getResourcesList(env, element)))
        {
            LOGI("convertJavaACLToOCAcl_afterGetResourcesList");
            return OC_STACK_ERROR;
        }

        tmp->validities = NULL; //TODO Seems Validities CBOR conversion is broken in C stack
#if 0
        if (nullptr == (tmp->validities = getValiditiesList(env, element)))
        {
            return OC_STACK_ERROR;
        }
#endif
        if (NULL == acesHead)
        {
            acesHead = tmp;
        }
        else
        {
            OicSecAce_t *ptr = acesHead;
            while(ptr->next != NULL) ptr = ptr->next;
            ptr->next = tmp;
            tmp->next = NULL;
        }
    }
    acl->aces = acesHead;
    return OC_STACK_OK;
}

OCStackResult JniSecureUtils::convertJavaPdACLToOCAcl(JNIEnv *env, jobject in, OicSecPdAcl_t *pdacl)
{
    jstring jData;
    jvalue args[1];

    jint jCount = (jint) env->CallIntMethod(in, g_mid_OcOicSecPdAcl_get_resources_cnt);
    if (!jCount || env->ExceptionCheck())
    {
        return OC_STACK_ERROR;
    }

    pdacl->resourcesLen = jCount;
    pdacl->resources = new char*[jCount];

    if (!pdacl->resources)
    {
        return OC_STACK_ERROR;
    }
    for (jint i = 0; i < jCount; ++i)
    {
        args[0].i = i;
        jData = (jstring) env->CallObjectMethodA(in, g_mid_OcOicSecPdAcl_get_resources, args);
        if (!jData || env->ExceptionCheck())
        {
            return OC_STACK_ERROR;
        }

        pdacl->resources[i] = (char*) env->GetStringUTFChars(jData, 0);
    }

    jCount = (jint) env->CallIntMethod(in, g_mid_OcOicSecPdAcl_get_permission);
    if (env->ExceptionCheck())
    {
        return OC_STACK_ERROR;
    }

    pdacl->permission = static_cast<uint16_t>(jCount);
    jCount = (jint) env->CallIntMethod(in, g_mid_OcOicSecPdAcl_get_periods_cnt);
    if (env->ExceptionCheck())
    {
        return OC_STACK_ERROR;
    }

    pdacl->prdRecrLen = jCount;
    if (jCount)
    {
        pdacl->periods = new char*[jCount];
        if (!pdacl->periods)
        {
            return OC_STACK_ERROR;
        }
    }
    for (jint i = 0; i < jCount; ++i)
    {
        args[0].i = i;
        jData = (jstring) env->CallObjectMethodA(in, g_mid_OcOicSecPdAcl_get_periods, args);
        if (!jData || env->ExceptionCheck())
        {
            return OC_STACK_ERROR;
        }

        pdacl->periods[i] = (char*) env->GetStringUTFChars(jData, 0);
    }

    if (jCount)
    {
        pdacl->recurrences = new char*[jCount];
        if (!pdacl->recurrences)
        {
            return OC_STACK_ERROR;
        }
    }
    for (jint i = 0; i < jCount; ++i)
    {
        args[0].i = i;
        jData = (jstring) env->CallObjectMethodA(in, g_mid_OcOicSecPdAcl_get_recurrences, args);
        if (!jData ||  env->ExceptionCheck())
        {
            return OC_STACK_ERROR;
        }

        pdacl->recurrences[i] = (char*) env->GetStringUTFChars(jData, 0);
    }
    return OC_STACK_OK;
}

static jobject setResourceListForJavaACL(JNIEnv *env, OicSecRsrc_t *resources)
{
	jobject jResourceList = env->NewObject(g_cls_LinkedList, g_mid_LinkedList_ctor);
    if (!jResourceList)
    {
        return nullptr;
    }
    
    OicSecRsrc_t *resourceHead = resources;
    for (OicSecRsrc_t *resource = resourceHead; resource != NULL; resource = resource->next)
    {
    	jobject jResource = env->NewObject(g_cls_OcOicSecAcl_resr, g_mid_OcOicSecAcl_resr_ctor);
    	// href
    	if (resource->href != NULL) {
			char *strHref = resource->href;
			jstring jStrHref = env->NewStringUTF(strHref);
			OICFree(strHref);
			if (!jStrHref)
			{
				return nullptr;
			}
			env->CallVoidMethod(jResource, g_mid_OcOicSecAcl_resr_set_href, jStrHref);
			if (env->ExceptionCheck())
			{
				return nullptr;
			}
			env->DeleteLocalRef(jStrHref);
		}
		
		// rel
		/*if (resource->rel != NULL) {
			char *strRel = resource->rel;
			jstring jStrRel = env->NewStringUTF(strRel);
			OICFree(strRel);
			if (!jStrRel)
			{
				return nullptr;
			}
			env->CallVoidMethod(jResource, g_mid_OcOicSecAcl_resr_set_rel, jStrRel);
			if (env->ExceptionCheck())
			{
				return nullptr;
			}
			env->DeleteLocalRef(jStrRel);
		}*/
		
		// Add resource object to list
		env->CallBooleanMethod(jResourceList, g_mid_LinkedList_add_object, jResource);
        if (env->ExceptionCheck())
        {
            return nullptr;
        }
        env->DeleteLocalRef(jResource);
    }
    
    return jResourceList;
}

static jobject getSubjectObjectForJava(JNIEnv *env, OicSecAce_t *ace)
{
	jstring jStrSubjectUuid = NULL;
	jobject jRole = NULL;
	jstring jStrConnType = NULL;
	
	if (ace->subjectType == OicSecAceUuidSubject)
	{
		char *strSubjectUuid = NULL;
		if (OC_STACK_OK != ConvertUuidToStr(&(ace->subjectuuid), &strSubjectUuid))
		{
			return nullptr;
		}
		jStrSubjectUuid = env->NewStringUTF(strSubjectUuid);
		OICFree(strSubjectUuid);
		if (!jStrSubjectUuid)
		{
			return nullptr;
		}
	}
	else if (ace->subjectType == OicSecAceRoleSubject)
	{
		char *roleId = ace->subjectRole.id;
		jstring jStrRoleId = env->NewStringUTF(roleId);
		if (!jStrRoleId)
		{
			return nullptr;
		}
		
		char *roleAuthority = ace->subjectRole.authority;
		jstring jStrRoleAuthority = env->NewStringUTF(roleAuthority);
		if (!jStrRoleAuthority)
		{
			return nullptr;
		}
		
		jRole = env->NewObject(g_cls_OcOicSecAcl_ace_subject_role, g_mid_OcOicSecAcl_ace_subject_role_ctor, jStrRoleId, jStrRoleAuthority);
		env->DeleteLocalRef(jStrRoleId);
		env->DeleteLocalRef(jStrRoleAuthority);
	}
	else if (ace->subjectType == OicSecAceConntypeSubject)
	{
		if (ace->subjectConn == AUTH_CRYPT) {
			jStrConnType = env->NewStringUTF("auth-crypt");
		} else if (ace->subjectConn == ANON_CLEAR) {
			jStrConnType = env->NewStringUTF("anon-clear");
		}
	}
	
	jobject res = env->NewObject(g_cls_OcOicSecAcl_ace_subject, g_mid_OcOicSecAcl_ace_subject_ctor, ace->subjectType, jStrSubjectUuid, jRole, jStrConnType);
	env->DeleteLocalRef(jStrSubjectUuid);
	env->DeleteLocalRef(jRole);
	env->DeleteLocalRef(jStrConnType);
	
	return res;
}

jobject JniSecureUtils::convertOCAclToJavaACL(JNIEnv *env, PMGetAclResult_t *aclResult)
{
	jobject jAcl = env->NewObject(g_cls_OcOicSecAcl, g_mid_OcOicSecAcl_ctor);
	if (!jAcl)
    {
        return nullptr;
    }
    
    if (aclResult->res == OC_STACK_OK && aclResult->acl)
    {
        // RownerUUid
        char * strRownerUuid = NULL;
        if (OC_STACK_OK != ConvertUuidToStr(&(aclResult->acl->rownerID), &strRownerUuid))
        {
        	return nullptr;
        }
        jstring jStrRownerUuid = env->NewStringUTF(strRownerUuid);
        OICFree(strRownerUuid);
        if (!jStrRownerUuid)
        {
        	return nullptr;
        }
        
        env->CallVoidMethod(jAcl, g_mid_OcOicSecAcl_set_rownerID, jStrRownerUuid);
        if (env->ExceptionCheck())
        {
            return nullptr;
        }
        env->DeleteLocalRef(jStrRownerUuid);
        
        jobject jAcesList = env->NewObject(g_cls_LinkedList, g_mid_LinkedList_ctor);
        if (!jAcesList)
        {
            return nullptr;
        }
        
        // List of ACEs
        OicSecAce_t *acesHead = aclResult->acl->aces;
        for (OicSecAce_t *ace = acesHead; ace != NULL; ace=ace->next)
        {
        	jobject jAce = env->NewObject(g_cls_OcOicSecAcl_ace, g_mid_OcOicSecAcl_ace_ctor);
        	if (!jAce)
        	{
        		return nullptr;
        	}
        	
        	// SubjectType
        	jobject subject = getSubjectObjectForJava(env, ace);
        	env->CallVoidMethod(jAce, g_mid_OcOicSecAcl_ace_set_subject, subject);
		    if (env->ExceptionCheck())
		    {
			    return nullptr;
		    }
        	
        	// Permission
        	jint jPermission = (unsigned int)ace->permission;
        	env->CallVoidMethod(jAce, g_mid_OcOicSecAcl_ace_set_permissions, jPermission);
        	if (env->ExceptionCheck())
		    {
			    return nullptr;
		    }
		
		    // AceId
		    jint jAceId = (unsigned int)ace->aceid;
        	env->CallVoidMethod(jAce, g_mid_OcOicSecAcl_ace_set_aceid, jAceId);
        	if (env->ExceptionCheck())
		    {
			    return nullptr;
		    }
		
		    // Resources
		    jobject jResourceList = setResourceListForJavaACL(env, ace->resources);
		    env->CallVoidMethod(jAce, g_mid_OcOicSecAcl_ace_set_resources, jResourceList);
		    if (env->ExceptionCheck())
		    {
		        return nullptr;
		    }
		    env->DeleteLocalRef(jResourceList);
		
		    // Validities
		
		    // Add ACE to List
		    env->CallBooleanMethod(jAcesList, g_mid_LinkedList_add_object, jAce);
            if (env->ExceptionCheck())
            {
                return nullptr;
            }
            env->DeleteLocalRef(jAce);
        }
        
        // Set List to ACL
        env->CallVoidMethod(jAcl, g_mid_OcOicSecAcl_set_aces, jAcesList);
        if (env->ExceptionCheck())
        {
            return nullptr;
        }
        env->DeleteLocalRef(jAcesList);
    }
	
	return jAcl;
}

jobject JniSecureUtils::convertOCCredToJavaCred(JNIEnv *env, PMGetCredsResult_t *credResult)
{
	jobject jCreds = env->NewObject(g_cls_OcOicSecCreds, g_mid_OcOicSecCreds_ctor);
	if (!jCreds)
    {
        return nullptr;
    }
    
    if (credResult->res == OC_STACK_OK && credResult->creds)
    {
        // RownerUUid
        char * strRownerUuid = NULL;
        if (OC_STACK_OK != ConvertUuidToStr(credResult->creds->rownerID, &strRownerUuid))
        {
        	return nullptr;
        }
        jstring jStrRownerUuid = env->NewStringUTF(strRownerUuid);
        OICFree(strRownerUuid);
        if (!jStrRownerUuid)
        {
        	return nullptr;
        }
        
        env->CallVoidMethod(jCreds, g_mid_OcOicSecCreds_set_rownerID, jStrRownerUuid);
        if (env->ExceptionCheck())
        {
            return nullptr;
        }
        env->DeleteLocalRef(jStrRownerUuid);
        
        jobject jCredList = env->NewObject(g_cls_LinkedList, g_mid_LinkedList_ctor);
        if (!jCredList)
        {
            return nullptr;
        }
        
        // List of credentials
        OicSecCred_t *credsHead = credResult->creds->creds;
        for (OicSecCred_t *cred = credsHead; cred != NULL; cred = cred->next)
        {
        	jobject jCred = env->NewObject(g_cls_OcOicSecCreds_cred, g_mid_OcOicSecCreds_cred_ctor);
        	if (!jCred)
        	{
        		return nullptr;
        	}
		
		    // CredId
		    jint jCredId = (unsigned int)cred->credId;
        	env->CallVoidMethod(jCred, g_mid_OcOicSecCreds_cred_set_credid, jCredId);
        	if (env->ExceptionCheck())
		    {
			    return nullptr;
		    }
		
		    // SubjectType
		    char *strSubject = NULL;
		    if (OC_STACK_OK != ConvertUuidToStr(&(cred->subject), &strSubject))
		    {
			    return nullptr;
		    }
		    jstring jStrSubject = env->NewStringUTF(strSubject);
		    OICFree(strSubject);
		    if (!jStrSubject)
		    {
			    return nullptr;
		    }
        	env->CallVoidMethod(jCred, g_mid_OcOicSecCreds_cred_set_subject, jStrSubject);
		    if (env->ExceptionCheck())
		    {
			    return nullptr;
		    }
		
		    // OicSecRole
		    // If roleId is all zeros, this property is not set in response
		    OicSecRole_t EMPTY_ROLE = { .id = { 0 }, .authority = { 0 } };
		    jobject jRole = NULL;
		    if (0 != memcmp(&cred->roleId.id, &EMPTY_ROLE.id, sizeof(EMPTY_ROLE.id)))
		    {
			    char *roleId = cred->roleId.id;
			    jstring jStrRoleId = env->NewStringUTF(roleId);
			    if (!jStrRoleId)
			    {
				    return nullptr;
			    }
			
			    jstring jStrRoleAuthority = env->NewStringUTF("");
			    if (0 != memcmp(&cred->roleId.authority, &EMPTY_ROLE.authority, sizeof(EMPTY_ROLE.authority)))
			    {
				    char *roleAuthority = cred->roleId.authority;
				    jStrRoleAuthority = env->NewStringUTF(roleAuthority);
				    if (!jStrRoleAuthority)
				    {
					    return nullptr;
				    }
			    }
		
			    jRole = env->NewObject(g_cls_OcOicSecCreds_cred_role, g_mid_OcOicSecCreds_cred_role_ctor, jStrRoleId, jStrRoleAuthority);
			    env->DeleteLocalRef(jStrRoleId);
			    env->DeleteLocalRef(jStrRoleAuthority);
			
			    env->CallVoidMethod(jCred, g_mid_OcOicSecCreds_cred_set_role, jRole);
			    if (env->ExceptionCheck())
			    {
				    return nullptr;
			    }
			    env->DeleteLocalRef(jRole);
		    }
		
		
		    // CredType
		    jint jCredType = (unsigned int)cred->credType;
        	env->CallVoidMethod(jCred, g_mid_OcOicSecCreds_cred_set_credtype, jCredType);
        	if (env->ExceptionCheck())
		    {
			    return nullptr;
		    }
		
		    // CredUsage
		    if (cred->credUsage)
		    {
		        jstring jStrCredUsage = env->NewStringUTF(cred->credUsage);
		        if (!jStrCredUsage)
		        {
			        return nullptr;
		        }
                
                env->CallVoidMethod(jCred, g_mid_OcOicSecCreds_cred_set_credusage, jStrCredUsage);
                if (env->ExceptionCheck())
                {
                    return nullptr;
                }
                env->DeleteLocalRef(jStrCredUsage);
		    }
		
		    // Add Cred to List
		    env->CallBooleanMethod(jCredList, g_mid_LinkedList_add_object, jCred);
            if (env->ExceptionCheck())
            {
                return nullptr;
            }
            env->DeleteLocalRef(jCred);
        }
        
        // Set List to Creds
        env->CallVoidMethod(jCreds, g_mid_OcOicSecCreds_set_creds, jCredList);
        if (env->ExceptionCheck())
        {
            return nullptr;
        }
        env->DeleteLocalRef(jCredList);
    }
	
	return jCreds;
}

