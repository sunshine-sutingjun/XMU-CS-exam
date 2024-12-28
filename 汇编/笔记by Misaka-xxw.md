# 汇编语言(实验版v1.0)

[toc]
<style>
h6 {
    background-color: pink;
}
h1 {
    text-align: center;
}
</style>

## 第3章 80x86的指令系统和寻址方式

### 3.1 80x86的寻址方式

...

---

### 3.3 80x86的指令系统

#### 3.3.1 数据传送指令(p47)

##### 1. 通用数据传送指令

###### mov

1. mov mem/reg1,mem/reg2
<span style="color:red">先略。。。</span>

###### push进栈指令

```
push src
```

(sp) ← (sp)-2
((sp)+1,(sp)) ← (src)

**格式**

push reg
push mem
~~push data~~8086不行
push segreg

<details>

```
push ax      ; 推送 AX 寄存器
push bx      ; 推送 BX 寄存器
push cx      ; 推送 CX 寄存器
push dx      ; 推送 DX 寄存器
push sp      ; 推送 SP 寄存器
push bp      ; 推送 BP 寄存器
push si      ; 推送 SI 寄存器
push di      ; 推送 DI 寄存器

push word ptr [address]  ; 推送内存地址中的值

push cs      ; 推送 CS 段寄存器
push ds      ; 推送 DS 段寄存器
push es      ; 推送 ES 段寄存器
push ss      ; 推送 SS 段寄存器
```

</details>

###### pop出栈指令

<span style="color:red">注意要画栈图</span>

```
pop dst
```

(dst) ← ((sp)+1,(sp))
(sp) ← (sp)+2

pop reg
pop mem
~~pop data~~8086不行
pop segreg

##### 2. 累加器专用传送指令

这些指令不影响标志位

###### in

```
in al,port ;字节, (al) ← (port)
in ax,port ;字, (ax) ← (port+1,port)
in al,dx   ;字节, (al) ← ((dx))
in ax,dx   ;字, (ax) ← ((dx)+1,(dx))
```

###### out

```
out port,al ;字节, port ← (al)
out port,ax ;字, (port+1,port) ← (ax)
out dx,al   ;字节, ((dx)) ← (al)
out dx,ax   ;字, ((dx)+1,(dx)) ← (ax)
```

###### xlat换码指令

xlat p55

##### 3. 地址传送指令

###### lea有效地址送寄存器

```
lea reg,sec ;(reg)<-src
```

```lea bx,list```≈```mov bx,offset list```, ```mov```更快

###### lds, les, lfs, lgs, lss指针送寄存器和?s

p56, 实验暂时不用

###### 标志寄存器传送指令

p57, 实验暂时不用

##### 4. 类型转换指令

###### cbw

将al的内容符号扩展到ah，形成ax的字。
若(AL)的最高有效位为0，则(AH)= 00H
若(AL)的最高有效位为1，则(AH)= 0FFH

###### cwd/cwde

将ax的内容符号扩展到dx，形成dx:ax中的双字。
若(AX)的最高有效位为0，则(DX) = 0000H
若(AX)的最高有效位为1，则(DX) = 0FFFFH

---

#### 3.3.2 算术指令

##### 3.3.2.1. 加法指令

###### add加法

###### adc带进位加法

###### inc 加1指令

##### 2. 减法指令

###### sub减法

###### sbb带借位减法

###### dec减1

###### neg求补

按位求反+1

###### cmp比较

前操作数-后操作数，但是不保存结果，只设置条件标志位

##### 3. 乘法指令

目的操作数必须是累加器

###### mul无符号数乘法

```
mul src
```

(ax)<-(al)*(src)    ;字节操作数
(dx,ax)<-(ax)*(src) ;字操作数

###### imul带符号数乘法

同上，但是是带符号数

##### 4. 除法指令

###### div无符号数除法

```div src```

字节操作：
(ax)/(src)=(al)......(ah)
字操作：
(dx,ax)/(src)=(ax)......(dx)
<span style="color:red">注意进制转换的代码</span>

