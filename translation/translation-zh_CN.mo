��    q      �  �   ,      �	  	   �	     �	  E   �	     �	  "   �	  
   
  	   !
     +
  1  7
     i  %   �  &   �     �  /   �  '     -   ;     i          �  %   �  M   �  "     q   3     �     �     �  &   �  $        (     7     K     [     m     �     �  '   �  &   �     �            $   *     O  .   n  �   �  *   N  ^   y  �   �  8   l     �  G   �     �      .     �   B  	   �  	   �     �     �     �     �               +     @     M     \     b  
   {     �     �     �     �     �     �  	   �     �  
   �     �     �  
          	   ,     6     H  
   N  
   Y  
   d     o     {  	   �     �      �     �     �     �     �  	   �     �               #     8     J  	   S     ]     i     n     }     �  
   �     �     �  �  �     l     y  <   �  
   �     �     �     �     �  �        �     	     %     A     R     r     �     �     �     �     �  7   �      (  p   I     �     �     �  $   �  $        >     K     ^     n     ~     �     �     �     �     �                    3     O  �   e  $     I   3  �   }  ?   
     J  I   Q     �    �  7   �   �   �   
   �!     �!  
   �!  
   �!  
   �!  
   �!     �!     �!     "     ""     6"  
   J"     U"     n"     u"     �"     �"     �"     �"     �"  	   �"  	   �"     �"     �"     �"     �"     �"  	   #     #     #  	   $#  	   .#  	   8#  	   B#  	   L#  	   V#     `#     s#     �#     �#     �#     �#     �#     �#     �#     �#     �#     �#     $     $     $     $     &$     >$     K$     R$     Y$     `$     J      (   i              o      *              _   m      >   2   P             K   .   -   ]           ;   U           q           ^       d           k      p          l   Y      
           f   @          :      %                  #   <   /   `       8   j   I       B   b      H   	   0          N      $       W       c       C   L   A   9          ?      e       D   +      1   G   )           Z   S   ,          =   R      5       &       4       V   M       6   O      F   a      "       E       7   n   h   !   Q      T         '   [      X   g   3          \     (custom) (new Entries) AND: your modifications are still unsaved, update will save them too! A_ppearance Add a script to your configuration Add script BURG Mode BURG found! Before you can edit your grub configuration we have to
mount the required partitions.

This assistant will help you doing this.


Please ensure the target system is based on the same cpu architecture
as the actually running one.
If not, you will get an error message when trying to load the configuration. Configuration has been saved Couldn't mount the selected partition Couldn't umount the selected partition Default title:  Do you want to configure BURG instead of grub2? Do you want to save your modifications? Do you want to select another root partition? Edit grub preferences Entry Entry %1 (by position) Error while installing the bootloader Grub Customizer is a graphical interface to configure the grub2/burg settings Grub Customizer: Partition chooser Install the bootloader to MBR and put some
files to the bootloaders data directory
(if they don't already exist). Install to MBR Mount failed! Mount selected Filesystem Move down the selected entry or script Move up the selected entry or script Name the Entry No Bootloader found No script found Partition Chooser Please type a device string! Preview: Proxy binary not found! Remove a script from your configuration Save configuration and generate a new  Script to insert: Seconds Select _partition … Select and mount your root partition Select required submountpoints The bootloader has been installed successfully The generated configuration didn't equal to the saved configuration on startup. So what you see now may not be what you see when you restart your pc. To fix this, click update! The saved configuration is not up to date! These are the mountpoints of your fstab file.
Please select every grub/boot related partition. This option doesn't work when the "os-prober" script finds other operating systems. Disable "%1" if you don't need to boot other operating systems. This seems not to be a root file system (no fstab found) Timeout To get the colors above working,
you have to select a background image! Unmount mounted Filesystem You selected the option for choosing another partition.
Please note: The os-prober may not find your actually running system.
So run Grub Customizer on the target system
again and save the configuration (or run update-grub/update-burg)
to get the entry back! You started Grub Customizer using the live CD. You will see all entries (uncustomized) when you run grub. This error accurs (in most cases), when you didn't install grub gustomizer currectly. _Advanced _Device:  _Edit _File _General _Help _Install to MBR … _Quit without saving _Quit without update _Save & Quit _Update & Quit _View _use another partition:  background background image black blue brown custom resolution:  cyan dark-gray default entry font color generate recovery entries green highlight: installing the bootloader… is active kernel parameters label light-blue light-cyan light-gray light-green light-magenta light-red loading configuration… look for other operating systems magenta menu colors name normal: partition pre_defined:  previously _booted entry red reload configuration remove background settings show menu transparent type umount failed! updating configuration value visibility white yellow Project-Id-Version: grub-customizer
Report-Msgid-Bugs-To: FULL NAME <EMAIL@ADDRESS>
POT-Creation-Date: 2011-12-23 17:05+0100
PO-Revision-Date: 2011-12-28 18:00+0000
Last-Translator: Careone <zzbusagain@yahoo.com.cn>
Language-Team: Chinese (Simplified) <zh_CN@li.org>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
X-Launchpad-Export-Date: 2012-01-31 23:00+0000
X-Generator: Launchpad (build 14734)
  (自定义) (新条目) 还有：修改还没有保存，更新时会进行保存！ 外观(_P) 添加脚本到配置 添加脚本 BURG 模式 找到 BURG！ 在开始编辑 Grub 配置前，需要
先挂载要必要的分区。

本助手将帮助你来操作这些。


请确保目标系统的 CPU 架构与实际硬件相符。
如果不相符，在加载配置时，会出现错误信息。 配置已保存 无法挂载选中的分区 无法卸载选中的分区 默认标题：  要配置BURG 来代替 Grub2 ? 保存修改吗？ 选择另一个根分区？ 编辑 grub 参数 项目 项目 %1 (按位置) 安装启动器时出现错误 Grub Customizer 是配置 grub2/burg 的图形化界面 Grub Customizer: 分区选择器 安装启动引导器到MBR，并放置相应的文件
到启动器数据目录（如果这个目录存在）。 安装到 MBR 挂载失败！ 挂载选中的文件系统 向下移动选中的项目或脚本 向上移动选中的项目或脚本 项目名称 未找到启动器 未找到脚本 分区选择器 请输入设备字符串！ 预览: 二进制代理未找到！ 从配置里删除脚本 保存并生成新的配置  插入脚本: 秒 选择分区(_P)... 选择并挂载根分区 选择必要的子挂载点 启动器安装成功 生成的配置不等于启动时已保存的配置。重启动电脑后看到的，不一定是现在你所看到的。要修复这个问题，请点击“更新”！ 已保存的配置不是最新的！ 这是 fstab 文件的挂载点。
请选择对应的 grub/boot 分区。 如果“os-prober”脚本找到其它的操作系统，本选项无效。如果不需要启动其它的操作系统，请禁用“%1”。 看起来不像是一个根文件系统(找不到 fstab 文件) 延时 如果想要获取上面的颜色，
你需要选择一个背景图像！ 卸载已挂载的文件系统 你选中了“选择其它分区”的选项。
请注意： os-prober 可能找不到实际运行的操作系统。
所以请在目标系统上重新运行 Grub Customizer 并保存配置，
把相应的项目找回来(或者运行 update-grub/update-burg 命令)！ 已使用免安装光盘(Live CD)启动 Grub Customizer 在运行 Grub 时会看到全部项目(未自定义)。如果没有正确安装 Grub customizer ， (在大多数情况下)会出现这个错误。 高级(_A) 设备(_D)：  编辑(_E) 文件(_F) 常规(_G) 帮助(_H) 安装到MBR...(_I) 不保存直接退出(_S) 不更新直接退出(_Q) 保存并退出(_S) 更新并退出(_U) 查看(_V) 使用另一分区(_U):  背景 背景图像 黑色 蓝色 褐色 自定义分辩率:  青色 深灰色 默认项 字体颜色 生成恢复项 绿色 高亮: 安装启动器... 活动的 内核参数 卷标 浅蓝色 浅青色 浅灰色 浅绿色 浅青色 浅红色 载入配置中… 查找其它操作系统 品红 菜单颜色 名称 正常: 分区 预定义(_D):  上一个启动项(_B) 红色 重新加载配置 删除背景 设置 显示菜单 透明 类型 卸载(umount)失败！ 更新配置 数值 可见 白色 黄色 