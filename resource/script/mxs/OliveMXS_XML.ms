
struct OmsXML_Printer
(
Integer_TabLevel = 1,
handle_File = Oms_File(),
count_element = 0,
count_complete_element = 0,
	fn InsertTabSpace = 
	(
		if Integer_TabLevel >0 then
		(
			for i=1 to Integer_TabLevel do
			(
				handle_File.OmsWrite "  ";	
			)
		)
	),	
	
	fn InitToSave = 
	(
		Integer_TabLevel = 0
		count_element = 0
		count_complete_element = 0
	),
	fn BeginSave = 
	(
		local strSaveName = "";
		strSaveName = (strSaveName as stringstream);
		format "export XML :  \"%\"" (getFilenameFile handle_File.string_FileName) to:strSaveName
		strSaveName = (strSaveName as string);
		progressstart strSaveName;
	),
	fn IncCompleteElementCount = 
	(
		count_complete_element += 1;
		local kprogress;
		kprogress = (count_complete_element * 100/count_element) 
		progressupdate (kprogress as integer);
	),
	fn EndSave = 
	(
		progressupdate 100.0f;
		progressend();
	),
	fn IncTabLevel = (Integer_TabLevel += 1),
	fn DecTabLevel = (Integer_TabLevel -= 1),
	fn IncElementCount = (count_element += 1)
	
)
struct OmsXML_Document 
(
Oms_TopElement ,

	fn SetTopElement arg_Element = 
	(
		Oms_TopElement = arg_Element;
	),	
		
	fn SaveXML arg_FileName = 
	(
		local kPrinter = OmsXML_Printer();
		kPrinter.handle_File.OmsOpenFile arg_FileName;
		kPrinter.InitToSave();
		kPrinter.BeginSave();
		kPrinter.handle_File.OmsWrite "<?xml version=\"1.0\" encoding=\"euc-kr\"?>\n";
		Oms_TopElement.PrepareAcceptPrinter kPrinter;
		Oms_TopElement.AcceptPrinter kPrinter;
		kPrinter.handle_File.OmsCloseFile();
		kPrinter.EndSave();
	)
);

struct OmsXML_Attribute
(
string_AttributeName = "",
string_AttributeValue = "",
	fn SetName arg_Name = (string_AttributeName = arg_Name),
	fn SetValue arg_Value = 
	(
		string_AttributeValue = string_AttributeValue as stringstream;
		format "%" arg_Value to:string_AttributeValue
		string_AttributeValue = string_AttributeValue as string;
	),
	fn Name = (return string_AttributeName;),
	fn Value = (return string_AttributeValue;)
)

struct OmsXML_Element
(
string_ElementValue = "",
string_ElementText = "",
array_Attribute = #(),
array_ChildElements = #(),
	fn PrepareAcceptPrinter arg_Printer =
	(
		arg_Printer.IncElementCount();
		for kChildElement in array_ChildElements do
		(
			kChildElement.PrepareAcceptPrinter arg_Printer;
		)
	)
	,
	fn AcceptPrinter arg_Printer = 
	(
		local khFile = arg_Printer.handle_File;
		local kStartTag = stringstream "";
		local kAttributes = "";
		
		format "<%" string_ElementValue to:kStartTag;
		kStartTag = kStartTag as string;
		
		arg_Printer.InsertTabSpace();
		
		for kAttribute in array_Attribute do
		(
			local kAttrTag = stringstream "";
			local kAttriName = kAttribute.Name();
			local kAttriValue = kAttribute.Value();
			format " %=\"%\"" kAttriName kAttriValue to:kAttrTag;
			kAttrTag = kAttrTag as string;
			kAttributes += kAttrTag;
		)

		kStartTag += kAttributes;
		
		local kChildCount = array_ChildElements.count;
		if kChildCount != 0 or string_ElementText != "" then
		(
			if kChildCount != 0 then
			(
				kStartTag += ">\n";
			)
			else
			(
				kStartTag += ">";
			)
			
			khFile.OmsWrite kStartTag;
			
			arg_Printer.IncTabLevel();
			khFile.OmsWrite string_ElementText;
			for kChildElement in array_ChildElements do
			(
				kChildElement.AcceptPrinter arg_Printer;
			)
			arg_Printer.DecTabLevel();

			local kEndTag = stringstream "";
			format "</%>\n" string_ElementValue to:kEndTag;
			kEndTag = kEndTag as string;
		
			arg_Printer.InsertTabSpace();
			khFile.OmsWrite kEndTag;
		)
		else
		(
			kStartTag += "/>\n";
			khFile.OmsWrite kStartTag ;
		)
		arg_Printer.IncCompleteElementCount();
	),
	
	fn SetValue arg_Value = 
	(
		string_ElementValue = arg_Value;
	),
	fn Value = (return string_ElementValue),
	fn SetText arg_Test = (string_ElementText = arg_Test),
	fn Text = (return string_ElementText),
	fn ChildCount = (return array_ChildElements.count),
	fn InsertChild arg_Child = 
	(
		if classof arg_Child == OmsXML_Element then
		(
			append array_ChildElements arg_Child;
		)
	),
	fn FindChildElement arg_Value = 
	(
		for i in array_ChildElements do
		(
			if i.Value() == arg_Value then
			(
				return i;
			)
		)
		return undefined;
	),

	fn InsertAttribute arg_Attribute =
	(
		if classof arg_Attribute == OmsXML_Attribute then
		(
			append array_Attribute arg_Attribute;
		)
	),
	
	fn SetAttribute arg_AttrName arg_AttrValue = 
	(
		kAttribute = OmsXML_Attribute();
		kAttribute.SetName arg_AttrName;
		kAttribute.SetValue arg_AttrValue;
		InsertAttribute kAttribute;
	)
)