###### idiv带符号数除法

同上

##### 5. 十进制调整指令

有压缩的BCD码调整指令：
DAA 加法的十进制调整指令
DAS 减法的十进制调整指令

非压缩的BCD码调整指令：
AAA 加法的ASCII调整指令
AAS 减法的ASCII调整指令
AAM 乘法的ASCII调整指令
AAD 除法的ASCII调整指令

#### 3.3.3 逻辑指令

##### 1. 逻辑运算指令

###### and 逻辑与指令

###### or 逻辑或指令

###### not 逻辑非指令

###### xor 异或指令

要使操作数的某些位变反，使用xor，那些位设为1

###### test 测试指令

做and运算，但是不保存结果，只置条件码
要测试操作数的某位是都为1，可以先将操作数取反，再用test测试。

##### 2. 移位指令(p73)

e.g. ```shl opr,cnt```
在8086中，```cnt```可以是```cl```或者```1```

###### shl 逻辑左移指令

无符号数乘法

###### sal 算数左移指令

有符号数乘法

###### shr 逻辑右移指令

无符号数除法

###### sal 算数右移指令

有符号数除法

###### rol 循环左移指令

###### ror 循环右移指令

###### rcl 带进位循环左移指令

###### rcr 带进位循环右移指令

#### 3.3.4 串处理指令

<span style="color:red">这里要写一下字符串代码</span>

##### 1. 与rep相配合工作的movs, stos, lods, ins, outs

###### rep重复串操作

重复串操作直到计数器Count Reg的内容为0位为止
操作：

```python
while Count_Reg != 0:
    Count_Reg-=1
    执行后面的串指令
```

###### movs 串传送指令

格式

```
movs dst,src
movsb ;字节
movsw ;字
```

第一种格式要在操作数里标名是字还是字节操作。
```movs  es:byte ptr[di],ds:[si]```

**相当于```strcpy```**
movs可以把由**源变址寄存器**指向的数据段中的一个字（或字节），传到**目的变址寄存器**指向的附加段中的一个字（或字节）去，同时根据**方向标志**以及数据格式（字or字节），对源变址寄存器和目的变址寄存器进行修改。

执行操作：

1. ((DI)) ← ((SI))
2. 字节操作：(SI)←(SI)±1,  (DI)←(DI)±1
字操作：  (SI)←(SI)±2,  (DI)←(DI)±2
方向标志DF=0时用 +，DF=1时用 - 。

执行REP MOVS之前，应先做好：

1. 源串首地址（末地址）→ SI
2. 目的串首地址（末地址）→ DI
3. 串长度 → CX
4. 建立方向标志（CLD使DF=0，STD使DF=1）

<mark>**方向标志**</mark>

+ ```cld```: df=0, 地址自动增量
+ ```std```: df=1, 地址自动减量

###### stos 存入串指令

格式

```
stos dst
stosb ;字节
stosw ;字
```

**相当于```memset```**
将al、ax的内容存入由**目的变址寄存器**指向的附加段的某单元中，并根据……
**初始化某一个缓冲区**时很有用

执行操作：

1. 字节操作：((DI))←(AL),  (DI)←(DI)±1
2. 字操作：((DI))←(AX),  (DI)←(DI)±2

例：把附加段中的5个字节缓冲区置为20H

```
lea  di, mess2
mov  al, 20H
mov  cx, 5
cld
rep  stosb
```

##### lods 从串取指令

格式

```
lods src
lodsb ;字节
lodsw ;字
```

LODS指令一般不与REP联用
源串必须在数据段中，目的串必须在附加段中，
但源串允许使用段跨越前缀来修改。
不影响条件标志位

执行操作：
字节操作：(AL)←((SI)),(SI)←(SI)±1
字操作：(AX)←((SI)),(SI)←(SI)±2

##### ins 串输入

格式

```
ins dst,dx
insb ;字节
insw ;字
```

执行操作：
字节操作：(DI)←((DX)), (DI)←(DI)±1
字操作：(DI+1,DI)←((DX)), (DI)←(DI)±2

