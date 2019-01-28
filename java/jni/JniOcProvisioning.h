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
#include "JniOcStack.h"
#include "OCProvisioningManager.hpp"
#include "JniSecureUtils.h"
#include "oxmjustworks.h"
#include "oxmrandompin.h"
#include <jni.h>
#include <mutex>

#ifndef _Included_org_iotivity_base_OcProvisioning
#define _Included_org_iotivity_base_OcProvisioning

/* DO NOT EDIT THIS FILE - it is machine generated */
/* Header for class org_iotivity_base_OcProvisioning */

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_iotivity_base_OcProvisioning
 * Method:    ownershipTransferCDdata
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_iotivity_base_OcProvisioning_ownershipTransferCBdata
  (JNIEnv *, jobject, jint, jobject);

/*
 * Class:     org_iotivity_base_OcProvisioning
 * Method:    discoverUnownedDevices
 * Signature: (I)[Lorg/iotivity/base/OcSecureResource;
 */
JNIEXPORT jobjectArray JNICALL Java_org_iotivity_base_OcProvisioning_discoverUnownedDevices1
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_iotivity_base_OcProvisioning
 * Method:    provisionInit
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_iotivity_base_OcProvisioning_provisionInit
  (JNIEnv *, jclass, jstring);

/*
 * Class:     org_iotivity_base_OcProvisioning
 * Method:    provisionClose
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_iotivity_base_OcProvisioning_provisionClose
  (JNIEnv *, jclass);

/*
 * Class:     org_iotivity_base_OcProvisioning
 * Method:    discoverOwnedDevices
 * Signature: (I)[Lorg/iotivity/base/OcSecureResource;
 */
JNIEXPORT jobjectArray JNICALL Java_org_iotivity_base_OcProvisioning_discoverOwnedDevices1
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_iotivity_base_OcProvisioning
 * Method:    discoverSingleDevice
 * Signature: (ILjava/lang/String;)Lorg/iotivity/base/OcSecureResource;
 */
JNIEXPORT jobject JNICALL Java_org_iotivity_base_OcProvisioning_discoverSingleDevice
  (JNIEnv *, jclass, jint, jstring);
  
/*
 * Class:     org_iotivity_base_OcProvisioning
 * Method:    discoverSingleDeviceInUnicast
 * Signature: (ILjava/lang/String;Ljava/lang/String;I)Lorg/iotivity/base/OcSecureResource;
 */
JNIEXPORT jobject JNICALL Java_org_iotivity_base_OcProvisioning_discoverSingleDeviceInUnicast
  (JNIEnv *, jclass, jint, jstring, jstring, jint);

/*
 * Class:     org_iotivity_base_OcProvisioning
 * Method:    setDisplayPinListener
 * Signature: (Lorg/iotivity/base/OcProvisioning/DisplayPinListener;)V
 */
JNIEXPORT void JNICALL Java_org_iotivity_base_OcProvisioning_setDisplayPinListener
  (JNIEnv *, jclass, jobject);

/*
 * Class:     org_iotivity_base_OcProvisioning
 * Method:    setDisplayNumListener
 * Signature: (Lorg/iotivity/base/OcProvisioning/DisplayNumListener;)V
 */
JNIEXPORT void JNICALL Java_org_iotivity_base_OcProvisioning_setDisplayNumListener
  (JNIEnv *, jclass, jobject);

/*
 * Class:     org_iotivity_base_OcProvisioning
 * Method:    unsetDisplayNumListener
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_iotivity_base_OcProvisioning_unsetDisplayNumListener
  (JNIEnv *, jclass);

/*
 * Class:     org_iotivity_base_OcProvisioning
 * Method:    setConfirmNumListener
 * Signature: (Lorg/iotivity/base/OcProvisioning/ConfirmNumListener;)V
 */
JNIEXPORT void JNICALL Java_org_iotivity_base_OcProvisioning_setConfirmNumListener
  (JNIEnv *, jclass, jobject);

/*
 * Class:     org_iotivity_base_OcProvisioning
 * Method:    unsetConfirmNumListener
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_iotivity_base_OcProvisioning_unsetConfirmNumListener
  (JNIEnv *, jclass);

/*
 * Class:     org_iotivity_base_OcProvisioning
 * Method:    setMVJustWorksOptions0
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_iotivity_base_OcProvisioning_setMVJustWorksOptions0
(JNIEnv *, jclass, jint);
/*
 * Method:    discoverMOTEnabledDevices1
 * Signature: (I)[Lorg/iotivity/base/OcSecureResource;
 */
JNIEXPORT jobjectArray JNICALL Java_org_iotivity_base_OcProvisioning_discoverMOTEnabledDevices1
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_iotivity_base_OcProvisioning
 * Method:    discoverMOTEnabledOwnedDevices1
 * Signature: (I)[Lorg/iotivity/base/OcSecureResource;
 */
JNIEXPORT jobjectArray JNICALL Java_org_iotivity_base_OcProvisioning_discoverMOTEnabledOwnedDevices1
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_iotivity_base_OcProvisioning
 * Method:    getDevicestatusLists
 * Signature: (I)[Lorg/iotivity/base/OcSecureResource;
 */
JNIEXPORT jobjectArray JNICALL Java_org_iotivity_base_OcProvisioning_getDeviceStatusList1
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_iotivity_base_OcProvisioning
 * Method:    saveTrustCertChain1
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_iotivity_base_OcProvisioning_saveTrustCertChain1
    (JNIEnv *, jobject, jbyteArray, jint);

/*
 * Class:     org_iotivity_base_OcProvisioning
 * Method:    provisionOwnCertificate
 * Signature: ([Ljava/lang/Byte;[Ljava/lang/Byte;)I
 */
JNIEXPORT jint JNICALL Java_org_iotivity_base_OcProvisioning_provisionOwnCertificate
    (JNIEnv *, jclass, jbyteArray, jbyteArray);

/*
 * Class:     org_iotivity_base_OcProvisioning
 * Method:    setPinType0
 * Signature: (II)I
 */
JNIEXPORT void JNICALL Java_org_iotivity_base_OcProvisioning_setPinType0
  (JNIEnv *, jclass, jint, jint);


/*
 * Class:     org_iotivity_base_OcProvisioning
 * Method:    saveACL
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_org_iotivity_base_OcProvisioning_saveACL
  (JNIEnv *, jclass, jobject);

/*
 * Class:     org_iotivity_base_OcProvisioning
 * Method:    doSelfOwnershiptransfer
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_iotivity_base_OcProvisioning_doSelfOwnershiptransfer
  (JNIEnv *, jclass);

/*
 * Class:     org_iotivity_base_OcProvisioning
 * Method:    setDeviceIdSeed1
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_iotivity_base_OcProvisioning_setDeviceIdSeed1
  (JNIEnv *, jobject, jbyteArray);

/*
 * Class:     org_iotivity_base_OcProvisioning
 * Method:    setPeerCnVerifyListener
 * Signature: (Lorg/iotivity/base/OcProvisioning/PeerCnVerifyListener;)V
 */
JNIEXPORT void JNICALL Java_org_iotivity_base_OcProvisioning_setPeerCnVerifyListener
  (JNIEnv *, jclass, jobject);
  
/*
 * Class:     org_iotivity_base_OcProvisioning
 * Method:    resetSvrDb
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_iotivity_base_OcProvisioning_resetSvrDb
  (JNIEnv *, jclass);
#ifdef __cplusplus
}
#endif
#endif
