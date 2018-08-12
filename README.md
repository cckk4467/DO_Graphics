# DO_Graphics
base on SDL2 的封装一点点的绘图库

**里面有我将要制作的缓动类的草稿函数。。。**

##更新
####2018.8.12
mmp，之前那个版本简直不能用！所有的alpha通道都是废的，函数注释乱的不忍直视。认真的写了些简短的函数说明，，，然后，调了一下午Alpha通道的问题。开始以为是IMAGE的类型不对，搞了半天。后面发现alpha通道失效，于是去找pixel format的问题。嗯，果然是默认的SDL_PIXELFORMAT_BGR888没有A！然后找半天如何修改这个format。。百度一万年无果，果断lartern+Google搜到了stackoverflow的一个问题，用SDL_AllocFormat！散步回来终于把连带问题全部解决。。。诶，我一开始是要干什么的来着？点模糊？下次再说吧，debug调哭了QAQ233