# 质子轰击重水计算F18产额

1. 按照B1的思路完成了F18产额的输出
2. 建立多线程模式下ROOT文件的输出 
3. 使用GPS来生成质子


## 软件要求
要求G4支持多线程，项目版本为10.6.2

## 使用方法

1. 修改run.mac，修改GPS参数实现对能量和束流的调整，可以在run中多次beamOn
2. 使用ROOT文件保存数据，tree中含有Beam,Energy,Counts,一个root文件Beam,Energy的个数与线程数对应，应该每个数都相同，代表束流强度和能量；Counts应当累加起来才能得到F18产额
3. 支持多线程，在mac文件中自行设置合适的核数

## 后续计算
1. 产额随能量变化
2. 产额随强度变化
3. 能量-强度关联（Dalitz）

## 现存问题
物理模型不清楚，产额数量少 <---修改模型材料后解决


### 使用方法（详细版）
编译完项目之后，修改run2.mac
```
# 质子和位置
/gps/particle proton
/gps/position 0 0 0 cm

# 模拟束流
/gps/pos/type Beam
/gps/pos/shape Circle
/gps/pos/radius 0.1 mm # 束流起点范围,模拟加速器的出射口
/gps/direction 1 0 0

#角度偏移，不用
#/gps/ang/type beam2d
#/gps/ang/sigma_x 2 mrad
#/gps/ang/sigma_y 2 mrad

# 能量分布
/gps/ene/type Gauss
/gps/ene/mono 15 MeV
/gps/ene/sigma 1 MeV

#/gps/energy 6 MeV #如果是单能请注释前面的能量分布，启用它

# 束流强度
/gps/number 1000000

# 事件数量
/run/beamOn 1000
```

1. 修改能量  
   能量有单能和分布能两种，按需选择。修改能量分布代码

2. 修改束流强度  
   换算束流强度和粒子数量，设置束流强度和事件数量，一次模拟的粒子数是两者的乘积。比如上面运行一次后产生的质子数量为1000000*1000个

3. 不同能量和强度运行  
   可一次性运行多个能量和强度值，只需要在run2.mac中重复能量设置即可，如下：
   ```
   #  ********和上面一样
   # 第0次
    #能量分布
   /gps/ene/type Gauss
   /gps/ene/mono 15 MeV
   /gps/ene/sigma 1 MeV
   #/gps/energy 6 MeV #如果是单能请注释前面的能量分布，启用它
   # 束流强度
   /gps/number 1000000
   # 事件数量
   /run/beamOn 1000
   
   # 第一次：能量为电能6，粒子数量为1000000*1000
   /gps/energy 6 MeV #如果是单能请注释前面的能量分布，启用它
   /gps/number 1000000
   /run/beamOn 1000

    # 第二次：能量为电能7，粒子数量为2000000*1000
   /gps/energy 7 MeV #如果是单能请注释前面的能量分布，启用它
   /gps/number 2000000
   /run/beamOn 1000
   ```
   ./main run2.mac运行后得到的数据为rt/output_target{i}.root，里面各自都有一个tree，记录了运行过程中的能量、束流和F18产额。后续就是将这些数字提取出来总结到一个图像上。 <--- ING