##### outs 串输出

格式

```
outs dx,src
outsb ;字节
outsw ;字
```

执行操作：
字节操作：((DX)) ← (SI),  (SI)←(SI)±1
字操作：((DX)) ←(SI+1，SI),  (SI)←(SI)±2

##### 2. repe/repz,repne/repnz,cmps,scas

###### repe/repz 为相等/为零时重复串操作

```python
while Count_Reg!=0 and zf!=0:
    Count_Reg-=1
    执行其后的串指令
```

###### repne/repnz 为不相等/不为零时重复串操作

```python
while Count_Reg!=0 and zf!=1:
    Count_Reg-=1
    执行其后的串指令
```

###### cmps 串比较指令

格式

```
cmps src,dst
cmpsb ;字节
cmpsw ;字
```

**相当于```strcmp```**

执行操作：
(1) ((SI)) - ((DI))
根据比较结果设置条件标志位：相等 ZF=1
(2) 字节操作：(SI)←(SI)±1,  (DI)←(DI)±1
字操作：(SI)←(SI)±2,  (DI)←(DI)±2

###### scas串扫描指令

格式

```
scas dst
scasb ;字节
scasw ;字
```

执行操作：
字节操作：(AL) - ((DI)),  (DI)←(DI)±1
字操作：(AX) - ((DI)),  (DI)←(DI)±2

#### 3.3.5 控制转移指令

<span>后面再看</span>

##### 1. 无条件转移指令

jmp

##### 2. 条件转移指令(p89)

jz/je
jnz
js
jns
jo
jno
jp/jpe
jnp/jpo
jb/jnae
jnb/jae/jnc

##### 3. 循环指令

###### loop

Count_Reg!=0

###### loopz/loope

Count_Reg!=0 && zf=1

###### loopnz/loopne

Count_Reg!=0 && zf=0

##### 4. 子程序

###### call

###### ret

## 堆栈情况

![alt text](images/push_ds.png)
堆栈段（SS）没有变化，始终保持为 076B。
堆栈指针（SP）在每次执行PUSH指令后减少2，这是因为每次PUSH操作都会将一个寄存器的值（2 字节）压入堆栈。

1. 一开始，sp初始化为0
2. push ds后，sp=0000h-2=0fffeh，压入ds=075Ch
3. sub ax,ax后，ax=0
4. push ax后，sp=0fffeh-2=0fffch，压入ax=0

## 附录 DOS系统功能调用（常用）

| AH  | 功能             | 调用参数                                  | 返回参数                   |
| --- | ---------------- | ----------------------------------------- | -------------------------- |
| 00  | 程序终止         | CS=程序段前缀PSP                          |                            |
| 01  | 键盘输入并回显   |                                           | AL=输入字符                |
| 02  | 显示输出         | DL=输出字符                               |                            |
| 09  | 显示字符串       | DS:DX=串地址 字符串以'$'结尾              |                            |
| 0A  | 键盘输入到缓冲区 | DS:DX=缓冲区首址 (DS:DX)=缓冲区最大字符数 | (DS:DX+1)=实际输入的字符数 |

## 常用debug(实验书p186)

```-d```: 显示内存单元内容
```-r```: 寄存器和标志位状态
```-g```: 运行
```-t```: 单步运行
```-u```: 反汇编
```-q```: 退出

|标志名|置位|复位|
|------|------|------|
|溢出Overflow|是OV|否NV|
|方向Direction|减量DN|增量UP|
|中断Interrupt|允许EI|屏蔽DI|
|符号Sign|负NG|正PL|
|零Zero|是ZR|否NZ|
|辅助进位Auxiliary Carry|是AC|否NA|
|奇偶Parity|偶PE|奇PO|
|进位Carry|是CY|否NC|

## 实验代码

### 成绩排名

