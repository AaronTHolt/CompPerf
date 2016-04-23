simple ClientClosed
{
	parameters:
		volatile double ThinkTime @unit(s) = default(250ms);
		int NumJobs = default(2);
		string OutputFile = default("ClientClosedOutput.txt");
		
	gates:
		inout proxy;
}

simple Proxy
{
	parameters:
		volatile double ServiceTime @unit(s) = default(10ms);
		double hitRate = default(0.7);
		
		@display("i=block/routing");
	gates:
		inout client;
		inout router;
}

simple Router
{
	parameters:
		volatile double ServiceTime @unit(s) = default(5ms);
		
		@display("i=block/routing");
	gates:
		inout proxy;
		inout origin[];
}

simple Origin
{
	parameters:
		volatile double ServiceTime @unit(s) = default(150ms);
		
		@display("i=block/routing");
	gates:
		inout router;
}

network WebClosed
{
	types:
	
		channel WAN extends ned.DelayChannel {
			delay = 36 ms;
		}

		channel LAN extends ned.DelayChannel {
			delay = 0 ms;
		}

	submodules:
		client : ClientClosed;
		proxy : Proxy;
		router : Router;
		originA : Origin {
			ServiceTime=150ms;
		}
		originB : Origin {
			ServiceTime=100ms;
		}

	connections:
		client.proxy <--> LAN <--> proxy.client;
		proxy.router <--> WAN <--> router.proxy;
		router.origin++ <--> LAN <--> originA.router;
		router.origin++ <--> LAN <--> originB.router;
}
