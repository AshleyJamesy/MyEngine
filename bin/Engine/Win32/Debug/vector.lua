Vector			 = {}
Vector.Prototype = {}
Vector.Metatable = { __index = Vector.Prototype }

Vector.Prototype.x = 0;
Vector.Prototype.y = 0;
Vector.Prototype.z = 0;

function Vector:New(_x, _y, _z)
	local _object = {};	
		_object.__index = _object;
	
	setmetatable(_object, Vector.Metatable);
	
	return _object;
end







