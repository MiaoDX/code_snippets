# The lossless video writer with OpenCV

``` vi
OpenCV doc on VideoWriter():

Most codecs are lossy. If you want lossless video file you need to use a lossless codecs (eg. FFMPEG FFV1, Huffman HFYU, Lagarith LAGS, etc...)

And 
http://www.fourcc.org/ffv1/
A lossless video codec based on arithmetic coding developed in the open source ffmpeg project.
```

To summary,

Use lossless codec for encoding (ffmpeg+ffv1+mkv), we are done.


Note,
This codes may depends on the version of OpenCV, tested okay with `3.4.6` and **have seen something wrong with prior versions**.
