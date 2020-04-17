MindVisionCamera => mvcam
这是工业相机运行节点，负责拍摄图像并传输

1. 打开文件夹“运行库大全”，根据平台选择合适的共享库放入lib文件夹中(这一步可以通过运行install.sh脚本完成，不过这个脚本有点bug，不能正确识别64bit系统，使用的时候要改动一下，后续修复问题后再更新这个脚本)
2. 运行节点：rosrun mvcam mvcam
3. 使用窗口界面查看图像：rosrun image_view image_view image:=/mvcam/image
4. 如需更多功能，请参阅头文件 CameraApi.h ，里面有大量的API可供使用
5. 如果已经插上相机，而运行时提示"没有连接设备"，其原因是权限问题，运行文件夹“运行库大全”中的instal.sh，以使得相机可以在非管理员权限下运行。
