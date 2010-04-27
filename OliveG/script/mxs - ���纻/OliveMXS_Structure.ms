 
 fn OmsAssertMessageBox arg_Bool arg_Message = 
 (	
	
	 if arg_Bool == false or arg_Bool == undefined  then
	(
		local kAssertPrefix = "[Assert]"
		if arg_Message == undefined or arg_Message == "" then
		(
			messagebox kAssertPrefix;
		)
		else
		(
			kAssertPrefix += " - ";
			kAssertPrefix += arg_Message;
			messagebox kAssertPrefix;
		)
	)
 );
 
 struct Oms_File 
 (
	handle_File = undefined
	,
	string_FileName = "";
	,
	fn OmsOpenFile arg_FileName =
	(
		if arg_FileName == undefined then
		(
			messagebox "something wrong in Filename want to open/create"
		);
		if iskindof arg_FileName  string then
		(
			print arg_FileName;
			handle_File = createfile arg_FileName ;
			
			if handle_File == undefined then
			(
				messagebox "file exported isn't opened"
			);
			
			print "success file open";
			string_FileName = arg_FileName;
		);
	)
	,
	fn OmsCloseFile = 
	(
		if handle_File != undefined then
		(
			flush handle_File;
			close handle_File;
			print "success file close";
		)
	)
	,
	fn OmsFileHandleCheck = 
	(
		 local kbCheck = (handle_File != undefined )
		OmsAssertMessageBox kbCheck "Invalid File Handle";
	)
	,
	fn OmsWrite arg_Value =
	(
		OmsFileHandleCheck();
		format "%" arg_Value to:handle_File;
		--format "%" arg_Value; -- debug string
	)
	,
	fn OmsWritePoint3 arg_Point3 = 
	(
		OmsFileHandleCheck();
		if iskindof arg_Point3 point3 then
		(
			OmsWrite arg_Point3.x;
			OmsWrite arg_Point3.y;
			OmsWrite arg_Point3.z;
		)
	)
 )