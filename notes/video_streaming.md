# Video through web

**NOTE** It seems that the MJPG is just suitable for 

[A fully functional RTSP/RTP streaming server hello world example in C++ for experimentation with JPEG payloads.](https://www.medialan.de/usecase0001.html)

[Remote video streaming with face detection](https://medium.com/@QuantuMobile/remote-video-streaming-with-face-detection-d52ce2d71419)

[HTTP server to stream your OpenCV processing in C++](https://github.com/JPery/MJPEGWriter)

[wpilibsuite/cscore, Camera access and streaming library](https://github.com/wpilibsuite/cscore)

[ethanrublee/streamer, A simple boost asio based mjpeg streaming server.](https://github.com/ethanrublee/streamer)  NICE API

[Main libjpeg-turbo repository https://libjpeg-turbo.org](https://github.com/libjpeg-turbo/libjpeg-turbo) Accelerate with SIMD, not for streaming, [but seems to accelerate for general purpose](http://unanancyowen.com/en/opencv-with-libjpeg-turbo/)

## With python

[Flask Video Streaming Revisited](https://blog.miguelgrinberg.com/post/flask-video-streaming-revisited)

Very elegant!

## Client

[利用python-opencv调用mjpg-stream视频流](http://blog.csdn.net/xiao__run/article/details/76342634)

[Creating a function using yield instead of return to generate frames from a http stream continuously](https://stackoverflow.com/questions/44157160/creating-a-function-using-yield-instead-of-return-to-generate-frames-from-a-http)

## Some comparison

[A COMPARISON OF DIFFERENT DATA STREAMING OPTIONS](http://andrewjesaitis.com/2016/08/25/streaming-comparison/)

However, it use python (which can be some disturbances w.r.t the implements) and the HTTP/1.1 already pretty interesting and the gRPC gives another view.

[GRPC: TRANSPORTING MASSIVE DATA WITH GOOGLE’S SERIALIZATION](https://alexandreesl.com/2017/05/02/grpc-transporting-massive-data-with-googles-serialization/)

[channelcat/sanic, Streaming](https://github.com/channelcat/sanic/blob/master/docs/sanic/streaming.md)

Seems an elegant implement with streaming support, only, not support windows, and the `async` is not familiar to me. -.-

And then, [google/flatbuffers](https://github.com/google/flatbuffers), another product by google, seem impressive.


[You Stream, I Stream, We All Stream For Protocol Buffers](http://www.sureshjoshi.com/development/streaming-protocol-buffers/)

> Instead, I’ll just write my data to a pb file from Android, pull it back in on the C++ side and run my signal processing algorithms (or alternatively, I send an in-memory Protobuffer across the JNI boundary). This way, I can develop my C++ and Android code on their own, and have an interface layer which is robust to changes.