```
datarea segment
    grade   dw 88,75,95,63,98,78,87,73,90,60
    rank    dw 10 dup(?)
datarea ends
prognam segment
main proc far
               assume cs:prognam,ds:datarea,es:datarea
    start:     
               push   ds
               sub    ax,ax
               push   ax
               mov    ax,datarea
               mov    ds,ax
               mov    es,ax
               call   sort
               call   output
               ret
main endp
sort proc
               mov    si,0
               mov    cx,10
    outer_loop:
               push   cx
               mov    cx,10
               mov    dx,1
               mov    ax,grade[si]
               mov    di,offset grade
    inner_loop:
               cmp    ax,[di]
               jge    no_add
               inc    dx
    no_add:    
               add    di,2
               loop   inner_loop
               pop    cx
               mov    rank[si],dx
               add    si,2
               loop   outer_loop
               ret
sort endp
output proc
               mov    cx,10
               mov    si,0
    t1:        
               push   cx
               mov    ax,rank[si]
               call   print_dec
               mov    dl,' '
               call   putchar
               pop    cx
               add    si,2
               loop   t1
               ret
output endp
putchar proc
               mov    ah,2
               int    21h
               ret
putchar endp
print_dec proc
    ;ax/?=al...ah, result:al,ah
               mov    bl,10
               div    bl
               mov    bx,ax
               mov    dl,bl
               add    dl,'0'
               call   putchar
               mov    dl,bh
               add    dl,'0'
               call   putchar
               ret
print_dec endp
prognam ends
end start
```

### ASCII码表

```
datarea segment
datarea ends
prognam segment
main proc far
             assume ds:datarea,cs:prognam,es:datarea
    start:   
             push   ds
             sub    ax,ax
             push   ax
             mov    ax,datarea
             mov    ds,ax
             mov    es,ax

             mov    dx,10h
             mov    bx,0
    rotate:  
             mov    ah,2
             int    21h
             inc    bx
             inc    dx
             push   dx
             cmp    bx,16
             mov    dl,' '
             mov    ah,2
             int    21h
             jl     continue
             xor    bx,bx
             mov    dl,0dh
             mov    ah,2
             int    21h
             mov    dl,0ah
             mov    ah,2
             int    21h
    continue:
             pop    dx
             cmp    dx,100h
             jl     rotate
             ret
main endp
prognam ends
end start
```

### 反转字符串

我流版

```
datarea segment
    limit   db 30
    len     db ?
    str     db 30 dup('$')
datarea ends
prognam segment
main proc far
            assume cs:prognam,ds:datarea,es:datarea
    start:  
            push   ds
            sub    ax,ax
            push   ax
            mov    ax,datarea
            mov    ds,ax
            mov    es,ax

            ;输入字符串
            lea    dx,limit
            mov    ah,0ah
            int    21h
            ;回车换行
            mov    dl,0dh
            mov    ah,2
            int    21h
            mov    dl,0ah
            mov    ah,2
            int    21h
            ;di置为字符串长度减一，cx计数器置为字符串长度除以2
            mov    si,0
            mov    bl,len
            xor    bh,bh
            mov    di,bx
            dec    di
            mov    cx,1
            ;除以2
            shr    bx,cl
            mov    cx,bx
    rotate: 
            mov    al,str[si]
            mov    bl,str[di]
            mov    str[si],bl
            mov    str[di],al
            inc    si
            dec    di
            loop   rotate
            lea    dx,str
            mov    ah,9
            int    21h
            ret
main endp
prognam ends
end start
```

ppt递归版

```
datarea segment
    str     db "123456",'$'
datarea ends
prognam segment
main proc far
            assume cs:prognam,ds:datarea,es:datarea
    start:  
            push   ds
            sub    ax,ax
            push   ax
            mov    ax,datarea
            mov    ds,ax
            mov    es,ax

            mov    bx, offset str
            push   bx
            call   revers
            pop    bx
            mov    dl, [bx]
            mov    ah, 2
            int    21h

            ret
main endp
revers proc  near
            push   bp
            mov    bp, sp
            push   ax
            push   bx
            push   dx
            mov    bx, [bp+4]
            mov    al, [bx]
            cmp    al, '$'
            je     return
    re_call:
            inc    bx
            push   bx
            call   revers
            pop    bx
            mov    dl, [bx]
            mov    ah, 2
            int    21h
    return: 
            pop    dx
            pop    bx
            pop    ax
            pop    bp
            ret
revers endp

prognam ends
end start
```

