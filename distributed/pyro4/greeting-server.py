# saved as greeting-server.py
import Pyro4
import Pyro4.naming


@Pyro4.expose
class GreetingMaker(object):
    def get_fortune(self, name):
        return "Hello, {0}. Here is your fortune message:\n" \
               "Tomorrow's lucky number is 12345678.".format(name)

def official(ip_in_lan='100.100.100.1'):
    daemon = Pyro4.Daemon(host=ip_in_lan)                # make a Pyro daemon
    ns = Pyro4.locateNS()                  # find the name server
    uri = daemon.register(GreetingMaker)   # register the greeting maker as a Pyro object
    ns.register("example.greeting", uri)   # register the object with a name in the name server

    print("Ready.")
    daemon.requestLoop()                   # start the event loop of the server to wait for calls

def another(ip_in_lan='100.100.100.1'):
    Pyro4.naming.locateNS()
    Pyro4.Daemon.serveSimple(
        {
          GreetingMaker: "example.greeting"
        },
        ns=True,
        port=1234,
        host=ip_in_lan
    )


if __name__=="__main__":
    ip_in_lan='192.168.0.151'
    # official(ip_in_lan)
    another(ip_in_lan)