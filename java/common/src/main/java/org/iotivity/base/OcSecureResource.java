/*
 *******************************************************************
 *
 * Copyright 2015 Samsung Electronics All Rights Reserved.
 *
 *-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
 */

package org.iotivity.base;

import java.util.List;
import java.util.ArrayList;
import java.util.EnumSet;
import java.util.Map;

public class OcSecureResource {

    private OcSecureResource(long nativeHandle) {
        this.mNativeHandle = nativeHandle;
    }

    /**
     *  Method to Start Ownership Transfer of an un-owned device.
     *
     *  @param doOwnershipTransferListener  Callback function, which will be called after
     *                                      completion of ownership Transfer.
     *  @throws OcException Failed transfer ownership.
     *                      Use OcException.GetErrorCode() for more details.
     */
    public native void doOwnershipTransfer(DoOwnershipTransferListener doOwnershipTransferListener)
        throws OcException;

    /**
     *  Method removes device credential from all devices in subnet
     *
     *  @param timeout               Maximum wait time for owned device discovery in seconds.
     *  @param removeDeviceListener  Callback function, which will be called after
     *                               completion of removing device.
     *  @throws OcException Failed to remove credential.
     *                      Use OcException.GetErrorCode() for more details.
     */
    public native void removeDevice(int timeout,  RemoveDeviceListener removeDeviceListener)
        throws OcException;

    /**
     *  Method resets the target device
     *
     *  @param timeout              Maximum wait time for owned device discovery in seconds.
     *  @param resetDeviceListener  Callback function, which will be called after
     *                              completion of reseting device.
     *  @throws OcException Failed to reset device.
     *                      Use OcException.GetErrorCode() for more details.
     */
    public native void resetDevice(int timeout,  ResetDeviceListener resetDeviceListener)
        throws OcException;

    /**
     *  Method removes the credential and relationship between the two devices.
     *
     *  @param device2                      Second device
     *  @param unlinkDevicesListener        Callback function, which will be called after
     *                                      completion of removing device.
     *  @throws OcException Failed to remove credential.
     *                      Use OcException.GetErrorCode() for more details.
     */
    public native void unlinkDevices(Object device2, UnlinkDevicesListener unlinkDevicesListener)
        throws OcException;

    /**
     *  Method removes the credential and relationship between the two devices.
     *
     *  @param credTypeSet OR'ed Cred Types
     *  @param keysize key size
     *  @param device2 Second device
     *  @param provisionCredentialsListener Callback function, which will be called after
     *                                      completion of removing device.
     *  @throws OcException Failed to remove the credential.
     *                      Use OcException.GetErrorCode() for more details.
     */
    public void provisionCredentials(EnumSet<CredType> credTypeSet, KeySize keysize, Object device2,
            ProvisionCredentialsListener provisionCredentialsListener) throws OcException {
        int credTypeInt = 0;

        for (CredType credType : CredType.values()) {
            if (credTypeSet.contains(credType))
                credTypeInt |= credType.getValue();
        }
        this.provisionCredentials1(credTypeInt, keysize.getValue(),
                device2, provisionCredentialsListener);
    }
    private native void provisionCredentials1(int type, int keySize, Object device2,
            ProvisionCredentialsListener provisionCredentialsListener)
        throws OcException;

    /**
     *  Method to provision the Trust certificate chain to secured device.
     *
     *  @param credTypeSet           OR'ed Cred Types
     *  @param credId                id of cert
     *  @param provisionTrustCertChainListener Callback function, which will be called after
     *                                      proviosion trust certificate chain.
     *  @throws OcException Failed to provision the Trust certificate chain.
     *                      Use OcException.GetErrorCode() for more details.
     */
    public void provisionTrustCertChain(EnumSet<CredType> credTypeSet, int credId,
            ProvisionTrustCertChainListener provisionTrustCertChainListener) throws OcException {
        int credTypeInt = 0;

        for (CredType credType : CredType.values()) {
            if (credTypeSet.contains(credType))
                credTypeInt |= credType.getValue();
        }
        this.provisionTrustCertChain1(credTypeInt, credId,
                provisionTrustCertChainListener);
    }
    private native void provisionTrustCertChain1(int credType, int credId,
            ProvisionTrustCertChainListener provisionTrustCertChainListener)
        throws OcException;

