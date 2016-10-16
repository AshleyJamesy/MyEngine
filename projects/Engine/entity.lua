Entity			 = {}
Entity.Prototype = {}
Entity.Metatable = { __index = Entity.Prototype }
Entity.Entities  = {}

Entity.Prototype.Name 			= "No Name";
Entity.Prototype.Author			= "No Author";
Entity.Prototype.Description	= "No Description";

Entity.Prototype.MaxHealth		= 0;
Entity.Prototype.Health			= 0;

function Entity:NewClass(_name)
	local _object = {};	
		_object.__index = _object;
	
	setmetatable(_object, Entity.Metatable);
	
	Entity.Entities[_name] 	= _object;
	
	return _object;
end

function Entity:Create(_name)
	local _object = {};	
		_object.__index 	= _object;
		_object.__newindex 	= _object;
	
	if(Entity.Entities[_name] ~= nil) then
		setmetatable(_object, Entity.Entities[_name]);
	end
	
	Hooks:Add("Awake", _object, _object.Awake);
	Hooks:Add("Start", _object, _object.Start);
	Hooks:Add("Update", _object, _object.Update);
	Hooks:Add("Render", _object, _object.Render);
	
	return _object;
end

function Entity.Prototype:Awake()
	
end

function Entity.Prototype:Start()
	
end

function Entity.Prototype:Update()
	
end

function Entity.Prototype:Render()
	
end

function Entity.Prototype:Destroy()
	
end

function Entity.Prototype:OnDeath()
	print(self.Name, "Death");
end

function Entity.Prototype:OnHeal(_amount)
	print(self.Name, "Healed", _amount);
end	

function Entity.Prototype:Heal(_amount)	
	self.Health = self.Health + _amount;
	
	self:OnHeal(_amount);
	
	if(self.Health > self.MaxHealth) then
		self.Health = self.MaxHealth;
	end
end

function Entity.Prototype:OnDamage(_amount)
	print(self.Name, "Damaged", _amount);
end

function Entity.Prototype:Damage(_amount)	
	self.Health = self.Health - _amount;
	
	self:OnDamage(_amount);
	
	if(self.Health <= 0) then
		self.Health = 0;
		
		self:OnDeath();
	end
end

function Entity.Prototype:SetHealth(_amount)
	self.Health = _amount;
	
	if(_amount < self.Health) then
		self:OnDamage(self.Health - _amount);
	end
	
	if(_amount > self.Health) then
		self:OnHeal(_amount - self.Health);
	end
	
	if(self.Health < 0) then
		self:OnDeath();
	end
	
	if(self.Health > self.MaxHealth) then
		self.Health = self.MaxHealth;
	end
end

function Entity.Prototype:GetHealth()
	return self.Health;
end