### 查找子串位置，十进制、十六进制输出

```
datarea segment
                 sentence_label label byte
    sentence_max db             50
    sentence_len db             ?
    sentence     db             50 dup('$')
                 key_label      label byte
    key_max      db             30
    key_len      db             ?
    key          db             30 dup('$')

    cmd1         db             'Input a sentence:','$'
    cmd2         db             'Input a keyword:','$'
    no_match_str db             'No match!',0dh,0ah,'$'
    match_str    db             "The location:",'$'
    crlf_str     db             0dh,0ah,'$'

datarea ends
prognam segment
main proc far
                 assume cs:prognam,ds:datarea,es:datarea
    start:       
                 push   ds
                 sub    ax,ax
                 push   ax
                 mov    ax,datarea
                 mov    ds,ax
                 mov    es,ax
    loops:       
                 lea    dx,cmd1
                 call   cout
                 call   cin_sentence
                 call   crlf
                 cmp    sentence[0],3                       ;比较ctrl+c
                 je     exit
                 lea    dx,cmd2
                 call   cout
                 call   cin_key
                 call   crlf
                 call   compare
                 jmp    loops
    exit:        
                 ret
main endp
cin proc
                 mov    ah,0ah
                 int    21h
                 ret
cin endp
cin_sentence proc
                 lea    dx,sentence_label
                 call   cin
                 ret
cin_sentence endp
cin_key proc
                 lea    dx,key_label
                 call   cin
                 ret
cin_key endp
cout proc
                 mov    ah,09h
                 int    21h
                 ret
cout endp
crlf proc
                 lea    dx,crlf_str
                 call   cout
                 ret
crlf endp
compare proc
    ;cx=sentence_len-key_len+1
                 xor    ch,ch
                 xor    dh,dh
                 xor    bx,bx
                 mov    cl,sentence_len
                 mov    dl,sentence_len
                 sub    cx,dx
                 inc    cx
    rotate:      
                 lea    si,sentence[bx]
                 lea    di,key
                 mov    cl,key_len
                 xor    ch,ch
                 cld
                 rep    cmpsb
                 jz     match
                 inc    bx
                 loop   rotate
    no_match:    
                 lea    dx,no_match_str
                 call   cout
                 ret
    match:       
                 lea    dx,match_str
                 call   cout
                 call   print_dec
                 call   crlf

                 lea    dx,match_str
                 call   cout
                 call   print_hex
                 call   crlf

                 ret
compare endp
    ;打印十进制数字
print_dec proc
    ;ax/?=al...ah
                 push   bx
                 mov    ax,bx
                 xor    cx,cx
    div10:       
                 mov    bl,10
                 div    bl
                 push   ax
                 inc    cx
                 xor    ah,ah
                 cmp    al,0
                 jne    div10
    print10:     
                 pop    dx
                 mov    dl,dh
                 add    dl,30h
                 mov    ah,2
                 int    21h
                 loop   print10
                 pop    bx
                 ret
print_dec endp
    ;打印十六进制数字
print_hex proc
                 push   bx
                 xor    ax,ax
    div16:       
                 mov    dx,0fh
                 and    dx,bx
                 push   dx
                 inc    ax
                 mov    cl,4
                 shr    bx,cl
                 cmp    bx,0
                 jne    div16
                 mov    cx,ax
    print16:     
                 pop    dx
                 add    dx,'0'
                 cmp    dx,'9'
                 jle    not_letter
                 add    dx,'A'-'0'-10
    not_letter:  
                 mov    ah,2
                 int    21h
                 loop   print16
                 pop    bx
                 ret
print_hex endp
prognam ends
end start
```