    /**
     *  Method to provision a certificate to a secured device.
     *
     *  @param pemCert Certificate to provision, encoded as PEM.
     *  @param provisionCertificateListener Callback function, which will be called when
     *                                      provisioning request receives a response from
                                            first resource server.
     *  @throws OcException Failed to provision the certificate.
     *                      Use OcException.GetErrorCode() for more details.
     */
    public native void provisionCertificate(String pemCert,
            ProvisionCertificateListener provisionCertificateListener) throws OcException;
        
    /**
     *  Method to provision an identity certificate to a secured device.
     *
     *  @param provisionIdentityCertificateListener Callback function, which will be called when
     *                                      provisioning request receives a response from
                                            first resource server.
     *  @throws OcException Failed to provision the certificate.
     *                      Use OcException.GetErrorCode() for more details.
     */
    public native void provisionIdentityCertificate(ProvisionCertificateListener provisionCertificateListener) throws OcException;
    
    /**
     *  Method to provision a role certificate to a secured device.
     *
     *  @param role Role to provision
     *  @param authority Authority for the role
     *  @param provisionRoleCertificateListener Callback function, which will be called when
     *                                      provisioning request receives a response from
                                            first resource server.
     *  @throws OcException Failed to provision the certificate.
     *                      Use OcException.GetErrorCode() for more details.
     */
    public native void provisionRoleCertificate(String role, String authority, ProvisionCertificateListener provisionCertificateListener) throws OcException;

	/**
     *  Method retrieves ACL information from resource.
     *
     *  @param getACLListener         Callback function, which will be called after
     *                                      completion of get acl resource for a device.
     *  @throws OcException Failed to retrieve ACL information.
     *                      Use OcException.GetErrorCode() for more details.
     */
    public native void getACL(GetAclListener getACLListener)
        throws OcException;

    /**
     *  Method send ACL information to resource.
     *
     *  @param acl object
     *  @param provisionACLListener         Callback function, which will be called after
     *                                      completion of removing device.
     *  @throws OcException Failed to send ACL information.
     *                      Use OcException.GetErrorCode() for more details.
     */
    public native void provisionACL(Object acl, ProvisionAclListener provisionACLListener)
        throws OcException;
        
    /**
     *  Method deletes ACE from ACL resource.
     *
     *  @param aceId              ID of the ACE to be deleted.
     *  @param deleteACEListener  Callback function, which will be called after
     *                              completion of ACE deletion.
     *  @throws OcException Failed to delete ACE.
     *                      Use OcException.GetErrorCode() for more details.
     */
    public native void deleteACE(int aceId,  DeleteACEListener deleteACEListener)
        throws OcException;
        
    /**
     *  Method retrieves credentials information from resource.
     *
     *  @param getCredentialsListener       Callback function, which will be called after
     *                                      completion of get acl resource for a device.
     *  @throws OcException Failed to retrieve credentials information.
     *                      Use OcException.GetErrorCode() for more details.
     */
    public native void getCredentials(GetCredentialsListener getCredentialsListener)
        throws OcException;
        
    /**
     *  Method deletes credential from credentials resource.
     *
     *  @param credId              ID of the credential to be deleted.
     *  @param deleteCredentialListener  Callback function, which will be called after
     *                              completion of credential deletion.
     *  @throws OcException Failed to delete credential.
     *                      Use OcException.GetErrorCode() for more details.
     */
    public native void deleteCredential(int credId,  DeleteCredentialListener deleteCredentialListener)
        throws OcException;

