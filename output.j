.source tests/op-matematicas
.class public test
.super java/lang/Object

.method public <init>()V
aload_0
invokenonvirtual java/lang/Object/<init>()V
return
.end method

.method public static main([Ljava/lang/String;)V
.limit locals 100
.limit stack 100
iconst_0
istore 1
fconst_0
fstore 2
.line 1
iconst_0
istore 3
.line 2
L_0:
iconst_0
istore 4
.line 3
L_1:
ldc 5
istore 4
.line 4
.line 5
L_2:
iconst_0
istore 5
.line 6
L_3:
ldc 130
istore 5
.line 7
.line 8
L_4:
iconst_0
istore 6
.line 9
L_5:
ldc 65536
istore 6
.line 10
.line 11
L_6:
iconst_0
istore 7
.line 12
L_7:
ldc -300
istore 7
.line 13
.line 14
L_8:
iconst_0
istore 8
.line 15
L_9:
ldc -11
istore 8
.line 16
.line 17
L_10:
iconst_0
istore 9
.line 18
L_11:
ldc 500
istore 9
.line 19
.line 20
L_12:
fconst_0
fstore 10
.line 21
L_13:
ldc 1.100000
fstore 10
.line 22
L_14:
ldc 6
iload 4
iadd
istore 3
.line 23
L_15:
iload 5
iload 7
irem
istore 4
.line 24
.line 25
L_16:
iload 3
ldc 5
if_icmpeq L_22
goto L_17
L_17:
iload 3
ldc 7
if_icmpge L_22
goto L_18
L_18:
iload 3
ldc 7
if_icmple L_22
goto L_19
L_19:
iload 3
ldc 7
if_icmpgt L_22
goto L_20
L_20:
iload 3
ldc 7
if_icmplt L_22
goto L_21
L_21:
iload 3
ldc 7
if_icmpne L_22
goto L_24
L_22:
.line 26
iload 6
istore 1
getstatic      java/lang/System/out Ljava/io/PrintStream;
iload 1
invokevirtual java/io/PrintStream/println(I)V
.line 27
L_23:
iload 3
istore 1
getstatic      java/lang/System/out Ljava/io/PrintStream;
iload 1
invokevirtual java/io/PrintStream/println(I)V
.line 28
goto L_25
.line 29
.line 30
L_24:
.line 31
fload 10
fstore 2
getstatic      java/lang/System/out Ljava/io/PrintStream;
fload 2
invokevirtual java/io/PrintStream/println(F)V
.line 32
.line 33
L_25:
return
.end method
