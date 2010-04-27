

handle_oxm = io.open("../../export/Plane01.oxm","rb");
if handle_oxm == nil then
messagebox("file open failed","file");
end

string_line = handle_oxm:read("*all");
messagebox(string_line,"line read check2"); 
simbol, string_line = string.match(string_line,"<(.*)>(.*)</%1>");
messagebox(simbol,"line read check2"); 
messagebox(string_line,"line read check2"); 


simbol, string_line = string.match(string_line,"<(.*)>(.*)</%1>");
messagebox(simbol,"line read check2"); 
messagebox(string_line,"line read check2"); 


simbol, string_line = string.match(string_line,"<(.*)>(.*)</%1>");
messagebox(simbol,"line read check2"); 
messagebox(string_line,"line read check2"); 


simbol, string_line = string.match(string_line,"<(.*)>(.*)</%1>");
messagebox(simbol,"line read check2"); 
messagebox(string_line,"line read check2"); 


simbol, string_line = string.match(string_line,"<(.*)>(.*)</%1>");
messagebox(simbol,"line read check2"); 
messagebox(string_line,"line read check2"); 
