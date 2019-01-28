/*
 * *****************************************************************
 *
 *  Copyright 2018 DEKRA Testing and Certification, S.A.U. All Rights Reserved.
 *
 *  ******************************************************************
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
 *  ******************************************************************
 */
 
package org.iotivity.base;
 
import java.security.InvalidParameterException;
import java.util.EnumSet;
 
public class OicSecCred {
    private int credID;
    private String subject;
    private CredSubjectRole role;
    private EnumSet<CredType> credTypes;
    private String credUsage;
    
    public OicSecCred() {
    }
    
    public OicSecCred(int credID, String subject, CredSubjectRole role,
            EnumSet<CredType> credTypes, String credUsage) {
        this.credID = credID;
        this.subject = subject;
        this.role = role;
        this.credTypes = credTypes;
        this.credUsage = credUsage;
    }
    
    public int getCredID() {
        return credID;
    }
    
    public void setCredID(int credID) {
        this.credID = credID;
    }
    
    public String getSubject() {
        return subject;
    }

    public void setSubject(String subject) {
        this.subject = subject;
    }
    
    public CredSubjectRole getRole() {
    	return role;
    }
    
    public void setRole(CredSubjectRole role) {
    	this.role = role;
    }

    public EnumSet<CredType> getCredType() {
        return credTypes;
    }
    
    public void setCredType(int credType) {
        this.credTypes = CredType.convertToEnumSet(credType);
    }
    
    public String getCredUsage() {
        return credUsage;
    }
    
    public void setCredUsage(String credUsage) {
        this.credUsage = credUsage;
    }
 }
 