    /**
     *  Method provisions credentials between two devices and ACLs for the devices who
     *  act as a server.
     *
     *  @param credTypeSet OR'ed Cred Types
     *  @param keysize keySize
     *  @param acl1 First acl
     *  @param device2 Second device
     *  @param acl2 Second acl
     *  @param provisionPairwiseDevicesListener Callback function, which will be called after
     *                                      completion of removing device.
     *  @throws OcException Failed to provision credentials.
     *                      Use OcException.GetErrorCode() for more details.
     */
    public void provisionPairwiseDevices(EnumSet<CredType> credTypeSet, KeySize keysize, Object acl1,
            Object device2, Object acl2,
            ProvisionPairwiseDevicesListener provisionPairwiseDevicesListener) throws OcException {
        int credTypeInt = 0;

        for (CredType credType : CredType.values()) {
            if (credTypeSet.contains(credType))
                credTypeInt |= credType.getValue();
        }
        this.provisionPairwiseDevices1(credTypeInt, keysize.getValue(), acl1, device2,
                acl2, provisionPairwiseDevicesListener);
    }
    private native void provisionPairwiseDevices1(int type, int keySize, Object acl1,
            Object device2, Object acl2,
            ProvisionPairwiseDevicesListener provisionPairwiseDevicesListener) throws OcException;

    /**
     *  Method to configure resource for direct pairing
     *
     *  @param pin                      pin number
     *  @param pdacls                   Array of Device Pairing Access Control List
     *  @param type                     List of supported OcPrmType
     *  @param edp                      enable (1) / disable (0)
     *  @param provisionDirectPairingListener   Callback function, which will be called after completion
     *                                  of Direct Pairing.
     *  @throws OcException Failed to configure resource.
     *                      Use OcException.GetErrorCode() for more details.
     */

    public void doProvisionDirectPairing(String pin, OicSecPdAcl[] pdacls, List<OcPrmType> type,
            boolean edp , ProvisionDirectPairingListener provisionDirectPairingListener)
        throws OcException {

        int[] typeArray = new int[type.size()];
        int i = 0;
        for (OcPrmType ocPrmType:type) {
            typeArray[i++] = ocPrmType.getValue();
        }

        this.provisionDirectPairing(pin, pdacls, typeArray, (edp ? 1: 0), provisionDirectPairingListener);
    }

    private native void provisionDirectPairing(String pin, OicSecPdAcl[] pdacls, int[] type,
            int edp , ProvisionDirectPairingListener provisionDirectPairingListener)
        throws OcException;

    public void selectOTMethod(OxmType oxmType,
            SelectOTMMethodListener selectOTMMethodListener) throws OcException {
        this.selectOTMethod0(oxmType.getValue(), selectOTMMethodListener);
    }

    /**
     * API to select OTM method.
     *
     * @param oxmType Method to be selected
     * @param selectOTMMethodListener Callback function, which will be called after completion
     *
     * @throws OcException Indicate failure selecting OTM method
     */
    private native void selectOTMethod0(int oxmType,
            SelectOTMMethodListener selectOTMMethodListener) throws OcException;
			
	public void setOTMethod(OxmType oxmType) throws OcException {
        this.setOTMethod0(oxmType.getValue());
    }

    /**
     * API to set OTM method.
     *
     * @param oxmType Method to be selected
     *
     * @throws OcException Indicate failure setting OTM method
     */
    private native void setOTMethod0(int oxmType) throws OcException;

    /**
     * API to select OTM method.
     *
     * @param oxmType Method to be selected
     * @param selectOTMMethodListener Callback function, which will be called after completion
     *
     * @throws OcException Indicate failure selecting OTM method
     */
    public void selectMOTMethod(OxmType oxmType,
            SelectOTMMethodListener selectOTMMethodListener) throws OcException {
        this.selectMOTMethod0(oxmType.getValue(), selectOTMMethodListener);
    }

    private native void selectMOTMethod0(int oxmType,
            SelectOTMMethodListener selectOTMMethodListener) throws OcException;

    /**
     * API to change Multiple Owner Transfer(MOT) mode.
     *
     * @param momType MOT mode to be selected.
     * @param changeMOTModeListener Callback function, which will be called after completion
     *
     * @throws OcException Indicate failure changing the MOT mode
     */
    public void changeMOTMode(MomType momType,
            ChangeMOTModeListener changeMOTModeListener) throws OcException {
        this.changeMOTMode0(momType.getValue(), changeMOTModeListener);
    }

    private native void changeMOTMode0(int momType,
            ChangeMOTModeListener changeMOTModeListener) throws OcException;

    /**
     * API to Add preConfigured PIN to local SVR DB.
     *
     * @param pin string to be saved in svr db.
     *
     * @throws OcException Indicate failure adding PIN
     */
    public void addPreConfigPIN(String pin) throws OcException {
        this.addPreConfigPIN0(pin, pin.length());
    }

