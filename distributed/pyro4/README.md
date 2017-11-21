[irmen/Pyro4](https://github.com/irmen/Pyro4): Pyro 4.x - Python remote objects.

The minimal demo of access remote objects in python with Pyro4 in a LAN, slight changed from the [http://pyro4.readthedocs.io/en/stable/intro.html#simple-example](http://pyro4.readthedocs.io/en/stable/intro.html#simple-example) and [a blog in Chinese](http://blog.csdn.net/xiaolewennofollow/article/details/52155457)

There are two PCs, one server with IP `192.168.0.151`, one client with IP `192.168.0.159`.

* Make sure they can ping each other.
* Start the `nameserver.py` by setting the `host` to be `0.0.0.0`(do not change when IP changes)
* Start the `greeting-server.py` in server
* Start the `greeting-client.py` in server, and then in the client.


In fact, it would be better if we do not have to care about the ip of server in the sever side at all, with `0.0.0.0` means all other computers can access this server. For example, in the wireless LAN in our lab, the IP of server is `192.168.0.151`, it can be accessed with this IP in the same LAN. I also hope that in another LAN, such as the virtual machines in the virtualbox can call the server with a different ip of maybe `100.100.100.1` in their LAN without a single line of change in the server code. But this is not the case at present. So we can only use it in a specific LAN by specify the ip of server in that LAN. (WELL, like a doggerel~)

Maybe more in-depth reading of the examples and docs can help, but by far, this is enough.