#pragma once


/*在数据提供进程创建了剪贴板数据后，一直到有其他进程获取剪贴板数据前，
这些数据都要占据内存空间。如在剪贴板放置的数据量过大，就会浪费内存空间，
降低对资源的利用率。
为避免这种浪费，可以采取延迟提交（Delayed rendering）技术，
即由数据提供进程先创建一个指定数据格式的空（NULL）剪贴板数据块，
直到有其他进程需要数据或自身进程要终止运行时才真正提交数据。

延迟提交的实现并不复杂，只需剪贴板拥有者进程在调用SetClipboardData（）
将数据句柄参数设置为NULL即可。
延迟提交的拥有者进程需要做的主要工作是对WM_RENDERFORMAT、
WM_DESTORYCLIPBOARD和WM_RENDERALLFORMATS等剪贴板延迟提交消息的处理。

当另一个进程调用GetClipboardData（）函数时，
系统将会向延迟提交数据的剪贴板拥有者进程发送WM_RENDERFORMAT消息。
剪贴板拥有者进程在此消息的响应函数中应使用相应的格式和实际的数据句柄来
调用SetClipboardData（）函数，但不必再调用OpenClipboard（）和EmptyClipboard（）
去打开和清空剪贴板了。在设置完数据有也无须调用CloseClipboard（）关闭剪贴板。


如果其他进程打开了剪贴板并且调用EmptyClipboard（）函数去清空剪贴板的内容，
接管剪贴板的拥有权时，
系统将向延迟提交的剪贴板拥有者进程发送WM_DESTROYCLIPBOARD消息，
以通知该进程对剪贴板拥有权的丧失。
而失去剪贴板拥有权的进程在收到该消息后则不会再向剪贴板提交数据。
另外，在延迟提交进程在提交完所有要提交的数据后也会收到此消息。
如果延迟提交剪贴板拥有者进程将要终止，系统将会为其发送一条WM_RENDERALLFORMATS消息，
通知其打开并清除剪贴板内容。在调用SetClipboardData（）设置各数据句柄后关闭剪贴板。*/


/*邮槽（Mailslot）也称为邮件槽，其是 Windows 提供的一种用来实现进程间通信的手段，

其提供的是基于不可靠的，并且是单向数据传输的服务。

邮件槽只支持单向数据传输，也就是服务器只能接收数据，而客户端只能发送数据，

何为服务端？何为客户端？

服务端就是创建邮槽的那一端，而客户端就是已存在的邮件槽的那一端。

还有需要提及的一点是，客户端在使用邮槽发送数据的时候只有当数据的长度 < 425 字节时，

才可以被广播给多个服务器，如果消息的长度 > 425 字节的话，那么在这种情形下，

邮槽是不支持广播通信的。*/

/*第一：匿名管道只能实现本地进程之间的通信，不能实现跨网络之间的进程间的通信。

第二：匿名管道只能实现父进程和子进程之间的通信，而不能实现任意两个本地进程之间的通信。

第三：所需要的系统的开销也就比命名管道小很多，这也许是匿名管道存在的价值吧。*/