/*
 *******************************************************************
 *
 * Copyright 2015 Dekra Testing and Certification S.A.U.
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

/**
 * ACE subjects
 */
public class OicSecAceSubject {
	private AceSubjectType subjectType;
	private String uuid;
	private AceSubjectRole role;
	private String connType;
	
	public OicSecAceSubject (int subjectType, String uuid, AceSubjectRole role, String connType) {
		this.subjectType = AceSubjectType.convertSubjectType(subjectType);
		this.uuid = uuid;
		this.role = role;
		this.connType = connType;
	}
	
	public AceSubjectType getSubjectType() {
		return subjectType;
	}
	
	public int getIntSubjectType() {
	    return subjectType.getValue();
	}
	
	public void setSubjectType(AceSubjectType subjectType) {
		this.subjectType = subjectType;
	}
	
	public String getUuid() {
		return uuid;
	}
	
	public void setUuid(String uuid) {
		this.uuid = uuid;
	}
	
	public AceSubjectRole getRole() {
		return role;
	}
	
	public void setRole(AceSubjectRole role) {
		this.role = role;
	}
	
	public String getConnType() {
		return connType;
	}
	
	public void setConnType() {
		this.connType = connType;
	}
}
