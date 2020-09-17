CONST OfficeAppId  = "0ff1ce15-a989-479d-af46-f275c6370663"
CONST MSG_LICSTATUS                     = "LICENSE STATUS: "
CONST MSG_LICENSED                      = " ---LICENSED--- "
CONST MSG_UNLICENSED                    = " ---UNLICENSED--- "
CONST MSG_OOBGRACE                      = " ---OOB_GRACE--- "
CONST MSG_OOTGRACE                      = " ---OOT_GRACE--- "
CONST MSG_NONGENGRACE                   = " ---NON_GENUINE_GRACE--- "
CONST MSG_NOTIFICATION                  = " ---NOTIFICATIONS--- "
CONST MSG_EXTENDEDGRACE                 = " ---EXTENDED GRACE--- "
CONST MSG_LICUNKNOWN                    = " ---UNKNOWN--- "



Dim productinstances, productClass, objWMI

Function ExecuteQuery(strSelect,strWhere,strClass)

 Set objWMI = GetObject("winmgmts:" _
                & "{impersonationLevel=impersonate}!\\" & "." & "\root\cimv2")


Set productinstances = objWMI.ExecQuery("SELECT " & strSelect & " FROM " & strClass)

End Function

Function setWmiClasses()
    productClass = "SoftwareLicensingProduct"
End Function

setWmiClasses()
ExecuteQuery "ID, Name, ApplicationId, PartialProductKey, Description,LicenseStatus , LicenseIsAddon ","ApplicationId = '" & OfficeAppId & "' " & "AND PartialProductKey <> NULL " & "AND LicenseIsAddon = FALSE",productClass
  For Each inst in productinstances
       ' intIsKms = InStr(UCase(inst.Description),"KMS")
        if inst.PartialProductKey<>"" then
	       WScript.Echo inst.PartialProductKey
	       WScript.Echo inst.Name
	       WScript.Echo inst.description	
        Select Case inst.LicenseStatus
                            Case 0
                                WScript.Echo MSG_LICSTATUS & MSG_UNLICENSED
                            Case 1
                                WScript.Echo MSG_LICSTATUS & MSG_LICENSED
                            Case 2
                                WScript.Echo MSG_LICSTATUS & MSG_OOBGRACE        
                            Case 3
                                WScript.Echo MSG_LICSTATUS & MSG_OOTGRACE
                            Case 4
                                WScript.Echo MSG_LICSTATUS & MSG_NONGENGRACE
                            Case 5
                                WScript.Echo MSG_LICSTATUS & MSG_NOTIFICATION
                            Case 6
                                WScript.Echo MSG_LICSTATUS & MSG_EXTENDEDGRACE    
                            Case Else
                                WScript.Echo MSG_LICSTATUS & MSG_LICUNKNOWN
                        End Select


        end if	               
  Next



