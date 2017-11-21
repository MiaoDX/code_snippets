# saved as greeting-client.py
import Pyro4

name = input("What is your name? ").strip()

ip_in_lan='100.100.100.1'

call_addr = "PYRONAME:example.greeting@" + ip_in_lan

greeting_maker = Pyro4.Proxy(call_addr)    # use name server object lookup uri shortcut
# greeting_maker = Pyro4.Proxy("PYRONAME:example.greeting")
print(greeting_maker.get_fortune(name))