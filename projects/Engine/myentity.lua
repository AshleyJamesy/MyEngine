local ENT 		= Entity:NewClass("MyEntity");

ENT.Name 		= "MyEntity";
ENT.Author		= "Ashley Ennerst";
ENT.Description = "Just a simple Entity";

ENT.MaxHealth 	= 100;
ENT.Health		= 100;

ENT.x = 0;
ENT.y = 0;
ENT.z = 0;
ENT.w = 1;
ENT.h = 1;
ENT.l = 1;
ENT.r = 1;
ENT.g = 0;
ENT.b = 0;
ENT.t = 0;

function ENT:Awake()
	
end

function ENT:Start()
	
end

function ENT:Update()
	self.t = self.t + 0.01;
	self.w = math.sin(self.t) * 2;
	self.h = math.sin(self.t) * 2;
end

function ENT:Render()
	Render.DrawQuadOutline(self.x, self.y, self.z, self.w, self.h, self.l, self.r, self.g, self.b);
end