    private native void addPreConfigPIN0(String pin, int pinLength) throws OcException;

    /**
     * API to provision preConfigured PIN.
     *
     * @param pin to be used while authentication.
     * @param provisionPreConfigPINListener Callback function, which will be called after
     *                                      completion
     *
     * @throws OcException Indicate failure provisioning PIN
     */
    public void  provisionPreConfigPIN(String pin,
            ProvisionPreConfigPINListener provisionPreConfigPINListener) throws OcException {
        this.provisionPreConfigPIN0(pin, pin.length(), provisionPreConfigPINListener);
    }

    private native void provisionPreConfigPIN0(String pin, int pinLength,
            ProvisionPreConfigPINListener provisionPreConfigPINListener) throws OcException;

    /**
     * API to  do Multiple Ownership Transfer for MOT enabled devices.
     *
     * @param doMultipleOwnershipTransferListener Callback function, which will
     *                                          be called after completion.
     */
    public native void doMultipleOwnershipTransfer(
            DoMultipleOwnershipTransferListener doMultipleOwnershipTransferListener);

    /**
     * selectOTMMethodListener can be registered with selectOTMMethod call.
     * Listener notified asynchronously.
     */
    public interface SelectOTMMethodListener {
        public void selectOTMMethodListener(List<ProvisionResult> provisionResultList,
                int hasError);
    }

    /**
     * changeMOTModeListener can be registered with changeMOTMode call.
     * Listener notified asynchronously.
     */
    public interface ChangeMOTModeListener {
        public void changeMOTModeListener(List<ProvisionResult> provisionResultList,
                int hasError);
    }

    /**
     * provisionPreConfigPINListener can be registered with ProvisionPreConfigPIN call.
     * Listener notified asynchronously.
     */
    public interface ProvisionPreConfigPINListener {
        public void provisionPreConfigPINListener(List<ProvisionResult> provisionResultList,
                int hasError);
    }

    /**
     * doMultipleOwnershipTransferListener can be registered with doMultipleOwnershipTransfer
     * call.
     * Listener notified asynchronously.
     */
    public interface DoMultipleOwnershipTransferListener {
        public void doMultipleOwnershipTransferListener(List<ProvisionResult> provisionResultList,
                int hasError);
    }

    /**
     * provisionDirectPairingListener can be registered with doOwnershipTransfer
     * call.
     * Listener notified asynchronously.
     */
    public interface ProvisionDirectPairingListener {
        public void provisionDirectPairingListener(List<ProvisionResult> provisionResultList,
                int hasError);
    }

    /**
     * doOwnershipTransferListener can be registered with doOwnershipTransfer
     * call.
     * Listener notified asynchronously.
     */
    public interface DoOwnershipTransferListener {
        public void doOwnershipTransferListener(List<ProvisionResult> provisionResultList,
                int hasError);
    }

    /**
     * removeDeviceListener can be registered with removeDeviceListener
     * call.
     * Listener notified asynchronously.
     */
    public interface RemoveDeviceListener {
        public void removeDeviceListener(List<ProvisionResult> provisionResultList,
                int hasError);
    }

    /**
     * resetDeviceListener can be registered with resetDeviceListener
     * call.
     * Listener notified asynchronously.
     */
    public interface ResetDeviceListener {
        public void resetDeviceListener(List<ProvisionResult> provisionResultList,
                int hasError);
    }

    /**
     * unlinkDevicesListener can be registered with unlinkDevicesListener
     * call.
     * Listener notified asynchronously.
     */
    public interface UnlinkDevicesListener {
        public void unlinkDevicesListener(List<ProvisionResult> provisionResultList,
                int hasError);
    }

    /**
     * provisionCredentialsListener can be registered with provisionCredentialsListener
     * call.
     * Listener notified asynchronously.
     */
    public interface ProvisionCredentialsListener {
        public void provisionCredentialsListener(List<ProvisionResult> provisionResultList,
                int hasError);
    }

    /**
     * provisionTrustCertChainListener can be registered with ProvisionTrustCertChainListener
     * call.
     * Listener notified asynchronously.
     */
    public interface ProvisionTrustCertChainListener {
        public void provisionTrustCertChainListener(List<ProvisionResult> provisionResultList,
                int hasError);
    }

