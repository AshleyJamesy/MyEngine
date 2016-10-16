local MyClass = {}
	MyClass.Events = {}

Hooks = MyClass
	
function MyClass:NewEvent(event_name)
	if(MyClass.Events[event_name] ~= nil) then 
		return false
	end
	
	MyClass.Events[event_name] = {}
	
	return true
end

function MyClass:Add(event_name, hook, _function)
	if(MyClass.Events[event_name] == nil) then 
		MyClass:NewEvent(event_name);
	end
	
	MyClass.Events[event_name][hook] = _function;
	
	return MyClass.Events[event_name][hook];
end

function MyClass:Call(event_name, ...)
	if(MyClass.Events[event_name] == nil) then 
		return nil
	end
	
	for hook, _function in pairs(MyClass.Events[event_name]) do
		local _return = nil
		
		if(type(hook) == "table") then
			_return = _function(hook, ...)
		else
			_return = _function(...)
		end
		
		if(_return ~= nil) then 
			return _return
		end
	end
end







