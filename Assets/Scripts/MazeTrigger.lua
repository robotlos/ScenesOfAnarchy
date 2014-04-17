-- new script file

function OnObjectLeave(self, object)
  math.randomseed( os.time())
  x = math.random(-400,400)
  y = math.random(-400,400)
	object:setPosition(hkvVec3(x,y,0))
end