    /**
     * provisionCertificateListener can be registered with ProvisionCertificateListener
     * call.
     * Listener notified asynchronously.
     */
    public interface ProvisionCertificateListener {
        public void provisionCertificateListener(List<ProvisionResult> provisionResultList,
                int hasError);
    }

	/**
     * getAclListener can be registered with getAclListener
     * call.
     * Listener notified asynchronously.
     */
    public interface GetAclListener {
        public void getAclListener(OicSecAcl aclResultList, int hasError);
    }

    /**
     * provisionAclListener can be registered with provisionAclListener
     * call.
     * Listener notified asynchronously.
     */
    public interface ProvisionAclListener {
        public void provisionAclListener(List<ProvisionResult> provisionResultList,
                int hasError);
    }
    
    /**
     * deleteACEListener can be registered with deleteACEListener
     * call.
     * Listener notified asynchronously.
     */
    public interface DeleteACEListener {
        public void deleteACEListener(List<ProvisionResult> provisionResultList,
                int hasError);
    }
    
    /**
     * getCredentialListener can be registered with getCredentialListener
     * call.
     * Listener notified asynchronously.
     */
    public interface GetCredentialsListener {
        public void getCredentialsListener(OicSecCreds credsResultList, int hasError);
    }
    
    /**
     * deleteCredentialListener can be registered with deleteCredentialListener
     * call.
     * Listener notified asynchronously.
     */
    public interface DeleteCredentialListener {
        public void deleteCredentialListener(List<ProvisionResult> provisionResultList,
                int hasError);
    }

    /**
     * provisionPairwiseDevicesListener can be registered with provisionPairwiseDevicesListener
     * call.
     * Listener notified asynchronously.
     */
    public interface ProvisionPairwiseDevicesListener {
        public void provisionPairwiseDevicesListener(List<ProvisionResult> provisionResultList,
                int hasError);
    }

    /** Method to get List of device ID of devices linked with invoking device.
     *
     *  @return Sring List  List of device id's of linked devices.
     *  @throws OcException Failed to get linked devices.
     *                      Use OcException.GetErrorCode() for more details.
     */
    public native List<String> getLinkedDevices() throws OcException;

     /**
      * Method to get IP address of sercure discovered device.
      * @return Stringified IP address.
      */
    public native String getIpAddr();
    
    /**
      * Method to get port of sercure discovered device.
      * @return device port.
      */
    public native String getPort();

    /**
     * Method to get device id of a device.
     * @return  Device ID of the selected device.
     */
    public native String getDeviceID();

    /**
     * Method to get device status (ON/OFF) of a device.
     * @return      ON/OFF
     * @throws OcException Failed to get device status.
     *                     Use OcException.GetErrorCode() for more details.
     */

    public DeviceStatus getDeviceStatus() throws OcException {
        return DeviceStatus.convertDeviceStatus(this.deviceStatus());
    }
    public native int deviceStatus() throws OcException;

    /**
     * Method to get device  ownership (OWNED/UNOWNED) status.
     * @return      OWNED/UNOWNED
     * @throws OcException Failed to get ownership status.
     *                     Use OcException.GetErrorCode() for more details.
     */

    public OwnedStatus getOwnedStatus() throws OcException {
        return  OwnedStatus.convertOwnedStatus(this.ownedStatus());
    }
    public native int ownedStatus() throws OcException;

    /*
     * Method to get device supported OxM.
     * @return list of supported OxM.
     * @throws OcException Failed to get supported OxM.
     *                     Use OcException.GetErrorCode() for more details.
     */
    public List<OxmType> getSupportedOTMethods() throws OcException {
        List<OxmType> otms = new ArrayList<>();
        int[] intOtms = this.getSupportedOTMethods1();
        for (int i = 0; i < intOtms.length; i++)
        {
            otms.add(OxmType.convertOxmType(intOtms[i]));
        }
        return otms;
    }
    public native int[] getSupportedOTMethods1() throws OcException;

    @Override
    protected void finalize() throws Throwable {
        super.finalize();
        dispose();
    }

    private native void dispose();

    private long mNativeHandle;
}
