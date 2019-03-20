# There can be `gotchas` here and there

* Jupyter notebook behaves strangely
    - At console, we can correctly import just installed packages
    - At jupyter, it just raise `ImportError: No module named XXX`
    - And the `sys.path` will give different values
    - Solution: [https://github.com/jupyter/notebook/issues/1524](https://github.com/jupyter/notebook/issues/1524)
    - `python -m ipykernel install --user`
