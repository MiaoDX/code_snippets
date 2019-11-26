#!/usr/bin/env python
# -*- coding:utf-8 -*-
#
# Colorize one mask, by different ways:
# * direct numpy indexing
# * np.take
# * numba take (flatten/ravel first and then reshape)
# * cv2.applyColorMap/cv2.LUT
# 100 runs | direct: 1064.02ms
# 100 runs | np.take: 451.20ms
# 100 runs | numba: 350.05ms
# 100 runs | cv2.lut: 165.59ms

import cv2
import time
from numba import jit
import numpy as np


class Mask2Color(object):
    def __init__(self):
        self._color_map = [(70, 70, 70), (128, 255, 0), (255, 0, 0),
                           (0, 255, 0), (119, 11, 32)]
        self._color_map_table = np.array(self._color_map).astype(
            np.uint8)[:, [2, 1, 0]]

        self.cv2_color_lut = np.zeros((256, 1, 3), dtype=np.uint8)
        num = len(self._color_map_table)
        self.cv2_color_lut[:num, 0, :] = self._color_map_table

    @staticmethod
    @jit(nopython=True)
    def _nb_get(arr, idx):
        return arr[idx]

    def colorize_nb(self, lbl):
        h, w = lbl.shape
        color_lbl = self._nb_get(self._color_map_table,
                                 lbl.ravel()).reshape(h, w, 3)
        return color_lbl

    def colorize_cv2_lut(self, lbl):
        # https://stackoverflow.com/questions/58269913/vectorize-pixelwise-assignment-for-color-mapping-of-a-segmentation-mask
        color_lbl = cv2.applyColorMap(lbl.astype(np.uint8), self.cv2_color_lut)
        return color_lbl

    def colorize_direct(self, lbl):
        color_lbl = self._color_map_table[lbl]
        return color_lbl

    def colorize_np_take(self, lbl):
        color_lbl = self._color_map_table.take(lbl, axis=0)
        return color_lbl


def run_mul(func, mask, num, run_name):
    # run once to make sure numba codes is compiled
    func(mask)

    t0 = time.perf_counter()
    for _ in range(num):
        mask_c = func(mask)
    print(f'{num} runs | {run_name}:{(time.perf_counter()-t0)*1000: .2f}ms')
    return mask_c


if __name__ == '__main__':

    mask_colorizer = Mask2Color()

    mask = np.random.randint(low=0, high=5, size=(720, 1280))
    num = 100

    mask_c_direct = run_mul(mask_colorizer.colorize_direct, mask, num,
                            'direct')
    mask_c_take = run_mul(mask_colorizer.colorize_np_take, mask, num,
                          'np.take')
    mask_c_nb = run_mul(mask_colorizer.colorize_nb, mask, num, 'numba')
    mask_c_cv2 = run_mul(mask_colorizer.colorize_cv2_lut, mask, num, 'cv2.lut')

    assert np.allclose(mask_c_direct, mask_c_take)
    assert np.allclose(mask_c_direct, mask_c_nb)
    assert np.allclose(mask_c_direct, mask_c_cv2)

    # cv2.imshow('Mask Color', mask_c)
    # cv2.waitKey()
