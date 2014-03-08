-- new script file

function OnObjectEnter(self, object)
	object:Remove() 
  Debug:PrintLine("Removed ball");
end
