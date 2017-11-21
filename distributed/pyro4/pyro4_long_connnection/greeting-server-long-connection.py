"""
The connection can be a long time, a.k.a, it can handle multi connection from different clients.

Try this by issue two (or more) clients.
"""

import Pyro4
import Pyro4.naming
import time

def show():
    import socket
    myname = socket.getfqdn(socket.gethostname())
    myaddr = socket.gethostbyname(myname)
    return "PC name:{}, ip addr:{}".format(myname, myaddr)


def time2str():
    return time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())


GLOBAL_VAR = 0

@Pyro4.expose
class GreetingMaker(object):

    def get_fortune(self, name):

        print("Receive request at:{}\nGoing to sleep for ten second".format(time2str()))

        global GLOBAL_VAR
        GLOBAL_VAR += 1

        var_clone = GLOBAL_VAR # copy of global variable, so as to the correct value is returned

        time.sleep(10)
        print("Done, ready to return")
        return "Hi, {}, greeting from {}\nYour finish time:{}, magic num:{}".format(name, show(), time2str(), var_clone)


def run(ip_in_lan='100.100.100.1'):
    daemon = Pyro4.Daemon(host=ip_in_lan)                # make a Pyro daemon
    ns = Pyro4.locateNS()                  # find the name server
    uri = daemon.register(GreetingMaker)   # register the greeting maker as a Pyro object
    ns.register("example.greeting", uri)   # register the object with a name in the name server

    print("Ready.")
    daemon.requestLoop()                   # start the event loop of the server to wait for calls

if __name__=="__main__":
    ip_in_lan='192.168.0.151'
    run(ip_in_lan)