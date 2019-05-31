#!/usr/bin/env python
# -*- coding:utf-8 -*-
# Author: DongxuMiao(dongxumiao@deepmotion.ai)

# For transform matrix inverse, T^inv * T = I
# np.linalg.inv will give the very same result compared with manipulating R, t separately
# but will take a little longer time, but who cares? -.-
# and scipy.linalg may have speedup with bigger matrix? at least not true for 4x4 here
# https://math.stackexchange.com/questions/1234948/inverse-of-a-rigid-transformation

import time
import numpy as np
import scipy.linalg
from tqdm import tqdm
from transforms3d import euler


def inv(transform: np.ndarray):
    assert transform.shape == (4, 4)
    "Invert rigid body transformation matrix"
    R = transform[0:3, 0:3]
    t = transform[0:3, 3]
    t_inv = -1 * R.T.dot(t)
    transform_inv = np.eye(4)
    transform_inv[0:3, 0:3] = R.T
    transform_inv[0:3, 3] = t_inv
    return transform_inv


def rand_ang():
    return np.random.randint(0, 360) / 360 * np.pi


def rand_T():
    R = euler.euler2mat(ai=rand_ang(),
                        aj=rand_ang(),
                        ak=rand_ang(),
                        axes='sxyz')
    t = np.random.rand(3) * 100
    T = np.eye(4)
    T[:3, :3] = R
    T[:3, 3] = t
    return T


def run(num=100000):
    T = rand_T()
    tran = T.copy()

    t0 = time.perf_counter()
    for _ in tqdm(range(num)):
        inv_np = np.linalg.inv(T)
    t1 = time.perf_counter()
    _t1 = t1 - t0

    t0 = time.perf_counter()
    for _ in tqdm(range(num)):
        inv_sp = scipy.linalg.inv(T)
    t1 = time.perf_counter()
    _t2 = t1 - t0

    t0 = time.perf_counter()
    for _ in tqdm(range(num)):
        inv_Rt = inv(tran)
    t1 = time.perf_counter()
    _t3 = t1 - t0

    print(_t1, _t2, _t3)

    assert np.allclose(inv_np, inv_sp)
    assert np.allclose(inv_np, inv_Rt)


if __name__ == '__main__':

    run(num=1000000)  # 8.586018962989328 51.440500037002494 6.288953461989877
