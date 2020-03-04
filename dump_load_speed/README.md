# The speed test of dump/load image file with OpenCV

This test aim at choosing one better image format when using QNX IECU@SAIC for data capturing.

On Laptop(X1 Carbon)

```
Test dump
Using Raw: 570.444
Using PNG ENCODE: 6089.1
Using PNG: 6525.08
Using JPG ENCODE: 1169.76
Using JPG: 1274.53
Using BMP: 418.337
Test load
Using Raw: 73.6282
Using PNG: 2993.55
Using JPG: 985.9
Using BMP: 139.892
```

However, on QNX IECU:

```
Test dump
Using Raw: 17152.3
Using PNG ENCODE: 18298.3
Using PNG: 24706
Using JPG ENCODE: 10310.6
Using JPG: 11995.5
Using BMP: 17475.3
Test load
Using Raw: 9931.6
Using PNG: 10429.6
Using JPG: 7316.71
Using BMP: 8145.67
```

That is, **writing to disk operation on IECU is already rather long**, which is a pity.

And, the images sizes are:

```
3.6M    /tmp/im.bin
1.7M    /tmp/im.bin.zip
3.6M    /tmp/im.bmp
1.7M    /tmp/im.bmp.zip
328K    /tmp/im.jpg
324K    /tmp/im.jpg.zip
1.6M    /tmp/im.png
1.5M    /tmp/im.png.zip
```

That is, bmp can be twice as large as png, this can be a burden when transfer outside from IECU.

And the zip version is a lot better, so, can be useful when transfer via baidunetdisc.

## Conclusion

One possible pipeline:

1. `bmp` when saving on IECU
2. `scp` to local pc
3. `zip` the images
4. `baidunetdisc` back

