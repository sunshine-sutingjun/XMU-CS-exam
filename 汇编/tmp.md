## 三、A+(B*10+C)/D
```
data segment
    a dw 100
    b dw 200
    numc dw 300
    d dw 23
data ends
code segment
main proc far
assume cs:code,ds:data
start:
    push ds
    sub ax,ax
    push ax
    mov ax,data
    mov ds,ax

    mov ax,b
    mov bx,10
    ;注意不能直接imul 10，会报错
    imul bx
    mov bx,ax
    mov cx,dx
    ;注意加数要先转移到ax中cwd
    mov ax,numc
    cwd
    add ax,bx
    adc dx,cx
    idiv d

    mov bx,ax
    mov cx,dx
    
    mov ax,a
    cwd
    add ax,bx
    adc cx,dx

    ret
main endp
code ends
end start
```
结果存放在dx,ax中

## 四、
```
data segment
    a dw 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
    b dw 20, 18, 16, 14, 12, 10, 8, 6, 4, 2, 0, 21, 23, 25, 27, 29, 31, 33, 34,
35

data ends
code segment
main proc far
assume cs:code,ds:data,es:data
start:
    push ds
    sub ax,ax
    push ax
    mov ax,data
    mov ds,ax
    mov es,ax

    lea si,a
    mov cx,15
outloop:
    lea di,b
    
    push cx
    mov cx,20
innerloop:
    mov bx,[si]
    cmp bx,[di]
    jnz next
    call output
next:
    add di,2
    loop innerloop
    pop cx
    add si,2
    loop outloop
    ret
main endp
output proc near
    mov cx,10d
    call divbx
    mov cx,1d
    call divbx
    call crlf
    ret
output endp
divbx proc near
    mov ax,bx
    mov dx,0
    div cx
    mov bx,dx
    mov dl,al
    add dl,30h
    mov ah,02h
    int 21h
    ret
divbx endp
crlf proc near
    mov dl,0ah
    mov ah,02h
    int 21h
    mov dl,0dh
    mov ah,02h
    int 21h
    ret
crlf endp
code ends
end start
```