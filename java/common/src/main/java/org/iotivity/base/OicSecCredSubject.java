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

/**
 * Credential subjects
 */
public class OicSecCredSubject {
	private CredSubjectType subjectType;
	private String uuid;
	private CredSubjectRole role;
	
	public OicSecCredSubject(int subjectType, String uuid, CredSubjectRole role) {
		this.subjectType = CredSubjectType.convertSubjectType(subjectType);
		this.uuid = uuid;
		this.role = role;
	}
	
	public CredSubjectType getSubjectType() {
		return subjectType;
	}
	
	public int getIntSubjectType() {
	    return subjectType.getValue();
	}
	
	public void setSubjectType(CredSubjectType subjectType) {
		this.subjectType = subjectType;
	}
	
	public String getUuid() {
		return uuid;
	}
	
	public void setUuid(String uuid) {
		this.uuid = uuid;
	}
	
	public CredSubjectRole getRole() {
		return role;
	}
	
	public void setRole(CredSubjectRole role) {
		this.role = role;
	}
}

