# open a named server, or type `python -m Pyro4.naming -n 0.0.0.0`
# `python -m Pyro4.nsc list` to list the present objects
import Pyro4.naming

if __name__ == '__main__':
    Pyro4.naming.startNSloop(host='0.0.0.0')