# 设置 $tp 寄存器的值,这个寄存器在 RISC-V 中用作 CPU ID
set $tp = $tp
# 在 exec 函数处设置断点
b exec

c

# 打印当前进程名称
p cpus[$tp]->proc->name
# $1 = "initcode\000\000\000\000\000\000\000"

step

p cpus[$tp]->proc->name
# $2 = "initcode\000\000\000\000\000\000\000"

step

p cpus[$tp]->proc->name
# $3 = "initcode\000\000\000\000\000\000\000"

b main

c

# 再次执行到exec断点
p cpus[$tp]->proc->name
# $4 = "init", '\000' <repeats 11 times>

s

s

c

p cpus[$tp]->proc->name
# $5 = "sh", '\000' <repeats 13 times>