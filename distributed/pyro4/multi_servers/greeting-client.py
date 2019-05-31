"""
It can call methods from multi servers, as expected.
"""
import Pyro4


def call_ip(server_ip_in_lan='100.100.100.1'):
    print("Going to call {}".format(server_ip_in_lan))

    call_addr = "PYRONAME:example.greeting@" + server_ip_in_lan

    greeting_maker = Pyro4.Proxy(
        call_addr)  # use name server object lookup uri shortcut
    # greeting_maker = Pyro4.Proxy("PYRONAME:example.greeting")
    print(greeting_maker.get_fortune(name))


if __name__ == '__main__':

    name = input("What is your name? ").strip()

    call_ip('192.168.0.151')
    call_ip('192.168.0.159')
