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
 * Subject Type.
 */
public enum AceSubjectType {
    SUBJECT_UUID(0),
    SUBJECT_ROLE(1),
    SUBJECT_CONNTYPE(2);
    
    private int value;

    private AceSubjectType(int value) {
        this.value = value;
    }

    public int getValue() {
        return this.value;
    }

    public static AceSubjectType convertSubjectType(int value) {
        if (0 == value) {
            return AceSubjectType.SUBJECT_UUID;
        }        
        else if (1 == value) {
            return AceSubjectType.SUBJECT_ROLE;
        }
        else if (2 == value) {
            return AceSubjectType.SUBJECT_CONNTYPE;
        }
        return null;
    }
}
