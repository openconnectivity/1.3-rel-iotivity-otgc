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
 
 import java.util.List;

public class OicSecCreds {
    private String rownerID;
    private List<OicSecCred> oicSecCreds;
	
	public OicSecCreds () {
        super();
    }
	
    public OicSecCreds(String rownerID, List<OicSecCred> oicSecCreds) {
        super();
        this.rownerID = rownerID;
        this.oicSecCreds = oicSecCreds;
    }
    public String getRownerID() {
        return rownerID;
    }

    public void setRownerID(String rownerID) {
        this.rownerID = rownerID;
    }

    public List<OicSecCred> getOicSecCredsList() {
        return oicSecCreds;
    }

    public OicSecCred[] getOicSecCreds() {
        return oicSecCreds.toArray(new OicSecCred[oicSecCreds.size()]);
    }

    public void setOicSecCreds(List<OicSecCred> oicSecCreds) {
        this.oicSecCreds = oicSecCreds;
    }
}

